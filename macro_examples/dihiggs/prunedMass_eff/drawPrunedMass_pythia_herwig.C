#include "setNCUStyle.C"
#include <TH1.h>
#include <TSystem.h>
#include <TLegend.h>

void drawPrunedMass_pythia_herwig(string infname, int M)
{
  setNCUStyle();
  TH1F* h1;
  TH1F* h2;
  TFile *inf2 = new TFile(Form("%s%d_13TeV-madgraph.root",infname.data(),M));
  TFile *inf1 = new TFile(Form("%s%d_13TeV-madgraph-herwigpp.root",infname.data(),M));

  bool isWW=(infname.find("WW")!= std::string::npos);
  std::string prefix=isWW? "WW":"hh";
  
  h1= (TH1F*)inf1->FindObjectAny("h_PR");
  h2= (TH1F*)inf2->FindObjectAny("h_PR");

  h1->SetLineColor(1);
  h1->SetLineWidth(2);
  h2->SetLineColor(2);
  h2->SetFillColor(2);
  h2->SetFillStyle(1001);
  h2->GetXaxis()->SetTitleSize(0.05);
  h2->GetYaxis()->SetTitleSize(0.05);
  h2->GetXaxis()->SetTitleOffset(1.2);
  h2->GetYaxis()->SetTitleOffset(1.2);
  if(isWW){
    h2->GetXaxis()->SetRangeUser(0,126);
    h1->GetXaxis()->SetRangeUser(0,126);
  }
  h2->GetXaxis()->SetTitle("L2+L3 corrected M_{pruned} [GeV]");
  h2->GetYaxis()->SetTitle("Arbitrary unit per 2 GeV");
  h2->DrawNormalized();
  h1->DrawNormalized("same");

  // For Legend
  TLegend* legend = new TLegend(0.146, 0.706, 0.547,0.886,NULL,"brNDC");
  legend->SetLineColor(1);
  legend->SetLineStyle(1);
  legend->SetLineWidth(1);
  legend->SetFillStyle(0);
  legend->SetTextSize(0.05);
  legend->SetHeader(Form("G_{bulk}#rightarrow%s, M_{G_{bulk}}=%d TeV",prefix.data(),(int)(M/1000)));
  legend->AddEntry(h1,"Herwig++","lpf");
  legend->AddEntry(h2,"Pythia8","lpf");
  legend->Draw("same");

  TLatex *lar = new TLatex(0.13, 0.94, "CMS");
  lar->SetNDC(kTRUE); 
  lar->SetTextSize(0.050);
  lar->SetTextFont(62);
  lar->SetLineWidth(5);
  lar->Draw("");

  TLatex *lar2 = new TLatex(0.25, 0.94, "Simulation");
  lar2->SetNDC(kTRUE); 
  lar2->SetTextSize(0.050);
  lar2->SetTextFont(52);
  lar2->SetLineWidth(5);
  lar2->Draw("");

  gSystem->mkdir("plots");
  c1->Print(Form("plots/prunedM_%s-M%d.eps",prefix.data(),M));
  c1->Print(Form("plots/prunedM_%s-M%d.gif",prefix.data(),M));
  c1->Print(Form("plots/prunedM_%s-M%d.C",prefix.data(),M));

}
