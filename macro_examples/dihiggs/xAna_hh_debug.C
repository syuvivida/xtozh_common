// example code to run Bulk Graviton->ZZ->ZlepZhad selections on electron-channel

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <TString.h>
#include <map>
#include <TH1D.h>
#include <TFile.h>
#include "untuplizer.h"
#include <TClonesArray.h>
#include <TLorentzVector.h>
#include <TF1.h>

using namespace std;



float getPUPPIweight(float puppipt, float puppieta ){


  TF1* puppisd_corrGEN      = new TF1("puppisd_corrGEN","[0]+[1]*pow(x*[2],-[3])");
  puppisd_corrGEN->SetParameters(
   				 1.00626,
   				 -1.06161,
   				 0.07999,
   				 1.20454
   				 );
  TF1* puppisd_corrRECO_cen = new TF1("puppisd_corrRECO_cen","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)+[5]*pow(x,5)");
  puppisd_corrRECO_cen->SetParameters(
   				      1.05807,
   				      -5.91971e-05,
   				      2.296e-07,
   				      -1.98795e-10,
   				      6.67382e-14,
   				      -7.80604e-18
   				      );

  TF1* puppisd_corrRECO_for = new TF1("puppisd_corrRECO_for","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)+[5]*pow(x,5)");
  puppisd_corrRECO_for->SetParameters(
   				      1.26638,
   				      -0.000658496,
   				      9.73779e-07,
   				      -5.93843e-10,
   				      1.61619e-13,
   				      -1.6272e-17);

  float genCorr  = 1.;
  float recoCorr = 1.;
  float totalWeight = 1.;

  genCorr =  puppisd_corrGEN->Eval( puppipt );
  if( fabs(puppieta)  <= 1.3 ) recoCorr = puppisd_corrRECO_cen->Eval( puppipt );
  else
    if( fabs(puppieta) > 1.3 ) recoCorr = puppisd_corrRECO_for->Eval( puppipt );

  totalWeight = genCorr * recoCorr;
  // file->Close();
  return totalWeight;
}


