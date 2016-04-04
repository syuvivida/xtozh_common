/*
 Author: Shin-Shan Eiko Yu

Assuming a new resonance (like graviton) decays to two identical bosons; each 
boson decays to two quarks. 
(1) Derive the momentum of each quark in the rest frame of boson. 
(2) Then, I did computation two ways. One is assuming the boson has only pZ. 
    The other is to assume the boson has only pT (pZ=0). 
(3) Once cosTheta_1 is set, you could know the pT and pZ of each quark in 
    the boson rest frame. 
(4) You could use either Lorentz transformation or the BoostVector in ROOT 
    to boost the quark momentum back to the lab frame.
(5) The magnitude of the boson momentum in the lab frame can have many 
    possibilities (which depends on the boost of the new resonance). I am 
    simplifying thing, by assuming that the new resonance has no boost (on 
    average this is true). 
    Then, I could derive the maximum possible momentum of the boson. 
(6) The direction of the boson momentum depends on the spin of the new resonance.  
    In our models, the probability for the boson to have very large pT and very 
    small pZ is much higher than having small pT, large pZ.
 */

#include <TLorentzVector.h>

void parallel(float mzp, float mboson, float m1, float m2, float cosTheta=1)
{

  float p= sqrt( (mboson*mboson-(m1+m2)*(m1+m2))*
                  (mboson*mboson-(m1-m2)*(m1-m2)))*0.5/mboson;

  cout << "p of quarks in the rest frame of boson is " << p << endl;
  float E1 = sqrt(p*p+m1*m1);

  float E2 = sqrt(p*p+m2*m2);

  cout << "E1 of quark1 in the rest frame = " << E1 
       << "\n E2 of quark2 in the rest frame = " << E2 << endl;

  // compute the minimum boost a boson must have so to have 
  // both daughters flying in the same direction as the mother

  float beta = p*cosTheta/E1;
  cout << "In order for both quarks to move in the same direction "
       << "of their boson mother in the lab frame,";
  cout << "beta of boson needs to be greater than p/E = " << beta << endl;  

  float p_lab = beta/sqrt(1-beta*beta)*mboson;
  cout << "boson momentum must be greater than " << p_lab << endl;

  float p1t_lab = p*sqrt(1-cosTheta*cosTheta);
  float p2t_lab = p1t_lab;

  cout << "before the boost" << endl;

  // assigning TLorentzVector to both quarks in the rest frame
  // of their mother boson
  TLorentzVector q1(0,0,0,0);
  q1.SetPxPyPzE(p1t_lab,0,p*cosTheta,E1);
  q1.Print();
  cout << "q1 Mass = " << q1.M() << endl;

  TLorentzVector q2(0,0,0,0);
  q2.SetPxPyPzE(-p2t_lab,0,-p*cosTheta,E2);
  q2.Print();
  cout << "q2 Mass = " << q2.M() << endl;
  
  TLorentzVector boson_l4(0,0,0,0);
  // maximum momentum along the z direction, assuming boson has only pZ
  float p_boson_lab = sqrt( (mzp*mzp-4*mboson*mboson)*
			    (mzp*mzp) )*0.5/mzp;
  float E_boson_lab = sqrt(p_boson_lab*p_boson_lab+mboson*mboson);
  boson_l4.SetPxPyPzE(0,0,p_boson_lab,E_boson_lab);
  boson_l4.Print();
  cout << "boson Mass = " << boson_l4.M() << endl;

  // boost the quarks back to the lab frame
  cout << "after the boost along the z direction" << endl;
  q1.Boost(-boson_l4.BoostVector());
  q1.Print();
  q2.Boost(-boson_l4.BoostVector());
  q2.Print();

  // check if the quarks are merged in one AK8 jet
  cout << "deltaR between two daughters in the lab frame = " << q1.DeltaR(q2) << endl;
  cout << "Angle between two daughters in the lab frame = " << q1.Vect().Angle(q2.Vect()) << endl;

  // check if this configuration will fail pruning
  cout << "z = " << TMath::Min(q1.Pt(),q2.Pt())/(q1.Pt()+q2.Pt()) << endl;
  cout << "dij*pT/m = " << q1.DeltaR(q2)*boson_l4.Pt()/boson_l4.M() << endl;


  // now assume the momentum of the mother boson is only on the transverse plane
  q1.SetPxPyPzE( p*cosTheta, 0, p1t_lab, E1);
  q1.Print();
  q2.SetPxPyPzE(-p*cosTheta, 0,-p2t_lab, E2);
  q2.Print();
  boson_l4.SetPxPyPzE(p_boson_lab,0,0,E_boson_lab);
  boson_l4.Print();

  // boost the quark momentum back to the lab frame
  cout << "after the boost along the transverse direction" << endl;
  q1.Boost(-boson_l4.BoostVector());
  q1.Print();
  q2.Boost(-boson_l4.BoostVector());
  q2.Print();

  // check if the quarks are merged in one AK8 jet
  cout << "deltaR between two daughters in the lab frame = " << q1.DeltaR(q2) << endl;
  cout << "Angle between two daughters in the lab frame = " << q1.Vect().Angle(q2.Vect()) << endl;

  // check if this configuration will fail pruning
  cout << "z = " << TMath::Min(q1.Pt(),q2.Pt())/(q1.Pt()+q2.Pt()) << endl;
  cout << "dij*pT/m = " << q1.DeltaR(q2)*boson_l4.Pt()/boson_l4.M() << endl;




  return;

}
