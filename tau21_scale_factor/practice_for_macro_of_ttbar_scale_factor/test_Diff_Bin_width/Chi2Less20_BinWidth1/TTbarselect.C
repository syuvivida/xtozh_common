// clean in 2015.3.30

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH1F.h>
#include <TBox.h>
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
#include <TLegend.h>
#include "TStyle.h"
#include "interface/untuplizer.h"
#include "interface/ElectronLooseID.C"
#include "interface/MuonTightID.C"
#include "interface/CA8JetLooseID.C"
#include "interface/EventSelectionMuonChannel.C"
#include "interface/neutrino_pz.C"
#include "interface/gen_leptonic_nu.C"
#include "interface/MinChi2_lep.C"
#include "interface/gen_leptonic_Bjet.C"
#include "interface/MinChi2_lep_and_had.C"
#include "interface/MinChi2_lep_and_had_1stAND2ndTerm.C"
#include "interface/gen_hadronic_Wjet_Bjet.C"


using namespace std;

void ElectronLooseID(TreeReader &, vector<Int_t> *  );
void MuonTightID(TreeReader &, vector<Int_t> *  );
void CA8JetLooseID(TreeReader &, vector<Int_t> *  );
int EventSelectionMuonChannel(TreeReader &, vector<Int_t> *,
 vector<Int_t> *, vector<Int_t> *, vector<Int_t> *,  vector<Int_t> *,
 vector<Int_t> *, vector<Int_t> * );
int neutrino_pz(TreeReader &, vector<Int_t> *, vector<Float_t> *, vector<Float_t> *);
void gen_leptonic_nu(TreeReader &,vector<Int_t> *);
float MinChi2_lep(TreeReader &, int,int,int , vector<Float_t> *  );
void gen_leptonic_Bjet(TreeReader &,vector<Int_t> *);
float MinChi2_lep_and_had( TreeReader &, int, int, int, int, int, vector<Float_t> *);
void gen_hadronic_Wjet_Bjet(TreeReader &, vector<Int_t> *, vector<Int_t> *);
float MinChi2_lep_and_had_1stAND2ndTerm( TreeReader &, int, int, int, int, int, vector<Float_t> *, double& , double&);


double uncertainty_calculate( double , double );


