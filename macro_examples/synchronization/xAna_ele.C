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
#include "isPassZee.h"
#include "isPassZmumu.h"
#include <TClonesArray.h>
#include <TLorentzVector.h>

using namespace std;
void xAna_ele(std::string inputFile){

  //get TTree from file ...
  TreeReader data(inputFile.data());

  Long64_t nTotal=0;
  Long64_t nPass[20]={0};
  ofstream fout;
  fout.open("ele_Eiko.txt");
  //Event loop
  for(Long64_t jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    if (jEntry % 50000 == 0)
      fprintf(stderr, "Processing event %lli of %lli\n", jEntry + 1, data.GetEntriesFast());

    data.GetEntry(jEntry);
    nTotal ++;

    // 0. check the generator-level information and make sure there is a Z->e+e-
    Int_t run          = data.GetInt("runId");
    Int_t lumi         = data.GetInt("lumiSection");
    Int_t event        = data.GetInt("eventId");
    Int_t nGenPar        = data.GetInt("nGenPar");
    Int_t* genParId      = data.GetPtrInt("genParId");
    Int_t* genParSt      = data.GetPtrInt("genParSt");
    Int_t* genMomParId   = data.GetPtrInt("genMomParId");
    Int_t* genDa1      = data.GetPtrInt("genDa1");
    Int_t* genDa2      = data.GetPtrInt("genDa2");

    bool hasLepton=false;

    for(int ig=0; ig < nGenPar; ig++){

      if(genParId[ig]!=23)continue;

      // check if the mother is a bulk graviton

      if(abs(genMomParId[ig])!=39)continue;

      int da1=genDa1[ig];
      int da2=genDa2[ig];

      if(da1<0 || da2<0)continue;
      int da1pdg = genParId[da1];
      int da2pdg = genParId[da2];

      if(abs(da1pdg)==11)
     	hasLepton=true;

      if(hasLepton)break;

    }

    // // 1. make sure there is a Z-> qq 
    // bool hasHadron=false;

    // for(int ig=0; ig < nGenPar; ig++){

    //   if(genParId[ig]!=23)continue;
    //   int da1=genDa1[ig];
    //   int da2=genDa2[ig];

    //   if(da1<0 || da2<0)continue;
    //   int da1pdg = genParId[da1];
    //   int da2pdg = genParId[da2];

    //   if(abs(da1pdg)>0 && abs(da1pdg)<6)
    //  	hasHadron=true;

    //   if(hasHadron)break;

    // }
    
    if(!hasLepton)continue;
    nPass[0]++;
    // if(!hasHadron)continue;
    // nPass[1]++;
     
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
	
 	if( (thisTrig.find("HLT_Ele105_CaloIdVT_GsfTrkIdT_v")!= std::string::npos && results==1)
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

    //4. look for good electrons first
    TClonesArray* eleP4 = (TClonesArray*) data.GetPtrTObject("eleP4");

    //5. select good electrons from Z
    vector<Int_t> goodZeeID;
    if(!isPassZee(data,goodZeeID))continue;
    TLorentzVector* thisEle =  (TLorentzVector*)eleP4->At(goodZeeID[0]);   
    TLorentzVector* thatEle =  (TLorentzVector*)eleP4->At(goodZeeID[1]);   
    
    nPass[4]++;



    //7.select a good CA8 and cleaned jet

    // first select muons for cleaning against jet
    std::vector<int> goodZmmID;
    TClonesArray* muP4 = (TClonesArray*) data.GetPtrTObject("muP4");
    TLorentzVector* thisMuo;
    TLorentzVector* thatMuo; 
    bool hasMuon=isPassZmumu(data,goodZmmID);
    if(hasMuon)
      {
	thisMuo =  (TLorentzVector*)muP4->At(goodZmmID[0]);   
	thatMuo =  (TLorentzVector*)muP4->At(goodZmmID[1]);   
      }
	
    Int_t nJet         = data.GetInt("FATnJet");
    TClonesArray* jetP4 = (TClonesArray*) data.GetPtrTObject("FATjetP4");
    Float_t*  jetPRmass = data.GetPtrFloat("FATjetPRmassL2L3Corr");

    int jetIndex=-1;
    for(int ij=0; ij<nJet; ij++)
      {
    	
     	TLorentzVector* thisJet = (TLorentzVector*)jetP4->At(ij);

	if(thisEle->DeltaR(*thisJet)<0.8)continue;
	if(thatEle->DeltaR(*thisJet)<0.8)continue;

	if(hasMuon && thisMuo->DeltaR(*thisJet)<0.8)continue;
	if(hasMuon && thatMuo->DeltaR(*thisJet)<0.8)continue;
	
	if(thisJet->Pt()<200)continue;
	if(fabs(thisJet->Eta())>2.4)continue;

	if(jetPRmass[ij]<40)continue;

     	if(jetIndex<0)
	  jetIndex=ij;
	    
	break;    	

      }
    
    if(jetIndex<0)
      continue;
    nPass[5]++;
    

    TLorentzVector l4_leadingJet = (*(TLorentzVector*)jetP4->At(jetIndex));
    TLorentzVector l4_Z = (*thisEle) + (*thatEle);
     
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
