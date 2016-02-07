
#include <fstream>
using namespace std;

void errmc(const float nsig,const float ntotal,float& eff, float& err);
void errRatio(const float nsig, const float nerr, const float nsig1, const float nerr1, float& r, float& rerr);

void errRatio(const float nsig, const float nerr, const float nsig1, const float nerr1, float& r, float& rerr)
{

  r = nsig/nsig1;
  rerr = r*sqrt(nerr*nerr/nsig/nsig + nerr1*nerr1/nsig1/nsig1);
  return;
}

void errmc(const float nsig, const float ntotal,float& eff, float& err)
{
  eff = nsig/ntotal;
  err = sqrt( (1-eff)*eff/ntotal);
  return;
}

void eff_prunedMass()
{

  const int NMASSPOINTS=3;

  int herwig_before_WW[3][2];
  int herwig_after_WW[3][2];

  int pythia_before_WW[3][2];
  int pythia_after_WW[3][2];

  ifstream fin;
  fin.open("eff_WW.dat");
  
  for(int i=0; i<NMASSPOINTS; i++)
    {
      fin >> herwig_before_WW[i][0] >> herwig_before_WW[i][1]
	  >> herwig_after_WW[i][0] >> herwig_after_WW[i][1];
      fin >> pythia_before_WW[i][0] >> pythia_before_WW[i][1]
	  >> pythia_after_WW[i][0] >> pythia_after_WW[i][1];
    }
  fin.close();

  int herwig_before_hh[3][2];
  int herwig_after_hh[3][2];

  int pythia_before_hh[3][2];
  int pythia_after_hh[3][2];

  ifstream fin2;
  fin2.open("eff_hh.dat");
  
  for(int i=0; i<NMASSPOINTS; i++)
    {
      fin2 >> herwig_before_hh[i][0] >> herwig_before_hh[i][1]
	  >> herwig_after_hh[i][0] >> herwig_after_hh[i][1];
      fin2 >> pythia_before_hh[i][0] >> pythia_before_hh[i][1]
	  >> pythia_after_hh[i][0] >> pythia_after_hh[i][1];
    }
  fin2.close();

  
  cout << "----------------------------------------------------" << endl;
  cout << "Before any cuts" << endl;

  for(int i=0; i<NMASSPOINTS; i++)
    {
      float eff_temp=-1, err_temp=-1;
      errmc(herwig_before_hh[i][1],herwig_before_hh[i][0],eff_temp,err_temp);

      float eff_temp2=-1, err_temp2=-1;
      errmc(herwig_before_WW[i][1],herwig_before_WW[i][0],eff_temp2,err_temp2);

      float rh=-1, rerrh=-1;
      errRatio(eff_temp,err_temp,eff_temp2,err_temp2,rh,rerrh);

      float eff_temp3=-1, err_temp3=-1;
      errmc(pythia_before_hh[i][1],pythia_before_hh[i][0],eff_temp3,err_temp3);

      float eff_temp4=-1, err_temp4=-1;
      errmc(pythia_before_WW[i][1],pythia_before_WW[i][0],eff_temp4,err_temp4);

      float rp=-1, rerrp=-1;
      errRatio(eff_temp3,err_temp3,eff_temp4,err_temp4,rp,rerrp);

      float doubleRatio=-1, doubleRatioErr=-1;
      errRatio(rh,rerrh,rp,rerrp,doubleRatio,doubleRatioErr);

      cout << std::setprecision(3) << eff_temp << " \\pm " << err_temp << " & ";
      cout << std::setprecision(3) << eff_temp2 << " \\pm " << err_temp2 << " & ";
      cout << std::setprecision(3) << rh << " \\pm " << rerrh << " & ";
      cout << std::setprecision(3) << eff_temp3 << " \\pm " << err_temp3 << " & ";
      cout << std::setprecision(3) << eff_temp4 << " \\pm " << err_temp4 << " & ";
      cout << std::setprecision(3) << rp << " \\pm " << rerrp << " & ";
      cout << std::setprecision(3) << doubleRatio << " \\pm " << doubleRatioErr << " \\\\" << endl;
    }

  cout << "----------------------------------------------------" << endl;




  cout << "----------------------------------------------------" << endl;
  cout << "After any cuts" << endl;

  for(int i=0; i<NMASSPOINTS; i++)
    {
      float eff_temp=-1, err_temp=-1;
      errmc(herwig_after_hh[i][1],herwig_after_hh[i][0],eff_temp,err_temp);

      float eff_temp2=-1, err_temp2=-1;
      errmc(herwig_after_WW[i][1],herwig_after_WW[i][0],eff_temp2,err_temp2);

      float rh=-1, rerrh=-1;
      errRatio(eff_temp,err_temp,eff_temp2,err_temp2,rh,rerrh);

      float eff_temp3=-1, err_temp3=-1;
      errmc(pythia_after_hh[i][1],pythia_after_hh[i][0],eff_temp3,err_temp3);

      float eff_temp4=-1, err_temp4=-1;
      errmc(pythia_after_WW[i][1],pythia_after_WW[i][0],eff_temp4,err_temp4);

      float rp=-1, rerrp=-1;
      errRatio(eff_temp3,err_temp3,eff_temp4,err_temp4,rp,rerrp);

      float doubleRatio=-1, doubleRatioErr=-1;
      errRatio(rh,rerrh,rp,rerrp,doubleRatio,doubleRatioErr);

      cout << std::setprecision(3) << eff_temp << " \\pm " << err_temp << " & ";
      cout << std::setprecision(3) << eff_temp2 << " \\pm " << err_temp2 << " & ";
      cout << std::setprecision(3) << rh << " \\pm " << rerrh << " & ";
      cout << std::setprecision(3) << eff_temp3 << " \\pm " << err_temp3 << " & ";
      cout << std::setprecision(3) << eff_temp4 << " \\pm " << err_temp4 << " & ";
      cout << std::setprecision(3) << rp << " \\pm " << rerrp << " & ";
      cout << std::setprecision(3) << doubleRatio << " \\pm " << doubleRatioErr << " \\\\" << endl;
    }


  cout << "----------------------------------------------------" << endl;

}
