//root
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <TF1.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TBox.h>
#include <TMath.h>
#include <TFile.h>
#include <TMinuit.h>
#include <TList.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TBranch.h>
#include <TRandom.h>
#include <TProfile.h>
#include <TLorentzVector.h>
#include <TSystemDirectory.h>
#include <TLegend.h>

//include interface
#include "interface/untuplizer.h"

using namespace std;

// global variable================================================
  	//gereral
	Long64_t Nev_MC, Nev_data;
	int N_available_event_MC=0;
	int N_available_event_data=0;

	// gen level 
	vector< vector<double> > fraction_ratio;
	int max_true_b=0;
	int max_true_nb=0;
	
	double true_eff=0;
	double true_mr=0;

	int gen_j=0;
	int gen_b=0;
	int gen_nb=0;
	int gen_j_pass_cut=0;
	int gen_b_pass_cut=0;
	int gen_nb_pass_cut=0;
	int gen_j_pass_cut_btagging=0;
	int gen_b_pass_cut_btagging=0;
	int gen_nb_pass_cut_btagging=0;

	// rec level
	vector<Int_t> Nt_from_rec(1,0) ; // # of event that have t b-tagging
	vector<Int_t> Nk_from_rec(1,0) ; // # of event that have k jet

	double best_eff_rec=0;
	double best_mr_rec=0;

	int total_kk_rec=0;
	int total_k_rec=0;
	int total_btag_pass_cut_rec=0;
	int total_nbtag_pass_cut_rec=0;
	
	// data
	vector<Int_t> Nt_from_data(1,0) ; // # of event that have t b-tagging
	vector<Int_t> Nk_from_data(1,0) ; // # of event that have k jet
	
	double best_eff_data=0;
	double best_mr_data=0;

	int total_kk_data=0;
	int total_k_data=0;
	int total_btag_pass_cut_data=0;
	int total_nbtag_pass_cut_data=0;

	// counting
	int N_CA8jet_before_deoverlap=0;
	int N_CA8jet_after_deoverlap=0;



//class============================================================================
class PO
{
	public:
    	Float_t pt;
    	Float_t eta;
    	Float_t phi;
    	Float_t en;
	Float_t M;
	PO(){}
	PO(Float_t pt_,Float_t eta_,Float_t phi_, Float_t en_, Float_t M_)	
	{ pt=pt_;eta=eta_;phi=phi_;en=en_;M=M_;}
	

};
	

class gen_par : public PO
{
	public:
	Int_t id;
	Int_t index;
	Int_t mid;
	Int_t mo1;
	Int_t mo2;
	Int_t status;
	
	gen_par():PO(){}
    	gen_par(Float_t pt_,Float_t eta_,Float_t phi_, Float_t en_,Float_t M_,
		Int_t id_,Int_t index_, Int_t mid_, Int_t mo1_, Int_t mo2_, Int_t status_)
		:PO(pt_,eta_,phi_,en_,M_)
	{ id=id_; index=index_; mid=mid_; mo1=mo1_; mo2=mo2_; status=status_;}
};

class ele : public PO
{
	public:
	Float_t del_eta_in;
	Float_t del_phi_in;
	Float_t sig_ieie;
	Float_t hoe;
	Float_t dxy;
	Float_t dz;
	Float_t eop;
	Float_t corr_pf_iso;
	Int_t pass_conv;
	Float_t missing_hits;

	Int_t pass_ID;
	Float_t user_trk_iso;
	Float_t user_cal_iso;
	Float_t rho;

	ele():PO(){}
    	ele(Float_t pt_,Float_t eta_,Float_t phi_, Float_t en_,Float_t M_,
			Float_t del_eta_in_, Float_t del_phi_in_, Float_t sig_ieie_, Float_t hoe_, 
			Float_t dxy_,Float_t dz_, Float_t eop_, Float_t corr_pf_iso_, Int_t pass_conv_, Float_t missing_hits_,
			Int_t pass_ID_, Float_t user_trk_iso_, Float_t user_cal_iso_, Float_t rho_)
		:PO(pt_,eta_,phi_,en_,M_)
    	{
		del_eta_in=del_eta_in_;
		del_phi_in=del_phi_in_;
		sig_ieie=sig_ieie_;
		hoe=hoe_;
		dxy=dxy_;
		dz=dz_;
		eop=eop_;
		corr_pf_iso=corr_pf_iso_;
		pass_conv=pass_conv_;
		missing_hits=missing_hits_;
		pass_ID=pass_ID_;
		user_trk_iso=user_trk_iso_;
		user_cal_iso=user_cal_iso_;
		rho=rho_;

	}

};

class mu : public PO
{
	public:
    	Int_t is_global_mu;
    	Int_t is_tracker_mu;
    	Int_t trk_layers;
    	Int_t pixel_hits;
    	Int_t hits;
    	Int_t matches;
    	Float_t dxy;
    	Float_t dz;

	Float_t corr_pf_iso;
	Int_t pass_ID;
	Float_t corr_trk_iso;
	
	mu():PO(){}
    	mu(Float_t pt_,Float_t eta_,Float_t phi_, Float_t en_,Float_t M_,  //note: mu has no energy leafe
	   		Int_t is_global_mu_, Int_t is_tracker_mu_, Int_t trk_layers_, Int_t pixel_hits_, Int_t hits_, Int_t matches_, Float_t dxy_, Float_t dz_, 
			Float_t corr_pf_iso_, Int_t pass_ID_, Float_t corr_trk_iso_)
		:PO(pt_,eta_,phi_,en_,M_)
    	{
    		is_global_mu=is_global_mu_;
    		is_tracker_mu=is_tracker_mu_;
    		trk_layers=trk_layers_;
    		pixel_hits=pixel_hits_;
    		hits=hits_;
    		matches=matches_;
    		dxy=dxy_;
    		dz=dz_;	
		corr_pf_iso=corr_pf_iso_;
		pass_ID=pass_ID_;
		corr_trk_iso=corr_trk_iso_;
	}

};

  


class jet : public PO
{
  	public:
	Float_t csv;

	//cut var
	Float_t n_had_ef;
	Float_t n_em_ef;
	Float_t c_had_ef;
	Float_t c_em_ef;
	Float_t c_multi;

	jet():PO(){}	
    	jet(Float_t pt_,Float_t eta_,Float_t phi_, Float_t en_, Float_t M_,
		Float_t csv_,
		Float_t n_had_ef_,Float_t n_em_ef_,Float_t c_had_ef_,Float_t c_em_ef_,Float_t c_multi_)
		:PO(pt_,eta_,phi_,en_,M_)
    	{ 
		csv=csv_;
	 	n_had_ef=n_had_ef_; n_em_ef=n_em_ef_; c_had_ef=c_had_ef_; c_em_ef=c_em_ef_; c_multi=c_multi_;
	}
};


class AK5jet : public jet
{
  	public:

	AK5jet():jet(){}	
    	AK5jet(Float_t pt_,Float_t eta_,Float_t phi_, Float_t en_, Float_t M_,
		Float_t csv_,
		Float_t n_had_ef_,Float_t n_em_ef_,Float_t c_had_ef_,Float_t c_em_ef_,Float_t c_multi_)
		:jet(pt_, eta_, phi_, en_, M_,
		csv_,
		n_had_ef_, n_em_ef_, c_had_ef_, c_em_ef_, c_multi_)
    	{ }
};


class CA8jet : public jet
{
  	public:

	CA8jet():jet(){}	
    	CA8jet(Float_t pt_,Float_t eta_,Float_t phi_, Float_t en_, Float_t M_,
		Float_t csv_,
		Float_t n_had_ef_,Float_t n_em_ef_,Float_t c_had_ef_,Float_t c_em_ef_,Float_t c_multi_)
		:jet(pt_, eta_, phi_, en_, M_,
		csv_,
		n_had_ef_, n_em_ef_, c_had_ef_, c_em_ef_, c_multi_)
    	{ }
};

class CA8subjet : public PO
{
  	public:
	Float_t csv;

	CA8subjet():PO(){}	
    	CA8subjet(Float_t pt_,Float_t eta_,Float_t phi_, Float_t en_, Float_t M_,
		Float_t csv_)
		:PO(pt_,eta_,phi_,en_,M_)
    	{ 
		csv=csv_;
	}
};

class met
{
	public:
	Float_t pt;
	Float_t phi;


	met(){}
	met( Float_t pt_, Float_t phi_)
	{ pt=pt_; phi=phi_;}
};



class event
{
	public:
	vector<gen_par> gen_pars;
	vector<CA8jet> CA8jets;
	vector<AK5jet> AK5jets;
	vector< vector<CA8subjet> > CA8subjets;
	vector< vector<CA8subjet> > CA8subjets_deoverlap_with_lepton_and_subjet;
	vector<ele> eles;
	vector<mu> mus;
	met missing_et;
	event(){}
};




// counter

class jet_cone
{
	public:
	int gen_b;
	int gen_nb;
	int gen_ele;
	int gen_mu;
	jet_cone(){ gen_b=0;gen_nb=0;gen_ele=0;gen_mu=0;}
	

};

// for minuit
class par_for_minuit
{
	public:
	string name;
	double fit_start;
	double number;
	double fit_step;
	double min;
	double max;
	par_for_minuit(){}
	par_for_minuit(double number_, string name_, double fit_start_,  double fit_step_, double min_, double max_ )
	{  number=number_; name=name_; fit_start=fit_start_;  fit_step=fit_step_; min=min_; max=max_;}
};

class par_err_pair_for_minuit
{
	public:
	Double_t v;
	Double_t err;
	par_err_pair_for_minuit(){}
	par_err_pair_for_minuit(Double_t v_, Double_t err_)
	{ v=v_;err=err_;}
	
};


//function======================================================================================================

//////////====tt
void tt(double i)
{
	cout<<"CHK"<<i<<endl;
}

//////////====math
Int_t factorial(Int_t n_)
{
	if (n_<0){return 0;}
	Int_t r=1;
	Int_t _n_=n_;
	for (Int_t i=1;i<=_n_;i++)
	{
		r=r*i;
	}
	return r;
}

long C(Int_t n,Int_t m)
{
	if (m>n || m<0){return 0;}
	long r_top=1;
	long r_down=1;	
	Int_t subscript;	
	if((n-m)<(m)){subscript=n-m;}
	else {subscript=m;}
	for (Int_t i =0;i<subscript;i++)
	{ r_top=r_top*(n-i); r_down=r_down*(i+1);}
	return (r_top/r_down);
//	return (factorial(n)/(factorial(m)*factorial(n-m))); //n>=18, memory overflow
}



