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
/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class

#include "DetectorConstruction.hh"
#include "CalorimeterSD.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4SDManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal 
G4GlobalMagFieldMessenger* DetectorConstruction::fMagFieldMessenger = 0; 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction(),
   fCheckOverlaps(true),
   fNofLayers(-1),
   fNofPlanes(-1)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ 
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Define materials 
  DefineMaterials();
  
  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{
  // Tungsten material defined using NIST Manager
  auto nistManager = G4NistManager::Instance();
  nistManager->FindOrBuildMaterial("G4_W"); //Tungsten
  nistManager->FindOrBuildMaterial("G4_Pb"); //Lead
  nistManager->FindOrBuildMaterial("G4_Si"); //Silicon
  
  // material
  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;  
  G4double density;
  G4double fractionmass;
  G4int ncomponents, natoms;

  G4Element* elH  = new G4Element("Hydrogen", "H" , z= 1., a=  1.01*g/mole);
  //G4Element* elBe = new G4Element("Beryllium","Be", z= 4., a=  9.01*g/mole);
  G4Element* elC  = new G4Element("Carbon"  , "C" , z= 6., a= 12.01*g/mole);
  G4Element* elN  = new G4Element("Nitrogen", "N" , z= 7., a= 14.01*g/mole);
  G4Element* elO  = new G4Element("Oxygen"  , "O" , z= 8., a= 16.00*g/mole);
  G4Element* elF  = new G4Element("Fluorine", "F" , z= 9., a= 19.00*g/mole);
  G4Element* elNa = new G4Element("Sodium"  , "Na", z= 11.,a= 22.99*g/mole);
  G4Element* elSi = new G4Element("Silicon" , "Si", z= 14.,a= 28.09*g/mole);
  G4Element* elS  = new G4Element("Sulphur" , "S" , z= 16.,a= 32.07*g/mole);
  G4Element* elK  = new G4Element("Potassium","K" , z= 19.,a= 39.10*g/mole);
  G4Element* elBr = new G4Element("Bromine" , "Br", z= 35.,a= 79.90*g/mole);
  G4Element* elSr = new G4Element("Stronium", "Sr", z= 38.,a= 87.62*g/mole);
  G4Element* elAg = new G4Element("Silver"  , "Ag", z= 47.,a=107.87*g/mole);
  G4Element* elI  = new G4Element("Iodine"  , "I" , z= 53.,a=126.91*g/mole);
  G4Element* elBa = new G4Element("Barium"  , "Br", z= 56.,a=137.33*g/mole);
  //G4Element* elPb = new G4Element("Lead"    , "Pb", z= 82.,a=207.19*g/mole);
  //G4Element* elFe = new G4Element("Iron"    , "Fe", z= 26.,a=55.85*g/mole);
  //G4Element* elTi = new G4Element("Titanium", "Ti", z= 22.,a=44.87*g/mole);
  //G4Element* elCa = new G4Element("Calcium",  "Ca", z= 20.,a=40.078*g/mole);

  // //http://inspirehep.net/record/641997/files/641997.pdf
  // new G4Material("EmulsionMaterial", z=8.9, a=18.2*g/mole, density=2.40*g/cm3);
  // new G4Material("BaseMaterial", z=7.05, a=14.7*g/mole, density=1.28*g/cm3);

  G4Material* EmulsionMat 
    = new G4Material("EmulsionMaterial" , 
                     density     = 2.77*0.97*g/cm3,
                     ncomponents = 14);
  EmulsionMat->AddElement(elH, fractionmass=0.024);
  EmulsionMat->AddElement(elC, fractionmass=0.13);
  EmulsionMat->AddElement(elN, fractionmass=0.0481);
  EmulsionMat->AddElement(elO, fractionmass=0.1243);
  EmulsionMat->AddElement(elS, fractionmass=0.0009);
  EmulsionMat->AddElement(elBr,fractionmass=0.2786);
  EmulsionMat->AddElement(elAg,fractionmass=0.3835);
  EmulsionMat->AddElement(elI, fractionmass=0.0081);
  EmulsionMat->AddElement(elSi,fractionmass=0.0008);
  EmulsionMat->AddElement(elNa,fractionmass=0.0008);
  EmulsionMat->AddElement(elSr,fractionmass=0.0002);
  EmulsionMat->AddElement(elBa,fractionmass=0.0001);
  EmulsionMat->AddElement(elK, fractionmass=0.0005);
  EmulsionMat->AddElement(elF, fractionmass=0.00004);

  G4Material* H2O 
    = new G4Material("Water", 
                     density     = 1.000*g/cm3, 
                     ncomponents = 2);
  H2O->AddElement(elH, natoms=2);
  H2O->AddElement(elO, natoms=1);

  G4Material* TAC
    = new G4Material("TAC", 
                     density     = 1.35*g/cm3, 
                     ncomponents = 3);
  TAC->AddElement(elH, fractionmass=0.061);           // TAC = Cellulose Acetate
  TAC->AddElement(elC, fractionmass=0.445);           //       except density
  TAC->AddElement(elO, fractionmass=0.494);

  G4Material* BaseMat
    = new G4Material("BaseMaterial", 
                     density     = 1.35*0.97*g/cm3,
                     ncomponents = 2);
  BaseMat->AddMaterial(TAC, fractionmass=0.961);     // BaseMaterial = TAC + H2O
  BaseMat->AddMaterial(H2O, fractionmass=0.039);     // BaseMaterial = TAC + H2O

  // thermal pyrolytic graphite (TPG)
  new G4Material("TpgMaterial", z=6., a=12.*g/mole, density=2.2*g/cm3);

  // epoxy adhesive
  // http://www.farnell.com/datasheets/24297.pdf
  G4Material* epoxy = new G4Material("Epoxy", density=0.95*g/cm3, ncomponents=4);
  epoxy->AddElement(elH, natoms=5);
  epoxy->AddElement(elC, natoms=2);
  epoxy->AddElement(elO, natoms=1);
  epoxy->AddElement(elN, natoms=1);
 
  // Vacuum
  new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
                  kStateGas, 2.73*kelvin, 3.e-18*pascal);

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
  // Geometry parameters
  fNofLayers = 1000; // temporary
  G4double absoThickness = 1.*mm;
  G4double emulThickness = 0.05*mm;
  G4double baseThickness = 0.20*mm;
  G4double calorSizeX = 25*cm;
  G4double calorSizeY = 25*cm;
  
  fNofPlanes = 3;
  G4double sctThickness = 0.285*mm;
  G4double baseBoardThickness = 0.380*mm;
  G4double glueThickness = 0.025*mm;
  G4double planeSizeXY = 24*cm; // interface detector
  G4double gapPlane = 35.*mm;
  G4double gapCaloSCT = 20.*mm;
  
  auto layerThickness = absoThickness + emulThickness*2 + baseThickness;
  auto calorThickness = fNofLayers * layerThickness;
  auto planeThickness = baseBoardThickness + glueThickness*2 + sctThickness*2;
  auto stationThickness = gapCaloSCT+gapPlane*2+planeThickness*3;
  
  auto worldSizeX  = 1.2 * calorSizeX;
  auto worldSizeY  = 1.2 * calorSizeY;
  auto worldSizeZ  = 1.2 * (calorThickness+stationThickness);
  
  // Get materials
  auto defaultMaterial = G4Material::GetMaterial("Galactic");
  auto absorberMaterial = G4Material::GetMaterial("G4_W"); //Tungsten
  //auto absorberMaterial = G4Material::GetMaterial("G4_Pb"); //Lead
  auto emulsionMaterial = G4Material::GetMaterial("EmulsionMaterial");
  auto baseMaterial = G4Material::GetMaterial("BaseMaterial");
  auto sctMaterial = G4Material::GetMaterial("G4_Si"); //Silicon
  auto baseBoardMaterial = G4Material::GetMaterial("TpgMaterial");
  auto glueMaterial = G4Material::GetMaterial("Epoxy");
  
  if ( ! defaultMaterial || ! absorberMaterial || ! emulsionMaterial || ! baseMaterial || ! sctMaterial || ! baseBoardMaterial || ! glueMaterial ) {
    G4ExceptionDescription msg;
    msg << "Cannot retrieve materials already defined."; 
    G4Exception("DetectorConstruction::DefineVolumes()",
      "MyCode0001", FatalException, msg);
  }
   
  //     
  // World
  //
  auto worldS 
    = new G4Box("World",           // its name
                 worldSizeX/2, worldSizeY/2, worldSizeZ/2); // its size
                         
  auto worldLV
    = new G4LogicalVolume(
                 worldS,           // its solid
                 defaultMaterial,  // its material
                 "World");         // its name
                                   
  auto worldPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 worldLV,          // its logical volume                         
                 "World",          // its name
                 0,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  
  // 
  // Calorimeter
  // 
  auto calorimeterS
    = new G4Box("Calorimeter",     // its name
                 calorSizeX/2, calorSizeY/2, calorThickness/2); // its size
                         
  auto calorLV
    = new G4LogicalVolume(
                 calorimeterS,     // its solid
                 defaultMaterial,  // its material
                 "Calorimeter");   // its name
                                   
  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., -stationThickness/2),
                 calorLV,          // its logical volume                         
                 "Calorimeter",    // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps
   
  //                                 
  // Layer
  //
  auto layerS 
    = new G4Box("Layer",           // its name
                 calorSizeX/2, calorSizeY/2, layerThickness/2); //its size
                         
  auto layerLV
    = new G4LogicalVolume(
                 layerS,           // its solid
                 defaultMaterial,  // its material
                 "Layer");         // its name

  new G4PVReplica(
                 "Layer",          // its name
                 layerLV,          // its logical volume
                 calorLV,          // its mother
                 kZAxis,           // axis of replication
                 fNofLayers,        // number of replica
                 layerThickness);  // witdth of replica
  
  //                               
  // Absorber
  //
  auto absorberS 
    = new G4Box("Abso",            // its name
                 calorSizeX/2, calorSizeY/2, absoThickness/2); // its size
                         
  auto absorberLV
    = new G4LogicalVolume(
                 absorberS,        // its solid
                 absorberMaterial, // its material
                 "AbsoLV");        // its name
                                   
   new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., -(emulThickness*2+baseThickness)/2), // its position
                 absorberLV,       // its logical volume                         
                 "Abso",           // its name
                 layerLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 

  //                               
  // Base
  //
  auto baseS 
    = new G4Box("Base",             // its name
                 calorSizeX/2, calorSizeY/2, baseThickness/2); // its size
                         
  auto baseLV
    = new G4LogicalVolume(
                 baseS,             // its solid
                 baseMaterial,      // its material
                 "BaseLV");         // its name
                                   
  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., absoThickness/2), // its position
                 baseLV,           // its logical volume                         
                 "Base",           // its name
                 layerLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 

  //                               
  // Emulsion
  //
  auto emulsionS 
    = new G4Box("Emulsion",             // its name
                 calorSizeX/2, calorSizeY/2, emulThickness/2); // its size
                         
  auto emulsionLV
    = new G4LogicalVolume(
                 emulsionS,             // its solid
                 emulsionMaterial,      // its material
                 "EmulsionLV");         // its name
                                   
  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., absoThickness/2-baseThickness/2-emulThickness/2), // its position
                 emulsionLV,       // its logical volume                         
                 "Emulsion1",      // its name
                 layerLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps
                                
  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., absoThickness/2+baseThickness/2+emulThickness/2), // its position
                 emulsionLV,       // its logical volume                         
                 "Emulsion2",      // its name
                 layerLV,          // its mother  volume
                 false,            // no boolean operation
                 1,                // copy number
                 fCheckOverlaps);  // checking overlaps

  //                                 
  // Station
  //
  auto stationS 
    = new G4Box("Station",           // its name
                 planeSizeXY/2, planeSizeXY/2, stationThickness/2); //its size
                         
  auto stationLV
    = new G4LogicalVolume(
                 stationS,         // its solid
                 defaultMaterial,  // its material
                 "Station");       // its name

  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., calorThickness/2),
                 stationLV,        // its logical volume                         
                 "Station",        // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps

  //                                 
  // Plane
  //
  auto planeS 
    = new G4Box("Plane",           // its name
                 planeSizeXY/2, planeSizeXY/2, planeThickness/2); //its size

  auto planeLV
    = new G4LogicalVolume(
                 planeS,           // its solid
                 defaultMaterial,  // its material
                 "Plane");         // its name

  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., -(planeThickness+gapPlane)+0.5*gapCaloSCT), // its position
                 planeLV,          // its logical volume                         
                 "Plane1",         // its name
                 stationLV,        // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 

  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 0.5*gapCaloSCT), // its position
                 planeLV,          // its logical volume                         
                 "Plane2",         // its name
                 stationLV,        // its mother  volume
                 false,            // no boolean operation
                 1,                // copy number
                 fCheckOverlaps);  // checking overlaps 

  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., (planeThickness+gapPlane)+0.5*gapCaloSCT), // its position
                 planeLV,          // its logical volume                         
                 "Plane3",         // its name
                 stationLV,        // its mother  volume
                 false,            // no boolean operation
                 2,                // copy number
                 fCheckOverlaps);  // checking overlaps 

  //                               
  // BaseBoard
  //
  auto baseBoardS 
    = new G4Box("BaseBoard",        // its name
                 planeSizeXY/2, planeSizeXY/2, baseBoardThickness/2); // its size

  auto baseBoardLV
    = new G4LogicalVolume(
                 baseBoardS,        // its solid
                 baseBoardMaterial, // its material
                 "BaseBoardLV");    // its name

  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 0.), // its position
                 baseBoardLV,      // its logical volume                         
                 "BaseBoard",      // its name
                 planeLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 

  //                               
  // Glue
  //
  auto glueS 
    = new G4Box("Glue",        // its name
                 planeSizeXY/2, planeSizeXY/2, glueThickness/2); // its size
                         
  auto glueLV
    = new G4LogicalVolume(
                 glueS,        // its solid
                 glueMaterial, // its material
                 "GlueLV");    // its name

  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., -(baseBoardThickness+glueThickness)/2), // its position
                 glueLV,           // its logical volume                         
                 "Glue1",          // its name
                 planeLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 

  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., (baseBoardThickness+glueThickness)/2), // its position
                 glueLV,           // its logical volume                         
                 "Glue2",          // its name
                 planeLV,          // its mother  volume
                 false,            // no boolean operation
                 1,                // copy number
                 fCheckOverlaps);  // checking overlaps 

  //                               
  // SCT
  //
  auto sctS 
    = new G4Box("SCT",        // its name
                 planeSizeXY/2, planeSizeXY/2, sctThickness/2); // its size
                         
  auto sctLV
    = new G4LogicalVolume(
                 sctS,        // its solid
                 sctMaterial, // its material
                 "SCTLV");    // its name

  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., -(baseBoardThickness+sctThickness)/2-glueThickness), // its position
                 sctLV,            // its logical volume                         
                 "SCT1",           // its name
                 planeLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 

  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., (baseBoardThickness+sctThickness)/2+glueThickness), // its position
                 sctLV,            // its logical volume                         
                 "SCT2",           // its name
                 planeLV,          // its mother  volume
                 false,            // no boolean operation
                 1,                // copy number
                 fCheckOverlaps);  // checking overlaps 

  //
  // print parameters
  //
  G4cout
    << G4endl 
    << "------------------------------------------------------------" << G4endl
    << "---> The calorimeter is " << fNofLayers << " layers of: [ "
    << absoThickness/mm << "mm of " << absorberMaterial->GetName() 
    << " + "
    << emulThickness/mm << "mm of " << emulsionMaterial->GetName()
    << " + "
    << baseThickness/mm << "mm of " << baseMaterial->GetName()
    << " + "
    << emulThickness/mm << "mm of " << emulsionMaterial->GetName() << " ] " << G4endl
    << "------------------------------------------------------------" << G4endl;
  
  //                                        
  // Visualization attributes
  //
  worldLV->SetVisAttributes(G4VisAttributes::GetInvisible());

  //auto visAttributes = new G4VisAttributes(G4Colour(1.0,1.0,1.0)); // white
  auto visAttributes = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5)); // grey
  //visAttributes->SetVisibility(false);
  calorLV->SetVisAttributes(visAttributes);

  layerLV->SetVisAttributes(G4VisAttributes::GetInvisible());
  
  visAttributes = new G4VisAttributes(G4Colour(0.0, 0.0, 0.9)); // blue
  visAttributes->SetVisibility(false);
  absorberLV->SetVisAttributes(visAttributes);

  visAttributes = new G4VisAttributes(G4Colour(0.9,0.9,0.0)); // yellow
  visAttributes->SetVisibility(false);
  baseLV->SetVisAttributes(visAttributes);

  visAttributes = new G4VisAttributes(G4Colour(0.8888,0.0,0.0)); // red
  visAttributes->SetVisibility(false);
  emulsionLV->SetVisAttributes(visAttributes);

  stationLV->SetVisAttributes(G4VisAttributes::GetInvisible());

  visAttributes = new G4VisAttributes(G4Colour(0.0,1.0,0.0)); // green
  //visAttributes = new G4VisAttributes(G4Colour(0.0, 0.0, 0.9));
  sctLV->SetVisAttributes(visAttributes);
  
  //
  // Always return the physical World
  //
  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{
  // G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

  // 
  // Sensitive detectors
  //
  auto emulsionSD 
    = new CalorimeterSD("EmulsionSD", "EmulsionHitsCollection", fNofLayers);
  G4SDManager::GetSDMpointer()->AddNewDetector(emulsionSD);
  SetSensitiveDetector("EmulsionLV",emulsionSD);






  // 
  // Magnetic field
  //
  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  G4ThreeVector fieldValue;
  fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  fMagFieldMessenger->SetVerboseLevel(1);
  
  // Register the field messenger for deleting
  G4AutoDelete::Register(fMagFieldMessenger);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