//void ZPrimeMass(std::string inputFile){
void TTbarselect(){

int N_bins = 1000; // 100=>10 , 200=>5, 1000=>1, 

//  TreeReader data(inputFile.data());
//  TreeReader data("flattuple_12_1_pNo.root");
//  TreeReader data("combine_130_files.root");
//  TreeReader data("TTJets_MassiveBinDECAY_TuneZ2star_8TeV.root");
//  TreeReader data("/Users/index0192/crab_WJet3/filtered_files/WJet3_51_files.root");
//  TreeReader data("/Users/index0192/crab_TT1/results/filtered_files/TT1_filtered.root");


TChain *root = new TChain("tree");
//TChain *root = new TChain("tree/tree");
root->Add("/Users/index0192/crab_TT1/results/filtered_files/TT1_filtered.root");
//root->Add("TTJets_MassiveBinDECAY_TuneZ2star_8TeV_filtered.root");
//root->Add("/Users/index0192/crab_WJet3/filtered_files/WJet3_51_files.root");
//root->Add("/Users/index0192/WJet1_filtered_files/*.root");
//root->Add("/Users/index0192/crab_TT1/results/filtered_files/*.root");
//root->Add("/Users/index0192/crab_TT1/results/filtered_files/TT1_filtered.root");
//root->Add("/Users/index0192/crab_WJet3/filtered_files/*.root");
TreeReader data(root);

//  TreeReader data("flattuple_1.root");

  // Declare the histogram of reconstructed mass

  TH1D* h_reco_both_sides_lep_top_mass = new TH1D("h_reco_both_sides_lep_top_mass", " reco both sides lep top mass",N_bins , 0,1000 );
  TH1D* h_reco_both_sides_had_top_mass = new TH1D("h_reco_both_sides_had_top_mass", " reco both sides had top mass",N_bins , 0,1000 );

  //

  TH1D* h_had_top_mass_match_had_B = new TH1D("h_had_top_mass_match_had_B", " had top mass match had B",100 , 0,1000 );

  TH1D* h_had_top_mass_unmatch_had_B = new TH1D("h_had_top_mass_unmatch_had_B", " had top mass unmatch had B",100 , 0,1000 );

  TH1D* h_had_top_mass_match_had_W = new TH1D("h_had_top_mass_match_had_W", " had top mass match had W",100 , 0,1000 );

  TH1D* h_had_top_mass_unmatch_had_W = new TH1D("h_had_top_mass_unmatch_had_W", " had top mass unmatch had W",100 , 0,1000 );


  TH1D* h_had_top_mass_match_lep_B = new TH1D("h_had_top_mass_match_lep_B", " had top mass match lep B",100 , 0,1000 );

  TH1D* h_had_top_mass_unmatch_lep_B = new TH1D("h_had_top_mass_unmatch_lep_B", " had top mass unmatch lep B",100 , 0,1000 );

  TH1D* h_had_top_mass_match_lep_nu = new TH1D("h_had_top_mass_match_lep_nu", " had top mass match lep nu",100 , 0,1000 );

  TH1D* h_had_top_mass_unmatch_lep_nu = new TH1D("h_had_top_mass_unmatch_lep_nu", " had top mass unmatch lep nu",100 , 0,1000 );

  //signal and background shape

  TH1D* h_had_top_mass_signal = new TH1D("h_had_top_mass_signal", " had top mass signal",N_bins , 0,1000 );
  TH1D* h_had_top_mass_bk1 = new TH1D("h_had_top_mass_bk1", " had top mass bk1",N_bins , 0,1000 );
  TH1D* h_had_top_mass_bk2 = new TH1D("h_had_top_mass_bk2", " had top mass bk2",N_bins , 0,1000 );

  TH1D* h_lep_top_mass_signal = new TH1D("h_lep_top_mass_signal", " lep top mass signal",N_bins , 0,1000 );
  TH1D* h_lep_top_mass_bk1 = new TH1D("h_lep_top_mass_bk1", " lep top mass bk1",N_bins , 0,1000 );
  TH1D* h_lep_top_mass_bk2 = new TH1D("h_lep_top_mass_bk2", " lep top mass bk2",N_bins , 0,1000 );

  TH2D* h_chi2_first_term_and_second_term = new TH2D("h_chi2_first_term_and_second_term", "chi2 first term and second term",5000 , 0,5000, 5000,0,5000 );

int event_pass_counter=0;
double counter0=0;
double counter1=0;
double counter2=0;
double counter3=0;
double counter4=0;
double counter5=0;
double counter6=0;
double counter7=0;
double counter8=0;
double counter9=0;
double counter10=0;
double counter11=0;
double counter12=0;
double counter13=0;
double counter14=0;

int counter_bk2=0;
int counter_bk2_all_had=0;
int counter_bk2_all_lep=0;
int counter_bk2_semi_lep=0;

int counter_bk2_semi_lep_ele=0;
int counter_bk2_semi_lep_mu=0;
int counter_bk2_semi_lep_tau=0;

int counter_bk2_semi_lep_tau_had=0;
int counter_bk2_semi_lep_tau_ele=0;
int counter_bk2_semi_lep_tau_mu=0;

int flag_check = 0;

cout<< "total # of event: "<< data.GetEntriesFast() << endl;

//--------------------------------------------------------------------//

  // begin of event loop
  
  for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++){
//  for (Long64_t ev = 0; ev < 100000; ev++){
//  for (Long64_t ev = 0; ev < 500000; ev++){
//  for (Long64_t ev = 0; ev < 50000; ev++){
//  for (Long64_t ev = 0; ev < 10000; ev++){
//  for (Long64_t ev = 0; ev < 5000; ev++){

    if ( ev % 5000 == 0 )
      fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());

        if (  flag_check == 1) cout<<"check step 0 "<<endl;

    data.GetEntry(ev);
    

    Int_t    nGenPar   = data.GetInt("nGenPar"); 
    Int_t*   genParId  = data.GetPtrInt("genParId");
    Int_t*   genParSt  = data.GetPtrInt("genParSt");
    Float_t* genParPt  = data.GetPtrFloat("genParPt");
    Float_t* genParEta = data.GetPtrFloat("genParEta");
    Float_t* genParPhi = data.GetPtrFloat("genParPhi");
    Float_t* genParM   = data.GetPtrFloat("genParM");
    Float_t* genParE     = data.GetPtrFloat("genParE");
    Int_t*   genMomParId = data.GetPtrInt("genMomParId");
    Int_t*   genMo1      = data.GetPtrInt("genMo1");
    Int_t*   genMo2      = data.GetPtrInt("genMo2");
    Int_t*   genDa1      = data.GetPtrInt("genDa1");
    Int_t*   genDa2      = data.GetPtrInt("genDa2");

    Int_t    nEle      = data.GetInt("nEle");
    Float_t* elePt     = data.GetPtrFloat("elePt");
    Float_t* eleScEta  = data.GetPtrFloat("eleScEta");
    Float_t* eleSigIhIh= data.GetPtrFloat("eleSigIhIh");
    Float_t* eleEta    = data.GetPtrFloat("eleEta");
    Float_t* elePhi    = data.GetPtrFloat("elePhi");
    Float_t* eleM      = data.GetPtrFloat("eleM");

    Int_t    nMu          = data.GetInt("nMu");
    Float_t* muPt         = data.GetPtrFloat("muPt");
    Float_t* muEta        = data.GetPtrFloat("muEta");
    Float_t* muPhi        = data.GetPtrFloat("muPhi");
    Float_t* muM          = data.GetPtrFloat("muM");
    Int_t*   isGlobalMuon = data.GetPtrInt("isGlobalMuon");
    Int_t*   isTrackerMuon= data.GetPtrInt("isTrackerMuon");
    Int_t*   muTrkLayers  = data.GetPtrInt("muTrkLayers");
    Int_t*   muPixelHits  = data.GetPtrInt("muPixelHits");
    Int_t*   muHits       = data.GetPtrInt("muHits");
    Int_t*   muMatches    = data.GetPtrInt("muMatches");
    Float_t* mudxy        = data.GetPtrFloat("mudxy");
    Float_t* mudz         = data.GetPtrFloat("mudz");

    Int_t    CA8nJet      = data.GetInt("CA8nJet");
    Float_t* CA8jetPt     = data.GetPtrFloat("CA8jetPt");
    Float_t* CA8jetEta    = data.GetPtrFloat("CA8jetEta");
    Float_t* CA8jetPhi    = data.GetPtrFloat("CA8jetPhi");
    Float_t* CA8jetEn     = data.GetPtrFloat("CA8jetEn");
    Float_t* CA8jetMass   = data.GetPtrFloat("CA8jetMass");
    Float_t* CA8jetCEmEF  = data.GetPtrFloat("CA8jetCEmEF");
    Float_t* CA8jetCHadEF = data.GetPtrFloat("CA8jetCHadEF");
    Float_t* CA8jetNEmEF  = data.GetPtrFloat("CA8jetNEmEF");
    Float_t* CA8jetNHadEF = data.GetPtrFloat("CA8jetNHadEF");
    Float_t* CA8jetCMulti = data.GetPtrFloat("CA8jetCMulti");
    Float_t* CA8jetPrunedMass = data.GetPtrFloat("CA8jetPrunedMass");
    Float_t* CA8jetCSV    = data.GetPtrFloat("CA8jetCSV");

    Float_t  pfMetCorrPt  = data.GetFloat("pfMetCorrPt");
    Float_t  pfMetCorrPhi = data.GetFloat("pfMetCorrPhi");

    //-----------------------------------------------------------------------------------// gen particle ID, 

	if (flag_check == 2){
    cout<<"nGenPar: "<< nGenPar <<endl;
    cout<<"nEle: "<< nEle  <<endl;
    cout<<"nMu: "<< nMu <<endl;
    cout<<"CA8nJet: "<<CA8nJet<<endl;
	}

    //-----------------------------------------------------------------------------------// reco elePt, muPt, CA8jetPt, Met

     if (flag_check == 1)   cout<<"check step 1 "<<endl;
    //-----------------------------------------------------------------------------------//
    vector<Int_t> Loose_Electron_index;
    ElectronLooseID(data, &Loose_Electron_index );

    vector<Int_t> Tight_Muon_index;
    MuonTightID(data, &Tight_Muon_index );

    vector<Int_t> Loose_CA8Jet_index;
    CA8JetLooseID(data, &Loose_CA8Jet_index );


    //-----------------------------------------------------------------------------------//
    // event selection in muon channel

    vector<Int_t> Muon_pass_index;
    vector<Int_t> leading_and_second_CA8Jet_index;
    //remove jets overlapped with lepton, leading jet pT>200 and pruned_mass in mass region [60,100],second jet pT>30
    vector<Int_t> Btagged_CA8Jet_index;
    vector<Int_t> CA8Jet_pass_index;//remove jets overlapped with lepton 

    int flag1 = -2;// muon channel event selection flag


    flag1 = EventSelectionMuonChannel(data, &Tight_Muon_index,   		&Loose_Electron_index ,
					    &Loose_CA8Jet_index, 		&Muon_pass_index, 
					    &leading_and_second_CA8Jet_index,	&Btagged_CA8Jet_index, 
					    &CA8Jet_pass_index  );
    // flag1 = 2  for pass, and -2 and -1 for fail 


    // tell  CA8Jet_pass_index is B-tagged jet or not
    vector<Int_t> Btagged_flag;
	if(CA8Jet_pass_index.size()>0 && Btagged_CA8Jet_index.size()>0 ){

    		for(int i=0;i<CA8Jet_pass_index.size();i++){
			int temp_B_flag=-1;

			for(int j=0;j<Btagged_CA8Jet_index.size();j++){
		   		if(CA8Jet_pass_index[i] == Btagged_CA8Jet_index[j])
	      				{ temp_B_flag= 1 ;break;}
			}
			Btagged_flag.push_back(temp_B_flag);// -1 for no b-tagged and 1 for pass b-tagged   
    		}
    

	}


   //-----------------------------------------------------------------------------------//
   // calculate neutrino pz
   
   vector<Float_t> nu_pz;// neutrino pz 2 solutions   
   vector<Float_t> nu_eta;//neutrino eta of 2 solutions

   if (flag1==2){
      if (Muon_pass_index.size()==1){// present way only calculate nu pz in case of 1 muon 
        neutrino_pz(data, &Muon_pass_index, &nu_pz, &nu_eta);
      }
   }

   //-----------------------------------------------------------------------------------// 
   // select gen leptonic neutrino

   // note, we are search in muon channel
    vector<Int_t> gen_leptonic_nu_index;

    gen_leptonic_nu(data, &gen_leptonic_nu_index);

   //-----------------------------------------------------------------------------------// 
   // select gen leptonic b-jet

   // note, we are search in muon channel,i.e. that is B quark associate with muon decay from top
    vector<Int_t> gen_leptonic_Bjet_index;
    gen_leptonic_Bjet(data, &gen_leptonic_Bjet_index);

      if (flag_check == 1)   cout<<"check step 2 "<<endl;

   //-----------------------------------------------------------------------------------// 
   // select gen hadronic b-jet

   // note, we are search in muon channel
    vector<Int_t> gen_hadronic_Wjet_index;
    vector<Int_t> gen_hadronic_Bjet_index;

    gen_hadronic_Wjet_Bjet(data, &gen_hadronic_Wjet_index ,&gen_hadronic_Bjet_index);

   //-----------------------------------------------------------------------------------// 
   // select gen hadronic W-jet

   // note, we are search in muon channel
