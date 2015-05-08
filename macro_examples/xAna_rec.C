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
#include <TGraphAsymmErrors.h>

using namespace std;
void xAna_rec(std::string inputFile){

  //get TTree from file ...
  TreeReader data(inputFile.data());

  //histogram anoucement
  Float_t xmin[13]={0, 0.05,
		    0.1,0.15,
		    0.2,0.25,
		    0.3,0.35,
		    0.4,0.45,
		    0.5,
		    1.0,
		    1.5};
  TH1F* h_mZ   = new TH1F("h_mZ","",100,50,150);
  TH1F* h_dR   = new TH1F("h_dR","",12,xmin);
  //  TH1F* h_dR   = new TH1F("h_dR","",15,0,1.5);
  h_dR  ->SetMarkerStyle(8);
  h_dR  ->SetMarkerSize(1);
  h_dR   ->SetXTitle("#Delta R between generator-level muons");
  TH1F* h_dR_deno = (TH1F*)h_dR->Clone("h_dR_deno");
  TH1F* h_dR_numr_muonReco[3];

  TH1F* h_dphi = new TH1F("h_dphi","",30,0,TMath::Pi());
  h_dphi->SetMarkerStyle(8);
  h_dphi->SetMarkerSize(1);
  h_dphi->SetXTitle("|#Delta #phi| between generator-level muons");
  TH1F* h_dphi_deno = (TH1F*)h_dphi->Clone("h_dphi_deno");
  TH1F* h_dphi_numr_muonReco[3];

  TH1F* h_deta = new TH1F("h_deta","",30,0,1.5);
  h_deta->SetMarkerStyle(8);
  h_deta->SetMarkerSize(1);
  h_deta->SetXTitle("|#Delta #eta| between generator-level muons");
  TH1F* h_deta_deno = (TH1F*)h_deta->Clone("h_deta_deno");
  TH1F* h_deta_numr_muonReco[3];


  TH1F* h_ptZ   = new TH1F("h_ptZ","",15,0,3000);
  h_ptZ ->SetMarkerStyle(8);
  h_ptZ ->SetMarkerSize(1);
  h_ptZ ->SetXTitle("generator-level p_{T}(ll) [GeV]");
  TH1F* h_ptZ_deno = (TH1F*)h_ptZ->Clone("h_ptZ_deno");
  TH1F* h_ptZ_numr_muonReco[3];

  std::string title[3]={"Two Global muon", "inclusive 1 Global + 1 Trk", "2 Trks"};

  for(int i=0; i < 3; i++)
    { 
      h_dR_numr_muonReco[i] = (TH1F*)h_dR->Clone(Form("h_dR_numr_muonReco%d",i));
      h_dR_numr_muonReco[i] -> SetTitle(title[i].data());
      h_dphi_numr_muonReco[i] = (TH1F*)h_dphi->Clone(Form("h_dphi_numr_muonReco%d",i));
      h_dphi_numr_muonReco[i] -> SetTitle(title[i].data());
      h_deta_numr_muonReco[i] = (TH1F*)h_deta->Clone(Form("h_deta_numr_muonReco%d",i));
      h_deta_numr_muonReco[i] -> SetTitle(title[i].data());
      h_ptZ_numr_muonReco[i] = (TH1F*)h_ptZ->Clone(Form("h_ptZ_numr_muonReco%d",i));
      h_ptZ_numr_muonReco[i] -> SetTitle(title[i].data());
      
    }
  
  //Event loop
  for(Long64_t jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    if (jEntry % 50000 == 0)
      fprintf(stderr, "Processing event %lli of %lli\n", jEntry + 1, data.GetEntriesFast());

    data.GetEntry(jEntry);



    Int_t nGenPar        = data.GetInt("nGenPar");
    Int_t* genParId      = data.GetPtrInt("genParId");
    Int_t* genParSt      = data.GetPtrInt("genParSt");
    Int_t* genMomParId   = data.GetPtrInt("genMomParId");
    Float_t* genParPt    = data.GetPtrFloat("genParPt");
    Float_t* genParEta    = data.GetPtrFloat("genParEta");
    Float_t* genParPhi    = data.GetPtrFloat("genParPhi");
    Float_t* genParM    = data.GetPtrFloat("genParM");

    int muIndex[2]={-1,-1};
    for(int ig=0; ig < nGenPar; ig++){

      if(abs(genParId[ig])!=13)continue;
      if(genParSt[ig]!=1)continue;
      if(genMomParId[ig] != 23 && genMomParId[ig] != genParId[ig])continue;

      if(genParPt[ig]<20)continue;
      if(abs(genParEta[ig])>2.4)continue;

      if(muIndex[0]<0)muIndex[0]=ig;
      else if(muIndex[1]<0)muIndex[1]=ig;
      if(muIndex[0]>=0 && muIndex[1]>=0)break;
    }


    if(muIndex[0]<0 || muIndex[1]<0)continue;

    // if(genParPt[muIndex[0]] < 40 && genParPt[muIndex[1]] < 40)continue;
    
    TLorentzVector l4_mu[2];
    for(int i=0;i<2;i++)
      {
	l4_mu[i].SetPtEtaPhiM(
			      genParPt[muIndex[i]],
			      genParEta[muIndex[i]],
			      genParPhi[muIndex[i]],
			      genParM[muIndex[i]]
			      );

      }
    Float_t gendR = l4_mu[0].DeltaR(l4_mu[1]);
    h_dR_deno->Fill(gendR);

    Float_t gendPhi = fabs(l4_mu[0].DeltaPhi(l4_mu[1]));
    h_dphi_deno->Fill(gendPhi);

    Float_t gendEta = fabs(l4_mu[0].Eta()-l4_mu[1].Eta());
    h_deta_deno->Fill(gendEta);

    Float_t genptll = (l4_mu[0]+l4_mu[1]).Pt();
    h_ptZ_deno->Fill(genptll);

    h_mZ->Fill((l4_mu[0]+l4_mu[1]).M());

    // if(gendR > 0.4 && gendEta < 0.4)
    //   cout << "gendR = " << gendR << " and gendEta = " << gendEta << endl;



    Float_t* muPt        = data.GetPtrFloat("muPt");
    Float_t* muEta       = data.GetPtrFloat("muEta");
    Float_t* muPhi       = data.GetPtrFloat("muPhi");
    Float_t* muM         = data.GetPtrFloat("muM");
    Int_t*   isGlobalMuon = data.GetPtrInt("isGlobalMuon");
    Int_t*   isTrackerMuon = data.GetPtrInt("isTrackerMuon");
    Int_t*   isGood        = data.GetPtrInt("muGood");
    Int_t*   ITrkID        = data.GetPtrInt("muITrkID");
    // Int_t*   SegID         = data.GetPtrInt("muSegID");
    Int_t    nMu   = data.GetInt("nMu"); 


    // gg, gt, tt
    bool findPair[3]={false,false,false};

    const float dRMin = 0.1;
    
    // loop over two reco muons and see if they are matched to generator-level muons
    for(int i=0; i < nMu; i++){

      bool isGlobal1 = isGlobalMuon[i];
      bool isTrack1  = isTrackerMuon[i];
      if(!isGlobal1 && !isTrack1)continue;
      if(muPt[i]<10)continue;
      if(fabs(muEta[i])>2.4)continue;
      if(isGood[i]==0)continue;
 
      TLorentzVector thisMu(0,0,0,0);
      thisMu.SetPtEtaPhiM
	(
	 muPt[i],
	 muEta[i],
	 muPhi[i],
	 muM[i]
	 );
      
      float dR1_gen0= thisMu.DeltaR(l4_mu[0]);
      float dR1_gen1= thisMu.DeltaR(l4_mu[1]);

      if(dR1_gen0 > dRMin && dR1_gen1 > dRMin)continue;
 
      for(int j=0; j < i; j++){


	bool isGlobal2 = isGlobalMuon[j];
	bool isTrack2  = isTrackerMuon[j];

	if(!isGlobal2 && !isTrack2)continue;
	if(muPt[j]<10)continue;
	if(fabs(muEta[j])>2.4)continue;
	if(isGood[j]==0)continue;

	if(ITrkID[i]!=-1 && ITrkID[i]==ITrkID[j])continue;

	TLorentzVector thatMu(0,0,0,0);
	thatMu.SetPtEtaPhiM
	  (
	   muPt[j],
	   muEta[j],
	   muPhi[j],
	   muM[j]
	   );

	float dR2_gen0= thatMu.DeltaR(l4_mu[0]);
	float dR2_gen1= thatMu.DeltaR(l4_mu[1]);
	
	if(dR2_gen0 > dRMin && dR2_gen1 > dRMin)continue;

	bool matched = 
	  (dR1_gen0 < dRMin && dR2_gen1 < dRMin) || 
	  (dR1_gen1 < dRMin && dR2_gen0 < dRMin);

	if(!matched)continue;

      if(isGlobal1 && isGlobal2)
	findPair[0]=true;

      if((isGlobal1 && isTrack2)  || (isGlobal2 && isTrack1) || 
	 (isGlobal1 && isGlobal2))
	findPair[1]=true;

      if(isTrack1 && isTrack2)
	findPair[2]=true;


      } // end loop of muon j


    } // end loop of muon i


    if(findPair[0])
      {
	h_dR_numr_muonReco[0]->Fill(gendR);
	h_dphi_numr_muonReco[0]->Fill(gendPhi);
	h_deta_numr_muonReco[0]->Fill(gendEta);
	h_ptZ_numr_muonReco[0]->Fill(genptll);
      }

    if(findPair[1])
      {
	h_dR_numr_muonReco[1]->Fill(gendR);
	h_dphi_numr_muonReco[1]->Fill(gendPhi);
	h_deta_numr_muonReco[1]->Fill(gendEta);
	h_ptZ_numr_muonReco[1]->Fill(genptll);
      }
     

    if(findPair[2])
      {
	h_dR_numr_muonReco[2]->Fill(gendR); 
	h_dphi_numr_muonReco[2]->Fill(gendPhi);
	h_deta_numr_muonReco[2]->Fill(gendEta);
	h_ptZ_numr_muonReco[2]->Fill(genptll);
      }



  } // end of loop over entries


  TGraphAsymmErrors* hrecoeff[3];
  TGraphAsymmErrors* hrecoeffPhi[3];
  TGraphAsymmErrors* hrecoeffEta[3];
  TGraphAsymmErrors* hrecoeffPtZ[3];

  //save output
  TString endfix=gSystem->GetFromPipe(Form("file=%s; echo \"${file##*/}\"",inputFile.data()));
  TString outputFile = "recHisto_" + endfix;
  TFile* outFile = new TFile(outputFile.Data(),"recreate");
  h_mZ->Write();

  h_dR_deno ->Write();
  h_dphi_deno ->Write();
  h_deta_deno ->Write();
  h_ptZ_deno->Write();

  for(int i=0; i<3; i++){
    

    h_dR_numr_muonReco[i]->Write();
    h_dphi_numr_muonReco[i]->Write();
    h_deta_numr_muonReco[i]->Write();
    h_ptZ_numr_muonReco[i]->Write();


    hrecoeff[i]=new TGraphAsymmErrors(h_dR_numr_muonReco[i], h_dR_deno);
    hrecoeff[i]->SetMarkerStyle(8);
    hrecoeff[i]->SetMarkerSize(1);
    hrecoeff[i]->SetMinimum(0);
    hrecoeff[i]->SetMaximum(1.1);
    hrecoeff[i]->SetName(Form("hrecoeff%02i",i));
    hrecoeff[i]->GetXaxis()->SetTitle("#Delta R between generator-level muons");
    hrecoeff[i]->GetXaxis()->SetTitleSize(0.045);
    hrecoeff[i]->GetYaxis()->SetTitle("Reconstruction Efficiency");
    hrecoeff[i]->GetYaxis()->SetTitleSize(0.045);

    hrecoeffPhi[i]=new TGraphAsymmErrors(h_dphi_numr_muonReco[i], h_dphi_deno);
    hrecoeffPhi[i]->SetMarkerStyle(8);
    hrecoeffPhi[i]->SetMarkerSize(1);
    hrecoeffPhi[i]->SetMinimum(0);
    hrecoeffPhi[i]->SetMaximum(1.1);
    hrecoeffPhi[i]->SetName(Form("hrecoeffPhi%02i",i));
    hrecoeffPhi[i]->GetXaxis()->SetTitle("|#Delta #phi| between generator-level muons");
    hrecoeffPhi[i]->GetXaxis()->SetTitleSize(0.045);
    hrecoeffPhi[i]->GetYaxis()->SetTitle("Reconstruction Efficiency");
    hrecoeffPhi[i]->GetYaxis()->SetTitleSize(0.045);

    hrecoeffEta[i]=new TGraphAsymmErrors(h_deta_numr_muonReco[i], h_deta_deno);
    hrecoeffEta[i]->SetMarkerStyle(8);
    hrecoeffEta[i]->SetMarkerSize(1);
    hrecoeffEta[i]->SetMinimum(0);
    hrecoeffEta[i]->SetMaximum(1.1);
    hrecoeffEta[i]->SetName(Form("hrecoeffEta%02i",i));
    hrecoeffEta[i]->GetXaxis()->SetTitle("|#Delta #eta| between generator-level muons");
    hrecoeffEta[i]->GetXaxis()->SetTitleSize(0.045);
    hrecoeffEta[i]->GetYaxis()->SetTitle("Reconstruction Efficiency");
    hrecoeffEta[i]->GetYaxis()->SetTitleSize(0.045);

    hrecoeffPtZ[i]=new TGraphAsymmErrors(h_ptZ_numr_muonReco[i], h_ptZ_deno);
    hrecoeffPtZ[i]->SetMarkerStyle(8);
    hrecoeffPtZ[i]->SetMarkerSize(1);
    hrecoeffPtZ[i]->SetMinimum(0);
    hrecoeffPtZ[i]->SetMaximum(1.1);
    hrecoeffPtZ[i]->SetName(Form("hrecoeffPtZ%02i",i));
    hrecoeffPtZ[i]->GetXaxis()->SetTitle("generator-level p_{T}(ll) [GeV]");
    hrecoeffPtZ[i]->GetXaxis()->SetTitleSize(0.045);
    hrecoeffPtZ[i]->GetYaxis()->SetTitle("Reconstruction Efficiency");
    hrecoeffPtZ[i]->GetYaxis()->SetTitleSize(0.045);

    hrecoeff[i]->Write();
    hrecoeffPhi[i]->Write();
    hrecoeffEta[i]->Write();
    hrecoeffPtZ[i]->Write();
  }
  outFile->Close();
}
