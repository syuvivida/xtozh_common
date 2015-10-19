#include <TROOT.h>
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TKey.h"
#include <string>
#include <iostream>
#include <fstream>
#include <TSystem.h>
#include <TSystemDirectory.h>
#include <TList.h>
using namespace std;

void countHistoEntries(string dirname, string rootname="NCU", string id="data7")
{
  string inputTextFile = "inputdir.txt";
  // clean-up files
  gSystem->Exec(Form("rm -rf %s",inputTextFile.data()));
  // output new text file
  gSystem->Exec(Form("ls -R %s | grep -a \"%s\" >> %s",
		     dirname.data(),id.data(), inputTextFile.data()));
  TSystemDirectory *base = new TSystemDirectory("root","root"); 
  Long64_t jEntry=0;
  int nfile=0;
  string tempdir;
  ifstream fin;
  fin.open(inputTextFile.data());
  fin >> tempdir;
  TString realDirName = gSystem->GetFromPipe(Form("a=%s; echo ${a%%:*}",tempdir.data()));
  while(!fin.eof()){
    cout << "Directory name = " << realDirName << endl;
    base->SetDirectory(realDirName.Data());
    TList *listOfFiles = base->GetListOfFiles();
    TIter fileIt(listOfFiles);
    TFile *fileH = new TFile();
    while((fileH = (TFile*)fileIt())) {
      std::string fileN = fileH->GetName();
      std::string baseString = rootname.data();
      if( fileH->IsFolder())  continue;
      if(fileN.find(baseString) == std::string::npos)continue;
      cout << fileN.data() << endl;
      nfile++;
      TFile *inf = TFile::Open(Form("%s/%s",realDirName.Data(),fileN.data()));
      TH1F *h = (TH1F*)inf->FindObjectAny("totalEvents");
      jEntry += h->GetEntries();
      inf->Close();
    }
    fin >> tempdir;
    realDirName = gSystem->GetFromPipe(Form("a=%s; echo ${a%%:*}",tempdir.data()));
  } // end of big loop

  std::cout << "Opened " << nfile << " files" << std::endl;
  
  cout << "Total number of entries = " << jEntry << endl;


}