//    vector<Int_t> gen_leptonic_Bjet_index;
//    gen_leptonic_Bjet(data, &gen_leptonic_Bjet_index);


   //-----------------------------------------------------------------------------------//


   //-----------------------------------------------------------------------------------//
   // residue of reconstruct leptonic top

   TLorentzVector jet;//CA8jet

   float chi2;
   float final_min_chi2 = 9999;


        TLorentzVector gen_nu;
        TLorentzVector reco_nu0;//neutrino
        TLorentzVector reco_nu1;//neutrino

        long double deltaR0;
        long double deltaR1;
        long double deltaPz0;
        long double deltaPz1;
        int correct_nu_pz_index = -1;


        TLorentzVector gen_Bjet;
        TLorentzVector reco_Bjet;//B jet

      if (flag_check == 1)  cout<<"check step 3 "<<endl;

   //-----------------------------------------------------------------------------------//
   // reconstruct 2 top quarks of both sides in the same time

   TLorentzVector had_W_jet;
   TLorentzVector had_b_jet;
   TLorentzVector had_top;

   TLorentzVector lep_nu;
   TLorentzVector lep_mu;
   TLorentzVector lep_b_jet;
   TLorentzVector lep_top;

   int had_W_jet_index=-99;int chi2_had_W_jet_index=-99;
   int had_B_jet_index=-99;int chi2_had_B_jet_index=-99;
   int lep_B_jet_index=-99;int chi2_lep_B_jet_index=-99;
   int lep_mu_index=-99;   int chi2_lep_mu_index=-99;
   int lep_nu_index=-99;   int chi2_lep_nu_index=-99;

   int both_side_combination_pass_flag =-1 ;
   float init_chi2 = 99999;
   final_min_chi2 = init_chi2;// reset this temp chi2 before minimize
   double First_term_save = -9;double Second_term_save = -9;

  if (flag1==2 && nu_pz.size()!=0 ){//pass event selection and has nu pz solution


	//had W
//	had_W_jet_index = leading_and_second_CA8Jet_index[0]; // had W chosen by leading jet
    for (int m=0;m<CA8Jet_pass_index.size();m++){// had W Jet chosen by any jets in CA8Jet_pass_index
        had_W_jet_index = CA8Jet_pass_index[m];

	//had b jet
        for (int j=0;j<CA8Jet_pass_index.size();j++){// had B Jet
//            if(CA8Jet_pass_index[j]==leading_and_second_CA8Jet_index[0]){continue;}
            if(CA8Jet_pass_index[j]== had_W_jet_index){continue;}
            if(Btagged_flag[j]!=1 ){continue;}// b tagging
	    had_B_jet_index = CA8Jet_pass_index[j];

	//lep mu
          for (int i=0;i<Muon_pass_index.size();i++){// Muon
	      lep_mu_index = Muon_pass_index[i];
  
	//lep b jet
	    for (int k=0;k<CA8Jet_pass_index.size();k++){// Jet
//	        if(CA8Jet_pass_index[k]==leading_and_second_CA8Jet_index[0]){continue;}
                if(CA8Jet_pass_index[k]== had_W_jet_index){continue;}
		if(CA8Jet_pass_index[k] == had_B_jet_index){continue;}
		if(Btagged_flag[k]!=1 ){continue;}// b tagging
		lep_B_jet_index = CA8Jet_pass_index[k];

	//lep nu
              for (int l=0;l<nu_pz.size();l++ ){// eta from nu pz 2 solutions
		  lep_nu_index = l;

		// both_side_combination_pass_flag =1 ;

double First_term = -99 ;double Second_term = -99;


                   chi2 = MinChi2_lep_and_had_1stAND2ndTerm(	data,lep_mu_index,
                                                   		lep_B_jet_index,
                                                   		lep_nu_index,
                                                   		had_W_jet_index,
                                                   		had_B_jet_index,
                                                   		&nu_eta,
							        First_term,Second_term);


//cout<<"chi2: "<< chi2<<" final_min_chi2: "<<final_min_chi2<<endl;
		      if( chi2 > init_chi2 ){cout<<"chi2: "<<chi2 <<endl;}
                      if( chi2 < final_min_chi2 ){// choose min chi2

                                final_min_chi2 = chi2;

                                chi2_lep_mu_index = lep_mu_index;
                                chi2_lep_nu_index = lep_nu_index;
                                chi2_lep_B_jet_index = lep_B_jet_index;
				chi2_had_W_jet_index = had_W_jet_index;
				chi2_had_B_jet_index = had_B_jet_index;
				First_term_save = First_term;
				Second_term_save = Second_term;
                      }

	      }//end nu loop
	    }//end lep b loop
	  }//end lep mu loop
	}//end had b loop
        }//end had W loop

}// if flag1==2 && nu_pz.size()!=0

  if(final_min_chi2 < 20.0) // 3.0, 4.0, 5.0, 6.0, 7.0, 10.0, 20.0, no require 
