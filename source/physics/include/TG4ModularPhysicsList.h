// $Id: TG4ModularPhysicsList.h,v 1.1 2002/06/20 11:57:45 hristov Exp $
// Category: physics
//
// Author: I. Hrivnacova
//
// Class TG4ModularPhysicsList
// ---------------------------
// The modular physics list.
// The physics processes and particles have to be created
// using the G4VPhysicsCreator derived classes
// and registered to this physics list.

#ifndef TG4_MODULAR_PHYSICS_LIST_H
#define TG4_MODULAR_PHYSICS_LIST_H

#include "TG4Verbose.h"

#include <G4VModularPhysicsList.hh>
#include <globals.hh>

class TG4ModularPhysicsList: public G4VModularPhysicsList,
                             public TG4Verbose
{
  public:
    TG4ModularPhysicsList();
    // --> protected
    // TG4ModularPhysicsList(const TG4ModularPhysicsList& right);
    virtual ~TG4ModularPhysicsList();
  
    // methods
    virtual void SetCuts();
    virtual void VerboseLevel(G4int level);
    void SetRangeCut(G4double value);
    void SetProcessActivation();
    void PrintAllProcesses() const;
    void DumpAllProcesses() const;
    
  protected:
    TG4ModularPhysicsList(const TG4ModularPhysicsList& right);

    // operators
    TG4ModularPhysicsList& operator=(const TG4ModularPhysicsList& right);

    // methods
    virtual void ConstructParticle();
    virtual void ConstructProcess();

  private:
    // methods
    void SetProcessActivation(G4ProcessManager* processManager,
                              G4int processId, G4bool activation);

    // static data members
    static const G4double  fgkDefaultCutValue; //default cut value
};

#endif //TG4_MODULAR_PHYSICS_LIST_H