double log_poisson(double x, double lamda)
{
	// it woks when x=200,000,000
	double term1 = (-1) * lamda;
	double term2 = x * log(lamda);
	double term3 = 0;
	for (double i = 0; i < x; i++)
	{
		term3 = term3 + log(x - i);
	}
	term3 = (-1) * term3;

	return term1 + term2 + term3;
}

// general
Float_t delta_R(PO O1_,PO O2_)
{
	Float_t a = (O1_.eta-O2_.eta);
	Float_t b = (O1_.phi-O2_.phi);
	return sqrt(a*a+b*b);
}


//for gen par
/*/for Zprime
//
bool is_wanted_b(gen_par g_)
{
	if (abs(g_.id)==5 && g_.status==3 && abs(g_.mid)==25)
	{ return true;}
	else
	{ return false;}
}/*/


// for TTbar sample
bool is_wanted_b(gen_par g_)
{
	if (abs(g_.id)==5 && g_.status==3 && abs(g_.mid)==6)
	{ return true;}
	else
	{ return false;}
}//*/

bool is_gen_j(gen_par g_)
{
	if (abs(g_.id)<=6 && abs(g_.id)>=1) //no id==7(b'), id==8(t') found.
	{ return true;}
	else
	{ return false;}
}


// jet selection
bool is_pass_csvl(jet j_)
{
	if (j_.csv>0.244 && j_.csv<=1){return true;}
	else {return false;}
}
bool is_pass_csvl(CA8subjet j_)
{
	if (j_.csv>0.244 && j_.csv<=1){return true;}
	else {return false;}
}


bool is_pass_csvm(jet j_)
{
	if (j_.csv>0.679 && j_.csv<=1){return true;}
	else {return false;}
}
bool is_pass_csvm(CA8subjet j_)
{
	if (j_.csv>0.679 && j_.csv<=1){return true;}
	else {return false;}
}

bool is_pass_jet_loose_id(jet j_)
{
	if(j_.n_had_ef>=0.99){return false;}
	if(j_.n_em_ef>=0.99){return false;}	
	if(j_.eta>=0.99)
	{
		if(j_.c_had_ef<=0){return false;}
		if(j_.c_em_ef>=0.99){return false;}
		if(j_.c_multi<=0){return false;}
	}
	return true;
}

bool is_pass_pteta(PO O1_)
{
	if(O1_.pt<20){return false;}
	if(abs(O1_.eta)>2.4){return false;}
	return true;

}


//ele selection
bool is_pass_ele_iso(ele e_)
{
	double iso_cut = 2+(0.03*e_.pt);
	
	if( e_.pass_ID <= 0 ) return false;
	//if( e_.pt <= 40 ) return false;
	if( e_.pt <= 10 ) return false;
	if( e_.user_trk_iso >= 5 ) return false;
	
	// barrel 
	if( abs(e_.eta) > 0 && abs(e_.eta) < 1.4442 )
	{ if( e_.user_cal_iso-0.06205*e_.rho >= iso_cut ){return false;} }
	
	// endcap selection
	if( abs(e_.eta) > 1.566 && abs(e_.eta) < 2.5 )
	{
		if( e_.pt < 50 )
		{ if( e_.user_cal_iso-0.06205*e_.rho >= 2.5 )return false; }
	
		if( e_.pt > 50 )
		{	if( e_.user_cal_iso-0.06205*e_.rho >= (iso_cut+0.5) )return false;}
	}

	return true;
}

bool is_pass_ele_loose_id(ele e_)
{
	if (e_.pt==0){return false;}
    	// barrel selection
    	if( abs(e_.eta) > 0 && abs(e_.eta) < 1.4442 )
	{
      		if ( abs( e_.del_eta_in ) > 0.007 ){return false;}
       		if ( abs( e_.del_phi_in ) > 0.15 ){return false;}
       		if (  e_.sig_ieie  > 0.01 ){return false;}
       		if (  e_.hoe  > 0.12 ){return false;}
       		if ( abs( e_.dxy ) > 0.02 ){return false;}
       		if ( abs( e_.dz ) > 0.2 ){return false;}
       		if ( abs( e_.eop ) > 0.05 ){return false;}
       		if ( ( e_.corr_pf_iso/e_.pt )  > 0.15 ){return false;;}
       		if (  e_.pass_conv !=  1 ){return false;}
       		if (  e_.missing_hits   > 1 ){return false;}
    	}
	// endcap selection
    	if( abs(e_.eta) > 1.566 && abs(e_.eta) < 2.5 )
	{
       		if ( abs( e_.del_eta_in ) > 0.009 ){return false;}
      		if ( abs( e_.del_phi_in ) > 0.1 ){return false;}
       		if (  e_.sig_ieie  > 0.03 ){return false;}
      		if (  e_.hoe  > 0.10 ){return false;}
      	 	if ( abs( e_.dxy ) > 0.02 ){return false;}
       		if ( abs( e_.dz ) > 0.2 ){return false;}
      	 	if ( abs( e_.eop ) > 0.05 ){return false;}

      	 	if (e_.pt<20){ if ( ( e_.corr_pf_iso/e_.pt )  > 0.1 ){return false;}}
      		else if(e_.pt>20){ if ( ( e_.corr_pf_iso/e_.pt )  > 0.15){return false;}}

      	 	if (  e_.pass_conv !=  1 ){return false;}
       		if (  e_.missing_hits  > 1 ){return false;}

		return true;
	}


}

//muon selection  
bool is_pass_mu_iso(mu m_)
{
	//if(m_.pt<45){return false;}
	if(m_.pt<10){return false;}
	if(abs(m_.eta)>2.1){return false;}
	if(m_.corr_pf_iso/m_.pt>0.05){return false;}
	
	return true;	
}


bool is_pass_mu_tight_id(mu m_)
{
	if ( ( m_.is_global_mu != 1 ) && ( m_.is_tracker_mu != 1 ) ){return false;}
       	if ( m_.trk_layers <= 5  ){return false;}
       	if ( m_.pixel_hits <= 0  ){return false;}
       	if ( m_.hits <= 0  ){return false;}
       	if ( m_.matches <= 1  ){return false;}
       	if ( m_.dxy >= 0.2  ){return false;}
       	if ( m_.dz >= 0.5  ){return false;}

	return true;

}

//event selection

bool is_pass_ev_selection(event ev)
{
	//to calculate # of "cadidate CA8sub bjet" and # of "cadidate CA8sub nbjet" in this event
	int ev_flag=0;

 	// 1: check deltaR of any subjet > 0.3
/*
	double R=0.3;
	vector <CA8subjet> all_CA8subjets_in_this_ev;
	for (int i=0;i<ev.CA8subjets.size();i++)
	{
		for(int j=0;j<ev.CA8subjets[i].size();j++)
		{
			all_CA8subjets_in_this_ev.push_back(ev.CA8subjets[i][j]);
		}
	}
	for( int i=0;i<all_CA8subjets_in_this_ev.size();i++)
	{
		for( int j=0;j<i;j++)
		{
			if(delta_R(all_CA8subjets_in_this_ev[i],all_CA8subjets_in_this_ev[j])<=R){ev_flag=1;break;}	
		}
	}
*/
	// 2: to check if have good lepton
	bool have_good_l=false;
	for(int i=0;i<ev.mus.size();i++)
	{
		mu this_mu=ev.mus[i];
		//if(this_mu.pt>35 && abs(this_mu.eta<2.1) && is_pass_mu_iso(this_mu)){have_good_l=true; break;}
		if(this_mu.pt>35 && abs(this_mu.eta<2.1) && is_pass_mu_iso(this_mu)){have_good_l=true; break;}
	}
	for(int i=0;i<ev.eles.size();i++)
	{
		ele this_ele=ev.eles[i];
		if(this_ele.pt>35 && abs(this_ele.eta<2.4) && is_pass_ele_iso(this_ele)){have_good_l=true; break;}
	}
	if(!have_good_l){ev_flag=2;}

/*
	// 3: to check if have at least 4 good jet
	// using subjet
	vector<CA8subjet> good_jets;
	for (int i=0;i<ev.CA8subjets.size();i++)
	{
		for(int j=0;j<ev.CA8subjets[i].size();j++)
		{
			CA8subjet this_subj=ev.CA8subjets[i][j];
			if(this_subj.pt>30 && abs(this_subj.eta<2.4))
			{
				good_jets.push_back(this_subj);
			}	
		}
	}
	if (good_jets.size()<4){ ev_flag=3;}

	// 4: to check if have 2 good leading jet
	// using subjet
	bool have_good_leading_jets=false;
	for (int i=0;i<good_jets.size();i++)
	{
		for (int j=0;j<good_jets.size();j++)
		{
			if(i==j){continue;}
			if(good_jets[i].pt>=70 && good_jets[j].pt>=50){have_good_leading_jets=true;}
		}
	}
	if(!have_good_leading_jets){ev_flag=4;}
*/

	// 3: to check if have at least 4 good jet
	// using CA8jet
	vector<CA8jet> good_jets;
	for (int i=0;i<ev.CA8jets.size();i++)
	{
	
		CA8jet this_j = ev.CA8jets[i];
		
		bool overlap_with_other_subjet=false; 
		for (int ii=0;ii<ev.CA8subjets[i].size();ii++)
		{
			
			for (int jj=0;jj<ev.CA8subjets[i].size();jj++)
			{
				if (ii==jj){continue;}
				if (delta_R(ev.CA8subjets[i][ii] , ev.CA8subjets[i][jj] )<=0.3){overlap_with_other_subjet=true;}		
			}		
		}
		if (overlap_with_other_subjet==true){continue;}
		
		bool overlap_with_lepton=false;
		for (int elei=0;elei<ev.eles.size();elei++)
		{	
			ele this_ele = ev.eles[elei];
			if (!is_pass_ele_loose_id(this_ele) || !is_pass_ele_iso(this_ele)){continue;}
			if (delta_R(this_j, this_ele)<0.8){overlap_with_lepton=true;}
		}

		for (int mui=0;mui<ev.mus.size();mui++)
		{
			mu this_mu = ev.mus[mui];
			if (!is_pass_mu_tight_id(this_mu) || !is_pass_mu_iso(this_mu)){continue;}
			if (delta_R(this_j, this_mu)<0.8){overlap_with_lepton=true;}
		}
		if (overlap_with_lepton==true){ continue;}
						
		if(this_j.pt>30 && abs(this_j.eta<2.4))
		{
			good_jets.push_back(this_j);
		}
	}
	if (good_jets.size()<4){ ev_flag=3;}

	// 4: to check if have 2 good leading jet
	// using CA8jet
	bool have_good_leading_jets=false;
	for (int i=0;i<good_jets.size();i++)
	{
		for (int j=0;j<good_jets.size();j++)
		{
			if(i==j){continue;}
			if(good_jets[i].pt>=70 && good_jets[j].pt>=50){have_good_leading_jets=true;}
		}
	}
	if(!have_good_leading_jets){ev_flag=4;}
	
	
	// 5: to check if missing Et > 20
	if (ev.missing_et.pt<20){ev_flag=5;}

//test
	if(ev_flag==0 || ev_flag==1){return true;} 
	else {return false;}//skip this event
	/*
	ev_flag:
		=0: this event is good event
		=1: !(the deltaR between any pairs of CA8subjet in this event should be > 0.3), skip this event.
		=2: !(have good lepton), skip this event.
		=3: !(have at least 4 good jets), skip this event.
		=4: !(have 2 good leading jets), skip this event.
		=5: !(missing Et > 20), skip this event.
	*/
}


