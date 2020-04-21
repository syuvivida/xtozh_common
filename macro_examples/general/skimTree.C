#define skimTree_cxx
#include "skimTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>


void skimTree::Loop()
{
//   In a ROOT session, you can do:
//      root> .L skimTree.C
//      root> skimTree t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;
   // outputfile = "xxxx_filtered.root"
   string remword=".root";
   size_t pos = inputFile_.find(remword);
   string forOutput = inputFile_;
   if(pos!= std::string::npos)
     forOutput.swap(forOutput.erase(pos,remword.length()));
   string endfix = "_filtered.root";
   string outputFile = forOutput + endfix;

   //
   TH1F* hm = new TH1F("hm","",200,0,200);
   TH1F* hmass_ele = (TH1F*)hm->Clone("hmass_ele");
   TH1F* hmass_muo = (TH1F*)hm->Clone("hmass_muo");
   TH1F* hpt_ele = (TH1F*)hm->Clone("hpt_ele");
   TH1F* hpt_muo = (TH1F*)hm->Clone("hpt_muo");

   // now open new root file                                                    
   TFile* newfile_data = new TFile(outputFile.data(),"recreate");

   // clone tree                                                                 
   TTree* newtree = fChain->CloneTree(0);
   newtree->SetMaxTreeSize(5000000000);
   cout << "Saving "  << outputFile       << " tree" << endl;

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nPassEvt=0;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if (jentry%100==0)
	printf("%4.1f%% done.\r",(float)jentry/(float)nentries*100.);      

      // this example filter keeps events with at least two electrons 
      // or two muons that form an invariant mass between 60 and 120 GeV and 
      // with pt > 60 GeV

      if(nEle < 2 && nMu < 2)continue;

      bool hasDoubleEle=false;

      for(int i=0; i < nEle; i++){

	TLorentzVector* i_l4=(TLorentzVector*)eleP4->At(i);

	for(int j=0; j< i; j++){

	  TLorentzVector* j_l4=(TLorentzVector*)eleP4->At(j);

	  double ZM = (*i_l4+*j_l4).M();
	  double Zpt = (*i_l4+*j_l4).Pt();

	  hmass_ele->Fill(ZM);
	  hpt_ele->Fill(Zpt);

	  if(Zpt > 60 && ZM > 60 && ZM < 120)
	    {
	      hasDoubleEle=true;
	      break;
	    }

	}
      } // end of double loop over electrons                                   


      bool hasDoubleMuo=false;
      for(int i=0; i < nMu; i++){
	
	TLorentzVector* i_l4=(TLorentzVector*)muP4->At(i);

	for(int j=0; j< i; j++){

	  TLorentzVector* j_l4=(TLorentzVector*)muP4->At(j);
	  double ZM = (*i_l4+*j_l4).M();
	  double Zpt = (*i_l4+*j_l4).Pt();

	  hmass_muo->Fill(ZM);
	  hpt_muo->Fill(Zpt);
	  
	  if(Zpt > 60 && ZM > 60 && ZM < 120)
	    {
	      hasDoubleMuo=true;
	      break;
	    }

	}
      } // end of double loop over double muons                            

      if(!hasDoubleEle && !hasDoubleMuo)continue;

      newtree->Fill();
      nPassEvt++;
   } // end of loop over events

   hmass_ele->Write();
   hmass_muo->Write();
   hpt_ele->Write();
   hpt_muo->Write();
   // newtree->Print();                                                          
   newtree->AutoSave();
   delete newfile_data;


   
   cout << "nentries = " << nentries << endl;
   cout << "Number of passed events = " << nPassEvt << endl;
   cout << "Reduction rate = " << (double)nPassEvt/(double)nentries << endl;


}
