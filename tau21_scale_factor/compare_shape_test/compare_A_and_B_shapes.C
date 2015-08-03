#include <TTree.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <iostream>
#include <vector>
#include <string>
#include <TFile.h>
#include <TObject.h>
#include <TSystem.h>
#include <TROOT.h>
#include "TH1.h"
#include "TAttFill.h"

void compare_A_and_B_shapes(){

int save_flag = 0;
save_flag =1 ;// do you want to save

// write the ROOT file names and histo names that you want to compare

char file_name_1[200]={"crab_TT1_semileptonic_ttbar_bk2_reversely_shape.root"};
char file_name_2[200]={"ttbar_signal_and_background_shape_normalize.root"};

//char hist_name_1[200]={"h_had_top_mass_bk1"}; // red
//char hist_name_2[200]={"h_had_top_mass_bk1"}; // blue

char hist_name_1[200]={"h_had_top_mass_signal"}; // red
char hist_name_2[200]={"h_had_top_mass_signal"}; // blue

//  open the siganl and background histograms

TFile  *f1 = new TFile(file_name_1);
TFile  *f2 = new TFile(file_name_2);

TH1D *h_A = (TH1D*)f1->Get(hist_name_1);
TH1D *h_B = (TH1D*)f2->Get(hist_name_2);

// Sumw2 and normalize

double scale;

h_A-> Sumw2();
scale = 1.0/( h_A->Integral() );
h_A->Scale(scale);

h_B-> Sumw2();
scale = 1.0/( h_B->Integral() );
h_B->Scale(scale);

// set color, clone the filled histo and set style 

int A_color = 2;// red
int B_color = 4;// blue

h_A->SetLineColor(A_color);
h_A->GetXaxis()->SetRangeUser(100, 600);// this is for this ttbar histo

TH1D *h_A_fill = (TH1D*) h_A ->Clone("h_A_fill");
h_A_fill -> Sumw2(false);
h_A_fill ->SetFillStyle(1001);
h_A_fill ->SetFillColorAlpha(A_color,0.2);

h_B->SetLineColor(B_color);

TH1D *h_B_fill = (TH1D*) h_B ->Clone("h_B_fill");
h_B_fill -> Sumw2(false);
h_B_fill ->SetFillStyle(1001);
h_B_fill ->SetFillColorAlpha(B_color,0.2);


// draw 

TCanvas* c1 = new TCanvas("c1","",500,500);

h_A->Draw();
h_A_fill->Draw("same");
h_B->Draw("same");
h_B_fill->Draw("same");

// save 

if (save_flag ==1){
//TFile  *myFile = new TFile("/Users/index0192/test.root","recreate");
TFile  *myFile = new TFile("compare_A_and_B.root","recreate");

c1->Write();

h_A->Write();
h_A_fill->Write();

h_B->Write();
h_B_fill->Write();

}






}
