#include "TROOT.h"
#include "TObject.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TLorentzVector.h"
#include "TF1.h"
#include "TLine.h"
#include "TString.h"
#include "TStyle.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>

using namespace std;

void plot() {
  char str[200];
  
  Int_t           idEvent;
  Int_t           nfsp;
  Int_t           PDGnu;
  Int_t           PDGlepton;
  Int_t           cc;
  Float_t         Enu_true;
  Float_t         Plepton;
  Int_t           id[500];   //[nfsp]
  Int_t           pdg[500];   //[nfsp]
  Float_t         px[500];   //[nfsp]
  Float_t         py[500];   //[nfsp]
  Float_t         pz[500];   //[nfsp]
  Float_t         E[500];   //[nfsp]

  // List of branches
  TBranch        *b_idEvent;   //!
  TBranch        *b_nfsp;   //!
  TBranch        *b_PDGnu;   //!
  TBranch        *b_PDGlepton;   //!
  TBranch        *b_cc;   //!
  TBranch        *b_Enu_true;   //!
  TBranch        *b_Plepton;   //!
  TBranch        *b_id;   //!
  TBranch        *b_pdg;   //!
  TBranch        *b_px;   //!
  TBranch        *b_py;   //!
  TBranch        *b_pz;   //!
  TBranch        *b_E;   //!

  TChain* fChain = new TChain("tree");
  //fChain->Add("numu_faser_1M.dump.root");
  fChain->Add("anumu_faser_1M.dump.root");
  
  fChain->SetBranchAddress("idEvent", &idEvent, &b_idEvent);
  fChain->SetBranchAddress("nfsp", &nfsp, &b_nfsp);
  fChain->SetBranchAddress("PDGnu", &PDGnu, &b_PDGnu);
  fChain->SetBranchAddress("PDGlepton", &PDGlepton, &b_PDGlepton);
  fChain->SetBranchAddress("cc", &cc, &b_cc);
  fChain->SetBranchAddress("Enu_true", &Enu_true, &b_Enu_true);
  fChain->SetBranchAddress("Plepton", &Plepton, &b_Plepton);
  fChain->SetBranchAddress("id", id, &b_id);
  fChain->SetBranchAddress("pdg", pdg, &b_pdg);
  fChain->SetBranchAddress("px", px, &b_px);
  fChain->SetBranchAddress("py", py, &b_py);
  fChain->SetBranchAddress("pz", pz, &b_pz);
  fChain->SetBranchAddress("E", E, &b_E);

  //ofstream outfile("numu_faser_1M.dump._001.txt");
  ofstream outfile("anumu_faser_1M.dump._001.txt");
  Int_t nevt = 1;
  
  //Int_t nentries = (Int_t)fChain->GetEntries();
  Int_t nentries = 1000;
  for(Int_t entry=nentries*0; entry<nentries*1; entry++) {
    fChain->GetEntry(entry);

    outfile << "event " << nevt << endl;
    outfile << "info: " << PDGnu << " " << PDGlepton << " " << Enu_true << " " << Plepton << " " << cc << endl;
    for(Int_t i=0; i<nfsp; i++) {
      if(abs(pdg[i])!=14 && abs(pdg[i])!=1000741840 && abs(pdg[i])!=2000000002 && abs(pdg[i])!=2000000101) {
	outfile << pdg[i] << " " << E[i] << " " << px[i] << " " << py[i] << " " << pz[i] << endl;
      }
    }
    nevt++;
  }
}
