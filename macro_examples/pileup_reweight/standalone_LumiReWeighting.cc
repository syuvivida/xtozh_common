/**
   \class    standalone_LumiReWeighting standalone_LumiReWeighting.h "PhysicsTools/Utilities/interface/standalone_LumiReWeighting.h"
   \brief    Class to provide lumi weighting for analyzers to weight "flat-to-N" MC samples to data

   This class will trivially take two histograms:
   1. The generated "flat-to-N" distributions from a given processing (or any other generated input)
   2. A histogram generated from the "estimatePileup" macro here:

   https://twiki.cern.ch/twiki/bin/view/CMS/LumiCalc#How_to_use_script_estimatePileup

   and produce weights to convert the input distribution (1) to the latter (2).

   \author Shin-Shan Eiko Yu, Salvatore Rappoccio, modified by Mike Hildreth
  
*/
#ifndef standalone_LumiReWeighting_cxx
#define standalone_LumiReWeighting_cxx
#include "TH1.h"
#include "TFile.h"
#include <string>
#include "standalone_LumiReWeighting.h"

//=======================================================
// For 2012 Data and MC
//=======================================================

Double_t Summer2012_S10[60] = {
  2.560E-06,
  5.239E-06,
  1.420E-05,
  5.005E-05,
  1.001E-04,
  2.705E-04,
  1.999E-03,
  6.097E-03,
  1.046E-02,
  1.383E-02,
  1.685E-02,
  2.055E-02,
  2.572E-02,
  3.262E-02,
  4.121E-02,
  4.977E-02,
  5.539E-02,
  5.725E-02,
  5.607E-02,
  5.312E-02,
  5.008E-02,
  4.763E-02,
  4.558E-02,
  4.363E-02,
  4.159E-02,
  3.933E-02,
  3.681E-02,
  3.406E-02,
  3.116E-02,
  2.818E-02,
  2.519E-02,
  2.226E-02,
  1.946E-02,
  1.682E-02,
  1.437E-02,
  1.215E-02,
  1.016E-02,
  8.400E-03,
  6.873E-03,
  5.564E-03,
  4.457E-03,
  3.533E-03,
  2.772E-03,
  2.154E-03,
  1.656E-03,
  1.261E-03,
  9.513E-04,
  7.107E-04,
  5.259E-04,
  3.856E-04,
  2.801E-04,
  2.017E-04,
  1.439E-04,
  1.017E-04,
  7.126E-05,
  4.948E-05,
  3.405E-05,
  2.322E-05,
  1.570E-05,
  5.005E-06};



double Data2012[60]={
  10989,
  18043.9,
  35535.2,
  241453,
  545770,
  3.62943e+06,
  2.02238e+07,
  6.09042e+07,
  1.43008e+08,
  2.76202e+08,
  4.71697e+08,
  7.05419e+08,
  8.8683e+08,
  9.9568e+08,
  1.06932e+09,
  1.1227e+09,
  1.15032e+09,
  1.15493e+09,
  1.14874e+09,
  1.13384e+09,
  1.10964e+09,
  1.08029e+09,
  1.04825e+09,
  1.00766e+09,
  9.48352e+08,
  8.64377e+08,
  7.58888e+08,
  6.41241e+08,
  5.2147e+08,
  4.07912e+08,
  3.06859e+08,
  2.22047e+08,
  1.54462e+08,
  1.03124e+08,
  6.60195e+07,
  4.06523e+07,
  2.43343e+07,
  1.44703e+07,
  8.83989e+06,
  5.7661e+06,
  4.12227e+06,
  3.22636e+06,
  2.70124e+06,
  2.35356e+06,
  2.09051e+06,
  1.86979e+06,
  1.67285e+06,
  1.49191e+06,
  1.32377e+06,
  1.16734e+06,
  1.0223e+06,
  888616,
  766289,
  655304,
  555539,
  466739,
  388507,
  320313,
  261511,
  211370
};


double Data2012Up[60]={
  10339.2,
  16473.8,
  29729.8,
  161564,
  475302,
  1.84602e+06,
  1.2363e+07,
  4.04539e+07,
  9.87285e+07,
  1.99084e+08,
  3.47697e+08,
  5.50585e+08,
  7.51522e+08,
  8.88065e+08,
  9.72276e+08,
  1.03377e+09,
  1.07722e+09,
  1.09755e+09,
  1.09965e+09,
  1.09336e+09,
  1.07943e+09,
  1.05745e+09,
  1.03092e+09,
  1.00224e+09,
  9.67166e+08,
  9.17297e+08,
  8.46504e+08,
  7.5561e+08,
  6.51442e+08,
  5.4249e+08,
  4.3621e+08,
  3.38536e+08,
  2.53615e+08,
  1.83402e+08,
  1.27897e+08,
  8.58818e+07,
  5.55299e+07,
  3.47171e+07,
  2.12236e+07,
  1.29532e+07,
  8.13578e+06,
  5.43669e+06,
  3.95037e+06,
  3.11756e+06,
  2.62013e+06,
  2.28914e+06,
  2.04017e+06,
  1.83305e+06,
  1.64933e+06,
  1.48086e+06,
  1.32413e+06,
  1.17775e+06,
  1.04129e+06,
  914643,
  797799,
  690771,
  593515,
  505898,
  427677,
  358497
};

