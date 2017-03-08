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

TF1* puppisd_corrGEN;
TF1* puppisd_corrRECO_cen;
TF1* puppisd_corrRECO_for;


float getPUPPIweight(float puppipt, float puppieta ){

  float genCorr  = 1.;
  float recoCorr = 1.;
  float totalWeight = 1.;

  genCorr =  puppisd_corrGEN->Eval( puppipt );
  if( fabs(puppieta)  <= 1.3 ) recoCorr = puppisd_corrRECO_cen->Eval( puppipt );
  else
    if( fabs(puppieta) > 1.3 ) recoCorr = puppisd_corrRECO_for->Eval( puppipt );

  totalWeight = genCorr * recoCorr;
  return totalWeight;
}


void xAna_hh_preSelection(std::string inputFile, bool debug=false){


  // getting Thea's corrections
  // reading the root file takes too long 
  TFile* file = TFile::Open( "weights/puppiCorr.root","READ");
  puppisd_corrGEN      = (TF1*)file->Get("puppiJECcorr_gen");
  puppisd_corrRECO_cen = (TF1*)file->Get("puppiJECcorr_reco_0eta1v3");
  puppisd_corrRECO_for = (TF1*)file->Get("puppiJECcorr_reco_1v3eta2v5");
  file->Close();


  TString outputFile;
  outputFile=gSystem->GetFromPipe(Form("file=%s; test=${file##*/}; echo \"cutFlowHisto_${test}\"",inputFile.data()));
  cout << "output file name = " << outputFile.Data() << endl;



  //get TTree from file ...
  TreeReader data(inputFile.data());
  
  Long64_t nTotal=0;
  Long64_t nPass[20]={0};

  TH1F* h[20][2];
  std::string title[2]={"Before cuts","After cuts"};
  for(int ih=0; ih<2; ih++){

    h[0][ih] = new TH1F(Form("h0_%d",ih),title[ih].data(),200,0,2000);
    h[0][ih] -> SetXTitle("p_{T}(jet) [GeV]");

    h[1][ih] = new TH1F(Form("h1_%d",ih),title[ih].data(),100,-3,3);
    h[1][ih] -> SetXTitle("#eta(jet) ");

    h[2][ih] = new TH1F(Form("h2_%d",ih),title[ih].data(),120,0,1.2);
    h[2][ih] -> SetXTitle("#tau_{21}^{puppi}(jet)");

    h[3][ih] = new TH1F(Form("h3_%d",ih),title[ih].data(),100,0,200);
    h[3][ih] -> SetXTitle("M_{jet}^{Thea,puppi}(jet) [GeV]");

    h[4][ih] = new TH1F(Form("h4_%d",ih),title[ih].data(),100,-1,1);
    h[4][ih] -> SetXTitle("Double-b-tagger discriminant");

    h[5][ih] = new TH1F(Form("h5_%d",ih),title[ih].data(),150,0,3.0);
    h[5][ih] -> SetXTitle("|#Delta #eta_{jj}|");

    h[6][ih] = new TH1F(Form("h6_%d",ih),title[ih].data(),150,500,3500);
    h[6][ih] -> SetXTitle("M_{jj} [GeV]");


  }


  for(Long64_t jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    if (jEntry % 1000 == 0)
      fprintf(stderr, "Processing event %lli of %lli\n", jEntry + 1, data.GetEntriesFast());


    if(debug && jEntry>10)break;

    data.GetEntry(jEntry);
    nTotal++;

    //2. pass various trigger paths

    bool isData  = data.GetBool("isData"); // only apply trigger if it's data

    std::string* trigName = data.GetPtrString("hlt_trigName");
    vector<bool> &trigResult = *((vector<bool>*) data.GetPtr("hlt_trigResult"));
    const Int_t nsize = data.GetPtrStringSize();

    bool passTrigger=false;
    for(int it=0; it< nsize; it++)
      {
	std::string thisTrig= trigName[it];
        bool results = trigResult[it];

        if( (thisTrig.find("HLT_PFHT800_v")!= std::string::npos && results==1) ||
	    (thisTrig.find("HLT_PFHT900_v")!= std::string::npos && results==1) || // for runH
	    (thisTrig.find("HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v")!= std::string::npos && results==1) ||
	    (thisTrig.find("HLT_AK8PFJet360_TrimMass30_v")!= std::string::npos && results==1) ||
	    (thisTrig.find("HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_v")!= std::string::npos && results==1) ||
	    (thisTrig.find("HLT_AK8PFHT650_TrimR0p1PT0p03Mass50_v")!= std::string::npos && results==1) 
            )
          {
            passTrigger=true;
            break;
          }
      }

    if(!passTrigger)continue;
    nPass[0]++;

    //0. has a good vertex
    Int_t nVtx        = data.GetInt("nVtx");
    if(nVtx<1)continue;
    nPass[1]++;

    //1. veto events containing 1 or 2 leptons

    Int_t nEle         = data.GetInt("nEle");
    TClonesArray* eleP4 = (TClonesArray*) data.GetPtrTObject("eleP4");
    Float_t* eleSCEta                = data.GetPtrFloat("eleScEta");
    Float_t* eleSigmaIEtaIEtaFull5x5 = data.GetPtrFloat("eleSigmaIEtaIEtaFull5x5");
    Float_t* eleHoverE               = data.GetPtrFloat("eleHoverE");
    Float_t* eleEcalPFClusterIso     = data.GetPtrFloat("eleEcalPFClusterIso");
    Float_t* eleHcalPFClusterIso     = data.GetPtrFloat("eleHcalPFClusterIso");
    Float_t* eleDr03TkSumPt          = data.GetPtrFloat("eleDr03TkSumPt");
    Float_t* eledEtaAtVtx            = data.GetPtrFloat("eledEtaAtVtx");
    Float_t* eledPhiAtVtx            = data.GetPtrFloat("eledPhiAtVtx");
    Int_t*   eleCharge               = data.GetPtrInt("eleCharge");
    vector<bool>    &isMediumEle= *((vector<bool>*) data.GetPtr("eleIsPassMVAMedium"));
    vector<bool>     &isTightEle= *((vector<bool>*) data.GetPtr("eleIsPassMVATight"));

    // check if there is any single tight electron
    bool hasSingleTightElectron=false;

    for(int ie=0; ie < nEle; ie++){

      TLorentzVector* thisEle= (TLorentzVector*)eleP4->At(ie);
      if( fabs(thisEle->Eta())>2.4 )continue;
      if( thisEle->Pt() < 25 )continue;
      bool preSelect= 

	( fabs(eleSCEta[ie]) < 1.4442 && eleSigmaIEtaIEtaFull5x5[ie] < 0.012 && 
	  eleHoverE[ie] < 0.09 && (eleEcalPFClusterIso[ie]/thisEle->Pt()) < 0.37 && ( eleHcalPFClusterIso[ie]/thisEle->Pt()) < 0.25 && (eleDr03TkSumPt[ie]/thisEle->Pt()) < 0.18 
	  && fabs(eledEtaAtVtx[ie]) < 0.0095 && fabs(eledPhiAtVtx[ie]) < 0.065 ) ||

	( fabs(eleSCEta[ie]) > 1.5660 && fabs(eleSCEta[ie]) < 2.5 && eleSigmaIEtaIEtaFull5x5[ie] < 0.033 && 
	  eleHoverE[ie] <0.09 && (eleEcalPFClusterIso[ie]/thisEle->Pt()) < 0.45 && (eleHcalPFClusterIso[ie]/thisEle->Pt()) < 0.28 && (eleDr03TkSumPt[ie]/thisEle->Pt()) < 0.18 );
    
      if(!preSelect)continue;

      if( !isTightEle[ie] )continue;

	
      hasSingleTightElectron=true;
      break;
      
    }
    if( hasSingleTightElectron )continue;
    nPass[2]++;


    // check if there is any double loose electron
    bool hasLooseElectronPair=false;
    for(int ie=0; ie < nEle; ie++){
      for(int je=0; je < ie; je++){

	if(eleCharge[ie]*eleCharge[je]>0)continue;

   	TLorentzVector* thisEle= (TLorentzVector*)eleP4->At(ie);

    	if( fabs(thisEle->Eta())>2.4 )continue;
    	if( thisEle->Pt() < 15 )continue;

   	TLorentzVector* thatEle = (TLorentzVector*)eleP4->At(je);
    	if( fabs(thatEle->Eta())>2.4 )continue;
    	if( thatEle->Pt() < 15 )continue;

	bool preSelect_ie= 

	( fabs(eleSCEta[ie]) < 1.4442 && eleSigmaIEtaIEtaFull5x5[ie] < 0.012 && 
	  eleHoverE[ie] < 0.09 && (eleEcalPFClusterIso[ie]/thisEle->Pt()) < 0.37 && ( eleHcalPFClusterIso[ie]/thisEle->Pt()) < 0.25 && (eleDr03TkSumPt[ie]/thisEle->Pt()) < 0.18 
	  && fabs(eledEtaAtVtx[ie]) < 0.0095 && fabs(eledPhiAtVtx[ie]) < 0.065 ) ||

	( fabs(eleSCEta[ie]) > 1.5660 && fabs(eleSCEta[ie]) < 2.5 && eleSigmaIEtaIEtaFull5x5[ie] < 0.033 && 
	  eleHoverE[ie] <0.09 && (eleEcalPFClusterIso[ie]/thisEle->Pt()) < 0.45 && (eleHcalPFClusterIso[ie]/thisEle->Pt()) < 0.28 && (eleDr03TkSumPt[ie]/thisEle->Pt()) < 0.18 );
	
	if(!preSelect_ie)continue;


	bool preSelect_je= 

	( fabs(eleSCEta[je]) < 1.4442 && eleSigmaIEtaIEtaFull5x5[je] < 0.012 && 
	  eleHoverE[je] < 0.09 && (eleEcalPFClusterIso[je]/thatEle->Pt()) < 0.37 && ( eleHcalPFClusterIso[je]/thatEle->Pt()) < 0.25 && (eleDr03TkSumPt[je]/thatEle->Pt()) < 0.18 
	  && fabs(eledEtaAtVtx[je]) < 0.0095 && fabs(eledPhiAtVtx[je]) < 0.065 ) ||

	( fabs(eleSCEta[je]) > 1.5660 && fabs(eleSCEta[je]) < 2.5 && eleSigmaIEtaIEtaFull5x5[je] < 0.033 && 
	  eleHoverE[je] <0.09 && (eleEcalPFClusterIso[je]/thatEle->Pt()) < 0.45 && (eleHcalPFClusterIso[je]/thatEle->Pt()) < 0.28 && (eleDr03TkSumPt[je]/thatEle->Pt()) < 0.18 );
	
	if(!preSelect_je)continue;


	if( !isMediumEle[ie] )continue;
	if( !isMediumEle[je] )continue;
	
	hasLooseElectronPair=true;
	break;
      
      }
    }

    if( hasLooseElectronPair )continue;
    nPass[3]++;
    
    
    // veto of single tight muon or two oppositely-charged muon pair
    Int_t nMu          = data.GetInt("nMu");
    TClonesArray* muP4 = (TClonesArray*) data.GetPtrTObject("muP4");
    Int_t*   muCharge        = data.GetPtrInt("muCharge");
    vector<bool>    &isLooseMuon= *((vector<bool>*) data.GetPtr("isLooseMuon"));
    vector<bool>    &isTightMuon= *((vector<bool>*) data.GetPtr("isTightMuon"));
    Float_t*          muIso1  = data.GetPtrFloat("muChHadIso");
    Float_t*          muIso2  = data.GetPtrFloat("muNeHadIso");
    Float_t*          muIso3  = data.GetPtrFloat("muGamIso");
    Float_t*          muIso4  = data.GetPtrFloat("muPUPt");
    
    // check if there is any single tight muon
    bool hasSingleTightMuon=false;

    for(int im=0; im < nMu; im++){

      TLorentzVector* thisMu = (TLorentzVector*)muP4->At(im);

      if( fabs(thisMu->Eta())>2.4 )continue;
      if( thisMu->Pt() < 25 )continue;
      if( !isTightMuon[im] )continue;

      float iso =  (muIso1[im] + max(0., muIso2[im]+muIso3[im] - 0.5*muIso4[im]))/thisMu->Pt();
      if( iso > 0.15)continue;
	
      hasSingleTightMuon=true;
      break;
      
    }
    if( hasSingleTightMuon )continue;
    nPass[4]++;


    // check if there is any double loose muons
    bool hasLooseMuonPair=false;
    for(int im=0; im < nMu; im++){
      for(int jm=0; jm < im; jm++){

	if(muCharge[im]*muCharge[jm]>0)continue;
	if( !isLooseMuon[im] )continue;
	if( !isLooseMuon[jm] )continue;

   	TLorentzVector* thisMu = (TLorentzVector*)muP4->At(im);

    	if( fabs(thisMu->Eta())>2.4 )continue;
    	if( thisMu->Pt() < 15 )continue;

   	TLorentzVector* thatMu = (TLorentzVector*)muP4->At(jm);
    	if( fabs(thatMu->Eta())>2.4 )continue;
    	if( thatMu->Pt() < 15 )continue;

	float iso1=  (muIso1[im] + max(0., muIso2[im]+muIso3[im] - 0.5*muIso4[im]))/thisMu->Pt();
	if( iso1> 0.25)continue;

	float iso2=  (muIso1[jm] + max(0., muIso2[jm]+muIso3[jm] - 0.5*muIso4[jm]))/thatMu->Pt();
	if( iso2> 0.25)continue;
	
	hasLooseMuonPair=true;
	break;
      
      }
    }
    if( hasLooseMuonPair )continue;

    nPass[5]++;

    // apply jet requirement

    int nJets         = data.GetInt("FATnJet");
    TClonesArray* fatjetP4   = (TClonesArray*) data.GetPtrTObject("FATjetP4");
    TClonesArray* puppijetP4 = (TClonesArray*) data.GetPtrTObject("FATjetPuppiP4");

    Float_t*  fatjetPuppiTau1 = data.GetPtrFloat("FATjetPuppiTau1");
    Float_t*  fatjetPuppiTau2 = data.GetPtrFloat("FATjetPuppiTau2");
    Float_t*  fatjetPuppiSDmass = data.GetPtrFloat("FATjetPuppiSDmass");
   
    vector<bool>    &passFatJetTightID = *((vector<bool>*) data.GetPtr("FATjetPassIDTight"));

    Float_t*  fatjetCEmEF = data.GetPtrFloat("FATjetCEmEF");
    Float_t*  fatjetMuoEF = data.GetPtrFloat("FATjetMuoEF");

    int nADDJets         = data.GetInt("ADDnJet");
    TClonesArray* addjetP4   = (TClonesArray*) data.GetPtrTObject("ADDjetP4");
    Float_t*  addjet_doublesv = data.GetPtrFloat("ADDjet_DoubleSV");

    if(nJets<2)continue;
    nPass[6]++;

    if(nADDJets<2)continue;
    nPass[7]++;

    Int_t nGoodJets=0;
    const float dRMax=0.8;
    int addJetIndex[2]={-1,-1};
    
    float thea_mass[2]={-1,-1};

    for(int ij=0; ij<2; ij++)
      {
	if( !passFatJetTightID[ij] )continue;
	
	TLorentzVector* thisJet = (TLorentzVector*)fatjetP4->At(ij);
	h[0][0]->Fill(thisJet->Pt());
	if( thisJet->Pt()<300 )continue;
	h[0][1]->Fill(thisJet->Pt());

	h[1][0]->Fill(thisJet->Eta());
	if( fabs(thisJet->Eta())>2.4 )continue;
	h[1][1]->Fill(thisJet->Eta());

	float tau21_puppi = fatjetPuppiTau2[ij]/fatjetPuppiTau1[ij];
	h[2][0]->Fill(tau21_puppi);
	if( tau21_puppi > 0.6 )continue;
	h[2][1]->Fill(tau21_puppi);

	TLorentzVector* thisJetPuppi = (TLorentzVector*)puppijetP4->At(ij);
	float thea_corr = getPUPPIweight(thisJetPuppi->Pt(),thisJetPuppi->Eta());
	float raw_mass = fatjetPuppiSDmass[ij];
	thea_mass[ij] = raw_mass*thea_corr;
	

	h[3][0]->Fill(thea_mass[ij]);
	if(thea_mass[ij] < 105 || thea_mass[ij] > 135)continue;
	h[3][1]->Fill(thea_mass[ij]);

	// now look for add jets

	for(int k=0; k < nADDJets; k++){
	  TLorentzVector* thatJet = (TLorentzVector*)addjetP4->At(k);
	  if(thisJet->DeltaR(*thatJet)<dRMax && addJetIndex[ij]<0)
	    {
	      addJetIndex[ij]=k;
	      break;
	    }
	}

	nGoodJets++;
      } // end of loop over two leading jets


    if(nGoodJets<2)continue;
    nPass[8]++;

    if(addJetIndex[0]==addJetIndex[1])
      {
	if(debug)cout << "Indices are the same: " << addJetIndex[0] << endl;
	continue;
      }

    if(addJetIndex[0]<0 || addJetIndex[1]<0)continue;
    if(debug)
      {
	cout << "ADDJet indices are " << addJetIndex[0] << "\t" << addJetIndex[1] << endl;
      }
    nPass[9]++;

    // check if any jet fail loose double b-tag

    const float DBLoose = 0.3;
    const float DBTight = 0.8;

    h[4][0]->Fill(addjet_doublesv[addJetIndex[0]]);
    h[4][0]->Fill(addjet_doublesv[addJetIndex[1]]);

    if(addjet_doublesv[addJetIndex[0]]< DBLoose)continue;
    if(addjet_doublesv[addJetIndex[1]]< DBLoose)continue;

    h[4][1]->Fill(addjet_doublesv[addJetIndex[0]]);
    h[4][1]->Fill(addjet_doublesv[addJetIndex[1]]);

    nPass[10]++;

    TLorentzVector* higgsJet[2];
    for(int i=0;i<2;i++)
      higgsJet[i] = (TLorentzVector*)fatjetP4->At(i);

    float dEta = fabs(higgsJet[0]->Eta()-higgsJet[1]->Eta());

    h[5][0]->Fill(dEta);
    if(dEta>1.3)continue;
    h[5][1]->Fill(dEta);
    nPass[11]++;

    float mjj = (*higgsJet[0]+*higgsJet[1]).M();

    float mjjred = mjj + 250 - thea_mass[0]-thea_mass[1];

    h[6][0]->Fill(mjjred);
    if(mjjred<750)continue;
    h[6][1]->Fill(mjjred);
    nPass[12]++;
    
    
  } // end of loop over entries

  TFile* outFile = new TFile(outputFile.Data(),"recreate");

  std::cout << "nTotal    = " << nTotal << std::endl;
  for(int i=0;i<20;i++)
    if(nPass[i]>0)
      std::cout << "nPass[" << i << "]= " << nPass[i] << std::endl;

  for(int i=0;i<7;i++)
    for(int ih=0; ih<2; ih++)
      h[i][ih]->Write();

  outFile->Write();

}
