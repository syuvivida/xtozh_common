#include <TH1.h>
#include <TCanvas.h>
#include <string>
#include <vector>
#include <TFile.h>
#include <TLegend.h>
#include <TStyle.h>

using namespace std;

void displayMultipleHistos(vector<string> files,
			   vector<string> legs,
			   string histo,
			   string title="",
			   string title2="test",
			   float xmin=-9999, float xmax=-9999, 
			   float ymin=0, float ymax=1.5)
{
  const unsigned int nfiles = files.size();
  TH1F* h[nfiles];
  TCanvas* c1 = new TCanvas("c1","",500,500);
  float max=-999;
  gStyle->SetOptStat(0);
  gStyle->SetTitleFontSize(0.07);
  for(unsigned i=0; i<nfiles; i++)
    {
      TFile *f = TFile::Open(files[i].data());
      cout << "Opening " << files[i].data() << endl;
      h[i] = dynamic_cast<TH1F*>(gDirectory->Get(histo.data()));
      h[i]->SetName(Form("h%d",i));
      h[i]->SetTitle("");
      if(title2!="test")
	h[i]->SetXTitle(title2.data());
      h[i]->Scale(1.0/h[i]->Integral());
      h[i]->SetMinimum(ymin); 
      if(xmax>xmin)
	h[i]->GetXaxis()->SetRangeUser(xmin,xmax);
      xtitle = h[i]->GetXaxis()->GetTitle();
      h[i]->SetMarkerStyle(20+i);
      h[i]->SetMarkerColor(2+i);
      h[i]->SetLineColor(2+i);
      h[i]->GetXaxis()->SetTitleOffset(1.2);
      h[i]->GetYaxis()->SetTitleOffset(1.4);

      if(h[i]->GetMaximum()>max)
	max=h[i]->GetMaximum();
    }

  for(unsigned i=0; i<nfiles; i++)
    {
      h[i]->SetMaximum(ymax*max);
      // h[i]->SetXTitle(xtitle.data());
      if(i==0)
	  h[i]->Draw("histe");

      else
	h[i]->Draw("histesame");
    }

  TLegend* leg = new TLegend(0.181452,0.662447,0.330645,0.883966) ;

  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetHeader(title.data());
  for(i=0; i < nfiles; i++)
    {
      leg->AddEntry(h[i],legs[i].data(),"lpf");
    }


  leg->Draw("same");

  string dirname ="compareHistos";
  gSystem->mkdir(dirname.data());
  TString outputFile=gSystem->GetFromPipe(Form("file=%s; histo=%s; test=${file##*Radion}; test2=${test%%.root*}; test3=${histo##*h_}; echo \"${test2}_${test3}\"",
					       files[0].data(),histo.data()));
  string tempout = outputFile;
  cout << tempout << endl;
  string prefix=dirname + "/" + tempout;
  string temp= prefix +  ".eps";
  c1->Print(temp.data());
  temp= prefix + ".gif";
  c1->Print(temp.data());
  temp= prefix + ".pdf";
  c1->Print(temp.data());

}
