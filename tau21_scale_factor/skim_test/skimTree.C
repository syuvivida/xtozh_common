#define skimTree_cxx
#include "skimTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>

void skimTree::Loop()
{
   if (fChain == 0) return;
  std::string remword=".root";
  size_t pos = inputFile_.find(remword);
  std::string forOutput = inputFile_;  
  if(pos!= std::string::npos)
    forOutput.swap(forOutput.erase(pos,remword.length()));   
  std::string endfix = "_filtered.root";
  std::string outputFile = forOutput + endfix;
   // now open new root file
  TFile* newfile_data = new TFile(outputFile.data(),"recreate");

  // clone tree
  TTree* newtree = fChain->CloneTree(0);
  newtree->SetMaxTreeSize(5000000000);
  cout << "Saving "  << outputFile       << " tree" << endl;

  ofstream fout;
  fout.open("wrong.dat");
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nPassEvt=0;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if (jentry%100==0)
      printf("%4.1f%% done.\r",(float)jentry/(float)nentries*100.);		


    // require events have two electrons or two muons
    // with mass = 60-120 GeV, pt > 60 GeV

    if(nEle < 2 && nMu < 2)continue;

    bool hasDoubleEle=false;

    for(int i=0; i < nEle; i++){
      
      TLorentzVector i_l4(0,0,0,0);
      i_l4.SetPtEtaPhiM(
			elePt->at(i),
			eleEta->at(i),
			elePhi->at(i),
			eleM->at(i)
			);
      for(int j=0; j< i; j++){
	
	TLorentzVector j_l4(0,0,0,0);
	j_l4.SetPtEtaPhiM(
			  elePt->at(j),
			  eleEta->at(j),
			  elePhi->at(j),
			  eleM->at(j)
			  );
	double Zpt = (i_l4+j_l4).Pt();
	double ZM = (i_l4+j_l4).M();

	if(Zpt > 60 && ZM > 60 && ZM < 120)
	  {
	    hasDoubleEle=true;
	    break;
	  }

      }
    } // end of double loop over electrons

    bool hasDoubleMuo=false;
    for(int i=0; i < nMu; i++){
      
      TLorentzVector i_l4(0,0,0,0);
      i_l4.SetPtEtaPhiM(
			muPt->at(i),
			muEta->at(i),
			muPhi->at(i),
			muM->at(i)
			);
      for(int j=0; j< i; j++){
	
	TLorentzVector j_l4(0,0,0,0);
	j_l4.SetPtEtaPhiM(
			  muPt->at(j),
			  muEta->at(j),
			  muPhi->at(j),
			  muM->at(j)
			  );
	double Zpt = (i_l4+j_l4).Pt();
	double ZM = (i_l4+j_l4).M();

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
  }
  
  // newtree->Print();
  newtree->AutoSave();
  delete newfile_data;
  fout.close();


 cout << "nentries = " << nentries << endl;
 cout << "Number of passed events = " << nPassEvt << endl;
 cout << "Reduction rate = " << (double)nPassEvt/(double)nentries << endl;

}
