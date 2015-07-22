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

int EventSelectionMuonChannel(TreeReader &data,
  vector<Int_t> *Tight_Muon_index, vector<Int_t> *Loose_Electron_index ,
  vector<Int_t> *Loose_CA8Jet_index, vector<Int_t> *Muon_pass_index,
  vector<Int_t> *leading_and_second_CA8Jet_index,
  vector<Int_t> *Btagged_CA8Jet_index,
  vector<Int_t> *CA8Jet_pass_index ){

    Int_t    nMu          = data.GetInt("nMu");
    Float_t* muPt         = data.GetPtrFloat("muPt");
    Float_t* muEta        = data.GetPtrFloat("muEta");
    Float_t* muCorrPfIso  = data.GetPtrFloat("muCorrPfIso");
    Float_t* muPhi        = data.GetPtrFloat("muPhi");
    Float_t* muM          = data.GetPtrFloat("muM");

    Int_t    nEle         = data.GetInt("nEle");
    Float_t* elePt        = data.GetPtrFloat("elePt");
    Float_t* eleScEta     = data.GetPtrFloat("eleScEta");
    Float_t* eleEta    = data.GetPtrFloat("eleEta");
    Float_t* elePhi    = data.GetPtrFloat("elePhi");
    Float_t* eleM      = data.GetPtrFloat("eleM");

    Int_t    CA8nJet      = data.GetInt("CA8nJet");
    Float_t* CA8jetPt     = data.GetPtrFloat("CA8jetPt");
    Float_t* CA8jetCSV    = data.GetPtrFloat("CA8jetCSV");
    Float_t* CA8jetEta    = data.GetPtrFloat("CA8jetEta");
    Float_t* CA8jetPhi    = data.GetPtrFloat("CA8jetPhi");
    Float_t* CA8jetEn     = data.GetPtrFloat("CA8jetEn");
    Float_t* CA8jetMass   = data.GetPtrFloat("CA8jetMass");
    Float_t* CA8jetPrunedMass = data.GetPtrFloat("CA8jetPrunedMass");

    Float_t  pfMetCorrPt  = data.GetFloat("pfMetCorrPt");


  //-----------------------------------------------------------------------------------//      in event selection the return -1 is fail, return 2 is pass 

  // determine which cut to turn on  
  int cuts_flag[7] = { 1 , 1 , 1 , 1 , 1 , 1 , 1 };// 1 for turn on , -1 for turn off
//            cut No:  1   2   3   4   5   6   7


  //-----------------------------------------------------------------------------------//
  // Muon pT>45, |Eta|<2.1, iso-Muon and the # of iso-Muon >= 1

if(cuts_flag[0] == 1){

    for (int i=0;i<Tight_Muon_index->size();i++){

        if ( muPt[ Tight_Muon_index->at(i) ] < 45  ){continue;}
        if ( muEta[ Tight_Muon_index->at(i) ] > 2.1  ){continue;}
        if ( ( muCorrPfIso[ Tight_Muon_index->at(i) ]/muPt[ Tight_Muon_index->at(i) ] ) > 0.05  ){continue;}
        Muon_pass_index->push_back( Tight_Muon_index->at(i) );
    }

    if ( Muon_pass_index->size() < 1 ){return -1;}
}

  //-----------------------------------------------------------------------------------//
  // reject addtional Muon with pT>10, |Eta|<2.1

if(cuts_flag[1] == 1){

    int local_counter1 =0;
 
    for (int i=0; i< Tight_Muon_index->size();i++){
        for (int j=0; j< Muon_pass_index->size();j++){
            if ( Tight_Muon_index->at(i) != Muon_pass_index->at(j) ){
                if( (muPt[ Tight_Muon_index->at(i) ] > 10) && (fabs( muEta[ Tight_Muon_index->at(i)]) < 2.1) )
                {local_counter1 = local_counter1 + 1;}                    
            }
        }    
    }
    
    if ( local_counter1 > 0 ){return -1;}

}

  //-----------------------------------------------------------------------------------//
  // reject addtional Electron with pT>12, |Eta|<2.1

if(cuts_flag[2] == 1){

    int local_counter2 =0;

    for (int i=0; i< Loose_Electron_index->size();i++){
                if( (elePt[ Loose_Electron_index->at(i) ] > 12) && (fabs( eleScEta[ Loose_Electron_index->at(i)]) < 2.1) )
                {local_counter2 = local_counter2 + 1;}
            }

    if ( local_counter2 > 0 ){return -1;}

}

  //-----------------------------------------------------------------------------------//
  // remove jets overlapped with lepton
  // find the jet which is not overlapped with lepton and save such jet to CA8Jet_pass_index

//   cout<<"this event    ----------------------------------------------"<<endl;

   TLorentzVector jet;//CA8jet

   //tag jet overlapped with lepton
//   vector<Int_t> overlapped_jet_index;
   for (int j=0;j<Loose_CA8Jet_index->size();j++){// Jet

//		cout<<"j: "<<j<<endl;
//                cout<<"Loose_CA8Jet_index->at(j): "<<Loose_CA8Jet_index->at(j)<<endl;
                jet.SetPtEtaPhiM(CA8jetPt[Loose_CA8Jet_index->at(j)],CA8jetEta[Loose_CA8Jet_index->at(j)],
                                 CA8jetPhi[Loose_CA8Jet_index->at(j)],CA8jetMass[Loose_CA8Jet_index->at(j)]);

                int ele_flag=1;
                int mu_flag=1;

                //no overlapped with ele 
                for(int e_index=0; e_index < Loose_Electron_index->size();e_index++)
                     {TLorentzVector loose_ele;
//		     cout<<"e_index: "<<e_index<<endl;
                     loose_ele.SetPtEtaPhiM(elePt[Loose_Electron_index->at(e_index)],eleEta[Loose_Electron_index->at(e_index)],elePhi[Loose_Electron_index->at(e_index)],eleM[Loose_Electron_index->at(e_index)]);
//                     cout<<"jet.DeltaR(loose_ele): "<<jet.DeltaR(loose_ele)<<endl;
                     if( jet.DeltaR(loose_ele) < 0.8 )
                         {ele_flag=-1;break;}
                     }
                //no overlapped with mu
                for(int mu_index=0; mu_index < Tight_Muon_index->size();mu_index++)
                     {TLorentzVector tight_mu;
//		     cout<<"mu_index: "<<mu_index<<endl;
                     tight_mu.SetPtEtaPhiM(muPt[Tight_Muon_index->at(mu_index)],muEta[Tight_Muon_index->at(mu_index)],muPhi[Tight_Muon_index->at(mu_index)],muM[Tight_Muon_index->at(mu_index)]);
//                     cout<<"jet.DeltaR(tight_mu): "<<jet.DeltaR(tight_mu)<<endl;
                     if( jet.DeltaR(tight_mu) < 0.8 )
                         {mu_flag=-1;break;}
                     }

                if( (ele_flag==1) && (mu_flag==1) ){CA8Jet_pass_index->push_back(Loose_CA8Jet_index->at(j));}
   }//end loop j

/*
if(CA8Jet_pass_index->size() > 0){
	for(int i=0;i<CA8Jet_pass_index->size();i++)
{cout<<"CA8Jet_pass_index->at(i): "<<CA8Jet_pass_index->at(i)<<endl;}
}
*/

  //-----------------------------------------------------------------------------------//
  // at least 2 CA8 jets (jets with no overlapping to lepton )

//    if ( Loose_CA8Jet_index->size() < 2 ){return -1;}   

if(cuts_flag[3] == 1){

    if ( CA8Jet_pass_index->size() < 2 ){return -1;}

}

  //-----------------------------------------------------------------------------------//
  // leading jet pT>200 and pruned mass in [60,100], second jet pT>30, use jets with no overlapping to lepton

if(cuts_flag[4] == 1){

    // leading jet
    float leading_CA8Jet_pT = -999 ;
    int leading_CA8Jet_index = -1 ;

    // in all jets that is not overlapped with lepton and prunemass in [60,100], to find the one with largest pT
    for (int i=0; i < CA8Jet_pass_index->size();i++){
//		cout<<"CA8Jet_pass_index->at(i): "<<CA8Jet_pass_index->at(i)<<endl;
//		cout<<"CA8jetPrunedMass[ CA8Jet_pass_index->at(i)]: "<<CA8jetPrunedMass[ CA8Jet_pass_index->at(i)]<<endl;
//		cout<<"CA8jetPt[ CA8Jet_pass_index->at(i)]: "<<CA8jetPt[ CA8Jet_pass_index->at(i)]<<endl;
		if( CA8jetPrunedMass[ CA8Jet_pass_index->at(i)]<60 || CA8jetPrunedMass[ CA8Jet_pass_index->at(i)]>100 ){continue;}
                if( CA8jetPt[ CA8Jet_pass_index->at(i) ] > leading_CA8Jet_pT )
                        { leading_CA8Jet_pT = CA8jetPt[ CA8Jet_pass_index->at(i) ];
                          leading_CA8Jet_index = CA8Jet_pass_index->at(i);
                        }
    }
//    cout<<"leading_CA8Jet_index: "<<leading_CA8Jet_index<<endl;
//    cout<<" leading jet pT: "<< CA8jetPt[ leading_CA8Jet_index ]<<endl; 
    if(leading_CA8Jet_pT>200){
	leading_and_second_CA8Jet_index->push_back(leading_CA8Jet_index);
    }  
    else{return -1;}

    // second jet
    float second_CA8Jet_pT = -999 ;
    int second_CA8Jet_index = -1 ;
    
    for (int i=0; i < CA8Jet_pass_index->size();i++){
            if( CA8Jet_pass_index->at(i) == leading_CA8Jet_index ){continue;}
//            cout<<"CA8Jet_pass_index->at(i): "<<CA8Jet_pass_index->at(i)<<endl;
//            cout<<"CA8jetPt[ CA8Jet_pass_index->at(i)]: "<<CA8jetPt[ CA8Jet_pass_index->at(i)]<<endl;

                if( CA8jetPt[ CA8Jet_pass_index->at(i) ] > second_CA8Jet_pT )
                        { second_CA8Jet_pT = CA8jetPt[ CA8Jet_pass_index->at(i) ];
                          second_CA8Jet_index = CA8Jet_pass_index->at(i);
                        }
    }
//    cout<<"second_CA8Jet_index: "<<second_CA8Jet_index<<endl;
//    cout<<" second jet pT: "<< CA8jetPt[ second_CA8Jet_index ]<<endl;
    if(second_CA8Jet_pT>30){
        leading_and_second_CA8Jet_index->push_back(second_CA8Jet_index);
    }
    else{return -1;}


}

  //-----------------------------------------------------------------------------------//
  // at least 1 b-tagged jet, CA8Jet_pass_index

if(cuts_flag[5] == 1){

    int local_counter3 =0;

    // loose 0.244 , medium 0.679 , tight 0.898  
    double b_tagging_value[3] = {0.244, 0.679, 0.898};
    int b_tagging_level = 0;

/*    for (int i=0; i < CA8Jet_pass_index->size();i++){
            
                if( CA8jetCSV[ CA8Jet_pass_index->at(i) ] > b_tagging_value[b_tagging_level] )
                        { local_counter3 = local_counter3 + 1 ;
                          Btagged_CA8Jet_index->
                                       push_back( CA8Jet_pass_index->at(i) );
                        }
    }
*/

    for (int i=0; i < Loose_CA8Jet_index->size();i++){
            
                if( CA8jetCSV[ Loose_CA8Jet_index->at(i) ] > b_tagging_value[b_tagging_level] )
                        { local_counter3 = local_counter3 + 1 ;
                          Btagged_CA8Jet_index->
                                       push_back( Loose_CA8Jet_index->at(i) );
			}
    }

    if ( local_counter3  < 1 ){return -1;}

}

  //-----------------------------------------------------------------------------------//
  // Missing Et>20

if(cuts_flag[6] == 1){

    if ( pfMetCorrPt  < 20 ){return -1;}

}

  //-----------------------------------------------------------------------------------//
  //

  // if an event pass all cuts and go here, then this event will send back 2 and be accepted 
  return 2;

}
