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
/// \file PrimaryGeneratorAction.hh
/// \brief Definition of the PrimaryGeneratorAction class

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include <iostream>
#include <fstream>

using namespace std;

class G4ParticleGun;
class G4ParticleDefinition;
class G4Event;

/// The primary generator action class with particle gum.
///
/// It defines a single particle which hits the calorimeter 
/// perpendicular to the input face. The type of the particle
/// can be changed via the G4 build-in commands of G4ParticleGun class 
/// (see the macros provided with this example).

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction();    
  virtual ~PrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event* event);
  
  // set methods
  void SetRandomFlag(G4bool value);

private:
  G4ParticleGun*  fParticleGun; // G4 particle gun
  G4ParticleDefinition* fElectron;
  G4ParticleDefinition* fPositron;
  G4ParticleDefinition* fMuonM;
  G4ParticleDefinition* fMuonP;
  G4ParticleDefinition* fPionM;
  G4ParticleDefinition* fPionP;
  G4ParticleDefinition* fPi0;
  G4ParticleDefinition* fProton;
  G4ParticleDefinition* fProtonB;
  G4ParticleDefinition* fNeutron;
  G4ParticleDefinition* fNeutronB;
  G4ParticleDefinition* fPhoton;
  G4ParticleDefinition* fK0;
  G4ParticleDefinition* fK0B;
  G4ParticleDefinition* fKL0;
  G4ParticleDefinition* fKaonM;
  G4ParticleDefinition* fKaonP;
  G4ParticleDefinition* fSigmaM;
  G4ParticleDefinition* fSigmaBP;
  G4ParticleDefinition* fSigmaP;
  G4ParticleDefinition* fSigmaBM;
  G4ParticleDefinition* fSigma_cP;
  G4ParticleDefinition* fSigma_cBM;
  G4ParticleDefinition* fLambda0;
  G4ParticleDefinition* fLambda0B;
  G4ParticleDefinition* fLambda_cP;
  G4ParticleDefinition* fLambda_cBM;
  G4ParticleDefinition* fDP;
  G4ParticleDefinition* fDM;
  G4ParticleDefinition* fD0;
  G4ParticleDefinition* fD0B;
  G4ParticleDefinition* fDsP;
  G4ParticleDefinition* fDsM;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
