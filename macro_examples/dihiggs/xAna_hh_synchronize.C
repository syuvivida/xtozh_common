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
void xAna_hh_synchronize(std::string inputFile){

  //get TTree from file ...
  TreeReader data(inputFile.data());

  Long64_t nTotal=0;
  Long64_t nPass[20]={0};

  TH1F* h_tau21=new TH1F("h_tau21","",100,0,1);
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



    //2. pass electron or muon trigger
    std::string* trigName = data.GetPtrString("hlt_trigName");
    vector<bool> &trigResult = *((vector<bool>*) data.GetPtr("hlt_trigResult"));
    const Int_t nsize = data.GetPtrStringSize();

    bool passTrigger=false;
    for(int it=0; it< nsize; it++)
      {
	std::string thisTrig= trigName[it];
	bool results = trigResult[it];

	// std::cout << thisTrig << " : " << results << std::endl;
	
	if( (thisTrig.find("HLT_PFHT900_v")!= std::string::npos && results==1)
	    )
	  {
	    passTrigger=true;
	    break;
	  }


      }

    if(!passTrigger)continue;
    nPass[1]++;

    int nFATJet         = data.GetInt("FATnJet");
    const int nJets=nFATJet;
    TClonesArray* fatjetP4 = (TClonesArray*) data.GetPtrTObject("FATjetP4");
    Float_t*  fatjetTau1 = data.GetPtrFloat("FATjetTau1");
    Float_t*  fatjetTau2 = data.GetPtrFloat("FATjetTau2");
    Float_t*  fatjetTau4 = data.GetPtrFloat("FATjetTau4");
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
    
    if(nJets<2)continue;
    int nGoodJets=0;
    for(int ij=0; ij<2; ij++)
      {
    	
     	TLorentzVector* thisJet = (TLorentzVector*)fatjetP4->At(ij);
	if(thisJet->Pt()<200)continue;
	//	if(fabs(thisJet->Eta())>2.4)continue;

	// if(fatjetPRmassL2L3Corr[ij]<105 ||
	//    fatjetPRmassL2L3Corr[ij]>135)continue;

	    
	// float tau21_j = fatjetTau2[ij]/fatjetTau1[ij];
	// bool isHP_that= (tau21_j < 0.6);
	// bool isLP_that= (tau21_j < 0.75);
	
	// if(!isLP_that)continue;
	nGoodJets++;
      }

    if(nGoodJets<2)continue;
    nPass[2]++;
    	

    nGoodJets=0;
    for(int ij=0; ij<2; ij++)
      {
    	
     	TLorentzVector* thisJet = (TLorentzVector*)fatjetP4->At(ij);
	if(thisJet->Pt()<200)continue;
	if(fabs(thisJet->Eta())>2.4)continue;

	// if(fatjetPRmassL2L3Corr[ij]<105 ||
	//    fatjetPRmassL2L3Corr[ij]>135)continue;

	    
	// float tau21_j = fatjetTau2[ij]/fatjetTau1[ij];
	// bool isHP_that= (tau21_j < 0.6);
	// bool isLP_that= (tau21_j < 0.75);
	
	// if(!isLP_that)continue;
	nGoodJets++;
      }

    if(nGoodJets<2)continue;
    nPass[3]++;


    TLorentzVector* thisJet = (TLorentzVector*)fatjetP4->At(0);
    TLorentzVector* thatJet = (TLorentzVector*)fatjetP4->At(1);
    
    float dEta = fabs(thisJet->Eta()-thatJet->Eta());

    if(dEta>1.3)continue;
    nPass[4]++;

    float mjj = (*thisJet+*thatJet).M();

    if(mjj<800)continue;

    nPass[5]++;

    
    nGoodJets=0;
    for(int ij=0; ij<2; ij++)
      {
    	
     	TLorentzVector* thisJet = (TLorentzVector*)fatjetP4->At(ij);
	if(thisJet->Pt()<200)continue;
	if(fabs(thisJet->Eta())>2.4)continue;

	// if(fatjetPRmassL2L3Corr[ij]<105 ||
	//    fatjetPRmassL2L3Corr[ij]>135)continue;
	    
        float tau21_j = fatjetTau2[ij]/fatjetTau1[ij];
	bool isHP_that= (tau21_j < 0.6);
	// bool isLP_that= (tau21_j < 0.75);
	h_tau21->Fill(tau21_j);
	
        if(!isHP_that)continue;
	nGoodJets++;
      }

    if(nGoodJets<2)continue;
    nPass[6]++;




    nGoodJets=0;
    for(int ij=0; ij<2; ij++)
      {
    	
     	TLorentzVector* thisJet = (TLorentzVector*)fatjetP4->At(ij);
	if(thisJet->Pt()<200)continue;
	if(fabs(thisJet->Eta())>2.4)continue;

	if(fatjetPRmassL2L3Corr[ij]<105 ||
	   fatjetPRmassL2L3Corr[ij]>135)continue;

	    
        float tau21_j = fatjetTau2[ij]/fatjetTau1[ij];
	bool isHP_that= (tau21_j < 0.6);
	// bool isLP_that= (tau21_j < 0.75);
	
        if(!isHP_that)continue;
	nGoodJets++;
      }

    if(nGoodJets<2)continue;
    nPass[7]++;

  } // end of loop over entries

  fout.close();

  std::cout << "nTotal    = " << nTotal << std::endl;
  for(int i=0;i<20;i++)
    if(nPass[i]>0)
      std::cout << "nPass[" << i << "]= " << nPass[i] << std::endl;
  for(int i=0; i<8;i++)
    {
      std::cout << " & " << nPass[i];}
  cout << "\\\\" << endl;
  TFile* outFile = new TFile("test.root","recreate");
  h_tau21->Write();
  h_hh->Write();
  outFile->Close();



}
