#include <string>
#include <vector>
#include "displayMultipleEffs.C"

using namespace std;

void call_display()
{
  std::string dirname="/afs/cern.ch/work/s/syu/13tev/scripts/";
  vector<string> filenames;
  filenames.push_back(dirname+"eff_HEEPNoIso_ZprimeToZhToZlephbb.root");
  filenames.push_back(dirname+"eff_LooseNoIso_ZprimeToZhToZlephbb.root");
  filenames.push_back(dirname+"eff_LeadHEEPSubHEEPLoose_ZprimeToZhToZlephbb.root");
  filenames.push_back(dirname+"eff_HEEPNoIsoOrLooseNoIso_ZprimeToZhToZlephbb.root");

  vector<string> legnames;
  legnames.push_back("HEEPNoIso");
  legnames.push_back("LooseNoIso");
  legnames.push_back("Lead:HEEP;Sub:HEEP or Loose");
  legnames.push_back("HEEPNoIso/LooseNoIso");

  displayMultipleEffs(filenames,legnames,"graph_gEff");
  displayMultipleEffs(filenames,legnames,"graph_gEff2");
  displayMultipleEffs(filenames,legnames,"graph_recoEff");
  displayMultipleEffs(filenames,legnames,"graph_recoEff2");







}
