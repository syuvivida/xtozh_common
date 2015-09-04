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
#include <TCanvas.h>
#include <TSystemDirectory.h>
#include <TList.h>
#include <TStyle.h>

using namespace std;
void xAna_hh1(std::string inputFile){

  //get TTree from file ...
  // TreeReader data(inputFile.data());


  std::vector<string> infiles;
  TString prefix;
  TString mstring;
  bool isQCD=false;
  if(inputFile.find(".root")!= std::string::npos)
    { 
      prefix=gSystem->GetFromPipe(Form("file=%s; test=${file##*softdrop_}; test2=${test%%.root*}; echo \"${test2}\"",inputFile.data()));
      mstring=gSystem->GetFromPipe(Form("file=%s; test=${file##*M-}; test2=${test%%_13TeV*}; echo \"Bulk Graviton Mass =${test2} GeV\"",inputFile.data()));
      cout << "output file name = " << prefix.Data() << endl;
      cout << "output file name = " << mstring.Data() << endl;
      infiles.push_back(inputFile.data());
    }
  else
    {
      isQCD=true;
      mstring="QCD HT=2000-Inf";
      prefix=gSystem->GetFromPipe(Form("file=%s; test=${file##*SPRING15/}; test2=${test%%/crab*}; echo \"${test2}\"",
					   inputFile.data()));
      cout << "output file name = " << prefix.Data() << endl;      
      TSystemDirectory *base = new TSystemDirectory("root","root");

      base->SetDirectory(inputFile.data());
      TList *listOfFiles = base->GetListOfFiles();
      TIter fileIt(listOfFiles);
      TFile *fileH = new TFile();
      int nfile=0;
      while(fileH = (TFile*)fileIt()) {
	std::string fileN = fileH->GetName();
	if( fileH->IsFolder())  continue;
	if(fileN.find("NCUGlobalTuples") == std::string::npos)continue;
	fileN = inputFile + "/" + fileN;
	cout << fileN.data() << endl;
	nfile++;
	infiles.push_back(fileN);
      }

      std::cout << "Opened " << nfile << " files" << std::endl;

    }
  
  TreeReader data(infiles);
  


  Long64_t nTotal=0;
  Long64_t nPass[20]={0};

  TH1F* h_SD=new TH1F("h_SD","",100,0,200);
  
  //Event loop
  for(Long64_t jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    if (jEntry % 50000 == 0)
      fprintf(stderr, "Processing event %lli of %lli\n", jEntry + 1, data.GetEntriesFast());

    data.GetEntry(jEntry);
    nTotal++;

    //0. has a good vertex
    Int_t nVtx        = data.GetInt("nVtx");
    if(nVtx<1)continue;
    nPass[0]++;

    int nFATJet         = data.GetInt("FATnJet");
    const int nJets=nFATJet;
    TClonesArray* fatjetP4 = (TClonesArray*) data.GetPtrTObject("FATjetP4");
    Float_t*  fatjetCISVV2 = data.GetPtrFloat("FATjetCISVV2");
    Float_t*  fatjetSDmass = data.GetPtrFloat("FATjetSDmass");
    Int_t*   nSubSoftDropJet = data.GetPtrInt("FATnSubSDJet");
    vector<float>   *subjetSDCSV =  data.GetPtrVectorFloat("FATsubjetSDCSV", nFATJet);
    vector<float>   *subjetSDPx  =  data.GetPtrVectorFloat("FATsubjetSDPx", nFATJet);
    vector<float>   *subjetSDPy  =  data.GetPtrVectorFloat("FATsubjetSDPy", nFATJet);
    vector<float>   *subjetSDPz  =  data.GetPtrVectorFloat("FATsubjetSDPz", nFATJet);
    vector<float>   *subjetSDE   =  data.GetPtrVectorFloat("FATsubjetSDCE", nFATJet);
    vector<bool>    &passFatJetLooseID = *((vector<bool>*) data.GetPtr("FATjetPassIDLoose"));

    
    int nFatBTag=0;
    for(int ij=0; ij<nJets; ij++)
      {
    	
     	TLorentzVector* thisJet = (TLorentzVector*)fatjetP4->At(ij);
    	if(thisJet->Pt()<30)continue;
    	if(fabs(thisJet->Eta())>2.5)continue;
    	if(fatjetSDmass[ij]<95 || fatjetSDmass[ij]>145)continue;
	if(!passFatJetLooseID[ij])continue;

    	if(fatjetCISVV2[ij] < 0.605)continue;
    	if(fatjetCISVV2[ij] > 1)continue;

    	nFatBTag++;
	
      }
    
    if(nFatBTag>=2)nPass[1]++;


    int nSubBTag[2]={0}; // check only the leading two fat jets 
    int nGoodFatJet=0;
    for(int ij=0; ij<nJets; ij++)
      {
    	
	TLorentzVector* thisJet = (TLorentzVector*)fatjetP4->At(ij);
	if(thisJet->Pt()<30)continue;
	if(fabs(thisJet->Eta())>2.5)continue;
	if(fatjetSDmass[ij]<95 || fatjetSDmass[ij]>145)continue;
	if(!passFatJetLooseID[ij])continue;

      	for(int is=0; is < nSubSoftDropJet[ij]; is++){
	  if(subjetSDCSV[ij][is] < 0.605)continue;
	  if(nGoodFatJet<2)
	  nSubBTag[nGoodFatJet]++;
	  
      	}

	nGoodFatJet++;
      }
  
    
    // if each fat jet has at least one subjet btag
    if(nSubBTag[0]>0 && nSubBTag[1]>0)nPass[2]++;

    // if one of the fat jets has at least two subjet btags
    if((nSubBTag[0]>1 && nSubBTag[1]>0) || 
       (nSubBTag[0]>0 && nSubBTag[1]>1))nPass[3]++;

    // if both fat jets have at least two subjet btags
    if(nSubBTag[0]>1 && nSubBTag[1]>1) nPass[4]++;
        

  } // end of loop over entries

  std::cout << "nTotal    = " << nTotal << std::endl;
  for(int i=0;i<20;i++)
    if(nPass[i]>0)
      std::cout << "nPass[" << i << "]= " << nPass[i] << std::endl;
 
  
  TH1D* h_CutFlow = new TH1D(" ", Form("Cut Flow for %s",mstring.Data()) ,6,0,6);

  std::string cut_name[6] = {"Total","Vertex","FATjet_{CSV}","#geq 2 Subjet_{CSV}","#geq 3 Subjet_{CSV}","#geq 4 Subjet_{CSV}"};
  ofstream fout;
  fout.open("eff.dat",ios::app|ios::out);
  //  fout << mstring.Data() << " ";
  for(int i=1;i<=6;i++){ // i is the index of column of cut flow plot 

    float ntotal = nTotal;
    float nsig = i==1? nTotal: nPass[i-2];
    float eff = nsig/ntotal;
    float err = sqrt( (1-eff)*eff/ntotal);
    h_CutFlow->SetBinContent(i,eff);
    h_CutFlow->SetBinError(i,err);
    h_CutFlow->GetXaxis()->SetBinLabel( i , cut_name[i-1].data() );
    if(i>=3)
      fout << eff << " " << err << " ";
  }
  fout << endl;
  
  h_CutFlow->GetXaxis()->SetLabelSize(0.05);
  h_CutFlow->SetStats(0);
  h_CutFlow->SetMarkerSize(2.0);
  h_CutFlow->SetLineColor(kRed-2);
  h_CutFlow->SetLineWidth(3);
  TCanvas* c1 = new TCanvas("c1","",500,500);
  if(isQCD)c1->SetLogy(1);
  gStyle->SetPaintTextFormat("6.3g");
  h_CutFlow->Draw();
  h_CutFlow->Draw("HIST TEXT0 SAME");
  TString outputFile;
  outputFile = prefix + ".pdf";
  c1->Print(outputFile.Data());
  outputFile = prefix + ".png";
  c1->Print(outputFile.Data());
  outputFile = prefix + ".eps";
  c1->Print(outputFile.Data());
}
