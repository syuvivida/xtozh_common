#include <TCanvas.h>
#include <TArrow.h>
#include <TLatex.h>
#include <TArc.h>
#include <string>

using namespace std;

void drawDecayAngle(float angle=45)
{

  TCanvas* c1 = new TCanvas("c1","",500,500);
  c1->Range(0,0,1,1);
  float b1x = 0.3+sqrt(0.08)*TMath::Cos(TMath::DegToRad()*angle);
  float b1y = 0.5+sqrt(0.08)*TMath::Sin(TMath::DegToRad()*angle);
  TArrow* b1 = new TArrow(0.3,0.5,b1x,b1y,0.06,"|>");
  b1->SetLineStyle(2);
  b1->SetLineWidth(3);

  float b2x = 0.29-sqrt(0.08)*TMath::Cos(TMath::DegToRad()*angle);
  float b2y = 0.49-sqrt(0.08)*TMath::Sin(TMath::DegToRad()*angle);

  TArrow* b2 = new TArrow(0.29,0.49,b2x,b2y,0.06,"|>");
  b2->SetLineStyle(2);
  b2->SetLineWidth(3);

  TArrow* m1 = new TArrow(0.295,0.495,0.7,0.495,0.06,"|>");
  m1->SetLineStyle(1);
  m1->SetLineWidth(4);
  m1->SetLineColor(2);
  m1->SetFillColor(2);
  
  b1->Draw();
  b2->Draw();
  m1->Draw();

  TLatex* bt1 = new TLatex(b1x,b1y+0.05,"b quark");
  bt1->Draw();
  TLatex* bt2 = new TLatex(b2x,b2y-0.08,"#bar{b} quark");
  bt2->Draw();
  TLatex* mt1 = new TLatex(0.75,0.495,"H^{0}");
  mt1->Draw();
  TLatex* tt1 = new TLatex(0.4,0.55,"#theta_{1}");
  tt1->Draw();

  TArc* arc = new TArc(0.295,0.495,0.1,0,angle);
  arc->SetLineWidth(2);
  arc->SetLineColor(4);
  arc->Draw();

  string prefix = Form("decayAngle%d",(int)angle);
  c1->Print((prefix+".pdf").data());
  c1->Print((prefix+".gif").data());
  c1->Print((prefix+".C").data());

}
