//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Dec 24 14:44:50 2019 by ROOT version 5.34/26
// from TTree tree/GENIE
// found on file: numu_faser_1M.dump.root
//////////////////////////////////////////////////////////

#ifndef Event_h
#define Event_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class Event {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
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

   Event(TTree *tree=0);
   virtual ~Event();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Event_cxx
Event::Event(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("numu_faser_1M.dump.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("numu_faser_1M.dump.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

Event::~Event()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Event::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Event::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Event::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

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
   Notify();
}

Bool_t Event::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Event::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Event::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Event_cxx
