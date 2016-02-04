#include "setNCUStyle.C"

void draw(string infname)
{
  setNCUStyle();
  TH1F* h1;
  TH1F* h2;
  TFile *inf = new TFile(infname.data());
  
  h1= (TH1F*)inf->FindObjectAny("h_hh");
  h2= (TH1F*)inf->FindObjectAny("h_hh2");

  h1->SetLineColor(1);
  h1->SetLineWidth(2);
  h2->SetLineColor(2);
  h2->SetFillColor(2);
  h2->SetFillStyle(1001);
  h2->GetXaxis()->SetTitleSize(0.05);
  h2->GetYaxis()->SetTitleSize(0.05);
  h2->GetXaxis()->SetTitleOffset(1.2);
  h2->GetYaxis()->SetTitleOffset(1.2);
  h2->GetYaxis()->SetTitle("Arbitrary unit per 10 GeV");
  h2->DrawNormalized();
  h1->DrawNormalized("same");

  // For Legend
  TLegend* legend = new TLegend(0.565, 0.693, 0.965,0.874,NULL,"brNDC");
  legend->SetLineColor(1);
  legend->SetLineStyle(1);
  legend->SetLineWidth(1);
  legend->SetFillStyle(0);
  legend->SetTextSize(0.05);
  legend->SetHeader("M_{G_{bulk}}=1.8 TeV");
//   legend->AddEntry("h1","No correction: M_{jj}");
//  legend->AddEntry("h2","corrected: M_{jj}-(M_{j1}-125)-(M_{j2}-125)");
  legend->AddEntry(h1,"No correction","lpf");
  legend->AddEntry(h2,"Corrected","lpf");
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

}
