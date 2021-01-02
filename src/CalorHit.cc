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
/// \file CalorHit.cc
/// \brief Implementation of the CalorHit class

#include "CalorHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<CalorHit>* CalorHitAllocator = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CalorHit::CalorHit()
 : G4VHit(),
   fCham(-1),
   fIDZ(-1),
   fIDZsub(-1),
   fParticleID(0),
   fTrackID(0),
   fParentID(0),
   fCharge(0),
   fE1(0),
   fE2(0),
   fEdep(0),
   fLen(0),
   fPos(0),
   fMom(0),
   fProcName("")
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CalorHit::~CalorHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CalorHit::CalorHit(const CalorHit& right)
  : G4VHit()
{
  fCham         = right.fCham;
  fIDZ          = right.fIDZ;
  fIDZsub       = right.fIDZsub;
  fParticleID   = right.fParticleID;
  fTrackID      = right.fTrackID;
  fParentID     = right.fParentID;
  fCharge       = right.fCharge;
  fPos          = right.fPos;
  fMom          = right.fMom;
  fE1           = right.fE1;
  fE2           = right.fE2;
  fEdep         = right.fEdep;
  fLen          = right.fLen;
  fProcName     = right.fProcName;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const CalorHit& CalorHit::operator=(const CalorHit& right)
{
  fCham         = right.fCham;
  fIDZ          = right.fIDZ;
  fIDZsub       = right.fIDZsub;
  fParticleID   = right.fParticleID;
  fTrackID      = right.fTrackID;
  fParentID     = right.fParentID;
  fCharge       = right.fCharge;
  fPos          = right.fPos;
  fMom          = right.fMom;
  fE1           = right.fE1;
  fE2           = right.fE2;
  fEdep         = right.fEdep;
  fLen          = right.fLen;
  fProcName     = right.fProcName;

  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool CalorHit::operator==(const CalorHit& right) const
{
  return ( this == &right ) ? true : false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CalorHit::Print()
{
  G4cout
     << "PDGID: "
     << std::setw(5) <<  fParticleID << " "
     << "Cham,IDZ,IDZsub,X,Y: "
     << std::setw(1) <<  fCham << " "
     << std::setw(3) <<  fIDZ << " "
     << std::setw(1) <<  fIDZsub << " "
     << std::setw(6) <<  fPos.x() << " "
     << std::setw(6) <<  fPos.y()
     << ", Edep: " 
     << std::setw(7) << G4BestUnit(fEdep,"Energy")
     << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
