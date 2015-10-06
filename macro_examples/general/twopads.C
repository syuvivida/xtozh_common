#include <TH1.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TStyle.h>

void twopads(TH1F* horiginal, float xmin, float xmax)
{
  gStyle->SetOptStat(0);
  TCanvas *c1 = new TCanvas("c1","",500,500);
  horiginal->Draw();
  float xlabelsize=horiginal->GetLabelSize("X"); 
  float ylabelsize=horiginal->GetLabelSize("Y");
  float canvassize = 0.5;
  float x1=0.4;
  float y1=0.35;
  TPad *subpad = new TPad("subpad","",
			  x1,y1,
			  x1+canvassize,y1+canvassize);
  subpad->Draw();
  subpad->cd();
  TH1F* hzoom = (TH1F*)horiginal->Clone("hzoom");
  hzoom->SetLabelSize(xlabelsize*0.7/canvassize,"X");
  hzoom->SetLabelSize(ylabelsize*0.7/canvassize,"Y");
  hzoom->SetXTitle("");
  if(xmax>xmin)
    hzoom->GetXaxis()->SetRangeUser(xmin,xmax);
  hzoom->Draw();
  c1->Draw("Same");

} 
