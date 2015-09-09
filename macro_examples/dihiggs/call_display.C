#include <string>
#include <vector>
#include "displayMultipleHistos.C"

using namespace std;

void call_display()
{
  std::string dirname="/afs/cern.ch/work/s/syu/debug/CMSSW_7_1_14/src/";
  vector<string> filenames;
  vector<string> legnames;
  ////////////////////////////////  
  filenames.clear();
  filenames.push_back(dirname+"Radionhh4b_M2000.root");
  filenames.push_back(dirname+"RShh4b_M2000.root");
  filenames.push_back(dirname+"Bulkhh4b_M2000.root");

  legnames.clear();
  legnames.push_back("Spin-0 Radion");
  legnames.push_back("Spin-2 RS Graviton");
  legnames.push_back("Spin-2 Bulk Graviton");
  
  displayMultipleHistos(filenames,legnames,"h_Xpz","X#rightarrow hh, M_{X}=2000 GeV");
  displayMultipleHistos(filenames,legnames,"h_Xy","X#rightarrow hh, M_{X}=2000 GeV");
  displayMultipleHistos(filenames,legnames,"h_cosThetaStar","X#rightarrow hh, M_{X}=2000 GeV");
  displayMultipleHistos(filenames,legnames,"h_cosPhi","X#rightarrow hh, M_{X}=2000 GeV");
  displayMultipleHistos(filenames,legnames,"h_Bpt0","X#rightarrow hh, M_{X}=2000 GeV","p_{T}(H) [GeV]",0,1500);
  displayMultipleHistos(filenames,legnames,"h_By0","X#rightarrow hh, M_{X}=2000 GeV","Rapidity of Higgs");
  displayMultipleHistos(filenames,legnames,"h_D_dR0","X#rightarrow hh, M_{X}=2000 GeV","#Delta R(b,b)",0,1);
  displayMultipleHistos(filenames,legnames,"h_cosTheta0","X#rightarrow hh, M_{X}=2000 GeV");


  ////////////////////////////////  
  filenames.clear();
  filenames.push_back(dirname+"Radionhh4b_M4500.root");
  filenames.push_back(dirname+"RShh4b_M4500.root");
  filenames.push_back(dirname+"Bulkhh4b_M4500.root");
  legnames.clear();
  legnames.push_back("Spin-0 Radion");
  legnames.push_back("Spin-2 RS Graviton");
  legnames.push_back("Spin-2 Bulk Graviton");
  
  displayMultipleHistos(filenames,legnames,"h_Xpz","X#rightarrow hh, M_{X}=4500 GeV");
  displayMultipleHistos(filenames,legnames,"h_Xy","X#rightarrow hh, M_{X}=4500 GeV");
  displayMultipleHistos(filenames,legnames,"h_cosThetaStar","X#rightarrow hh, M_{X}=4500 GeV");
  displayMultipleHistos(filenames,legnames,"h_cosPhi","X#rightarrow hh, M_{X}=4500 GeV");
  displayMultipleHistos(filenames,legnames,"h_Bpt0","X#rightarrow hh, M_{X}=4500 GeV","p_{T}(H) [GeV]");
  displayMultipleHistos(filenames,legnames,"h_By0","X#rightarrow hh, M_{X}=4500 GeV","Rapidity of Higgs");
  displayMultipleHistos(filenames,legnames,"h_D_dR0","X#rightarrow hh, M_{X}=4500 GeV","#Delta R(b,b)",0,0.5);
  displayMultipleHistos(filenames,legnames,"h_cosTheta0","X#rightarrow hh, M_{X}=4500 GeV");




  ////////////////////////////////  
  filenames.clear();
  filenames.push_back(dirname+"Radionhh4b_M2000_gluon.root");
  filenames.push_back(dirname+"RShh4b_M2000_gluon.root");
  filenames.push_back(dirname+"Bulkhh4b_M2000_gluon.root");

  legnames.clear();
  legnames.push_back("Spin-0 Radion");
  legnames.push_back("Spin-2 RS Graviton");
  legnames.push_back("Spin-2 Bulk Graviton");
  
  displayMultipleHistos(filenames,legnames,"h_Xpz","X#rightarrow hh, M_{X}=2000 GeV, GF only");
  displayMultipleHistos(filenames,legnames,"h_Xy","X#rightarrow hh, M_{X}=2000 GeV, GF only");
  displayMultipleHistos(filenames,legnames,"h_cosThetaStar","X#rightarrow hh, M_{X}=2000 GeV, GF only");
  displayMultipleHistos(filenames,legnames,"h_cosPhi","X#rightarrow hh, M_{X}=2000 GeV, GF only");
  displayMultipleHistos(filenames,legnames,"h_Bpt0","X#rightarrow hh, M_{X}=2000 GeV, GF only","p_{T}(H) [GeV]",0,1500);
  displayMultipleHistos(filenames,legnames,"h_By0","X#rightarrow hh, M_{X}=2000 GeV, GF only","Rapidity of Higgs");
  displayMultipleHistos(filenames,legnames,"h_D_dR0","X#rightarrow hh, M_{X}=2000 GeV, GF only","#Delta R(b,b)",0,1);
  displayMultipleHistos(filenames,legnames,"h_cosTheta0","X#rightarrow hh, M_{X}=2000 GeV, GF only");


  ////////////////////////////////  
  filenames.clear();
  filenames.push_back(dirname+"Radionhh4b_M4500_gluon.root");
  filenames.push_back(dirname+"RShh4b_M4500_gluon.root");
  filenames.push_back(dirname+"Bulkhh4b_M4500_gluon.root");
  legnames.clear();
  legnames.push_back("Spin-0 Radion");
  legnames.push_back("Spin-2 RS Graviton");
  legnames.push_back("Spin-2 Bulk Graviton");
  
  displayMultipleHistos(filenames,legnames,"h_Xpz","X#rightarrow hh, M_{X}=4500 GeV, GF only");
  displayMultipleHistos(filenames,legnames,"h_Xy","X#rightarrow hh, M_{X}=4500 GeV, GF only");
  displayMultipleHistos(filenames,legnames,"h_cosThetaStar","X#rightarrow hh, M_{X}=4500 GeV, GF only");
  displayMultipleHistos(filenames,legnames,"h_cosPhi","X#rightarrow hh, M_{X}=4500 GeV, GF only");
  displayMultipleHistos(filenames,legnames,"h_Bpt0","X#rightarrow hh, M_{X}=4500 GeV, GF only","p_{T}(H) [GeV]");
  displayMultipleHistos(filenames,legnames,"h_By0","X#rightarrow hh, M_{X}=4500 GeV, GF only","Rapidity of Higgs");
  displayMultipleHistos(filenames,legnames,"h_D_dR0","X#rightarrow hh, M_{X}=4500 GeV, GF only","#Delta R(b,b)",0,0.5);
  displayMultipleHistos(filenames,legnames,"h_cosTheta0","X#rightarrow hh, M_{X}=4500 GeV, GF only");






  ////////////////////////////////  
  filenames.clear();
  filenames.push_back(dirname+"RadionWW_M2000.root");
  filenames.push_back(dirname+"RSWW_M2000.root");
  filenames.push_back(dirname+"BulkWW_M2000.root");

  legnames.clear();
  legnames.push_back("Spin-0 Radion");
  legnames.push_back("Spin-2 RS Graviton");
  legnames.push_back("Spin-2 Bulk Graviton");
  
  displayMultipleHistos(filenames,legnames,"h_Xpz","X#rightarrow WW, M_{X}=2000 GeV");
  displayMultipleHistos(filenames,legnames,"h_Xy","X#rightarrow WW, M_{X}=2000 GeV");
  displayMultipleHistos(filenames,legnames,"h_cosThetaStar","X#rightarrow WW, M_{X}=2000 GeV");
  displayMultipleHistos(filenames,legnames,"h_cosPhi","X#rightarrow WW, M_{X}=2000 GeV");
  displayMultipleHistos(filenames,legnames,"h_Bpt0","X#rightarrow WW, M_{X}=2000 GeV","p_{T}(W) [GeV]",0,1500);
  displayMultipleHistos(filenames,legnames,"h_By0","X#rightarrow WW, M_{X}=2000 GeV","Rapidity of W");
  displayMultipleHistos(filenames,legnames,"h_D_dR0","X#rightarrow WW, M_{X}=2000 GeV","#Delta R(q,q)",0,1);
  displayMultipleHistos(filenames,legnames,"h_cosTheta0","X#rightarrow WW, M_{X}=2000 GeV");


  ////////////////////////////////  
  filenames.clear();
  filenames.push_back(dirname+"RadionWW_M4500.root");
  filenames.push_back(dirname+"RSWW_M4500.root");
  filenames.push_back(dirname+"BulkWW_M4500.root");
  legnames.clear();
  legnames.push_back("Spin-0 Radion");
  legnames.push_back("Spin-2 RS Graviton");
  legnames.push_back("Spin-2 Bulk Graviton");
  
  displayMultipleHistos(filenames,legnames,"h_Xpz","X#rightarrow WW, M_{X}=4500 GeV");
  displayMultipleHistos(filenames,legnames,"h_Xy","X#rightarrow WW, M_{X}=4500 GeV");
  displayMultipleHistos(filenames,legnames,"h_cosThetaStar","X#rightarrow WW, M_{X}=4500 GeV");
  displayMultipleHistos(filenames,legnames,"h_cosPhi","X#rightarrow WW, M_{X}=4500 GeV");
  displayMultipleHistos(filenames,legnames,"h_Bpt0","X#rightarrow WW, M_{X}=4500 GeV","p_{T}(W) [GeV]");
  displayMultipleHistos(filenames,legnames,"h_By0","X#rightarrow WW, M_{X}=4500 GeV","Rapidity of W");
  displayMultipleHistos(filenames,legnames,"h_D_dR0","X#rightarrow WW, M_{X}=4500 GeV","#Delta R(q,q)",0,0.5);
  displayMultipleHistos(filenames,legnames,"h_cosTheta0","X#rightarrow WW, M_{X}=4500 GeV");




  ////////////////////////////////  
  filenames.clear();
  filenames.push_back(dirname+"RadionWW_M2000_gluon.root");
  filenames.push_back(dirname+"RSWW_M2000_gluon.root");
  filenames.push_back(dirname+"BulkWW_M2000_gluon.root");

  legnames.clear();
  legnames.push_back("Spin-0 Radion");
  legnames.push_back("Spin-2 RS Graviton");
  legnames.push_back("Spin-2 Bulk Graviton");
  
  displayMultipleHistos(filenames,legnames,"h_Xpz","X#rightarrow WW, M_{X}=2000 GeV, GF only");
  displayMultipleHistos(filenames,legnames,"h_Xy","X#rightarrow WW, M_{X}=2000 GeV, GF only");
  displayMultipleHistos(filenames,legnames,"h_cosThetaStar","X#rightarrow WW, M_{X}=2000 GeV, GF only");
  displayMultipleHistos(filenames,legnames,"h_cosPhi","X#rightarrow WW, M_{X}=2000 GeV, GF only");
  displayMultipleHistos(filenames,legnames,"h_Bpt0","X#rightarrow WW, M_{X}=2000 GeV, GF only","p_{T}(W) [GeV]",0,1500);
  displayMultipleHistos(filenames,legnames,"h_By0","X#rightarrow WW, M_{X}=2000 GeV, GF only","Rapidity of W");
  displayMultipleHistos(filenames,legnames,"h_D_dR0","X#rightarrow WW, M_{X}=2000 GeV, GF only","#Delta R(q,q)",0,1);
  displayMultipleHistos(filenames,legnames,"h_cosTheta0","X#rightarrow WW, M_{X}=2000 GeV, GF only");


  ////////////////////////////////  
  filenames.clear();
  filenames.push_back(dirname+"RadionWW_M4500_gluon.root");
  filenames.push_back(dirname+"RSWW_M4500_gluon.root");
  filenames.push_back(dirname+"BulkWW_M4500_gluon.root");
  legnames.clear();
  legnames.push_back("Spin-0 Radion");
  legnames.push_back("Spin-2 RS Graviton");
  legnames.push_back("Spin-2 Bulk Graviton");
  
  displayMultipleHistos(filenames,legnames,"h_Xpz","X#rightarrow WW, M_{X}=4500 GeV, GF only");
  displayMultipleHistos(filenames,legnames,"h_Xy","X#rightarrow WW, M_{X}=4500 GeV, GF only");
  displayMultipleHistos(filenames,legnames,"h_cosThetaStar","X#rightarrow WW, M_{X}=4500 GeV, GF only");
  displayMultipleHistos(filenames,legnames,"h_cosPhi","X#rightarrow WW, M_{X}=4500 GeV, GF only");
  displayMultipleHistos(filenames,legnames,"h_Bpt0","X#rightarrow WW, M_{X}=4500 GeV, GF only","p_{T}(W) [GeV]");
  displayMultipleHistos(filenames,legnames,"h_By0","X#rightarrow WW, M_{X}=4500 GeV, GF only","Rapidity of W");
  displayMultipleHistos(filenames,legnames,"h_D_dR0","X#rightarrow WW, M_{X}=4500 GeV, GF only","#Delta R(q,q)",0,0.5);
  displayMultipleHistos(filenames,legnames,"h_cosTheta0","X#rightarrow WW, M_{X}=4500 GeV, GF only");







}
