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
/// \file CalorHit.hh
/// \brief Definition of the CalorHit class

#ifndef CalorHit_h
#define CalorHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Threading.hh"

/// Calorimeter hit class
///
/// It defines data members to store the the energy deposit and track lengths
/// of charged particles in a selected volume:
/// - fEdep, fTrackLength

class CalorHit : public G4VHit
{
  public:
    CalorHit();
    CalorHit(const CalorHit&);
    virtual ~CalorHit();

    // operators
    const CalorHit& operator=(const CalorHit&);
    G4bool operator==(const CalorHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // methods from base class
    virtual void Draw() {}
    virtual void Print();

    // set methods
    void SetChamber(G4int cham);
    void SetIDZ(G4int IDZ);
    void SetIDZsub(G4int IDZsub);
    void SetParticleID(G4int particleID);
    void SetTrackID(G4int trackID);
    void SetParentID(G4int parentID);
    void SetCharge(G4double charge);
    void SetPosition(G4ThreeVector pos);
    void SetMomentum(G4ThreeVector mom);
    void SetEnergyPreS(G4double kE1);
    void SetEnergyPost(G4double kE2);
    void SetEnergyDepo(G4double edep);
    void SetTrackLength(G4double len);
    void SetProcessName(G4String procName);

    // get methods
    G4int GetChamber() const;
    G4int GetIDZ() const;
    G4int GetIDZsub() const;
    G4int GetParticleID() const;
    G4int GetTrackID() const;
    G4int GetParentID() const;
    G4double GetCharge() const;
    G4ThreeVector GetPosition() const;
    G4ThreeVector GetMomentum() const;
    G4double GetEnergyPreS() const;
    G4double GetEnergyPost() const;
    G4double GetEnergyDepo() const;
    G4double GetTrackLength() const;
    G4String GetProcessName() const;
    
  private:
    G4int fCham, fIDZ, fIDZsub, fParticleID, fTrackID, fParentID;
    G4double fCharge, fE1, fE2, fEdep, fLen;
    G4ThreeVector fPos, fMom;
    G4String fProcName;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

using CalorHitsCollection = G4THitsCollection<CalorHit>;

extern G4ThreadLocal G4Allocator<CalorHit>* CalorHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* CalorHit::operator new(size_t)
{
  if (!CalorHitAllocator) {
    CalorHitAllocator = new G4Allocator<CalorHit>;
  }
  void *hit;
  hit = (void *) CalorHitAllocator->MallocSingle();
  return hit;
}

inline void CalorHit::operator delete(void *hit)
{
  if (!CalorHitAllocator) {
    CalorHitAllocator = new G4Allocator<CalorHit>;
  }
  CalorHitAllocator->FreeSingle((CalorHit*) hit);
}

inline void CalorHit::SetChamber(G4int cham) { fCham = cham; }
inline void CalorHit::SetIDZ(G4int IDZ) { fIDZ = IDZ; }
inline void CalorHit::SetIDZsub(G4int IDZsub) { fIDZsub = IDZsub; }
inline void CalorHit::SetParticleID(G4int particleID) { fParticleID = particleID; }
inline void CalorHit::SetTrackID(G4int trackID) { fTrackID = trackID; }
inline void CalorHit::SetParentID(G4int parentID) { fParentID = parentID; }
inline void CalorHit::SetCharge(G4double charge) { fCharge = charge; }
inline void CalorHit::SetPosition(G4ThreeVector pos) { fPos = pos; }
inline void CalorHit::SetMomentum(G4ThreeVector mom) { fMom = mom; }
inline void CalorHit::SetEnergyPreS(G4double kE1) { fE1 = kE1; }
inline void CalorHit::SetEnergyPost(G4double kE2) { fE2 = kE2; }
inline void CalorHit::SetEnergyDepo(G4double edep) { fEdep = edep; }
inline void CalorHit::SetTrackLength(G4double len) { fLen = len; }
inline void CalorHit::SetProcessName(G4String procName) { fProcName = procName; }

inline G4int CalorHit::GetChamber() const { return fCham; }
inline G4int CalorHit::GetIDZ() const { return fIDZ; }
inline G4int CalorHit::GetIDZsub() const { return fIDZsub; }
inline G4int CalorHit::GetParticleID() const { return fParticleID; }
inline G4int CalorHit::GetTrackID() const { return fTrackID; }
inline G4int CalorHit::GetParentID() const { return fParentID; }
inline G4double CalorHit::GetCharge() const { return fCharge; }
inline G4ThreeVector CalorHit::GetPosition() const { return fPos; }
inline G4ThreeVector CalorHit::GetMomentum() const { return fMom; }
inline G4double CalorHit::GetEnergyPreS() const { return fE1; }
inline G4double CalorHit::GetEnergyPost() const { return fE2; }
inline G4double CalorHit::GetEnergyDepo() const { return fEdep; }
inline G4double CalorHit::GetTrackLength() const { return fLen; }
inline G4String CalorHit::GetProcessName() const { return fProcName; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
