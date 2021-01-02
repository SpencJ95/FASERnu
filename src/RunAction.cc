//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file RunAction.cc
/// \brief Implementation of the RunAction class

#include "RunAction.hh"
#include "Analysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal double e_beam;
G4ThreadLocal int id_beam;
G4ThreadLocal double x_beam;
G4ThreadLocal double y_beam;
G4ThreadLocal int pdgnu_nuEvt;
G4ThreadLocal int pdglep_nuEvt;
G4ThreadLocal double Enu_nuEvt;
G4ThreadLocal double Plep_nuEvt;
G4ThreadLocal int cc_nuEvt;
G4ThreadLocal double x_nuEvt;
G4ThreadLocal double y_nuEvt;
G4ThreadLocal double z_nuEvt;
G4ThreadLocal std::vector<int> cham;
G4ThreadLocal std::vector<int> idz;
G4ThreadLocal std::vector<int> idzsub;
G4ThreadLocal std::vector<int> pdgid;
G4ThreadLocal std::vector<int> id;
G4ThreadLocal std::vector<int> idParent;
G4ThreadLocal std::vector<double> charge;
G4ThreadLocal std::vector<double> x;
G4ThreadLocal std::vector<double> y;
G4ThreadLocal std::vector<double> z;
G4ThreadLocal std::vector<double> px;
G4ThreadLocal std::vector<double> py;
G4ThreadLocal std::vector<double> pz;
G4ThreadLocal std::vector<double> e1;
G4ThreadLocal std::vector<double> e2;
G4ThreadLocal std::vector<double> len;
G4ThreadLocal std::vector<double> edep;

RunAction::RunAction()
 : G4UserRunAction()
{ 
  // set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);     

  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in Analysis.hh
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  // Create directories 
  //analysisManager->SetHistoDirectoryName("histograms");
  //analysisManager->SetNtupleDirectoryName("ntuple");
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);
    // Note: merging ntuples is available only with Root output

  // Book histograms, ntuple

  // Creating ntuple
  //
  analysisManager->CreateNtuple("FASERnu", "");
  analysisManager->CreateNtupleDColumn("e_beam");
  analysisManager->CreateNtupleIColumn("id_beam");
  analysisManager->CreateNtupleDColumn("x_beam");
  analysisManager->CreateNtupleDColumn("y_beam");
  analysisManager->CreateNtupleIColumn("pdgnu_nuEvt");
  analysisManager->CreateNtupleIColumn("pdglep_nuEvt");
  analysisManager->CreateNtupleDColumn("Enu_nuEvt");
  analysisManager->CreateNtupleDColumn("Plep_nuEvt");
  analysisManager->CreateNtupleIColumn("cc_nuEvt");
  analysisManager->CreateNtupleDColumn("x_nuEvt");
  analysisManager->CreateNtupleDColumn("y_nuEvt");
  analysisManager->CreateNtupleDColumn("z_nuEvt");
  analysisManager->CreateNtupleIColumn("chamber",cham);
  analysisManager->CreateNtupleIColumn("iz",idz);
  analysisManager->CreateNtupleIColumn("izsub",idzsub);
  analysisManager->CreateNtupleIColumn("pdgid",pdgid);
  analysisManager->CreateNtupleIColumn("id",id);
  analysisManager->CreateNtupleIColumn("idParent",idParent);
  analysisManager->CreateNtupleDColumn("charge",charge);
  analysisManager->CreateNtupleDColumn("x",x);
  analysisManager->CreateNtupleDColumn("y",y);
  analysisManager->CreateNtupleDColumn("z",z);
  analysisManager->CreateNtupleDColumn("px",px);
  analysisManager->CreateNtupleDColumn("py",py);
  analysisManager->CreateNtupleDColumn("pz",pz);
  analysisManager->CreateNtupleDColumn("e1",e1);
  analysisManager->CreateNtupleDColumn("e2",e2);
  analysisManager->CreateNtupleDColumn("len",len);
  analysisManager->CreateNtupleDColumn("edep",edep);
  analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
  delete G4AnalysisManager::Instance();  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{ 
  //inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);
  
  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  G4String fileName = "FASERnu1";
  analysisManager->OpenFile(fileName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  // print histogram statistics
  //
  auto analysisManager = G4AnalysisManager::Instance();

  // save histograms & ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
