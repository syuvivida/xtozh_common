//root -q -b -l juwu.C++\(\"inputFile\"\,\"outputFile\"\)


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
#include "ElectronSelections.h"

using namespace std;
void xAna_ele(std::string inputFile, int LeptonMode){

  //get TTree from file ...
  TreeReader data(inputFile.data());

  Long64_t nLepton[3]={0};
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

      if(abs(da1pdg)==LeptonMode)
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

    Int_t nVtx        = data.GetInt("nVtx");
    if(nVtx<1)continue;
    nPass[3]++;

    Int_t nEle         = data.GetInt("nEle");
    Int_t run          = data.GetInt("runId");
    Int_t lumi         = data.GetInt("lumiSection");
    Int_t event        = data.GetInt("eventId");
    vector<bool> &passHEEPID = *((vector<bool>*) data.GetPtr("eleIsPassHEEPNoIso"));
    TClonesArray* eleP4 = (TClonesArray*) data.GetPtrTObject("eleP4");
    Float_t* eleSCEta         = data.GetPtrFloat("eleScEta");
    Float_t* eleMiniIso       = data.GetPtrFloat("eleMiniIso");
    Int_t*   eleCharge        = data.GetPtrInt("eleCharge");

    bool findEPair=false;
    TLorentzVector l4_Z(0,0,0,0);
    std::vector<int> myElectrons;

    // select_electrons(data, myElectrons);

    // select good electrons

    for(int ie=0; ie< nEle; ie++)
      {

    	TLorentzVector* thisEle = (TLorentzVector*)eleP4->At(ie);

    	if(fabs(thisEle->Eta())>2.5)continue;

    	if(! (fabs(eleSCEta[ie])<1.442 || fabs(eleSCEta[ie])>1.566))continue;
    	
    	if(thisEle->Pt() < 115)continue;

    	if(!passHEEPID[ie])continue;
    	
    	if(eleMiniIso[ie]>0.1)continue;

    	myElectrons.push_back(ie);
      }

	

    for(unsigned int i=0; i< myElectrons.size(); i++)
      {
	int ie = myElectrons[i];
	TLorentzVector* thisEle = (TLorentzVector*)eleP4->At(ie);

	for(unsigned int j=0; j< i; j++)
	  {
	    int je= myElectrons[j];

	    if(eleCharge[ie]*eleCharge[je]>0)continue;

	    TLorentzVector* thatEle = (TLorentzVector*)eleP4->At(je);

	    Float_t mll  = (*thisEle+*thatEle).M();
	    Float_t ptll = (*thisEle+*thatEle).Pt();
	    

	    if(mll<70 || mll>110)continue;
	    if(ptll<200)continue;

	    if(!findEPair)l4_Z=(*thisEle+*thatEle);

	    findEPair=true;
	  }	
      }

    if(!findEPair)
      continue;
    nPass[4]++;


    Int_t nJet         = data.GetInt("FATnJet");
    TClonesArray* jetP4 = (TClonesArray*) data.GetPtrTObject("FATjetP4");
    Float_t*  jetSDmass = data.GetPtrFloat("FATjetSDmass");

    TLorentzVector l4_leadingJet(0,0,0,0);
    bool findAJet=false;
    for(int ij=0; ij<nJet; ij++)
      {
	
	TLorentzVector* thisJet = (TLorentzVector*)jetP4->At(ij);

	if(jetSDmass[ij]<50 || jetSDmass[ij]>110)continue;
	
	if(!findAJet)
	  l4_leadingJet = *thisJet;
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
  for(int i=0; i<3; i++)
    std::cout << "nLepton[" << i << "]    = " << nLepton[i] << std::endl;
  for(int i=0;i<20;i++)
    if(nPass[i]>0)
      std::cout << "nPass[" << i << "]= " << nPass[i] << std::endl;
    
}
