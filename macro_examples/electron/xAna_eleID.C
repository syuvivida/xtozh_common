// example code to run Bulk Graviton->ZZ->ZlepZhad selections on electron-channel

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <TString.h>
#include <string>
#include <map>
#include <TH1D.h>
#include <TFile.h>
#include "untuplizer.h"
#include <TClonesArray.h>
#include <TLorentzVector.h>
#include <TEfficiency.h>
#include <TSystemDirectory.h>
#include <TList.h>
#include <TPad.h>
#include <TGraphAsymmErrors.h>

#define DEBUG 0
using namespace std;
void xAna_eleID(std::string inputFile, int mode){

  //get TTree from file ...

  TString outputFile;
  std::vector<string> infiles;
  // string idname[4]={"HEEPMiniIso","LooseMiniIso","LeadHEEPSubHEEPLooseMiniIso","HEEPMiniIsoOrLooseMiniIso"};
  string idname[4]={"HEEPNoIso","LooseNoIso","LeadHEEPSubHEEPLoose","HEEPNoIsoOrLooseNoIso"};

  if(inputFile.find(".root")!= std::string::npos)
    { 
      outputFile=gSystem->GetFromPipe(Form("file=%s; test=${file##*ZprimeToZhToZlephbb/}; echo \"eff_%s_${test}\"",inputFile.data(),idname[mode].data()));
      cout << "output file name = " << outputFile.Data() << endl;
      infiles.push_back(inputFile.data());
    }
  else
    {
      outputFile=gSystem->GetFromPipe(Form("file=%s; test=${file##*signalMC/}; echo \"eff_%s_${test}.root\"",inputFile.data(),idname[mode].data()));
      cout << "output file name = " << outputFile.Data() << endl;      
      TSystemDirectory *base = new TSystemDirectory("root","root");

      base->SetDirectory(inputFile.data());
      TList *listOfFiles = base->GetListOfFiles();
      TIter fileIt(listOfFiles);
      TFile *fileH = new TFile();
      int nfile=0;
      while(fileH = (TFile*)fileIt()) {
	std::string fileN = fileH->GetName();
	if( fileH->IsFolder())  continue;
	if(fileN.find("Zprime") == std::string::npos)continue;
	fileN = inputFile + "/" + fileN;
	cout << fileN.data() << endl;
	nfile++;
	infiles.push_back(fileN);
      }

      std::cout << "Opened " << nfile << " files" << std::endl;

    }
  
  TreeReader data(infiles);
  
  Long64_t nTotal=0;
  Long64_t nPass[20]={0};
  TH1F* h_pt = new TH1F("h_pt","",50,0,1000);
  h_pt->SetXTitle("generator-level #p_{T}");
  TH1F* h_dR = new TH1F("h_dR","",20,0,1);
  h_dR->SetXTitle("generator-level #Delta R(e,e)");
  TH1F* h_ptr = new TH1F("h_ptr","",50,-1,1);
  h_ptr->SetXTitle("ptratio");
  TH1F* h_gendR_nocut = (TH1F*)h_dR->Clone("h_gendR_nocut"); 
  TH1F* h_gendR[4];
  TH1F* h_recodR[4];
  TH1F* h_genpt[4];
  TH1F* h_recopt[4];
  string name[4]={"matched reconstructed Z","matched reconstructed Z passing " + idname[mode] + " cuts",
		  "matched reconstructed electron",
		  "matched reconstructed electron passing " + idname[mode] + " cuts"};
  string endfix[4]={"p_{T}(Z) [GeV]","p_{T}(Z) [GeV]","p_{T}(e) [GeV]","p_{T}(e) [GeV]"};

  for(int i=0; i<4; i++)
    {
      h_gendR[i] = (TH1F*)h_dR->Clone(Form("h_gendR%d",i));
      h_gendR[i]->SetTitle(name[i].data());

      h_genpt[i] = (TH1F*)h_pt->Clone(Form("h_genpt%d",i));
      h_genpt[i]->SetTitle(name[i].data());
      h_genpt[i]->SetXTitle(Form("generator-level %s",endfix[i].data()));

      h_recodR[i] = (TH1F*)h_dR->Clone(Form("h_recoR%d",i));
      h_recodR[i]->SetTitle(name[i].data());
      h_recodR[i]->SetXTitle("reconstruction-level #Delta R(e,e)");

      h_recopt[i] = (TH1F*)h_pt->Clone(Form("h_recopt%d",i));
      h_recopt[i]->SetTitle(name[i].data());
      h_recopt[i]->SetXTitle(Form("reconstruction-level %s",endfix[i].data()));

    }

  h_dR->SetXTitle("#Delta R(gen-e,reco-e)");

  //Event loop
  for(Long64_t jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    if (jEntry % 50000 == 0)
      fprintf(stderr, "Processing event %lli of %lli\n", jEntry + 1, data.GetEntriesFast());

    data.GetEntry(jEntry);
    nTotal ++;

    // 0. check the generator-level information and make sure there is a Z->e+e-
    Int_t nGenPar        = data.GetInt("nGenPar");
    Int_t* genParId      = data.GetPtrInt("genParId");
    Int_t* genParSt      = data.GetPtrInt("genParSt");
    Int_t* genMomParId   = data.GetPtrInt("genMomParId");


    int geneIndex[2]={-1,-1};
    nPass[0]++;

    for(int ig=0; ig < nGenPar; ig++){

      if(genParSt[ig]!=1)continue;

      if(abs(genParId[ig])!=11)continue;

      if(genMomParId[ig]!=23 &&
	 genMomParId[ig]!=genParId[ig])continue;

      if(geneIndex[0]<0 && genParId[ig]==11)
	geneIndex[0]=ig;
      if(geneIndex[1]<0 && genParId[ig]== -11)
	geneIndex[1]=ig;
      
      if(geneIndex[0]>=0 &&
	 geneIndex[1]>=0)
	break;
	
    }
    if(geneIndex[0]<0 || geneIndex[1]<0)continue;
    nPass[1]++;

    TClonesArray* genParP4 = (TClonesArray*) data.GetPtrTObject("genParP4");
    TLorentzVector gene_l4[2];
    TLorentzVector genZ_l4;

    for(int i=0; i<2; i++)
      {
	gene_l4[i] = *((TLorentzVector*)genParP4->At(geneIndex[i]));
	genZ_l4 += gene_l4[i];
      }

    float gendR = gene_l4[0].DeltaR(gene_l4[1]);
    h_gendR_nocut->Fill(gendR);
    

    //2. has a good vertex
    Int_t nVtx        = data.GetInt("nVtx");
    if(nVtx<1)continue;
    nPass[2]++;


    //3. select good electrons based on kinematic selections only
    std::vector<int> goodElectrons;
    Int_t nEle         = data.GetInt("nEle");
    Float_t* eleSCEta         = data.GetPtrFloat("eleScEta");
    Float_t* eleSCEt          = data.GetPtrFloat("eleScEt");

    for(int ie=0; ie< nEle; ie++)
      {

    	if(fabs(eleSCEta[ie])>2.5)continue;

    	if(fabs(eleSCEta[ie])>1.4442 && fabs(eleSCEta[ie])<1.566)continue;
    	
	if(eleSCEt[ie]<35)continue; // for HEEP ID 

    	goodElectrons.push_back(ie);
      }

    if(goodElectrons.size()<2)continue;
    nPass[3]++;

    

    //4. select a good Z boson matched to gen-level
    TClonesArray* eleP4 = (TClonesArray*) data.GetPtrTObject("eleP4");
    Int_t*   eleCharge        = data.GetPtrInt("eleCharge");         
    int zIndex[2]={-1,-1};
    const float DRMAX=0.1;
    const float RPTMAX=0.3;

    for(unsigned int i=0; i< goodElectrons.size(); i++)
      {
	int ie = goodElectrons[i];
	TLorentzVector* thisEle = (TLorentzVector*)eleP4->At(ie);

	float dR1_gen0= thisEle->DeltaR(gene_l4[0]);
	float dR1_gen1= thisEle->DeltaR(gene_l4[1]);
	if(dR1_gen0 > DRMAX && dR1_gen1 > DRMAX)continue;
	
	float ptr1_gen0= (thisEle->Pt()-gene_l4[0].Pt())/gene_l4[0].Pt();
	float ptr1_gen1= (thisEle->Pt()-gene_l4[1].Pt())/gene_l4[1].Pt();

	h_ptr->Fill(ptr1_gen0);
	h_ptr->Fill(ptr1_gen1);

	if(fabs(ptr1_gen0)>RPTMAX && fabs(ptr1_gen1)>RPTMAX )continue;

	for(unsigned int j=0; j< i; j++)
	  {
	    int je= goodElectrons[j];

	    if(eleCharge[ie]*eleCharge[je]>0)continue;

	    TLorentzVector* thatEle = (TLorentzVector*)eleP4->At(je);

	    float dR2_gen0= thatEle->DeltaR(gene_l4[0]);
	    float dR2_gen1= thatEle->DeltaR(gene_l4[1]);
	    
	    if(dR2_gen0 > DRMAX && dR2_gen1 > DRMAX)continue;

	    float ptr2_gen0= (thatEle->Pt()-gene_l4[0].Pt())/gene_l4[0].Pt();
	    float ptr2_gen1= (thatEle->Pt()-gene_l4[1].Pt())/gene_l4[1].Pt();

	    h_ptr->Fill(ptr2_gen0);
	    h_ptr->Fill(ptr2_gen1);

	    if(fabs(ptr2_gen0)>RPTMAX && fabs(ptr2_gen1)>RPTMAX )continue;

	    Float_t mll  = (*thisEle+*thatEle).M();
	    float pt1=thisEle->Pt();
	    float pt2=thatEle->Pt();
	    float ptmax = TMath::Max(pt1,pt2);
	    float ptmin = TMath::Min(pt1,pt2);

	    if(mll<70 || mll>110)continue;

	    if(ptmax<115)continue;


	    bool matched = 
	      (dR1_gen0 < DRMAX && fabs(ptr1_gen0)< RPTMAX && 
	       dR2_gen1 < DRMAX && fabs(ptr2_gen1)< RPTMAX ) ||
	      (dR1_gen1 < DRMAX && fabs(ptr1_gen1)< RPTMAX && 
	       dR2_gen0 < DRMAX && fabs(ptr2_gen0)< RPTMAX);
	    
	    if(!matched){
	      if(DEBUG){
		cout << "Why? " << dR1_gen0 << "\t" << dR1_gen1 << "\t" <<
		  dR2_gen0 << "\t" << dR2_gen1 << "\t" <<
		  ptr1_gen0 << "\t" << ptr1_gen1 << "\t" <<
		  ptr2_gen0 << "\t" << ptr2_gen1 << endl;
		gene_l4[0].Print();
		gene_l4[1].Print();
		thisEle->Print();
		thatEle->Print();
	      }	      
	      continue;
	    }

	    
	    // check if these electrons are matched to gen-level electrons
 


	    if(pt1>pt2){
	      zIndex[0]=ie;
	      zIndex[1]=je;
	    }
	    else
	      {
		zIndex[0]=je;
		zIndex[1]=ie;
	      }

	    break;

	    
	  }	
      }

    if(zIndex[0]<0 || zIndex[1]<0)continue;
    nPass[4]++;

    if(DEBUG && gendR<0.1)
      for(int i=0;i<2;i++)
	gene_l4[i].Print();

    TLorentzVector rece_l4[2];
    TLorentzVector recoZ_l4;
    for(int i=0; i<2; i++)
      {
	rece_l4[i] = *((TLorentzVector*)eleP4->At(zIndex[i]));
	if(DEBUG && gendR<0.1)rece_l4[i].Print();
	recoZ_l4 += rece_l4[i];
      }


    float recdR = rece_l4[0].DeltaR(rece_l4[1]);


    h_gendR[0]->Fill(gendR);
    h_recodR[0]->Fill(recdR);

    h_genpt[0]->Fill(genZ_l4.Pt());
    h_recopt[0]->Fill(recoZ_l4.Pt());

    h_genpt[2]->Fill(gene_l4[0].Pt());
    h_recopt[2]->Fill(rece_l4[0].Pt());
    h_genpt[2]->Fill(gene_l4[1].Pt());
    h_recopt[2]->Fill(rece_l4[1].Pt());

    h_gendR[2]->Fill(gendR);
    h_gendR[2]->Fill(gendR);
    h_recodR[2]->Fill(recdR);
    h_recodR[2]->Fill(recdR);

    bool passEle[2]={false,false};
    vector<bool> &passHEEPID = *((vector<bool>*) data.GetPtr("eleIsPassHEEPNoIso"));
    vector<bool> &passLoose = *((vector<bool>*) data.GetPtr("eleIsPassLooseNoIso"));

    for(int i=0;i<2;i++)
      {
	switch (mode){
	case 0:
	  passEle[i] = passHEEPID[zIndex[i]];
	  break;
	case 1:
	  passEle[i] = passLoose[zIndex[i]];
	  break;
	case 2:
	  passEle[0] = passHEEPID[zIndex[0]];
	  passEle[1] = passHEEPID[zIndex[1]] || passLoose[zIndex[1]];
	  break;
	case 3:
	  passEle[i] = passHEEPID[zIndex[i]] || passLoose[zIndex[i]];
	  break;
	default:
	  passEle[i] = passHEEPID[zIndex[i]];
	  break;
	}
      }

    // Float_t* eleMiniIso       = data.GetPtrFloat("eleMiniIso");
    // for(int i=0;i<2;i++)
    //   passEle[i] = passEle[i] && (eleMiniIso[zIndex[i]]<0.1);

    if(passEle[0])
      {
	h_gendR[3]->Fill(gendR);
	h_recodR[3]->Fill(recdR);
	h_genpt[3]->Fill(gene_l4[0].Pt());
	h_recopt[3]->Fill(rece_l4[0].Pt());

      }
    if(passEle[1])
      {
	h_gendR[3]->Fill(gendR);
	h_recodR[3]->Fill(recdR);
	h_genpt[3]->Fill(gene_l4[1].Pt());
	h_recopt[3]->Fill(rece_l4[1].Pt());

      }

    
    if(!passEle[0] || !passEle[1])continue;
   
    nPass[5]++;
 
    h_gendR[1]->Fill(gendR);
    h_recodR[1]->Fill(recdR);
    
    h_genpt[1]->Fill(genZ_l4.Pt());
    h_recopt[1]->Fill(recoZ_l4.Pt());

    


  } // end of loop over entries

  std::cout << "nTotal    = " << nTotal << std::endl;
  for(int i=0;i<20;i++)
    if(nPass[i]>0)
      std::cout << "nPass[" << i << "]= " << nPass[i] << std::endl;
  

  // deltaR efficiency

  TEfficiency* gEff = new TEfficiency(*h_gendR[1],*h_gendR[0]);
  gEff->SetName("gEff");
  gEff->SetTitle("Z-ID efficiency; generator-level #Delta R(e,e); total ID efficiency per Z candidate");
  
  gEff->Draw();
  gPad->Update();
  TGraphAsymmErrors* graph_gEff=gEff->GetPaintedGraph();
  graph_gEff->SetName("graph_gEff");
  graph_gEff->GetXaxis()->SetTitle("generator-level #Delta R(e,e)");
  graph_gEff->GetYaxis()->SetTitle("Total ID efficiency per Z candidate");

  TEfficiency* recoEff = new TEfficiency(*h_recodR[1],*h_recodR[0]);
  recoEff->SetName("recoEff");
  recoEff->SetTitle("Z-ID efficiency; reconstruction-level #Delta R(e,e); total ID efficiency per Z candidate");

  recoEff->Draw();
  gPad->Update();

  TGraphAsymmErrors* graph_recoEff=recoEff->GetPaintedGraph();
  graph_recoEff->SetName("graph_recoEff");
  graph_recoEff->GetXaxis()->SetTitle("reconstruction-level #Delta R(e,e)");
  graph_recoEff->GetYaxis()->SetTitle("Total ID efficiency per Z candidate");

  TEfficiency* gEff2 = new TEfficiency(*h_gendR[3],*h_gendR[2]);
  gEff2->SetName("gEff2");
  gEff2->SetTitle("electron-ID efficiency; generator-level #Delta R(e,e); ID efficiency per electron");

  gEff2->Draw();
  gPad->Update();

  TGraphAsymmErrors* graph_gEff2=gEff2->GetPaintedGraph();
  graph_gEff2->SetName("graph_gEff2");
  graph_gEff2->GetXaxis()->SetTitle("generator-level #Delta R(e,e)");
  graph_gEff2->GetYaxis()->SetTitle("ID efficiency per electron");

  TEfficiency* recoEff2 = new TEfficiency(*h_recodR[3],*h_recodR[2]);
  recoEff2->SetName("recoEff2");
  recoEff2->SetTitle("electron-ID efficiency; reconstruction-level #Delta R(e,e); ID efficiency per electron");

  recoEff2->Draw();
  gPad->Update();

  TGraphAsymmErrors* graph_recoEff2=recoEff2->GetPaintedGraph();
  graph_recoEff2->SetName("graph_recoEff2");
  graph_recoEff2->GetXaxis()->SetTitle("reconstruction-level #Delta R(e,e)");
  graph_recoEff2->GetYaxis()->SetTitle("ID efficiency per electron");


  // pt efficiency
  TEfficiency* ptgEff = new TEfficiency(*h_genpt[1],*h_genpt[0]);
  ptgEff->SetName("ptgEff");
  ptgEff->SetTitle("Z-ID efficiency; generator-level p_{T}(Z) [GeV]; total ID efficiency per Z candidate");
  
  ptgEff->Draw();
  gPad->Update();

  TGraphAsymmErrors* ptgraph_gEff=ptgEff->GetPaintedGraph();
  ptgraph_gEff->SetName("ptgraph_gEff");
  ptgraph_gEff->GetXaxis()->SetTitle("generator-level p_{T}(Z) [GeV]");
  ptgraph_gEff->GetYaxis()->SetTitle("Total ID efficiency per Z candidate");

  TEfficiency* ptrecoEff = new TEfficiency(*h_recopt[1],*h_recopt[0]);
  ptrecoEff->SetName("ptrecoEff");
  ptrecoEff->SetTitle("Z-ID efficiency; reconstruction-level p_{T}(Z) [GeV]; total ID efficiency per Z candidate");

  ptrecoEff->Draw();
  gPad->Update();

  TGraphAsymmErrors* ptgraph_recoEff=ptrecoEff->GetPaintedGraph();
  ptgraph_recoEff->SetName("ptgraph_recoEff");
  ptgraph_recoEff->GetXaxis()->SetTitle("reconstruction-level p_{T}(Z) [GeV]");
  ptgraph_recoEff->GetYaxis()->SetTitle("Total ID efficiency per Z candidate");

  TEfficiency* ptgEff2 = new TEfficiency(*h_genpt[3],*h_genpt[2]);
  ptgEff2->SetName("ptgEff2");
  ptgEff2->SetTitle("electron-ID efficiency; generator-level p_{T}(e) [GeV]; ID efficiency per electron");

  ptgEff2->Draw();
  gPad->Update();

  TGraphAsymmErrors* ptgraph_gEff2=ptgEff2->GetPaintedGraph();
  ptgraph_gEff2->SetName("ptgraph_gEff2");
  ptgraph_gEff2->GetXaxis()->SetTitle("generator-level p_{T}(e) [GeV]");
  ptgraph_gEff2->GetYaxis()->SetTitle("ID efficiency per electron");

  TEfficiency* ptrecoEff2 = new TEfficiency(*h_recopt[3],*h_recopt[2]);
  ptrecoEff2->SetName("ptrecoEff2");
  ptrecoEff2->SetTitle("electron-ID efficiency; reconstruction-level p_{T}(e) [GeV]; ID efficiency per electron");

  ptrecoEff2->Draw();
  gPad->Update();

  TGraphAsymmErrors* ptgraph_recoEff2=ptrecoEff2->GetPaintedGraph();
  ptgraph_recoEff2->SetName("ptgraph_recoEff2");
  ptgraph_recoEff2->GetXaxis()->SetTitle("reconstruction-level p_{T}(e) [GeV]");
  ptgraph_recoEff2->GetYaxis()->SetTitle("ID efficiency per electron");


  TFile* outFile = new TFile(outputFile.Data(),"recreate");
  h_dR->Write();
  h_ptr->Write();
  h_gendR_nocut->Write();
  for(int i=0;i<4;i++)
    {
      h_gendR[i]->Write();
      h_recodR[i]->Write();
      h_genpt[i]->Write();
      h_recopt[i]->Write();
    }
  gEff->Write();
  recoEff->Write();
  gEff2->Write();
  recoEff2->Write();

  graph_gEff->Write();
  graph_recoEff->Write();
  graph_gEff2->Write();
  graph_recoEff2->Write();

  ptgEff->Write();
  ptrecoEff->Write();
  ptgEff2->Write();
  ptrecoEff2->Write();

  ptgraph_gEff->Write();
  ptgraph_recoEff->Write();
  ptgraph_gEff2->Write();
  ptgraph_recoEff2->Write();

  outFile->Close();
    
}
