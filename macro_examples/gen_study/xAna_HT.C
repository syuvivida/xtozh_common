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
#include <TSystemDirectory.h>
#include <TList.h>

using namespace std;
void xAna_HT(std::string inputFile, bool test=false){

  std::vector<string> infiles;
  TString outputFile;
 
  //get TTree from file ...
  outputFile="test.root";

  cout << "output file name = " << outputFile.Data() << endl;      
  TSystemDirectory *base = new TSystemDirectory("root","root");

  base->SetDirectory(inputFile.data());
  TList *listOfFiles = base->GetListOfFiles();
  TIter fileIt(listOfFiles);
  TFile *fileH = new TFile();
  int nfile=0;
  while(fileH = (TFile*)fileIt()) {
    std::string fileN = fileH->GetName();
    if( fileH->IsFolder())  continue;
    if(fileN.find("root") == std::string::npos)continue;
    fileN = inputFile + "/" + fileN;
    cout << fileN.data() << endl;
    nfile++;
    infiles.push_back(fileN);
  }
  
  std::cout << "Opened " << nfile << " files" << std::endl;
  
  cout << "output file name = " << outputFile.Data() << endl;
  //get TTree from file ...
  TreeReader data(infiles);
 
  TH1F* hpt = new TH1F("hpt","",1000,0,1000);
  hpt->Sumw2();
  hpt->SetLineWidth(2);
  hpt->SetTitleOffset(1.5,"X");
  hpt->SetTitleOffset(1.5,"Y");
  hpt->SetYTitle("Arbitrary Unit");

  TH1F* hllpt_before = (TH1F*)hpt->Clone("hllpt_before");
  hllpt_before->SetXTitle("Generator-level p_{T}(ll) [GeV]");
  TH1F* hllpt_after  = (TH1F*)hpt->Clone("hllpt_after");
  hllpt_after->SetXTitle("Generator-level p_{T}(ll) [GeV]");


  TH1F* hzpt_before = (TH1F*)hpt->Clone("hzpt_before");
  hzpt_before->SetXTitle("Generator-level p_{T}(Z) [GeV]");
  TH1F* hzpt_after  = (TH1F*)hpt->Clone("hzpt_after");
  hzpt_after->SetXTitle("Generator-level p_{T}(Z) [GeV]");

  TH1F* hrecozpt_before = (TH1F*)hpt->Clone("hrecozpt_before");
  hrecozpt_before->SetXTitle("Reconstruction-level p_{T}(ll) [GeV]");
  TH1F* hrecozpt_after = (TH1F*)hpt->Clone("hrecozpt_after");
  hrecozpt_after->SetXTitle("Reconstruction-level p_{T}(ll) [GeV]");


  TH1F* hht_before = (TH1F*)hpt->Clone("hht_before");
  TH1F* hht_after  = (TH1F*)hpt->Clone("hht_after");

  Long64_t nTotal=0;
  Long64_t nPass[20]={0};
  //Event loop
  for(Long64_t jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    if (jEntry % 50000 == 0)
      fprintf(stderr, "Processing event %lli of %lli\n", jEntry + 1, data.GetEntriesFast());
    if (test && jEntry > 5000)break;

    data.GetEntry(jEntry);
    nTotal ++;
        // 0. check the generator-level information and make sure there is a Z->e+e-
    Int_t nGenPar        = data.GetInt("nGenPar");
    Int_t* genParId      = data.GetPtrInt("genParId");
    Int_t* genParSt      = data.GetPtrInt("genParSt");
    Int_t* genMomParId   = data.GetPtrInt("genMomParId");
    Float_t HT        = data.GetFloat("HT");
    Float_t mcWeight  = data.GetFloat("mcWeight");
    Float_t weight = 1;

    if(mcWeight>0)weight = 1;
    else weight = -1;

    TClonesArray* genParP4 = (TClonesArray*) data.GetPtrTObject("genParP4");

    hht_before->Fill(HT,weight);
 
    
    float zpt=-1;
    bool findAZ=false;
    bool findEle[2]={false,false};
    TLorentzVector ele_P4[2];
    for(int ig=0; ig < nGenPar; ig++){

      TLorentzVector* thisGen = (TLorentzVector*)genParP4->At(ig);
      int pid=genParId[ig];
      int mompid = genMomParId[ig];
      int status = genParSt[ig];
      if(pid==23 && zpt<0)
	{
	  zpt = thisGen->Pt();
	  findAZ=true;
	}
      else if(status==1 && (pid==11 || pid==13 || pid==15) && (mompid==pid || mompid==23))
	{
	  ele_P4[0]=*(thisGen);
	  findEle[0]=true;
	}
      else if(status==1 && (pid==-11 || pid==-13 || pid==-15) && (mompid==pid || mompid==23))
	{
	  ele_P4[1]=*(thisGen);
	  findEle[1]=true;
	}
    }

    bool findAPair=false;
    if(findEle[0] && findEle[1]){
      nPass[0]++;
      findAPair=true;
    }
    if(findAZ)nPass[1]++;

    float llpt = (ele_P4[0]+ele_P4[1]).Pt();
    if(findAZ)
      hzpt_before->Fill(zpt,weight);
    if(findAPair)
      hllpt_before->Fill(llpt,weight);



    //4. look for good electrons first
    Int_t nEle         = data.GetInt("nEle");
    // Int_t run          = data.GetInt("runId");
    // Int_t lumi         = data.GetInt("lumiSection");
    // Int_t event        = data.GetInt("eventId");
    vector<bool> &passHEEPID = *((vector<bool>*) data.GetPtr("eleIsPassHEEPNoIso"));
    TClonesArray* eleP4 = (TClonesArray*) data.GetPtrTObject("eleP4");
    Float_t* eleSCEta         = data.GetPtrFloat("eleScEta");
    Float_t* eleMiniIso       = data.GetPtrFloat("eleMiniIso");
    Int_t*   eleCharge        = data.GetPtrInt("eleCharge");

    //5. select good electrons
    std::vector<int> goodElectrons;

    for(int ie=0; ie< nEle; ie++)
      {

    	TLorentzVector* thisEle = (TLorentzVector*)eleP4->At(ie);

    	if(! (fabs(eleSCEta[ie])<1.4442 || 
	      (fabs(eleSCEta[ie])>1.566 && fabs(eleSCEta[ie])<2.5)))continue;
    	
	if(thisEle->Pt() < 35)continue;

	if(!passHEEPID[ie])continue;
    	
	if(eleMiniIso[ie]>0.1)continue;

	goodElectrons.push_back(ie);
      }

	
    //6. select a good Z boson
    bool findEPair=false;
    TLorentzVector l4_Z(0,0,0,0);
    for(unsigned int i=0; i< goodElectrons.size(); i++)
      {
	int ie = goodElectrons[i];
	TLorentzVector* thisEle = (TLorentzVector*)eleP4->At(ie);

	for(unsigned int j=0; j< i; j++)
	  {
	    int je= goodElectrons[j];

	    if(eleCharge[ie]*eleCharge[je]>0)continue;

	    TLorentzVector* thatEle = (TLorentzVector*)eleP4->At(je);

	    Float_t mll  = (*thisEle+*thatEle).M();

	    if(mll<70 || mll>110)continue;

	    if(!findEPair){
	      l4_Z=(*thisEle+*thatEle);
	    }
	    findEPair=true;
	    break;
	  }	
      }

    if(findEPair && findAPair)
      hrecozpt_before->Fill(l4_Z.Pt(),weight);

    if(HT<100)continue;
    nPass[2]++;
    hht_after->Fill(HT,weight);

    if(findAZ)
      hzpt_after->Fill(zpt,weight);
    if(findAPair)
      hllpt_after->Fill(llpt,weight);

    if(findEPair && findAPair)
      hrecozpt_after->Fill(l4_Z.Pt(),weight);

  } // end of loop over entries

  std::cout << "nTotal    = " << nTotal << std::endl;
  for(int i=0;i<20;i++)
    if(nPass[i]>0)
      std::cout << "nPass[" << i << "]= " << nPass[i] << std::endl;

  TFile* outFile = new TFile("test.root","recreate");

  hllpt_before->Write();
  hllpt_after->Write();
  hzpt_before->Write();
  hzpt_after->Write();
  hrecozpt_before->Write();
  hrecozpt_after->Write();
  hht_before->Write();
  hht_after->Write();

  outFile->Close();
    
}
