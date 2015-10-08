#include <TH1.h>
#include <TCanvas.h>
#include <string>
#include <vector>
#include <iostream>
#include <TFile.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TSystem.h>
#include "setNCUStyle.C"
using namespace std;

void displayMultipleHistos(vector<string> files,
			   vector<string> legs,
			   string histo,
			   string title="",
			   string title2="test",
			   float xmin=-9999, float xmax=-9999, 
			   bool rebin=true,
			   float ymin=0, float ymax=1.7,
			   float x1NDC=0.181452,
			   float y1NDC=0.662447,
			   float x2NDC=0.330645,
			   float y2NDC=0.883966)
{
  const unsigned int nfiles = files.size();
  TH1F* h[nfiles];
  setNCUStyle();
  TCanvas* c1 = new TCanvas("c1","",500,500);
  float max=-999;
  gStyle->SetOptStat(0);
  gStyle->SetTitleFontSize(0.07);
  int markerStyle[5]={20,21,22,23,29};
  int color[8]={kRed, kOrange-3, kYellow, kGreen+2, kAzure+1, kBlue, kViolet-3};
  vector<double> integrals; 
  for(unsigned i=0; i<nfiles; i++)
    {
      TFile *f = TFile::Open(files[i].data());
      cout << "Opening " << files[i].data() << endl;
      h[i] = dynamic_cast<TH1F*>(gDirectory->Get(histo.data()));
      h[i]->SetName(Form("h%d",i));
      if(rebin)h[i]->Rebin(4);
      h[i]->SetTitle("");
      if(title2!="test")
	h[i]->SetXTitle(title2.data());
      integrals.push_back(h[i]->Integral(0,h[i]->GetNbinsX()+1));
      h[i]->Scale(1.0/integrals[i]);
      h[i]->SetMinimum(ymin); 
      if(xmax>xmin)
	h[i]->GetXaxis()->SetRangeUser(xmin,xmax);
      h[i]->SetMarkerStyle(markerStyle[i%5]);
      h[i]->SetMarkerColor(color[i%8]);
      h[i]->SetLineColor(color[i%8]);
      h[i]->SetLineStyle(1+i);
      h[i]->GetXaxis()->SetTitleOffset(1.2);
      h[i]->GetYaxis()->SetTitleOffset(1.4);
      h[i]->SetYTitle("Arbitrary Unit");
      if(h[i]->GetMaximum()>max)
	max=h[i]->GetMaximum();
    }

  for(unsigned int i=0; i<nfiles; i++)
    {
      h[i]->SetMaximum(ymax*max);
      if(i==0)
	  h[i]->Draw("histe");

      else
	h[i]->Draw("histesame");
    }

  // compute the fraction of DY and GF
  int frac_GF = 100*integrals[nfiles-1]/integrals[nfiles-2];
  int frac_DY = 100 - frac_GF;
  string temp1= Form("%d",frac_DY);
  string temp2= Form(" %d",frac_GF);

  legs[nfiles-2] += " (" +  temp1 + "% DY" + ", " + temp2 + "% GF)"; 

  TLegend* leg = new TLegend(x1NDC,y1NDC,x2NDC,y2NDC) ;

  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetHeader(title.data());
  leg->AddEntry((TObject*)0, "","");
  for(unsigned i=0; i < nfiles; i++)
    {
      leg->AddEntry(h[i],legs[i].data(),"lpf");
    }


  leg->Draw("same");

  TString dirname ="compareHistos";
  gSystem->mkdir(dirname.Data());
  TString outputFile=gSystem->GetFromPipe(Form("file=%s; histo=%s; test=${file##*Radion}; test2=${test%%.root*}; test3=${histo##*h_}; echo \"${test2}_${test3}\"",
					       files[0].data(),histo.data()));
  TString tempout = outputFile;
  cout << tempout << endl;
  TString prefix=dirname + "/" + tempout;
  TString temp= prefix +  ".eps";
  c1->Print(temp.Data());
  temp= prefix + ".gif";
  c1->Print(temp.Data());
  temp= prefix + ".pdf";
  c1->Print(temp.Data());

}
