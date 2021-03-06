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
/// \file eventgenerator/HepMC/HepMCEx01/src/ExN04DetectorConstruction.cc
/// \brief Implementation of the ExN04DetectorConstruction class
//
// $Id: ExN04DetectorConstruction.cc 77801 2013-11-28 13:33:20Z gcosmo $
//

#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4FieldManager.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4PVParameterised.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4TransportationManager.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "ExN04CalorimeterParametrisation.hh"
#include "ExN04CalorimeterROGeometry.hh"
#include "ExN04CalorimeterSD.hh"
#include "ExN04DetectorConstruction.hh"
#include "ExN04Field.hh"
#include "ExN04MuonSD.hh"
#include "ExN04TrackerParametrisation.hh"
#include "ExN04TrackerSD.hh"


#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4PhysicalConstants.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ExN04DetectorConstruction::ExN04DetectorConstruction()
{
  //#include "ExN04DetectorParameterDef.icc"
  DefineMaterials();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ExN04DetectorConstruction::~ExN04DetectorConstruction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void ExN04DetectorConstruction::DefineMaterials()
{
  //-------------------------------------------------------------------------
  // Materials
  //-------------------------------------------------------------------------


  
  //
  // Database Material
  //
  
  G4NistManager* nistManager = G4NistManager::Instance();
  nistManager->SetVerbose(1);
  nistManager->FindOrBuildMaterial("G4_POLYETHYLENE"); // plates 
  nistManager->FindOrBuildMaterial("G4_WATER");   // shielding
  nistManager->FindOrBuildMaterial("G4_POLYSTYRENE");  // base emulsion
  nistManager->FindOrBuildMaterial("G4_Pb");  //  lead
  nistManager->FindOrBuildMaterial("G4_Fe");
  nistManager->FindOrBuildMaterial("G4_Cu");  
  nistManager->FindOrBuildMaterial("G4_PLEXIGLASS");
  nistManager->FindOrBuildMaterial("G4_AIR");  

  //
  // Material Properties
  //
  
  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;  
  G4double density, opera_density, opera_base_density;
  G4double fractionmass;
  G4String name, symbol; 
  G4int ncomponents, natoms;
  G4int base_ncomponents;

  //
  // Emulsion Component  
  //
  
  a = 126.9*g/mole;
  G4Element* elI  = new G4Element(name="Iodium", symbol="I", z=53., a);
  
  a = 107.9*g/mole;
  G4Element* elAg  = new G4Element(name="Silver", symbol="Ag", z=47., a);

  a = 79.9*g/mole;
  G4Element* elBr  = new G4Element(name="Bromine", symbol="Br", z=35., a);
  
  a = 32.1*g/mole;
  G4Element* elS  = new G4Element(name="Sulphur", symbol="S", z=16., a);
  
  a = 16.00*g/mole;
  G4Element* elO  = new G4Element(name="Oxygen", symbol="O", z=8., a);

  a = 14.01*g/mole;
  G4Element* elN  = new G4Element(name="Nitrogen", symbol="N", z= 7., a);
  
  a = 12.00*g/mole;
  G4Element* elC  = new G4Element(name="Carbon", symbol="C", z= 6., a);

  a = 1.01*g/mole;
  G4Element* elH  = new G4Element(name="Hydrogen",symbol="H" , z= 1., a);

  //
  // NIT EMULSION MATERIAL
  //
  
  density = 3.43*g/cm3; // NIT Emulsion
  G4Material* Emulsion = new G4Material(name="Emulsion", density, ncomponents=8);

  //
  // Fraction Mass NIT
  //
  
  Emulsion->AddElement(elAg,fractionmass=0.44065);
  Emulsion->AddElement(elBr,fractionmass=0.32190);
  Emulsion->AddElement(elI, fractionmass=0.01875);
  Emulsion->AddElement(elC, fractionmass=0.1012);
  Emulsion->AddElement(elO, fractionmass=0.0741);
  Emulsion->AddElement(elN, fractionmass=0.0268);
  Emulsion->AddElement(elH, fractionmass=0.0163);
  Emulsion->AddElement(elS, fractionmass=0.0003);

  //// OTHER MATERIAL
  a = 39.1*g/mole;
  G4Element* elK  = new G4Element(name="Potassium", symbol="K", z=19., a);

  /// POTASSIUM BROMIDE
  G4double density_KBr = 2.75*g/cm3; // NIT Emulsion
  G4Material* KBr = new G4Material(name="KBr", density_KBr, ncomponents=2);
  KBr->AddElement(elK,fractionmass=0.32855);
  KBr->AddElement(elBr,fractionmass=0.67145);
  
  //
  // World Material
  //
  
  new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
		 kStateGas, 2.73*kelvin, 3.e-18*pascal);
 

  //PMMA C5H8O2 ( Acrylic )
  // -------------
  G4double ACRdensity = 1.19*g/cm3;
  G4Material* Acrylic = new G4Material(name="Acrylic", ACRdensity, base_ncomponents=3);
  Acrylic->AddElement(elC, 5);
  Acrylic->AddElement(elH, 8);
  Acrylic->AddElement(elO, 2);
  

  G4Material* Polystyrene = new G4Material("Polystyrene", density= 1.050*g/cm3, ncomponents=2);
  Polystyrene->AddElement(elC, natoms=8); 
  Polystyrene->AddElement(elH, natoms=8);

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4VPhysicalVolume* ExN04DetectorConstruction::Construct()
{

  ///// Physical Parameters /////

  //
  // Get materials
  //
  G4Material* KBrMaterial = G4Material::GetMaterial("KBr");            
  G4Material* defaultMaterial = G4Material::GetMaterial("Galactic");
  G4Material* airMaterial = G4Material::GetMaterial("G4_AIR");           
  G4Material* emulsionMaterial = G4Material::GetMaterial("Emulsion");            
  //G4Material* baseMaterial = G4Material::GetMaterial("G4_POLYSTYRENE");
  G4Material* baseMaterial = G4Material::GetMaterial("Acrylic");
  //G4Material* plateMaterial = G4Material::GetMaterial("G4_WATER");
  G4Material* polyMaterial = G4Material::GetMaterial("G4_POLYETHYLENE");
  G4Material* leadMaterial = G4Material::GetMaterial("G4_Pb");
  G4Material* supportMaterial = G4Material::GetMaterial("G4_Fe");
  G4Material* CuMaterial = G4Material::GetMaterial("G4_Cu");
  G4Material* nitrogen_box_Material = G4Material::GetMaterial("G4_PLEXIGLASS");
  G4Material* waterMaterial = G4Material::GetMaterial("G4_WATER");
  

  if ( ! defaultMaterial ) {
    G4ExceptionDescription msg;
    msg << "Cannot retrieve materials already defined."; 
    G4Exception("B4DetectorConstruction::DefineVolumes()",
      "MyCode0001", FatalException, msg);
  }  

 
  /////  Geometrical Parameters /////

  //
  //Dimensioni del mondo
  //
  
  G4double worldSizeX = 20 *m;
  G4double worldSizeY = 20 *m;
  G4double worldSizeZ = 20 *m; 

  //
  // Detector
  //
  
  //G4double baseThickness  = 175*um; // PLASTIC
  G4double baseThickness  = 1*mm;  //PMMA  --- SLIDE GLASS
  G4double layerThickness = 50*um;
  G4double emuSizeX       = 36.0*cm; //7.5*cm;  
  G4double emuSizeY       = 30.0*cm; //2.5*cm;
  G4int nFilm             = 1;//270;//45;//150;   //envir //cosmog
  G4double filmThickness   = baseThickness+layerThickness*2; //*2 se double coated
  G4double detThickness   = filmThickness*nFilm;



  
  //     
  // World
  //
  
  G4VSolid* worldS 
    = new G4Box("World", worldSizeX/2, worldSizeY/2, worldSizeZ/2);                      
  G4LogicalVolume* worldLV
    = new G4LogicalVolume(worldS, defaultMaterial,"World");
                                   
  G4VPhysicalVolume* worldPV
    = new G4PVPlacement(0, G4ThreeVector(),worldLV,                         
                 "World", 0, false, 0, fCheckOverlaps); 
  
  //                               
  // Emulsion Detector
  //
  
  G4VSolid* detectorS 
    = new G4Box("Detector", emuSizeX/2, emuSizeY/2, detThickness/2);
                         
  G4LogicalVolume* detectorLV
    = new G4LogicalVolume(detectorS, defaultMaterial, "Detector"); 
                                   
  fDetectorPV
    = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), 
			detectorLV, "Detector", worldLV,  
			false, 0, fCheckOverlaps); 
  //                               
  // Emulsion Film
  //
  
  G4VSolid* filmS 
    = new G4Box("Film", emuSizeX/2, emuSizeY/2, filmThickness/2);
  
  G4LogicalVolume* filmLV
    = new G4LogicalVolume(filmS,defaultMaterial, "Film");
  
  new G4PVReplica("Film", filmLV, detectorLV,
		  kZAxis, nFilm, filmThickness);

  //                               
  // Layers
  //
 
   G4VSolid* emulsionS 
    = new G4Box("Emulsion", emuSizeX/2, emuSizeY/2, layerThickness/2);
                         
  G4LogicalVolume* emulsionLV
    = new G4LogicalVolume(emulsionS, emulsionMaterial, "Emulsion"); 
  
  fEmulsionTopPV 
    = new G4PVPlacement(0, G4ThreeVector(0., 0.,filmThickness/2 - layerThickness/2),       
			emulsionLV, "TopEmulsion", filmLV,
			false, 0, fCheckOverlaps);

  fEmulsionBotPV 
    = new G4PVPlacement(0, G4ThreeVector(0., 0.,-filmThickness/2 + layerThickness/2),       
			emulsionLV, "BotEmulsion", filmLV,
			false, 0, fCheckOverlaps);
  
  //
  // Plastic base
  //
 
  G4VSolid* baseS 
    = new G4Box("Base", emuSizeX/2, emuSizeY/2, baseThickness/2);
  
  G4LogicalVolume* baseLV
    = new G4LogicalVolume(baseS, baseMaterial, "Base"); 
  
  fBasePV
    = new G4PVPlacement(0, G4ThreeVector(0., 0.,filmThickness/2 - layerThickness - baseThickness/2), 
			baseLV, "Base", filmLV,false, 0, fCheckOverlaps);


  /*

  //
  // Shield dimension
  //

  ///// Poly Cu Pb ////////////////
  G4double innerRadius   = 50*cm;  
  G4double outerRadius   = 0*cm;
  G4int nRegion = 2;
  G4VPhysicalVolume* fHallPV[nRegion];
  /////////////////////////////


  //
  // Shield
  //
  
  G4VSolid* hallS[nRegion];
  G4LogicalVolume* hallLV[nRegion];

  for(G4int i=0; i<nRegion;i++){

    G4String annulus_index = "Annulus_"+G4UIcommand::ConvertToString(i);
    if(i!=0)innerRadius = outerRadius+1*um;
    if(i==0)outerRadius = innerRadius+1*um;
    if(i==1)outerRadius = innerRadius+100*cm;
    //if(i==1)outerRadius = innerRadius+20*cm;

    
    hallS[i] = new G4Sphere(annulus_index,   // Name
				      innerRadius,    // Inner radius
				      outerRadius,    // Outer radius
				      0.*deg,         // Starting phi
				      360.*deg,       // Delta phi
				      0.*deg,         // Starting theta
				      180.*deg);      // Delta theta

    if(i==0){
    hallLV[i]
      = new G4LogicalVolume(hallS[i], defaultMaterial, annulus_index);
    }

    if(i==1){
    hallLV[i]
      = new G4LogicalVolume(hallS[i], defaultMaterial, annulus_index);
    }
    
    fHallPV[i]
      = new G4PVPlacement(0, G4ThreeVector(0., 0.,0.),
			  hallLV[i],annulus_index, worldLV,  
			  false, 0, fCheckOverlaps); 

			  G4cout << i << " " << innerRadius << " " << outerRadius << " " << hallLV[i]->GetMaterial() << G4endl;

  }*/

  

  
   ///// Draw Experimental Setup /////
  
   //                                        
   // Visualization attributes
   //
   
   worldLV->SetVisAttributes (G4VisAttributes::Invisible);
   
   G4VisAttributes* emulsionVisAtt= new G4VisAttributes();
   emulsionVisAtt->SetVisibility(true);
   emulsionVisAtt->SetColour(G4Colour::Yellow());
   emulsionVisAtt->SetForceSolid(true);
   emulsionLV->SetVisAttributes(emulsionVisAtt);
/*
   G4VisAttributes* FirstVisAtt= new G4VisAttributes();
   FirstVisAtt->SetVisibility(true);
   FirstVisAtt->SetColour(G4Colour::Red());
   FirstVisAtt->SetForceAuxEdgeVisible(true);
   hallLV[0]->SetVisAttributes(FirstVisAtt);

   G4VisAttributes* SecondVisAtt= new G4VisAttributes();
   SecondVisAtt->SetVisibility(true);
   SecondVisAtt->SetColour(G4Colour::Green());
   SecondVisAtt->SetForceAuxEdgeVisible(true);
   hallLV[1]->SetVisAttributes(SecondVisAtt);
*/ 
   
   G4VisAttributes* baseVisAtt= new G4VisAttributes();
   baseVisAtt->SetVisibility(true);
   baseVisAtt->SetColour(G4Colour::White());
   baseVisAtt->SetForceSolid(true);
   baseLV->SetVisAttributes(baseVisAtt);
   //KBrLV->SetVisAttributes(baseVisAtt);
   
   return worldPV;

  
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN04DetectorConstruction::PrintDetectorParameters()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
