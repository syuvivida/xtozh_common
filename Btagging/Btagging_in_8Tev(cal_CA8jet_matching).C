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

//class============================================================================
class PO
{
	public:
    	Float_t pt;
    	Float_t eta;
    	Float_t phi;
    	Float_t en;
	Float_t M;
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
 
    	ele(Float_t pt_,Float_t eta_,Float_t phi_, Float_t en_,Float_t M_,
			Float_t del_eta_in_, Float_t del_phi_in_, Float_t sig_ieie_, Float_t hoe_, 
			Float_t dxy_,Float_t dz_, Float_t eop_, Float_t corr_pf_iso_, Int_t pass_conv_, Float_t missing_hits_)
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
	
    	CA8jet(Float_t pt_,Float_t eta_,Float_t phi_, Float_t en_, Float_t M_,
		Float_t csv_,
		Float_t n_had_ef_,Float_t n_em_ef_,Float_t c_had_ef_,Float_t c_em_ef_,Float_t c_multi_)
		:jet(pt_, eta_, phi_, en_, M_,
		csv_,
		n_had_ef_, n_em_ef_, c_had_ef_, c_em_ef_, c_multi_)
    	{ }
};



class event_for_likelihood
{
	public:
	Int_t kk;
	Int_t k;
	Int_t t;
	event_for_likelihood(Int_t kk_, Int_t k_,Int_t t_)
	{ kk=kk_; k=k_; t=t_;}
};



class CA8dr8
{
	public:
	int gen_b;
	int gen_nb;
	int gen_ele;
	int gen_mu;
	CA8dr8(){ gen_b=0;gen_nb=0;gen_ele=0;gen_mu=0;}
	

};


//function======================================================================================================

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

Int_t C(Int_t n,Int_t m)
{
	if (m>n || m<0){return 0;}
	Int_t r_top=1;
	Int_t r_down=1;	
	Int_t subscript;	
	if((n-m)<(m)){subscript=n-m;}
	else {subscript=m;}
	for (Int_t i =0;i<subscript;i++)
	{ r_top=r_top*(n-i); r_down=r_down*(i+1);}
	return (r_top/r_down);
//	return (factorial(n)/(factorial(m)*factorial(n-m))); //n>=18, memory overflow
}



// general
Float_t delta_R(PO O1_,PO O2_)
{
	Float_t a = (O1_.eta-O2_.eta);
	Float_t b = (O1_.phi-O2_.phi);
	return sqrt(a*a+b*b);
}


//for gen par
bool is_wanted_b(gen_par g_)
{
	if (abs(g_.id)==5 && g_.status==3 && abs(g_.mid)==25)
	{ return true;}
	else
	{ return false;}
}

bool is_gen_j(gen_par g_)
{
	if (abs(g_.id)<=8 && abs(g_.id)>=1)
	{ return true;}
	else
	{ return false;}
}

// jet selection
bool is_pass_csvl(jet j_)
{
	if (j_.csv>0.244){return true;}
	else {return false;}
}

