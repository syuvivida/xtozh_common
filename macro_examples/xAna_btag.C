//root -q -b -l juwu.C++\(\"inputFile\"\,\"outputFile\"\)


#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <TH1D.h>
#include <TRandom.h>
#include <TLorentzVector.h>
#include <TString.h>
#include <TFile.h>
#include "untuplizer.h"
#include "JetSelections.h"
#include "passElectronID.C"
#include <standalone_LumiReWeighting.cc>


using namespace std;
void xAna_btag(std::string inputFile, Float_t signalM=-1){


  if(signalM<0){
    TString masspoint=gSystem->GetFromPipe(Form("file=%s; test=${file##*M}; echo \"${test%%.root*}\"",inputFile.data()));

    signalM = masspoint.Atof();
  }
  cout << "resonance mass = " << signalM << endl;

  standalone_LumiReWeighting LumiWeights_central(0);
  //get TTree from file ...
  TreeReader data(inputFile.data());

  bool isData=false;
  if(inputFile.find("data")!= std::string::npos)
    isData=true;

  TH1F* h_nvtx = new TH1F("h_nvtx","",100,0,100);
  TH1F* h_nvtx2 = new TH1F("h_nvtx2","",100,0,100);
  TH1F* h_CA8jetTau21   = new TH1F("h_CA8jetTau21","",20,0,1);
  TH1F* h_CA8jetPrunedM = new TH1F("h_CA8jetPrunedM","",100,100,200);
  TH1F* h_mX = new TH1F("h_mX","",1000,500,2500);

  //histogram anoucement
  TH1F* h_mZ   = new TH1F("h_mZ","",100,0,10000);

  double nDeno[3]={0};
  double nNumr[3]={0};
  
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




    int lep[2];
    
    if(!passElectronID(data,&lep[0],&lep[1]))continue;
    
    Float_t* elePt        = data.GetPtrFloat("elePt");
    Float_t* eleEta       = data.GetPtrFloat("eleEta");
    Float_t* elePhi       = data.GetPtrFloat("elePhi");
    Float_t* eleM         = data.GetPtrFloat("eleM");
    Int_t*   eleID        = data.GetPtrInt("elePassID");

    TLorentzVector ele[2];

    for(int i=0; i<2; i++)
      {
	int index = lep[i];
	ele[i].SetPtEtaPhiM(elePt[index],
			   eleEta[index],
			   elePhi[index],
			   eleM[index]
			   );

      }
    
    TLorentzVector z_l4= ele[0]+ele[1];
    Float_t mZ = z_l4.M();
    if(mZ>110 || mZ < 70)continue;
    Float_t Zpt = z_l4.Pt();
    if(Zpt<80)continue;
    h_mZ->Fill(mZ,PU_weight_central);
    h_nvtx->Fill(nvtx);
    h_nvtx2->Fill(nvtx,PU_weight_central);

    
    // require a jet 
    Int_t jetIndex=-1;
    if(!PassJet(data, jetIndex))continue;

    Int_t nGenPar        = data.GetInt("nGenPar");
    Int_t* genParId      = data.GetPtrInt("genParId");
    Int_t* genParSt      = data.GetPtrInt("genParSt");
    Float_t* genParPt    = data.GetPtrFloat("genParPt");
    Float_t* genParEta    = data.GetPtrFloat("genParEta");
    Float_t* genParPhi    = data.GetPtrFloat("genParPhi");
    Float_t* genParM    = data.GetPtrFloat("genParM");

    
    TLorentzVector b_l4[2];
    int bindex[2]={-1,-1};

    for(int i=0; i < nGenPar; i++){

      if(abs(genParId[i])!=5)continue;
      if(genParSt[i]!=3)continue;

      if(bindex[0]<0){
	bindex[0]=i;
	b_l4[0].SetPtEtaPhiM(genParPt[i],
			     genParEta[i],
			     genParPhi[i],
			     genParM[i]);

      }
      else if(bindex[1]<0){
	bindex[1]=i;
	b_l4[1].SetPtEtaPhiM(genParPt[i],
			     genParEta[i],
			     genParPhi[i],
			     genParM[i]);



      }

    }


    Int_t    nCA8jet     = data.GetInt("CA8nJet");
    Float_t* CA8jetPt    = data.GetPtrFloat("CA8jetPt");
    Float_t* CA8jetEta   = data.GetPtrFloat("CA8jetEta");
    Float_t* CA8jetPhi   = data.GetPtrFloat("CA8jetPhi");
    Float_t* CA8jetE     = data.GetPtrFloat("CA8jetEn");
    Float_t* CA8jetTau1  = data.GetPtrFloat("CA8jetTau1");
    Float_t* CA8jetTau2  = data.GetPtrFloat("CA8jetTau2");
    Float_t* CA8jetPrunedM  = data.GetPtrFloat("CA8jetPrunedMass");
    Float_t* CA8jetCSV  = data.GetPtrFloat("CA8jetCSV");

    h_CA8jetTau21->Fill(CA8jetTau2[jetIndex]/CA8jetTau1[jetIndex],PU_weight_central);
    h_CA8jetPrunedM->Fill(CA8jetPrunedM[jetIndex],PU_weight_central);


    TLorentzVector jet(0,0,0,0);
    jet.SetPtEtaPhiE(
		     CA8jetPt[jetIndex],
		     CA8jetEta[jetIndex],
		     CA8jetPhi[jetIndex],
		     CA8jetE[jetIndex]
		     );
    
    TLorentzVector X = z_l4 + jet;
    
    Float_t mX = X.M();

    h_mX->Fill(mX,PU_weight_central);


    if(mX < signalM*0.85 || mX > signalM*1.15)continue;

    // if(bindex[0]<0 || bindex[1]<0)continue;
    
    // bool matchGenB=false;
    // if(jet.DeltaR(b_l4[0])>0.8 && jet.DeltaR(b_l4[1])>0.8)continue;

    Int_t   nSubPrunedJet = data.GetPtrInt("CA8nSubPrunedJet")[jetIndex];
    
    nDeno[2] += PU_weight_central;
    if(CA8jetCSV[jetIndex]>0.244)nNumr[2] += PU_weight_central;


    if(nSubPrunedJet<=1)
      {
	nDeno[0] += PU_weight_central;
	if(CA8jetCSV[jetIndex]>0.244)nNumr[0] += PU_weight_central;
      }
    else {


      vector<int>     *subjetMotherIndex =  data.GetPtrVectorInt("CA8subjetMotherIndex", nCA8jet);
      vector<float>   *subjetPrunedPt=  data.GetPtrVectorFloat("CA8subjetPrunedPt", nCA8jet);
      vector<float>   *subjetPrunedEta =  data.GetPtrVectorFloat("CA8subjetPrunedEta", nCA8jet);
      vector<float>   *subjetPrunedPhi =  data.GetPtrVectorFloat("CA8subjetPrunedPhi", nCA8jet);
      vector<float>   *subjetPrunedMass =  data.GetPtrVectorFloat("CA8subjetPrunedMass", nCA8jet);
      vector<float>   *subjetPrunedEn =  data.GetPtrVectorFloat("CA8subjetPrunedEn", nCA8jet);
      vector<float>   *subjetPrunedCSV =  data.GetPtrVectorFloat("CA8subjetPrunedCSV", nCA8jet);

      TLorentzVector subjet_l4[2];
      bool problem=false;
      for(int ij=0; ij < nSubPrunedJet; ij++)
	{
	  if(subjetMotherIndex[jetIndex][ij]!=jetIndex)
	    {
	      cout << "There is a problem !!" << endl;
	      problem=true;
	      break;
	    }

	  subjet_l4[ij].SetPtEtaPhiE
	    (
	     subjetPrunedPt[jetIndex][ij],
	     subjetPrunedEta[jetIndex][ij],
	     subjetPrunedPhi[jetIndex][ij],
	     subjetPrunedEn[jetIndex][ij]
	     );
	}
      if(problem)continue;
      float drj1j2 = subjet_l4[0].DeltaR(subjet_l4[1]);

      if(drj1j2 < 0.3)
	{
	  nDeno[0] += PU_weight_central;
	  if(CA8jetCSV[jetIndex]>0.244)nNumr[0] += PU_weight_central;
	}
      else
	{
	  nDeno[1] += PU_weight_central;
	  if(subjetPrunedCSV[jetIndex][0]>0.244 && 
	     subjetPrunedCSV[jetIndex][1]>0.244)nNumr[1] += PU_weight_central;

	}
      
    }


  } // end of loop over entries

  cout << "Merged jet = " << nNumr[2] << " / " << nDeno[2] << endl;
  cout << "Merged jet = " << nNumr[0] << " / " << nDeno[0] << endl;
  cout << "Separate sub jet = " << nNumr[1] << " / " << nDeno[1] << endl;

  //save output
  TString endfix=gSystem->GetFromPipe(Form("file=%s; echo \"${file##*/}\"",inputFile.data()));
  TString outputFile = "btagHisto_" + endfix;

  TFile* outFile = new TFile(outputFile.Data(),"recreate");
  h_mZ->Write();
  h_nvtx->Write();
  h_nvtx2->Write();
  h_CA8jetTau21->Write();
  h_CA8jetPrunedM->Write();
  h_mX->Write();
  outFile->Close();

}
