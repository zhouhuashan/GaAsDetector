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
//
// $Id: ExN02SteppingAction.cc,v 1.9 2006-06-29 17:48:18 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "ExN02SteppingAction.hh"
#include "G4SteppingManager.hh"
#include "TTree.h"
#include "TFile.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02SteppingAction::ExN02SteppingAction()
{ 
	t1 = new TTree("myTree1","");	
	t1->Branch("trackid",&trackid,"trackid /I");	
	t1->Branch("px",&px,"px /F");
	t1->Branch("py",&py,"py /F");
	t1->Branch("pz",&pz,"pz /F");
	t1->Branch("x",&x,"x /F");
	t1->Branch("y",&y,"y /F");
	t1->Branch("z",&z,"z /F");
	t2 = new TTree("myTree2","");	
	t2->Branch("E",&E0,"E /F");
	t2->Branch("px",&px0,"px /F");
	t2->Branch("py",&py0,"py /F");
	t2->Branch("pz",&pz0,"pz /F");
	t2->Branch("x",&x0,"x /F");
	t2->Branch("y",&y0,"y /F");
	t2->Branch("z",&z0,"z /F");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02SteppingAction::UserSteppingAction(const G4Step* aStep)
{ 
	if((aStep->GetTrack()->GetDynamicParticle()->GetCharge())==(-1))
	{	
		px = aStep->GetTrack()->GetDynamicParticle()->GetMomentum().x();
		py = aStep->GetTrack()->GetDynamicParticle()->GetMomentum().y();
		pz = aStep->GetTrack()->GetDynamicParticle()->GetMomentum().z();
		x = aStep->GetPreStepPoint()->GetPosition().x();
		y = aStep->GetPreStepPoint()->GetPosition().y();
		z = aStep->GetPreStepPoint()->GetPosition().z();
		t1->Fill();
		if((aStep->GetTrack()->GetCurrentStepNumber())==10){
			E0 = aStep->GetTrack()->GetVertexKineticEnergy();			
			px0 = aStep->GetTrack()->GetVertexMomentumDirection().x();
			py0 = aStep->GetTrack()->GetVertexMomentumDirection().y();
			pz0 = aStep->GetTrack()->GetVertexMomentumDirection().z();
			x0 = aStep->GetTrack()->GetVertexPosition().x();
			y0 = aStep->GetTrack()->GetVertexPosition().y();
			z0 = aStep->GetTrack()->GetVertexPosition().z();		
			t2->Fill();
		}
	}
}

ExN02SteppingAction::~ExN02SteppingAction()
{
	TFile f1("file1.root","RECREATE");
	t1->Write();
	f1.Close();
	TFile f2("file2.root","RECREATE");
	t2->Write();
	f2.Close();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


