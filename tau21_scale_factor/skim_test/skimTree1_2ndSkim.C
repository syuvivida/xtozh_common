#define skimTree1_2ndSkim_cxx
#include "skimTree1_2ndSkim.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>

void skimTree1_2ndSkim::Loop()
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

    // require events have CA8jet pt >200
/*
    bool hasCA8jet=false;

    for(int i=0; i < CA8nJet; i++){

	double jet_pt = CA8jetPt->at(i);
      	
	if(jet_pt >200)
	{
		hasCA8jet=true;
		cout<<"ev: "<< jentry << " jet pt: "<<jet_pt<<endl;
		break;
        }


    } // end of loop over ca8 jet
*/
    // require gen muon (status=3) <- W <- top

    //           cout<<"ev: "<< jentry <<endl;

    bool hasGenMuon=false;

    for(int i=0; i < nGenPar; i++){

	if(genParId->at(i) !=13 && genParId->at(i) != -13  ){continue;}
	if(genParSt->at(i)!=3){continue;}

	       //cout<<"ev: "<< jentry <<endl;
               //cout<<" ID : "<< genParId->at(i)<<" status: " <<genParSt->at(i)<<endl;

	int mother_index = genMo1->at(i);
        if(genParId->at(mother_index) !=24 && genParId->at(mother_index) != -24  ){continue;}

              //cout<<" mother ID : "<< genParId->at(mother_index)<<endl;

        int grandmother_index = genMo1->at(mother_index);
        if(genParId->at(grandmother_index) !=6 && genParId->at(grandmother_index) != -6  ){continue;}

              //cout<<" grand mother ID : "<< genParId->at(grandmother_index)<<endl;
    
                hasGenMuon=true;
//                cout<<"ev: "<< jentry << " jet pt: "<<jet_pt<<endl;
                break;


    } // end of loop over gen




    if(!hasGenMuon)continue;
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
