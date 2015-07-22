#include "TH1.h"
#include "TFile.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TRandom.h"
#include "TCanvas.h"
#include <fstream>
#include <TTree.h>
#include <iostream>
#include <string>
#include <TObject.h>
#include <TROOT.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void normalize_TH1F( TH1F *);

void normalize_and_save(){


// open TH1F in ROOT file 
//TFile  *f1 = new TFile("ttbar_signal_and_background_shape.root");

//char filename[200]={"ttbar_semileptonic_15M_filter_OriginalCut_shape.root"};
//char filename[200]={"ttbar_semileptonic_15M_filter_ChangeClassify_shape.root"};
//char filename[200]={"ttbar_semileptonic_15M_filter_ChangeClassify_RelaxChi2hadW_shape.root"};
char filename[200]={"ttbar_semileptonic_15M_filter_ChangeClassify_RelaxChi2hadW_Chi2Less4_shape.root"};

  std::string name = filename;

TFile  *f1 = new TFile(filename);

// ttbar_semileptonic_15M_filter_OriginalCut_shape.root
// ttbar_semileptonic_15M_filter_ChangeClassify_shape.root
// ttbar_semileptonic_15M_filter_ChangeClassify_RelaxChi2hadW_shape.root
// ttbar_semileptonic_15M_filter_ChangeClassify_RelaxChi2hadW_Chi2Less4_shape.root

//
    TH1F  *h_had_top_mass_signal_normalize = (TH1F*) f1->Get("h_had_top_mass_signal");
    TH1F  *h_had_top_mass_bk1_normalize = (TH1F*) f1->Get("h_had_top_mass_bk1");
    TH1F  *h_had_top_mass_bk2_normalize = (TH1F*) f1->Get("h_had_top_mass_bk2");

    TH1F  *h_lep_top_mass_signal_normalize = (TH1F*) f1->Get("h_lep_top_mass_signal");
    TH1F  *h_lep_top_mass_bk1_normalize = (TH1F*) f1->Get("h_lep_top_mass_bk1");
    TH1F  *h_lep_top_mass_bk2_normalize = (TH1F*) f1->Get("h_lep_top_mass_bk2");

//h_had_top_mass_signal_normalize->SetName("h_had_top_mass_signal_normalize");

// normailize 


//    h_had_top_mass_signal_normalize->Sumw2();
//    h_had_top_mass_signal_normalize->Scale((1/h_had_top_mass_signal_normalize->GetEntries()));

    normalize_TH1F( h_had_top_mass_signal_normalize);
    normalize_TH1F( h_had_top_mass_bk1_normalize);
    normalize_TH1F( h_had_top_mass_bk2_normalize);

    normalize_TH1F( h_lep_top_mass_signal_normalize);
    normalize_TH1F( h_lep_top_mass_bk1_normalize);
    normalize_TH1F( h_lep_top_mass_bk2_normalize);

//    h_had_top_mass_signal_normalize->Draw();

{
 TCanvas * d9 =new TCanvas("d9","",600,600);

h_had_top_mass_signal_normalize->Draw("histe");
h_had_top_mass_bk1_normalize->Draw("histesame");
h_had_top_mass_bk2_normalize->Draw("histesame");
}

{ 
 TCanvas * d10 =new TCanvas("d10","",600,600);

h_lep_top_mass_signal_normalize->Draw("histe");
h_lep_top_mass_bk1_normalize->Draw("histesame");
h_lep_top_mass_bk2_normalize->Draw("histesame");
}


// save the normalized TH1F in new ROOT file
//TFile  *f2 = new TFile("ttbar_signal_and_background_shape_normalize.root","RECREATE");

  std::string prefix("normalize_");
  std::string new_name = prefix + name ;

  char new_filename[200]; 
  strcpy(new_filename, new_name.c_str());

TFile  *f2 = new TFile(new_filename,"RECREATE");

    	h_had_top_mass_signal_normalize->Write();
	h_had_top_mass_bk1_normalize->Write();
	h_had_top_mass_bk2_normalize->Write();

	h_lep_top_mass_signal_normalize->Write();
	h_lep_top_mass_bk1_normalize->Write();
	h_lep_top_mass_bk2_normalize->Write();

}

void normalize_TH1F( TH1F *h_name)
{
    h_name->Sumw2();
    h_name->Scale((1/h_name->GetEntries()));

}