//  if(final_min_chi2 < 6000) //i.e. no requirement on chi2 
	{	
	both_side_combination_pass_flag =1 ;
	h_chi2_first_term_and_second_term->Fill(First_term_save,Second_term_save);
	} 

   //-----------------------------------------------------------------------------------//

  //after choose min chi2 to plot the top mass
  if(both_side_combination_pass_flag == 1   ){
    

                had_W_jet.SetPtEtaPhiM(CA8jetPt[chi2_had_W_jet_index],CA8jetEta[chi2_had_W_jet_index],
                                       CA8jetPhi[chi2_had_W_jet_index],CA8jetMass[chi2_had_W_jet_index]);

                had_b_jet.SetPtEtaPhiM(CA8jetPt[chi2_had_B_jet_index],CA8jetEta[chi2_had_B_jet_index],
                                       CA8jetPhi[chi2_had_B_jet_index],CA8jetMass[chi2_had_B_jet_index]);

		had_top = had_W_jet +  had_b_jet ;

        	lep_b_jet.SetPtEtaPhiM(         CA8jetPt[chi2_lep_B_jet_index],
              	                  		CA8jetEta[chi2_lep_B_jet_index],
                                		CA8jetPhi[chi2_lep_B_jet_index],
                                		CA8jetMass[chi2_lep_B_jet_index]);


        	lep_mu.SetPtEtaPhiM(            muPt[chi2_lep_mu_index],
                                		muEta[chi2_lep_mu_index],
                                		muPhi[chi2_lep_mu_index],
                                		muM[chi2_lep_mu_index]);

        	lep_nu.SetPtEtaPhiM(            pfMetCorrPt,
                                		nu_eta[chi2_lep_nu_index],
                                		pfMetCorrPhi,
                                		0);

        	lep_top = lep_mu + lep_b_jet + lep_nu ;

        	h_reco_both_sides_lep_top_mass->Fill( lep_top.M() );
                h_reco_both_sides_had_top_mass->Fill( had_top.M() );


  }//end if combination_pass_flag == 1 

       if (flag_check == 1)  cout<<"check step 4 "<<endl;

   //-----------------------------------------------------------------------------------//

  // after choose min chi2 to check the neutrino correct rate of use chi2 method
  if( both_side_combination_pass_flag== 1){

        deltaR0 =-99;
        deltaR1 =-99;
        deltaPz0 =-99;
        deltaPz1 =-99;
        correct_nu_pz_index = -1;

        // require  only one gen-nu, i.e ttbar semi-leptonic decay
        if(  gen_leptonic_nu_index.size()==1 && gen_hadronic_Wjet_index.size()==1  )
        {

//             counter0 = counter0 + 1 ;//all event to compare gen_nu and reco_nu

             gen_nu.SetPtEtaPhiE(genParPt[ gen_leptonic_nu_index[0] ],
                                 genParEta[ gen_leptonic_nu_index[0] ],
                                 genParPhi[ gen_leptonic_nu_index[0] ],
                                 genParE[ gen_leptonic_nu_index[0] ] );

             reco_nu0.SetPtEtaPhiM(pfMetCorrPt,nu_eta[0],pfMetCorrPhi,0);
             reco_nu1.SetPtEtaPhiM(pfMetCorrPt,nu_eta[1],pfMetCorrPhi,0);

             deltaR0 = gen_nu.DeltaR( reco_nu0 );
             deltaR1 = gen_nu.DeltaR( reco_nu1 );

             deltaPz0 = fabs(gen_nu.Pz() - reco_nu0.Pz());
             deltaPz1 = fabs(gen_nu.Pz() - reco_nu1.Pz());


          if( deltaPz0 > deltaPz1 ){
              correct_nu_pz_index = 1;}
          else if( deltaPz0 < deltaPz1 ){
              correct_nu_pz_index = 0;}

          if (correct_nu_pz_index == chi2_lep_nu_index )//chi2 has correct choice 
          {counter1 = counter1 + 1 ;
          h_had_top_mass_match_lep_nu->Fill( had_top.M() );
          }
          else{
          h_had_top_mass_unmatch_lep_nu->Fill( had_top.M() );
          }




          counter0 = counter0 + 1 ;

        }// gen nu size == 1 if

  }// both_side_combination_pass_flag == 1 if

   //-----------------------------------------------------------------------------------//

  // after choose min chi2 to check the lep B-jet correct rate of use chi2 method
  if( both_side_combination_pass_flag == 1){

        deltaR0=-99;
        deltaPz0=-99;

        // require  only one gen-nu, i.e ttbar semi-leptonic decay
        if(  gen_leptonic_nu_index.size()==1 && gen_hadronic_Wjet_index.size()==1  )// require only one gen nu also require only one gen B quark
        {

//             counter0 = counter0 + 1 ;//all event to compare gen_nu and reco_nu

             gen_Bjet.SetPtEtaPhiE(genParPt[ gen_leptonic_Bjet_index[0] ],
                                 genParEta[ gen_leptonic_Bjet_index[0] ],
                                 genParPhi[ gen_leptonic_Bjet_index[0] ],
                                 genParE[ gen_leptonic_Bjet_index[0] ] );

             reco_Bjet.SetPtEtaPhiM(       CA8jetPt[chi2_lep_B_jet_index],
                                           CA8jetEta[chi2_lep_B_jet_index],
                                           CA8jetPhi[chi2_lep_B_jet_index],
                                           CA8jetMass[chi2_lep_B_jet_index]);


             deltaR0 = gen_Bjet.DeltaR( reco_Bjet );

             deltaPz0 = fabs(gen_Bjet.Pz() - reco_Bjet.Pz());

          counter4 = counter4 + 1 ;
         if( deltaR0 < 0.8 ){
           counter5 = counter5 + 1 ;;
          h_had_top_mass_match_lep_B->Fill( had_top.M() );
          }
          else{
          h_had_top_mass_unmatch_lep_B->Fill( had_top.M() );
          }




        }// gen nu size == 1 if

  }// both_side_combination_pass_flag == 1

   //-----------------------------------------------------------------------------------//

  // after choose min chi2 to check the had B-jet correct rate of use chi2 method
  if(both_side_combination_pass_flag == 1){

        deltaR0=-99;
        deltaPz0=-99;

        // require  exact one gen-nu and exact one had W, i.e ttbar semi-leptonic decay
        if(  gen_leptonic_nu_index.size()==1 && gen_hadronic_Wjet_index.size()==1  )
        {

//             counter0 = counter0 + 1 ;//all event to compare gen_nu and reco_nu

             gen_Bjet.SetPtEtaPhiE(genParPt[ gen_hadronic_Bjet_index[0] ],
                                 genParEta[ gen_hadronic_Bjet_index[0] ],
                                 genParPhi[ gen_hadronic_Bjet_index[0] ],
                                 genParE[ gen_hadronic_Bjet_index[0] ] );

             reco_Bjet.SetPtEtaPhiM(       CA8jetPt[chi2_had_B_jet_index],
                                           CA8jetEta[chi2_had_B_jet_index],
                                           CA8jetPhi[chi2_had_B_jet_index],
                                           CA8jetMass[chi2_had_B_jet_index]);


             deltaR0 = gen_Bjet.DeltaR( reco_Bjet );

             deltaPz0 = fabs(gen_Bjet.Pz() - reco_Bjet.Pz());

         counter6 = counter6 + 1 ;
         if( deltaR0 < 0.8 ){
           counter7 = counter7 + 1 ;;
	  h_had_top_mass_match_had_B->Fill( had_top.M() );
          }
	  else{
          h_had_top_mass_unmatch_had_B->Fill( had_top.M() );
	  }

      }//if gen_leptonic_nu_index.size()==1 && gen_hadronic_Wjet_index.size()==1
  }// both_side_combination_pass_flag == 1