bool is_pass_csvm(jet j_)
{
	if (j_.csv>0.679){return true;}
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

bool is_pass_jet_pteta(jet j_)
{
	if(j_.pt<20){return false;}
	if(abs(j_.eta)>2.4){return false;}
	return true;

}


//ele selection
bool is_pass_ele_loose_id(ele e_)
{
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


        // calculate likelihood
	// b = treu_b#(no cut), kk = jet#(no cut), k = jet#(pass cut), t = btagg#(pass cut)
        // likelihhod:cut
        double get_log_likelihood_of_cut(Float_t bcut_eff, Float_t nbcut_eff, int b, int kk, int k)
        {
                double p_total = 0; 
                double p_pass_cut = 0;
            	for (int i = 0; i <= b; i++)
            	{
                	if ( k - i < 0 || kk - k < b - i) { continue; }              
                	p_pass_cut = C(k, i) * C(kk - k, b - i) * pow(bcut_eff, i) * pow(1 - bcut_eff, b - i) * pow(nbcut_eff, k - i) * pow(1 - nbcut_eff, kk - k - b + i);
  
                	p_total += p_pass_cut;
            	}
            	return log(p_total);
        }

        // likelihood:btagging
        double get_log_likelihood(Float_t bcut_eff, Float_t nbcut_eff, Float_t eff, Float_t mr, int b, int kk, int k, int t)
        {
            	double p_total = 0; //p_total=l(lowercase L)
            	double p_pass_cut = 0;
            	double p_pass_btagging = 0;
            	for (int i = 0; i <= b; i++)
            	{
                	if ( k - i < 0 || kk - k < b - i) { continue; }
                	p_pass_cut = C(k, i) * C(kk - k, b - i) * pow(bcut_eff, i) * pow(1 - bcut_eff, b - i) * pow(nbcut_eff, k - i) * pow(1 - nbcut_eff, kk - k - b + i);

                	int b_ = i;
                	p_pass_btagging = 0;
                	for (int j = 0; j <= b_; j++)
                	{
                    		if (t - j < 0 || k - t < b_ - j) {continue; }
                    		double this_p = C(t, j) * C(k - t, b_ - j) * pow(eff, j) * pow(1 - eff, b_ - j) * pow(mr, t - j) * pow(1 - mr, k - t - b_ + j);
                    		p_pass_btagging += this_p;              
                	}               
                p_total += p_pass_cut * p_pass_btagging;
            	}           
            	return log(p_total);
        }



//main =======================================================================================================================================================
void Btagging_in_8Tev()
{

	TFile output("output.root","recreate");

	//hist
	TH1D* H_IM = new TH1D("H_IM","H_IM",200,0,200);
	TH1D* H_IM_csvl = new TH1D("H_IM_csvl","H_IM_csvl",200,0,200);
	TH1D* H_IM_csvm = new TH1D("H_IM_csvm","H_IM_csvm",200,0,200);

	TH1D* Zee_IM = new TH1D("Zee_IM","Zee_IM",200,0,200);

	// root file
  	TChain *root = new TChain("tree/tree");
  	root->Add("../flattuple.root");// Zprime sample
  	//root->Add("../TTbar_sample/flattuple_1.root");// TTbar sample from yu	
  	TreeReader data(root);
  	Long64_t N_of_ev = data.GetEntriesFast();

  	cout<< "N_of_ev : "<< N_of_ev << endl;

	//get liklihood
	vector<Int_t> Nt(7,0) ; // # of event that have t b-tagging
	vector<Int_t> nk(10,0) ; // # of event that have k jet
	vector<event_for_likelihood> events_for_likelihood;	

	// rec level
	int total_kk=0;
	int total_k=0;
	int total_btag_pass_cut=0;
	int total_nbtag_pass_cut=0;
	int total_event_have_0_bq=0;
	int total_event_have_1_bq=0;
	int total_event_have_2_bq=0;
	int total_event_have_3_bq=0;
	int total_event_have_4_bq=0;
	
	// gen level
	int gen_j=0;
	int gen_b=0;
	int gen_nb=0;
	int gen_j_pass_cut=0;
	int gen_b_pass_cut=0;
	int gen_nb_pass_cut=0;
	int gen_j_pass_cut_btagging=0;
	int gen_b_pass_cut_btagging=0;
	int gen_nb_pass_cut_btagging=0;

	int gen_b_no_matching=0;

	int matched_gen_Jet=0;

	int total_gen_jet=0;

	int CA8_around_1_b=0;
	int CA8_around_2_b=0;
	int CA8_around_1_nb=0;
	int CA8_around_many_nb=0;
	int CA8_around_ele_noj=0;
	int CA8_around_mu_noj=0;

	int n_of_ev_with_0_CA8_around_b=0;
	int n_of_ev_with_1_CA8_around_b=0;
	int n_of_ev_with_2_CA8_around_b=0;
	int n_of_ev_with_3_CA8_around_b=0;
	

	// event loop : counting b-tagging
  	for (Long64_t Nth = 0; Nth < N_of_ev; Nth++)
    	{
		cout<<endl<<"=====================event:"<<Nth<<"==============================="<<endl;
 		
  		data.GetEntry(Nth);
		//test
		int nbq=0;

		// gen_par var
		Int_t nGenPar=data.GetInt("nGenPar");
      		Float_t *genParPt=data.GetPtrFloat("genParPt");  
      		Float_t *genParEta=data.GetPtrFloat("genParEta"); 
      		Float_t *genParPhi=data.GetPtrFloat("genParPhi"); 
     		Float_t *genParE=data.GetPtrFloat("genParE");
     		Float_t *genParM=data.GetPtrFloat("genParM");	
		Int_t *genParId=data.GetPtrInt("genParId");	
		Int_t *genParIndex=data.GetPtrInt("genParIndex");
		Int_t *genMomParId=data.GetPtrInt("genMomParId");
		Int_t *genMo1=data.GetPtrInt("genMo1");  //not mom id?
		Int_t *genMo2=data.GetPtrInt("genMo2");  //not mom id?
		Int_t *genParSt=data.GetPtrInt("genParSt");

		// gen_j var
		Int_t nGenJet=data.GetInt("nGenJet");
      		Float_t *genJetPt=data.GetPtrFloat("genJetPt");  
      		Float_t *genJetEta=data.GetPtrFloat("genJetEta"); 
      		Float_t *genJetPhi=data.GetPtrFloat("genJetPhi"); 
     		Float_t *genJetE=data.GetPtrFloat("genJetE");

      		// CA8jet var
      		Int_t CA8nJet=data.GetInt("CA8nJet");
      		Float_t *CA8jetPt=data.GetPtrFloat("CA8jetPt");  
      		Float_t *CA8jetEta=data.GetPtrFloat("CA8jetEta"); 
      		Float_t *CA8jetPhi=data.GetPtrFloat("CA8jetPhi"); 
     		Float_t *CA8jetEn=data.GetPtrFloat("CA8jetEn");
     		Float_t *CA8jetMass=data.GetPtrFloat("CA8jetMass");
      		Float_t *CA8jetCSV=data.GetPtrFloat("CA8jetCSV");

  		Float_t *CA8jetNHadEF=data.GetPtrFloat("CA8jetNHadEF");
  		Float_t *CA8jetNEmEF=data.GetPtrFloat("CA8jetNEmEF");
  		Float_t *CA8jetCHadEF=data.GetPtrFloat("CA8jetCHadEF");
  		Float_t *CA8jetCEmEF=data.GetPtrFloat("CA8jetCEmEF");
  		Float_t *CA8jetCMulti=data.GetPtrFloat("CA8jetCMulti");

      		// AK5jet var
      		Int_t AK5nJet=data.GetInt("AK5nJet");
      		Float_t *AK5jetPt=data.GetPtrFloat("AK5jetPt");  
      		Float_t *AK5jetEta=data.GetPtrFloat("AK5jetEta"); 
      		Float_t *AK5jetPhi=data.GetPtrFloat("AK5jetPhi"); 
     		Float_t *AK5jetEn=data.GetPtrFloat("AK5jetEn");
     		Float_t *AK5jetMass=data.GetPtrFloat("AK5jetMass");
      		Float_t *AK5jetCSV=data.GetPtrFloat("AK5jetCSV");

  		Float_t *AK5jetNHadEF=data.GetPtrFloat("AK5jetNHadEF");
  		Float_t *AK5jetNEmEF=data.GetPtrFloat("AK5jetNEmEF");
  		Float_t *AK5jetCHadEF=data.GetPtrFloat("AK5jetCHadEF");
  		Float_t *AK5jetCEmEF=data.GetPtrFloat("AK5jetCEmEF");
  		Float_t *AK5jetCMulti=data.GetPtrFloat("AK5jetCMulti");

		// var

		Int_t N_btagging=0;
		Int_t N_jet_pass_cut=0;


		//CA8 match with genPar
		vector<CA8dr8> CA8dr8s_this_ev;
		float R=0.8;
		int n_of_CA8_around_b=0;

      		for (int i=0;i<CA8nJet;i++)
        	{	
			//cout<<endl<<"----rec jet:"<<i<<"----"<<endl;
			CA8jet this_j(CA8jetPt[i],CA8jetEta[i],CA8jetPhi[i],CA8jetEn[i],CA8jetMass[i],CA8jetCSV[i],
				CA8jetNHadEF[i],CA8jetNEmEF[i],CA8jetCHadEF[i],CA8jetCEmEF[i],CA8jetCMulti[i]);		
			
			CA8dr8 this_CA8dr8;
			
			
			for(int j=0;j<nGenPar;j++)
			{
				gen_par this_g = gen_par(genParPt[j], genParEta[j], genParPhi[j], genParE[j], genParM[j],
					genParId[j], genParIndex[j], genMomParId[j], genMo1[j], genMo2[j], genParSt[j]);
				if (delta_R(this_j,this_g)<=R)
				{
					int this_g_id=abs(this_g.id);
					if(this_g_id==5){this_CA8dr8.gen_b++;}
					if(this_g_id<=4 && this_g_id>=0){this_CA8dr8.gen_nb++;}
					if(this_g_id==11){this_CA8dr8.gen_ele++;}
					if(this_g_id==13){this_CA8dr8.gen_mu++;}				
				}	
			}
			if (this_CA8dr8.gen_b>0){ n_of_CA8_around_b++;}
			CA8dr8s_this_ev.push_back(this_CA8dr8);
		}
		if( n_of_CA8_around_b==0){n_of_ev_with_0_CA8_around_b++;}
		if( n_of_CA8_around_b==1){n_of_ev_with_1_CA8_around_b++;}
		if( n_of_CA8_around_b==2){n_of_ev_with_2_CA8_around_b++;}
		if( n_of_CA8_around_b==3){n_of_ev_with_3_CA8_around_b++;}
		
		
		for (int i=0;i<CA8dr8s_this_ev.size();i++)
		{
			cout<<endl<<"----rec jet:"<<i<<"----"<<endl;
			CA8dr8 this_CA8dr8=CA8dr8s_this_ev[i];
			cout<<"around this CA8 R="<<R<<":"<<
			"gen_b="<<this_CA8dr8.gen_b<<
			",gen_nb="<<this_CA8dr8.gen_nb<<
			",ele="<<this_CA8dr8.gen_ele<<
			",mu"<<this_CA8dr8.gen_mu<<endl;

			if (this_CA8dr8.gen_b==1){CA8_around_1_b++; }
			if (this_CA8dr8.gen_b==2){CA8_around_2_b++; }
			if (this_CA8dr8.gen_nb==1){CA8_around_1_nb++;}
			if (this_CA8dr8.gen_b>1){CA8_around_many_nb++;}
			if (this_CA8dr8.gen_ele>0 && this_CA8dr8.gen_b==0 && this_CA8dr8.gen_nb==0){CA8_around_ele_noj++;}
			if (this_CA8dr8.gen_mu>0 && this_CA8dr8.gen_b==0 && this_CA8dr8.gen_nb==0 ){CA8_around_mu_noj++;}
			
			
		}



	} //event loop end here

	cout<<"==========================================reprot========================================="<<endl;
	cout<<"CA8_around_1_b:"<<CA8_around_1_b<<endl;
	cout<<"CA8_around_2_b:"<<CA8_around_2_b<<endl;
	cout<<"CA8_around_1_nb:"<<CA8_around_1_nb<<endl;
	cout<<"CA8_around_many_nb:"<<CA8_around_many_nb<<endl;
	cout<<"CA8_around_ele_noj:"<<CA8_around_ele_noj<<endl;
	cout<<"CA8_around_mu_noj:"<<CA8_around_mu_noj<<endl;
	cout<<"n_of_ev_with_0_CA8_around_b:"<<n_of_ev_with_0_CA8_around_b<<endl;
	cout<<"n_of_ev_with_1_CA8_around_b:"<<n_of_ev_with_1_CA8_around_b<<endl;
	cout<<"n_of_ev_with_2_CA8_around_b:"<<n_of_ev_with_2_CA8_around_b<<endl;
	cout<<"n_of_ev_with_3_CA8_around_b:"<<n_of_ev_with_3_CA8_around_b<<endl;


 	    
}
