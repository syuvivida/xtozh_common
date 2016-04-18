#include <vector>
#include <string>
#include <iostream>
#include <TMath.h>
#include <TClonesArray.h>
#include <TLorentzVector.h>
#include "untuplizer.h"

bool isPassZmumu(TreeReader &data, vector<Int_t>& goodMuID){

  Int_t    nMu       = data.GetInt("nMu");
  Int_t*   muCharge  = data.GetPtrInt("muCharge");
  TClonesArray* muP4 = (TClonesArray*) data.GetPtrTObject("muP4");
  vector<bool>& isHighPtMuon = *((vector<bool>*) data.GetPtr("isHighPtMuon"));
  vector<bool>& isCustomTrackerMuon = *((vector<bool>*) data.GetPtr("isCustomTrackerMuon"));
  Float_t* muTrkIso     = data.GetPtrFloat("muTrkIso");
  Float_t* muInnerTrkPt = data.GetPtrFloat("muInnerTrkPt");

  // select good muons
  std::vector<Int_t> goodMuons;
  for(Int_t im = 0; im < nMu; im++){
      
    TLorentzVector* myMu = (TLorentzVector*)muP4->At(im);
    if( !isHighPtMuon[im] && !isCustomTrackerMuon[im] ) continue;
    if( fabs(myMu->Eta()) > 2.4 ) continue;
    if( myMu->Pt() < 20 ) continue;

    goodMuons.push_back(im);

  }	


  // select good Z boson

  bool findMPair = false;
  TLorentzVector* thisMu = NULL;
  TLorentzVector* thatMu = NULL;

  for(unsigned int i = 0; i < goodMuons.size(); i++){

    Int_t im = goodMuons[i];
    thisMu = (TLorentzVector*)muP4->At(im);
    Float_t pt1  = thisMu->Pt();
    Float_t regularIso1 = muTrkIso[im]/pt1;

    for(unsigned int j = 0; j < i; j++){

      Int_t jm = goodMuons[j];
      thatMu = (TLorentzVector*)muP4->At(jm);

      if( !isHighPtMuon[im] && !isHighPtMuon[jm] ) continue;
      if(! ( (thisMu->Pt()>50 && fabs(thisMu->Eta())<2.1) ||
	     (thatMu->Pt()>50 && fabs(thatMu->Eta())<2.1) ))continue;

      Float_t pt2  = thatMu->Pt();
      Float_t regularIso2 = muTrkIso[jm]/pt2;
      Float_t boostIso1 = ( muTrkIso[im]-muInnerTrkPt[jm] )/pt1;
      Float_t boostIso2 = ( muTrkIso[jm]-muInnerTrkPt[im] )/pt2;

      Float_t mll  = (*thisMu+*thatMu).M();
      Float_t ptll = (*thisMu+*thatMu).Pt();


      // check isolation
      Float_t dR = thisMu->DeltaR(*thatMu);
      // if the two muons are far away, use regular isolation
      if(dR > 0.3 && regularIso1 > 0.1)continue;
      if(dR > 0.3 && regularIso2 > 0.1)continue;

      // if the two muons are close, use corrected isolation
      if(dR < 0.3 && boostIso1 > 0.1)continue;
      if(dR < 0.3 && boostIso2 > 0.1)continue;
      

      if( muCharge[im]*muCharge[jm] > 0 ) continue;
      if( mll < 70 || mll > 110 ) continue;
      if( ptll < 170 ) continue;


      if( !findMPair ){

	goodMuID.push_back( (pt1 > pt2) ? im : jm );
	goodMuID.push_back( (pt1 > pt2) ? jm : im );

      }

      findMPair = true;
      break;

    }
  }

  if( !findMPair ) return false;
  return true;

}
