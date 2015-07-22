#include <TH1.h>
#include <TMinuit.h>
#include <TStyle.h>
#include <TLegend.h>                    // this one is fit_chi2_err.C without theory error
#include <TCanvas.h>
#include <iostream>
#include <TH2.h>

TH1D* signal_pos;
TH1D* background_pos1;
TH1D* background_pos2;
TH1D* data;
TH1D* fit_result;

using namespace std;


// -- returns prediction and error on the prediction based on stat unc in templates
Double_t ftotal_pos(Double_t *x, Double_t *par, Double_t& err) {  
//Double_t ftotal_pos(Double_t *x, Double_t *par) {  
  Double_t xx = x[0];
  Int_t bin_signal = signal_pos->GetXaxis()->FindBin(xx);
  Int_t bin_background1 = background_pos1->GetXaxis()->FindBin(xx);
  Int_t bin_background2 = background_pos2->GetXaxis()->FindBin(xx);

  Double_t sr = par[0]*signal_pos->GetBinContent(bin_signal);
  Double_t br1 = par[1]*background_pos1->GetBinContent(bin_background1);
  Double_t br2 = (1-par[0]-par[1])*background_pos2->GetBinContent(bin_background2);

  double sigerr = signal_pos->GetBinError(bin_signal);
  double bkgerr1 = background_pos1->GetBinError(bin_background1); 
  double bkgerr2 = background_pos2->GetBinError(bin_background2);
 
  err = sqrt((1-par[0]-par[1])*(1-par[0]-par[1])*bkgerr2*bkgerr2 +
	     par[1]*par[1]*bkgerr1*bkgerr1 + 
	     par[0]*par[0]*sigerr*sigerr);
 

  return sr + br1 + br2 ;


}



// -- Defines Chi2 to minimize taking into account error on the prediction from templates stat uncertainties
void fcn(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
  Double_t delta2;
  Double_t sum=0;

  for (int i=1; i<= data->GetNbinsX(); i++) {
    Double_t data_value = data->GetBinContent(i);
    if(data_value==0)continue;
    Double_t data_err = data->GetBinError(i);
    Double_t temp_x[2];
    Double_t center = data->GetBinCenter(i);
    temp_x[0]=center;
    Double_t sr, br, serr, berr;
    Double_t theory_err;
    Double_t theory_value = ftotal_pos(temp_x,par,theory_err);
    
    // delta2 = (theory_value-data_value)*(theory_value-data_value)/
    //   ( pow(data_err,2) + pow(theory_err,2));
    delta2 = (theory_value-data_value)*(theory_value-data_value)/
      ( pow(data_err,2) /*+ pow(theory_err,2)*/  );

    sum +=  delta2;
    
    // for this round, set the fit content
    fit_result->SetBinContent(i,theory_value);
    fit_result->SetBinError(i,theory_err);
   

  }
  f=sum  ;

}



// -- main function
void fit_chi2_err(TH1F* dataInput, TH1F* sigTemplate, TH1F* bkgTemplate1, TH1F* bkgTemplate2, std::string prefix,
 		Double_t& sigFrac, Double_t& sigFrac_intial ,Double_t& sigFrac_err, Double_t& bkg1Frac, Double_t& bkg1Frac_intial , Double_t& bkg1Frac_err, Double_t& FitChi2)