//   TLorentzVector had_W_jet;
   TLorentzVector gen_W_jet;

   //-----------------------------------------------------------------------------------//

  // after choose min chi2 to check the had W-jet correct rate of use chi2 method
  if(both_side_combination_pass_flag == 1){

        deltaR0=-99;
        deltaPz0=-99;

        // require  exact one gen-nu and exact one had W, i.e ttbar semi-leptonic decay
        if(  gen_leptonic_nu_index.size()==1 && gen_hadronic_Wjet_index.size()==1  )
        {

//             counter0 = counter0 + 1 ;//all event to compare gen_nu and reco_nu

             gen_W_jet.SetPtEtaPhiE(genParPt[ gen_hadronic_Wjet_index[0] ],
                                    genParEta[ gen_hadronic_Wjet_index[0] ],
                                    genParPhi[ gen_hadronic_Wjet_index[0] ],
                                    genParE[ gen_hadronic_Wjet_index[0] ] );

             had_W_jet.SetPtEtaPhiM(       CA8jetPt[chi2_had_W_jet_index],
                                           CA8jetEta[chi2_had_W_jet_index],
                                           CA8jetPhi[chi2_had_W_jet_index],
                                           CA8jetMass[chi2_had_W_jet_index]);


             deltaR0 = gen_W_jet.DeltaR( had_W_jet );

             deltaPz0 = fabs(gen_W_jet.Pz() - had_W_jet.Pz());

         counter8 = counter8 + 1 ;
         if( deltaR0 < 0.8 ){
           counter9 = counter9 + 1 ;
          
          h_had_top_mass_match_had_W->Fill( had_top.M() );
          }
          else{
          h_had_top_mass_unmatch_had_W->Fill( had_top.M() );
          }



      }//if gen_leptonic_nu_index.size()==1 && gen_hadronic_Wjet_index.size()==1
  }// both_side_combination_pass_flag == 1


       if (flag_check == 1)   cout<<"check step 5 "<<endl;
   //-----------------------------------------------------------------------------------//

  TLorentzVector ele;  TLorentzVector gen_particle; TLorentzVector reco_object;



   //-----------------------------------------------------------------------------------//


