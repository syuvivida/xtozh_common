#include <string>
#include <vector>
#include "displayMultipleHistos.C"

using namespace std;

void call_display()
{
  std::string dirname="/afs/cern.ch/work/s/syu/debug/CMSSW_7_1_14/src/";
  vector<string> filenames;
  
  filenames.push_back(dirname+"Radion.root");
  filenames.push_back(dirname+"RS.root");
  filenames.push_back(dirname+"Bulk.root");

  vector<string> legnames;
  legnames.push_back("Spin-0 Radion");
  legnames.push_back("Spin-2 RS Graviton");
  legnames.push_back("Spin-2 Bulk Graviton");
  
  displayMultipleHistos(filenames,legnames,"h_Xpz","M=2000 GeV");
  displayMultipleHistos(filenames,legnames,"h_Xy","M=2000 GeV");
  displayMultipleHistos(filenames,legnames,"h_cosThetaStar","M=2000 GeV");
  displayMultipleHistos(filenames,legnames,"h_cosPhi","M=2000 GeV");
  displayMultipleHistos(filenames,legnames,"h_Bpt0","M=2000 GeV");
  displayMultipleHistos(filenames,legnames,"h_By0","M=2000 GeV");
  displayMultipleHistos(filenames,legnames,"h_D_dR0","M=2000 GeV");
  displayMultipleHistos(filenames,legnames,"h_cosTheta0","M=2000 GeV");
  displayMultipleHistos(filenames,legnames,"h_Bpt1","M=2000 GeV");
  displayMultipleHistos(filenames,legnames,"h_By1","M=2000 GeV");
  displayMultipleHistos(filenames,legnames,"h_D_dR1","M=2000 GeV");
  displayMultipleHistos(filenames,legnames,"h_cosTheta1","M=2000 GeV");







}
