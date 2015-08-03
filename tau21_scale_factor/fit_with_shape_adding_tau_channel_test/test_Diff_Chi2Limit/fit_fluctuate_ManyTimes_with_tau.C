#include "TH1.h"
#include "TFile.h"
//#include "fit_chi2_err_manytimes.C"
#include "fit_chi2_err_two_components.C"
#include "TStyle.h"
#include "TSystem.h"
#include "TRandom.h"
#include "TCanvas.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//#include <cstring> 

void fit_fluctuate_ManyTimes_with_tau(){

int N_times = 1;//1000   // how many things to fluctuate 

int save_pseudo_data_flag = 0; // save pseudo-data in ROOT file
int save_flag = 0; // save the pull and fit-bias in ROOT file

int sample_flag=6; // choose which sample

//
//TFile *f1 ;
char filename_[200];

                   // strcpy will give the content of filename to filename_, since only filename_ can leave the if's{ }
     if (sample_flag == 0){char filename[200]={"shape_chi2Less3.root"}; strcpy(filename_, filename); }
else if (sample_flag == 1){char filename[200]={"shape_chi2Less4.root"}; strcpy(filename_, filename); }
else if (sample_flag == 2){char filename[200]={"shape_chi2Less5.root"}; strcpy(filename_, filename); }
else if (sample_flag == 3){char filename[200]={"shape_chi2Less10.root"}; strcpy(filename_, filename); }
else if (sample_flag == 4){char filename[200]={"shape_chi2Less20.root"}; strcpy(filename_, filename); }
else if (sample_flag == 5){char filename[200]={"shape_chi2Less50.root"}; strcpy(filename_, filename); }
else if (sample_flag == 6){char filename[200]={"shape_chi2Less100.root"}; strcpy(filename_, filename); }
else if (sample_flag == 7){char filename[200]={"shape_chi2Less500.root"}; strcpy(filename_, filename); }

TFile *f1 = new TFile(filename_);

//

double Frc1[8]={0.375,0.374,0.371,0.356,0.341,0.321,0.308,0.290};
int NumberData[8]={473,536,581,705,791,878,937,1031};

double fraction_1= Frc1[sample_flag] ;//0.10;//         0.56      0.28                0.342
int NumberOfEventOfData = NumberData[sample_flag] ;//536;//  686       1047                536 

//

double lower_SigFrc = 0; double upper_SigFrc = 1.0;
int N_bins_SigFrc =100;


double lower_Pull1 = -10; double upper_Pull1 = 10;
int N_bins_Pull1 =200;

double lower_Pull2 = -2; double upper_Pull2 = 2;
int N_bins_Pull2 =200;

//
//char filename[200]={"normalize_ttbar_semileptonic_15M_filter_OriginalCut_shape.root"};
//char filename[200]={"normalize_ttbar_semileptonic_15M_filter_ChangeClassify_shape.root"};
//char filename[200]={"normalize_ttbar_semileptonic_15M_filter_ChangeClassify_RelaxChi2hadW_shape.root"};
//char filename[200]={"normalize_ttbar_semileptonic_15M_filter_ChangeClassify_RelaxChi2hadW_Chi2Less4_shape.root"};

//cout<<"test1"<<endl;

// TFile *f1 = new TFile("shape_with_add_tau_channel.root");
// TFile *f1 = new TFile(filename);

//TH1F *h_Sig     = (TH1F*)f1->Get("h_MuonPlusTau_signal");
//TH1F *h_Bk1 = (TH1F*)f1->Get("h_MuonPlusTau_bk1");

TH1F *h_Sig     = (TH1F*)f1->Get("h_had_top_mass_signal");
TH1F *h_Bk1 = (TH1F*)f1->Get("h_had_top_mass_bk1");

//cout<<"test2"<<endl;

TH1F *h_Data  =  (TH1F*)h_Sig->Clone();// now I don't have the data
h_Data->Reset();


// clone, Sumw2 and normalize

   TH1F *h_Signal = (TH1F*)h_Sig->Clone();
   TH1F *h_Background1 = (TH1F*)h_Bk1 ->Clone();

h_Signal->Sumw2();
h_Background1->Sumw2();
        
double scale;

scale = 1.0/( h_Signal->Integral() );
h_Signal->Scale(scale);

scale = 1.0/( h_Background1->Integral() );
h_Background1->Scale(scale);

///////////////

    TCanvas * c1 =new TCanvas("c1","the template shape",600,600);
	h_Signal->Draw();
	h_Background1->Draw("same");

/////////////

   // declare the fluctuated histograms

   TH1F *h_data_new = (TH1F*)h_Data->Clone("h_data_new");
	h_data_new->Reset();

   TH1F *h_fill_Sig = (TH1F*)h_Signal->Clone();
        h_fill_Sig->Reset();

   TH1F *h_fill_Bk1 = (TH1F*)h_Background1->Clone();
        h_fill_Bk1->Reset();

//   TH1F *h_fill_Bk2 = (TH1F*)h_Background2->Clone();
//        h_fill_Bk2->Reset();

///////

  TH1F *h_Distri_SigFrc = new TH1F("distribution of signal fraction","",N_bins_SigFrc,lower_SigFrc,upper_SigFrc);
  TH1F *h_Distri_True = new TH1F("distribution of true fraction",""  ,N_bins_SigFrc,lower_SigFrc,upper_SigFrc);

  TH1F *h_Distri_Pull2 = new TH1F("distribution of fit bias","" ,N_bins_Pull2,lower_Pull2,upper_Pull2);
  TH1F *h_Distri_Pull1 = new TH1F("distribution of pull ","" ,N_bins_Pull1,lower_Pull1,upper_Pull1);
///

//int NumberOfEventOfData = 982;//982 

//double fraction_1= 0.1;//0.568
double fraction_2= 1- fraction_1;//0.431
//double fraction_3= 1 - fraction_1 -fraction_2 ;
// Data = fraction_1*Sig + fraction_2*Bk1 + fraction_3*Bk2

double n_1 = NumberOfEventOfData * fraction_1; 
double n_2 = NumberOfEventOfData * fraction_2;
//double n_3 = NumberOfEventOfData * fraction_3;

//int save_pseudo_data_flag = 0;


for (int i=0; i<N_times ;i++)
{

//cout<< "the i-th: "<< i <<" times"<<endl;


// reset to empty

        h_data_new->Reset();
  	h_fill_Sig->Reset();    
	h_fill_Bk1->Reset();
//	h_fill_Bk2->Reset();

int n_1_prime =0;
int n_2_prime =0;
//int n_3_prime =0;
//


n_1_prime = gRandom->Poisson(n_1);
n_2_prime = gRandom->Poisson(n_2);
//n_3_prime = gRandom->Poisson(n_3);


cout<<"n_1_prime: "<<n_1_prime<<endl;
cout<<"n_2_prime: "<<n_2_prime<<endl;
//

      h_fill_Sig ->FillRandom(h_Signal     ,n_1_prime );
      h_fill_Bk1 ->FillRandom(h_Background1,n_2_prime );
//      h_fill_Bk2 ->FillRandom(h_Background2,n_3_prime );


//
//        h_data_new->Reset();

      h_data_new ->Add(h_fill_Sig);
      h_data_new ->Add(h_fill_Bk1);
//      h_data_new ->Add(h_fill_Bk2);
//

// save pseudo data, that is for 1 times then save it. Save the pseudo data
if (save_pseudo_data_flag == 1)
{
TFile  *myFile = new TFile("pseudodata.root","recreate");

h_data_new->Write();
h_fill_Sig->Write();
h_fill_Bk1->Write();

}

double n_data = h_data_new->GetEntries();
double n_Sig = h_fill_Sig->GetEntries();
double n_Bk1 = h_fill_Bk1->GetEntries();
//double n_Bk2 = h_fill_Bk2->GetEntries();

//
//    	TCanvas * c2 =new TCanvas("c2","the data after fluctuate",600,600);
//	h_data_new->SetLineColor(1);
//  	h_data_new->GetYaxis()->SetRangeUser(0.,2000);
//	h_data_new->Draw();
//	h_fill_Sig->Draw("same");
//	h_fill_Bk1->Draw("same");
//	h_fill_Bk2->Draw("same");
//

        //TCanvas * c4 =new TCanvas("c4","for the fit",600,600);



//char name[200]={"test_2_components_fit"};
char nu[10];
    sprintf(nu,"%d",i);
cout<<"nu: "<< nu<<endl;
  std::string name = nu;
cout<<"name: "<< name<<endl;

double sigFrac_intial =  fraction_1;//0.48;//n_Sig/n_data ;//n_Sig/n_data ;// 0.48
//double bkg1Frac_intial = fraction_2;//0.4;//n_Bk1/n_data ;

   double sig, sigerr,bkgfrc1,bkgfrcerr1,chi2;

fit_chi2_err_two_components(    h_data_new,
                                h_Signal,
                                h_Background1,
                                //h_Background2,
                                name,
                                sig, sigFrac_intial ,sigerr,
                                //bkgfrc1, bkg1Frac_intial, bkgfrcerr1,
                                chi2);


/*     fit_chi2_err_manytimes(    h_data_new,
                                h_Signal,
                                h_Background1,
                                //h_Background2,
                                "name",
                                sig, sigFrac_intial ,sigerr,
                                //bkgfrc1, bkg1Frac_intial, bkgfrcerr1,
                                chi2);
*/

/*   double sig, sigerr,bkgfrc1,bkgfrcerr1,chi2;
     fit_chi2_err_manytimes(	h_data_new,
				h_Signal,
				h_Background1,
				h_Background2,
				"name",
				sig, sigFrac_intial ,sigerr,
				bkgfrc1, bkg1Frac_intial, bkgfrcerr1,
				chi2);
*/

h_Distri_SigFrc->Fill(sig);
h_Distri_True->Fill(n_Sig/n_data);


double pull2 = (sig - (n_Sig/n_data) ) / (n_Sig/n_data) ;   
h_Distri_Pull2->Fill(pull2);

double pull1 = (sig - (n_Sig/n_data) ) / sigerr ;
h_Distri_Pull1->Fill(pull1);

      cout<< endl;
//      cout << "  name: " << name <<endl;
      cout<<"*********************************************************" <<endl;

      cout<< endl;
cout<< "the i-th: "<< i <<" times"<<endl;

//      cout << "Fitted result = " << sig << " +- " << sigerr ;//<< endl;

      cout <<" sig    :" << sig    << " sigerr    : " << sigerr <<endl;
      bkgfrc1= 1 - sig ;
      cout <<" bkgfrc1:"<< bkgfrc1 <<endl;


//      cout <<" bkgfrc1:"<< bkgfrc1 << " bkgfrcerr1: " << bkgfrcerr1<<endl;
//	double bkgfrc2= 1 - sig - bkgfrc1;
//      cout <<" bkgfrc2:"<< bkgfrc2 <<endl;

      cout << " chi2/dof= " << chi2 << endl;

cout<<endl;
//cout<<"NumberOfEventOfData: "<<NumberOfEventOfData<<endl;
cout<< "fraction 1 should be: "<< n_Sig/n_data <<endl;
cout<< "fraction 2 should be: "<< 1- n_Sig/n_data <<endl;


      cout<<"***********************************************************" <<endl;


}

 gStyle->SetOptStat(1);
 gStyle->SetOptFit(1);

TCanvas * c0 =new TCanvas("c0","distribution of fit result",600,600);
h_Distri_SigFrc->Draw();
h_Distri_SigFrc->Fit("gaus");
c0 ->Update();

TCanvas * c3 =new TCanvas("c3","true",600,600);
//h_Distri_True->Draw();
h_Distri_True->Fit("gaus");
c3 ->Update();

TCanvas * c4 =new TCanvas("c4","pull",600,600);
//h_Distri_Pull1->Draw();
h_Distri_Pull1 ->Fit("gaus");
c4 ->Update();

TCanvas * c2 =new TCanvas("c2","fit bias",600,600);
h_Distri_Pull2->Draw();
h_Distri_Pull2->Fit("gaus");
c2 ->Update();

cout<<endl;
cout<<"NumberOfEventOfData: "<<NumberOfEventOfData<<endl;
cout<< "fraction 1 should be: "<< fraction_1 <<endl;
cout<< "fraction 2 should be: "<< fraction_2 <<endl;


//int save_flag = 1;
//save_flag=1;

if( save_flag == 1){
TFile *myFile = new TFile("test_pull_and_FitBias.root","recreate");
c4->Write();
c2->Write();

}



}
