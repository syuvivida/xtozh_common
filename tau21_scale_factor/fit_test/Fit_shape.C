#include "TH1.h"
#include "TFile.h"
#include "fit_chi2_err.C"
#include "TStyle.h"
#include "TSystem.h"
#include "TRandom.h"
#include "TCanvas.h"

//const int size=10;
//const int number=4;

void Fit_shape(){


// TFile *fGetData = new TFile("fake_data.root");
 TFile *fGetData = new TFile("fake_data_3_comp.root");

TH1F *h_Data       = (TH1F*)fGetData->Get("h_FakeData") ;
TH1F *h_Signal     = (TH1F*)fGetData->Get("h_had_top_mass_signal");
TH1F *h_Background1 = (TH1F*)fGetData->Get("h_had_top_mass_bk1");
TH1F *h_Background2 = (TH1F*)fGetData->Get("h_had_top_mass_bk2");

//h_Signal->Draw();

char name[200]={"test_3_components_fit"};
                           

   double sig, sigerr,bkgfrc1,bkgfrcerr1,chi2;
     fit_chi2_err(h_Data,h_Signal,h_Background1,h_Background2,"name",sig,sigerr,bkgfrc1,bkgfrcerr1,chi2);

      cout<< endl;
      cout << "  name: " << name ;

//      cout << "Fitted result = " << sig << " +- " << sigerr ;//<< endl;

      cout << "sig: " << sig << " sigerr " << sigerr <<endl;
      cout <<" bkgfrc1:"<< bkgfrc1 << " bkgfrcerr1:  " << bkgfrcerr1<<endl;

      cout << " chi2/dof= " << chi2 << endl;


/*
  TFile *fGetData = new TFile("FakesFromJetsResults_Data.root");

  TFile *fSignal = new TFile("FakesFromJetsResults_Signal.root");

  TFile *fBackground = new TFile("FakesFromJetsResults_Background.root");

/////////

TH1F *h_Data_inclusive_category_[8];//
TH1F *h_Signal_inclusive_category_[8];
TH1F *h_Background_inclusive_category_[8];

//int size=10;
//int number =4;

//char test[number][size]={"Yuhsiang","Marco","Eiko","Susie"};
//char test[4][10]={"Yuhsiang","Marco","Eiko","Susie"};

//string test[4]={"Yuhsiang","Marco","Eiko","Susie"};

//test[0]= "Yu-Hsiang";


//char words[2][2][20]={{"Yuhsiang","Marco"},{"Eiko","Susie"}};



//for(int i=0;i<4;i++){
//cout<<"test[i]"<<test[i] <<endl;

//}


char category_name[8][200]={"Inclusive_Barrel_Sigma_Ieta_Ieta_TIGHT_Quark",
                            "Inclusive_Barrel_Sigma_Ieta_Ieta_TIGHT_Gluon",
                            "Inclusive_Barrel_Sigma_Ieta_Ieta_FO_Quark",
                            "Inclusive_Barrel_Sigma_Ieta_Ieta_FO_Gluon",
                            "Inclusive_Endcap_Sigma_Ieta_Ieta_TIGHT_Quark",
                            "Inclusive_Endcap_Sigma_Ieta_Ieta_TIGHT_Gluon",
                            "Inclusive_Endcap_Sigma_Ieta_Ieta_FO_Quark",
                            "Inclusive_Endcap_Sigma_Ieta_Ieta_FO_Gluon"};


for(int i=0;i<8;i++){

h_Data_inclusive_category_[i]       = (TH1F*)fGetData->Get(category_name[i]);
h_Signal_inclusive_category_[i]     = (TH1F*)fSignal->Get(category_name[i]);
h_Background_inclusive_category_[i] = (TH1F*)fBackground->Get(category_name[i]);

}


// Once I have defined the name and get the histo from root file,I can use them






//TH1F  *h_Data_TIGHT_Quark_Barrel = (TH1F*)fGetData->Get("Inclusive_Barrel_Sigma_Ieta_Ieta_TIGHT_Quark");
//TH1F  *h_Signal_TIGHT_Quark_Barrel = (TH1F*)fSignal->Get("Inclusive_Barrel_Sigma_Ieta_Ieta_TIGHT_Quark");
//TH1F  *h_Background_TIGHT_Quark_Barrel = (TH1F*)fBackground->Get("Inclusive_Barrel_Sigma_Ieta_Ieta_TIGHT_Quark");

/////////

  for(int i=0;i<8;i++){
//      cout<< endl;
//      cout << "  category: " << category_name[i] <<  endl;
//      cout<< endl;

      double sig, sigerr,chi2;
     fit_chi2_err(h_Data_inclusive_category_[i],h_Signal_inclusive_category_[i],h_Background_inclusive_category_[i],category_name[i],sig,sigerr,chi2);

      cout<< endl;
      cout << "  category: " << category_name[i] ;//<<  endl;
      //cout<< endl;

      cout << "Fitted result = " << sig << " +- " << sigerr ;//<< endl;
      cout << " chi2/dof= " << chi2 << endl;



  }

////////////////  fit data in categories and Pt bins

  TFile *fGetData_Pt_Bins = new TFile("Data_8_categories_5_Pt_bins.root");

  TFile *fSignal_Pt_Bins = new TFile("Signal_8_categories_5_Pt_bins.root");

  TFile *fBackground_Pt_Bins = new TFile("Background_8_categories_5_Pt_bins.root");

///////////////

 TH1F *h_Data_inclusive_category_Pt_bins[8][5];// 8 categories and 5 Pt bins
 TH1F *h_Signal_inclusive_category_Pt_bins[8][5];
 TH1F *h_Background_inclusive_category_Pt_bins[8][5];

///////////////

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

/////////////

for(int i=0;i<8;i++){//category
  for(int j=0;j<5;j++){//Pt bins
 
h_Data_inclusive_category_Pt_bins[i][j]       = (TH1F*)fGetData_Pt_Bins ->Get(category_Pt_name[i][j]);
h_Signal_inclusive_category_Pt_bins[i][j]     = (TH1F*)fSignal_Pt_Bins ->Get(category_Pt_name[i][j]);
h_Background_inclusive_category_Pt_bins[i][j] = (TH1F*)fBackground_Pt_Bins ->Get(category_Pt_name[i][j]);

      }
}

for(int i=0;i<8;i++){//category
  for(int j=1;j<5;j++){//Pt bins

      double sig, sigerr,chi2;
     fit_chi2_err(h_Data_inclusive_category_Pt_bins[i][j],h_Signal_inclusive_category_Pt_bins[i][j],h_Background_inclusive_category_Pt_bins[i][j],category_Pt_name[i][j],sig,sigerr,chi2);

      cout<< endl;
      cout << "  category_Pt_name[i][j]: " << category_Pt_name[i][j] ;//<<  endl;
      //cout<< endl;

      cout << "Fitted result = " << sig << " +- " << sigerr ;//<< endl;
      cout << " chi2/dof= " << chi2 << endl;


      }
}




*/














}
