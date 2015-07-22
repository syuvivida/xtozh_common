#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <TH1D.h>
#include <TH1F.h>
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

using namespace std;

void gen_leptonic_Bjet(TreeReader &data, vector<Int_t> *gen_leptonic_Bjet_index
		      ){

    Int_t    nGenPar     = data.GetInt("nGenPar");
    Int_t*   genParId    = data.GetPtrInt("genParId");
    Int_t*   genMomParId = data.GetPtrInt("genMomParId");
    Int_t*   genMo1      = data.GetPtrInt("genMo1");
    Int_t*   genDa1      = data.GetPtrInt("genDa1");
    Int_t*   genDa2      = data.GetPtrInt("genDa2");
    Int_t*   genParSt    = data.GetPtrInt("genParSt");    
    Float_t* genParE     = data.GetPtrFloat("genParE");
    Float_t* genParPt    = data.GetPtrFloat("genParPt");
    Float_t* genParEta   = data.GetPtrFloat("genParEta");
    Float_t* genParPhi   = data.GetPtrFloat("genParPhi");

  //-----------------------------------------------------------------------------------//
  // find leptonic W whose decay products are Muon and Neutrino, again I foucus on Muon channel

 vector<Int_t> gen_lep_W_index;
 vector<Int_t> gen_lep_mu_index;
 vector<Int_t> gen_lep_nu_index;

 int lep_W_index = -999;

 for(Int_t i = 0; i < nGenPar; i++){
    
     // find W 
     if (genParId[i]!=24 && genParId[i]!= -24){continue;}

     // require W <- top
     if ( genParId[ genMo1[ i ] ] != 6 && genParId[ genMo1[ i ] ] != -6 ){continue;}

     // find muon <- W 
     if ( (genParId[ genDa1[ i ] ] != 13) && (genParId[ genDa1[ i ] ] != -13) &&
          (genParId[ genDa2[ i ] ] != 13) && (genParId[ genDa2[ i ] ] != -13) ){continue;}

     //cout<<"find W"<<endl;

     lep_W_index = i ;

     gen_lep_W_index.push_back(lep_W_index);
 }

/* if(gen_lep_W_index->size()>0){ 
   for(int i=0;i<gen_lep_W_index->size();i++)
   {cout<<"gen_lep_W_index->at(i): "<<gen_lep_W_index->at(i)<<endl;}
 }*/

  //-----------------------------------------------------------------------------------//
  // find B-jet using such W found in above

   for(int j=0;j<gen_lep_W_index.size();j++){// W index loop

   	int top_index = genMo1[ gen_lep_W_index[j] ];
	int Bjet_index;

//	cout<<"top_index:"<< top_index <<endl;

	//find B-jet
    	if( (genParId[genDa1[ top_index ]] == 5) || (genParId[genDa1[ top_index ]] == -5) )
		{Bjet_index = genDa1[ top_index ]; }
        if( (genParId[genDa2[ top_index ]] == 5) || (genParId[genDa2[ top_index ]] == -5) )
                {Bjet_index = genDa2[ top_index ]; }

//	cout<<"j: "<<j<<endl;
//	cout<<"Bjet_index: "<<Bjet_index<<endl;
//	cout<<"genParId[Bjet_index]: "<<genParId[Bjet_index]<<endl;
//	cout<<"genParSt[Bjet_index]: "<<genParSt[Bjet_index]<<endl;

//	int dauther_1_index = genDa1[ Bjet_index ];
//        int dauther_2_index = genDa2[ Bjet_index ];	
//	cout<<"genParId[dauther_1_index]: "<<genParId[dauther_1_index]<<endl;
//        cout<<"genParSt[dauther_1_index]: "<<genParSt[dauther_1_index]<<endl;
//        cout<<"genParId[dauther_2_index]: "<<genParId[dauther_2_index]<<endl;
//        cout<<"genParSt[dauther_2_index]: "<<genParSt[dauther_2_index]<<endl;

        //cout<<"genParId[]: "<<genParId[]<<endl;
        //cout<<"genParSt[]: "<<genParSt[]<<endl;

        gen_leptonic_Bjet_index->push_back(Bjet_index);

   }//end W index loop


  //-----------------------------------------------------------------------------------//
  // find Muon of status=1 and whose ancestor mother is the W found in above

/*
   int Muon_index = -999;


   for(int j=0;j<gen_lep_W_index->size();j++){// W index loop

        for(Int_t i = 0; i < nGenPar; i++){//Muon index loop
    
     		// find Muon 
     		if (genParId[i]!=13 && genParId[i]!= -13){continue;}

     		// status = 1 
     		if (genParSt[i]!=1){continue;}

                // trace back can find W index
        	int generation=-1;//which generation you find the W index 
        	int temp_index;
        	temp_index = genMo1[i];       

        	for(int k=0;k<8;k++)//trace its ancestor up to 8 generations
        	{       //cout<<"k:"<<k<<endl;
	           	if (temp_index == gen_lep_W_index->at(j)){
				generation=k+1;
				//k=9;//end loop
  				break;//end loop avoid segmentation violation error
			}
                        //cout<<"genParSt[temp_index]:"<<genParSt[temp_index]<<endl;
                        if(genParSt[temp_index]!=1&&genParSt[temp_index]!=2&&genParSt[temp_index]!=3)
				{break;}//end loop avoid segmentation violation error
           		int temp_mom_index = genMo1[temp_index];
           		temp_index = temp_mom_index;

        	}
        	if (generation == -1){continue;}
        	//cout<<"in which generation you find the W index: "<< generation<<endl;



      //  	cout<<"find Muon"<<endl;
        	Muon_index = i;
        	gen_lep_mu_index->push_back(Muon_index);
 
     		}// i Muon index loop

    	}// j W index loop , for 2 W indices, there are exact 2 muon corresponded


  
//   for(int i=0;i<gen_lep_mu_index->size();i++)
//   {cout<<"gen_lep_mu_index->at(i): "<<gen_lep_mu_index->at(i)<<endl;}
      

  //-----------------------------------------------------------------------------------//
  // find Neutrino of status=1 and whose ancestor mother is the W found in above

  int Neutrino_index = -999;


   for(int j=0;j<gen_lep_W_index->size();j++){// W index loop

        for(Int_t i = 0; i < nGenPar; i++){//Muon index loop

                // find Neutrino 
                if (genParId[i]!=14 && genParId[i]!= -14){continue;}

                // status = 1 
                if (genParSt[i]!=1){continue;}

                // trace back can find W index
                int generation=-1;//which generation you find the W index 
                int temp_index;
                temp_index = genMo1[i];

                for(int k=0;k<8;k++)//trace its ancestor up to 8 generations
                {       //cout<<"k:"<<k<<endl;
                        if (temp_index == gen_lep_W_index->at(j)){
                                generation=k+1;
                                break;//end loop avoid segmentation violation error
                        }
                        if(genParSt[temp_index]!=1&&genParSt[temp_index]!=2&&genParSt[temp_index]!=3)
                                {break;}//end loop avoid segmentation violation error
                        int temp_mom_index = genMo1[temp_index];
                        temp_index = temp_mom_index;

                }
                if (generation == -1){continue;}

        //        cout<<"find Neutrino"<<endl;
                Neutrino_index = i;
                gen_lep_nu_index->push_back(Neutrino_index);

                }// i Muon index loop

        }// j W index loop , for 2 W indices, there are exact 2 muon corresponded



//   for(int i=0;i<gen_lep_nu_index->size();i++)
//   {cout<<"gen_lep_nu_index->at(i): "<<gen_lep_nu_index->at(i)<<endl;}

*/

  //-----------------------------------------------------------------------------------//



}
