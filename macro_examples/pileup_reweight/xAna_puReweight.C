//root -q -b -l juwu.C++\(\"inputFile\"\,\"outputFile\"\)


#include <vector>
#include <iostream>
#include <algorithm>
#include <TString.h>
#include <map>
#include <TH1D.h>
#include <TFile.h>
#include "untuplizer.h"
#include <standalone_LumiReWeighting.cc>


using namespace std;
void xAna_puReweight(std::string inputFile){

  standalone_LumiReWeighting LumiWeights_central(0);
  //get TTree from file ...
  TreeReader data(inputFile.data());

  bool isData=false;
  if(inputFile.find("data")!= std::string::npos)
    isData=true;

  TH1F* h_nvtx = new TH1F("h_nvtx","",100,0,100);
  TH1F* h_nvtx2 = new TH1F("h_nvtx2","",100,0,100);

  
  //Event loop
  for(Long64_t jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    if (jEntry % 50000 == 0)
      fprintf(stderr, "Processing event %lli of %lli\n", jEntry + 1, data.GetEntriesFast());

    data.GetEntry(jEntry);

    double PU_weight_central =1;
    if(!isData){
      Float_t ntrue= data.GetFloat("pu_nTrueInt");
      PU_weight_central = LumiWeights_central.weight(ntrue);
    }
    
    Int_t nvtx = data.GetInt("info_nVtx");


    std::string* trigName = data.GetPtrString("hlt_trigName");
    Int_t* trigResult = data.GetPtrInt("hlt_trigResult");
    const Int_t nsize = data.GetPtrStringSize();

    bool passTrigger=false;
    for(int it=0; it< nsize; it++)
      {
 	std::string thisTrig= trigName[it];
 	int results = trigResult[it];
	  
 	if(thisTrig.find("HLT_DoubleEle33")!= std::string::npos && results==1)
 	  {
 	    passTrigger=true;
 	    break;
 	  }


      }

    if(isData && !passTrigger)continue;


    h_nvtx->Fill(nvtx);
    h_nvtx2->Fill(nvtx,PU_weight_central);

  } // end of loop over entries

  //save output
  TString endfix=gSystem->GetFromPipe(Form("file=%s; echo \"${file##*/}\"",inputFile.data()));
  TString outputFile = "muHisto_" + endfix;
  TFile* outFile = new TFile(outputFile.Data(),"recreate");
  h_nvtx->Write();
  h_nvtx2->Write();
  outFile->Close();

}