int leading_jet_flag = -1;
int W_match_flag = -1;

// study W -> q q match to which CA8 jet in the case enter chi2-sorting and semi-leptonic 
  if( both_side_combination_pass_flag== 1 &&
        gen_leptonic_nu_index.size()==1 &&  gen_hadronic_Wjet_index.size()==1 
//	(gen_leptonic_nu_index.size()!=1 || gen_hadronic_Wjet_index.size()!=1) // this to study the bk2 shape 
	 ){

	// find had W in gen
        for(int j=0; j<nGenPar  ;j++){

                if(genParSt[j]!=3 ){continue;}
                if(genParId[j]!= 24 && genParId[j]!= -24){continue;}
                if(genParId[genMo1[j]]!= 6 && genParId[genMo1[j]]!= -6){continue;}
	        if ( 	(genParId[ genDa1[ j ] ] != 1) && (genParId[ genDa1[ j ] ] != -1) &&
          	     	(genParId[ genDa1[ j ] ] != 2) && (genParId[ genDa1[ j ] ] != -2) &&
          		(genParId[ genDa1[ j ] ] != 3) && (genParId[ genDa1[ j ] ] != -3) &&
          		(genParId[ genDa1[ j ] ] != 4) && (genParId[ genDa1[ j ] ] != -4) &&
          		(genParId[ genDa1[ j ] ] != 5) && (genParId[ genDa1[ j ] ] != -5) &&
          		(genParId[ genDa1[ j ] ] != 6) && (genParId[ genDa1[ j ] ] != -6) ){continue;}

		int gen_had_W_index = j;

                gen_particle.SetPtEtaPhiE(genParPt[ gen_had_W_index ],
                                          genParEta[ gen_had_W_index ],
                                          genParPhi[ gen_had_W_index ],
                                          genParE[ gen_had_W_index ] );

		int number_match_to_WmergedJet = 0;

		// CA8 pass jet
		for (int k=0;k<CA8Jet_pass_index.size();k++){

			reco_object.SetPtEtaPhiM(       CA8jetPt[CA8Jet_pass_index[k]],
                   			                CA8jetEta[CA8Jet_pass_index[k]],
                                        		CA8jetPhi[CA8Jet_pass_index[k]],
                                        		CA8jetMass[CA8Jet_pass_index[k]]);

			int da1_flag = -1; int da2_flag = -1;

			// match to W
			if ( reco_object.DeltaR(gen_particle) < 0.8 ){ 

				//match to da1 of W
				int daughter_index_of_W = genDa1[ gen_had_W_index ];
		                gen_particle.SetPtEtaPhiE(	genParPt[ daughter_index_of_W ],
                                          			genParEta[ daughter_index_of_W ],
                                          			genParPhi[ daughter_index_of_W ],
                                          			genParE[ daughter_index_of_W ] );

				if( reco_object.DeltaR(gen_particle) < 0.8 ){da1_flag = 1;}

				//match to da2 of W
                                daughter_index_of_W = genDa2[ gen_had_W_index ];
                                gen_particle.SetPtEtaPhiE(      genParPt[ daughter_index_of_W ],
                                                                genParEta[ daughter_index_of_W ],
                                                                genParPhi[ daughter_index_of_W ],
                                                                genParE[ daughter_index_of_W ] );

                                if( reco_object.DeltaR(gen_particle) < 0.8 ){da2_flag = 1;}

			}// end if match W 

			if(da1_flag==1 && da2_flag==1){
				number_match_to_WmergedJet = number_match_to_WmergedJet +1 ;// find a CA8 jet match to W-merged jet	
//				counter11 = counter11+1 ;/* break;*/

				if( CA8Jet_pass_index[k] == leading_and_second_CA8Jet_index[0]){
					leading_jet_flag = 1;
				}// match to leading jet
				
                                if( CA8Jet_pass_index[k] == chi2_had_W_jet_index ){
                                     W_match_flag  = 1;
                                }// match to W-jet choosen by chi2

			}
		}// end loop CA8Jet_pass_index
		if ( number_match_to_WmergedJet >=1){counter11 = counter11+1 ;}//
                if ( number_match_to_WmergedJet >=2){cout <<"2 CA8 jet match to W-merged jet"<<endl ;}//

		if ( leading_jet_flag == 1){counter12 = counter12+1 ;} // 


	}//end loop nGenPar


  }//end if 

   //-----------------------------------------------------------------------------------//


   //-----------------------------------------------------------------------------------//
   // count # of events study


   if(  flag1==2 
//	&&  both_side_combination_pass_flag== 1 //&& 
        //gen_leptonic_nu_index.size()==1 &&
        //gen_hadronic_Wjet_index.size()==1  
	)
	{ counter2 = counter2 +1; }

   if(  flag1==2 &&
        both_side_combination_pass_flag== 1 //&& 
//        && gen_leptonic_nu_index.size()==1 &&
//           gen_hadronic_Wjet_index.size()==1  
        )
        { counter3 = counter3 +1; }

   if(  flag1==2 &&
        both_side_combination_pass_flag== 1 //&& 
        && gen_leptonic_nu_index.size()==1 &&
           gen_hadronic_Wjet_index.size()==1  
        )
        { counter13 = counter13 +1; }// Evt+chi2+gen_semi_leptonic



