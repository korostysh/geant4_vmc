// $Id: Ex02RootManager.h,v 1.1 2002/06/20 11:52:35 hristov Exp $
//
// Geant4 novice ExampleN02 adapted to Virtual Monte Carlo 
//
// Class Ex02RootManager
// ---------------------
// Class that takes care of Root IO.
//
// by Ivana Hrivnacova, 5.4.2002


#ifndef EX02_ROOT_MANAGER_H
#define EX02_ROOT_MANAGER_H

#include <TObject.h>
#include <TTree.h>
#include <TFile.h>

class TParticle;

enum FileMode { kRead, kWrite};

class Ex02RootManager : public TObject
{
  public:
    Ex02RootManager(FileMode fileMode);
    Ex02RootManager();
    virtual ~Ex02RootManager();     
  
    // static access method
    static Ex02RootManager* Instance(); 

    // methods
    void  Register(const char* name, void* clonesAddress);
    void  Register(const char* name, const char* className, void* objAddress);
    void  Fill();
    void  Write();
    void  ReadEvent(Int_t i);
    
  private:
    // data members
    static  Ex02RootManager* fgInstance; //Singleton instance

    // data members
    TFile*  fFile;
    TTree*  fTree;
    
    ClassDef(Ex02RootManager,0) // Root IO manager
};

#endif //EX02_ROOT_MANAGER_H   
   
