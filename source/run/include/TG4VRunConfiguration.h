// $Id: TG4VRunConfiguration.h,v 1.1 2002/06/20 11:58:25 hristov Exp $
// Category: run
//
// Author: I. Hrivnacova
//
// Class TG4VRunConfiguration
// --------------------------
// Abstract class that takes care of creating  all user defined classes 
// that will be initialized and managed by Geant4 kernel (G4RunManager).
// It has one pure virtual method CreateUserConfiguration()
// that has to be be implemented by a derived class.

#ifndef TG4V_RUN_CONFIGURATION_H
#define TG4V_RUN_CONFIGURATION_H

class TG4TrackingAction;
class TG4SteppingAction;
class TG4SDConstruction;
class TG4ModularPhysicsList;

class G4VUserDetectorConstruction;
class G4VUserPrimaryGeneratorAction;
class G4UserRunAction;
class G4UserEventAction;
class G4UserStackingAction;
class G4RunManager;

class TG4VRunConfiguration
{
  public:
    TG4VRunConfiguration();
    // --> protected
    // TG4VRunConfiguration(const TG4VRunConfiguration& right);
    virtual ~TG4VRunConfiguration();

    // methods
    void ConfigureRunManager(G4RunManager* runManager);

    // get methods
    TG4ModularPhysicsList* GetPhysicsList() const;
    TG4SDConstruction* GetSDConstruction() const;

  protected:
    TG4VRunConfiguration(const TG4VRunConfiguration& right);

    // operators
    TG4VRunConfiguration& operator=(const TG4VRunConfiguration& right);

    // methods
    virtual void CreateUserConfiguration() = 0;

    // data members
    G4VUserDetectorConstruction*    fDetectorConstruction; //det construction
    TG4SDConstruction*              fSDConstruction;       //sensitive detectors 
                                                           //construction
    TG4ModularPhysicsList*          fPhysicsList;          //physics list
    G4VUserPrimaryGeneratorAction*  fPrimaryGenerator;     //primary generator
    G4UserRunAction*                fRunAction;            //run action
    G4UserEventAction*              fEventAction;          //event action
    TG4TrackingAction*              fTrackingAction;       //tracking action
    TG4SteppingAction*              fSteppingAction;       //stepping action
    G4UserStackingAction*           fStackingAction;       //stacking action
};

#endif //TG4V_RUN_CONFIGURATION_H