//   if(  flag1==2 
//        )
//        { counter2 = counter2 +1; }

//   if(  flag1==2 
//        )
//        { counter3 = counter3 +1; }

   //-----------------------------------------------------------------------------------//
   // plot the shape of different siganl shape and background shape 


   int bk2_flag =0;

   if ( flag1==2
	&& both_side_combination_pass_flag== 1
//	&& gen_leptonic_nu_index.size()==1 && gen_hadronic_Wjet_index.size()==1
	)
   {
	if ( gen_leptonic_nu_index.size()==1 && gen_hadronic_Wjet_index.size()==1 ){
	//  if ( gen_leptonic_nu_index.size()!=1 || gen_hadronic_Wjet_index.size()!=1 ){ // this is for study bk2 shape

		// signal, 
//		if( leading_jet_flag == 1){ // the leading jet match to  W-merged jet in gen
                if( W_match_flag== 1){ // the W-jet chosen by chi2 match to  W-merged jet in gen
//			counter12 = counter12+1 ;

			h_had_top_mass_signal->Fill( had_top.M() );
                        h_lep_top_mass_signal->Fill( lep_top.M() );
		}

		// bkg1 
		else{
			h_had_top_mass_bk1->Fill( had_top.M() );
                        h_lep_top_mass_bk1->Fill( lep_top.M() );
		}

	}
	//  bkg2, fail semi-leptonic
	else{ 
                        h_had_top_mass_bk2->Fill( had_top.M() );
                        h_lep_top_mass_bk2->Fill( lep_top.M() );
			bk2_flag = 1;
	}

   }

   //-----------------------------------------------------------------------------------//


   //-----------------------------------------------------------------------------------//

  }   // end of event loop

       if (flag_check == 1)  cout<<"check step 6 "<<endl;

