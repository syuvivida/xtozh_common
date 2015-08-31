#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <string>
#include <vector>
#include <TFile.h>
#include <TLegend.h>

using namespace std;

void displayMultipleEffs(vector<string> files,
		   vector<string> legs,
		   string histo,
		   string title="",
		   string output="test",
		   string notation="", 
		   float xmin=-1, float xmax=-1, float ymin=0, float ymax=1.2)
{
  const unsigned int nfiles = files.size();
  TGraphAsymmErrors* h[nfiles];
  TCanvas* c1 = new TCanvas("c1","",500,500);
  for(unsigned i=0; i<nfiles; i++)
    {
      TFile *f = TFile::Open(files[i].data());
      cout << "Opening " << files[i].data() << endl;
      h[i] = dynamic_cast<TGraphAsymmErrors*>(gDirectory->Get(histo.data()));
      h[i]->SetName(Form("h%d",i));
      h[i]->SetMinimum(ymin);
      h[i]->SetMaximum(ymax);
      h[i]->SetMarkerColor(2+i);
      h[i]->SetLineColor(2+i);
      h[i]->GetXaxis()->SetTitleOffset(1.4);
      h[i]->GetYaxis()->SetTitleOffset(1.4);

      if(i==0)
	h[i]->Draw("ap");
      else
	h[i]->Draw("psame");
    }


  TLegend* leg = new TLegend(0.159194,0.236287,0.306452,0.457806) ;

  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetHeader(title.data());
  for(i=0; i < nfiles; i++)
    {
      leg->AddEntry(h[i],legs[i].data(),"lf");
    }


  leg->Draw("same");

  string dirname ="compareEff";
  gSystem->mkdir(dirname.data());
  string temp= dirname + "/" + histo +  ".eps";
  c1->Print(temp.data());
  temp= dirname + "/" + histo + ".gif";
  c1->Print(temp.data());
  temp= dirname + "/" + histo + ".pdf";
  c1->Print(temp.data());

}