// calculate likelihood





// calculate expection value of Nt
double get_expvalue_of_Nt(  double eff, double mr, int t)
{
        double this_expvalue = 0;
        for (int i = 0; i < fraction_ratio.size() ; i++)
        {
                for (int j = 0; j < fraction_ratio[i].size() ; j++)
                {
                    	double term1 = N_available_event_MC * fraction_ratio[i][j];

                        for (int ii = 0; ii <= i; ii++) // in i b-jet, ii b-jet pass btagging
                        {
                                for (int jj = 0; jj <= j; jj++) // in j nb-jet, jj nb-jet pass btagging
                                {
                                    	if (ii + jj != t) { continue; }

                                    	double term2 = C(i, ii) * pow(eff, ii) * pow(1 - eff, i - ii);
                                    	double term3 = C(j, jj) * pow(mr, jj) * pow(1 - mr, j - jj);
                                    	this_expvalue += (term1 *  term2 * term3);

                                    	//debug
                                    	if (term1 * term2 * term3 < 0)
                                    	{
						cout<<"in get_expvalue_of_Nt"<<endl;
                              			cout<<"<"<<term1 * term2 * term3<<". "<<"term1="<<term1<<",term2="<<term2<<",term3="<<term3<<endl;
                                		cout<<"eff="<<eff<<","<<endl;
                                		cout<<"mr="<<mr<<","<<endl;
                                		cout<<"t="<<t<<","<<endl;
                                    	}
                                }
                        }

                }
        }
        return this_expvalue;
}





//for minuit




