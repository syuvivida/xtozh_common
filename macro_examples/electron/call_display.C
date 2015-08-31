#include <string>
#include <vector>
#include "displayMultipleEffs.C"

using namespace std;

void call_display()
{
  std::string dirname="/afs/cern.ch/work/s/syu/13tev/scripts/";
  vector<string> filenames;
  // filenames.push_back(dirname+"eff_HEEPMiniIso_ZprimeToZhToZlephbb.root");
  // filenames.push_back(dirname+"eff_LooseMiniIso_ZprimeToZhToZlephbb.root");
  // filenames.push_back(dirname+"eff_LeadHEEPSubHEEPLooseMiniIso_ZprimeToZhToZlephbb.root");
  // filenames.push_back(dirname+"eff_HEEPMiniIsoOrLooseMiniIso_ZprimeToZhToZlephbb.root");

  filenames.push_back(dirname+"eff_HEEPNoIso_ZprimeToZhToZlephbb.root");
  filenames.push_back(dirname+"eff_LooseNoIso_ZprimeToZhToZlephbb.root");
  filenames.push_back(dirname+"eff_LeadHEEPSubHEEPLoose_ZprimeToZhToZlephbb.root");
  filenames.push_back(dirname+"eff_HEEPNoIsoOrLooseNoIso_ZprimeToZhToZlephbb.root");

  vector<string> legnames;
  legnames.push_back("HEEPNoIso");
  legnames.push_back("LooseNoIso");
  legnames.push_back("Lead:HEEPNoIso;Sub:HEEPNoIso/LooseNoIso");
  legnames.push_back("HEEPNoIso/LooseNoIso");

  // displayMultipleEffs(filenames,legnames,"graph_gEff","with MiniIso<0.1");
  // displayMultipleEffs(filenames,legnames,"graph_gEff2","with MiniIso<0.1");
  // displayMultipleEffs(filenames,legnames,"graph_recoEff","with MiniIso<0.1");
  // displayMultipleEffs(filenames,legnames,"graph_recoEff2","with MiniIso<0.1");
  
  displayMultipleEffs(filenames,legnames,"graph_gEff","no iso cut");
  displayMultipleEffs(filenames,legnames,"graph_gEff2","no iso cut");
  displayMultipleEffs(filenames,legnames,"graph_recoEff","no iso cut");
  displayMultipleEffs(filenames,legnames,"graph_recoEff2","no iso cut");

  displayMultipleEffs(filenames,legnames,"ptgraph_gEff","no iso cut");
  displayMultipleEffs(filenames,legnames,"ptgraph_gEff2","no iso cut");
  displayMultipleEffs(filenames,legnames,"ptgraph_recoEff","no iso cut");
  displayMultipleEffs(filenames,legnames,"ptgraph_recoEff2","no iso cut");







}
