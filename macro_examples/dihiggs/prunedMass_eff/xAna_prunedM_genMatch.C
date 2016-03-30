// example code to run Bulk Graviton->ZZ->ZlepZhad selections on electron-channel

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <TString.h>
#include <map>
#include <TH2.h>
#include <TH1D.h>
#include <TFile.h>
#include "untuplizer.h"
#include <TClonesArray.h>
#include <TLorentzVector.h>
#include <TSystem.h>

using namespace std;
const float wMassMin=65;
const float wMassMax=105;
//const float wMassMax=85;
const float hMassMin=105;
const float hMassMax=135;
void xAna_prunedM_genMatch(std::string inputFile, bool debug=false){

  std::string dirName="prunedM_genMatch";

  gSystem->mkdir(dirName.data());
  TString outputFile=gSystem->GetFromPipe(Form("file=%s; test=${file##*/}; echo \"%s/histoPR_${test}\"",
					       inputFile.data(), dirName.data()));
  std::cout << "output file name = " << outputFile.Data() << endl;

  bool isHerwigpp=(inputFile.find("herwigpp")!= std::string::npos);
  cout << endl;
  if(isHerwigpp)cout << "Note!! This is a herwigpp MC sample " << endl;
  else
    cout << "This is a pythia8 MC sample" << endl;
  cout << endl;



  bool isWW=(inputFile.find("WW")!= std::string::npos);
  bool ishh=(inputFile.find("hh")!= std::string::npos);
  cout << endl;
  if(isWW)cout << "Note!! This is BulkG->WW" << endl;
  else if(ishh)
    cout << "This is BulkG->hh" << endl;
  cout << endl;



  //get TTree from file ...
  TreeReader data(inputFile.data());
  
  Long64_t nTotal=0;
  Long64_t nPass[20]={0};

  TH1F* h_PR=new TH1F("h_PR","",100,0,200);

  TH1F* h_jMass_after  =(TH1F*)h_PR->Clone("h_jMass_after");
  TH1F* h_jMass_afterHP=(TH1F*)h_PR->Clone("h_jMass_afterHP");
  TH1F* h_jMass_afterLP=(TH1F*)h_PR->Clone("h_jMass_afterLP");

  TH1F* h_PR_after     =(TH1F*)h_PR->Clone("h_PR_after");
  TH1F* h_PR_afterHP   =(TH1F*)h_PR->Clone("h_PR_afterHP");
  TH1F* h_PR_afterLP   =(TH1F*)h_PR->Clone("h_PR_afterLP");

  TH1F* h_rawPR_after  =(TH1F*)h_PR->Clone("h_rawPR_after");
  TH1F* h_rawPR_afterHP=(TH1F*)h_PR->Clone("h_rawPR_afterHP");
  TH1F* h_rawPR_afterLP=(TH1F*)h_PR->Clone("h_rawPR_afterLP");

  TH2F* h_PRCos=new TH2F("h_PRCos","",50,0,200,20,-1,1);
  TH2F* h_PRdR=new TH2F("h_PRdR","",50,0,200,60,0,6);
  TH2F* h_dRCos=new TH2F("h_dRCos","",60,0,6,20,-1,1);
  TH2F* h_MassCos=new TH2F("h_MassCos","",50,0,200,20,-1,1);

  // for debugging
  TH2F* h_AngleCos=new TH2F("h_AngleCos","",40,0,2,20,-1,1);

  TH1F* h_hh=new TH1F("h_hh","",900,0,4500);

  Long64_t nTotalJets=0;
  Long64_t nTotalJetsMassUp=0;
  Long64_t nTotalJetsMassCentral=0;
  Long64_t nTotalJetsMassDown=0;
  Long64_t nTotalJetsMassLP=0;
  Long64_t nTotalJetsMassLPext=0;
  Long64_t nTotalJetsMassHP=0;

  Long64_t nTotalJets_after=0;
  Long64_t nTotalJetsMassUp_after=0;
  Long64_t nTotalJetsMassCentral_after=0;
  Long64_t nTotalJetsMassDown_after=0;
  Long64_t nTotalJetsMassLP_after=0;
  Long64_t nTotalJetsMassLPext_after=0;
  Long64_t nTotalJetsMassHP_after=0;

  for(Long64_t jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    if (jEntry % 50000 == 0)
      fprintf(stderr, "Processing event %lli of %lli\n", jEntry + 1, data.GetEntriesFast());

    if(debug && jEntry>10)break;

    data.GetEntry(jEntry);
    nTotal++;

    Int_t nGenPar        = data.GetInt("nGenPar");
    Int_t* genParId      = data.GetPtrInt("genParId");
    Int_t* genParSt      = data.GetPtrInt("genParSt");
    Int_t* genMomParId   = data.GetPtrInt("genMomParId");

    int genHIndex[2]={-1,-1};
    const int bosonID= ishh? 25: 24;

    for(int ig=0; ig < nGenPar; ig++){

      if(abs(genParId[ig])!=bosonID)continue;

      if(isHerwigpp && abs(genMomParId[ig])!=bosonID)continue;

      if(genHIndex[0]<0)
	genHIndex[0]=ig;

      else if(genHIndex[1]<0)
	genHIndex[1]=ig;

    }    
    

    if(genHIndex[0]<0 || genHIndex[1]<0)continue;
    nPass[0]++;

    if(genHIndex[0]==genHIndex[1])continue;
    
    // 1. make sure there is a W/h-> qq 
    bool hasLepton=false;
    Int_t* genDa1      = data.GetPtrInt("genDa1");
    Int_t* genDa2      = data.GetPtrInt("genDa2");

    for(int ig=0; ig < nGenPar; ig++){

      if(abs(genParId[ig])!=bosonID)continue;
      int da1=genDa1[ig];
      int da2=genDa2[ig];

      if(da1<0 || da2<0)continue;
      int da1pdg = genParId[da1];
      int da2pdg = genParId[da2];

      if(abs(da1pdg)>10 && abs(da1pdg)<17)
       	hasLepton=true;
      if(abs(da2pdg)>10 && abs(da2pdg)<17)
       	hasLepton=true;

      if(hasLepton)break;

    }

    if(hasLepton)continue;

    nPass[1]++;

    TLorentzVector genH_l4[2];
    TClonesArray* genParP4 = (TClonesArray*) data.GetPtrTObject("genParP4");

    
    for(int ih=0; ih<2; ih++)
      genH_l4[ih] = *((TLorentzVector*)genParP4->At(genHIndex[ih]));

    if(debug){
      cout << genHIndex[0] << "\t" << genHIndex[1] << endl;
      cout << " p = " << genH_l4[0].P() << " " << genH_l4[1].P() << endl;
      genH_l4[0].Print();
      genH_l4[1].Print();
    }

    int nFATJet         = data.GetInt("FATnJet");
    const int nJets=nFATJet;
    TClonesArray* fatjetP4 = (TClonesArray*) data.GetPtrTObject("FATjetP4");
    
    // check matching first

    bool findAMatch=false;
    const float dRMax=0.4;
    int matchedHJetIndex[2]={-1,-1};
		      
    for(int ij=0; ij<nJets; ij++)
      {
	TLorentzVector* thisJet = (TLorentzVector*)fatjetP4->At(ij);

	for(int jj=0; jj<nJets; jj++)
	  {

	    if(ij==jj)continue;
	    TLorentzVector* thatJet = (TLorentzVector*)fatjetP4->At(jj);
	    
	    if(thisJet->DeltaR(genH_l4[0])<dRMax && 
	       thatJet->DeltaR(genH_l4[1])<dRMax)
	      {
		matchedHJetIndex[0]=ij;
		matchedHJetIndex[1]=jj;
		findAMatch=true;
		break;
	      }

	    if(findAMatch)break;

	  }	

	if(findAMatch)break;

      }

    if(!findAMatch)continue;
    if(debug)
      cout << matchedHJetIndex[0] << "\t" << matchedHJetIndex[1] << endl;
    nPass[2]++;

    Int_t event        = data.GetInt("eventId");
    //0. has a good vertex
    Int_t nVtx        = data.GetInt("nVtx");
    if(nVtx<1)continue;
    nPass[3]++;

    Float_t*  fatjetTau1 = data.GetPtrFloat("FATjetTau1");
    Float_t*  fatjetTau2 = data.GetPtrFloat("FATjetTau2");
    Float_t*  fatjetCISVV2 = data.GetPtrFloat("FATjetCISVV2");
    Float_t*  fatjetPRmass = data.GetPtrFloat("FATjetPRmass");
    Float_t*  fatjetPRmassL2L3Corr = data.GetPtrFloat("FATjetPRmassL2L3Corr");

    Float_t*  jecUp   = data.GetPtrFloat("FATjetCorrUncUp");
    Float_t*  jecDown = data.GetPtrFloat("FATjetCorrUncDown");
    Int_t*   nSubSoftDropJet = data.GetPtrInt("FATnSubSDJet");
    vector<float>   *subjetSDCSV =  data.GetPtrVectorFloat("FATsubjetSDCSV", nFATJet);
    vector<float>   *subjetSDPx  =  data.GetPtrVectorFloat("FATsubjetSDPx", nFATJet);
    vector<float>   *subjetSDPy  =  data.GetPtrVectorFloat("FATsubjetSDPy", nFATJet);
    vector<float>   *subjetSDPz  =  data.GetPtrVectorFloat("FATsubjetSDPz", nFATJet);
    vector<float>   *subjetSDE   =  data.GetPtrVectorFloat("FATsubjetSDE", nFATJet);
    vector<bool>    &passFatJetLooseID = *((vector<bool>*) data.GetPtr("FATjetPassIDLoose"));


    int nGoodJets=0;
    for(int i=0; i<2; i++)
      {
    	
	int ij = matchedHJetIndex[i];
	float mass=fatjetPRmassL2L3Corr[ij];
	h_PR->Fill(mass);
	nTotalJets++;

	if(ishh && (mass < hMassMin ||
		    mass > hMassMax))continue;
	if(isWW && (mass < wMassMin ||
		    mass > wMassMax))continue;

	nTotalJetsMassCentral++;
	float tau21_i = fatjetTau2[ij]/fatjetTau1[ij];

	if(tau21_i<0.75)nTotalJetsMassLP++;
	if(tau21_i<0.6)nTotalJetsMassHP++;
	else if(tau21_i>=0.6 && tau21_i<0.75)nTotalJetsMassLPext++;
	
	nGoodJets++;
	
      }
    if(nGoodJets>=2)nPass[4]++;
   
    // check systematic uncertainty JECUp
    for(int i=0; i<2; i++)
      {
    	
	int ij = matchedHJetIndex[i];
	float mass=fatjetPRmassL2L3Corr[ij]*(1+fabs(jecUp[i]));

	if(ishh && (mass < hMassMin ||
		    mass > hMassMax))continue;
	if(isWW && (mass < wMassMin ||
		    mass > wMassMax))continue;	

	nTotalJetsMassUp++;
      }

    // check systematic uncertainty JECDown
    for(int i=0; i<2; i++)
      {
    	
	int ij = matchedHJetIndex[i];
	float mass=fatjetPRmassL2L3Corr[ij]*(1-fabs(jecDown[i]));

	if(ishh && (mass < hMassMin ||
		    mass > hMassMax))continue;
	if(isWW && (mass < wMassMin ||
		    mass > wMassMax))continue;	

	nTotalJetsMassDown++;
      }


 
    TLorentzVector recoH_l4[2];
    nGoodJets=0;
    for(int i=0; i<2; i++)
      {
    	
	int ij = matchedHJetIndex[i];
     	TLorentzVector* thisJet = (TLorentzVector*)fatjetP4->At(ij);
	recoH_l4[i]= (*thisJet);
    	if(thisJet->Pt()<200)continue;
	if(fabs(thisJet->Eta())>2.4)continue;
	nGoodJets++;
      }

    if(nGoodJets<2)continue;
    nPass[5]++;
    
    if(debug)
      {
	recoH_l4[0].Print();
	recoH_l4[1].Print();
      }

    float dEta=fabs(recoH_l4[0].Eta()-recoH_l4[1].Eta());
    if(dEta>1.3)continue;
    nPass[6]++;

    float M=(recoH_l4[0] + recoH_l4[1]).M();
    if(M<1000)continue;
    nPass[7]++;


    nGoodJets=0;
    for(int i=0; i<2; i++)
      {
    	bool isLP=false;
	bool isHP=false;
	int ij = matchedHJetIndex[i];
	float tau21 = fatjetTau2[ij]/fatjetTau1[ij];

	TLorentzVector* thisJet = (TLorentzVector*)fatjetP4->At(ij);
	h_jMass_after->Fill(thisJet->M());

	float mass=fatjetPRmassL2L3Corr[ij];
	h_PR_after->Fill(mass);

	float raw_mass=fatjetPRmass[ij];
	h_rawPR_after->Fill(raw_mass);


	TLorentzVector* thisH = (TLorentzVector*)genParP4->At(genHIndex[i]);

	TLorentzVector thisB(*((TLorentzVector*)genParP4->At(genDa1[genHIndex[i]])));
	thisB.Boost(-thisH->BoostVector());
	float cos=TMath::Cos(thisB.Vect().Angle(thisH->Vect()));

	if(debug)
	  cout <<  "cosTheta1 = " << cos << endl;
	
	TLorentzVector* b1   = (TLorentzVector*)genParP4->At(genDa1[genHIndex[i]]);
	TLorentzVector* b2   = (TLorentzVector*)genParP4->At(genDa2[genHIndex[i]]);
	float dR = b1->DeltaR(*b2);

	float cosbb = TMath::Cos(b1->Vect().Angle(b2->Vect()));
	float dTheta= sqrt(2*(1-cosbb));
	if(debug)
	  {
	    b1->Print();
	    b2->Print();
	    cout << "sqrt(2*(1-cos(angle))) = " << dTheta << endl;
	  }

	if(debug)
	  cout << "dR = " << dR << endl;

	h_PRCos   ->Fill(mass,cos);
	h_PRdR    ->Fill(mass,dR );
	h_dRCos   ->Fill(dR,cos);
	h_MassCos ->Fill(thisJet->M(),cos);
	h_AngleCos->Fill(dTheta,cos);


	if(tau21<0.75)isLP=true;
	if(tau21<0.6)isHP=true;

	if(isLP)h_PR_afterLP->Fill(mass);
	if(isHP)h_PR_afterHP->Fill(mass);

	if(isLP)h_rawPR_afterLP->Fill(raw_mass);
	if(isHP)h_rawPR_afterHP->Fill(raw_mass);


	if(isLP)h_jMass_afterLP->Fill(thisJet->M());
	if(isHP)h_jMass_afterHP->Fill(thisJet->M());

	nTotalJets_after++;

	if(ishh && (mass < hMassMin ||
		    mass > hMassMax))continue;
	if(isWW && (mass < wMassMin ||
		    mass > wMassMax))continue;

	nTotalJetsMassCentral_after++;

	if(isLP)nTotalJetsMassLP_after++;
	if(isHP)nTotalJetsMassHP_after++;
	else if(isLP)nTotalJetsMassLPext_after++;


	nGoodJets++;
      }

    // check systematic uncertainty JECUp
    for(int i=0; i<2; i++)
      {
    	
	int ij = matchedHJetIndex[i];
	float mass=fatjetPRmassL2L3Corr[ij]*(1+fabs(jecUp[i]));

	if(ishh && (mass < hMassMin ||
		    mass > hMassMax))continue;
	if(isWW && (mass < wMassMin ||
		    mass > wMassMax))continue;	

	nTotalJetsMassUp_after++;
      }

    // check systematic uncertainty JECDown
    for(int i=0; i<2; i++)
      {
    	
	int ij = matchedHJetIndex[i];
	float mass=fatjetPRmassL2L3Corr[ij]*(1-fabs(jecDown[i]));

	if(ishh && (mass < hMassMin ||
		    mass > hMassMax))continue;
	if(isWW && (mass < wMassMin ||
		    mass > wMassMax))continue;	

	nTotalJetsMassDown_after++;
      }



    if(nGoodJets<2)continue;
    nPass[8]++;

    int nHP=0;
    int nLP=0;
    for(int i=0; i<2; i++)
      {
    	
	int ij = matchedHJetIndex[i];

	float tau21 = fatjetTau2[ij]/fatjetTau1[ij];
	bool isHP= (tau21 < 0.6);
	bool isLP= (tau21 < 0.75);
       
	if(isHP)nHP++;
	if(isLP)nLP++;
      }

    if(nHP==0 && nLP<2)continue;
    nPass[9]++;

    int nSubBJet=0;

    for(int i=0; i<2; i++)
      {    	
	int ij = matchedHJetIndex[i];
	for(int is=0; is < nSubSoftDropJet[ij]; is++){
	  if(subjetSDCSV[ij][is] < 0.605)continue;
	  nSubBJet++;
	}
      }
    nPass[10+nSubBJet]++;

    

  } // end of loop over entries

  std::cout << "nTotal    = " << nTotal << std::endl;
  std::cout << "nTotalJets    = " << nTotalJets << std::endl;
  std::cout << "nTotalJets_after    = " << nTotalJets_after << std::endl;
  std::cout << "nTotalJetsHP    = " << nTotalJetsMassHP << std::endl;
  std::cout << "nTotalJetsHP_after    = " << nTotalJetsMassHP_after << std::endl;
  std::cout << "nTotalJetsLP    = " << nTotalJetsMassLP << std::endl;
  std::cout << "nTotalJetsLP_after    = " << nTotalJetsMassLP_after << std::endl;
  std::cout << "nTotalJetsLPext    = " << nTotalJetsMassLPext << std::endl;
  std::cout << "nTotalJetsLPext_after    = " << nTotalJetsMassLPext_after << std::endl;

  std::cout << "nTotalJetsMassCentral    = " << nTotalJetsMassCentral << std::endl;
  std::cout << "nTotalJetsMassCentral_after    = " << nTotalJetsMassCentral_after << std::endl;

  std::cout << "nTotalJetsMassUp    = " << nTotalJetsMassUp << std::endl;
  std::cout << "nTotalJetsMassUp_after    = " << nTotalJetsMassUp_after << std::endl;

  std::cout << "nTotalJetsMassDown    = " << nTotalJetsMassDown << std::endl;
  std::cout << "nTotalJetsMassDown_after    = " << nTotalJetsMassDown_after << std::endl;

  for(int i=0;i<20;i++)
    if(nPass[i]>0)
      std::cout << "nPass[" << i << "]= " << nPass[i] << std::endl;


  std::string prefix=isWW? "WW": "hh";
  ofstream fout;
  fout.open(Form("eff_%s.dat",prefix.data()),ios::out| ios::app);
  fout << nPass[3] << " " << nPass[4] << " " << nPass[7] << " " << nPass[8] << endl;
  fout.close();

  ofstream foutM;
  foutM.open(Form("Masseff_%s.dat",prefix.data()),ios::out| ios::app);
  foutM << nTotalJets << " " << nTotalJetsMassCentral << " " << nTotalJets_after << " " << nTotalJetsMassCentral_after << endl;
  foutM.close();


  ofstream foutH;
  foutH.open(Form("HPeff_%s.dat",prefix.data()),ios::out| ios::app);
  foutH << nTotalJets << " " << nTotalJetsMassHP << " " << nTotalJets_after << " " << nTotalJetsMassHP_after << endl;
  foutH.close();


  ofstream foutL;
  foutL.open(Form("LPeff_%s.dat",prefix.data()),ios::out| ios::app);
  foutL << nTotalJets << " " << nTotalJetsMassLP << " " << nTotalJets_after << " " << nTotalJetsMassLP_after << endl;
  foutL.close();


  ofstream foutLext;
  foutLext.open(Form("LPexteff_%s.dat",prefix.data()),ios::out| ios::app);
  foutLext << nTotalJets << " " << nTotalJetsMassLPext << " " << nTotalJets_after << " " << nTotalJetsMassLPext_after << endl;
  foutLext.close();


  //for JES uncertainty
  ofstream foutjes;
  foutjes.open(Form("JECeff_%s.dat",prefix.data()),ios::out| ios::app);
  foutjes << nTotalJets << " " << nTotalJetsMassCentral << " " << nTotalJets_after << " " << nTotalJetsMassCentral_after << endl;
  foutjes.close();

  ofstream foutjesUp;
  foutjesUp.open(Form("JECUpeff_%s.dat",prefix.data()),ios::out| ios::app);
  foutjesUp << nTotalJets << " " << nTotalJetsMassUp << " " << nTotalJets_after << " " << nTotalJetsMassUp_after << endl;
  foutjesUp.close();

  ofstream foutjesDown;
  foutjesDown.open(Form("JECDowneff_%s.dat",prefix.data()),ios::out| ios::app);
  foutjesDown << nTotalJets << " " << nTotalJetsMassDown << " " << nTotalJets_after << " " << nTotalJetsMassDown_after << endl;
  foutjesDown.close();


  TFile* outFile = new TFile(outputFile.Data(),"recreate");

  h_PR->Write();
  h_PR_after->Write();
  h_PR_afterHP->Write();
  h_PR_afterLP->Write();

  h_PRCos->Write();
  h_PRdR->Write();
  h_dRCos->Write();
  h_MassCos->Write();

  h_AngleCos->Write();


  h_rawPR_after->Write();
  h_rawPR_afterHP->Write();
  h_rawPR_afterLP->Write();

  h_jMass_after->Write();
  h_jMass_afterHP->Write();
  h_jMass_afterLP->Write();

  outFile->Close();




}
