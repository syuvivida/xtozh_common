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


void compare_2Samples_5PtBins(){

    //////////////////////////////////////////////
    //                                          //
    //    open old histograms of Tprime sample  //
    //                                          //
    //////////////////////////////////////////////
TFile  *f1 = new TFile("Tprime_5_Pt_Bins_Barrel_and_Endcap.root");


    TH1F  *h_Sig_Tprime_TIGHT_Gluon_Barrel_Pt_Bin_[5];
    TH1F  *h_New_Sig_Tprime_TIGHT_Gluon_Barrel_Pt_Bin_[5];    

    TH1F  *h_Sig_Tprime_TIGHT_Quark_Barrel_Pt_Bin_[5];
    TH1F  *h_New_Sig_Tprime_TIGHT_Quark_Barrel_Pt_Bin_[5];

    TH1F  *h_Sig_Tprime_FO_Gluon_Barrel_Pt_Bin_[5];
    TH1F  *h_New_Sig_Tprime_FO_Gluon_Barrel_Pt_Bin_[5];

    TH1F  *h_Sig_Tprime_FO_Quark_Barrel_Pt_Bin_[5];
    TH1F  *h_New_Sig_Tprime_FO_Quark_Barrel_Pt_Bin_[5];

    TH1F  *h_Sig_Tprime_TIGHT_Gluon_Endcap_Pt_Bin_[5];
    TH1F  *h_New_Sig_Tprime_TIGHT_Gluon_Endcap_Pt_Bin_[5];

    TH1F  *h_Sig_Tprime_TIGHT_Quark_Endcap_Pt_Bin_[5];
    TH1F  *h_New_Sig_Tprime_TIGHT_Quark_Endcap_Pt_Bin_[5];

    TH1F  *h_Sig_Tprime_FO_Gluon_Endcap_Pt_Bin_[5];
    TH1F  *h_New_Sig_Tprime_FO_Gluon_Endcap_Pt_Bin_[5];

    TH1F  *h_Sig_Tprime_FO_Quark_Endcap_Pt_Bin_[5];
    TH1F  *h_New_Sig_Tprime_FO_Quark_Endcap_Pt_Bin_[5];


   char newhname[500];

   for (int i=0;i<5;i++){

       sprintf( newhname,"Sigma_Ieta_Ieta_TIGHT_Gluon_Barrel_Pt_Bin_%d",i);

       h_Sig_Tprime_TIGHT_Gluon_Barrel_Pt_Bin_[i] =(TH1F*) f1->Get( newhname );
       h_New_Sig_Tprime_TIGHT_Gluon_Barrel_Pt_Bin_[i] =(TH1F*)h_Sig_Tprime_TIGHT_Gluon_Barrel_Pt_Bin_[i]->Clone(newhname);

       sprintf( newhname,"Sigma_Ieta_Ieta_TIGHT_Quark_Barrel_Pt_Bin_%d",i);

       h_Sig_Tprime_TIGHT_Quark_Barrel_Pt_Bin_[i] =(TH1F*) f1->Get( newhname );
       h_New_Sig_Tprime_TIGHT_Quark_Barrel_Pt_Bin_[i] =(TH1F*)h_Sig_Tprime_TIGHT_Quark_Barrel_Pt_Bin_[i]->Clone(newhname);

       sprintf( newhname,"Sigma_Ieta_Ieta_FO_Gluon_Barrel_Pt_Bin_%d",i);

       h_Sig_Tprime_FO_Gluon_Barrel_Pt_Bin_[i] =(TH1F*) f1->Get( newhname );
       h_New_Sig_Tprime_FO_Gluon_Barrel_Pt_Bin_[i] =(TH1F*)h_Sig_Tprime_FO_Gluon_Barrel_Pt_Bin_[i]->Clone(newhname);

       sprintf( newhname,"Sigma_Ieta_Ieta_FO_Quark_Barrel_Pt_Bin_%d",i);

       h_Sig_Tprime_FO_Quark_Barrel_Pt_Bin_[i] =(TH1F*) f1->Get( newhname );
       h_New_Sig_Tprime_FO_Quark_Barrel_Pt_Bin_[i] =(TH1F*)h_Sig_Tprime_FO_Quark_Barrel_Pt_Bin_[i]->Clone(newhname);

       sprintf( newhname,"Sigma_Ieta_Ieta_TIGHT_Gluon_Endcap_Pt_Bin_%d",i);

       h_Sig_Tprime_TIGHT_Gluon_Endcap_Pt_Bin_[i] =(TH1F*) f1->Get( newhname );
       h_New_Sig_Tprime_TIGHT_Gluon_Endcap_Pt_Bin_[i] =(TH1F*)h_Sig_Tprime_TIGHT_Gluon_Endcap_Pt_Bin_[i]->Clone(newhname);

       sprintf( newhname,"Sigma_Ieta_Ieta_TIGHT_Quark_Endcap_Pt_Bin_%d",i);

       h_Sig_Tprime_TIGHT_Quark_Endcap_Pt_Bin_[i] =(TH1F*) f1->Get( newhname );
       h_New_Sig_Tprime_TIGHT_Quark_Endcap_Pt_Bin_[i] =(TH1F*)h_Sig_Tprime_TIGHT_Quark_Endcap_Pt_Bin_[i]->Clone(newhname);

       sprintf( newhname,"Sigma_Ieta_Ieta_FO_Gluon_Endcap_Pt_Bin_%d",i);

       h_Sig_Tprime_FO_Gluon_Endcap_Pt_Bin_[i] =(TH1F*) f1->Get( newhname );
       h_New_Sig_Tprime_FO_Gluon_Endcap_Pt_Bin_[i] =(TH1F*)h_Sig_Tprime_FO_Gluon_Endcap_Pt_Bin_[i]->Clone(newhname);

       sprintf( newhname,"Sigma_Ieta_Ieta_FO_Quark_Endcap_Pt_Bin_%d",i);

       h_Sig_Tprime_FO_Quark_Endcap_Pt_Bin_[i] =(TH1F*) f1->Get( newhname );
       h_New_Sig_Tprime_FO_Quark_Endcap_Pt_Bin_[i] =(TH1F*)h_Sig_Tprime_FO_Quark_Endcap_Pt_Bin_[i]->Clone(newhname);

       }

//h_Sig_Tprime_TIGHT_Gluon_Barrel_Pt_Bin_[4]->Draw();
//h_New_Sig_Tprime_TIGHT_Gluon_Barrel_Pt_Bin_[4]->Draw();       


    /////////////////////////////////////
    //                                 //
    //   normalize the histogram to 1  //
    //                                 //
    /////////////////////////////////////


   for (int i=0;i<5;i++){


       h_New_Sig_Tprime_TIGHT_Gluon_Barrel_Pt_Bin_[i]->Sumw2();
       h_New_Sig_Tprime_TIGHT_Gluon_Barrel_Pt_Bin_[i]->Scale((1/h_New_Sig_Tprime_TIGHT_Gluon_Barrel_Pt_Bin_[i]->GetEntries()));
       h_New_Sig_Tprime_TIGHT_Quark_Barrel_Pt_Bin_[i]->Sumw2();
       h_New_Sig_Tprime_TIGHT_Quark_Barrel_Pt_Bin_[i]->Scale((1/h_New_Sig_Tprime_TIGHT_Quark_Barrel_Pt_Bin_[i]->GetEntries()));
       h_New_Sig_Tprime_FO_Gluon_Barrel_Pt_Bin_[i]->Sumw2();
       h_New_Sig_Tprime_FO_Gluon_Barrel_Pt_Bin_[i]->Scale((1/h_New_Sig_Tprime_FO_Gluon_Barrel_Pt_Bin_[i]->GetEntries()));

       h_New_Sig_Tprime_FO_Quark_Barrel_Pt_Bin_[i]->Sumw2();
       h_New_Sig_Tprime_FO_Quark_Barrel_Pt_Bin_[i]->Scale((1/h_New_Sig_Tprime_FO_Quark_Barrel_Pt_Bin_[i]->GetEntries()));

       h_New_Sig_Tprime_TIGHT_Gluon_Endcap_Pt_Bin_[i]->Sumw2();
       h_New_Sig_Tprime_TIGHT_Gluon_Endcap_Pt_Bin_[i]->Scale((1/h_New_Sig_Tprime_TIGHT_Gluon_Endcap_Pt_Bin_[i]->GetEntries()));
       h_New_Sig_Tprime_TIGHT_Quark_Endcap_Pt_Bin_[i]->Sumw2();
       h_New_Sig_Tprime_TIGHT_Quark_Endcap_Pt_Bin_[i]->Scale((1/h_New_Sig_Tprime_TIGHT_Quark_Endcap_Pt_Bin_[i]->GetEntries()));
       h_New_Sig_Tprime_FO_Gluon_Endcap_Pt_Bin_[i]->Sumw2();
       h_New_Sig_Tprime_FO_Gluon_Endcap_Pt_Bin_[i]->Scale((1/h_New_Sig_Tprime_FO_Gluon_Endcap_Pt_Bin_[i]->GetEntries()));

       h_New_Sig_Tprime_FO_Quark_Endcap_Pt_Bin_[i]->Sumw2();
       h_New_Sig_Tprime_FO_Quark_Endcap_Pt_Bin_[i]->Scale((1/h_New_Sig_Tprime_FO_Quark_Endcap_Pt_Bin_[i]->GetEntries()));

       }

//h_New_Sig_Tprime_TIGHT_Gluon_Barrel_Pt_Bin_[4]->Draw();

     /////////////////////////////////////////
     //                                     //
     //  open old histograms of GJet sample //
     //                                     //
     /////////////////////////////////////////

TFile  *f2 = new TFile("GJet_5_Pt_Bins_Barrel_and_Endcap.root");

    TH1F  *h_Sig_GJet_TIGHT_Gluon_Barrel_Pt_Bin_[5];
    TH1F  *h_New_Sig_GJet_TIGHT_Gluon_Barrel_Pt_Bin_[5];

    TH1F  *h_Sig_GJet_TIGHT_Quark_Barrel_Pt_Bin_[5];
    TH1F  *h_New_Sig_GJet_TIGHT_Quark_Barrel_Pt_Bin_[5];

    TH1F  *h_Sig_GJet_FO_Gluon_Barrel_Pt_Bin_[5];
    TH1F  *h_New_Sig_GJet_FO_Gluon_Barrel_Pt_Bin_[5];

    TH1F  *h_Sig_GJet_FO_Quark_Barrel_Pt_Bin_[5];
    TH1F  *h_New_Sig_GJet_FO_Quark_Barrel_Pt_Bin_[5];

    TH1F  *h_Sig_GJet_TIGHT_Gluon_Endcap_Pt_Bin_[5];
    TH1F  *h_New_Sig_GJet_TIGHT_Gluon_Endcap_Pt_Bin_[5];

    TH1F  *h_Sig_GJet_TIGHT_Quark_Endcap_Pt_Bin_[5];
    TH1F  *h_New_Sig_GJet_TIGHT_Quark_Endcap_Pt_Bin_[5];

    TH1F  *h_Sig_GJet_FO_Gluon_Endcap_Pt_Bin_[5];
    TH1F  *h_New_Sig_GJet_FO_Gluon_Endcap_Pt_Bin_[5];

    TH1F  *h_Sig_GJet_FO_Quark_Endcap_Pt_Bin_[5];
    TH1F  *h_New_Sig_GJet_FO_Quark_Endcap_Pt_Bin_[5];


   for (int i=0;i<5;i++){

       sprintf( newhname,"Sigma_Ieta_Ieta_TIGHT_Gluon_Barrel_Pt_Bin_%d",i);

       h_Sig_GJet_TIGHT_Gluon_Barrel_Pt_Bin_[i] =(TH1F*) f2->Get( newhname );
       h_New_Sig_GJet_TIGHT_Gluon_Barrel_Pt_Bin_[i] =(TH1F*)h_Sig_GJet_TIGHT_Gluon_Barrel_Pt_Bin_[i]->Clone(newhname);

       sprintf( newhname,"Sigma_Ieta_Ieta_TIGHT_Quark_Barrel_Pt_Bin_%d",i);

       h_Sig_GJet_TIGHT_Quark_Barrel_Pt_Bin_[i] =(TH1F*) f2->Get( newhname );
       h_New_Sig_GJet_TIGHT_Quark_Barrel_Pt_Bin_[i] =(TH1F*)h_Sig_GJet_TIGHT_Quark_Barrel_Pt_Bin_[i]->Clone(newhname);

       sprintf( newhname,"Sigma_Ieta_Ieta_FO_Gluon_Barrel_Pt_Bin_%d",i);

       h_Sig_GJet_FO_Gluon_Barrel_Pt_Bin_[i] =(TH1F*) f2->Get( newhname );
       h_New_Sig_GJet_FO_Gluon_Barrel_Pt_Bin_[i] =(TH1F*)h_Sig_GJet_FO_Gluon_Barrel_Pt_Bin_[i]->Clone(newhname);

       sprintf( newhname,"Sigma_Ieta_Ieta_FO_Quark_Barrel_Pt_Bin_%d",i);

       h_Sig_GJet_FO_Quark_Barrel_Pt_Bin_[i] =(TH1F*) f2->Get( newhname );
       h_New_Sig_GJet_FO_Quark_Barrel_Pt_Bin_[i] =(TH1F*)h_Sig_GJet_FO_Quark_Barrel_Pt_Bin_[i]->Clone(newhname);

       sprintf( newhname,"Sigma_Ieta_Ieta_TIGHT_Gluon_Endcap_Pt_Bin_%d",i);

       h_Sig_GJet_TIGHT_Gluon_Endcap_Pt_Bin_[i] =(TH1F*) f2->Get( newhname );
       h_New_Sig_GJet_TIGHT_Gluon_Endcap_Pt_Bin_[i] =(TH1F*)h_Sig_GJet_TIGHT_Gluon_Endcap_Pt_Bin_[i]->Clone(newhname);

       sprintf( newhname,"Sigma_Ieta_Ieta_TIGHT_Quark_Endcap_Pt_Bin_%d",i);

       h_Sig_GJet_TIGHT_Quark_Endcap_Pt_Bin_[i] =(TH1F*) f2->Get( newhname );
       h_New_Sig_GJet_TIGHT_Quark_Endcap_Pt_Bin_[i] =(TH1F*)h_Sig_GJet_TIGHT_Quark_Endcap_Pt_Bin_[i]->Clone(newhname);

       sprintf( newhname,"Sigma_Ieta_Ieta_FO_Gluon_Endcap_Pt_Bin_%d",i);

       h_Sig_GJet_FO_Gluon_Endcap_Pt_Bin_[i] =(TH1F*) f2->Get( newhname );
       h_New_Sig_GJet_FO_Gluon_Endcap_Pt_Bin_[i] =(TH1F*)h_Sig_GJet_FO_Gluon_Endcap_Pt_Bin_[i]->Clone(newhname);

       sprintf( newhname,"Sigma_Ieta_Ieta_FO_Quark_Endcap_Pt_Bin_%d",i);

       h_Sig_GJet_FO_Quark_Endcap_Pt_Bin_[i] =(TH1F*) f2->Get( newhname );
       h_New_Sig_GJet_FO_Quark_Endcap_Pt_Bin_[i] =(TH1F*)h_Sig_GJet_FO_Quark_Endcap_Pt_Bin_[i]->Clone(newhname);

       }

//h_Sig_GJet_TIGHT_Gluon_Barrel_Pt_Bin_[0]->Draw();
//h_New_Sig_GJet_TIGHT_Gluon_Barrel_Pt_Bin_[0]->Draw();

     /////////////////////////////////////
     //                                 //
     //   normalize the histogram to 1  //
     //                                 //
     /////////////////////////////////////

   for (int i=0;i<5;i++){

       h_New_Sig_GJet_TIGHT_Gluon_Barrel_Pt_Bin_[i]->Sumw2();
       h_New_Sig_GJet_TIGHT_Gluon_Barrel_Pt_Bin_[i]->Scale((1/h_New_Sig_GJet_TIGHT_Gluon_Barrel_Pt_Bin_[i]->GetEntries()));

       h_New_Sig_GJet_TIGHT_Quark_Barrel_Pt_Bin_[i]->Sumw2();
       h_New_Sig_GJet_TIGHT_Quark_Barrel_Pt_Bin_[i]->Scale((1/h_New_Sig_GJet_TIGHT_Quark_Barrel_Pt_Bin_[i]->GetEntries()));

       h_New_Sig_GJet_FO_Gluon_Barrel_Pt_Bin_[i]->Sumw2();
       h_New_Sig_GJet_FO_Gluon_Barrel_Pt_Bin_[i]->Scale((1/h_New_Sig_GJet_FO_Gluon_Barrel_Pt_Bin_[i]->GetEntries()));

       h_New_Sig_GJet_FO_Quark_Barrel_Pt_Bin_[i]->Sumw2();
       h_New_Sig_GJet_FO_Quark_Barrel_Pt_Bin_[i]->Scale((1/h_New_Sig_GJet_FO_Quark_Barrel_Pt_Bin_[i]->GetEntries()));

       h_New_Sig_GJet_TIGHT_Gluon_Endcap_Pt_Bin_[i]->Sumw2();
       h_New_Sig_GJet_TIGHT_Gluon_Endcap_Pt_Bin_[i]->Scale((1/h_New_Sig_GJet_TIGHT_Gluon_Endcap_Pt_Bin_[i]->GetEntries()));

       h_New_Sig_GJet_TIGHT_Quark_Endcap_Pt_Bin_[i]->Sumw2();
       h_New_Sig_GJet_TIGHT_Quark_Endcap_Pt_Bin_[i]->Scale((1/h_New_Sig_GJet_TIGHT_Quark_Endcap_Pt_Bin_[i]->GetEntries()));

       h_New_Sig_GJet_FO_Gluon_Endcap_Pt_Bin_[i]->Sumw2();
       h_New_Sig_GJet_FO_Gluon_Endcap_Pt_Bin_[i]->Scale((1/h_New_Sig_GJet_FO_Gluon_Endcap_Pt_Bin_[i]->GetEntries()));

       h_New_Sig_GJet_FO_Quark_Endcap_Pt_Bin_[i]->Sumw2();
       h_New_Sig_GJet_FO_Quark_Endcap_Pt_Bin_[i]->Scale((1/h_New_Sig_GJet_FO_Quark_Endcap_Pt_Bin_[i]->GetEntries()));


       }

//cout<<h_New_Sig_GJet_TIGHT_Gluon_Barrel_Pt_Bin_[0]->GetEntries()<<endl;

//h_New_Sig_GJet_TIGHT_Gluon_Barrel_Pt_Bin_[0]->Draw();
//h_New_Sig_GJet_FO_Quark_Endcap_Pt_Bin_[0]->Draw();

//h_Sig_GJet_FO_Gluon_Barrel_Pt_Bin_[1]->Draw();
//h_New_Sig_GJet_FO_Gluon_Barrel_Pt_Bin_[1]->Draw();



//cout<< h_New_Sig_Tprime_FO_Gluon_Barrel_Pt_Bin_[1]->GetEntries()<<endl;
//cout<< h_New_Sig_GJet_FO_Gluon_Barrel_Pt_Bin_[1]->GetEntries()<<endl;


    ///////////////////////////////////
    //                               //
    //   superimpose two histograms  //
    //                               //
    ///////////////////////////////////



TCanvas * c_TIGHT_Gluon_Barrel_Pt_Bin_[5];
TCanvas * c_TIGHT_Quark_Barrel_Pt_Bin_[5];
TCanvas * c_FO_Gluon_Barrel_Pt_Bin_[5];
TCanvas * c_FO_Quark_Barrel_Pt_Bin_[5];
TCanvas * c_TIGHT_Gluon_Endcap_Pt_Bin_[5];
TCanvas * c_TIGHT_Quark_Endcap_Pt_Bin_[5];
TCanvas * c_FO_Gluon_Endcap_Pt_Bin_[5];
TCanvas * c_FO_Quark_Endcap_Pt_Bin_[5];

int S_TIGHT_Gluon_Barrel_Pt_Bin_[5]={1};// define Status to prevent #1=0 and #2=0 
int S_TIGHT_Quark_Barrel_Pt_Bin_[5]={1};// if that case happen I will adjust the Status from 1 to 0
int S_FO_Gluon_Barrel_Pt_Bin_[5]={1};// and in the loop saving the TCanvas I will remove the Status=0 one 
int S_FO_Quark_Barrel_Pt_Bin_[5]={1};
int S_TIGHT_Gluon_Endcap_Pt_Bin_[5]={1};
int S_TIGHT_Quark_Endcap_Pt_Bin_[5]={1};
int S_FO_Gluon_Endcap_Pt_Bin_[5]={1};
int S_FO_Quark_Endcap_Pt_Bin_[5]={1};






double n1,n2;

   for (int i=0;i<5;i++){

       sprintf( newhname,"c_TIGHT_Gluon_Barrel_Pt_Bin_%d",i);

c_TIGHT_Gluon_Barrel_Pt_Bin_[i] = new TCanvas(newhname,newhname,600,600);

c_TIGHT_Gluon_Barrel_Pt_Bin_[i]->cd();

n1=0;
n2=0;
n1 = h_New_Sig_Tprime_TIGHT_Gluon_Barrel_Pt_Bin_[i]->GetEntries();
n2 = h_New_Sig_GJet_TIGHT_Gluon_Barrel_Pt_Bin_[i]->GetEntries();
cout<<"TIGHT_Gluon_Barrel,i:"<<i<<endl;
cout<<"# of Tprime:"<<n1<<endl;
cout<<"# of GJet:"<<n2<<endl;

      if( n1!=0 && n2!=0 ){

           h_New_Sig_Tprime_TIGHT_Gluon_Barrel_Pt_Bin_[i]->GetXaxis()->SetRangeUser(0,0.04);
           h_New_Sig_Tprime_TIGHT_Gluon_Barrel_Pt_Bin_[i]->GetYaxis()->SetRangeUser(0,1);
           h_New_Sig_Tprime_TIGHT_Gluon_Barrel_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
           h_New_Sig_Tprime_TIGHT_Gluon_Barrel_Pt_Bin_[i]->SetMarkerColor(2);//red
           h_New_Sig_Tprime_TIGHT_Gluon_Barrel_Pt_Bin_[i]->SetLineColor(2);
           h_New_Sig_Tprime_TIGHT_Gluon_Barrel_Pt_Bin_[i]->Draw("histe");

           h_New_Sig_GJet_TIGHT_Gluon_Barrel_Pt_Bin_[i]->SetMarkerColor(4);//blue
           h_New_Sig_GJet_TIGHT_Gluon_Barrel_Pt_Bin_[i]->SetLineColor(4);
           h_New_Sig_GJet_TIGHT_Gluon_Barrel_Pt_Bin_[i]->Draw("histesame");
          }
      else if (n1==0 && n2!=0){ 
           h_New_Sig_GJet_TIGHT_Gluon_Barrel_Pt_Bin_[i]->GetXaxis()->SetRangeUser(0,0.04);
           h_New_Sig_GJet_TIGHT_Gluon_Barrel_Pt_Bin_[i]->GetYaxis()->SetRangeUser(0,1);
           h_New_Sig_GJet_TIGHT_Gluon_Barrel_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
           h_New_Sig_GJet_TIGHT_Gluon_Barrel_Pt_Bin_[i]->SetMarkerColor(4);//blue
           h_New_Sig_GJet_TIGHT_Gluon_Barrel_Pt_Bin_[i]->SetLineColor(4);
           h_New_Sig_GJet_TIGHT_Gluon_Barrel_Pt_Bin_[i]->Draw("histe");
          }
      else if (n1!=0 && n2==0){
           h_New_Sig_Tprime_TIGHT_Gluon_Barrel_Pt_Bin_[i]->GetXaxis()->SetRangeUser(0,0.04);
           h_New_Sig_Tprime_TIGHT_Gluon_Barrel_Pt_Bin_[i]->GetYaxis()->SetRangeUser(0,1);
           h_New_Sig_Tprime_TIGHT_Gluon_Barrel_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
           h_New_Sig_Tprime_TIGHT_Gluon_Barrel_Pt_Bin_[i]->SetMarkerColor(2);//red
           h_New_Sig_Tprime_TIGHT_Gluon_Barrel_Pt_Bin_[i]->SetLineColor(2);
           h_New_Sig_Tprime_TIGHT_Gluon_Barrel_Pt_Bin_[i]->Draw("histe");
          }
      else if (n1==0 && n2==0){
           cout<<"TIGHT_Gluon_Barrel Pt["<<i<<"]"<<endl;
           S_TIGHT_Gluon_Barrel_Pt_Bin_[i]=0;

          }


//c_TIGHT_Gluon_Barrel_Pt_Bin_[i]->Write();

       sprintf( newhname,"c_TIGHT_Quark_Barrel_Pt_Bin_%d",i);

c_TIGHT_Quark_Barrel_Pt_Bin_[i] = new TCanvas(newhname,newhname,600,600);

c_TIGHT_Quark_Barrel_Pt_Bin_[i]->cd();

n1=0;
n2=0;
n1 = h_New_Sig_Tprime_TIGHT_Quark_Barrel_Pt_Bin_[i]->GetEntries();
n2 = h_New_Sig_GJet_TIGHT_Quark_Barrel_Pt_Bin_[i]->GetEntries();
cout<<"TIGHT_Quark_Barrel,i:"<<i<<endl;
cout<<"# of Tprime:"<<n1<<endl;
cout<<"# of GJet:"<<n2<<endl;

      if( n1!=0 && n2!=0 ){

           h_New_Sig_Tprime_TIGHT_Quark_Barrel_Pt_Bin_[i]->GetXaxis()->SetRangeUser(0,0.04);
           h_New_Sig_Tprime_TIGHT_Quark_Barrel_Pt_Bin_[i]->GetYaxis()->SetRangeUser(0,1);
           h_New_Sig_Tprime_TIGHT_Quark_Barrel_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
           h_New_Sig_Tprime_TIGHT_Quark_Barrel_Pt_Bin_[i]->SetMarkerColor(2);//red
           h_New_Sig_Tprime_TIGHT_Quark_Barrel_Pt_Bin_[i]->SetLineColor(2);
           h_New_Sig_Tprime_TIGHT_Quark_Barrel_Pt_Bin_[i]->Draw("histe");

           h_New_Sig_GJet_TIGHT_Quark_Barrel_Pt_Bin_[i]->SetMarkerColor(4);//blue
           h_New_Sig_GJet_TIGHT_Quark_Barrel_Pt_Bin_[i]->SetLineColor(4);
           h_New_Sig_GJet_TIGHT_Quark_Barrel_Pt_Bin_[i]->Draw("histesame");
          }
      else if (n1==0 && n2!=0){
           h_New_Sig_GJet_TIGHT_Quark_Barrel_Pt_Bin_[i]->GetXaxis()->SetRangeUser(0,0.04);
           h_New_Sig_GJet_TIGHT_Quark_Barrel_Pt_Bin_[i]->GetYaxis()->SetRangeUser(0,1);
           h_New_Sig_GJet_TIGHT_Quark_Barrel_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
           h_New_Sig_GJet_TIGHT_Quark_Barrel_Pt_Bin_[i]->SetMarkerColor(4);//blue
           h_New_Sig_GJet_TIGHT_Quark_Barrel_Pt_Bin_[i]->SetLineColor(4);
           h_New_Sig_GJet_TIGHT_Quark_Barrel_Pt_Bin_[i]->Draw("histe");
          }
      else if (n1!=0 && n2==0){
           h_New_Sig_Tprime_TIGHT_Quark_Barrel_Pt_Bin_[i]->GetXaxis()->SetRangeUser(0,0.04);
           h_New_Sig_Tprime_TIGHT_Quark_Barrel_Pt_Bin_[i]->GetYaxis()->SetRangeUser(0,1);
           h_New_Sig_Tprime_TIGHT_Quark_Barrel_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
           h_New_Sig_Tprime_TIGHT_Quark_Barrel_Pt_Bin_[i]->SetMarkerColor(2);//red
           h_New_Sig_Tprime_TIGHT_Quark_Barrel_Pt_Bin_[i]->SetLineColor(2);
           h_New_Sig_Tprime_TIGHT_Quark_Barrel_Pt_Bin_[i]->Draw("histe");
          }
      else if (n1==0 && n2==0){
           cout<<"TIGHT_Quark_Barrel Pt["<<i<<"]"<<endl;
           S_TIGHT_Quark_Barrel_Pt_Bin_[i]=0;
          }

///////////////
       sprintf( newhname,"c_FO_Gluon_Barrel_Pt_Bin_%d",i);

c_FO_Gluon_Barrel_Pt_Bin_[i] = new TCanvas(newhname,newhname,600,600);

c_FO_Gluon_Barrel_Pt_Bin_[i]->cd();

n1=0;
n2=0;
n1 = h_New_Sig_Tprime_FO_Gluon_Barrel_Pt_Bin_[i]->GetEntries();
n2 = h_New_Sig_GJet_FO_Gluon_Barrel_Pt_Bin_[i]->GetEntries();
cout<<"FO_Gluon_Barrel,i:"<<i<<endl;
cout<<"# of Tprime:"<<n1<<endl;
cout<<"# of GJet:"<<n2<<endl;




      if( n1!=0 && n2!=0 ){

           h_New_Sig_Tprime_FO_Gluon_Barrel_Pt_Bin_[i]->GetXaxis()->SetRangeUser(0,0.04);
           h_New_Sig_Tprime_FO_Gluon_Barrel_Pt_Bin_[i]->GetYaxis()->SetRangeUser(0,1);
           h_New_Sig_Tprime_FO_Gluon_Barrel_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
           h_New_Sig_Tprime_FO_Gluon_Barrel_Pt_Bin_[i]->SetMarkerColor(2);//red
           h_New_Sig_Tprime_FO_Gluon_Barrel_Pt_Bin_[i]->SetLineColor(2);
           h_New_Sig_Tprime_FO_Gluon_Barrel_Pt_Bin_[i]->Draw("histe");

           h_New_Sig_GJet_FO_Gluon_Barrel_Pt_Bin_[i]->SetMarkerColor(4);//blue
           h_New_Sig_GJet_FO_Gluon_Barrel_Pt_Bin_[i]->SetLineColor(4);
           h_New_Sig_GJet_FO_Gluon_Barrel_Pt_Bin_[i]->Draw("histesame");
          }
      else if (n1==0 && n2!=0){
           h_New_Sig_GJet_FO_Gluon_Barrel_Pt_Bin_[i]->GetXaxis()->SetRangeUser(0,0.04);
           h_New_Sig_GJet_FO_Gluon_Barrel_Pt_Bin_[i]->GetYaxis()->SetRangeUser(0,1);
           h_New_Sig_GJet_FO_Gluon_Barrel_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
           h_New_Sig_GJet_FO_Gluon_Barrel_Pt_Bin_[i]->SetMarkerColor(4);//blue
           h_New_Sig_GJet_FO_Gluon_Barrel_Pt_Bin_[i]->SetLineColor(4);
           h_New_Sig_GJet_FO_Gluon_Barrel_Pt_Bin_[i]->Draw("histe");
          }
      else if (n1!=0 && n2==0){
           h_New_Sig_Tprime_FO_Gluon_Barrel_Pt_Bin_[i]->GetXaxis()->SetRangeUser(0,0.04);
           h_New_Sig_Tprime_FO_Gluon_Barrel_Pt_Bin_[i]->GetYaxis()->SetRangeUser(0,1);
           h_New_Sig_Tprime_FO_Gluon_Barrel_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
           h_New_Sig_Tprime_FO_Gluon_Barrel_Pt_Bin_[i]->SetMarkerColor(2);//red
           h_New_Sig_Tprime_FO_Gluon_Barrel_Pt_Bin_[i]->SetLineColor(2);
           h_New_Sig_Tprime_FO_Gluon_Barrel_Pt_Bin_[i]->Draw("histe");
          }
      else if (n1==0 && n2==0){
           cout<<"FO_Gluon_Barrel Pt["<<i<<"]"<<endl;
           S_FO_Gluon_Barrel_Pt_Bin_[i]=0;
          }



/////////////

       sprintf( newhname,"c_FO_Quark_Barrel_Pt_Bin_%d",i);

c_FO_Quark_Barrel_Pt_Bin_[i] = new TCanvas(newhname,newhname,600,600);

c_FO_Quark_Barrel_Pt_Bin_[i]->cd();

n1=0;
n2=0;
n1 = h_New_Sig_Tprime_FO_Quark_Barrel_Pt_Bin_[i]->GetEntries();
n2 = h_New_Sig_GJet_FO_Quark_Barrel_Pt_Bin_[i]->GetEntries();
cout<<"FO_Quark_Barrel,i:"<<i<<endl;
cout<<"# of Tprime:"<<n1<<endl;
cout<<"# of GJet:"<<n2<<endl;

      if( n1!=0 && n2!=0 ){

           h_New_Sig_Tprime_FO_Quark_Barrel_Pt_Bin_[i]->GetXaxis()->SetRangeUser(0,0.04);
           h_New_Sig_Tprime_FO_Quark_Barrel_Pt_Bin_[i]->GetYaxis()->SetRangeUser(0,1);
           h_New_Sig_Tprime_FO_Quark_Barrel_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
           h_New_Sig_Tprime_FO_Quark_Barrel_Pt_Bin_[i]->SetMarkerColor(2);//red
           h_New_Sig_Tprime_FO_Quark_Barrel_Pt_Bin_[i]->SetLineColor(2);
           h_New_Sig_Tprime_FO_Quark_Barrel_Pt_Bin_[i]->Draw("histe");

           h_New_Sig_GJet_FO_Quark_Barrel_Pt_Bin_[i]->SetMarkerColor(4);//blue
           h_New_Sig_GJet_FO_Quark_Barrel_Pt_Bin_[i]->SetLineColor(4);
           h_New_Sig_GJet_FO_Quark_Barrel_Pt_Bin_[i]->Draw("histesame");
          }
      else if (n1==0 && n2!=0){
           h_New_Sig_GJet_FO_Quark_Barrel_Pt_Bin_[i]->GetXaxis()->SetRangeUser(0,0.04);
           h_New_Sig_GJet_FO_Quark_Barrel_Pt_Bin_[i]->GetYaxis()->SetRangeUser(0,1);
           h_New_Sig_GJet_FO_Quark_Barrel_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
           h_New_Sig_GJet_FO_Quark_Barrel_Pt_Bin_[i]->SetMarkerColor(4);//blue
           h_New_Sig_GJet_FO_Quark_Barrel_Pt_Bin_[i]->SetLineColor(4);
           h_New_Sig_GJet_FO_Quark_Barrel_Pt_Bin_[i]->Draw("histe");
          }
      else if (n1!=0 && n2==0){
           h_New_Sig_Tprime_FO_Quark_Barrel_Pt_Bin_[i]->GetXaxis()->SetRangeUser(0,0.04);
           h_New_Sig_Tprime_FO_Quark_Barrel_Pt_Bin_[i]->GetYaxis()->SetRangeUser(0,1);
           h_New_Sig_Tprime_FO_Quark_Barrel_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
           h_New_Sig_Tprime_FO_Quark_Barrel_Pt_Bin_[i]->SetMarkerColor(2);//red
           h_New_Sig_Tprime_FO_Quark_Barrel_Pt_Bin_[i]->SetLineColor(2);
           h_New_Sig_Tprime_FO_Quark_Barrel_Pt_Bin_[i]->Draw("histe");
          }
      else if (n1==0 && n2==0){
           cout<<"FO_Quark_Barrel Pt["<<i<<"]"<<endl;
           S_FO_Quark_Barrel_Pt_Bin_[i]=0;
          }





//////////////////////

       sprintf( newhname,"c_TIGHT_Gluon_Endcap_Pt_Bin_%d",i);

c_TIGHT_Gluon_Endcap_Pt_Bin_[i] = new TCanvas(newhname,newhname,600,600);

c_TIGHT_Gluon_Endcap_Pt_Bin_[i]->cd();

n1=0;
n2=0;
n1 = h_New_Sig_Tprime_TIGHT_Gluon_Endcap_Pt_Bin_[i]->GetEntries();
n2 = h_New_Sig_GJet_TIGHT_Gluon_Endcap_Pt_Bin_[i]->GetEntries();
cout<<"TIGHT_Gluon_Endcap,i:"<<i<<endl;
cout<<"# of Tprime:"<<n1<<endl;
cout<<"# of GJet:"<<n2<<endl;


      if( n1!=0 && n2!=0 ){

           h_New_Sig_Tprime_TIGHT_Gluon_Endcap_Pt_Bin_[i]->GetXaxis()->SetRangeUser(0,0.04);
           h_New_Sig_Tprime_TIGHT_Gluon_Endcap_Pt_Bin_[i]->GetYaxis()->SetRangeUser(0,1);
           h_New_Sig_Tprime_TIGHT_Gluon_Endcap_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
           h_New_Sig_Tprime_TIGHT_Gluon_Endcap_Pt_Bin_[i]->SetMarkerColor(2);//red
           h_New_Sig_Tprime_TIGHT_Gluon_Endcap_Pt_Bin_[i]->SetLineColor(2);
           h_New_Sig_Tprime_TIGHT_Gluon_Endcap_Pt_Bin_[i]->Draw("histe");

           h_New_Sig_GJet_TIGHT_Gluon_Endcap_Pt_Bin_[i]->SetMarkerColor(4);//blue
           h_New_Sig_GJet_TIGHT_Gluon_Endcap_Pt_Bin_[i]->SetLineColor(4);
           h_New_Sig_GJet_TIGHT_Gluon_Endcap_Pt_Bin_[i]->Draw("histesame");
          }
      else if (n1==0 && n2!=0){
           h_New_Sig_GJet_TIGHT_Gluon_Endcap_Pt_Bin_[i]->GetXaxis()->SetRangeUser(0,0.04);
           h_New_Sig_GJet_TIGHT_Gluon_Endcap_Pt_Bin_[i]->GetYaxis()->SetRangeUser(0,1);
           h_New_Sig_GJet_TIGHT_Gluon_Endcap_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
           h_New_Sig_GJet_TIGHT_Gluon_Endcap_Pt_Bin_[i]->SetMarkerColor(4);//blue
           h_New_Sig_GJet_TIGHT_Gluon_Endcap_Pt_Bin_[i]->SetLineColor(4);
           h_New_Sig_GJet_TIGHT_Gluon_Endcap_Pt_Bin_[i]->Draw("histe");
          }
      else if (n1!=0 && n2==0){
           h_New_Sig_Tprime_TIGHT_Gluon_Endcap_Pt_Bin_[i]->GetXaxis()->SetRangeUser(0,0.04);
           h_New_Sig_Tprime_TIGHT_Gluon_Endcap_Pt_Bin_[i]->GetYaxis()->SetRangeUser(0,1);
           h_New_Sig_Tprime_TIGHT_Gluon_Endcap_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
           h_New_Sig_Tprime_TIGHT_Gluon_Endcap_Pt_Bin_[i]->SetMarkerColor(2);//red
           h_New_Sig_Tprime_TIGHT_Gluon_Endcap_Pt_Bin_[i]->SetLineColor(2);
           h_New_Sig_Tprime_TIGHT_Gluon_Endcap_Pt_Bin_[i]->Draw("histe");
          }
      else if (n1==0 && n2==0){
           cout<<"TIGHT_Gluon_Endcap Pt["<<i<<"]"<<endl;
           S_TIGHT_Gluon_Endcap_Pt_Bin_[i]=0;
          }





////////////////////////////

       sprintf( newhname,"c_TIGHT_Quark_Endcap_Pt_Bin_%d",i);

c_TIGHT_Quark_Endcap_Pt_Bin_[i] = new TCanvas(newhname,newhname,600,600);

c_TIGHT_Quark_Endcap_Pt_Bin_[i]->cd();

n1=0;
n2=0;
n1 = h_New_Sig_Tprime_TIGHT_Quark_Endcap_Pt_Bin_[i]->GetEntries();
n2 = h_New_Sig_GJet_TIGHT_Quark_Endcap_Pt_Bin_[i]->GetEntries();
cout<<"TIGHT_Quark_Endcap,i:"<<i<<endl;
cout<<"# of Tprime:"<<n1<<endl;
cout<<"# of GJet:"<<n2<<endl;



      if( n1!=0 && n2!=0 ){

           h_New_Sig_Tprime_TIGHT_Quark_Endcap_Pt_Bin_[i]->GetXaxis()->SetRangeUser(0,0.04);
           h_New_Sig_Tprime_TIGHT_Quark_Endcap_Pt_Bin_[i]->GetYaxis()->SetRangeUser(0,1);
           h_New_Sig_Tprime_TIGHT_Quark_Endcap_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
           h_New_Sig_Tprime_TIGHT_Quark_Endcap_Pt_Bin_[i]->SetMarkerColor(2);//red
           h_New_Sig_Tprime_TIGHT_Quark_Endcap_Pt_Bin_[i]->SetLineColor(2);
           h_New_Sig_Tprime_TIGHT_Quark_Endcap_Pt_Bin_[i]->Draw("histe");

           h_New_Sig_GJet_TIGHT_Quark_Endcap_Pt_Bin_[i]->SetMarkerColor(4);//blue
           h_New_Sig_GJet_TIGHT_Quark_Endcap_Pt_Bin_[i]->SetLineColor(4);
           h_New_Sig_GJet_TIGHT_Quark_Endcap_Pt_Bin_[i]->Draw("histesame");
          }
      else if (n1==0 && n2!=0){
           h_New_Sig_GJet_TIGHT_Quark_Endcap_Pt_Bin_[i]->GetXaxis()->SetRangeUser(0,0.04);
           h_New_Sig_GJet_TIGHT_Quark_Endcap_Pt_Bin_[i]->GetYaxis()->SetRangeUser(0,1);
           h_New_Sig_GJet_TIGHT_Quark_Endcap_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
           h_New_Sig_GJet_TIGHT_Quark_Endcap_Pt_Bin_[i]->SetMarkerColor(4);//blue
           h_New_Sig_GJet_TIGHT_Quark_Endcap_Pt_Bin_[i]->SetLineColor(4);
           h_New_Sig_GJet_TIGHT_Quark_Endcap_Pt_Bin_[i]->Draw("histe");
          }
      else if (n1!=0 && n2==0){
           h_New_Sig_Tprime_TIGHT_Quark_Endcap_Pt_Bin_[i]->GetXaxis()->SetRangeUser(0,0.04);
           h_New_Sig_Tprime_TIGHT_Quark_Endcap_Pt_Bin_[i]->GetYaxis()->SetRangeUser(0,1);
           h_New_Sig_Tprime_TIGHT_Quark_Endcap_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
           h_New_Sig_Tprime_TIGHT_Quark_Endcap_Pt_Bin_[i]->SetMarkerColor(2);//red
           h_New_Sig_Tprime_TIGHT_Quark_Endcap_Pt_Bin_[i]->SetLineColor(2);
           h_New_Sig_Tprime_TIGHT_Quark_Endcap_Pt_Bin_[i]->Draw("histe");
          }
      else if (n1==0 && n2==0){
           cout<<"TIGHT_Quark_Endcap Pt["<<i<<"]"<<endl;
           S_TIGHT_Quark_Endcap_Pt_Bin_[i]=0;
          }






///////////////////////////
       sprintf( newhname,"c_FO_Gluon_Endcap_Pt_Bin_%d",i);

c_FO_Gluon_Endcap_Pt_Bin_[i] = new TCanvas(newhname,newhname,600,600);

c_FO_Gluon_Endcap_Pt_Bin_[i]->cd();

n1=0;
n2=0;
n1 = h_New_Sig_Tprime_FO_Gluon_Endcap_Pt_Bin_[i]->GetEntries();
n2 = h_New_Sig_GJet_FO_Gluon_Endcap_Pt_Bin_[i]->GetEntries();
cout<<"FO_Gluon_Endcap,i:"<<i<<endl;
cout<<"# of Tprime:"<<n1<<endl;
cout<<"# of GJet:"<<n2<<endl;




      if( n1!=0 && n2!=0 ){

           h_New_Sig_Tprime_FO_Gluon_Endcap_Pt_Bin_[i]->GetXaxis()->SetRangeUser(0,0.04);
           h_New_Sig_Tprime_FO_Gluon_Endcap_Pt_Bin_[i]->GetYaxis()->SetRangeUser(0,1);
           h_New_Sig_Tprime_FO_Gluon_Endcap_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
           h_New_Sig_Tprime_FO_Gluon_Endcap_Pt_Bin_[i]->SetMarkerColor(2);//red
           h_New_Sig_Tprime_FO_Gluon_Endcap_Pt_Bin_[i]->SetLineColor(2);
           h_New_Sig_Tprime_FO_Gluon_Endcap_Pt_Bin_[i]->Draw("histe");

           h_New_Sig_GJet_FO_Gluon_Endcap_Pt_Bin_[i]->SetMarkerColor(4);//blue
           h_New_Sig_GJet_FO_Gluon_Endcap_Pt_Bin_[i]->SetLineColor(4);
           h_New_Sig_GJet_FO_Gluon_Endcap_Pt_Bin_[i]->Draw("histesame");
          }
      else if (n1==0 && n2!=0){
           h_New_Sig_GJet_FO_Gluon_Endcap_Pt_Bin_[i]->GetXaxis()->SetRangeUser(0,0.04);
           h_New_Sig_GJet_FO_Gluon_Endcap_Pt_Bin_[i]->GetYaxis()->SetRangeUser(0,1);
           h_New_Sig_GJet_FO_Gluon_Endcap_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
           h_New_Sig_GJet_FO_Gluon_Endcap_Pt_Bin_[i]->SetMarkerColor(4);//blue
           h_New_Sig_GJet_FO_Gluon_Endcap_Pt_Bin_[i]->SetLineColor(4);
           h_New_Sig_GJet_FO_Gluon_Endcap_Pt_Bin_[i]->Draw("histe");
          }
      else if (n1!=0 && n2==0){
           h_New_Sig_Tprime_FO_Gluon_Endcap_Pt_Bin_[i]->GetXaxis()->SetRangeUser(0,0.04);
           h_New_Sig_Tprime_FO_Gluon_Endcap_Pt_Bin_[i]->GetYaxis()->SetRangeUser(0,1);
           h_New_Sig_Tprime_FO_Gluon_Endcap_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
           h_New_Sig_Tprime_FO_Gluon_Endcap_Pt_Bin_[i]->SetMarkerColor(2);//red
           h_New_Sig_Tprime_FO_Gluon_Endcap_Pt_Bin_[i]->SetLineColor(2);
           h_New_Sig_Tprime_FO_Gluon_Endcap_Pt_Bin_[i]->Draw("histe");
          }
      else if (n1==0 && n2==0){
           cout<<"FO_Gluon_Endcap Pt["<<i<<"]"<<endl;
           S_FO_Gluon_Endcap_Pt_Bin_[i]=0;
          }





/////////////
       sprintf( newhname,"c_FO_Quark_Endcap_Pt_Bin_%d",i);

c_FO_Quark_Endcap_Pt_Bin_[i] = new TCanvas(newhname,newhname,600,600);

c_FO_Quark_Endcap_Pt_Bin_[i]->cd();

n1=0;
n2=0;
n1 = h_New_Sig_Tprime_FO_Quark_Endcap_Pt_Bin_[i]->GetEntries();
n2 = h_New_Sig_GJet_FO_Quark_Endcap_Pt_Bin_[i]->GetEntries();
cout<<"FO_Quark_Endcap,i:"<<i<<endl;
cout<<"# of Tprime:"<<n1<<endl;
cout<<"# of GJet:"<<n2<<endl;




      if( n1!=0 && n2!=0 ){

           h_New_Sig_Tprime_FO_Quark_Endcap_Pt_Bin_[i]->GetXaxis()->SetRangeUser(0,0.04);
           h_New_Sig_Tprime_FO_Quark_Endcap_Pt_Bin_[i]->GetYaxis()->SetRangeUser(0,1);
           h_New_Sig_Tprime_FO_Quark_Endcap_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
           h_New_Sig_Tprime_FO_Quark_Endcap_Pt_Bin_[i]->SetMarkerColor(2);//red
           h_New_Sig_Tprime_FO_Quark_Endcap_Pt_Bin_[i]->SetLineColor(2);
           h_New_Sig_Tprime_FO_Quark_Endcap_Pt_Bin_[i]->Draw("histe");

           h_New_Sig_GJet_FO_Quark_Endcap_Pt_Bin_[i]->SetMarkerColor(4);//blue
           h_New_Sig_GJet_FO_Quark_Endcap_Pt_Bin_[i]->SetLineColor(4);
           h_New_Sig_GJet_FO_Quark_Endcap_Pt_Bin_[i]->Draw("histesame");
          }
      else if (n1==0 && n2!=0){
           h_New_Sig_GJet_FO_Quark_Endcap_Pt_Bin_[i]->GetXaxis()->SetRangeUser(0,0.04);
           h_New_Sig_GJet_FO_Quark_Endcap_Pt_Bin_[i]->GetYaxis()->SetRangeUser(0,1);
           h_New_Sig_GJet_FO_Quark_Endcap_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
           h_New_Sig_GJet_FO_Quark_Endcap_Pt_Bin_[i]->SetMarkerColor(4);//blue
           h_New_Sig_GJet_FO_Quark_Endcap_Pt_Bin_[i]->SetLineColor(4);
           h_New_Sig_GJet_FO_Quark_Endcap_Pt_Bin_[i]->Draw("histe");
          }
      else if (n1!=0 && n2==0){
           h_New_Sig_Tprime_FO_Quark_Endcap_Pt_Bin_[i]->GetXaxis()->SetRangeUser(0,0.04);
           h_New_Sig_Tprime_FO_Quark_Endcap_Pt_Bin_[i]->GetYaxis()->SetRangeUser(0,1);
           h_New_Sig_Tprime_FO_Quark_Endcap_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
           h_New_Sig_Tprime_FO_Quark_Endcap_Pt_Bin_[i]->SetMarkerColor(2);//red
           h_New_Sig_Tprime_FO_Quark_Endcap_Pt_Bin_[i]->SetLineColor(2);
           h_New_Sig_Tprime_FO_Quark_Endcap_Pt_Bin_[i]->Draw("histe");
          }
      else if (n1==0 && n2==0){
           cout<<"FO_Quark_Endcap Pt["<<i<<"]"<<endl;
           S_FO_Quark_Endcap_Pt_Bin_[i]=0;
          }





//////////////


       }//end loop i and end the superimpose

    /////////////////////////
    //                     //
    //  save in root file  //
    //                     //
    /////////////////////////


       TFile* f_result = new TFile("Result_of_2_sample_compare.root","RECREATE");
       f_result->cd();

   for (int i=0;i<5;i++){

//c_TIGHT_Gluon_Barrel_Pt_Bin_[i]->SetXTitle("SigmaIetaIeta");
c_TIGHT_Gluon_Barrel_Pt_Bin_[i]->Write();

c_TIGHT_Quark_Barrel_Pt_Bin_[i]->Write();
c_FO_Gluon_Barrel_Pt_Bin_[i]->Write();
c_FO_Quark_Barrel_Pt_Bin_[i]->Write();
c_TIGHT_Gluon_Endcap_Pt_Bin_[i]->Write();
c_TIGHT_Quark_Endcap_Pt_Bin_[i]->Write();
c_FO_Gluon_Endcap_Pt_Bin_[i]->Write();
c_FO_Quark_Endcap_Pt_Bin_[i]->Write();


/*
       if(S_TIGHT_Gluon_Barrel_Pt_Bin_[i]==1)  {c_TIGHT_Gluon_Barrel_Pt_Bin_[i]->Write();}
       if(S_TIGHT_Quark_Barrel_Pt_Bin_[i]==1)   {c_TIGHT_Quark_Barrel_Pt_Bin_[i]->Write();}
       if(S_FO_Gluon_Barrel_Pt_Bin_[i]==1 )  {c_FO_Gluon_Barrel_Pt_Bin_[i]->Write();}
       if(S_FO_Quark_Barrel_Pt_Bin_[i]==1 )  {c_FO_Quark_Barrel_Pt_Bin_[i]->Write();}
       if(S_TIGHT_Gluon_Endcap_Pt_Bin_[i]==1 )  {c_TIGHT_Gluon_Endcap_Pt_Bin_[i]->Write();}
       if(S_TIGHT_Quark_Endcap_Pt_Bin_[i]==1 )  {c_TIGHT_Quark_Endcap_Pt_Bin_[i]->Write();}
       if(S_FO_Gluon_Endcap_Pt_Bin_[i] ==1 ) {c_FO_Gluon_Endcap_Pt_Bin_[i]->Write();}
       if(S_FO_Quark_Endcap_Pt_Bin_[i]==1 )  {c_FO_Quark_Endcap_Pt_Bin_[i]->Write();}
*/


        }


    /////////////////////////
    //                     //
    //  print to pdf file  //
    //                     //
    /////////////////////////

for(int i=0;i<5;i++){

   if(i==0){c_TIGHT_Gluon_Barrel_Pt_Bin_[i]->Print("checkpdf_comv2.pdf(");}
//   else if(i==4){c_TIGHT_Quark_Barrel_Pt_Bin_[i]->Print("checkpdf_comv2.pdf)");} 
   else {c_TIGHT_Gluon_Barrel_Pt_Bin_[i]->Print("checkpdf_comv2.pdf");} 

}

for(int i=0;i<5;i++){
c_TIGHT_Quark_Barrel_Pt_Bin_[i]->Print("checkpdf_comv2.pdf");
}

for(int i=0;i<5;i++){
c_FO_Gluon_Barrel_Pt_Bin_[i]->Print("checkpdf_comv2.pdf");
}

for(int i=0;i<5;i++){
c_FO_Quark_Barrel_Pt_Bin_[i]->Print("checkpdf_comv2.pdf");
}

for(int i=0;i<5;i++){
c_TIGHT_Gluon_Endcap_Pt_Bin_[i]->Print("checkpdf_comv2.pdf");
}

for(int i=0;i<5;i++){
c_TIGHT_Quark_Endcap_Pt_Bin_[i]->Print("checkpdf_comv2.pdf");
}

for(int i=0;i<5;i++){
c_FO_Gluon_Endcap_Pt_Bin_[i]->Print("checkpdf_comv2.pdf");
}

for(int i=0;i<5;i++){

  if(i==4){c_FO_Quark_Endcap_Pt_Bin_[i]->Print("checkpdf_comv2.pdf)");}
  else {c_FO_Quark_Endcap_Pt_Bin_[i]->Print("checkpdf_comv2.pdf");}

}

















}
