#include "TH1.h"
#include "TFile.h"
#include "fit_chi2_err.C"
#include "TStyle.h"
#include "TSystem.h"
#include "TRandom.h"
#include "TCanvas.h"

void fit_with_fluctuate_test(){

 TFile *fGetData = new TFile("fake_data_3_comp.root");

TH1F *h_Data       = (TH1F*)fGetData->Get("h_FakeData") ;
TH1F *h_Signal     = (TH1F*)fGetData->Get("h_had_top_mass_signal");
TH1F *h_Background1 = (TH1F*)fGetData->Get("h_had_top_mass_bk1");
TH1F *h_Background2 = (TH1F*)fGetData->Get("h_had_top_mass_bk2");

TCanvas * c0 =new TCanvas("c0","for the fit",600,600);

//
    TCanvas * c1 =new TCanvas("c1","the template shape",600,600);
	h_Signal->Draw();
	h_Background1->Draw("same");
	h_Background2->Draw("same");

///

   TH1F *h_data_new = (TH1F*)h_Data->Clone();
	h_data_new->Reset();

   TH1F *h_fill_Sig = (TH1F*)h_Signal->Clone();
        h_fill_Sig->Reset();

   TH1F *h_fill_Bk1 = (TH1F*)h_Background1->Clone();
        h_fill_Bk1->Reset();

   TH1F *h_fill_Bk2 = (TH1F*)h_Background2->Clone();
        h_fill_Bk2->Reset();

////

int NumberOfEventOfData = 982; 

double fraction_1= 0.49;
double fraction_2= 0.39;
double fraction_3= 1 - fraction_1 -fraction_2 ;
// Data = fraction_1*Sig + fraction_2*Bk1 + fraction_3*Bk2

double n_1 = NumberOfEventOfData * fraction_1; 
double n_2 = NumberOfEventOfData * fraction_2;
double n_3 = NumberOfEventOfData * fraction_3;

//////

int n_1_prime = gRandom->Poisson(n_1);
int n_2_prime = gRandom->Poisson(n_2);
int n_3_prime = gRandom->Poisson(n_3);

//

      h_fill_Sig ->FillRandom(h_Signal     ,n_1_prime );
      h_fill_Bk1 ->FillRandom(h_Background1,n_2_prime );
      h_fill_Bk2 ->FillRandom(h_Background2,n_3_prime );

//
/*    TCanvas * c3 =new TCanvas("c3","compare the fluctuated template and original ones",600,600);
        h_Signal->Draw();
	//h_fill_Sig->Scale(1/h_fill_Sig->Integral() );
        //h_fill_Sig->SetLineColor(1);
	//h_fill_Sig->Draw("same");
        h_Background1->Draw("same");
	//h_fill_Bk1->Scale(1/h_fill_Bk1->Integral() );
	//h_fill_Bk1->SetLineColor(1);
	//h_fill_Bk1->Draw("same");
        h_Background2->Draw("same");
        h_fill_Bk2->Scale(1/h_fill_Bk2->Integral() );
        h_fill_Bk2->SetLineColor(1);
        h_fill_Bk2->Draw("same");
*/

//

      h_data_new ->Add(h_fill_Sig);
      h_data_new ->Add(h_fill_Bk1);
      h_data_new ->Add(h_fill_Bk2);
//

double n_data = h_data_new->GetEntries();
double n_Sig = h_fill_Sig->GetEntries();
double n_Bk1 = h_fill_Bk1->GetEntries();
double n_Bk2 = h_fill_Bk2->GetEntries();

//cout<< "fraction 1 should be: "<< n_Sig/n_data <<endl;
//cout<< "fraction 2 should be: "<< n_Bk1/n_data <<endl;
//cout<< "fraction 3 should be: "<< n_Bk2/n_data <<endl;
//
    	TCanvas * c2 =new TCanvas("c2","the data after fluctuate",600,600);
	h_data_new->SetLineColor(1);
//  	h_data_new->GetYaxis()->SetRangeUser(0.,2000);
	h_data_new->Draw();
	h_fill_Sig->Draw("same");
	h_fill_Bk1->Draw("same");
	h_fill_Bk2->Draw("same");
//

        //TCanvas * c4 =new TCanvas("c4","for the fit",600,600);

char name[200]={"test_3_components_fit"};


double sigFrac_intial = 0.75;//n_Sig/n_data ;// 0.48
double bkg1Frac_intial = 0.13; //n_Bk1/n_data ;// 0.4


   double sig, sigerr,bkgfrc1,bkgfrcerr1,chi2;
     fit_chi2_err(	h_data_new,
			h_Signal,
			h_Background1,
			h_Background2,
			"name",
			sig, sigFrac_intial ,sigerr,
			bkgfrc1, bkg1Frac_intial , bkgfrcerr1,
			chi2);

      cout<< endl;
      cout << "  name: " << name <<endl;

//      cout << "Fitted result = " << sig << " +- " << sigerr ;//<< endl;

      cout <<" sig    :" << sig    << " sigerr    : " << sigerr <<endl;
      cout <<" bkgfrc1:"<< bkgfrc1 << " bkgfrcerr1: " << bkgfrcerr1<<endl;
	double bkgfrc2= 1 - sig - bkgfrc1;
      cout <<" bkgfrc2:"<< bkgfrc2 <<endl;

      cout << " chi2/dof= " << chi2 << endl;

cout<<endl;
cout<<"NumberOfEventOfData: "<<NumberOfEventOfData<<endl;
cout<< "fraction 1 should be: "<< n_Sig/n_data <<endl;
cout<< "fraction 2 should be: "<< n_Bk1/n_data <<endl;
cout<< "fraction 3 should be: "<< n_Bk2/n_data <<endl;

cout<< "sigFrac_intial: "<< sigFrac_intial <<endl;
cout<< "bkg1Frac_intial: "<< bkg1Frac_intial <<endl;

/*
  TFile *fGetData = new TFile("FakeData_new_sample_Fsig0.7.root");

  TFile *fSignal = new TFile("FakesFromJetsResults_Signal.root");

  TFile *fBackground = new TFile("FakesFromJetsResults_Background.root");

////////////// choose which category of histo you want to perform Pull2



cout<<"Endcap_FO_Gluon"<<endl;
TH1F  *h_Data = (TH1F*)fGetData->Get("FakeData_Inclusive_Endcap_Sigma_Ieta_Ieta_FO_Gluon");
TH1F  *h_Signal = (TH1F*)fSignal->Get("Inclusive_Endcap_Sigma_Ieta_Ieta_FO_Gluon");
TH1F  *h_Background = (TH1F*)fBackground->Get("Inclusive_Endcap_Sigma_Ieta_Ieta_FO_Gluon");


//////////////


TCanvas *c1 = new TCanvas("c1","",640,640);
  h_Data->GetXaxis()->SetRangeUser(0,0.05);
  h_Data->Draw();

TCanvas *c2 = new TCanvas("c2","",640,640);
  h_Signal->GetXaxis()->SetRangeUser(0,0.05);
  h_Signal->Draw();

TCanvas *c3 = new TCanvas("c3","",640,640);
  h_Background ->GetXaxis()->SetRangeUser(0,0.05);
  h_Background ->Draw();


      double sig, sigerr,chi2;


///////////  start Pull2   //////////////////

float Purity = 0.7 ;//input the fake data purity 

int GetNum = h_Data ->GetEntries();

//cout<<"GetNum integral:"<<GetNum<<endl;

float Nsig = GetNum*Purity;
float Nbkg = GetNum*(1-Purity);


  TH1F *h_fillSig = new TH1F("fillSig","",2000,-1,1);
  TH1F *h_fillBkg = new TH1F("fillBkg","",2000,-1,1);
  TH1F *h_pseudoexperiment = new TH1F("pseudoexperiment","",2000,-1,1);

  TH1F *h_Pull1 = new TH1F("Pull1","",50,-5,5);
  TH1F *h_Pull2 = new TH1F("Pull2","",100,-0.2,0.2);

TCanvas *c4 = new TCanvas("c4","",640,640);

  for(int i=0;i<100;i++){// pseudo-experiment

      //preapre the pseudo-experiment
      int temp_nsig = gRandom->Poisson(Nsig);
      int temp_nbkg = gRandom->Poisson(Nbkg);
cout<<"i:"<<i<<endl;
//cout<<"temp_nsig:"<<temp_nsig<<endl;
//cout<<"temp_nbkg:"<<temp_nbkg<<endl;


      h_fillSig->Reset();
      h_fillBkg->Reset();
      h_pseudoexperiment->Reset();

      h_fillSig ->FillRandom(h_Signal, temp_nsig);
      h_fillBkg ->FillRandom(h_Background, temp_nbkg);

//h_fillSig->Draw();

      h_pseudoexperiment ->Add(h_fillSig);
      h_pseudoexperiment ->Add(h_fillBkg);

//      h_pseudoexperiment->Draw();


      //fit it and get Pull1 and Pull2  
      fit_chi2_err(h_pseudoexperiment ,h_Signal ,h_Background ,sig ,sigerr ,chi2);

      cout << "Fitted result = " << sig << " +- " << sigerr << endl;
      cout << "Purity = " << Purity << endl;

      float pull1_value = (sig-Purity)/sigerr;
      float pull2_value = (sig-Purity)/Purity;

      if(sigerr>1e-6)h_Pull1->Fill(pull1_value);
      if(Purity>1e-6)h_Pull2->Fill(pull2_value);

  }



 gStyle->SetOptStat(1);
 gStyle->SetOptFit(1);

TCanvas *c5 = new TCanvas("c5","",640,640);

//c5->cd();
// gStyle->SetOptStat(1);
// gStyle->SetOptFit(1);
//    h_Pull1->Draw();
//    h_Pull1->ResetStats();
    h_Pull1 ->Fit("gaus");
//    h_Pull1->Draw();
// gStyle->SetOptStat(1);
// gStyle->SetOptFit(1);

c5 ->Update();

TCanvas *c6 = new TCanvas("c6","",640,640);

 gStyle->SetOptStat(1);
 gStyle->SetOptFit(1);

    h_Pull2 ->Fit("gaus");

c6 ->Update();

    TFile *myFile = new TFile("Pull1_and_Pull2_new_sample.root","recreate");

    h_Pull1->SetXTitle("Pull: (fit-input)/fit_err");
    h_Pull1->Write();

    h_Pull2->SetXTitle("Bias: (fit-input)/input");
    h_Pull2->Write();


*/

}
