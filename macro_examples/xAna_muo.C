// example code to run Bulk Graviton->ZZ->ZlepZhad selections on muon-channel


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
void xAna_muo(std::string inputFile){

  //get TTree from file ...
  TreeReader data(inputFile.data());

  Long64_t nTotal=0;
  Long64_t nPass[20]={0};
  ofstream fout;
  fout.open("muo_Eiko.txt");
  TH1F* h_SD=new TH1F("h_SD","",100,0,200);
  //Event loop
  for(Long64_t jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    if (jEntry % 50000 == 0)
      fprintf(stderr, "Processing event %lli of %lli\n", jEntry + 1, data.GetEntriesFast());

    data.GetEntry(jEntry);
    nTotal ++;

    // 0. check the generator-level information and make sure there is a Z->mm
    Int_t nGenPar        = data.GetInt("nGenPar");
    Int_t* genParId      = data.GetPtrInt("genParId");
    Int_t* genParSt      = data.GetPtrInt("genParSt");
    Int_t* genMomParId   = data.GetPtrInt("genMomParId");
    Int_t* genDa1      = data.GetPtrInt("genDa1");
    Int_t* genDa2      = data.GetPtrInt("genDa2");


    bool hasLepton=false;

    for(int ig=0; ig < nGenPar; ig++){

      if(genParId[ig]!=23)continue;
      int da1=genDa1[ig];
      int da2=genDa2[ig];

      if(da1<0 || da2<0)continue;
      int da1pdg = genParId[da1];
      int da2pdg = genParId[da2];

      if(abs(da1pdg)==13)
     	hasLepton=true;

      if(hasLepton)break;

    }

    bool hasHadron=false;

    for(int ig=0; ig < nGenPar; ig++){

      if(genParId[ig]!=23)continue;
      int da1=genDa1[ig];
      int da2=genDa2[ig];

      if(da1<0 || da2<0)continue;
      int da1pdg = genParId[da1];
      int da2pdg = genParId[da2];

      if(abs(da1pdg)>0 && abs(da1pdg)<6)
     	hasHadron=true;

      if(hasHadron)break;

    }
    
    if(!hasLepton)continue;
    nPass[0]++;
    if(!hasHadron)continue;
    nPass[1]++;

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
	
 	if( (thisTrig.find("HLT_Ele105")!= std::string::npos && results==1)
	    ||
	    (thisTrig.find("HLT_Mu45")!= std::string::npos && results==1)
	    )
 	  {
 	    passTrigger=true;
 	    break;
 	  }


      }


    if(!passTrigger)continue;
    nPass[2]++;

    //3. has a good vertex
    Int_t nVtx        = data.GetInt("nVtx");
    if(nVtx<1)continue;
    nPass[3]++;

    //4. look for mymuons first
    Int_t nMu          = data.GetInt("nMu");
    Int_t run          = data.GetInt("runId");
    Int_t lumi         = data.GetInt("lumiSection");
    Int_t event        = data.GetInt("eventId");
    vector<bool> &isHighPtMuon = *((vector<bool>*) data.GetPtr("isHighPtMuon"));
    vector<bool> &isCustomTrackerMuon = *((vector<bool>*) data.GetPtr("isCustomTrackerMuon"));
    TClonesArray* muP4 = (TClonesArray*) data.GetPtrTObject("muP4");
    Int_t*   muCharge        = data.GetPtrInt("muCharge");
    Float_t* muMiniIso       = data.GetPtrFloat("muMiniIso");

    //5. select  mymuons
    std::vector<int> myMuons;

    for(int im=0; im< nMu; im++)
      {

    	TLorentzVector* thisMu = (TLorentzVector*)muP4->At(im);

    	if(fabs(thisMu->Eta())>2.1)continue;

    	if(thisMu->Pt() < 50)continue;

    	if(!isHighPtMuon[im] && !isCustomTrackerMuon[im])continue;
    	
    	if(muMiniIso[im]>0.1)continue;

    	myMuons.push_back(im);
      }

    //6. select a good Z boson
    bool findMPair=false;
    TLorentzVector l4_Z(0,0,0,0);

    for(unsigned int i=0; i< myMuons.size(); i++)
      {
	int im = myMuons[i];
	TLorentzVector* thisMu = (TLorentzVector*)muP4->At(im);

	for(unsigned int j=0; j< i; j++)
	  {
	    int jm= myMuons[j];

	    if(muCharge[im]*muCharge[jm]>0)continue;

	    TLorentzVector* thatMu = (TLorentzVector*)muP4->At(jm);

	    Float_t mll  = (*thisMu+*thatMu).M();
	    Float_t ptll = (*thisMu+*thatMu).Pt();
	    

	    if(mll<70 || mll>110)continue;
	    if(ptll<200)continue;

	    if(! 
	       ((isHighPtMuon[im] && isCustomTrackerMuon[jm]) ||
		(isHighPtMuon[jm] && isCustomTrackerMuon[im])
		))
	      continue;

	    if(!findMPair)l4_Z=(*thisMu+*thatMu);

	    findMPair=true;
	  }	
      }

    if(!findMPair)
      continue;
    nPass[4]++;

    //7. select a good CA8 and cleaned jet
    // first select muons for cleaning against jet
    std::vector<int> goodMuons;

    for(int im=0; im< nMu; im++)
      {

    	TLorentzVector* thisMu = (TLorentzVector*)muP4->At(im);

    	if(!isHighPtMuon[im] && !isCustomTrackerMuon[im])continue;
    	
    	if(muMiniIso[im]>0.1)continue;	

        if ( goodMuons.size()==1 ) {
	  bool highPt_AND_tracker = isHighPtMuon[0] && isCustomTrackerMuon[im];
	  bool tracker_AND_highPt = isHighPtMuon[im] && isCustomTrackerMuon[0]; 
	  if ( !(highPt_AND_tracker or tracker_AND_highPt) ) continue; 
        }

    	if(fabs(thisMu->Eta())>2.1)continue;

    	if(thisMu->Pt() < 50)continue;

    	goodMuons.push_back(im);
      }

    // second select good electrons for cleaning against jets
    Int_t nEle         = data.GetInt("nEle");
    vector<bool> &passHEEPID = *((vector<bool>*) data.GetPtr("eleIsPassHEEPNoIso"));
    TClonesArray* eleP4 = (TClonesArray*) data.GetPtrTObject("eleP4");
    Float_t* eleSCEta         = data.GetPtrFloat("eleScEta");
    Float_t* eleMiniIso       = data.GetPtrFloat("eleMiniIso");

    std::vector<int> goodElectrons;

    for(int ie=0; ie< nEle; ie++)
      {

    	TLorentzVector* thisEle = (TLorentzVector*)eleP4->At(ie);

    	if(fabs(thisEle->Eta())>2.5)continue;

    	if(! (fabs(eleSCEta[ie])<1.442 || fabs(eleSCEta[ie])>1.566))continue;
    	
    	if(thisEle->Pt() < 115)continue;

    	if(!passHEEPID[ie])continue;
    	
    	if(eleMiniIso[ie]>0.1)continue;

    	goodElectrons.push_back(ie);
      }

	
    Int_t nJet         = data.GetInt("FATnJet");
    TClonesArray* jetP4 = (TClonesArray*) data.GetPtrTObject("FATjetP4");
    Float_t*  jetSDmass = data.GetPtrFloat("FATjetSDmass");

    TLorentzVector l4_leadingJet(0,0,0,0);
    bool findAJet=false;
    for(int ij=0; ij<nJet; ij++)
      {
    	
     	TLorentzVector* thisJet = (TLorentzVector*)jetP4->At(ij);

	if(jetSDmass[ij]<50 || jetSDmass[ij]>110)continue;

	bool hasOverLap=false;
	for(unsigned int ie=0; ie < goodElectrons.size(); ie++)
	  {
	    TLorentzVector* thisEle = (TLorentzVector*)eleP4->At(goodElectrons[ie]);
	    if(thisEle->DeltaR(*thisJet)<0.8)hasOverLap=true;
	    if(hasOverLap)break;
	    
	  }
	for(unsigned int im=0; im < goodMuons.size(); im++)
	  {
	    TLorentzVector* thisMuo = (TLorentzVector*)muP4->At(goodMuons[im]);
	    if(thisMuo->DeltaR(*thisJet)<0.8)hasOverLap=true;
	    if(hasOverLap)break;
	    
	  }
	
	if(hasOverLap)continue;
	
	if(thisJet->Pt()<200)continue;
	if(fabs(thisJet->Eta())>2.4)continue;

     	if(!findAJet)
	  {
	    l4_leadingJet = *thisJet;
	    h_SD->Fill(jetSDmass[ij]);
	  }
	    
     	findAJet=true;
    	

      }
   

    
    if(!findAJet)
      continue;
    nPass[5]++;

    Float_t MGrav = (l4_leadingJet + l4_Z).M();
    if(MGrav<400)continue;
    nPass[6]++;

    fout << run << " " << lumi << " " << event << endl;
    

  } // end of loop over entries

  fout.close();
  std::cout << "nTotal    = " << nTotal << std::endl;
  for(int i=0;i<20;i++)
    if(nPass[i]>0)
      std::cout << "nPass[" << i << "]= " << nPass[i] << std::endl;
    
}