cout<<"counter2: "<<counter2<<" # of events passing Evt "<<endl;
cout<<"counter3: "<<counter3<<" # of events passing Evt + chi2 "<<endl;
cout<<"counter13: "<<counter13<<" # of events passing Evt + chi2 + gen_semi_leptonic"<<endl;

double uncertainty;


////////////
cout<<"counter0: "<<counter0<</*" # of all events used for check correct rate of min chi2"<<*/endl;
cout<<"counter1: "<<counter1<</*" # of correct events choosen by min chi2"<<*/endl;
uncertainty = uncertainty_calculate(counter1,counter0);
cout<<"lep nu correct rate counter1/counter0: "<<counter1/counter0
<<" +/- "<< uncertainty <<endl;

cout<<"counter4: "<<counter4<<""<<endl;
cout<<"counter5: "<<counter5<<""<<endl;
uncertainty = uncertainty_calculate(counter5,counter4);
cout<<"lep B jet correct rate counter5/counter4: "<<counter5/counter4
<<" +/- "<< uncertainty <<endl;

cout<<"counter6: "<<counter6<<""<<endl;
cout<<"counter7: "<<counter7<<""<<endl;
uncertainty = uncertainty_calculate(counter7,counter6);
cout<<"had B jet correct rate counter7/counter6: "<<counter7/counter6
<<" +/- "<< uncertainty <<endl;

cout<<"counter8: "<<counter8<<""<<endl;
cout<<"counter9: "<<counter9<<""<<endl;
uncertainty = uncertainty_calculate(counter9,counter8);
cout<<"had W jet correct rate counter9/counter8: "<<counter9/counter8
<<" +/- "<< uncertainty <<endl;

////////////


cout<<"counter11: "<<counter11<<""<<endl;
cout<<"counter12: "<<counter12<<""<<endl;
cout<<"the rate that W-merged jet is the leading jet, counter12/counter11: "<<counter12/counter11<<endl;







      if (flag_check == 1)  cout<<"check step 7 "<<endl;

int save_flag = 1;
//save_flag=1;

if( save_flag == 1){
//TFile *myFile = new TFile("WJet1_background_shape.root","recreate");
//TFile *myFile = new TFile("crab_TT1_semileptonic_ttbar_shape.root","recreate");
TFile *myFile = new TFile("test_shape.root","recreate");
//TFile *myFile = new TFile("crab_TT1_semileptonic_ttbar_bk2_reversely_shape.root","recreate"); // this is for study bk2 shapes
}

{
 TCanvas * d9 =new TCanvas("d9","",600,600);

h_reco_both_sides_had_top_mass->SetLineColor(1);
h_reco_both_sides_had_top_mass->Draw();

h_had_top_mass_signal->SetLineColor(2);
h_had_top_mass_signal->Draw("same");

h_had_top_mass_bk1->SetLineColor(3);
h_had_top_mass_bk1->Draw("same");

h_had_top_mass_bk2->SetLineColor(4);
h_had_top_mass_bk2->Draw("same");

  TLegend* leg = new TLegend(0.6,0.5,0.95,0.6);
   leg->SetHeader("had top mass(black)= sig(red) + bk1(green) + bk2(blue)");
   leg->Draw();

if( save_flag == 1){
d9->Write();
h_reco_both_sides_had_top_mass->Write();
h_had_top_mass_signal->Write();
h_had_top_mass_bk1->Write();
h_had_top_mass_bk2->Write();
	}
}

{
 TCanvas * d10 =new TCanvas("d10","",600,600);

h_reco_both_sides_lep_top_mass->SetLineColor(1);
h_reco_both_sides_lep_top_mass->Draw();

h_lep_top_mass_signal->SetLineColor(2);
h_lep_top_mass_signal->Draw("same");

h_lep_top_mass_bk1->SetLineColor(3);
h_lep_top_mass_bk1->Draw("same");

h_lep_top_mass_bk2->SetLineColor(4);
h_lep_top_mass_bk2->Draw("same");

  TLegend* leg = new TLegend(0.6,0.5,0.95,0.6);
   leg->SetHeader("lep top mass(black)= sig(red) + bk1(green) + bk2(blue)");
   leg->Draw();

if( save_flag == 1){
d10->Write();
h_reco_both_sides_lep_top_mass->Write();
h_lep_top_mass_signal->Write();
h_lep_top_mass_bk1->Write();
h_lep_top_mass_bk2->Write();
	}

}

 TCanvas * d11 =new TCanvas("d11","",600,600);
 gStyle->SetPalette(1);
h_chi2_first_term_and_second_term->Draw("COLZ,TEXT");
//h_chi2_first_term_and_second_term->Draw();
if( save_flag == 1){
d11->Write();
h_chi2_first_term_and_second_term->Write();
}
  
}

double uncertainty_calculate( double pass, double total)
{
double fail = total - pass;

double uncertainty = sqrt(pass*fail*(pass+fail))/pow(pass+fail,2);

return uncertainty;
}
