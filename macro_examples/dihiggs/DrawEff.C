#include <TGraphErrors.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <TCanvas.h>
#include <TLegend.h>
#include <TAxis.h>
using namespace std;

struct eff
{
  float value;
  float error;
};

void DrawEff()
{
  const int neff=4;
  vector<eff> csv[neff];
  const int nmass=11;
  ifstream fin;
  fin.open("eff.dat");
  for(int i=0;i<nmass;i++)
    {
      for(int i=0;i<neff;i++){
	eff temp_eff;
	fin >> temp_eff.value >> temp_eff.error;
	
	csv[i].push_back(temp_eff);

      }

    }

  float   y[neff][nmass];
  float  ey[neff][nmass];

  for(int i=0;i<neff;i++)
    for(unsigned j=0; j<nmass; j++)
      {
	cout << csv[i][j].value << " +- " << 
	  csv[i][j].error << endl;
	y[i][j]=csv[i][j].value;
	ey[i][j]=csv[i][j].error;
	
      }

  float x[nmass]={
    1000,
    1200,
    1400,
    1600,
    1800,
    2000,
    2500,
    3000,
    3500,
    4000,
    4500
  };

  float ex[nmass];
  for(int i=0;i<nmass;i++)
    {
      ex[i]=50;
    }


  TGraphErrors* csveff[neff];
  int markerstyle[neff]={20,21,29,31};
  int color[neff]={kRed,kBlue,kMagenta,kGreen+2};
  for(int i=0;i<neff;i++)
    {
      csveff[i] = new TGraphErrors(nmass,x,y[i],ex,ey[i]);
      csveff[i]->SetName(Form("csveff%d",i));
      csveff[i]->SetLineColor(color[i]);
      csveff[i]->SetMarkerStyle(markerstyle[i]);
      csveff[i]->SetMarkerColor(color[i]);
      csveff[i]->SetMarkerSize(1.5);
      csveff[i]->SetMaximum(0.45);
      csveff[i]->SetMinimum(0);
      csveff[i]->SetTitle("Signal Event Efficiency");
      csveff[i]->GetXaxis()->SetTitle("Mass of Graviton [GeV]");
      csveff[i]->GetXaxis()->SetTitleOffset(1.4);
      csveff[i]->GetYaxis()->SetTitle("Efficiency");
      csveff[i]->GetYaxis()->SetTitleOffset(1.4);
    }

  std::string legs[4]={"#geq 2 FatJet_{CSV}","#geq 2 SubJet_{CSV}","#geq 3 SubJet_{CSV}","#geq 4 SubJet_{CSV}",};
  TCanvas* c1 = new TCanvas("c1","",500,500);
				
  csveff[1]->Draw("acp");
  csveff[0]->Draw("cpsame");
  csveff[2]->Draw("cpsame");
  csveff[3]->Draw("cpsame");
  TLegend* leg = new TLegend(0.596774,0.664557,0.747984,0.886076) ;

  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.045);
  for(int i=0; i < neff  ; i++)
    {
      leg->AddEntry(csveff[i],legs[i].data(),"l");
    }


  leg->Draw("same");
  c1->Print("csveff.eps");
  c1->Print("csveff.pdf");
  c1->Print("csveff.png");


}
