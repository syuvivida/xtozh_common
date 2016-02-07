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
void xAna_hh2(std::string inputFile){

  //get TTree from file ...
  TreeReader data(inputFile.data());

  Long64_t nTotal=0;
  Long64_t nPass[20]={0};

  TH1F* h_SD=new TH1F("h_SD","",100,0,200);
  TH1F* h_hh=new TH1F("h_hh","",900,0,4500);
  //Event loop
  ofstream fout;
  fout.open("eiko.dat");

  for(Long64_t jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    if (jEntry % 50000 == 0)
      fprintf(stderr, "Processing event %lli of %lli\n", jEntry + 1, data.GetEntriesFast());

    data.GetEntry(jEntry);
    nTotal++;
    Int_t event        = data.GetInt("eventId");
    //0. has a good vertex
    Int_t nVtx        = data.GetInt("nVtx");
    if(nVtx<1)continue;
    nPass[0]++;

    int nFATJet         = data.GetInt("FATnJet");
    const int nJets=nFATJet;
    TClonesArray* fatjetP4 = (TClonesArray*) data.GetPtrTObject("FATjetP4");
    Float_t*  fatjetTau1 = data.GetPtrFloat("FATjetTau1");
    Float_t*  fatjetTau2 = data.GetPtrFloat("FATjetTau2");
    Float_t*  fatjetCISVV2 = data.GetPtrFloat("FATjetCISVV2");
    Float_t*  fatjetPRmass = data.GetPtrFloat("FATjetPRmass");
    Float_t*  fatjetPRmassL2L3Corr = data.GetPtrFloat("FATjetPRmassL2L3Corr");
    Float_t*  fatjetSDmass = data.GetPtrFloat("FATjetSDmass");
    Int_t*   nSubSoftDropJet = data.GetPtrInt("FATnSubSDJet");
    vector<float>   *subjetSDCSV =  data.GetPtrVectorFloat("FATsubjetSDCSV");
    //  vector<float>   *subjetSDCSV =  data.GetPtrVectorFloat("FATsubjetSDCSV", nFATJet);
    vector<float>   *subjetSDPx  =  data.GetPtrVectorFloat("FATsubjetSDPx", nFATJet);
    vector<float>   *subjetSDPy  =  data.GetPtrVectorFloat("FATsubjetSDPy", nFATJet);
    vector<float>   *subjetSDPz  =  data.GetPtrVectorFloat("FATsubjetSDPz", nFATJet);
    vector<float>   *subjetSDE   =  data.GetPtrVectorFloat("FATsubjetSDE", nFATJet);
    vector<bool>    &passFatJetLooseID = *((vector<bool>*) data.GetPtr("FATjetPassIDLoose"));
    
    int nFatBTag=0;
    int leadB=-1;
    int subB=-1;
    vector<int> myJets;
    for(int ij=0; ij<nJets; ij++)
      {
    	
     	TLorentzVector* thisJet = (TLorentzVector*)fatjetP4->At(ij);
    	if(thisJet->Pt()<200)continue;
	if(fabs(thisJet->Eta())>2.4)continue;
    	// // if(fatjetSDmass[ij]<95 || fatjetSDmass[ij]>145)continue;
	// if(!passFatJetLooseID[ij])continue;
	
    	// if(fatjetCISVV2[ij] < 0.605)continue;
    	// if(fatjetCISVV2[ij] > 1)continue;

	// if(leadB<0)leadB=ij;
	// else if(subB<0)subB=ij;

    	nFatBTag++;
	myJets.push_back(ij);

      }
    
    if(nFatBTag<1)continue;
    //    if(nJets<1)continue;
    nPass[1]++;

    bool findAPair=false;
    int bindex1=-1;
    int bindex2=-1;

    for(unsigned int i=0; i < myJets.size(); i++)
      {
	TLorentzVector* thish = (TLorentzVector*)fatjetP4->At(myJets[i]); 
	
	float tau21_i = fatjetTau2[myJets[i]]/fatjetTau1[myJets[i]];
	bool isHP_this= (tau21_i < 0.6);
	bool isLP_this= (tau21_i < 0.75);
       
	
	for(unsigned int j=i+1; j < myJets.size(); j++)
	  {
	    TLorentzVector* thath = (TLorentzVector*)fatjetP4->At(myJets[j]); 
	    float dEta=fabs(thish->Eta()-thath->Eta());
	    if(dEta>1.3)continue;
	    float M=(*thish + *thath).M();
	    if(M<1000)continue;
	    if(fatjetPRmassL2L3Corr[myJets[i]]<105 ||
	       fatjetPRmassL2L3Corr[myJets[i]]>135)continue;
	    if(fatjetPRmassL2L3Corr[myJets[j]]<105 ||
	       fatjetPRmassL2L3Corr[myJets[j]]>135)continue;

	    
	    float tau21_j = fatjetTau2[myJets[j]]/fatjetTau1[myJets[j]];
	    bool isHP_that= (tau21_j < 0.6);
	    bool isLP_that= (tau21_j < 0.75);

	    if(!isLP_this || !isLP_that)continue;
	    if(!isHP_this && !isHP_that)continue;
	    if(!findAPair){
	      bindex1=myJets[i];
	      bindex2=myJets[j];
	    }
	    findAPair=true;
	    break;
	  }
	//	if(findAPair)break;
      }
    if(!findAPair)continue;
    if(bindex1<0)continue;
    if(bindex2<0)continue;

    nPass[2]++;

    fout << event << "\t" << bindex1 << "\t" << bindex2 << endl;
    int nSubBJet=0;

    for(int is=0; is < nSubSoftDropJet[bindex1]; is++){
      if(subjetSDCSV[bindex1][is] < 0.605)continue;
      nSubBJet++;
    }
    for(int is=0; is < nSubSoftDropJet[bindex2]; is++){
      if(subjetSDCSV[bindex2][is] < 0.605)continue;
      nSubBJet++;
    }
    
    nPass[3+nSubBJet]++;

    

  } // end of loop over entries

  fout.close();

  std::cout << "nTotal    = " << nTotal << std::endl;
  for(int i=0;i<20;i++)
    if(nPass[i]>0)
      std::cout << "nPass[" << i << "]= " << nPass[i] << std::endl;

  TFile* outFile = new TFile("test.root","recreate");

  h_hh->Write();
  outFile->Close();



}
