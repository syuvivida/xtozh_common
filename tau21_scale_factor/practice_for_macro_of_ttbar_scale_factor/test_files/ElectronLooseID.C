#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <TH1D.h>
#include <TH1F.h>
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
#include "untuplizer.h"

void ElectronLooseID(TreeReader &data,vector<Int_t> *test 
		      ){

  Int_t    nEle   = data.GetInt("nEle"); 
  Int_t*   elePassID = data.GetPtrInt("elePassID");
  Float_t  eleRho = data.GetFloat("eleRho");
  Float_t* eleEt  = data.GetPtrFloat("eleEt");
  Float_t* eleScEta = data.GetPtrFloat("eleScEta");
  Float_t* eleUserTrkIso = data.GetPtrFloat("eleUserTrkIso");
  Float_t* eleUserCalIso = data.GetPtrFloat("eleUserCalIso");


//test header file
 test->push_back(10);



/*  for(Int_t i = 0; i < nEle; i++){





    if( fabs(eleScEta[sortEleIndex]) > 0 && fabs(eleScEta[sortEleIndex]) < 1.4442 ){


    }

    // endcap selection
    if( fabs(eleScEta[sortEleIndex]) > 1.566 && fabs(eleScEta[sortEleIndex]) < 2.5 ){

    
    }
  }    

  //-----------------------------------------------------------------------------------//

*/

}