void xAna_hh_debug(std::string inputFile, bool CHS=false, bool cutHMass=true, bool debug=false, bool cut=true){

  TString outputFile;
  outputFile=gSystem->GetFromPipe(Form("file=%s; test=${file##*/}; echo \"massHisto_${test}\"",inputFile.data()));
  if(CHS)outputFile = "CHS_" + outputFile;
  if(cutHMass)outputFile = "cutHMass_" + outputFile;

  cout << "output file name = " << outputFile.Data() << endl;


  //get TTree from file ...
  TreeReader data(inputFile.data());
  
  Long64_t nTotal=0;
  Long64_t nPass[20]={0};

  TH1F* h_mass     = new TH1F("h_mass","",100,1000,3000);
  TH1F* hmjj = (TH1F*)h_mass->Clone("hmjj");
  TH1F* hmjj_reduced = (TH1F*)h_mass->Clone("hmjj_reduced");
  TH1F* hmjj_reduced_corr = (TH1F*)h_mass->Clone("hmjj_reduced_corr");

  for(Long64_t jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    if (jEntry % 1000 == 0)
      fprintf(stderr, "Processing event %lli of %lli\n", jEntry + 1, data.GetEntriesFast());


    if(debug && jEntry>10)break;

    data.GetEntry(jEntry);
    nTotal++;

    //2. pass electron or muon trigger                                                                                                                                          
    std::string* trigName = data.GetPtrString("hlt_trigName");
    vector<bool> &trigResult = *((vector<bool>*) data.GetPtr("hlt_trigResult"));
    const Int_t nsize = data.GetPtrStringSize();

    bool passTrigger=false;
    for(int it=0; it< nsize; it++)
      {
	std::string thisTrig= trigName[it];
        bool results = trigResult[it];

        // std::cout << thisTrig << " : " << results << std::endl;                                                                                                              

        if( (thisTrig.find("HLT_PFHT800_v")!= std::string::npos && results==1)
            )
          {
            passTrigger=true;
            break;
          }


      }

    if(!passTrigger && cut)continue;
    nPass[0]++;




    //0. has a good vertex
    Int_t nVtx        = data.GetInt("nVtx");
    if(nVtx<1 && cut)continue;
    nPass[1]++;


    int nFATJet         = CHS? data.GetInt("FATnJet"):data.GetInt("AK8PuppinJet");
    const int nJets=nFATJet;
    TClonesArray* fatjetP4   = CHS? (TClonesArray*) data.GetPtrTObject("FATjetP4"):
      (TClonesArray*) data.GetPtrTObject("AK8PuppijetP4");
    Float_t*  fatjetTau1 = CHS? data.GetPtrFloat("FATjetTau1"):data.GetPtrFloat("AK8PuppijetTau1");
    Float_t*  fatjetTau2 = CHS? data.GetPtrFloat("FATjetTau2"):data.GetPtrFloat("AK8PuppijetTau2");
    Float_t*  fatjetPRmassL2L3Corr = data.GetPtrFloat("FATjetPRmassL2L3Corr");
    Float_t*  fatjetRawmass = CHS? data.GetPtrFloat("FATjetPRmass"): data.GetPtrFloat("AK8PuppijetSDmass");
    Float_t*  fatjetDSV = data.GetPtrFloat("AK8Puppijet_DoubleSV");

    vector<bool>    &passFatJetTightID = *((vector<bool>*) data.GetPtr("AK8PuppijetPassIDTight"));
    if(nFATJet<2)continue;
    int nGoodJets=0;
    for(int ij=0; ij<2; ij++)
      {
	TLorentzVector* thisJet = (TLorentzVector*)fatjetP4->At(ij);
    	if(thisJet->Pt()<300)continue;
	if(fabs(thisJet->Eta())>2.4)continue;
	if(!passFatJetTightID[ij])continue;
	nGoodJets++;
      }

    if(nGoodJets<2)continue;
    nPass[2]++;
    
    TLorentzVector recoH_l4[2];
    recoH_l4[0] = *((TLorentzVector*)fatjetP4->At(0));
    recoH_l4[1] = *((TLorentzVector*)fatjetP4->At(1));
    
    if(debug)
      {
	recoH_l4[0].Print();
	recoH_l4[1].Print();
      }

    float dEta=fabs(recoH_l4[0].Eta()-recoH_l4[1].Eta());
    if(dEta>1.3 && cut)continue;
    nPass[3]++;

    float M=(recoH_l4[0] + recoH_l4[1]).M();
    float Mred = M-(recoH_l4[0].M()-125)-(recoH_l4[1].M()-125);
    if(M<1000 && cut)continue;
    nPass[4]++;


    float thea_mass[2]={-999,-999};
    for(int ij=0; ij<2; ij++)
      {
	float thea_corr= getPUPPIweight(recoH_l4[ij].Pt(),recoH_l4[ij].Eta());
	thea_mass[ij]= CHS? fatjetPRmassL2L3Corr[ij]: fatjetRawmass[ij]*thea_corr;
      }
    
    if(cutHMass && (thea_mass[0]<105 || thea_mass[0]>135))continue;
    if(cutHMass && (thea_mass[1]<105 || thea_mass[1]>135))continue;
    if(!cutHMass && fatjetRawmass[0]<50)continue;
    if(!cutHMass && fatjetRawmass[1]<50)continue;
    nPass[5]++;

    float Mred_corr = M-(thea_mass[0]-125)-(thea_mass[1]-125);

    int nHP=0;
    int nLP=0;
    for(int ij=0; ij<2; ij++)
      {
    	
	float tau21_i = fatjetTau2[ij]/fatjetTau1[ij];
	bool isHP= (tau21_i < 0.6);
	if(isHP)nHP++;
      }

    if(nHP<2 && cut)continue;
    nPass[6]++;
    
    // if(fatjetDSV[0]<0.6)continue;
    // if(fatjetDSV[1]<0.6)continue;
    // nPass[7]++;
    hmjj->Fill(M);
    hmjj_reduced->Fill(Mred);
    hmjj_reduced_corr->Fill(Mred_corr);

    //

  } // end of loop over entries

  std::cout << "nTotal    = " << nTotal << std::endl;
  for(int i=0;i<20;i++)
    if(nPass[i]>0)
      std::cout << "nPass[" << i << "]= " << nPass[i] << std::endl;

  TFile* outFile = new TFile(outputFile.Data(),"recreate");

  hmjj->Write();
  hmjj_reduced->Write();
  hmjj_reduced_corr->Write();
  outFile->Close();


}
