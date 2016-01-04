//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007 - 2015 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file  Garfield/geant4/src/GarfieldG4FastSimulationModel.cxx
/// \brief Implementation of the GarfieldG4FastSimulationModel class 
///
/// Garfield garfieldpp example adapted to Virtual Monte Carlo.
/// This class is imported from garfieldpp example.
/// There is disabled WriteGeometryToGDML function in order to avoid
/// requiring Geant4 optional library.
///
/// \date 28/10/2015
/// \author D. Pheiffer, CERN

/*
 * GarfieldModel.cpp
 *
 *  Created on: Apr 9, 2014
 *      Author: dpfeiffe
 */
#include <iostream>
#include "GarfieldG4FastSimulationModel.h"
#include "G4VPhysicalVolume.hh"
#include "G4Electron.hh"
#include "G4Gamma.hh"

#include "G4SystemOfUnits.hh"

// I.H. make this optional
// #include "G4GDMLParser.hh"

GarfieldG4FastSimulationModel::GarfieldG4FastSimulationModel(G4String modelName,
		G4Region* envelope) :
		G4VFastSimulationModel(modelName, envelope) {
	fGarfieldPhysics = GarfieldPhysics::GetInstance();
	fGarfieldPhysics->InitializePhysics();

}

GarfieldG4FastSimulationModel::GarfieldG4FastSimulationModel(G4String modelName) :
		G4VFastSimulationModel(modelName) {
	// I.H.
	fGarfieldPhysics = GarfieldPhysics::GetInstance();
	fGarfieldPhysics->InitializePhysics();
}

GarfieldG4FastSimulationModel::~GarfieldG4FastSimulationModel() {
}

// I.H. make this optional
// void GarfieldG4FastSimulationModel::WriteGeometryToGDML(
// 		G4VPhysicalVolume* physicalVolume) {

// 	G4GDMLParser* parser = new G4GDMLParser();
// 	remove("garfieldGeometry.gdml");
// 	parser->Write("garfieldGeometry.gdml", physicalVolume, false);
// 	delete parser;
// }

G4bool GarfieldG4FastSimulationModel::IsApplicable(
		const G4ParticleDefinition& particleType) {

	G4String particleName = particleType.GetParticleName();

	if (fGarfieldPhysics->FindParticleName(particleName)) {
		//G4cout << "\nGarfield model applicable for " << particleName << G4endl;
		return true;
	}
	return false;

}

G4bool GarfieldG4FastSimulationModel::ModelTrigger(
		const G4FastTrack& fastTrack) {
	double ekin_keV = fastTrack.GetPrimaryTrack()->GetKineticEnergy() / keV;
	G4String particleName =
			fastTrack.GetPrimaryTrack()->GetParticleDefinition()->GetParticleName();
	//if (fastTrack.GetPrimaryTrack()->GetParentID() != 0) {

	if (fGarfieldPhysics->FindParticleNameEnergy(particleName, ekin_keV)) {
		G4cout << "\nGarfield model triggered for " << particleName << " with "
				<< ekin_keV << " keV" << G4endl;
		return true;
	}
	return false;
	//} else {
	//	return false;
	//}

}

void GarfieldG4FastSimulationModel::DoIt(const G4FastTrack& fastTrack,
		G4FastStep& fastStep) {

	G4TouchableHandle theTouchable =
			fastTrack.GetPrimaryTrack()->GetTouchableHandle();
	G4String name = theTouchable->GetVolume()->GetName();

	G4ThreeVector pdirection = fastTrack.GetPrimaryTrack()->GetMomentum().unit();
	G4ThreeVector localdir = fastTrack.GetPrimaryTrackLocalDirection();

	G4ThreeVector worldPosition = fastTrack.GetPrimaryTrack()->GetPosition();
	G4ThreeVector localPosition = fastTrack.GetPrimaryTrackLocalPosition();

	double ekin_keV = fastTrack.GetPrimaryTrack()->GetKineticEnergy() / keV;
	G4double globalTime = fastTrack.GetPrimaryTrack()->GetGlobalTime();


	G4String particleName =
			fastTrack.GetPrimaryTrack()->GetParticleDefinition()->GetParticleName();

	fastStep.KillPrimaryTrack();

	if (particleName == "kaon+") {
		particleName = "K+";
	} else if (particleName == "kaon-") {
		particleName = "K-";
	} else if (particleName == "anti_proton") {
		particleName = "anti-proton";
	}


	fGarfieldPhysics->DoIt(particleName, ekin_keV, globalTime,
			localPosition.x() / CLHEP::cm, localPosition.y() / CLHEP::cm,
			localPosition.z() / CLHEP::cm, localdir.x(), localdir.y(),
			localdir.z());

	if (fGarfieldPhysics->GetCreateSecondariesInGeant4()) {
		std::vector<GarfieldElectron*>* secondaryElectrons =
				fGarfieldPhysics->GetSecondaryElectrons();

		if (secondaryElectrons->size() > 0) {
			fastStep.SetNumberOfSecondaryTracks(secondaryElectrons->size());

			G4double totalEnergySecondaries_MeV = 0;

			for (std::vector<GarfieldElectron*>::iterator it =
					secondaryElectrons->begin();
					it != secondaryElectrons->end(); ++it) {
				G4double x = (*it)->getX_mm();
				G4double y = (*it)->getY_mm();
				G4double z = (*it)->getZ_mm();
				G4double eKin_MeV = (*it)->getEkin_MeV();
				G4double dx = (*it)->getDX();
				G4double dy = (*it)->getDY();
				G4double dz = (*it)->getDZ();
				G4double time = (*it)->getTime();
				//std::cout << "Secondaries " << globalTime <<  " globalTime " << localTime << " localTime " << properTime << " properTime " << std::endl;
				//std::cout << x <<  " x " << y << " y " << z << " z " << std::endl;
				//std::cout << dx <<  " dx " << dy << " dy " << dz << " dz " << std::endl;
				//G4cout << "Secondaries garfield time " << time << G4endl;
				G4ThreeVector momentumDirection(dx, dy, dz);
				G4ThreeVector position(x, y, z);
				//std::cout << eKin_MeV << " eKin_MeV " << std::endl;
				G4DynamicParticle electron(G4Electron::ElectronDefinition(),
						momentumDirection, eKin_MeV);

				fastStep.CreateSecondaryTrack(electron, position, time, true);
				totalEnergySecondaries_MeV += eKin_MeV;
			}
		}
	}
}