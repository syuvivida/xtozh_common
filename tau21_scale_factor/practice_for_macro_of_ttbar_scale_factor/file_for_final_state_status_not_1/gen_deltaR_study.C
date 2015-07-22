#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <TF1.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TBox.h>
#include <TMath.h>
#include <TFile.h>
#include <TList.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TBranch.h>
#include <TRandom.h>
#include <TProfile.h>
#include <TLorentzVector.h>
#include <TSystemDirectory.h>
#include "untuplizer.h"

#include "gen_lepW_and_Mu_Nu.C"

using namespace std;

void gen_lepW_and_Mu_Nu(TreeReader &,vector<Int_t> *,
 				     vector<Int_t> *,
				     vector<Int_t> *);

void gen_deltaR_study(){
  TreeReader data("combine_130_files.root");

//--------------------------------------------------------------------//
  // Declare the histogram of reconstructed mass

//  TH1D* h_genParId = new TH1D("h_genParId", "gen particle ID",60 , -30,30 );


//--------------------------------------------------------------------//

  // begin of event loop
  
//  for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++){
  for (Long64_t ev = 0; ev < 100000; ev++){

    if ( ev % 5000 == 0 )
      fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());

//        cout<<"ev event: "<<ev<<endl;

    data.GetEntry(ev);
    

    Int_t    nGenPar   = data.GetInt("nGenPar"); 
    Int_t*   genParId  = data.GetPtrInt("genParId");
    Int_t*   genParSt  = data.GetPtrInt("genParSt");
    Float_t* genParPt  = data.GetPtrFloat("genParPt");
    Float_t* genParEta = data.GetPtrFloat("genParEta");
    Float_t* genParPhi = data.GetPtrFloat("genParPhi");
    Float_t* genParM   = data.GetPtrFloat("genParM");
    Float_t* genParE     = data.GetPtrFloat("genParE");
    Int_t*   genMomParId = data.GetPtrInt("genMomParId");
    Int_t*   genMo1      = data.GetPtrInt("genMo1");


    //-----------------------------------------------------------------------------------// find gen index of lep_W and its' decay product Muon and neutrino  

    vector<Int_t> gen_lep_W_index;
    vector<Int_t> gen_lep_nu_index;
    vector<Int_t> gen_lep_mu_index;

    gen_lepW_and_Mu_Nu(data, &gen_lep_W_index,
			     &gen_lep_nu_index,
			     &gen_lep_mu_index);

   //-----------------------------------------------------------------------------------//

  }   // end of event loop


/*    TCanvas * c1 =new TCanvas("c1","",600,600);
    h_genParId->Draw();
    TCanvas * c2 =new TCanvas("c2","",600,600);
    h_elePt->Draw();
    TCanvas * c3 =new TCanvas("c3","",600,600);
    h_muPt->Draw();
    TCanvas * c4 =new TCanvas("c4","",600,600);
    h_CA8jetPt->Draw();
    TCanvas * c5 =new TCanvas("c5","",600,600);
    h_pfMetCorrPt->Draw();
*/
    TCanvas * c6 =new TCanvas("c6","",600,600);
//h_deltaR_genNu_recoNu_smaller->Draw();
//h_deltaR_genNu_recoLep->Draw();
//h_LooseCA8jetPt->Draw();
//h_nCA8jet_pass_Evt_cut->Draw();
//h_leptonic_top_mass->Draw();
//h_deltaR_genNu_recoNu1->Draw();
//    TCanvas * c7 =new TCanvas("c7","",600,600);
//h_hadronic_top_mass->Draw();
//h_deltaR_genNu_recoNu2->SetLineColor(2);
//h_deltaR_genNu_recoNu2->SetLineColor(kOrange+10);
//h_deltaR_genNu_recoNu2->Draw("same");
//    c1->Print("genParId.png");
//    c2->Print("elePt.png");
//    c3->Print("muPt.png");
//    c4->Print("CA8jetPt.png");
//    c5->Print("pfMetCorrPt.png");

  // Fitting the mass ratio
  
  
}