double Data2012Down[60]={
  11724.5,
  19902.8,
  44863.7,
  339155,
  743895,
  7.00539e+06,
  3.24477e+07,
  9.23379e+07,
  2.06514e+08,
  3.84946e+08,
  6.33653e+08,
  8.68168e+08,
  1.01481e+09,
  1.10526e+09,
  1.17055e+09,
  1.20756e+09,
  1.21589e+09,
  1.20997e+09,
  1.19401e+09,
  1.16725e+09,
  1.1346e+09,
  1.09849e+09,
  1.05087e+09,
  9.79592e+08,
  8.79594e+08,
  7.57304e+08,
  6.24966e+08,
  4.94228e+08,
  3.74304e+08,
  2.71514e+08,
  1.88621e+08,
  1.25304e+08,
  7.94667e+07,
  4.8195e+07,
  2.82241e+07,
  1.63195e+07,
  9.66831e+06,
  6.13806e+06,
  4.30997e+06,
  3.34351e+06,
  2.78819e+06,
  2.42188e+06,
  2.14265e+06,
  1.90621e+06,
  1.69414e+06,
  1.49911e+06,
  1.31834e+06,
  1.151e+06,
  996917,
  856073,
  728476,
  614028,
  512470,
  423360,
  346081,
  279861,
  223811,
  176962,
  138301,
  106809
};



standalone_LumiReWeighting::standalone_LumiReWeighting(int mode) {

  std::cout << "=======================================================================" << std::endl;
  
  std::vector<double> MC_distr;
  std::vector<double> Lumi_distr;

  MC_distr.clear();
  Lumi_distr.clear();
  switch (mode)
    {
    case 0:
      std::cout << "Using central value " << std::endl;
      break;
    case 1:
      std::cout << "Using +1 sigma 5% value " << std::endl;
      break;
    case -1:
      std::cout << "Using -1 sigma 5% value " << std::endl;
      break;
    default:
      std::cout << "Using central value " << std::endl;
      break;
    } // end of switch

  Int_t NBins = 60;
  
  for( int i=0; i< NBins; ++i) {
    switch (mode){
    case 0:
      Lumi_distr.push_back(Data2012[i]);
      break;
    case 1:
      Lumi_distr.push_back(Data2012Up[i]);
      break;
    case -1:
      Lumi_distr.push_back(Data2012Down[i]);
      break;
    default:
      Lumi_distr.push_back(Data2012[i]);
      break;
    } // end of switch

    MC_distr.push_back(Summer2012_S10[i]);
  } // end of loop over bins

  // no histograms for input: use vectors
  
  // now, make histograms out of them:

  // first, check they are the same size...

  if( MC_distr.size() != Lumi_distr.size() ){   
    std::cout << "MC_distr.size() = " << MC_distr.size() << std::endl;
    std::cout << "Lumi_distr.size() = " << Lumi_distr.size() << std::endl;
    std::cerr <<"ERROR: standalone_LumiReWeighting: input vectors have different sizes. Quitting... \n";

  }


  weights_ = new TH1D(Form("luminumer_%d",mode),
 		      Form("luminumer_%d",mode),
 		      NBins,0.0, double(NBins));

  TH1D* den = new TH1D(Form("lumidenom_%d",mode),
 		       Form("lumidenom_%d",mode),
 		       NBins,0.0, double(NBins));


  
  for(int ibin = 1; ibin<NBins+1; ++ibin ) {
    weights_->SetBinContent(ibin, Lumi_distr[ibin-1]);
    den->SetBinContent(ibin,MC_distr[ibin-1]);
  }

  std::cout << "Data Input " << std::endl;
  for(int ibin = 1; ibin<NBins+1; ++ibin){
    std::cout << "   " << ibin-1 << " " << weights_->GetBinContent(ibin) << std::endl;
  }
  std::cout << "MC Input " << std::endl;
  for(int ibin = 1; ibin<NBins+1; ++ibin){
    std::cout << "   " << ibin-1 << " " << den->GetBinContent(ibin) << std::endl;
  }

  // check integrals, make sure things are normalized

  double deltaH = weights_->Integral();
  if(fabs(1.0 - deltaH) > 0.02 ) { //*OOPS*...
    weights_->Scale( 1.0/ weights_->Integral() );
  }
  double deltaMC = den->Integral();
  if(fabs(1.0 - deltaMC) > 0.02 ) {
    den->Scale(1.0/ den->Integral());
  }

  weights_->Divide( den );  // so now the average weight should be 1.0    

  std::cout << "Reweighting: Computed Weights per In-Time Nint " << std::endl;


  for(int ibin = 1; ibin<NBins+1; ++ibin){
    std::cout << "   " << ibin-1 << " " << weights_->GetBinContent(ibin) << std::endl;
  }

  std::cout << "=======================================================================" << std::endl;

}

standalone_LumiReWeighting::~standalone_LumiReWeighting()
{
}



double standalone_LumiReWeighting::weight( double npv ) {
  int bin = weights_->GetXaxis()->FindBin( npv );
  return weights_->GetBinContent( bin );
}


#endif
