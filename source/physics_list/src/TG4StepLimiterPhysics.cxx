// $Id: TG4StepLimiterPhysics.cxx,v 1.4 2007/05/31 10:24:33 brun Exp $

//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: vmc@pcroot.cern.ch
//-------------------------------------------------

// Category: physics_lists
// Class TG4StepLimiterPhysics
// ----------------------------
// See the class description in the header file.

#include "TG4StepLimiterPhysics.h"
#include "TG4ProcessControlMap.h"
#include "TG4ProcessMCMap.h"

#include <TMCProcess.h>

#include <G4ParticleDefinition.hh>
#include <G4ProcessManager.hh>
#include <G4StepLimiter.hh>

//_____________________________________________________________________________
TG4StepLimiterPhysics::TG4StepLimiterPhysics(const G4String& name)
  : TG4VPhysicsConstructor(name),
    fStepLimiterProcess(0) 
{
//
}

//_____________________________________________________________________________
TG4StepLimiterPhysics::TG4StepLimiterPhysics(G4int verboseLevel,
                                             const G4String& name)
  : TG4VPhysicsConstructor(name, verboseLevel), 
    fStepLimiterProcess(0) 
{
//
}

//_____________________________________________________________________________
TG4StepLimiterPhysics::~TG4StepLimiterPhysics() 
{
//
  delete fStepLimiterProcess;
}

//
// protected methods
//

//_____________________________________________________________________________
void TG4StepLimiterPhysics::ConstructParticle()
{
/// No particles instatiated 

}

//_____________________________________________________________________________
void TG4StepLimiterPhysics::ConstructProcess()
{
/// Set step limiter process to all particles

  fStepLimiterProcess = new G4StepLimiter();

  theParticleIterator->reset();
  while( (*theParticleIterator)() ){

    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();

    pmanager ->AddProcess(fStepLimiterProcess, -1, -1, 6);
  }
  
  if (VerboseLevel() > 0) {
    G4cout << "### Step limiter physics constructed." << G4endl;
  }  
}