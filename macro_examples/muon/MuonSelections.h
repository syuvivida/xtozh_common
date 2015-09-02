void select_highptMuons(TreeReader &data, vector<int> &accepted) {

  accepted.clear();
  Int_t nMu      = data.GetInt("nMu");
  vector<bool> &isGlobalMuon = *((vector<bool>*) data.GetPtr("isGlobalMuon"));
  Int_t* muHits  = data.GetPtrInt("muHits");
  Int_t* muMatches  = data.GetPtrInt("muMatches");
  Int_t* muTrkLayers = data.GetPtrInt("muTrkLayers");
  Int_t* muPixelHits = data.GetPtrInt("muPixelHits");
  Float_t* muTrkPtErr= data.GetPtrFloat("muTrkPtErr");
  Float_t* muTrkPt   = data.GetPtrFloat("muTrkPt");
  Float_t* mudxy     = data.GetPtrFloat("mudxy");
  Float_t* mudz      = data.GetPtrFloat("mudz");

  for(int im=0; im< nMu; im++)
    {
      
      if(!isGlobalMuon[im])continue;

      if(muHits[im]<1)continue;

      if(muMatches[im]<2)continue;
      
      if(muTrkLayers[im]<6)continue;

      if(muPixelHits[im]<1)continue;

      if(muTrkPtErr[im]/muTrkPt[im] >0.3)continue;

      if(fabs(mudxy[im])>0.2)continue;

      if(fabs(mudz[im])>0.5)continue;

      accepted.push_back(im);

    }
  return;

}



void select_customizeTrackerMuon(TreeReader &data, vector<int> &accepted) {

  accepted.clear();
  Int_t nMu      = data.GetInt("nMu");
  vector<bool> &isTrackerMuon = *((vector<bool>*) data.GetPtr("isTrackerMuon"));
  Int_t* muMatches  = data.GetPtrInt("muMatches");
  Int_t* muTrkLayers = data.GetPtrInt("muTrkLayers");
  Int_t* muPixelHits = data.GetPtrInt("muPixelHits");
  Float_t* muTrkPtErr= data.GetPtrFloat("muTrkPtErr");
  Float_t* muTrkPt   = data.GetPtrFloat("muTrkPt");
  Float_t* mudxy     = data.GetPtrFloat("mudxy");
  Float_t* mudz      = data.GetPtrFloat("mudz");

  for(int im=0; im< nMu; im++)
    {
      if(!isTrackerMuon[im])continue;

      if(muMatches[im]<2)continue;

      if(muTrkLayers[im]<6)continue;

      if(muPixelHits[im]<1)continue;

      if(muTrkPtErr[im]/muTrkPt[im] >0.3)continue;

      if(fabs(mudxy[im])>0.2)continue;

      if(fabs(mudz[im])>0.5)continue;



      accepted.push_back(im);
      
    }
  return;

}




