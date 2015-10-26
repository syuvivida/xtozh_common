#include "setNCUStyle.C"
#include <string>
#include "TCanvas.h"
using namespace std;

void twopads_HT(string inputfile, string histo)
{
  setNCUStyle();
  TFile *inf = new TFile(inputfile.data());

  TH1F *hzpt_before = (TH1F*)inf->FindObjectAny(Form("%s_before",histo.data()));
  TH1F *hzpt_after  = (TH1F*)inf->FindObjectAny(Form("%s_after",histo.data()));
 
  hzpt_before->Draw();
  hzpt_after->SetLineColor(2);
  hzpt_after->SetFillStyle(3004);
  hzpt_after->SetFillColor(kRed-7);
  hzpt_after->Draw("histsame");

  float xmin=90;
  float xmax=histo=="hzpt"?130:165;
  int   xint=histo=="hzpt"?101:162;

  cout << "Integral of hzpt_before = " << hzpt_before->Integral(xint,1001) << endl;
  cout << "Integral of hzpt_after = " << hzpt_after->Integral(xint,1001) << endl;
  c1->SetLogy(1);

  // TLegend* legend = new TLegend(0.1426, 0.1550, 0.4429,0.3554,NULL,"brNDC");
  TLegend* legend = new TLegend(0.5940, 0.2561, 0.8943,0.4564,NULL,"brNDC");
  legend->SetLineColor(1);
  legend->SetLineStyle(1);
  legend->SetLineWidth(1);
  legend->SetFillStyle(0);
  legend->SetTextSize(0.05);
  legend->AddEntry(hzpt_before,"No cut");
  legend->AddEntry(hzpt_after,"H_{T}>100 GeV");

  legend->Draw("same");

 
  float xlabelsize=hzpt_before->GetLabelSize("X"); 
  float ylabelsize=hzpt_before->GetLabelSize("Y");
  float canvassize = 0.5;
  float x1=0.4446;
  float y1=0.4146;
  TPad *subpad = new TPad("subpad","",
			  x1,y1,
			  x1+canvassize,y1+canvassize);
  subpad->SetFillStyle(0);
  subpad->Draw();
  subpad->cd();
  TH1F* hzoom_before = (TH1F*)hzpt_before->Clone("hzoom_before");
  hzoom_before->SetLabelSize(xlabelsize*0.7/canvassize,"X");
  hzoom_before->SetLabelSize(ylabelsize*0.7/canvassize,"Y");
  hzoom_before->SetXTitle("");
  hzoom_before->SetYTitle("");
  hzoom_before->GetXaxis()->SetRangeUser(xmin,xmax);
  hzoom_before->Draw();

  TH1F* hzoom_after = (TH1F*)hzpt_after->Clone("hzoom_after");
  hzoom_after->SetLabelSize(xlabelsize*0.7/canvassize,"X");
  hzoom_after->SetLabelSize(ylabelsize*0.7/canvassize,"Y");
  hzoom_after->SetXTitle("");
  hzoom_after->SetYTitle("");
  hzoom_after->GetXaxis()->SetRangeUser(xmin,xmax);
  hzoom_after->SetFillStyle(3004);
  hzoom_after->SetFillColor(kRed-7);
  hzoom_after->Draw("histsame");

  c1->Draw("Same");

  int bins=hzpt_before->GetNbinsX()+1;
  bool findFirstBin=false;
  for(int i=hzpt_before->GetNbinsX()+1; i>=0;i--)
    {
      int diff = hzpt_before->GetBinContent(i) - hzpt_after->GetBinContent(i);
      cout << i << ": " << diff << endl;
      if(diff==0 && !findFirstBin)
	bins=i;
      else
	findFirstBin=true;
    }

  cout << "First bin that the two histograms are equal is bin " << bins << endl;
  

}
