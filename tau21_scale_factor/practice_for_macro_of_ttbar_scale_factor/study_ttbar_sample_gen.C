#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <TF1.h>
#include <TH1D.h>
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

void study_ttbar_sample_gen(){

//  TreeReader data(inputFile.data());
//  TreeReader data("flattuple_12_1_pNo.root");
TreeReader data("combine_130_files.root");

//TChain *root = new TChain("tree");
//TChain *root = new TChain("tree/tree");

//root->Add("/Users/index0192/crab_TT1/results/filtered_files/*.root");
//TreeReader data(root);

cout<< "total # of event: "<< data.GetEntriesFast() << endl;
   //-----------------------------------------------------------------------------------//
	int counter1=0;
	Long64_t total_number = data.GetEntriesFast();

   //-----------------------------------------------------------------------------------//
  // begin of event loop

  for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++){

    if ( ev % 5000 == 0 )
      fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());

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

   //-----------------------------------------------------------------------------------// 
   // select gen leptonic neutrino

   // note, we are search in muon channel
    vector<Int_t> gen_leptonic_nu_index;

    gen_leptonic_nu(data, &gen_leptonic_nu_index);

   //-----------------------------------------------------------------------------------// 

   // select gen hadronic b-jet

   // note, we are search in muon channel
    vector<Int_t> gen_hadronic_Wjet_index;
    vector<Int_t> gen_hadronic_Bjet_index;

//    cout<<"ev event: "<<ev<<"   ----------------------------------------------"<<endl;
    gen_hadronic_Wjet_Bjet(data, &gen_hadronic_Wjet_index ,&gen_hadronic_Bjet_index);

   //-----------------------------------------------------------------------------------// 

                if(  gen_leptonic_nu_index.size()==1 && gen_hadronic_Wjet_index.size()==1  ){
		counter1 = counter1+1;

		}

  }// end event loop

cout<<"total_number: "<< total_number<<endl;
cout<< "counter1: "<< counter1 <<endl;




}



