//void fit_chi2_err(TH1F* dataInput, TH1F* sigTemplate, TH1F* bkgTemplate, Double_t& sigFrac, Double_t& sigFrac_err)
//void fit_chi2_err(TH1F* dataInput, TH1F* sigTemplate, TH1F* bkgTemplate, Double_t& sigFrac, Double_t& sigFrac_err, Double_t& FitChi2)
{
  gStyle->SetOptStat(kFALSE);
  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetFrameBorderMode(0);

  Double_t scale=1.;




  data = (TH1D*)dataInput->Clone();
  data->SetName("data");
  data->SetLineColor(1);
  data->SetMarkerColor(1);
  data->SetXTitle("SigmaIetaIeta");
  data->Sumw2();
//  scale = 1.0/(Double_t)data->Integral(0,1000); 
  scale = 1.0/(Double_t)data->Integral();
//  scale = 1.0/(Double_t)data->Integral();//changed by Yu-hsiang
  cout << "scale for data = " << scale << endl;
  data->Scale(scale);


  fit_result = (TH1D*)dataInput->Clone();
  fit_result->SetName("fit_result");
  fit_result->SetLineColor(8); 
  fit_result->SetMarkerColor(8);
  fit_result->SetLineStyle(2);
  fit_result->Sumw2();
  fit_result->Reset();


  signal_pos = (TH1D*)sigTemplate->Clone();
  signal_pos->SetName("signal_pos");
  signal_pos->SetLineColor(2);
  signal_pos->SetMarkerColor(2);
  signal_pos->SetFillColor(2);
  signal_pos->SetXTitle("SigmaIetaIeta");
  signal_pos->Sumw2();
//  scale = 1.0/(Double_t)signal_pos->Integral(0,1000); 
  scale = 1.0/(Double_t)signal_pos->Integral();
//  scale = 1.0/(Double_t)signal_pos->Integral();//changed by Yu-hsiang
  cout << "scale for signal template = " << scale << endl;
  signal_pos->Scale(scale);


  background_pos1 = (TH1D*)bkgTemplate1->Clone();
  background_pos1->SetName("background_pos1");
  background_pos1->SetLineColor(4);
  background_pos1->SetMarkerColor(4);
  background_pos1->SetFillColor(4);
  background_pos1->SetXTitle("SigmaIetaIeta");
  background_pos1->Sumw2();
//  scale = 1.0/(Double_t)background_pos->Integral(0,1000); 
  scale = 1.0/(Double_t)background_pos1->Integral();
//  scale = 1.0/(Double_t)background_pos->Integral();//changed by Yu-hsiang
  cout << "scale for background template = " << scale << endl;
  background_pos1->Scale(scale);

  background_pos2 = (TH1D*)bkgTemplate2->Clone();
  background_pos2->SetName("background_pos2");
  background_pos2->SetLineColor(7);
  background_pos2->SetMarkerColor(7);
  background_pos2->SetFillColor(7);
  background_pos2->SetXTitle("SigmaIetaIeta");
  background_pos2->Sumw2();
  scale = 1.0/(Double_t)background_pos2->Integral();
  cout << "scale for background template = " << scale << endl;
  background_pos2->Scale(scale);


//////////  count the number of points and the dof   



  int Number_of_points =0 ;

//  for (int i=1;i<2000;i++){ //the Sig or Bkg histo has 2000 bins
   for (int i=1;i<= sigTemplate->GetNbinsX();i++){ 
    if( ( ( bkgTemplate2->GetBinContent(i) ) != 0) || ( ( bkgTemplate1->GetBinContent(i) ) != 0) || ( ( sigTemplate->GetBinContent(i) ) != 0 ) ){
    Number_of_points = Number_of_points+1;

    }
  }
cout<<"Number_of_points:"<<Number_of_points<<endl;
int dof = Number_of_points-1 ;//dof=Number_of_points - free_par
                              //and in this case we normalize it so free_par =1
cout<<"dof of this fit:"<<dof<<endl;


  //cout<<"sigFrac_intial in chi2 macro: "<< sigFrac_intial <<endl;
  //cout<< "bkg1Frac_intial in chi2 macro: " << bkg1Frac_intial<< endl;


/////////



  TMinuit *gMinuit = new TMinuit(2);  //initialize TMinuit with a maximum of 5 (1param??) params
  gMinuit->SetFCN(fcn); // sets function to minimize: fcn is Chi2 with errors on templates

  Double_t arglist[10];
  Int_t ierflg = 0; // status flag, it is 0 when ereything goes fine

  // -- sets error
  arglist[0] = 1;
  gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

  // set first parameter
  Double_t vstart = sigFrac_intial;
  //Double_t vstart = 0.48 ;//0.11;//intial value
  Double_t step = 0.001;
  gMinuit->mnparm(0, "fsig", vstart, step, 0,1,ierflg);

  // set second parameter
    vstart = bkg1Frac_intial;
//    vstart = 0.4; //0.69;//intial value
    step = 0.001;
  gMinuit->mnparm(1, "fbk1", vstart, step, 0,1,ierflg);

  // Now ready for minimization step
  arglist[0] = 1000;
  arglist[1] = 0.01;
  gMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

  Double_t fsig=0;
  Double_t fsigerr=0;
  Double_t fbk1=0;
  Double_t fbk1err=0;
  Double_t chi2 = 0;


  if ( ierflg == 0 ) 
    {

      // Print results
      Double_t amin,edm,errdef;
      Int_t nvpar,nparx,icstat;
      gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
      gMinuit->mnprin(3,amin);
      chi2 = (gMinuit->fAmin)/dof;
      gMinuit->GetParameter(0, fsig, fsigerr );  
      gMinuit->GetParameter(1, fbk1, fbk1err );
      cout << "Fsig = " << fsig << " +- " << fsigerr << endl;
      cout << "Fbk1 = " << fbk1 << " +- " << fbk1err << endl;
      cout << "Chi2/degree of freedom = " << chi2 <<endl;

      TCanvas* c1 = new TCanvas("c1","",500,500);

  TH2F *htmp2 = new TH2F("htmp2","",100, 0., 0.025, 100, 0., data->GetMaximum()*1.25);

  htmp2->SetNdivisions(505,"XY");
  htmp2->SetXTitle("SigmaIetaIeta");
  htmp2->SetYTitle("A.U.");
  htmp2->SetLineColor(1); 

//     htmp2->Draw();


  TH1D* signal_display = (TH1D*)signal_pos->Clone();
  signal_display->SetName("signal_display");
  Double_t scale_sig = signal_display->Integral();
  signal_display->Scale(fsig/scale_sig);
  signal_display->SetFillStyle(3001);

      
  TH1D* background_display1 = (TH1D*)background_pos1->Clone();
  background_display1->SetName("background_display1");
  Double_t scale_background1 = background_display1->Integral();
  background_display1->Scale(fbk1/scale_background1);
  background_display1->SetFillStyle(3001);

  TH1D* background_display2 = (TH1D*)background_pos2->Clone();
  background_display2->SetName("background_display2");
  Double_t scale_background2 = background_display2->Integral();
  background_display2->Scale((1-fsig-fbk1)/scale_background2);
  background_display2->SetFillStyle(3001);

  fit_result->GetXaxis()->SetRangeUser(100,600);
  fit_result->GetYaxis()->SetRangeUser(0.,0.2);
  fit_result->SetXTitle("mass of hadronic top");
//  fit_result->SetXTitle("#sigma_{i#eta i#eta}");
  fit_result->SetTitleSize(0.04,"X");
  fit_result->GetXaxis()->SetLabelSize(0.04);

  fit_result->Draw("histe");
  data->Draw("esame");
  signal_display->Draw("histsame");
  background_display1->Draw("histsame");
  background_display2->Draw("histsame");

  char result[300];
  sprintf(result,"fsig = %.3lf #pm %.3lf",fsig,fsigerr );
  sigFrac = fsig;
  sigFrac_err = fsigerr ;
  bkg1Frac =fbk1;
  bkg1Frac_err =fbk1err;

  FitChi2 = chi2;

  TLegend* leg = new TLegend(0.9,0.6,0.6,0.9);
  leg->SetHeader(result);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.035);
  leg->SetBorderSize(0);
  leg->AddEntry(data,"data");
  leg->AddEntry(fit_result,"fit");
  leg->AddEntry(signal_display,"signal template");
  leg->AddEntry(background_display1,"background template1");
  leg->AddEntry(background_display2,"background template2");
  leg->Draw("same");

      std::string outputFile = "plots_of_fit_results/"+  prefix + ".eps";
      c1->Print(outputFile.data());

//      outputFile = prefix + ".gif";
      outputFile = "plots_of_fit_results/"+  prefix + ".gif";
      c1->Print(outputFile.data());

      outputFile = "plots_of_fit_results/"+ prefix + ".C";
      c1->Print(outputFile.data());

      outputFile = "plots_of_fit_results/"+ prefix + ".pdf";
      c1->Print(outputFile.data());

    }

    
  else{
    cout << "Fit failed!\n";
    sigFrac = 0;
    sigFrac_err = 0;
  }

  
  return;

}



