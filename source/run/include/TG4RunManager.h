// $Id: TG4RunManager.h,v 1.1 2002/06/20 11:58:25 hristov Exp $
// Category: run
//
// Author: I. Hrivnacova
//
// Class TG4RunManager
// -------------------
// Geant4 implementation of the MonteCarlo interface methods                    
// for access to Geant4 at run level.
// It provides also methods for switching between Geant4 and
// Root UIs.

#ifndef TG4_RUN_MANAGER_H
#define TG4_RUN_MANAGER_H

#include "TG4Verbose.h"
#include "TG4RunMessenger.h"

#include <globals.hh>

#include <Rtypes.h>

class TG4VRunConfiguration;

class G4RunManager;
class G4UIsession;

class TApplication;

class TG4RunManager : public TG4Verbose
{
  public:
    TG4RunManager(TG4VRunConfiguration* configuration, int argc, char** argv);
    TG4RunManager(TG4VRunConfiguration* configuration);
    // --> protected
    // TG4RunManager();
    // TG4RunManager(const TG4RunManager& right);
    virtual ~TG4RunManager();

    // static access method
    static TG4RunManager* Instance();

    // methods
    void Initialize();
    void LateInitialize();
    void ProcessEvent();
    void ProcessRun(G4int nofEvents);

    // get methods
    Int_t CurrentEvent() const;

    //
    // methods for Geant4 only 
    //
    void StartGeantUI();
    void StartRootUI();
    void ProcessGeantMacro(G4String macroName);
    void ProcessRootMacro(G4String macroName);
    void ProcessGeantCommand(G4String command);
    void ProcessRootCommand(G4String command);
    void UseG3Defaults();      


  protected:
    TG4RunManager();
    TG4RunManager(const TG4RunManager& right);

    // operators
    TG4RunManager& operator=(const TG4RunManager& right);
   
    // data members    

  private:
    // methods
    void CreateGeantUI();
    void CreateRootUI();
    void FilterARGV(const G4String& option);
    Text_t* G4StringToTextT(G4String string) const;
    
    // static data members
    static TG4RunManager*  fgInstance; //this instance
    
    // data members    
    G4RunManager*         fRunManager;       //G4RunManager
    TG4RunMessenger       fMessenger;        //messenger
    TG4VRunConfiguration* fRunConfiguration; //TG4VRunConfiguration
    G4UIsession*          fGeantUISession;   //G4 UI 
    TApplication*         fRootUISession;    //Root UI 
    G4bool                fRootUIOwner;      //ownership of Root UI
    G4int                 fARGC;             //argc 
    char**                fARGV;             //argv
};

// inline methods
inline TG4RunManager* TG4RunManager::Instance() 
{ return fgInstance; }

#endif //TG4_RUN_MANAGER_H
