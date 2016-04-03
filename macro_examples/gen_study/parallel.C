#include <TLorentzVector.h>

void parallel(float mzp, float mboson, float m1, float m2, float cosTheta=1)
{

  float p= sqrt( (mboson*mboson-(m1+m2)*(m1+m2))*
                  (mboson*mboson-(m1-m2)*(m1-m2)))*0.5/mboson;

  cout << "p in the rest frame of boson is " << p << endl;
  float E1 = sqrt(p*p+m1*m1);

  float E2 = sqrt(p*p+m2*m2);

  cout << "E1 = " << E1 << "\t E2 = " << E2 << endl;

  float beta = p*cosTheta/E1;

  cout << "beta needs to be greater than p/E = " << beta << endl;
  
  float p_lab = beta/sqrt(1-beta*beta)*mboson;

  cout << "boson momentum must be greater than " << p_lab << endl;

  float p1t_lab = p*sqrt(1-cosTheta*cosTheta);
  float p2t_lab = p1t_lab;

  cout << "before the boost" << endl;
    
  TLorentzVector q1(0,0,0,0);
  q1.SetPxPyPzE(p1t_lab,0,p*cosTheta,E1);
  q1.Print();
  cout << "q1 Mass = " << q1.M() << endl;

  TLorentzVector q2(0,0,0,0);
  q2.SetPxPyPzE(-p2t_lab,0,-p*cosTheta,E2);
  q2.Print();
  cout << "q2 Mass = " << q2.M() << endl;
  
  TLorentzVector boson_l4(0,0,0,0);
  // maximum momentum
  float p_boson_lab = sqrt( (mzp*mzp-4*mboson*mboson)*
			    (mzp*mzp) )*0.5/mzp;
  float E_boson_lab = sqrt(p_boson_lab*p_boson_lab+mboson*mboson);
  boson_l4.SetPxPyPzE(0,0,p_boson_lab,E_boson_lab);
  boson_l4.Print();
  cout << "boson Mass = " << boson_l4.M() << endl;


  cout << "after the boost along the z direction" << endl;
  q1.Boost(-boson_l4.BoostVector());
  q1.Print();
  q2.Boost(-boson_l4.BoostVector());
  q2.Print();

  cout << "deltaR between two daughters in the lab frame = " << q1.DeltaR(q2) << endl;
  cout << "Angle between two daughters in the lab frame = " << q1.Vect().Angle(q2.Vect()) << endl;

  cout << "z = " << TMath::Min(q1.Pt(),q2.Pt())/(q1.Pt()+q2.Pt()) << endl;
  cout << "dij*pT/m = " << q1.DeltaR(q2)*boson_l4.Pt()/boson_l4.M() << endl;

  q1.SetPxPyPzE( p*cosTheta, 0, p1t_lab, E1);
  q1.Print();
  q2.SetPxPyPzE(-p*cosTheta, 0,-p2t_lab, E2);
  q2.Print();
  boson_l4.SetPxPyPzE(p_boson_lab,0,0,E_boson_lab);
  boson_l4.Print();

  cout << "after the boost along the transverse direction" << endl;
  q1.Boost(-boson_l4.BoostVector());
  q1.Print();
  q2.Boost(-boson_l4.BoostVector());
  q2.Print();

  cout << "deltaR between two daughters in the lab frame = " << q1.DeltaR(q2) << endl;
  cout << "Angle between two daughters in the lab frame = " << q1.Vect().Angle(q2.Vect()) << endl;

  cout << "z = " << TMath::Min(q1.Pt(),q2.Pt())/(q1.Pt()+q2.Pt()) << endl;
  cout << "dij*pT/m = " << q1.DeltaR(q2)*boson_l4.Pt()/boson_l4.M() << endl;




  return;

}
