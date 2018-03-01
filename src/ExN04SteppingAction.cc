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
/// \file eventgenerator/HepMC/HepMCEx01/src/ExN04SteppingAction.cc
/// \brief Implementation of the ExN04SteppingAction class
//
// $Id: ExN04SteppingAction.cc 77801 2013-11-28 13:33:20Z gcosmo $
//

#include "G4SteppingManager.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4TrackStatus.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "ExN04SteppingAction.hh"

#include "ExN04SteppingAction.hh"
#include "ExN04TrackingAction.hh"
#include "ExN04EventAction.hh"
#include "ExN04DetectorConstruction.hh"
#include "ExN04Analysis.hh"
#include "ExN04AnalysisManager.hh"
#include "ExN04PrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4ThreeVector.hh" 
#include "G4VProcess.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4TouchableHandle.hh"
#include <math.h>
#include "G4VParticleChange.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ExN04SteppingAction::ExN04SteppingAction(const ExN04DetectorConstruction* detectorConstruction, ExN04EventAction* eventAction, ExN04RunAction* runAction, ExN04PrimaryGeneratorAction* primarygeneratorAction)
    : G4UserSteppingAction(),
    fDetConstruction(detectorConstruction),
    fEventAction(eventAction),
    fRunAction(runAction),
    fGenAction(primarygeneratorAction)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ExN04SteppingAction::~ExN04SteppingAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void ExN04SteppingAction::UserSteppingAction(const G4Step * step)
{
  /*
  G4Track* theTrack = theStep->GetTrack();

  // check if it is alive
  if(theTrack->GetTrackStatus()!=fAlive) { return; }

  // check if it is primary
  if(theTrack->GetParentID()!=0) { return; }

  // check if it is NOT muon
  G4ParticleDefinition * particleType = theTrack->GetDefinition();
  if((particleType==G4MuonPlus::MuonPlusDefinition())
   ||(particleType==G4MuonMinus::MuonMinusDefinition()))
  { return; }

  // check if it is entering to the calorimeter volume
  G4StepPoint * thePrePoint = theStep->GetPreStepPoint();
  G4VPhysicalVolume * thePrePV = thePrePoint->GetPhysicalVolume();
  G4String thePrePVname = thePrePV->GetName();
  if(thePrePVname(0,4)=="calo") { return; }
  G4StepPoint * thePostPoint = theStep->GetPostStepPoint();
  G4VPhysicalVolume * thePostPV = thePostPoint->GetPhysicalVolume();
  G4String thePostPVname = thePostPV->GetName();
  if(thePostPVname(0,4)!="calo") { return; }

  // then suspend the track
  theTrack->SetTrackStatus(fSuspend);
  */

  //------------VARIABLES ------------------------------------// 
  //G4String volume_name = volume->GetCurrentLV();
  G4Track *track = step->GetTrack();
  G4String name = track->GetDefinition()->GetParticleName();
  G4double tracklength= track->GetTrackLength() / (nm);
  G4double steplength= step->GetStepLength()/(nm);
  //G4String volume_name = volume->GetCurrentLV();
  /// Definizioni
  //G4double trackangle=0.;
  //G4int charge = track->GetDefinition()->GetPDGCharge();
  G4int pdgcode = track->GetDefinition()->GetPDGEncoding();
  G4StepPoint* prePoint      = step->GetPreStepPoint();
  G4StepPoint* postPoint     = step->GetPostStepPoint();
  G4ThreeVector prePointPos  = prePoint->GetPosition() / (um); 
  G4ThreeVector postPointPos = postPoint->GetPosition()/ (um);
  G4double kinene = prePoint->GetKineticEnergy() / (keV);
  G4double edep = step->GetTotalEnergyDeposit() / (keV); 
  G4ThreeVector momvect = prePoint->GetMomentum() / (keV);
  const G4VProcess *proc = postPoint->GetProcessDefinedStep();
  G4String volume_name = prePoint->GetPhysicalVolume()->GetName();
  G4int parentID = track->GetParentID();
  G4int trackID  = track->GetTrackID();
  G4int StepNo = step->GetTrack()->GetCurrentStepNumber();
  G4int whichInter=0;
  G4int whichVol=0;
  G4int copyNo=-1;
  G4int creatorID=-1;
  //------------- PHYSICAL PROCESSES-----------------------------//
  G4String Transportation = "Transportation";
  G4String Scintillation = "Scintillation";
  G4String inelastic = "inelastic";
  G4String hadElastic = "hadElastic";
  G4String nCapture = "nCapture";
  G4String hBertiniCaptureAtRest = "hBertiniCaptureAtRest";
  G4String msc = "msc";
  G4String eIoni = "eIoni";
  G4String eBrem = "eBrem";
  G4String phot = "phot";
  G4String Rayl = "Rayl";
  G4String compt = "compt";
  G4String hIoni = "hIoni";
  G4String ionIoni = "ionIoni";
  G4String neutronInelastic = "neutronInelastic";
  G4String RadioactiveDecay = "RadioactiveDecay";
  G4String Decay = "Decay";
  G4String protonInelastic = "protonInelastic";
  G4String pimenoInelastic = "pi-Inelastic";
  G4String pipiuInelastic = "pi+Inelastic";
  G4String conv = "conv";
  G4String CoulombScat = "CoulombScat";
  G4String dInelastic = "dInelastic";
  G4String tInelastic = "tInelastic";
  G4String He3Inelastic = "He3Inelastic";
  G4String alphaInelastic = "alphaInelastic";
  G4String kaon0LInelastic = "kaon0LInelastic";
  G4String creator = "null";
  if(track->GetCreatorProcess() != 0) creator = track->GetCreatorProcess()->GetProcessName();
  //-----------------------------------------------------------------------------------------//
  //--------------EVENT NUMBER----------------------------// 
  /////   Numero evento  //////////////////////
  G4int eID=0;
  const G4Event* evt = G4RunManager::GetRunManager()->GetCurrentEvent();
  if(evt) eID = evt->GetEventID();
  //G4cout << "Vale" << eID << G4endl;
  //-------------------------------------------------------------------//

  //-------- PROCESS INDEX-------------------------------------------------------//
  ////////////////////////////////////////
  if(track->GetCreatorProcess() != 0){
  if(track->GetCreatorProcess()->GetProcessName()==Transportation) creatorID = -1;
  if(track->GetCreatorProcess()->GetProcessName()==Scintillation) creatorID = 1;
  if(track->GetCreatorProcess()->GetProcessName()==msc) creatorID = 2;
  if(track->GetCreatorProcess()->GetProcessName()==eIoni) creatorID = 3;
  if(track->GetCreatorProcess()->GetProcessName()==eBrem) creatorID = 4;
  if(track->GetCreatorProcess()->GetProcessName()==phot) creatorID = 5;
  if(track->GetCreatorProcess()->GetProcessName()==Rayl) creatorID = 6;
  if(track->GetCreatorProcess()->GetProcessName()==compt) creatorID = 7;
  if(track->GetCreatorProcess()->GetProcessName()==hIoni) creatorID = 8;
  if(track->GetCreatorProcess()->GetProcessName()==ionIoni) creatorID = 9;
  if(track->GetCreatorProcess()->GetProcessName()==neutronInelastic) creatorID = 10;
  if(track->GetCreatorProcess()->GetProcessName()==protonInelastic) creatorID = 11;
  if(track->GetCreatorProcess()->GetProcessName()==RadioactiveDecay) creatorID = 12;
  if(track->GetCreatorProcess()->GetProcessName()==Decay) creatorID = 13;
  if(track->GetCreatorProcess()->GetProcessName()==hadElastic) creatorID = 14;
  if(track->GetCreatorProcess()->GetProcessName()==nCapture) creatorID = 15;
  if(track->GetCreatorProcess()->GetProcessName()==hBertiniCaptureAtRest) creatorID = 16;
  if(track->GetCreatorProcess()->GetProcessName()==pimenoInelastic) creatorID = 17;
  if(track->GetCreatorProcess()->GetProcessName()==pipiuInelastic) creatorID = 18;
  if(track->GetCreatorProcess()->GetProcessName()==conv) creatorID = 19;
  if(track->GetCreatorProcess()->GetProcessName()==CoulombScat) creatorID = 20;
  if(track->GetCreatorProcess()->GetProcessName()==dInelastic) creatorID = 21;
  if(track->GetCreatorProcess()->GetProcessName()==tInelastic) creatorID = 22;
  if(track->GetCreatorProcess()->GetProcessName()==He3Inelastic) creatorID = 23;
  if(track->GetCreatorProcess()->GetProcessName()==alphaInelastic) creatorID = 24;
  if(track->GetCreatorProcess()->GetProcessName()==kaon0LInelastic) creatorID = 25;
}

  if(proc->GetProcessName()==Transportation) whichInter = -1;
  if(proc->GetProcessName()==Scintillation) whichInter = 1;
  if(proc->GetProcessName()==msc) whichInter = 2;
  if(proc->GetProcessName()==eIoni) whichInter = 3;
  if(proc->GetProcessName()==eBrem) whichInter = 4;
  if(proc->GetProcessName()==phot) whichInter = 5;
  if(proc->GetProcessName()==Rayl) whichInter = 6;
  if(proc->GetProcessName()==compt) whichInter = 7;
  if(proc->GetProcessName()==hIoni) whichInter = 8;
  if(proc->GetProcessName()==ionIoni) whichInter = 9;
  if(proc->GetProcessName()==neutronInelastic) whichInter = 10;
  if(proc->GetProcessName()==protonInelastic) whichInter = 11;
  if(proc->GetProcessName()==RadioactiveDecay) whichInter = 12;
  if(proc->GetProcessName()==Decay) whichInter = 13;
  if(proc->GetProcessName()==hadElastic) whichInter = 14;
  if(proc->GetProcessName()==nCapture) whichInter = 15;
  if(proc->GetProcessName()==hBertiniCaptureAtRest) whichInter = 16;
  if(proc->GetProcessName()==pimenoInelastic) whichInter = 17;
  if(proc->GetProcessName()==pipiuInelastic) whichInter = 18;
  if(proc->GetProcessName()==conv) whichInter = 19;
  if(proc->GetProcessName()==CoulombScat) whichInter = 20;
  if(proc->GetProcessName()==dInelastic) whichInter = 21;
  if(proc->GetProcessName()==tInelastic) whichInter = 22;
  if(proc->GetProcessName()==He3Inelastic) whichInter = 23;
  if(proc->GetProcessName()==alphaInelastic) whichInter = 24;
  if(proc->GetProcessName()==kaon0LInelastic) whichInter = 25;
  //--------------------------------------------------------------------//
  //----------VOLUME INDEX----------------------------------------------//   
  if(whichVol!=0)G4String volume_name_post = postPoint->GetPhysicalVolume()->GetName();

  if(volume_name=="TopEmulsion") whichVol=1;
  if(volume_name=="BottomEmulsion")  whichVol=2;
  //if(volume_name=="TopEmulsion2") whichVol=1;
  //if(volume_name=="BottomEmulsion2")  whichVol=2;
  if(volume_name=="Base") whichVol=3;
  if(volume_name=="Annulus_0") whichVol=4;
  if(volume_name=="Annulus_1") whichVol=5;
  //-------------------------------------------------------------------------------------//
  //-----------COPY NUMBER---------------------------------------------------------------//
  if(whichVol==1 || whichVol==2)copyNo = prePoint->GetTouchableHandle()->GetCopyNumber(1);
  //-------------------------------------------------------------------------------------//
                                            
  //-----MC BEAM-----------------//
  if(parentID==0 && StepNo==1) {
    fRunAction->ClearVectors();
    fRunAction->EventInfoMC(pdgcode,creatorID,whichInter,kinene,StepNo,trackID,parentID,whichVol,&momvect);
    //G4cout << eID << G4endl;
  }
  //------------------------------------------------------------------------------------------------------------//
  //------------ALL DAUGHTERS (e-,e+,p,N)-----------------------// FILLING NTUPLES
  if(whichVol==1 || whichVol==2 /*|| ((whichVol==4 || whichVol==5) && pdgcode==2112)*/){
    if (kinene!=0 && (pdgcode==11 || pdgcode==-11 || pdgcode==2212 || pdgcode>=1000000000 || pdgcode==0 /*|| pdgcode==22*/ || pdgcode==2112)){ 
      fRunAction->EventInfoRecoilLast(creatorID,whichInter,kinene,StepNo,trackID,parentID,&prePointPos,&postPointPos,&momvect,tracklength,pdgcode,whichVol,edep,copyNo,steplength);
    }
  }
  //--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
  //-------------------PRINT DATA----------------------------------------------------------------------------------------------------------------//
  if(((whichVol==1 || whichVol==2) && (pdgcode==11 || pdgcode==-11 || pdgcode==2212 || pdgcode>=1000000000 || pdgcode==0 /*|| pdgcode==22*/)) /* || ((whichVol==4 || whichVol==5) && pdgcode==2112)*/){
    G4cout << eID << " " << parentID << " " << trackID << " " << StepNo << " " <<  name << " " << creator << " " <<  proc->GetProcessName() << " " << whichInter << " " << kinene << " " << edep << " " << steplength << " "  << " " << tracklength << " " << prePointPos[0] << " " << prePointPos[1] << " " << prePointPos[2] <<  " " << postPointPos[0] << " "
	   << postPointPos[1] << " " << postPointPos[2] << " " << whichVol << " " << copyNo <<  " " << momvect[0] << " " << momvect[1] << " " << momvect[2] << " " << volume_name << G4endl;    
  }
  //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
}
