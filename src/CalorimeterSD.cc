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
/// \file CalorimeterSD.cc
/// \brief Implementation of the CalorimeterSD class

#include "CalorimeterSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4VProcess.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CalorimeterSD::CalorimeterSD(
			     const G4String& name, 
			     const G4String& hitsCollectionName,
			     G4int nofLayers)
 : G4VSensitiveDetector(name),
   fHitsCollection(nullptr),
   fNofLayers(nofLayers)
{
  collectionName.insert(hitsCollectionName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CalorimeterSD::~CalorimeterSD() 
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CalorimeterSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection
  fHitsCollection 
    = new CalorHitsCollection(SensitiveDetectorName, collectionName[0]); 

  // Add this collection in hce
  auto hcID 
    = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool CalorimeterSD::ProcessHits(G4Step* step, 
				  G4TouchableHistory*)
{  
  // energy deposit
  G4double edep = step->GetTotalEnergyDeposit();
  if ( edep==0. ) return false; 

  const G4StepPoint* preStepPoint = step->GetPreStepPoint();
  auto touchable = preStepPoint->GetTouchable();
    
  // Get calorimeter cell id 
  auto replicaNumber = touchable->GetReplicaNumber(1);
  auto copyNumber = touchable->GetCopyNumber();
  
  if ( replicaNumber<0 || replicaNumber>=fNofLayers || copyNumber<0 || copyNumber>1) {
    G4ExceptionDescription msg;
    msg << "Cannot access hit replicaNumber " << replicaNumber << " copyNumber " << copyNumber; 
    G4Exception("CalorimeterSD::ProcessHits()",
      "MyCode0004", FatalException, msg);
  }         

  const G4StepStatus status = preStepPoint->GetStepStatus();

  G4ParticleDefinition*  pd = step->GetTrack()->GetDefinition();
  G4int particleID   = pd->GetPDGEncoding();
  G4int trackID      = step->GetTrack()->GetTrackID();
  G4int parentID     = step->GetTrack()->GetParentID();
  G4double charge    = pd->GetPDGCharge();
  G4ThreeVector pos  = preStepPoint->GetPosition();
  G4ThreeVector mom  = preStepPoint->GetMomentum();

  G4double kE1      = preStepPoint->GetKineticEnergy();
  G4double kE2      = step->GetPostStepPoint()->GetKineticEnergy();
  G4double len      = step->GetStepLength();
  const G4VProcess* proc = step->GetPostStepPoint()->GetProcessDefinedStep();
  G4String procName = proc ? proc->GetProcessName() : "";

  if (status == fGeomBoundary) {
    CalorHit* hit = new CalorHit();

    hit->SetChamber(0);
    hit->SetIDZ(replicaNumber);
    hit->SetIDZsub(copyNumber);
    hit->SetParticleID(particleID);
    hit->SetTrackID(trackID);
    hit->SetParentID(parentID);
    hit->SetCharge(charge);
    hit->SetPosition(pos);
    hit->SetMomentum(mom);
    hit->SetEnergyPreS(kE1);
    hit->SetEnergyPost(kE2);
    hit->SetEnergyDepo(edep);
    hit->SetTrackLength(len);
    hit->SetProcessName(procName);

    fHitsCollection->insert(hit);
  }

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CalorimeterSD::EndOfEvent(G4HCofThisEvent*)
{
  if ( verboseLevel>1 ) { 
     auto nofHits = fHitsCollection->entries();
     G4cout
       << G4endl 
       << "-------->Hits Collection: in this event they are " << nofHits 
       << " hits in the detector. The hit processes are ";
     G4int maxN = nofHits>25 ? 25 : nofHits;
     for(auto i=0; i<maxN; i++) {
       G4cout << (*fHitsCollection)[i]->GetProcessName() << " ";
     }
     G4cout << "..." << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
