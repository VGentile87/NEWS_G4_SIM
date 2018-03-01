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
/// \file eventgenerator/HepMC/HepMCEx01/src/ExN04RunAction.cc
/// \brief Implementation of the ExN04RunAction class
//
// $Id: ExN04RunAction.cc 77801 2013-11-28 13:33:20Z gcosmo $
//

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "ExN04RunAction.hh"
#include "ExN04Analysis.hh"
#include "G4Run.hh"
#include "ExN04EventAction.hh"
#include "G4UnitsTable.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ExN04RunAction::ExN04RunAction()
   : G4UserRunAction()
{
  // set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(0);       // MALEDETTO

  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in B4Analysis.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  // Create directories 
  //analysisManager->SetHistoDirectoryName("histograms");
  //analysisManager->SetNtupleDirectoryName("ntuple");
  analysisManager->SetVerboseLevel(0);
  analysisManager->SetFirstHistoId(1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ExN04RunAction::~ExN04RunAction()
{
  delete G4AnalysisManager::Instance(); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void ExN04RunAction::BeginOfRunAction(const G4Run* /*aRun*/)
{
  //-----------DYNAMIC SEED FOR EACH RUN--------------------------//
  // aggiunto io
  long seeds[2];
  time_t systime = time(NULL);
  //seeds[0] = (long) systime;
  //seeds[1] = (long) (systime*G4UniformRand());
  seeds[0] = 0;  // settare per controlli tra pacchetti
  seeds[1] = 1;
  G4Random::setTheSeeds(seeds);  
  //inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);
  
  // Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  // Open an output file
  //
  G4String fileName = "Root_data_G4_sim";
  
  analysisManager->OpenFile(fileName);
  analysisManager->SetFirstNtupleId(1);

  //
  // Creating ntuple
  //

  //ClearVectors();
 
  analysisManager->CreateNtuple("tree1", "Emu_Info");
  analysisManager->CreateNtupleIColumn("Event");
  //analysisManager->CreateNtupleIColumn("Nneu");
  //analysisManager->CreateNtupleIColumn("Nrec");
  //analysisManager->CreateNtupleDColumn("Nrec2");
  analysisManager->CreateNtupleIColumn("vMC_TrackId",vMC_TrackId);
  analysisManager->CreateNtupleIColumn("vMC_StepId",vMC_StepId);
  analysisManager->CreateNtupleIColumn("vMC_PartId",vMC_PartId);
  analysisManager->CreateNtupleIColumn("vMC_ParentId",vMC_ParentId);
  analysisManager->CreateNtupleIColumn("vMC_CreatorId",vMC_CreatorId);
  analysisManager->CreateNtupleIColumn("vMC_InteractionId",vMC_InteractionId);
  analysisManager->CreateNtupleIColumn("vMC_VolumeId",vMC_VolumeId);
  analysisManager->CreateNtupleDColumn("vMC_EnergyKin",vMC_EnergyKin);
  analysisManager->CreateNtupleDColumn("vMC_PX",vMC_PX);
  analysisManager->CreateNtupleDColumn("vMC_PY",vMC_PY);
  analysisManager->CreateNtupleDColumn("vMC_PZ",vMC_PZ);
  /*
  analysisManager->CreateNtupleIColumn("event_id");
  analysisManager->CreateNtupleIColumn("Nneu");
  analysisManager->CreateNtupleIColumn("Nrec");
  analysisManager->CreateNtupleDColumn("Nrec2");
  analysisManager->CreateNtupleIColumn("vPartName",vPartName);
  analysisManager->CreateNtupleIColumn("vCreator",vCreator);
  analysisManager->CreateNtupleIColumn("vInteraction",vInteraction);
  analysisManager->CreateNtupleDColumn("vEnergyKin",vEnergyKin);
  analysisManager->CreateNtupleIColumn("vStep",vStep);
  analysisManager->CreateNtupleIColumn("vTrackId",vTrackId);
  analysisManager->CreateNtupleIColumn("vVolume",vVolume);
  analysisManager->CreateNtupleIColumn("vParentId",vParentId);
  analysisManager->CreateNtupleDColumn("vMC_PX",vMC_PX);
  analysisManager->CreateNtupleDColumn("vMC_PY",vMC_PY);
  analysisManager->CreateNtupleDColumn("vMC_PZ",vMC_PZ);

  analysisManager->CreateNtupleIColumn("vCreatorFirst",vCreatorFirst);
  analysisManager->CreateNtupleIColumn("vInteractionFirst",vInteractionFirst);
  analysisManager->CreateNtupleDColumn("vEnergyKinFirst",vEnergyKinFirst);
  analysisManager->CreateNtupleDColumn("vEnergyDepFirst",vEnergyDepFirst);
  analysisManager->CreateNtupleIColumn("vStepFirst",vStepFirst);
  analysisManager->CreateNtupleIColumn("vTrackIdFirst",vTrackIdFirst);
  analysisManager->CreateNtupleIColumn("vParentIdFirst",vParentIdFirst);
  analysisManager->CreateNtupleDColumn("vFirstHitX",vFirstHitX);
  analysisManager->CreateNtupleDColumn("vFirstHitY",vFirstHitY);
  analysisManager->CreateNtupleDColumn("vFirstHitZ",vFirstHitZ);
  analysisManager->CreateNtupleDColumn("vFirstHitPX",vFirstHitPX);
  analysisManager->CreateNtupleDColumn("vFirstHitPY",vFirstHitPY);
  analysisManager->CreateNtupleDColumn("vFirstHitPZ",vFirstHitPZ);
  analysisManager->CreateNtupleDColumn("vTrackLengthFirst",vTrackLengthFirst);
  analysisManager->CreateNtupleIColumn("vPartNameFirst",vPartNameFirst);
  analysisManager->CreateNtupleIColumn("vVolumeFirst",vVolumeFirst);
  */
  analysisManager->CreateNtupleIColumn("vTrackId",vTrackId);
  analysisManager->CreateNtupleIColumn("vStepId",vStepId);
  analysisManager->CreateNtupleIColumn("vPartId",vPartId);
  analysisManager->CreateNtupleIColumn("vParentId",vParentId);
  analysisManager->CreateNtupleIColumn("vCreatorId",vCreatorId);
  analysisManager->CreateNtupleIColumn("vInteractionId",vInteractionId);
  analysisManager->CreateNtupleIColumn("vVolumeId",vVolumeId);
  analysisManager->CreateNtupleIColumn("vCopyNo",vCopyNo);
  analysisManager->CreateNtupleDColumn("vEnergyKin",vEnergyKin);
  analysisManager->CreateNtupleDColumn("vEnergyDep",vEnergyDep);
  analysisManager->CreateNtupleDColumn("vPreHitX",vPreHitX);
  analysisManager->CreateNtupleDColumn("vPreHitY",vPreHitY);
  analysisManager->CreateNtupleDColumn("vPreHitZ",vPreHitZ);
  analysisManager->CreateNtupleDColumn("vPostHitX",vPostHitX);
  analysisManager->CreateNtupleDColumn("vPostHitY",vPostHitY);
  analysisManager->CreateNtupleDColumn("vPostHitZ",vPostHitZ);
  analysisManager->CreateNtupleDColumn("vHitPX",vHitPX);
  analysisManager->CreateNtupleDColumn("vHitPY",vHitPY);
  analysisManager->CreateNtupleDColumn("vHitPZ",vHitPZ);
  analysisManager->CreateNtupleDColumn("vTrackLength",vTrackLength);
  analysisManager->CreateNtupleDColumn("vStepLength",vStepLength);

  analysisManager->FinishNtuple(1);
  analysisManager->SetFirstNtupleId(2);
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN04RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  // print histogram statistics
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  //if ( analysisManager->GetH1(1) ) {
  //if ( analysisManager->GetH1(1) ) {
    //    G4cout << "\n ----> print histograms statistic ";
  // if(isMaster) {
      //G4cout << "for the entire run \n" << G4endl; 
  // }
  // else {
      //G4cout << "for the local thread \n" << G4endl; 
  // }

        
    //G4cout << "---> BRICK <--- " << G4endl;
   
    /*  G4cout << " EEmu : mean = " 
       << G4BestUnit(analysisManager->GetH1(1)->mean(), "Energy") 
       << " rms = " 
       << G4BestUnit(analysisManager->GetH1(1)->rms(),  "Energy") << G4endl;
    

      G4cout << " LEmu : mean = " 
      << G4BestUnit(analysisManager->GetH1(2)->mean(), "Length") 
      << " rms = " 
      << G4BestUnit(analysisManager->GetH1(2)->rms(),  "Length") << G4endl;
    */
    // }
    //}
    // }

  // save histograms & ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

