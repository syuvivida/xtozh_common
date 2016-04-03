void parallel(float mzp, float m1, float m2, float cosTheta=1, float boost_factor=1)
{

  float p= sqrt( (mzp*mzp-(m1+m2)*(m1+m2))*
                  (mzp*mzp-(m1-m2)*(m1-m2)))*0.5/mzp;

  cout << "p in the rest frame of boson is " << p << endl;
  float E1 = sqrt(p*p+m1*m1);

  float E2 = sqrt(p*p+m2*m2);

  cout << "E1 = " << E1 << "\t E2 = " << E2 << endl;

  float beta = p*cosTheta/E1;

  cout << "beta needs to be greater than p/E = " << beta << endl;
  
  float p_lab = beta/sqrt(1-beta*beta)*mzp;

  cout << "boson momentum must be greater than " << p_lab << endl;

  beta = 400.*boost_factor/sqrt(400*boost_factor*400*boost_factor+mzp*mzp);

  float p1z_lab = (-beta*E1 + p*cosTheta)/sqrt(1-beta*beta);
  float p2z_lab = (-beta*E2 - p*cosTheta)/sqrt(1-beta*beta);

  float p1t_lab = p*sqrt(1-cosTheta*cosTheta);
  float p2t_lab = p1t_lab;

  float p1_lab = sqrt(p1z_lab*p1z_lab + p1t_lab*p1t_lab);
  float p2_lab = sqrt(p2z_lab*p2z_lab + p2t_lab*p2t_lab);

  cout << "p1z_lab = " << p1z_lab << endl;
  cout << "p2z_lab = " << p2z_lab << endl;

  cout << "p1t_lab = " << p1t_lab << endl;
  cout << "p2t_lab = " << p2t_lab << endl;

  cout << "p1_lab = " << p1_lab << endl;
  cout << "p2_lab = " << p2_lab << endl;

  cout << "z = " << TMath::Min(fabs(p1_lab),fabs(p2_lab))/(
							   fabs(p1_lab)+fabs(p2_lab)) << endl;

  return;

}
