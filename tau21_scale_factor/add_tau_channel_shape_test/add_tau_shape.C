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

void add_tau_shape(){

int save_flag = 0;
save_flag =1 ;

// open the siganl and background histograms

TFile  *f1 = new TFile("ttbar_signal_and_background_shape.root");
TFile  *f2 = new TFile("crab_TT1_semileptonic_ttbar_bk2_reversely_shape.root");
//TFile  *f2 = new TFile("Wbb_background_shape.root");

cout<< "test 1" <<endl;

// get histogram
TH1D *h_muon_Signal = (TH1D*)f1->Get("h_had_top_mass_signal");
TH1D *h_muon_Bkg1 = (TH1D*)f1->Get("h_had_top_mass_bk1");

TH1D *h_tau_Signal = (TH1D*)f2->Get("h_had_top_mass_signal");
TH1D *h_tau_Bkg1 = (TH1D*)f2->Get("h_had_top_mass_bk1");

cout<< "test 2" <<endl;

// create new histo

   TH1D *h_Signal = (TH1D*)h_muon_Signal->Clone("h_MuonPlusTau_signal");
        h_Signal->Reset();

   TH1D *h_Bkg1 = (TH1D*)h_muon_Bkg1->Clone("h_MuonPlusTau_bk1");
        h_Bkg1->Reset();





cout<< "test 3" <<endl;

// Sumw2

h_muon_Signal-> Sumw2();
h_muon_Bkg1-> Sumw2();

h_tau_Signal-> Sumw2();
h_tau_Bkg1-> Sumw2();

h_Signal-> Sumw2();
h_Bkg1-> Sumw2();

cout<< "test 4" <<endl;

// add

      	h_Signal ->Add(h_muon_Signal);
      	h_Signal ->Add(h_tau_Signal);

	h_Bkg1 ->Add(h_muon_Bkg1);
        h_Bkg1 ->Add(h_tau_Bkg1);

cout<< "test 5" <<endl;

// draw 

TCanvas* c1 = new TCanvas("c1","",500,500);

h_Signal->SetLineColor(2);
h_Signal->GetXaxis()->SetRangeUser(100, 600);
h_Signal->Draw();

TH1D *h_Signal_fill = (TH1D*)h_Signal->Clone("h_Signal_fill");
h_Signal_fill-> Sumw2(false);
h_Signal_fill->SetFillStyle(1001);
h_Signal_fill->SetFillColorAlpha(2,0.2);
h_Signal_fill->Draw("same");

h_Bkg1->SetLineColor(3);
h_Bkg1->Draw("same");

TH1D *h_Bkg1_fill = (TH1D*)h_Bkg1->Clone("h_Bkg1_fill");
h_Bkg1_fill-> Sumw2(false);
h_Bkg1_fill->SetFillStyle(1001);
h_Bkg1_fill->SetFillColorAlpha(3,0.2);
h_Bkg1_fill->Draw("same");

cout<< "test 6" <<endl;

// save 

if (save_flag ==1){
//TFile  *myFile = new TFile("/Users/index0192/test.root","recreate");
TFile  *myFile = new TFile("shape_with_add_tau_channel.root","recreate");

c1->Write();

h_Signal     ->Write();
h_Signal_fill->Write();
h_Bkg1       ->Write();
h_Bkg1_fill  ->Write();

}


/*

////////////////////////////////////////////////////////////////////
//                                                                //
//             produce fake data in inclusively 8 categories      //
//                                                                //
////////////////////////////////////////////////////////////////////


// open the old histo

TFile  *fSignal = new TFile("FakesFromJetsResults_Signal.root");
TFile  *fBackground = new TFile("FakesFromJetsResults_Background.root");

////

TH1F *h_FakeData_inclusive_category_[8];// FakeData
TH1F *h_Signal_inclusive_category_[8];
TH1F *h_Background_inclusive_category_[8];

///
char category_name[8][200]={"Inclusive_Barrel_Sigma_Ieta_Ieta_TIGHT_Quark",
                            "Inclusive_Barrel_Sigma_Ieta_Ieta_TIGHT_Gluon",
                            "Inclusive_Barrel_Sigma_Ieta_Ieta_FO_Quark",
                            "Inclusive_Barrel_Sigma_Ieta_Ieta_FO_Gluon",
                            "Inclusive_Endcap_Sigma_Ieta_Ieta_TIGHT_Quark",
                            "Inclusive_Endcap_Sigma_Ieta_Ieta_TIGHT_Gluon",
                            "Inclusive_Endcap_Sigma_Ieta_Ieta_FO_Quark",
                            "Inclusive_Endcap_Sigma_Ieta_Ieta_FO_Gluon"};


for(int i=0;i<8;i++){//open old histo and book fake data histo

h_Signal_inclusive_category_[i]     = (TH1F*)fSignal->Get(category_name[i]);
h_Background_inclusive_category_[i] = (TH1F*)fBackground->Get(category_name[i]);

h_FakeData_inclusive_category_[i] = new TH1F (category_name[i],"",2000,-1,1);
}
////////////

// normalise signal and background histo to 1
for(int i=0;i<8;i++){//

h_Signal_inclusive_category_[i]->Sumw2();
h_Signal_inclusive_category_[i]->Scale((1/h_Signal_inclusive_category_[i]->Integral() ));

h_Background_inclusive_category_[i]->Sumw2();
h_Background_inclusive_category_[i]->Scale((1/h_Background_inclusive_category_[i]->Integral() ));


}


// add the cloned histo to get the fakedata histo with determined fraction of signal 

double fraction_of_signal = 0.7; 
//now the 8 category of histo is uesd to the same fraction of signal ,but you also can set different fraction of signal in each histograms 

for(int i=0;i<8;i++){//

h_FakeData_inclusive_category_[i] -> Sumw2();
h_FakeData_inclusive_category_[i] -> Add(h_Signal_inclusive_category_[i],fraction_of_signal);
h_FakeData_inclusive_category_[i] -> Add(h_Background_inclusive_category_[i],(1-fraction_of_signal));

}

//set name of fake data histo

for(int i=0;i<8;i++){//

h_FakeData_inclusive_category_[i] ->SetName(category_name[i]) ;

}


// save the histos in root file 

     TFile *fout = new TFile("FakeData_new_sample_Fsig0.7_new_code.root","recreate");

for(int i=0;i<8;i++){//

h_FakeData_inclusive_category_[i] ->SetXTitle("SigmaIetaIeta");h_FakeData_inclusive_category_[i] ->Write();

}

///////////////////////////////////////////////////
//                                               //
//             produce fake data in Pt bins      //
//                                               //
///////////////////////////////////////////////////


// open the old histo

TFile  *fSignal_Pt_bins = new TFile("Signal_8_categories_5_Pt_bins.root");
TFile  *fBackground_Pt_bins = new TFile("Background_8_categories_5_Pt_bins.root");

/////////

  //  8 categories and 5 Pt bins
 TH1F *h_FakeData_inclusive_category_Pt_bins[8][5];// fake data
 TH1F *h_Signal_inclusive_category_Pt_bins[8][5];
 TH1F *h_Background_inclusive_category_Pt_bins[8][5];

//////////
char category_Pt_name[8][5][100];

for(int i=0;i<8;i++){//8 categories
 for(int j=0;j<5;j++){//5 Pt bins

  if(i==0){   sprintf( category_Pt_name[i][j],"Sigma_Ieta_Ieta_TIGHT_Quark_Barrel_Pt_Bin_%d",j);}
  if(i==1){   sprintf( category_Pt_name[i][j],"Sigma_Ieta_Ieta_TIGHT_Gluon_Barrel_Pt_Bin_%d",j);}
  if(i==2){   sprintf( category_Pt_name[i][j],"Sigma_Ieta_Ieta_FO_Quark_Barrel_Pt_Bin_%d",j);}
  if(i==3){   sprintf( category_Pt_name[i][j],"Sigma_Ieta_Ieta_FO_Gluon_Barrel_Pt_Bin_%d",j);}
  if(i==4){   sprintf( category_Pt_name[i][j],"Sigma_Ieta_Ieta_TIGHT_Quark_Endcap_Pt_Bin_%d",j);}
  if(i==5){   sprintf( category_Pt_name[i][j],"Sigma_Ieta_Ieta_TIGHT_Gluon_Endcap_Pt_Bin_%d",j);}
  if(i==6){   sprintf( category_Pt_name[i][j],"Sigma_Ieta_Ieta_FO_Quark_Endcap_Pt_Bin_%d",j);}
  if(i==7){   sprintf( category_Pt_name[i][j],"Sigma_Ieta_Ieta_FO_Gluon_Endcap_Pt_Bin_%d",j);}

//cout<<"i:"<<i<<" j:"<<j<<endl;
//cout<<"category_Pt_name[i][j]:"<<category_Pt_name[i][j] <<endl;

 }
}
///////////

//open old histo and book fake data histo
for(int i=0;i<8;i++){//
  for(int j=1;j<5;j++){

h_Signal_inclusive_category_Pt_bins[i][j] = (TH1F*)fSignal_Pt_bins->Get(category_Pt_name[i][j]);
h_Background_inclusive_category_Pt_bins[i][j] = (TH1F*)fBackground_Pt_bins->Get(category_Pt_name[i][j]);

h_FakeData_inclusive_category_Pt_bins[i][j] = new TH1F (category_Pt_name[i][j],"",2000,-1,1);
  }
}
////////////


// normalise signal and background histo to 1
for(int i=0;i<8;i++){//
  for(int j=1;j<5;j++){
h_Signal_inclusive_category_Pt_bins[i][j] ->Sumw2();
h_Signal_inclusive_category_Pt_bins[i][j] ->Scale((1/ h_Signal_inclusive_category_Pt_bins[i][j]->Integral() ));

h_Background_inclusive_category_Pt_bins[i][j]->Sumw2();
h_Background_inclusive_category_Pt_bins[i][j]->Scale((1/h_Background_inclusive_category_Pt_bins[i][j]->Integral() ));

  }
}

// the fraction_of_signal have been defined previously


for(int i=0;i<8;i++){//
    for(int j=1;j<5;j++){
h_FakeData_inclusive_category_Pt_bins[i][j] -> Sumw2();
h_FakeData_inclusive_category_Pt_bins[i][j] -> Add(h_Signal_inclusive_category_Pt_bins[i][j],fraction_of_signal);
h_FakeData_inclusive_category_Pt_bins[i][j] -> Add(h_Background_inclusive_category_Pt_bins[i][j],(1-fraction_of_signal));
     }
}


//set name of fake data histo

for(int i=0;i<8;i++){//
       for(int j=1;j<5;j++){
h_FakeData_inclusive_category_Pt_bins[i][j] ->SetName( category_Pt_name[i][j]) ;
     }
}


// save the histos in root file

     TFile *fout_Pt_bins = new TFile("FakeData_new_sample_Fsig0.7_new_code_Pt_bins.root","recreate");

for(int i=0;i<8;i++){//
       for(int j=1;j<5;j++){
h_FakeData_inclusive_category_Pt_bins[i][j] ->SetXTitle("SigmaIetaIeta");
h_FakeData_inclusive_category_Pt_bins[i][j] ->Write();
     }
}


*/













}
