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
#include <TVector3.h>
#include "change.C"

void change(double& );

using namespace std;

void test(){

double a =10.5;

cout<<"before a:" << a <<endl;

change(a);

cout<<"after a:" << a <<endl;

}
