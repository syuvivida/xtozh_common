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

void gen_lepW_and_Mu_Nu(TreeReader &data, vector<Int_t> *gen_lep_W_index,
					  vector<Int_t> *gen_lep_nu_index, 
					  vector<Int_t> *gen_lep_mu_index 
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
 // find leptonic W and its' decay product Muon and Neutrino, again I foucus on Muon channel

 int lep_W_index;
 int Muon_index=-999;
 int Neutrino_index=-999;

 int dauther_index = -99;
 int dauther_id = -99;
 int dauther_st = -99;

 for(Int_t i = 0; i < nGenPar; i++){
    
     // find W 
     if (genParId[i]!=24 && genParId[i]!= -24){continue;}

     // require W <- top
     if ( genParId[ genMo1[ i ] ] != 6 && genParId[ genMo1[ i ] ] != -6 ){continue;}

     // find muon <- W 
     if ( (genParId[ genDa1[ i ] ] != 13) && (genParId[ genDa1[ i ] ] != -13) &&
          (genParId[ genDa2[ i ] ] != 13) && (genParId[ genDa2[ i ] ] != -13) ){continue;}

     cout<<"find W"<<endl;
//     cout<<"gen W index i: "<< i<<endl;
//     cout<<"genParId[i]: "<<  genParId[i] <<endl;
//     cout<<"mother id: "<<    genParId[ genMo1[ i ] ]<<endl;

//     cout<<"dauther 1 id: "<< genParId[ genDa1[i] ]<<endl;
//     cout<<"dauther 1 st: "<< genParSt[ genDa1[i] ] <<endl;

//     cout<<"dauther 2 id: "<< genParId[ genDa2[i] ]<<endl;
//     cout<<"dauther 2 st: "<< genParSt[ genDa2[i] ] <<endl;

/*
     int da1_index = genDa1[i];
     cout<<"dauther 1 index: "<<  da1_index <<endl;
     cout<<"dauther 1 id: "<< genParId[ da1_index ]<<endl;
     cout<<"dauther 1 st: "<< genParSt[ da1_index ] <<endl;
     int da11_index = genDa1[genDa1[i]] ;
     int da12_index = genDa2[genDa1[i]] ;
     cout<<"dauther 11 index: "<<  da11_index <<endl;
     cout<<"dauther 11 id: "<< genParId[ da11_index ]<<endl;
     cout<<"dauther 11 st: "<< genParSt[ da11_index ] <<endl;
//     cout<<"dauther 12 id: "<< genParId[ da12_index ]<<endl;   
//     cout<<"dauther 12 st: "<< genParSt[ da12_index ] <<endl;
     int da111_index = genDa1[genDa1[genDa1[i]]] ;
     cout<<"dauther 111 index: "<<  da111_index <<endl;
     cout<<"dauther 111 id: "<< genParId[ da111_index ]<<endl;   
     cout<<"dauther 111 st: "<< genParSt[ da111_index ] <<endl;

     int da2_index = genDa2[i];
     cout<<"dauther 2 index: "<<  da2_index <<endl;
     cout<<"dauther 2 id: "<< genParId[ da2_index ]<<endl;
     cout<<"dauther 2 st: "<< genParSt[ da2_index ] <<endl;
     int da21_index = genDa1[genDa2[i]] ;
     int da22_index = genDa2[genDa2[i]] ;
     cout<<"dauther 21 index: "<<  da21_index <<endl;
     cout<<"dauther 21 id: "<< genParId[ da21_index ]<<endl;   
     cout<<"dauther 21 st: "<< genParSt[ da21_index ] <<endl;
//     cout<<"dauther 22 id: "<< genParId[ da22_index ]<<endl;
//     cout<<"dauther 22 st: "<< genParSt[ da22_index ] <<endl;
     int da211_index = genDa1[genDa1[genDa2[i]]] ;
     cout<<"dauther 211 index: "<<  da211_index <<endl;
     cout<<"dauther 211 id: "<< genParId[ da211_index ]<<endl;
     cout<<"dauther 211 st: "<< genParSt[ da211_index ] <<endl;
*/

  // test finding finally not status 1 state
  if (genParId[ genDa1[i] ]==14 || genParId[ genDa1[i] ]==-14 ){

    int test_dau_index = genDa1[i];
    int test_dau_id = genParId[ test_dau_index ];
    int test_dau_st = genParSt[ test_dau_index ];
    int count_levels=0;
    int temp_index=0; int present_index=0;

    for(int k=0;k>-100;k++){
       if(test_dau_id!=14 && test_dau_id!=-14 ){
          cout<<"index: "<<test_dau_index<<" id: "<<test_dau_id<<" st: "<<test_dau_st<<endl;
          k=-101;//end loop
         cout<<"mother index: "<<present_index <<endl;
         cout<<"mother id: "<<genParId[present_index ]<<endl;
         cout<<"                           mother st: "<<genParSt[present_index ]<<endl;
         cout<<"find daughter again "<<endl;
         cout<<"dau index: "<<genDa1[present_index] <<endl;
         cout<<"dau id: "<<genParId[genDa1[present_index] ]<<endl;
         cout<<"dau st: "<<genParSt[genDa1[present_index] ]<<endl;



//          cout<<"mother st: "<<genParSt[ genMo1[test_dau_index] ]<<endl;
          //if(genParSt[ genMo1[test_dau_index] ]!=1)
          //{cout<<"index: "<<test_dau_index<<"id: "<<test_dau_id<<" st: "<<test_dau_st<<endl;}
       }
       else{
       present_index= test_dau_index;// to get mother index in if 
       temp_index = genDa1[test_dau_index]; 
       test_dau_id=0;test_dau_st=0;

       test_dau_index = temp_index;
       test_dau_id = genParId[ test_dau_index ];
       test_dau_st = genParSt[ test_dau_index ];
       count_levels = count_levels+1;
       }
    }
    cout<<"count_levels: "<<count_levels<<endl;
  }



     lep_W_index = i ;

/*
     // find status = 1 Muon, it need deal with infinite loop until find it 
     //Da1
     if((genParId[ genDa1[ i ] ] == 13) || (genParId[ genDa1[ i ] ] == -13)) {

     cout<<"start loop"<<endl;

cout<<"genParId[ genDa1[ i ] ]: "<<genParId[ genDa1[ i ] ]<<endl;
cout<<" genDa1[ i ] : "<< genDa1[ i ] <<endl;

          dauther_index = genDa1[ i ];
          dauther_id = genParId[ dauther_index ];
          dauther_st = genParSt[ dauther_index ];
 cout<<"dauther_index in stage 1-1:"<<dauther_index<<endl;

          for(int j=0;j>-100;j++){
             if( (dauther_st==1) &&
                 ( (dauther_id==13) || (dauther_id==-13) ) ){
 cout<<"dauther_index in stage 2-1:"<<dauther_index<<endl;
                 Muon_index = dauther_index; 
                 j = -200;//end infinite loop
             }
             else{
    cout<<"enter here,j: "<<j<<endl;

cout<<"dauther_index: "<<dauther_index <<endl;
cout<<"dauther_id: "<<dauther_id <<endl;
cout<<"dauther_st: "<<dauther_st <<endl;

                 int grand_dauther_index = genDa1[dauther_index] ;
                 dauther_index = grand_dauther_index;
                 dauther_id = genParId[ dauther_index ];
                 dauther_st = genParSt[ dauther_index ];
             }// continue loop

             if(j>5){j=-300;}//out of loop if try 20 times
          }//end j loop
     }//Da1

     //Da2
     if((genParId[ genDa2[ i ] ] == 13) || (genParId[ genDa2[ i ] ] == -13)) {
          

     cout<<"start loop"<<endl;

          dauther_index = genDa2[ i ];
          dauther_id = genParId[ dauther_index ];
          dauther_st = genParSt[ dauther_index ];
 cout<<"dauther_index in stage 1-2:"<<dauther_index<<endl;
          
          for(int j=0;j>-100;j++){
             if( (dauther_st==1) && 
                 ( (dauther_id==13) || (dauther_id==-13) ) ){   
 cout<<"dauther_index in stage 2-2:"<<dauther_index<<endl;
                 Muon_index = dauther_index;
                 j = -200;//end infinite loop
             }
             else{

    cout<<"enter here,j: "<<j<<endl;

cout<<"dauther_index: "<<dauther_index <<endl;
cout<<"dauther_id: "<<dauther_id <<endl;
cout<<"dauther_st: "<<dauther_st <<endl;

                 int grand_dauther_index = genDa1[dauther_index] ;
                 dauther_index = grand_dauther_index;
                 dauther_id = genParId[ dauther_index ];
                 dauther_st = genParSt[ dauther_index ];
             }// continue loop
             
             if(j>5){j=-300;}//out of loop if try 20 times
          }//end j loop
      }//Da2
*/

/*
     // find status = 1 Neutrino, it need deal with infinite loop until find it 
     //Da1
     if((genParId[ genDa1[ i ] ] = 14) || (genParId[ genDa1[ i ] ] = -14)) {

          dauther_index = genDa1[ i ];
          dauther_id = genParId[ dauther_index ];
          dauther_st = genParSt[ dauther_index ];

          for(int j=0;j<-100;j++){
             if( (dauther_st==1) &&
                 ( (dauther_id==14) || (dauther_id==-14) ) ){
                 Neutrino_index = dauther_index;
                 j = -200;//end infinite loop
             }
             else{
                 int grand_dauther_index = genDa1[dauther_index] ;
                 dauther_index = grand_dauther_index;
                 dauther_id = genParId[ dauther_index ];
                 dauther_st = genParSt[ dauther_index ];
             }// continue loop

             if(j>20){j=-300;}//out of loop if try 20 times
          }//end j loop
     }//Da1

     //Da2
     if((genParId[ genDa2[ i ] ] = 14) || (genParId[ genDa2[ i ] ] = -14)) {

          dauther_index = genDa2[ i ];
          dauther_id = genParId[ dauther_index ];
          dauther_st = genParSt[ dauther_index ];

          for(int j=0;j<-100;j++){
             if( (dauther_st==1) &&
                 ( (dauther_id==14) || (dauther_id==-14) ) ){
                 Neutrino_index = dauther_index;
                 j = -200;//end infinite loop
             }
             else{
                 int grand_dauther_index = genDa1[dauther_index] ;
                 dauther_index = grand_dauther_index;
                 dauther_id = genParId[ dauther_index ];
                 dauther_st = genParSt[ dauther_index ];
             }// continue loop

             if(j>20){j=-300;}//out of loop if try 20 times
          }//end j loop
     }//Da2
*/

//     cout<<"lep_W_index: "<< lep_W_index <<endl;
//     cout<<"genParId[lep_W_index]: "<<genParId[lep_W_index ]<<endl;
  
//     cout<<"Muon_index: "<<Muon_index<<endl;
//     cout<<"genParId[Muon_index]: "<<genParId[Muon_index ]<<endl;
//     cout<<"genParSt[Muon_index]: "<<genParSt[Muon_index ]<<endl;

//     cout<<"Neutrino_index: "<<Neutrino_index<<endl;
//     cout<<"genParId[Neutrino_index]: "<<genParId[Neutrino_index ]<<endl;
//     cout<<"genParSt[Neutrino_index]: "<<genParSt[Neutrino_index ]<<endl;


 } 



  //-----------------------------------------------------------------------------------//

  // finding muon neutrino <- W boson <- top quark 
  // new version to find status=1 neutrino

/*
  for(Int_t i = 0; i < nGenPar; i++){

     if (genParId[i]!=14 && genParId[i]!= -14){continue;}
     if (genParSt[i]!=1){continue;}

//     cout<<"gen paricle index i: "<< i<<endl;                             
//     cout<<"genParId[i]: "<<genParId[i] <<endl;
//     cout<<"genParSt[i]: "<<genParSt[i] <<endl;

     int mom_id = genMomParId[i]; 
     int mom_index = genMo1[i];
     int grandmom_index;
     int W_index=0;
     //set zero to avoid cannot find W and make error later to require W decay from top

     for(int j=0; j > -100; j++){// find W boson (mother of nu) index

//        cout<<"mon index i: "<< mom_index<<endl;
//        cout<<"mom Id: "<< mom_id<<endl;                    
//        cout<<"mom St: "<< genParSt[mom_index]<<endl;

        if(mom_id== 24 || mom_id== -24){

//           cout<<"find W boson when trace back the nu mother"<<endl;
           W_index = mom_index;
           j= -150 ;//make it go out of loop

        }
        else{

//           cout<<"in loop trace nu's mother"<<endl;
           grandmom_index = genMo1[ mom_index];
           mom_index = grandmom_index;
           mom_id = genParId[mom_index];
           
        }
        if(j>20){j=-200;}
        //to end the infinite loop if cannot find W after try 20 times

     } 

//     cout<<"check W find after out of loop?"<<endl;
//     cout<<"W_index: "<<W_index<<endl;
//     cout<<"gen id of W_index: "<<genParId[ W_index ]<<endl;
     
     if ( genParId[ genMo1[ W_index ] ] != 6 && genParId[ genMo1[ W_index ] ] != -6 ){continue;}// require W <- top 

//     cout<<"W's mother is top?"<<endl;
//     cout<<"genParId[ genMo1[ W_index ] ]: "<<genParId[ genMo1[ W_index ] ]<<endl;

//        cout<<"it is leptonic neutrino" <<endl;
//     cout<<"gen paricle index i: "<< i<<endl;                             
//     cout<<"genParId[i]: "<<genParId[i] <<endl;
//     cout<<"genParSt[i]: "<<genParSt[i] <<endl;

        // if it can go to this step, after require all requirement, then save in gen_leptonic_nu_index
        gen_leptonic_nu_index->push_back(i); 
     
  }
*/


  //-----------------------------------------------------------------------------------//
  // finding muon neutrino <- W boson <- top quark   

  // old version to find status=3 neutrino

/*
  for(Int_t i = 0; i < nGenPar; i++){
     if (genParId[i]!=14 && genParId[i]!= -14){continue;}

//     if (genParSt[i]!=3){continue;}
     // status=3 nu's mother is W, grandmother is top 

//     if (genMomParId[i]!=24 && genMomParId[i]!= -24){continue;}
     
//     if ( genParId[ genMo1[ genMo1[i] ] ] != 6 && genParId[ genMo1[ genMo1[i]] ] != -6 ){continue;} 

        cout<<"gen paricle index i: "<< i<<endl;
        cout<<"genParId[i]: "<<genParId[i] <<endl;
        cout<<"genParSt[i]: "<<genParSt[i] <<endl;
        cout<<"genMomParId[i]: "<<genMomParId[i] <<endl;
        cout<<"genMo1[i]: "<<genMo1[i] <<endl;
        cout<<"genMo1[ genMo1[i]]: "<<genMo1[ genMo1[i] ] <<endl;
        cout<<"genParId[ genMo1[ genMo1[i]] ]: "<<genParId[ genMo1[ genMo1[i]] ] <<endl;
//        cout<<"it is leptonic neutrino" <<endl;

        gen_leptonic_nu_index->push_back(i); 

     
  }
*/

  //-----------------------------------------------------------------------------------//



}
