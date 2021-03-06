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
/// \file eventgenerator/HepMC/HepMCEx01/include/ExN04DetectorConstruction.hh
/// \brief Definition of the ExN04DetectorConstruction class
//
// $Id: ExN04DetectorConstruction.hh 77801 2013-11-28 13:33:20Z gcosmo $
//

#ifndef ExN04DetectorConstruction_h
#define ExN04DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;
class G4Material;
class G4Box;
class G4Tubs;
class G4LogicalVolume;
class G4VSolid;

class ExN04DetectorConstruction : public G4VUserDetectorConstruction {
public:
  ExN04DetectorConstruction();
  ~ExN04DetectorConstruction();

  virtual G4VPhysicalVolume* Construct();

  const G4VPhysicalVolume* GetEmulsionTopPV() const;
  const G4VPhysicalVolume* GetEmulsionBotPV() const;
  const G4VPhysicalVolume* GetBasePV() const;
  const G4VPhysicalVolume* GetWorldPV() const;
  const G4VPhysicalVolume* GetWaterPV() const;
  const G4VPhysicalVolume* GetAfterShieldingPV() const;
  const G4VPhysicalVolume* GetTopPlatePV() const;
  const G4VPhysicalVolume* GetBotPlatePV() const;

  public:
  
  void PrintDetectorParameters(); // MODIFIED
  
  G4double GetWorldSizeX()         {return fWorldSizeX;}; 
  G4double GetWorldSizeY()         {return fWorldSizeY;}; //mod
  G4double GetWorldSizeZ()         {return fWorldSizeZ;}; //mod

  const G4VPhysicalVolume* GetphysiWorld() {return fPhysiWorld;};  

private:
  
  G4Material*        fDefaultMaterial;
  G4double           fWorldSizeY;
  G4double           fWorldSizeZ;
  G4double           fWorldSizeX;

  G4Material*        fCylMaterial;
  G4double           fCylInR;
  G4double           fCylOutR;
  G4double           fCylSizeZ;
  
  G4Box*             fSolidWorld;    //pointer to the solid World 
  G4LogicalVolume*   fLogicWorld;    //pointer to the logical World
  G4VPhysicalVolume* fPhysiWorld;    //pointer to the physical World
  
  //DetectorMessenger* fDetectorMessenger;  //pointer to the Messenger
  
  G4VPhysicalVolume*   fDetectorPV; 
  G4VPhysicalVolume*   fEmulsionTopPV; 
  G4VPhysicalVolume*   fEmulsionBotPV; 
  G4VPhysicalVolume*   fBasePV;
  G4VPhysicalVolume*   fBase2PV;
  G4VPhysicalVolume*   fWaterPV;
  G4VPhysicalVolume*   fPolyethilenePV;
  G4VPhysicalVolume*   fBrickPV;
  G4VPhysicalVolume*   fPoly1PV;
  G4VPhysicalVolume*   fPoly2PV;
  G4VPhysicalVolume*   fPoly3PV;
  G4VPhysicalVolume*   fPolyTopPV;
  G4VPhysicalVolume*   fPolyTop2PV;
  G4VPhysicalVolume*   fCooling_boxPV;
  G4VPhysicalVolume*   fNitrogen_boxPV;
  G4VPhysicalVolume*   fAfterShieldingPV; 
  G4VPhysicalVolume*   fplateTopPV;
  G4VPhysicalVolume*   fplateBotPV;
  G4VPhysicalVolume*   fSidesPV;
  G4VPhysicalVolume*   fboxPV;

  
  G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps

private:

   void DefineMaterials();
  G4VPhysicalVolume* ConstructDetector();     //MODIFIED
  
};

// inline functions

inline const G4VPhysicalVolume* ExN04DetectorConstruction::GetEmulsionTopPV() const { 
  return fEmulsionTopPV; 
}

inline const G4VPhysicalVolume* ExN04DetectorConstruction::GetEmulsionBotPV() const { 
  return fEmulsionBotPV; 
}


inline const G4VPhysicalVolume* ExN04DetectorConstruction::GetBasePV() const { 
  return fBasePV; 
}

inline const G4VPhysicalVolume* ExN04DetectorConstruction::GetWaterPV() const { 
  return fWaterPV; 
}

inline const G4VPhysicalVolume* ExN04DetectorConstruction::GetAfterShieldingPV() const { 
  return fAfterShieldingPV; 
}

inline const G4VPhysicalVolume* ExN04DetectorConstruction::GetTopPlatePV() const { 
  return fplateTopPV; 
}

inline const G4VPhysicalVolume* ExN04DetectorConstruction::GetBotPlatePV() const { 
  return fplateBotPV; 
}
    
     
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#endif
