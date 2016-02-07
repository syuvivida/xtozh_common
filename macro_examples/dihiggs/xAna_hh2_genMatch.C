// example code to run Bulk Graviton->ZZ->ZlepZhad selections on electron-channel

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <TString.h>
#include <map>
#include <TH1D.h>
#include <TFile.h>
#include "untuplizer.h"
#include <TClonesArray.h>
#include <TLorentzVector.h>

using namespace std;
void xAna_hh2_genMatch(std::string inputFile, bool debug=false){

  bool isHerwigpp=(inputFile.find("herwigpp")!= std::string::npos);
  cout << endl;
  if(isHerwigpp)cout << "Note!! This is a herwigpp MC sample " << endl;
  else
    cout << "This is a pythia8 MC sample" << endl;
  cout << endl;
  //get TTree from file ...
  TreeReader data(inputFile.data());
  
  Long64_t nTotal=0;
  Long64_t nPass[20]={0};

  TH1F* h_SD=new TH1F("h_SD","",100,0,200);
  TH1F* h_hh=new TH1F("h_hh","",900,0,4500);

  for(Long64_t jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    if (jEntry % 50000 == 0)
      fprintf(stderr, "Processing event %lli of %lli\n", jEntry + 1, data.GetEntriesFast());


    if(debug && jEntry>10)break;

    data.GetEntry(jEntry);
    nTotal++;


    Int_t nGenPar        = data.GetInt("nGenPar");
    Int_t* genParId      = data.GetPtrInt("genParId");
    Int_t* genParSt      = data.GetPtrInt("genParSt");
    Int_t* genMomParId   = data.GetPtrInt("genMomParId");

    int genHIndex[2]={-1,-1};

    for(int ig=0; ig < nGenPar; ig++){

      if(genParId[ig]!=25)continue;

      if(isHerwigpp && genMomParId[ig]!=25)continue;

      if(genHIndex[0]<0)
	genHIndex[0]=ig;

      else if(genHIndex[1]<0)
	genHIndex[1]=ig;

    }    

    if(genHIndex[0]<0 || genHIndex[1]<0)continue;
    nPass[0]++;

    if(genHIndex[0]==genHIndex[1])continue;
    nPass[1]++;

    TLorentzVector genH_l4[2];
    TClonesArray* genParP4 = (TClonesArray*) data.GetPtrTObject("genParP4");

    for(int ih=0; ih<2; ih++)
      genH_l4[ih] = *((TLorentzVector*)genParP4->At(genHIndex[ih]));


    if(debug){
      cout << genHIndex[0] << "\t" << genHIndex[1] << endl;
      genH_l4[0].Print();
      genH_l4[1].Print();

    }
    int nFATJet         = data.GetInt("FATnJet");
    const int nJets=nFATJet;
    TClonesArray* fatjetP4 = (TClonesArray*) data.GetPtrTObject("FATjetP4");

    // check matching first

    bool findAMatch=false;
    const float dRMax=0.4;
    int matchedHJetIndex[2]={-1,-1};
		      
    for(int ij=0; ij<nJets; ij++)
      {
	TLorentzVector* thisJet = (TLorentzVector*)fatjetP4->At(ij);

	for(int jj=0; jj<nJets; jj++)
	  {

	    if(ij==jj)continue;
	    TLorentzVector* thatJet = (TLorentzVector*)fatjetP4->At(jj);
	    
	    if(thisJet->DeltaR(genH_l4[0])<dRMax && 
	       thatJet->DeltaR(genH_l4[1])<dRMax)
	      {
		matchedHJetIndex[0]=ij;
		matchedHJetIndex[1]=jj;
		findAMatch=true;
		break;
	      }

	    if(findAMatch)break;

	  }	

	if(findAMatch)break;

      }

    if(!findAMatch)continue;
    if(debug)
      cout << matchedHJetIndex[0] << "\t" << matchedHJetIndex[1] << endl;
    nPass[2]++;

    Int_t event        = data.GetInt("eventId");
    //0. has a good vertex
    Int_t nVtx        = data.GetInt("nVtx");
    if(nVtx<1)continue;
    nPass[3]++;

    Float_t*  fatjetTau1 = data.GetPtrFloat("FATjetTau1");
    Float_t*  fatjetTau2 = data.GetPtrFloat("FATjetTau2");
    Float_t*  fatjetCISVV2 = data.GetPtrFloat("FATjetCISVV2");
    Float_t*  fatjetPRmass = data.GetPtrFloat("FATjetPRmass");
    Float_t*  fatjetPRmassL2L3Corr = data.GetPtrFloat("FATjetPRmassL2L3Corr");
    Int_t*   nSubSoftDropJet = data.GetPtrInt("FATnSubSDJet");
    vector<float>   *subjetSDCSV =  data.GetPtrVectorFloat("FATsubjetSDCSV", nFATJet);
    vector<float>   *subjetSDPx  =  data.GetPtrVectorFloat("FATsubjetSDPx", nFATJet);
    vector<float>   *subjetSDPy  =  data.GetPtrVectorFloat("FATsubjetSDPy", nFATJet);
    vector<float>   *subjetSDPz  =  data.GetPtrVectorFloat("FATsubjetSDPz", nFATJet);
    vector<float>   *subjetSDE   =  data.GetPtrVectorFloat("FATsubjetSDE", nFATJet);
    vector<bool>    &passFatJetLooseID = *((vector<bool>*) data.GetPtr("FATjetPassIDLoose"));
    
    TLorentzVector recoH_l4[2];
    int nGoodJets=0;
    for(int i=0; i<2; i++)
      {
    	
	int ij = matchedHJetIndex[i];
     	TLorentzVector* thisJet = (TLorentzVector*)fatjetP4->At(ij);
	recoH_l4[i]= (*thisJet);
    	if(thisJet->Pt()<200)continue;
	if(fabs(thisJet->Eta())>2.4)continue;
	nGoodJets++;
      }

    if(nGoodJets<2)continue;
    nPass[4]++;
    
    if(debug)
      {
	recoH_l4[0].Print();
	recoH_l4[1].Print();
      }

    float dEta=fabs(recoH_l4[0].Eta()-recoH_l4[1].Eta());
    if(dEta>1.3)continue;
    nPass[5]++;

    float M=(recoH_l4[0] + recoH_l4[1]).M();
    if(M<1000)continue;
    nPass[6]++;

    nGoodJets=0;
    for(int i=0; i<2; i++)
      {
    	
	int ij = matchedHJetIndex[i];

	if(fatjetPRmassL2L3Corr[ij]<105 ||
	   fatjetPRmassL2L3Corr[ij]>135)continue;
	nGoodJets++;
      }

    if(nGoodJets<2)continue;
    nPass[7]++;

    int nHP=0;
    int nLP=0;
    for(int i=0; i<2; i++)
      {
    	
	int ij = matchedHJetIndex[i];

	float tau21_i = fatjetTau2[ij]/fatjetTau1[ij];
	bool isHP= (tau21_i < 0.6);
	bool isLP= (tau21_i < 0.75);
       
	if(isHP)nHP++;
	if(isLP)nLP++;
      }

    if(nHP==0 && nLP<2)continue;
    nPass[8]++;

    int nSubBJet=0;

    for(int i=0; i<2; i++)
      {    	
	int ij = matchedHJetIndex[i];
	for(int is=0; is < nSubSoftDropJet[ij]; is++){
	  if(subjetSDCSV[ij][is] < 0.605)continue;
	  nSubBJet++;
	}
      }
    nPass[9+nSubBJet]++;

    

  } // end of loop over entries

  std::cout << "nTotal    = " << nTotal << std::endl;
  for(int i=0;i<20;i++)
    if(nPass[i]>0)
      std::cout << "nPass[" << i << "]= " << nPass[i] << std::endl;

  TFile* outFile = new TFile("test.root","recreate");

  h_hh->Write();
  outFile->Close();



}
