#include "setNCUStyle.C"
#include "TCanvas.h"
#include "TH1.h"
#include "TFile.h"

#include <string>
#include <iostream>
using namespace std;

const int NFILES=6;

const Double_t xSecDY100 = 139.4*1.23;
const Double_t xSecDY200 = 42.75*1.23;
const Double_t xSecDY400 = 5.497*1.23;
const Double_t xSecDY600 = 2.21*1.23;
const Double_t xSecDYNLO = 6025.2;
const Double_t xSecDYLO  = 4895;
const Double_t dataLumi  = 3000;
const Double_t crossSection[NFILES]={
  xSecDYLO,
  xSecDYNLO,
  xSecDY100,
  xSecDY200,
  xSecDY400,
  xSecDY600
};

const string infiles[NFILES]={
  "DYJets_LO.root",
  "DYJets_NLO.root",
  "DYJetsToLL_M-50_HT-100to200_13TeV.root",
  "DYJetsToLL_M-50_HT-200to400_13TeV.root",
  "DYJetsToLL_M-50_HT-400to600_13TeV.root",
  "DYJetsToLL_M-50_HT-600toInf_13TeV.root"
};

int color[8]={kRed, kOrange-3, kYellow, kGreen+2, kAzure+1, kBlue, kViolet-3};



void NLOLO_corr(string histo)
{
  setNCUStyle();
  TFile *inf[NFILES];
  TH1F* hzpt[NFILES];
  TH1F* heve[NFILES];

  for(int i=0; i<NFILES; i++)
    {
      inf[i]= new TFile(infiles[i].data());
      heve[i] = (TH1F*)inf[i]->FindObjectAny("hevent");
      heve[i]->SetName(Form("heve%d",i));
      hzpt[i] = (TH1F*)inf[i]->FindObjectAny(Form("%s_before",histo.data()));
      hzpt[i]->SetName(Form("%s%d",histo.data(),i));
      hzpt[i]->Sumw2();
      double scale = dataLumi*crossSection[i]/heve[i]->Integral();
      cout << "scale = " << scale << endl;
      hzpt[i]->SetLineColor(color[i]);
      hzpt[i]->Scale(scale);
    }

  TH1F* hzpt_all = (TH1F*)hzpt[0]->Clone(Form("%s_all",histo.data()));
  hzpt_all->Reset();
  hzpt_all->Sumw2();
  hzpt_all->SetLineColor(color[NFILES]);
  
  for(int i=2; i<NFILES; i++)
    {
      hzpt_all->Add(hzpt[i]);
    }


  TH1F* hratio = (TH1F*)hzpt[0]->Clone("hratio");
  hratio->Reset();
  hratio->Divide(hzpt[1],hzpt[0]);

  TH1F* hratio2 = (TH1F*)hzpt[0]->Clone("hratio2");
  hratio2->Reset();
  hratio2->Divide(hzpt[1],hzpt_all);
  
  TCanvas* c1 = new TCanvas("c1","",1000,1000);
  c1->Divide(2,2);
  c1->cd(1);
  hzpt[1]->Draw();
  hzpt[0]->Draw("same");
  c1->cd(2);
  hzpt[1]->Draw();
  hzpt_all->Draw("same");

  c1->cd(3);
  hratio->Draw();
  c1->cd(4);
  hratio2->Draw();
  
  TFile* outFile = new TFile(Form("NLOLO_corr_%s.root",histo.data()),"recreate");

  hzpt[0]->Write("DYJetLO");
  hzpt[1]->Write("DYJetNLO");
  hzpt_all->Write("DYLOHTAll");
  hratio->Write();
  hratio2->Write();

  outFile->Close();
    

}