void fcn_btagging(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{

	double total_log_like=0;
        for (int t = 0; t < Nt_from_rec.size(); t++)
        {
		// par[0] is eff, par[1] is mr
		if(get_expvalue_of_Nt( par[0], par[1] ,t)==0){continue;}
		double this_log_like=log_poisson(double(Nt_from_rec[t]), get_expvalue_of_Nt( par[0], par[1] ,t));
                total_log_like += this_log_like;
		if (this_log_like < -10000000)
		{ 
			cout<<"this_log_like < -10000000"<<"when eff="<<par[0]<<",mr="<<par[1]<<",t="<<t;
			cout<<",Nt_from_rec[t]="<<double(Nt_from_rec[t])<<",get_expvalue_of_N="<<get_expvalue_of_Nt( par[0], par[1] ,t)<<endl;
		}  
        }

	f=-2*total_log_like;

}




vector<par_err_pair_for_minuit> get_min_par_btagging2p(vector<par_for_minuit> pars_ )
{
	int Npar = pars_.size();
  	TMinuit *gMinuit = new TMinuit(Npar);  //initialize TMinuit with a maximum of 2 params
  	gMinuit->SetFCN(fcn_btagging); // fcn_btagging is the function to do minimization

  	Double_t arglist[10];
  	Int_t ierflg = 0; // status flag, it will be 0 when no programing error found

  	// -- sets par error
  	arglist[0] = 1;
  	gMinuit->mnexcm("SET ERR", arglist ,Npar,ierflg);
	
	//set pars
	vector<par_err_pair_for_minuit> par_err_pairs;
	for(int i=0;i<Npar;i++)
	{
		Double_t number = pars_[i].number;
		string name = pars_[i].name;
	 	Double_t start = pars_[i].fit_start;	
  		Double_t step = pars_[i].fit_step;
		Double_t min = pars_[i].min;
		Double_t max = pars_[i].max;
  		gMinuit->mnparm(number, name, start, step, min,max,ierflg);
		
		par_err_pair_for_minuit A(0,0); 
		par_err_pairs.push_back(A);	
	}

 	// Now ready for minimization step
 	arglist[0] = 1000; //number of iteration, beyond this number, Tminuit stop. 
  	arglist[1] = 0.01;
  	gMinuit->mnexcm("MIGRAD", arglist ,Npar,ierflg);

	for (int i=0;i<Npar;i++)
	{
  		if ( ierflg == 0 ) 
   		{
      			gMinuit->GetParameter(i,par_err_pairs[i].v , par_err_pairs[i].err );  	
		}
		else
		{ cout<<"get_minuit have the error code:"<<ierflg<<endl; }
	}
	return par_err_pairs;
}

//main =======================================================================================================================================================
void Btagging_in_8Tev()
{

	TFile output("output.root","recreate");

	//hist
	//TH1D* var = new TH1D("name","title",bin,xmin,xmax);	
	TH1D* H_IM = new TH1D("H_IM","H_IM",200,0,200);
	TH1D* H_IM_csvl = new TH1D("H_IM_csvl","H_IM_csvl",200,0,200);
	TH1D* H_IM_csvm = new TH1D("H_IM_csvm","H_IM_csvm",200,0,200);

	TH1D* Zee_IM = new TH1D("Zee_IM","Zee_IM",200,0,200);

	TH1D* CA8CSV_b_evcut = new TH1D("CA8CSV_b_evcut","CA8CSV_b_evcut",100,0,1);
	TH1D* CA8subjetCSV_b_evcut = new TH1D("CA8subjetCSV_b_evcut","CA8subjetCSV_b_evcut",100,0,1);
	TH1D* CA8CSV_a_evcut = new TH1D("CA8CSV_a_evcut","CA8CSV_a_evcut",100,0,1);
	TH1D* CA8subjetCSV_a_evcut = new TH1D("CA8subjetCSV_a_evcut","CA8subjetCSV_a_evcut",100,0,1);





	// root file
  	TChain *MC = new TChain("tree/tree");
  	TChain *data = new TChain("tree/tree");
  	//MC->Add("../flattuple.root");// Zprime sample
  	MC->Add("../TTbar_sample/flattuple_1.root");// TTbar sample from yu
  	data->Add("../data_sample/delpanj_v4_data_DoubleMu_A.root");// TTbar sample from yu		
  	TreeReader inner_data_for_MC(MC);
    	TreeReader inner_data_for_data(data);
  	Nev_MC = inner_data_for_MC.GetEntriesFast();
    	Nev_data = inner_data_for_data.GetEntriesFast();

  	cout<< "Nev_MC : "<< Nev_MC << endl;
  	cout<< "Nev_data : "<< Nev_data << endl;
	
  	
  	
  	
	//configure
	vector<event> events_MC;
	vector<event> events_data;

	
	int n_CA8sj=0;
	
	// Btagging function
	typedef bool (*jet_alg)(CA8subjet);
	jet_alg btagging = is_pass_csvl;
	//jet_alg btagging = is_pass_csvm;


	//matching

	// event loop : set up MC
  	for (Long64_t Nth = 0; Nth < Nev_MC; Nth++)
    	{
 		inner_data_for_MC.GetEntry(Nth);

		// gen_par var
		Int_t nGenPar=inner_data_for_MC.GetInt("nGenPar");
      		Float_t *genParPt=inner_data_for_MC.GetPtrFloat("genParPt");  
      		Float_t *genParEta=inner_data_for_MC.GetPtrFloat("genParEta"); 
      		Float_t *genParPhi=inner_data_for_MC.GetPtrFloat("genParPhi"); 
     		Float_t *genParE=inner_data_for_MC.GetPtrFloat("genParE");
     		Float_t *genParM=inner_data_for_MC.GetPtrFloat("genParM");	
		Int_t *genParId=inner_data_for_MC.GetPtrInt("genParId");	
		Int_t *genParIndex=inner_data_for_MC.GetPtrInt("genParIndex");
		Int_t *genMomParId=inner_data_for_MC.GetPtrInt("genMomParId");
		Int_t *genMo1=inner_data_for_MC.GetPtrInt("genMo1");  //not mom id
		Int_t *genMo2=inner_data_for_MC.GetPtrInt("genMo2");  //not mom id
		Int_t *genParSt=inner_data_for_MC.GetPtrInt("genParSt");



      		// CA8jet var
      		Int_t CA8nJet=inner_data_for_MC.GetInt("CA8nJet");
      		Float_t *CA8jetPt=inner_data_for_MC.GetPtrFloat("CA8jetPt");  
      		Float_t *CA8jetEta=inner_data_for_MC.GetPtrFloat("CA8jetEta"); 
      		Float_t *CA8jetPhi=inner_data_for_MC.GetPtrFloat("CA8jetPhi"); 
     		Float_t *CA8jetEn=inner_data_for_MC.GetPtrFloat("CA8jetEn");
     		Float_t *CA8jetMass=inner_data_for_MC.GetPtrFloat("CA8jetMass");
      		Float_t *CA8jetCSV=inner_data_for_MC.GetPtrFloat("CA8jetCSV");

  		Float_t *CA8jetNHadEF=inner_data_for_MC.GetPtrFloat("CA8jetNHadEF");
  		Float_t *CA8jetNEmEF=inner_data_for_MC.GetPtrFloat("CA8jetNEmEF");
  		Float_t *CA8jetCHadEF=inner_data_for_MC.GetPtrFloat("CA8jetCHadEF");
  		Float_t *CA8jetCEmEF=inner_data_for_MC.GetPtrFloat("CA8jetCEmEF");
  		Float_t *CA8jetCMulti=inner_data_for_MC.GetPtrFloat("CA8jetCMulti");

		// muon var
      		Int_t nMu =inner_data_for_MC.GetInt("nMu");
      		Float_t *muPt=inner_data_for_MC.GetPtrFloat("muPt");
   		Float_t *muEta=inner_data_for_MC.GetPtrFloat("muEta");
   		Float_t *muPhi=inner_data_for_MC.GetPtrFloat("muPhi");
   		//no muEnergy!
   		Float_t *muM=inner_data_for_MC.GetPtrFloat("muM");

		Int_t*   isGlobalMuon = inner_data_for_MC.GetPtrInt("isGlobalMuon");
    		Int_t*   isTrackerMuon= inner_data_for_MC.GetPtrInt("isTrackerMuon");
    		Int_t*   muTrkLayers  = inner_data_for_MC.GetPtrInt("muTrkLayers");
    		Int_t*   muPixelHits  = inner_data_for_MC.GetPtrInt("muPixelHits");
    		Int_t*   muHits       = inner_data_for_MC.GetPtrInt("muHits");
    		Int_t*   muMatches    = inner_data_for_MC.GetPtrInt("muMatches");
    		Float_t* mudxy        = inner_data_for_MC.GetPtrFloat("mudxy");
    		Float_t* mudz         = inner_data_for_MC.GetPtrFloat("mudz");

   		Float_t *nuCorrPfIso=inner_data_for_MC.GetPtrFloat("muCorrPfIso");				
		Int_t* muPassID = inner_data_for_MC.GetPtrInt("muPassID");
		Float_t* muCorrTrkIso = inner_data_for_MC.GetPtrFloat("muCorrTrkIso");

      		// ele var
      		Int_t nEle =inner_data_for_MC.GetInt("nEle");
      		Float_t *elePt=inner_data_for_MC.GetPtrFloat("elePt");
   		Float_t *eleEta=inner_data_for_MC.GetPtrFloat("eleEta");
   		Float_t *elePhi=inner_data_for_MC.GetPtrFloat("elePhi");
   		Float_t *eleEnergy=inner_data_for_MC.GetPtrFloat("eleEnergy");
   		Float_t *eleM=inner_data_for_MC.GetPtrFloat("eleM");

		Float_t *eleDelEtaIn=inner_data_for_MC.GetPtrFloat("eleDelEtaIn");
		Float_t *eleDelPhiIn=inner_data_for_MC.GetPtrFloat("eleDelPhiIn");
		Float_t *eleSigIhIh=inner_data_for_MC.GetPtrFloat("eleSigIhIh");
		Float_t *eleHoE=inner_data_for_MC.GetPtrFloat("eleHoE");
		Float_t *eleDxy=inner_data_for_MC.GetPtrFloat("eleDxy");
		Float_t *eleDz=inner_data_for_MC.GetPtrFloat("eleDz");
		Float_t *eleEoverP=inner_data_for_MC.GetPtrFloat("eleEoverP");
		Float_t *eleCorrPfIso=inner_data_for_MC.GetPtrFloat("eleCorrPfIso");
		Int_t *elePassConv=inner_data_for_MC.GetPtrInt("elePassConv");
		Float_t *eleMissingHits=inner_data_for_MC.GetPtrFloat("eleMissingHits");

		Int_t *elePassID=inner_data_for_MC.GetPtrInt("elePassID");
		Float_t *eleUserTrkIso=inner_data_for_MC.GetPtrFloat("eleUserTrkIso");
		Float_t *eleUserCalIso=inner_data_for_MC.GetPtrFloat("eleUserCalIso");
		Float_t eleRho=inner_data_for_MC.GetFloat("eleRho");

		

		// CA8 subjet var
		vector<Float_t> *CA8subjetPrunedPt=inner_data_for_MC.GetPtrVectorFloat("CA8subjetPrunedPt");
		vector<Float_t> *CA8subjetPrunedEta=inner_data_for_MC.GetPtrVectorFloat("CA8subjetPrunedEta");
		vector<Float_t> *CA8subjetPrunedPhi=inner_data_for_MC.GetPtrVectorFloat("CA8subjetPrunedPhi");
		vector<Float_t> *CA8subjetPrunedEn=inner_data_for_MC.GetPtrVectorFloat("CA8subjetPrunedEn");
		vector<Float_t> *CA8subjetPrunedMass=inner_data_for_MC.GetPtrVectorFloat("CA8subjetPrunedMass");
		vector<Float_t> *CA8subjetPrunedCSV=inner_data_for_MC.GetPtrVectorFloat("CA8subjetPrunedCSV");
		vector<Int_t> *CA8subjetPrunedPartonFlavor=inner_data_for_MC.GetPtrVectorInt("CA8subjetPrunedPartonFlavor");

      		// AK5jet var
      		Int_t AK5nJet=inner_data_for_MC.GetInt("AK5nJet");
      		Float_t *AK5jetPt=inner_data_for_MC.GetPtrFloat("AK5jetPt");  
      		Float_t *AK5jetEta=inner_data_for_MC.GetPtrFloat("AK5jetEta"); 
      		Float_t *AK5jetPhi=inner_data_for_MC.GetPtrFloat("AK5jetPhi"); 
     		Float_t *AK5jetEn=inner_data_for_MC.GetPtrFloat("AK5jetEn");
     		Float_t *AK5jetMass=inner_data_for_MC.GetPtrFloat("AK5jetMass");
      		Float_t *AK5jetCSV=inner_data_for_MC.GetPtrFloat("AK5jetCSV");

  		Float_t *AK5jetNHadEF=inner_data_for_MC.GetPtrFloat("AK5jetNHadEF");
  		Float_t *AK5jetNEmEF=inner_data_for_MC.GetPtrFloat("AK5jetNEmEF");
  		Float_t *AK5jetCHadEF=inner_data_for_MC.GetPtrFloat("AK5jetCHadEF");
  		Float_t *AK5jetCEmEF=inner_data_for_MC.GetPtrFloat("AK5jetCEmEF");
  		Float_t *AK5jetCMulti=inner_data_for_MC.GetPtrFloat("AK5jetCMulti");

		//met
		Float_t pfMetCorrPt=inner_data_for_MC.GetFloat("pfMetCorrPt");
		Float_t pfMetCorrPhi=inner_data_for_MC.GetFloat("pfMetCorrPhi");


		event this_ev;

      		for (Int_t i=0;i<nEle;i++)
        	{
      			ele ele_i(elePt[i],eleEta[i],elePhi[i],eleEnergy[i],eleM[i],
				 eleDelEtaIn[i],eleDelPhiIn[i],eleSigIhIh[i],eleHoE[i],eleDxy[i],
				 eleDz[i],eleEoverP[i],eleCorrPfIso[i],elePassConv[i],eleMissingHits[i],
				 elePassID[i],eleUserTrkIso[i],eleUserCalIso[i],eleRho);
			this_ev.eles.push_back(ele_i);
		}

      		for (Int_t i=0;i<nMu;i++)
        	{
      			mu mu_i(muPt[i],muEta[i],muPhi[i],0,muM[i], // no muEnergy
		 		isGlobalMuon[i],isTrackerMuon[i],muTrkLayers[i],muPixelHits[i],muHits[i],muMatches[i],mudxy[i],mudz[i],        				
				nuCorrPfIso[i],muPassID[i],muCorrTrkIso[i]);
			this_ev.mus.push_back(mu_i);
		}
		
      		for (Int_t i=0;i<AK5nJet;i++)
        	{
      			AK5jet jet_i(AK5jetPt[i],AK5jetEta[i],AK5jetPhi[i],AK5jetEn[i],AK5jetMass[i],AK5jetCSV[i],
				AK5jetNHadEF[i],AK5jetNEmEF[i],AK5jetCHadEF[i],AK5jetCEmEF[i],AK5jetCMulti[i]);
			this_ev.AK5jets.push_back(jet_i);
		}
      		for (Int_t i=0;i<CA8nJet;i++)
        	{
      			CA8jet jet_i(CA8jetPt[i],CA8jetEta[i],CA8jetPhi[i],CA8jetEn[i],CA8jetMass[i],CA8jetCSV[i],
				CA8jetNHadEF[i],CA8jetNEmEF[i],CA8jetCHadEF[i],CA8jetCEmEF[i],CA8jetCMulti[i]);
			this_ev.CA8jets.push_back(jet_i);

			vector<CA8subjet> this_subj_vector;
			for (int j=0;j<CA8subjetPrunedPt->size();j++)
			{

				CA8subjet this_subj(CA8subjetPrunedPt[i][j],CA8subjetPrunedEta[i][j],CA8subjetPrunedPhi[i][j],CA8subjetPrunedEn[i][j],
					CA8subjetPrunedMass[i][j],CA8subjetPrunedCSV[i][j]);
				this_subj_vector.push_back(this_subj);	 
			}
			this_ev.CA8subjets.push_back(this_subj_vector);
		}
		for(int i=0;i<nGenPar;i++)  //gen par loop
		{
			gen_par this_g = gen_par(genParPt[i], genParEta[i], genParPhi[i], genParE[i], genParM[i],
				genParId[i], genParIndex[i], genMomParId[i], genMo1[i], genMo2[i], genParSt[i]);
			this_ev.gen_pars.push_back(this_g);
		}
      		met met_i(pfMetCorrPt,pfMetCorrPhi);
		this_ev.missing_et=met_i;


		// get CA8jet after deoverlap with other sub jet and good lepton in every event
     		for (Int_t i=0;i<CA8nJet;i++)
        	{
			vector<CA8subjet> this_subj_vector;
			CA8jet this_j = this_ev.CA8jets[i];
	
			bool subjet_overlap=false;
			for (int j=0;j<this_ev.CA8subjets[i].size();j++)
			{
				CA8subjet this_subj = this_ev.CA8subjets[i][j];
				for (int k=0;k<this_ev.CA8subjets[i].size();k++)
				{
					if (k==j){continue;}
					if(delta_R(this_ev.CA8subjets[i][k],this_subj)<=0.3)
					{ subjet_overlap=true; break;}
				}
			}
			if (subjet_overlap==true){continue;}



			bool overlap_with_lepton=false;
			for (int elei=0;elei<this_ev.eles.size();elei++)
			{	
				ele this_ele = this_ev.eles[elei];
				if (!is_pass_ele_loose_id(this_ele) || !is_pass_ele_iso(this_ele)){continue;}
				if (delta_R(this_j, this_ele)<0.8){overlap_with_lepton=true;}
			}

			for (int mui=0;mui<this_ev.mus.size();mui++)
			{
				mu this_mu = this_ev.mus[mui];
				if (!is_pass_mu_tight_id(this_mu) || !is_pass_mu_iso(this_mu)){continue;}
				if (delta_R(this_j, this_mu)<0.8){overlap_with_lepton=true;}
			}
			if (overlap_with_lepton){ continue;}
			
			for (int j=0;j<CA8subjetPrunedPt->size();j++)
			{ this_subj_vector.push_back(this_ev.CA8subjets[i][j]); }

			this_ev.CA8subjets_deoverlap_with_lepton_and_subjet.push_back(this_subj_vector);
		}

		events_MC.push_back(this_ev);

	}

	// event loop : set up data
  	for (Long64_t Nth = 0; Nth < Nev_data; Nth++)
    	{
 		inner_data_for_data.GetEntry(Nth);


      		// CA8jet var
      		Int_t CA8nJet=inner_data_for_data.GetInt("CA8nJet");
      		Float_t *CA8jetPt=inner_data_for_data.GetPtrFloat("CA8jetPt");  
      		Float_t *CA8jetEta=inner_data_for_data.GetPtrFloat("CA8jetEta"); 
      		Float_t *CA8jetPhi=inner_data_for_data.GetPtrFloat("CA8jetPhi"); 
     		Float_t *CA8jetEn=inner_data_for_data.GetPtrFloat("CA8jetEn");
     		Float_t *CA8jetMass=inner_data_for_data.GetPtrFloat("CA8jetMass");
      		Float_t *CA8jetCSV=inner_data_for_data.GetPtrFloat("CA8jetCSV");

  		Float_t *CA8jetNHadEF=inner_data_for_data.GetPtrFloat("CA8jetNHadEF");
  		Float_t *CA8jetNEmEF=inner_data_for_data.GetPtrFloat("CA8jetNEmEF");
  		Float_t *CA8jetCHadEF=inner_data_for_data.GetPtrFloat("CA8jetCHadEF");
  		Float_t *CA8jetCEmEF=inner_data_for_data.GetPtrFloat("CA8jetCEmEF");
  		Float_t *CA8jetCMulti=inner_data_for_data.GetPtrFloat("CA8jetCMulti");

		// muon var
      		Int_t nMu =inner_data_for_data.GetInt("nMu");
      		Float_t *muPt=inner_data_for_data.GetPtrFloat("muPt");
   		Float_t *muEta=inner_data_for_data.GetPtrFloat("muEta");
   		Float_t *muPhi=inner_data_for_data.GetPtrFloat("muPhi");
   		//no muEnergy!
   		Float_t *muM=inner_data_for_data.GetPtrFloat("muM");

		Int_t*   isGlobalMuon = inner_data_for_data.GetPtrInt("isGlobalMuon");
    		Int_t*   isTrackerMuon= inner_data_for_data.GetPtrInt("isTrackerMuon");
    		Int_t*   muTrkLayers  = inner_data_for_data.GetPtrInt("muTrkLayers");
    		Int_t*   muPixelHits  = inner_data_for_data.GetPtrInt("muPixelHits");
    		Int_t*   muHits       = inner_data_for_data.GetPtrInt("muHits");
    		Int_t*   muMatches    = inner_data_for_data.GetPtrInt("muMatches");
    		Float_t* mudxy        = inner_data_for_data.GetPtrFloat("mudxy");
    		Float_t* mudz         = inner_data_for_data.GetPtrFloat("mudz");

   		Float_t *nuCorrPfIso=inner_data_for_data.GetPtrFloat("muCorrPfIso");				
		Int_t* muPassID = inner_data_for_data.GetPtrInt("muPassID");
		Float_t* muCorrTrkIso = inner_data_for_data.GetPtrFloat("muCorrTrkIso");

      		// ele var
      		Int_t nEle =inner_data_for_data.GetInt("nEle");
      		Float_t *elePt=inner_data_for_data.GetPtrFloat("elePt");
   		Float_t *eleEta=inner_data_for_data.GetPtrFloat("eleEta");
   		Float_t *elePhi=inner_data_for_data.GetPtrFloat("elePhi");
   		Float_t *eleEnergy=inner_data_for_data.GetPtrFloat("eleEnergy");
   		Float_t *eleM=inner_data_for_data.GetPtrFloat("eleM");

		Float_t *eleDelEtaIn=inner_data_for_data.GetPtrFloat("eleDelEtaIn");
		Float_t *eleDelPhiIn=inner_data_for_data.GetPtrFloat("eleDelPhiIn");
		Float_t *eleSigIhIh=inner_data_for_data.GetPtrFloat("eleSigIhIh");
		Float_t *eleHoE=inner_data_for_data.GetPtrFloat("eleHoE");
		Float_t *eleDxy=inner_data_for_data.GetPtrFloat("eleDxy");
		Float_t *eleDz=inner_data_for_data.GetPtrFloat("eleDz");
		Float_t *eleEoverP=inner_data_for_data.GetPtrFloat("eleEoverP");
		Float_t *eleCorrPfIso=inner_data_for_data.GetPtrFloat("eleCorrPfIso");
		Int_t *elePassConv=inner_data_for_data.GetPtrInt("elePassConv");
		Float_t *eleMissingHits=inner_data_for_data.GetPtrFloat("eleMissingHits");

		Int_t *elePassID=inner_data_for_data.GetPtrInt("elePassID");
		Float_t *eleUserTrkIso=inner_data_for_data.GetPtrFloat("eleUserTrkIso");
		Float_t *eleUserCalIso=inner_data_for_data.GetPtrFloat("eleUserCalIso");
		Float_t eleRho=inner_data_for_data.GetFloat("eleRho");

		

		// CA8 subjet var
		vector<Float_t> *CA8subjetPrunedPt=inner_data_for_data.GetPtrVectorFloat("CA8subjetPrunedPt");
		vector<Float_t> *CA8subjetPrunedEta=inner_data_for_data.GetPtrVectorFloat("CA8subjetPrunedEta");
		vector<Float_t> *CA8subjetPrunedPhi=inner_data_for_data.GetPtrVectorFloat("CA8subjetPrunedPhi");
		vector<Float_t> *CA8subjetPrunedEn=inner_data_for_data.GetPtrVectorFloat("CA8subjetPrunedEn");
		vector<Float_t> *CA8subjetPrunedMass=inner_data_for_data.GetPtrVectorFloat("CA8subjetPrunedMass");
		vector<Float_t> *CA8subjetPrunedCSV=inner_data_for_data.GetPtrVectorFloat("CA8subjetPrunedCSV");
		vector<Int_t> *CA8subjetPrunedPartonFlavor=inner_data_for_data.GetPtrVectorInt("CA8subjetPrunedPartonFlavor");

      		// AK5jet var
      		Int_t AK5nJet=inner_data_for_data.GetInt("AK5nJet");
      		Float_t *AK5jetPt=inner_data_for_data.GetPtrFloat("AK5jetPt");  
      		Float_t *AK5jetEta=inner_data_for_data.GetPtrFloat("AK5jetEta"); 
      		Float_t *AK5jetPhi=inner_data_for_data.GetPtrFloat("AK5jetPhi"); 
     		Float_t *AK5jetEn=inner_data_for_data.GetPtrFloat("AK5jetEn");
     		Float_t *AK5jetMass=inner_data_for_data.GetPtrFloat("AK5jetMass");
      		Float_t *AK5jetCSV=inner_data_for_data.GetPtrFloat("AK5jetCSV");

  		Float_t *AK5jetNHadEF=inner_data_for_data.GetPtrFloat("AK5jetNHadEF");
  		Float_t *AK5jetNEmEF=inner_data_for_data.GetPtrFloat("AK5jetNEmEF");
  		Float_t *AK5jetCHadEF=inner_data_for_data.GetPtrFloat("AK5jetCHadEF");
  		Float_t *AK5jetCEmEF=inner_data_for_data.GetPtrFloat("AK5jetCEmEF");
  		Float_t *AK5jetCMulti=inner_data_for_data.GetPtrFloat("AK5jetCMulti");

		//met
		Float_t pfMetCorrPt=inner_data_for_data.GetFloat("pfMetCorrPt");
		Float_t pfMetCorrPhi=inner_data_for_data.GetFloat("pfMetCorrPhi");


		event this_ev;

      		for (Int_t i=0;i<nEle;i++)
        	{
      			ele ele_i(elePt[i],eleEta[i],elePhi[i],eleEnergy[i],eleM[i],
				 eleDelEtaIn[i],eleDelPhiIn[i],eleSigIhIh[i],eleHoE[i],eleDxy[i],
				 eleDz[i],eleEoverP[i],eleCorrPfIso[i],elePassConv[i],eleMissingHits[i],
				 elePassID[i],eleUserTrkIso[i],eleUserCalIso[i],eleRho);
			this_ev.eles.push_back(ele_i);
		}

      		for (Int_t i=0;i<nMu;i++)
        	{
      			mu mu_i(muPt[i],muEta[i],muPhi[i],0,muM[i], // no muEnergy
		 		isGlobalMuon[i],isTrackerMuon[i],muTrkLayers[i],muPixelHits[i],muHits[i],muMatches[i],mudxy[i],mudz[i],        				
				nuCorrPfIso[i],muPassID[i],muCorrTrkIso[i]);
			this_ev.mus.push_back(mu_i);
		}
		
      		for (Int_t i=0;i<AK5nJet;i++)
        	{
      			AK5jet jet_i(AK5jetPt[i],AK5jetEta[i],AK5jetPhi[i],AK5jetEn[i],AK5jetMass[i],AK5jetCSV[i],
				AK5jetNHadEF[i],AK5jetNEmEF[i],AK5jetCHadEF[i],AK5jetCEmEF[i],AK5jetCMulti[i]);
			this_ev.AK5jets.push_back(jet_i);
		}
      		for (Int_t i=0;i<CA8nJet;i++)
        	{
      			CA8jet jet_i(CA8jetPt[i],CA8jetEta[i],CA8jetPhi[i],CA8jetEn[i],CA8jetMass[i],CA8jetCSV[i],
				CA8jetNHadEF[i],CA8jetNEmEF[i],CA8jetCHadEF[i],CA8jetCEmEF[i],CA8jetCMulti[i]);
			this_ev.CA8jets.push_back(jet_i);

			vector<CA8subjet> this_subj_vector;
			for (int j=0;j<CA8subjetPrunedPt->size();j++)
			{

				CA8subjet this_subj(CA8subjetPrunedPt[i][j],CA8subjetPrunedEta[i][j],CA8subjetPrunedPhi[i][j],CA8subjetPrunedEn[i][j],
					CA8subjetPrunedMass[i][j],CA8subjetPrunedCSV[i][j]);
				this_subj_vector.push_back(this_subj);	 
			}
			this_ev.CA8subjets.push_back(this_subj_vector);
		}

      		met met_i(pfMetCorrPt,pfMetCorrPhi);
		this_ev.missing_et=met_i;


		// get CA8jet after deoverlap with other sub jet and good lepton in every event
     		for (Int_t i=0;i<CA8nJet;i++)
        	{
			vector<CA8subjet> this_subj_vector;
			CA8jet this_j = this_ev.CA8jets[i];
	
			bool subjet_overlap=false;
			for (int j=0;j<this_ev.CA8subjets[i].size();j++)
			{
				CA8subjet this_subj = this_ev.CA8subjets[i][j];
				for (int k=0;k<this_ev.CA8subjets[i].size();k++)
				{
					if (k==j){continue;}
					if(delta_R(this_ev.CA8subjets[i][k],this_subj)<=0.3)
					{ subjet_overlap=true; break;}
				}
			}
			if (subjet_overlap==true){continue;}



			bool overlap_with_lepton=false;
			for (int elei=0;elei<this_ev.eles.size();elei++)
			{	
				ele this_ele = this_ev.eles[elei];
				if (!is_pass_ele_loose_id(this_ele) || !is_pass_ele_iso(this_ele)){continue;}
				if (delta_R(this_j, this_ele)<0.8){overlap_with_lepton=true;}
			}

			for (int mui=0;mui<this_ev.mus.size();mui++)
			{
				mu this_mu = this_ev.mus[mui];
				if (!is_pass_mu_tight_id(this_mu) || !is_pass_mu_iso(this_mu)){continue;}
				if (delta_R(this_j, this_mu)<0.8){overlap_with_lepton=true;}
			}
			if (overlap_with_lepton){ continue;}
			
			for (int j=0;j<CA8subjetPrunedPt->size();j++)
			{ this_subj_vector.push_back(this_ev.CA8subjets[i][j]); }

			this_ev.CA8subjets_deoverlap_with_lepton_and_subjet.push_back(this_subj_vector);
		}

		events_data.push_back(this_ev);

	}
	
	// event loop : get size of fraction ratio matrix
	int max_N_of_candidate_sub_bjet=0;
	int max_N_of_candidate_sub_nbjet=0;
  	for (Long64_t Nth = 0; Nth < Nev_MC; Nth++)
    	{
		//cout<<endl<<"=====================event:"<<Nth<<"==============================="<<endl;
	
		// matching gen par and CA8subjet

		if(!is_pass_ev_selection(events_MC[Nth])){continue;}

 		//to check this event has 2 b-CA8subjet, to check deltaR of this 2 subjet > 0.3
		int N_of_CA8subjet=0;
		int N_of_candidate_sub_bjet=0;
		int N_of_candidate_sub_nbjet=0;
		double R=0.3;

		//vector< vector<CA8subjet> > this_CA8subjets=events_MC[Nth].CA8subjets;
		vector< vector<CA8subjet> > this_CA8subjets=events_MC[Nth].CA8subjets_deoverlap_with_lepton_and_subjet;
		for (int i=0;i<this_CA8subjets.size();i++)
		{	
			for (int j=0;j<this_CA8subjets[i].size();j++)
			{				
				CA8subjet this_j=this_CA8subjets[i][j];

				if(!is_pass_pteta(this_j)){continue;}

				N_of_CA8subjet++;
				bool matching_with_b=false;
				for(int ii=0;ii<events_MC[Nth].gen_pars.size();ii++)  //gen par loop
				{
					gen_par this_g = events_MC[Nth].gen_pars[ii];
					if (delta_R(this_j,this_g)<=R  && is_wanted_b(this_g))
					{
						matching_with_b=true; 
					}
						
				}
				if (matching_with_b){ N_of_candidate_sub_bjet++;}

			}
		}

		N_available_event_MC++;
		N_of_candidate_sub_nbjet=N_of_CA8subjet-N_of_candidate_sub_bjet;
		if (max_N_of_candidate_sub_bjet<N_of_candidate_sub_bjet){ max_N_of_candidate_sub_bjet=N_of_candidate_sub_bjet; }
		if (max_N_of_candidate_sub_nbjet<N_of_candidate_sub_nbjet){ max_N_of_candidate_sub_nbjet=N_of_candidate_sub_nbjet; }
		

	}
	max_true_b=max_N_of_candidate_sub_bjet;	
	max_true_nb=max_N_of_candidate_sub_nbjet;
	/*	
	Nk_from_rec = vector<Int_t>(max_true_b+max_true_nb+1,0);
	Nt_from_rec = vector<Int_t>(max_true_b+max_true_nb+1,0);
	Nk_from_data = vector<Int_t>(max_true_b+max_true_nb+1,0);
	Nt_from_data = vector<Int_t>(max_true_b+max_true_nb+1,0);
	*/
	Nk_from_rec = vector<Int_t>(100,0);
	Nt_from_rec = vector<Int_t>(100,0);
	Nk_from_data = vector<Int_t>(100,0);
	Nt_from_data = vector<Int_t>(100,0);
		
	
	cout<<"max_true_b="<<max_true_b<<", max_true_nb="<<max_true_nb<<";    ";
	vector< vector<double> > mask(max_N_of_candidate_sub_bjet+1, vector<double>(max_N_of_candidate_sub_nbjet+1,0));
	fraction_ratio=mask;

	// event loop : get fraction ratio matrix
  	for (Long64_t Nth = 0; Nth < Nev_MC; Nth++)
    	{
		//cout<<endl<<"=====================event:"<<Nth<<"==============================="<<endl;
	
		// matching gen par and CA8subjet
		if(!is_pass_ev_selection(events_MC[Nth])){continue;}

 		//to check this event has 2 b-CA8subjet, to check deltaR of this 2 subjet > 0.3
		int N_of_CA8subjet=0;
		int N_of_candidate_sub_bjet=0;
		int N_of_candidate_sub_nbjet=0;

		double R=0.3;

		//vector< vector<CA8subjet> > this_CA8subjets=events_MC[Nth].CA8subjets;
		vector< vector<CA8subjet> > this_CA8subjets=events_MC[Nth].CA8subjets_deoverlap_with_lepton_and_subjet;
		for (int i=0;i<this_CA8subjets.size();i++)
		{	
			for (int j=0;j<this_CA8subjets[i].size();j++)
			{
				CA8subjet this_j=this_CA8subjets[i][j];

				if(!is_pass_pteta(this_j)){continue;}

				N_of_CA8subjet++;
				bool matching_with_b=false;
				for(int ii=0;ii<events_MC[Nth].gen_pars.size();ii++)  //gen par loop
				{
					gen_par this_g = events_MC[Nth].gen_pars[ii];
					if (delta_R(this_j,this_g)<=R  && is_wanted_b(this_g))
					{matching_with_b=true;}
						
				}
				if (matching_with_b){ N_of_candidate_sub_bjet++;}

			}
		}

		N_of_candidate_sub_nbjet=N_of_CA8subjet-N_of_candidate_sub_bjet;
		fraction_ratio[N_of_candidate_sub_bjet][N_of_candidate_sub_nbjet]+=(1/double(N_available_event_MC));
	}	






	// event loop : counting b-tagging for MC
  	for (Long64_t Nth = 0; Nth < Nev_MC; Nth++)
    	{
		//cout<<endl<<"=====================event:"<<Nth<<"==============================="<<endl;
		




		//test1
		for(int i=0;i<events_MC[Nth].CA8jets.size();i++)
		{
			if(events_MC[Nth].CA8jets[i].csv<0 || events_MC[Nth].CA8jets[i].csv>1){continue;}
			CA8CSV_b_evcut->Fill(events_MC[Nth].CA8jets[i].csv);
		}
		for (int i=0;i<events_MC[Nth].CA8subjets_deoverlap_with_lepton_and_subjet.size();i++)
		{
			for (int j=0;j<events_MC[Nth].CA8subjets_deoverlap_with_lepton_and_subjet[i].size();j++)
			{
				if(events_MC[Nth].CA8subjets_deoverlap_with_lepton_and_subjet[i][j].csv<0 || events_MC[Nth].CA8subjets_deoverlap_with_lepton_and_subjet[i][j].csv>1){continue;}
				CA8subjetCSV_b_evcut->Fill(events_MC[Nth].CA8subjets_deoverlap_with_lepton_and_subjet[i][j].csv);
			}
		}
		

		if(!is_pass_ev_selection(events_MC[Nth])){continue;}

		//test2
		for(int i=0;i<events_MC[Nth].CA8jets.size();i++)
		{
			if(events_MC[Nth].CA8jets[i].csv<0 || events_MC[Nth].CA8jets[i].csv>1){continue;}
			CA8CSV_a_evcut->Fill(events_MC[Nth].CA8jets[i].csv);
		}
		for (int i=0;i<events_MC[Nth].CA8subjets_deoverlap_with_lepton_and_subjet.size();i++)
		{
			for (int j=0;j<events_MC[Nth].CA8subjets_deoverlap_with_lepton_and_subjet[i].size();j++)
			{
				if(events_MC[Nth].CA8subjets_deoverlap_with_lepton_and_subjet[i][j].csv<0 || events_MC[Nth].CA8subjets_deoverlap_with_lepton_and_subjet[i][j].csv>1){continue;}
				CA8subjetCSV_a_evcut->Fill(events_MC[Nth].CA8subjets_deoverlap_with_lepton_and_subjet[i][j].csv);
			}
		}
		
		//counting
		for(int i=0;i<events_MC[Nth].CA8jets.size();i++){ N_CA8jet_before_deoverlap++;}
		for(int i=0;i<events_MC[Nth].CA8subjets_deoverlap_with_lepton_and_subjet.size();i++){ N_CA8jet_after_deoverlap++;}		


		//vector< vector<CA8subjet> > this_CA8subjets=events_MC[Nth].CA8subjets;
		vector< vector<CA8subjet> > this_CA8subjets=events_MC[Nth].CA8subjets_deoverlap_with_lepton_and_subjet;
		
		
 		//calculate gen jets
		for (int i=0;i<this_CA8subjets.size();i++)
		{
			for (int j=0;j<this_CA8subjets[i].size();j++)
			{
				CA8subjet this_j=this_CA8subjets[i][j];
	
				if(!is_pass_pteta(this_j)){continue;}
		
				n_CA8sj++;
				string this_j_is="";
							
				// to see if this sj is b or nb
			
				double R=0.3;
				jet_cone this_jet_cone;
			
				for(int ii=0;ii<events_MC[Nth].gen_pars.size();ii++)  //gen par loop
				{
					gen_par this_g = events_MC[Nth].gen_pars[ii];
					if (delta_R(this_j,this_g)<=R)
					{
						int this_g_id=abs(this_g.id);
						if(is_wanted_b(this_g)){this_jet_cone.gen_b++;}
						if(this_g_id<=4 && this_g_id>=0){this_jet_cone.gen_nb++;}
						if(this_g_id==11){this_jet_cone.gen_ele++;}
						if(this_g_id==13){this_jet_cone.gen_mu++;}				
					}	
				}
				if (this_jet_cone.gen_b>0)
				{
					gen_j++; gen_b++;
					if(this_jet_cone.gen_b==1){this_j_is="b";}
					else if (this_jet_cone.gen_b==2){this_j_is="2b";}				
				}
				else{this_j_is="nb"; gen_j++; gen_nb++;} //actually, this_j matching with nbq, ele, or mu, or nothing. 


			
				//get 4p
				if (this_jet_cone.gen_b>0)
				{
					if ( is_pass_pteta(this_j))
					{
						gen_j_pass_cut++;
						gen_b_pass_cut++;
				
						if(btagging(this_j))
						{ gen_j_pass_cut_btagging++; gen_b_pass_cut_btagging++; }
					}
				}
				else if (this_j_is=="nb")
				{
					if ( is_pass_pteta(this_j))
					{
						gen_j_pass_cut++;
						gen_nb_pass_cut++;
				
						if(btagging(this_j))
						{ gen_j_pass_cut_btagging++; gen_nb_pass_cut_btagging++; }
					}
				}

			}
		}

		// proccess for rec jet 
		
		// counter
		Int_t N_btagging=0;
		Int_t N_jet_pass_cut=0;
		
		int N_CA8subjet_this_ev=0;
		for (int i=0;i<this_CA8subjets.size();i++)
        	{
			for (int j=0;j<this_CA8subjets[i].size();j++)
			{

				CA8subjet this_sj=this_CA8subjets[i][j];

				if(!is_pass_pteta(this_sj)){continue;}

				total_kk_rec++;
				N_CA8subjet_this_ev++;
				if ( is_pass_pteta(this_sj))
				{N_jet_pass_cut++;total_k_rec++;}
				else
				{continue;}
				if ( btagging(this_sj))
				{ N_btagging++;total_btag_pass_cut_rec++;}
				else {total_nbtag_pass_cut_rec++;}
			}
				
		}
		Nt_from_rec[N_btagging]++;
		Nk_from_rec[N_jet_pass_cut]++;
		
		//----------------------------k----------------------t-------------------------------
		//cout<<"this event have "<<N_CA8subjet_this_ev<<"jet, and "<<N_jet_pass_cut<< "jet pass cut, and "<<N_btagging<<" btagging."<<endl;


	
	} 
	
	
	// event loop : counting b-tagging for data
  	for (Long64_t Nth = 0; Nth < Nev_data; Nth++)
    	{
    		if(!is_pass_ev_selection(events_data[Nth])){continue;}
    			
    		//vector< vector<CA8subjet> > this_CA8subjets=events_data[Nth].CA8subjets;
		vector< vector<CA8subjet> > this_CA8subjets=events_data[Nth].CA8subjets_deoverlap_with_lepton_and_subjet;
		// counter
		Int_t N_btagging=0;
		Int_t N_jet_pass_cut=0;
		
    		int N_CA8subjet_this_ev=0;
		for (int i=0;i<this_CA8subjets.size();i++)
        	{
			for (int j=0;j<this_CA8subjets[i].size();j++)
			{

				CA8subjet this_sj=this_CA8subjets[i][j];

				if(!is_pass_pteta(this_sj)){continue;}

				total_kk_data++;
				N_CA8subjet_this_ev++;
				if ( is_pass_pteta(this_sj))
				{N_jet_pass_cut++;total_k_data++;}
				else
				{continue;}
				if ( btagging(this_sj))
				{ N_btagging++;total_btag_pass_cut_data++;}
				else {total_nbtag_pass_cut_data++;}
			}
				
		}
		//test
		if (N_btagging>=Nt_from_data.size() || N_jet_pass_cut>= Nk_from_data.size())
		{
			cout<<"N_btagging:"<<N_btagging<<endl;
			cout<<"Nt_from_data.size():"<<Nt_from_data.size()<<endl;
			cout<<"N_jet_pass_cut:"<<N_jet_pass_cut<<endl;
			cout<<"Nk_from_data.size():"<<Nk_from_data.size()<<endl;
			cout<<endl;
			
		}
		N_available_event_data++;
		Nt_from_data[N_btagging]++;
		Nk_from_data[N_jet_pass_cut]++;
    	}//event loop end here
    	
    	

	cout<<"N_available_event_MC="<<N_available_event_MC<<endl;
	cout<<"N_available_event_data="<<N_available_event_data<<endl;
	cout<<"=========================  gen level  ==========================================="<<endl<<endl;
	cout<<"total_kk_rec="<<gen_j<<"(b="<<gen_b<<", nb="<<gen_nb<<"),"<<endl;
	cout<<"total_k_rec="<<gen_j_pass_cut<<"(b="<<gen_b_pass_cut<<", nb="<<gen_nb_pass_cut<<")"<<endl;
	cout<<"total_t="<<gen_j_pass_cut_btagging<<"(b="<<gen_b_pass_cut_btagging<<", nb="<<gen_nb_pass_cut_btagging<<")"<<endl;
	cout<<endl;

	cout<<"=========================  rec level(analysis)  ==========================================="<<endl<<endl;
	cout<<"total_kk_rec="<<total_kk_rec<<endl;
	cout<<"total_k_rec="<<total_k_rec<<endl;
	cout<<"total_btag_pass_cut_rec="<<total_btag_pass_cut_rec<<endl;
	cout<<"total_nbtag_pas_cut="<<total_nbtag_pass_cut_rec<<endl;
	cout<<endl;

	cout<<"=========================  4p in gen level  ==========================================="<<endl<<endl;
	true_eff=(double)gen_b_pass_cut_btagging/(double)gen_b_pass_cut;
	true_mr=(double)gen_nb_pass_cut_btagging/(double)gen_nb_pass_cut;
	cout<<"eff="<<true_eff<<endl;
	cout<<"mr="<<true_mr<<endl;
	cout<<endl;


	cout<<"=========================  Nt_from_rec  ==========================================="<<endl<<endl;
	double sum_of_Nt_from_rec=0;
	double N_of_jet_from_Nt_from_rec=0;
	for (int i =0;i<Nt_from_rec.size();i++)
	{ 
		cout<<"Nt_from_rec["<<i<<"]:"<<Nt_from_rec[i]<<endl;
		sum_of_Nt_from_rec+=Nt_from_rec[i];
		N_of_jet_from_Nt_from_rec+=Nt_from_rec[i]*i;
	}
	cout<<"sum_of_Nt_from_rec="<<sum_of_Nt_from_rec<<endl;
	cout<<"N_of_jet_from_Nt_from_rec="<<N_of_jet_from_Nt_from_rec<<endl;
	cout<<endl;

	cout<<"===================  exp value of Nt=get_expvalue_of_Nt( true_eff, true_mr, i)  =============="<<endl<<endl;
	double sum_of_exp_value_of_Nt=0;
	double N_of_jet_exp_value_of_Nt=0;	
	for ( int i=0;i< max_true_b+max_true_nb+1;i++)
	{
		double this_exp_value_of_Nt=get_expvalue_of_Nt( true_eff, true_mr, i);
		cout<<"exp value of number of event that have "<<i<<" jet pass cut & btagging:"<<this_exp_value_of_Nt<<endl;
		sum_of_exp_value_of_Nt+=this_exp_value_of_Nt;
		N_of_jet_exp_value_of_Nt+=this_exp_value_of_Nt*i;
	}
	cout<<"sum_of_exp_value_of_Nt="<<sum_of_exp_value_of_Nt<<endl;
	cout<<"N_of_jet_exp_value_of_Nt="<<N_of_jet_exp_value_of_Nt<<endl;
	cout<<endl;

	cout<<"============================  fraction ratio  ========================================="<<endl<<endl;
	double sum_of_fraction_ratio=0;
	double N_of_jet_from_fraction_ratio=0;
	for (int i=0;i<fraction_ratio.size();i++)
	{
		
		for (int j=0;j<fraction_ratio[i].size();j++)
		{ 
			cout<<fraction_ratio[i][j]<<",    ";
			sum_of_fraction_ratio+=fraction_ratio[i][j];	
			N_of_jet_from_fraction_ratio+=(i+j)*fraction_ratio[i][j]*N_available_event_MC;
		}
		cout<<endl;
		
	}
	cout<<"sum_of_fraction_ratio="<<sum_of_fraction_ratio<<endl;
	cout<<"N_of_jet_from_fraction_ratio="<<N_of_jet_from_fraction_ratio<<endl;
	cout<<endl;


	//get btagging 2p
	// par_for_minuit(par_number,par_name, par_starting_value, step, min, max)
	double this_step =0.001;	
	par_for_minuit eff_rec(0,"eff_rec", 0.7, this_step ,0+this_step,1-this_step);
	par_for_minuit mr_rec(1,"mr_rec", 0.1, this_step ,0+this_step,1-this_step);	
	vector<par_for_minuit> pars_btagging2p;
	pars_btagging2p.push_back(eff_rec);
	pars_btagging2p.push_back(mr_rec);
	vector<par_err_pair_for_minuit> results_btagging2p=get_min_par_btagging2p(pars_btagging2p);
	best_eff_rec=results_btagging2p[0].v;
	best_mr_rec=results_btagging2p[1].v;


	cout<<"=========================  analysis result  ==========================================="<<endl<<endl;
	cout<<",best_eff_rec="<<best_eff_rec<<"+-"<<results_btagging2p[0].err<<endl;
	cout<<",best_mr_rec="<<best_mr_rec<<"+-"<<results_btagging2p[1].err<<endl;
	cout<<endl;

	cout<<"=========================  ratio rec/gen  ==========================================="<<endl<<endl;
	cout<<",best_eff_rec/true_eff="<<best_eff_rec/true_eff<<endl;
	cout<<",best_mr_rec/true_mr="<<best_mr_rec/true_mr<<endl;
	cout<<endl;

	cout<<"=================  counting # of CA8jets before/after deoverlap with good lepton  ======================"<<endl<<endl;
	cout<<"N_CA8jet_before_deoverlap:"<<N_CA8jet_before_deoverlap<<endl;
	cout<<"N_CA8jet_after_deoverlap:"<<N_CA8jet_after_deoverlap<<endl;
	cout<<"fraction:"<<((double)N_CA8jet_before_deoverlap-(double)N_CA8jet_after_deoverlap)/(double)N_CA8jet_before_deoverlap<<endl;

//*/

/*
  	//event loop : analyzer
  	for (Long64_t Nth = 0; Nth < Nev_MC; Nth++)
    	{
		cout<<"=====================event:"<<Nth<<"==============================="<<endl;
		


      		inner_data_for_MC.GetEntry(Nth);

		// genpar var
		Int_t *genParId=inner_data_for_MC.GetPtrInt("genParId");
		Int_t *genMomParId=inner_data_for_MC.GetPtrInt("genMomParId");
		Int_t nGenPar=inner_data_for_MC.GetInt("nGenPar");
		Int_t *genParSt=inner_data_for_MC.GetPtrInt("genParSt");
		Int_t nGenJet=inner_data_for_MC.GetInt("nGenJet");
		Int_t *genMo1=inner_data_for_MC.GetPtrInt("genMo1");


      		// AK5jet var
      		Int_t AK5nJet=inner_data_for_MC.GetInt("AK5nJet");
      		Float_t *AK5jetPt=inner_data_for_MC.GetPtrFloat("AK5jetPt");  
      		Float_t *AK5jetEta=inner_data_for_MC.GetPtrFloat("AK5jetEta"); 
      		Float_t *AK5jetPhi=inner_data_for_MC.GetPtrFloat("AK5jetPhi"); 
     		Float_t *AK5jetEn=inner_data_for_MC.GetPtrFloat("AK5jetEn");
     		Float_t *AK5jetMass=inner_data_for_MC.GetPtrFloat("AK5jetMass");
      		Float_t *AK5jetCSV=inner_data_for_MC.GetPtrFloat("AK5jetCSV");

  		Float_t *AK5jetNHadEF=inner_data_for_MC.GetPtrFloat("AK5jetNHadEF");
  		Float_t *AK5jetNEmEF=inner_data_for_MC.GetPtrFloat("AK5jetNEmEF");
  		Float_t *AK5jetCHadEF=inner_data_for_MC.GetPtrFloat("AK5jetCHadEF");
  		Float_t *AK5jetCEmEF=inner_data_for_MC.GetPtrFloat("AK5jetCEmEF");
  		Float_t *AK5jetCMulti=inner_data_for_MC.GetPtrFloat("AK5jetCMulti");
		

      		// CA8jet var
      		Int_t CA8nJet=inner_data_for_MC.GetInt("CA8nJet");
      		Float_t *CA8jetPt=inner_data_for_MC.GetPtrFloat("CA8jetPt");  
      		Float_t *CA8jetEta=inner_data_for_MC.GetPtrFloat("CA8jetEta"); 
      		Float_t *CA8jetPhi=inner_data_for_MC.GetPtrFloat("CA8jetPhi"); 
     		Float_t *CA8jetEn=inner_data_for_MC.GetPtrFloat("CA8jetEn");
     		Float_t *CA8jetMass=inner_data_for_MC.GetPtrFloat("CA8jetMass");
      		Float_t *CA8jetCSV=inner_data_for_MC.GetPtrFloat("CA8jetCSV");

  		Float_t *CA8jetNHadEF=inner_data_for_MC.GetPtrFloat("CA8jetNHadEF");
  		Float_t *CA8jetNEmEF=inner_data_for_MC.GetPtrFloat("CA8jetNEmEF");
  		Float_t *CA8jetCHadEF=inner_data_for_MC.GetPtrFloat("CA8jetCHadEF");
  		Float_t *CA8jetCEmEF=inner_data_for_MC.GetPtrFloat("CA8jetCEmEF");
  		Float_t *CA8jetCMulti=inner_data_for_MC.GetPtrFloat("CA8jetCMulti");;                    
      		// ELE var
      		Int_t nEle =inner_data_for_MC.GetInt("nEle");
      		Float_t *elePt=inner_data_for_MC.GetPtrFloat("elePt");
   		Float_t *eleEta=inner_data_for_MC.GetPtrFloat("eleEta");
   		Float_t *elePhi=inner_data_for_MC.GetPtrFloat("elePhi");
   		Float_t *eleEnergy=inner_data_for_MC.GetPtrFloat("eleEnergy");
   		Float_t *eleM=inner_data_for_MC.GetPtrFloat("eleM");

		Float_t *eleDelEtaIn=inner_data_for_MC.GetPtrFloat("eleDelEtaIn");
		Float_t *eleDelPhiIn=inner_data_for_MC.GetPtrFloat("eleDelPhiIn");
		Float_t *eleSigIhIh=inner_data_for_MC.GetPtrFloat("eleSigIhIh");
		Float_t *eleHoE=inner_data_for_MC.GetPtrFloat("eleHoE");
		Float_t *eleDxy=inner_data_for_MC.GetPtrFloat("eleDxy");
		Float_t *eleDz=inner_data_for_MC.GetPtrFloat("eleDz");
		Float_t *eleEoverP=inner_data_for_MC.GetPtrFloat("eleEoverP");
		Float_t *eleCorrPfIso=inner_data_for_MC.GetPtrFloat("eleCorrPfIso");
		Int_t *elePassConv=inner_data_for_MC.GetPtrInt("elePassConv");
		Float_t *eleMissingHits=inner_data_for_MC.GetPtrFloat("eleMissingHits");

		// var

		Int_t N_pass_btagging=0;

		//cout<<"N_of_jet:"<<AK5nJet<<endl;


		// genpar OPRATION
		for (Int_t i=0;i<nGenPar;i++)
		{
			if (abs(genParId[i])<=8 && abs(genParId[i])>0 && genParSt[i]==3)
			{
				cout<<"*"<<i<<",";
			}
			
			if (abs(genParId[i])==5)
			{
				cout<<"Mo:"<<genMomParId[i]<<",";
			}
			
		}

		//cout<<"nGenJet:"<<nGenJet<<","<<"AK5nJet:"<<AK5nJet<<","<<"CA8nJet:"<<CA8nJet;
		
		for (Int_t i=0;i<nGenJet;i++)
		{
			if (abs(genParId[i])==5)
			{
			}
			
		}







      		// jet OPERATION
      		for (Int_t i=0;i<AK5nJet;i++)
        	{
      			AK5jet jet_i(AK5jetPt[i],AK5jetEta[i],AK5jetPhi[i],AK5jetEn[i],AK5jetMass[i],AK5jetCSV[i],
				AK5jetNHadEF[i],AK5jetNEmEF[i],AK5jetCHadEF[i],AK5jetCEmEF[i],AK5jetCMulti[i]);
			
            		for (Int_t j =0;j<i;j++)
	      		{
      				AK5jet jet_j(AK5jetPt[j],AK5jetEta[j],AK5jetPhi[j],AK5jetEn[j],AK5jetMass[j],AK5jetCSV[j],
				AK5jetNHadEF[j],AK5jetNEmEF[j],AK5jetCHadEF[j],AK5jetCEmEF[j],AK5jetCMulti[j]);
				// jet loose ID
				if(is_pass_jet_loose_id(jet_i) && is_pass_jet_loose_id(jet_j)){}
				else {continue;}
				TLorentzVector jet_i_lv;
				jet_i_lv.SetPtEtaPhiE(jet_i.pt, jet_i.eta, jet_i.phi, jet_i.en);
				TLorentzVector jet_j_lv;
				jet_j_lv.SetPtEtaPhiE(jet_j.pt, jet_j.eta, jet_j.phi, jet_j.en);

				TLorentzVector H_lv;
				H_lv = jet_i_lv+jet_j_lv;
				H_IM->Fill(H_lv.M());

				// jet CSV
				if (is_pass_csvl(jet_i) && is_pass_csvl(jet_j) )
				{ H_IM_csvl->Fill(H_lv.M());}
				if (is_pass_csvm(jet_i) && is_pass_csvm(jet_j) )
				{ H_IM_csvm->Fill(H_lv.M());}


					
                
	      		}


        	}




     		// ELE OPERATION
      		
		for (Int_t i=0;i<nEle;i++)
		{
      			ele ele_i(elePt[i],eleEta[i],elePhi[i],eleEnergy[i],eleM[i],
				eleDelEtaIn[i],eleDelPhiIn[i],eleSigIhIh[i],eleHoE[i],
				eleDxy[i],eleDz[i],eleEoverP[i],eleCorrPfIso[i],elePassConv[i],eleMissingHits[i]);

			if(!is_pass_ele_loose_id(ele_i)){continue;}
			TLorentzVector ele_i_lv;
			ele_i_lv.SetPtEtaPhiE(ele_i.pt, ele_i.eta, ele_i.phi, ele_i.en);

			for(Int_t j=0;j<1;j++)
			{
      				ele ele_j(elePt[j],eleEta[j],elePhi[j],eleEnergy[j],eleM[j],
					eleDelEtaIn[j],eleDelPhiIn[j],eleSigIhIh[j],eleHoE[j],
					eleDxy[j],eleDz[j],eleEoverP[j],eleCorrPfIso[j],elePassConv[j],eleMissingHits[j]);

				if(!is_pass_ele_loose_id(ele_j)){continue;}
				TLorentzVector ele_j_lv;
				ele_j_lv.SetPtEtaPhiE(ele_j.pt, ele_j.eta, ele_j.phi, ele_j.en);
				TLorentzVector Zee_lv;
				Zee_lv = ele_i_lv+ele_j_lv;
				cout<<"Zee_IM:"<<Zee_lv.M()<<endl;
				Zee_IM->Fill(Zee_lv.M());


			}
	
		}

		
		cout<<endl;

		
    	}
*/
	H_IM->Write();
	H_IM_csvm->Write();
	H_IM_csvl->Write();
	Zee_IM->Write();
	
	CA8CSV_b_evcut->Write(); 
	CA8subjetCSV_b_evcut->Write();
	CA8CSV_a_evcut->Write();
	CA8subjetCSV_a_evcut->Write();

 	    
}
