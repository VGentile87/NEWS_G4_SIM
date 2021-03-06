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
/// \file eventgenerator/HepMC/HepMCEx01/src/ExN04PrimaryGeneratorAction.cc
/// \brief Implementation of the ExN04PrimaryGeneratorAction class
//
// $Id: ExN04PrimaryGeneratorAction.cc 77801 2013-11-28 13:33:20Z gcosmo $
//

#include "ExN04PrimaryGeneratorAction.hh"
#include "ExN04PrimaryGeneratorMessenger.hh"
#include "ExN04DetectorConstruction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "HepMCG4AsciiReader.hh"
#include "HepMCG4PythiaInterface.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

class G4ParticleGun;
class G4GeneralParticleSource;
class G4Event;
class ExN04DetectorConstruction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ExN04PrimaryGeneratorAction::ExN04PrimaryGeneratorAction(ExN04DetectorConstruction* DC)
{
  // default generator is particle gun.
  currentGenerator = particleGun= new G4ParticleGun();
  currentGeneratorName = "particleGun";
  currentGenerator = particleSource= new G4GeneralParticleSource();
  currentGeneratorName = "particleSource";
  hepmcAscii = new HepMCG4AsciiReader();
#ifdef G4LIB_USE_PYTHIA
  pythiaGen = new HepMCG4PythiaInterface();
#else
  pythiaGen = 0;
#endif
  gentypeMap["particleSource"] = particleSource;
  gentypeMap["particleGun"] = particleGun;
  gentypeMap["hepmcAscii"] = hepmcAscii;
  gentypeMap["pythia"] = pythiaGen;

   messenger= new ExN04PrimaryGeneratorMessenger(this);
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ExN04PrimaryGeneratorAction::~ExN04PrimaryGeneratorAction()
{
  delete messenger;
  //delete particleGun;
  //delete particleSource;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void ExN04PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  
  if(currentGenerator)
    currentGenerator-> GeneratePrimaryVertex(anEvent);
  else
    G4Exception("ExN04PrimaryGeneratorAction::GeneratePrimaries",
                "PrimaryGeneratorAction001", FatalException,
                "generator is not instanciated." );
  
  //this function is called at the begining of event
  // 
  //fParticleGun->GeneratePrimaryVertex(anEvent);
  //particleSource->GeneratePrimaryVertex(anEvent);
}
