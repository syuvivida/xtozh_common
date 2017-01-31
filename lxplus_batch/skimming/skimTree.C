#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include <iostream>

using namespace std;

void skimTree(int w , string st){
  TChain* tree = new TChain("tree/treeMaker");
  tree->Add(st.data());
  TFile* outputfile = new TFile(Form("skimmed_NCUGlobalTuples_%d.root",w),"RECREATE");
  TTree* newtree = tree->CopyTree("FATjetPuppiSDmass[0]>43 && FATjetPuppiSDmass[1]>43 && FATjetP4[0].Pt()>200 && FATjetP4[1].Pt()>200 && fabs(FATjetP4[0].Eta())<2.4 && fabs(FATjetP4[1].Eta())<2.4 && fabs(FATjetP4[0].Eta()-FATjetP4[1].Eta())<1.3");
  //  outputfile->cd();
  newtree->AutoSave();
  delete outputfile;
}
