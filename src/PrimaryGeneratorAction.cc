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
/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Electron.hh"
#include "G4MuonMinus.hh"
#include "G4NeutrinoE.hh"
#include "G4NeutrinoMu.hh"
#include "G4NeutrinoTau.hh"
#include "G4AntiNeutrinoE.hh"
#include "G4AntiNeutrinoMu.hh"
#include "G4AntiNeutrinoTau.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "Analysis.hh"
#include <string>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// https://indico.ihep.ac.cn/event/9624/session/4/contribution/15/material/slides/0.pdf
namespace { G4Mutex myMutex = G4MUTEX_INITIALIZER; }
// variable for text read
ifstream* source;

PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(nullptr),
   fElectron(nullptr),
   fPositron(nullptr),
   fMuonM(nullptr),
   fMuonP(nullptr),
   fPionM(nullptr),
   fPionP(nullptr),
   fPi0(nullptr),
   fProton(nullptr),
   fProtonB(nullptr),
   fNeutron(nullptr),
   fNeutronB(nullptr),
   fPhoton(nullptr),
   fK0(nullptr),
   fK0B(nullptr),
   fKL0(nullptr),
   fKaonM(nullptr),
   fKaonP(nullptr),
   fSigmaM(nullptr),
   fSigmaBP(nullptr),
   fSigmaP(nullptr),
   fSigmaBM(nullptr),
   fSigma_cP(nullptr),
   fSigma_cBM(nullptr),
   fLambda0(nullptr),
   fLambda0B(nullptr),
   fLambda_cP(nullptr),
   fLambda_cBM(nullptr),
   fDP(nullptr),
   fDM(nullptr),
   fD0(nullptr),
   fD0B(nullptr),
   fDsP(nullptr),
   fDsM(nullptr)
{
  G4AutoLock lock(&myMutex);
  
  G4int nofParticles = 1;
  fParticleGun = new G4ParticleGun(nofParticles);

  // default particle kinematic
  //
  //G4ParticleDefinition* particleDefinition = G4Electron::Definition();
  //G4ParticleDefinition* particleDefinition = G4MuonMinus::Definition();
  //G4ParticleDefinition* particleDefinition = G4NeutrinoE::Definition();

  auto particleTable = G4ParticleTable::GetParticleTable();
  fElectron = particleTable->FindParticle("e-");
  fPositron = particleTable->FindParticle("e+");
  fMuonM = particleTable->FindParticle("mu-");
  fMuonP = particleTable->FindParticle("mu+");
  fPionM = particleTable->FindParticle("pi-");
  fPionP = particleTable->FindParticle("pi+");
  fPi0 = particleTable->FindParticle("pi0");
  fProton = particleTable->FindParticle("proton");
  fProtonB = particleTable->FindParticle("anti_proton");
  fNeutron = particleTable->FindParticle("neutron");
  fNeutronB = particleTable->FindParticle("anti_neutron");
  fPhoton = particleTable->FindParticle("gamma");
  fK0 = particleTable->FindParticle("kaon0");
  fK0B = particleTable->FindParticle("anti_kaon0");
  fKL0 = particleTable->FindParticle("kaon0L");
  fKaonM = particleTable->FindParticle("kaon-");
  fKaonP = particleTable->FindParticle("kaon+");
  fSigmaM = particleTable->FindParticle("sigma-");
  fSigmaBP = particleTable->FindParticle("anti_sigma-");
  fSigmaP = particleTable->FindParticle("sigma+");
  fSigmaBM = particleTable->FindParticle("anti_sigma+");
  fSigma_cP = particleTable->FindParticle("sigma_c+");
  fSigma_cBM = particleTable->FindParticle("anti_sigma_c+");
  fLambda0 = particleTable->FindParticle("lambda");
  fLambda0B = particleTable->FindParticle("anti_lambda");
  fLambda_cP = particleTable->FindParticle("lambda_c+");
  fLambda_cBM = particleTable->FindParticle("anti_lambda_c+");
  fDP = particleTable->FindParticle("D+");
  fDM = particleTable->FindParticle("D-");
  fD0 = particleTable->FindParticle("D0");
  fD0B = particleTable->FindParticle("anti_D0");
  fDsP = particleTable->FindParticle("Ds+");
  fDsM = particleTable->FindParticle("Ds-");

  if(!source) {
    //source = new ifstream("gen_ntuple2/input/numu_faser_1M.dump._001.txt");
    source = new ifstream("../fnumin/gen_ntuple2/input/anumu_faser_1M.dump._001.txt");
    if(!source->is_open()) {
      printf("Error opening file numu_faser_1M.dump.txt");
      exit(1);
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  G4AutoLock lock(&myMutex);
  if(source) { delete source; source = 0; }
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// This function is called at the begining of event
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4AutoLock lock(&myMutex);
  
  G4double worldYHalfLength = 0.;
  G4double worldZHalfLength = 0.;
  auto worldLV = G4LogicalVolumeStore::GetInstance()->GetVolume("World");
  G4Box* worldBox = dynamic_cast<G4Box*>(worldLV->GetSolid());
  if ( worldBox ) {
    worldYHalfLength = worldBox->GetYHalfLength();  
    worldZHalfLength = worldBox->GetZHalfLength();  
  }
  else {
    G4ExceptionDescription msg;
    msg << "World volume of box shape not found." << G4endl;
    msg << "Perhaps you have changed geometry." << G4endl;
    msg << "The gun will be place in the center.";
    G4Exception("B4PrimaryGeneratorAction::GeneratePrimaries()",
      "MyCode0002", JustWarning, msg);
  }

  // //
  // // GENIE: a nu_mu collision event
  // //
  // fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,-worldZHalfLength+worldZHalfLength*(1-1/1.2)+1.3*500*mm+0.5*mm));

  // fParticleGun->SetParticleDefinition(fMuonM);
  // fParticleGun->SetParticleEnergy(202.17*GeV);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(6.63, -4.06, 202.02));
  // fParticleGun->GeneratePrimaryVertex(anEvent);

  // fParticleGun->SetParticleDefinition(fProton);
  // fParticleGun->SetParticleEnergy(53.00*GeV);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-0.33, 0.16, 52.99));
  // fParticleGun->GeneratePrimaryVertex(anEvent);

  // fParticleGun->SetParticleDefinition(fProtonB);
  // fParticleGun->SetParticleEnergy(64.42*GeV);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-0.46, 0.74, 64.41));
  // fParticleGun->GeneratePrimaryVertex(anEvent);

  // fParticleGun->SetParticleDefinition(fPi0);
  // fParticleGun->SetParticleEnergy(9.48*GeV);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-0.09, 0.02, 9.48));
  // fParticleGun->GeneratePrimaryVertex(anEvent);

  // fParticleGun->SetParticleDefinition(fPi0);
  // fParticleGun->SetParticleEnergy(2.57*GeV);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.20,-0.34, 2.54));
  // fParticleGun->GeneratePrimaryVertex(anEvent);

  // fParticleGun->SetParticleDefinition(fPi0);
  // fParticleGun->SetParticleEnergy(0.66*GeV);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-0.36, 0.06, 0.53));
  // fParticleGun->GeneratePrimaryVertex(anEvent);

  // fParticleGun->SetParticleDefinition(fPionP);
  // fParticleGun->SetParticleEnergy(320.70*GeV);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-2.87, 0.89, 320.69));
  // fParticleGun->GeneratePrimaryVertex(anEvent);

  // fParticleGun->SetParticleDefinition(fPi0);
  // fParticleGun->SetParticleEnergy(145.18*GeV);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-1.17, 0.95, 145.18));
  // fParticleGun->GeneratePrimaryVertex(anEvent);

  // fParticleGun->SetParticleDefinition(fPionM);
  // fParticleGun->SetParticleEnergy(190.55*GeV);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-1.51, 1.52, 190.54));
  // fParticleGun->GeneratePrimaryVertex(anEvent);

  // fParticleGun->SetParticleDefinition(fPi0);
  // fParticleGun->SetParticleEnergy(10.91*GeV);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-0.15, 0.10, 10.91));
  // fParticleGun->GeneratePrimaryVertex(anEvent);

  // fParticleGun->SetParticleDefinition(fProton);
  // fParticleGun->SetParticleEnergy(1.54*GeV);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.26, -0.07, 1.19));
  // fParticleGun->GeneratePrimaryVertex(anEvent);

  // fParticleGun->SetParticleDefinition(fProton);
  // fParticleGun->SetParticleEnergy(0.98*GeV);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-0.18, -0.15, -0.16));
  // fParticleGun->GeneratePrimaryVertex(anEvent);

  // fParticleGun->SetParticleDefinition(fProton);
  // fParticleGun->SetParticleEnergy(1.03*GeV);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.32, 0.18, 0.22));
  // fParticleGun->GeneratePrimaryVertex(anEvent);


  ///////////
  // BES-III:
  ///////////
  // fParticleGun->SetParticleDefinition(fElectron);
  // fParticleGun->SetParticleEnergy(0.679992*GeV);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0.121218,0.6691));
  // fParticleGun->SetParticlePosition(G4ThreeVector(0,0,0));
  // fParticleGun->GeneratePrimaryVertex(anEvent);

  // fParticleGun->SetParticleDefinition(fPositron);
  // fParticleGun->SetParticleEnergy(0.127887*GeV);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0.121218,0.0407536));
  // fParticleGun->SetParticlePosition(G4ThreeVector(0,0,0));
  // fParticleGun->GeneratePrimaryVertex(anEvent);

  // fParticleGun->SetParticleDefinition(fMuonM);
  // fParticleGun->SetParticleEnergy(0.599883*GeV);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0.121218,0.577929));
  // fParticleGun->SetParticlePosition(G4ThreeVector(0,0,0));
  // fParticleGun->GeneratePrimaryVertex(anEvent);

  // fParticleGun->SetParticleDefinition(fMuonP);
  // fParticleGun->SetParticleEnergy(0.207995*GeV);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0.121218,0.131924));
  // fParticleGun->SetParticlePosition(G4ThreeVector(0,0,0));
  // fParticleGun->GeneratePrimaryVertex(anEvent);

  // fParticleGun->SetParticleDefinition(fPionM);
  // fParticleGun->SetParticleEnergy(0.505079*GeV);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0.121218,0.470033));
  // fParticleGun->SetParticlePosition(G4ThreeVector(0,0,0));
  // fParticleGun->GeneratePrimaryVertex(anEvent);

  // fParticleGun->SetParticleDefinition(fPionP);
  // fParticleGun->SetParticleEnergy(0.302799*GeV);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0.121218,0.23982));
  // fParticleGun->SetParticlePosition(G4ThreeVector(0,0,0));
  // fParticleGun->GeneratePrimaryVertex(anEvent);

  // // single particle gun:
  // fParticleGun->SetParticleDefinition(fNeutron);
  // fParticleGun->SetParticleEnergy(1.0*GeV);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
  // fParticleGun->SetParticlePosition(G4ThreeVector(0,0,-worldZHalfLength));
  // // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,-1,0.2));
  // // fParticleGun->SetParticlePosition(G4ThreeVector(0,worldYHalfLength,-2.5*cm));
  // fParticleGun->GeneratePrimaryVertex(anEvent);


  // FASERnu muons:
  // // randomized
  // e_beam = G4RandFlat::shoot(0.,7000.);
  // id_beam = 13;
  // x_beam = G4RandFlat::shoot(-12.5,12.5);
  // y_beam = G4RandFlat::shoot(-12.5,12.5);

  // //fParticleGun->SetParticleDefinition(fElectron);
  // fParticleGun->SetParticleDefinition(fMuonM);
  // fParticleGun->SetParticleEnergy(e_beam*GeV);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
  // fParticleGun->SetParticlePosition(G4ThreeVector(x_beam*cm,y_beam*cm,-worldZHalfLength));
  // fParticleGun->GeneratePrimaryVertex(anEvent);
  // //printf("%g, %g, %g\n",e_beam,x_beam,y_beam);


  // FASERnu text read:
  float tmp1, tmp2, tmp3, tmp4;
  int i1, i2, i3;
  bool start = false;
  string line;
  while ( getline(*source,line) ) {
    if(line.compare(0,5,"event")==0) {
      if(!start) {
	start = true;
	continue;
      }
      else break;
    }
    else if(line.compare(0,5,"info:")==0) {
      sscanf(line.data(),"info: %d %d %f %f %d",&i1,&i2,&tmp1,&tmp2,&i3);
      pdgnu_nuEvt = i1; pdglep_nuEvt = i2; cc_nuEvt = i3; Enu_nuEvt = tmp1; Plep_nuEvt = tmp2;
      x_nuEvt = G4RandFlat::shoot(-12.5,12.5);
      y_nuEvt = G4RandFlat::shoot(-12.5,12.5);
      z_nuEvt = G4RandFlat::shoot(-69.65,60.35); // 130(Calo)+9.3(Silicon)
      e_beam = 0; id_beam = 0; x_beam = 0; y_beam = 0;
      start = true;
    }
    else if(start) {
      sscanf(line.data(),"%d %f %f %f %f",&i1,&tmp1,&tmp2,&tmp3,&tmp4);

      if(i1==11) fParticleGun->SetParticleDefinition(fElectron);
      else if(i1==-11) fParticleGun->SetParticleDefinition(fPositron);
      else if(i1==13) fParticleGun->SetParticleDefinition(fMuonM);
      else if(i1==-13) fParticleGun->SetParticleDefinition(fMuonP);
      else if(i1==211) fParticleGun->SetParticleDefinition(fPionP);
      else if(i1==-211) fParticleGun->SetParticleDefinition(fPionM);
      else if(i1==111) fParticleGun->SetParticleDefinition(fPi0);
      else if(i1==2212) fParticleGun->SetParticleDefinition(fProton);
      else if(i1==-2212) fParticleGun->SetParticleDefinition(fProtonB);
      else if(i1==2112) fParticleGun->SetParticleDefinition(fNeutron);
      else if(i1==-2112) fParticleGun->SetParticleDefinition(fNeutronB);
      else if(i1==22) fParticleGun->SetParticleDefinition(fPhoton);
      else if(i1==311) fParticleGun->SetParticleDefinition(fK0);
      else if(i1==-311) fParticleGun->SetParticleDefinition(fK0B);
      else if(i1==130) fParticleGun->SetParticleDefinition(fKL0);
      else if(i1==-321) fParticleGun->SetParticleDefinition(fKaonM);
      else if(i1==321) fParticleGun->SetParticleDefinition(fKaonP);
      else if(i1==3112) fParticleGun->SetParticleDefinition(fSigmaM);
      else if(i1==-3112) fParticleGun->SetParticleDefinition(fSigmaBP);
      else if(i1==3222) fParticleGun->SetParticleDefinition(fSigmaP);
      else if(i1==-3222) fParticleGun->SetParticleDefinition(fSigmaBM);
      else if(i1==4212) fParticleGun->SetParticleDefinition(fSigma_cP);
      else if(i1==-4212) fParticleGun->SetParticleDefinition(fSigma_cBM);
      else if(i1==3122) fParticleGun->SetParticleDefinition(fLambda0);
      else if(i1==-3122) fParticleGun->SetParticleDefinition(fLambda0B);
      else if(i1==4122) fParticleGun->SetParticleDefinition(fLambda_cP);
      else if(i1==-4122) fParticleGun->SetParticleDefinition(fLambda_cBM);
      else if(i1==411) fParticleGun->SetParticleDefinition(fDP);
      else if(i1==-411) fParticleGun->SetParticleDefinition(fDM);
      else if(i1==421) fParticleGun->SetParticleDefinition(fD0);
      else if(i1==-421) fParticleGun->SetParticleDefinition(fD0B);
      else if(i1==431) fParticleGun->SetParticleDefinition(fDsP);
      else if(i1==-431) fParticleGun->SetParticleDefinition(fDsM);
      else {
	if(abs(i1)!=12 && abs(i1)!=16) {
	  printf("Error: Unkown particle ID: %d\n",i1);
	}
	continue;
      }

      //printf("Xin: %d %f %f %f %f\n",i1,tmp1,tmp2,tmp3,tmp4);

      fParticleGun->SetParticleEnergy(tmp1*GeV);
      fParticleGun->SetParticleMomentumDirection(G4ThreeVector(tmp2,tmp3,tmp4));
      fParticleGun->SetParticlePosition(G4ThreeVector(x_nuEvt*cm,y_nuEvt*cm,z_nuEvt*cm));
      fParticleGun->GeneratePrimaryVertex(anEvent);
    }
  }
  printf("Xin: %d %d %d %f %f\n",pdgnu_nuEvt,pdglep_nuEvt,cc_nuEvt,Enu_nuEvt,Plep_nuEvt);
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
