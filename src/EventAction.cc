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
/// \file EventAction.cc
/// \brief Implementation of the EventAction class

#include "EventAction.hh"
#include "CalorimeterSD.hh"
#include "CalorHit.hh"


#include "Analysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
 : G4UserEventAction(),
   fCalorHCID(-1)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CalorHitsCollection* 
EventAction::GetCalorHitsCollection(G4int hcID, const G4Event* event) const
{
  auto hitsCollection =
    static_cast<CalorHitsCollection*>(event->GetHCofThisEvent()->GetHC(hcID));
  
  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID; 
    G4Exception("EventAction::GetCalorHitsCollection()",
      "MyCode0003", FatalException, msg);
  }
  return hitsCollection;
}






  









//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::PrintEventStatistics(G4double Edep) const
{
  // print event statistics
  G4cout
     << " Emulsion layer energy: " 
     << std::setw(7) << G4BestUnit(Edep, "Energy")
     << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{
  auto sdManager = G4SDManager::GetSDMpointer();

  // Get hit collections IDs (just once)
  fCalorHCID   = sdManager->GetCollectionID("EmulsionHitsCollection");


  cham.clear();
  idz.clear();
  idzsub.clear();
  pdgid.clear();
  id.clear();
  idParent.clear();
  charge.clear();
  x.clear();
  y.clear();
  z.clear();
  px.clear();
  py.clear();
  pz.clear();
  e1.clear();
  e2.clear();
  len.clear();
  edep.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{
  // Get hits collections
  auto calorHC = GetCalorHitsCollection(fCalorHCID, event);


  for (unsigned long i = 0; i < calorHC->GetSize(); ++i) {
    auto hit = static_cast<CalorHit*>(calorHC->GetHit(i));
    if(hit && hit->GetEnergyDepo()>1*keV) {
      cham.push_back(hit->GetChamber());
      idz.push_back(hit->GetIDZ());
std::cout << "Pushing back idz with value " << hit->GetIDZ() << std::endl;
      idzsub.push_back(hit->GetIDZsub());
      pdgid.push_back(hit->GetParticleID());
      id.push_back(hit->GetTrackID());
      idParent.push_back(hit->GetParentID());
      charge.push_back(hit->GetCharge());
      x.push_back(hit->GetPosition().x()/mm);
      y.push_back(hit->GetPosition().y()/mm);
      z.push_back(hit->GetPosition().z()/mm);
std::cout << "Pushing back z with value " << hit->GetPosition().z()/mm << std::endl;
      px.push_back(hit->GetMomentum().x()/MeV);
      py.push_back(hit->GetMomentum().y()/MeV);
      pz.push_back(hit->GetMomentum().z()/MeV);
      e1.push_back(hit->GetEnergyPreS()/MeV);
      e2.push_back(hit->GetEnergyPost()/MeV);
      len.push_back(hit->GetTrackLength()/mm);
      edep.push_back(hit->GetEnergyDepo()/MeV);
    }
  }



  // Fill histograms, ntuple

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  analysisManager->FillNtupleDColumn(0, e_beam*1000); // MeV
  analysisManager->FillNtupleIColumn(1, id_beam);
  analysisManager->FillNtupleDColumn(2, x_beam*10); // mm
  analysisManager->FillNtupleDColumn(3, y_beam*10); // mm

  analysisManager->FillNtupleIColumn(4, pdgnu_nuEvt);
  analysisManager->FillNtupleIColumn(5, pdglep_nuEvt);
  analysisManager->FillNtupleDColumn(6, Enu_nuEvt*1000); // MeV
  analysisManager->FillNtupleDColumn(7, Plep_nuEvt*1000); // MeV
  analysisManager->FillNtupleIColumn(8, cc_nuEvt);
  analysisManager->FillNtupleDColumn(9, x_nuEvt*10); // mm
  analysisManager->FillNtupleDColumn(10, y_nuEvt*10); // mm
  analysisManager->FillNtupleDColumn(11, z_nuEvt*10); // mm
  
  // fill ntuple
  analysisManager->AddNtupleRow();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
