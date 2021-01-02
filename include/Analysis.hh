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
/// \file Analysis.hh
/// \brief Selection of the analysis technology

#ifndef Analysis_h
#define Analysis_h 1

#include "g4root.hh"
//#include "g4csv.hh"
//#include "g4xml.hh"

#endif

#include "G4Types.hh"
#include <vector>

extern G4ThreadLocal double e_beam;
extern G4ThreadLocal int id_beam;
extern G4ThreadLocal double x_beam;
extern G4ThreadLocal double y_beam;
extern G4ThreadLocal int pdgnu_nuEvt;
extern G4ThreadLocal int pdglep_nuEvt;
extern G4ThreadLocal double Enu_nuEvt;
extern G4ThreadLocal double Plep_nuEvt;
extern G4ThreadLocal int cc_nuEvt;
extern G4ThreadLocal double x_nuEvt;
extern G4ThreadLocal double y_nuEvt;
extern G4ThreadLocal double z_nuEvt;
extern G4ThreadLocal std::vector<int> cham;
extern G4ThreadLocal std::vector<int> idz;
extern G4ThreadLocal std::vector<int> idzsub;
extern G4ThreadLocal std::vector<int> pdgid;
extern G4ThreadLocal std::vector<int> id;
extern G4ThreadLocal std::vector<int> idParent;
extern G4ThreadLocal std::vector<double> charge;
extern G4ThreadLocal std::vector<double> x;
extern G4ThreadLocal std::vector<double> y;
extern G4ThreadLocal std::vector<double> z;
extern G4ThreadLocal std::vector<double> px;
extern G4ThreadLocal std::vector<double> py;
extern G4ThreadLocal std::vector<double> pz;
extern G4ThreadLocal std::vector<double> e1;
extern G4ThreadLocal std::vector<double> e2;
extern G4ThreadLocal std::vector<double> len;
extern G4ThreadLocal std::vector<double> edep;
