
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

void JES_prunedMass()
{

  const int NMASSPOINTS=3;

  int herwig_before_central[3][2];
  int herwig_after_central[3][2];

  int pythia_before_central[3][2];
  int pythia_after_central[3][2];

  ifstream fin;
  fin.open("JECeff_hh.dat");
  
  for(int i=0; i<NMASSPOINTS; i++)
    {
      fin >> herwig_before_central[i][0] >> herwig_before_central[i][1]
	  >> herwig_after_central[i][0] >> herwig_after_central[i][1];
      fin >> pythia_before_central[i][0] >> pythia_before_central[i][1]
	  >> pythia_after_central[i][0] >> pythia_after_central[i][1];
    }
  fin.close();


  int herwig_before_up[3][2];
  int herwig_after_up[3][2];

  int pythia_before_up[3][2];
  int pythia_after_up[3][2];

  ifstream finUp;
  finUp.open("JECUpeff_hh.dat");
  
  for(int i=0; i<NMASSPOINTS; i++)
    {
      finUp >> herwig_before_up[i][0] >> herwig_before_up[i][1]
	  >> herwig_after_up[i][0] >> herwig_after_up[i][1];
      finUp >> pythia_before_up[i][0] >> pythia_before_up[i][1]
	  >> pythia_after_up[i][0] >> pythia_after_up[i][1];
    }
  finUp.close();


  int herwig_before_down[3][2];
  int herwig_after_down[3][2];

  int pythia_before_down[3][2];
  int pythia_after_down[3][2];

  ifstream finDown;
  finDown.open("JECDowneff_hh.dat");
  
  for(int i=0; i<NMASSPOINTS; i++)
    {
      finDown >> herwig_before_down[i][0] >> herwig_before_down[i][1]
	  >> herwig_after_down[i][0] >> herwig_after_down[i][1];
      finDown >> pythia_before_down[i][0] >> pythia_before_down[i][1]
	  >> pythia_after_down[i][0] >> pythia_after_down[i][1];
    }
  finDown.close();


  
  cout << "----------------------------------------------------" << endl;
  cout << "Before any cuts" << endl;

  for(int i=0; i<NMASSPOINTS; i++)
    {

      float eff_temp4=-1, err_temp4=-1;
      errmc(pythia_before_central[i][1],pythia_before_central[i][0],eff_temp4,err_temp4);

      float eff_temp1=-1, err_temp1=-1;
      errmc(pythia_before_up[i][1],pythia_before_up[i][0],eff_temp1,err_temp1);

      float rUp=-1, rerrUp=-1;
      errRatio(eff_temp1,err_temp1,eff_temp4,err_temp4,rUp,rerrUp);

      float eff_temp3=-1, err_temp3=-1;
      errmc(pythia_before_down[i][1],pythia_before_down[i][0],eff_temp3,err_temp3);

      float rDown=-1, rerrDown=-1;
      errRatio(eff_temp3,err_temp3,eff_temp4,err_temp4,rDown,rerrDown);



      cout << std::setprecision(3) << eff_temp1 << " $\\pm$ " << std::setprecision(1) << err_temp1 << " & ";
      cout << std::setprecision(3) << eff_temp3 << " $\\pm$ "<< std::setprecision(1) << err_temp3 << " & ";
      cout << std::setprecision(3) << eff_temp4 << " $\\pm$ " << std::setprecision(1) << err_temp4 << " & ";
      cout << std::setprecision(3) << rUp << " $\\pm$ " << std::setprecision(2) << rerrUp << " & ";
      cout << std::setprecision(3) << rDown << " $\\pm$ " << std::setprecision(2) << rerrDown << " \\\\" << endl;
    }

  cout << "----------------------------------------------------" << endl;



  cout << "----------------------------------------------------" << endl;
  cout << "After any cuts" << endl;

  for(int i=0; i<NMASSPOINTS; i++)
    {

      float eff_temp4=-1, err_temp4=-1;
      errmc(pythia_after_central[i][1],pythia_after_central[i][0],eff_temp4,err_temp4);

      float eff_temp1=-1, err_temp1=-1;
      errmc(pythia_after_up[i][1],pythia_after_up[i][0],eff_temp1,err_temp1);

      float rUp=-1, rerrUp=-1;
      errRatio(eff_temp1,err_temp1,eff_temp4,err_temp4,rUp,rerrUp);

      float eff_temp3=-1, err_temp3=-1;
      errmc(pythia_after_down[i][1],pythia_after_down[i][0],eff_temp3,err_temp3);

      float rDown=-1, rerrDown=-1;
      errRatio(eff_temp3,err_temp3,eff_temp4,err_temp4,rDown,rerrDown);



      cout << std::setprecision(3) << eff_temp1 << " $\\pm$ " << std::setprecision(1) << err_temp1 << " & ";
      cout << std::setprecision(3) << eff_temp3 << " $\\pm$ "<< std::setprecision(1) << err_temp3 << " & ";
      cout << std::setprecision(3) << eff_temp4 << " $\\pm$ " << std::setprecision(1) << err_temp4 << " & ";
      cout << std::setprecision(3) << rUp << " $\\pm$ " << std::setprecision(2) << rerrUp << " & ";
      cout << std::setprecision(3) << rDown << " $\\pm$ " << std::setprecision(2) << rerrDown << " \\\\" << endl;
    }

  cout << "----------------------------------------------------" << endl;





}
