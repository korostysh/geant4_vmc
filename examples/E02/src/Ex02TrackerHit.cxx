// $Id: Ex02TrackerHit.cxx,v 1.1.1.1 2002/06/16 15:57:36 hristov Exp $
//
// Geant4 ExampleN02 adapted to Virtual Monte Carlo 
//
// Id: Ex02TrackerHit.cc,v 1.7 2002/01/09 17:24:10 ranjard Exp 
// GEANT4 tag Name: geant4-04-00-patch-02 
//
//
// by Ivana Hrivnacova, 21.4.2002

#include <iostream>

#include "Ex02TrackerHit.h"

ClassImp(Ex02TrackerHit)

using namespace std;

//_____________________________________________________________________________
Ex02TrackerHit::Ex02TrackerHit() 
{}

//_____________________________________________________________________________
Ex02TrackerHit::~Ex02TrackerHit() 
{}

/*
//_____________________________________________________________________________
void Ex02TrackerHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(pos);
    circle.SetScreenSize(0.04);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}
*/

//_____________________________________________________________________________
void Ex02TrackerHit::Print(const Option_t* opt) const
{
  cout << "  trackID: " << fTrackID 
       << "  chamberNb: " << fChamberNb
       << "  energy deposit (keV): " << fEdep * 1.0e06
       << "  position (cm): (" 
       << fPos[0] << ", " << fPos[1] << ", " << fPos[2] << ")"
       << endl;
}
