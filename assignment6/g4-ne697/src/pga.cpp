#include "pga.hpp"
#include "G4Gamma.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

namespace ne697 {
  PGA::PGA():
    G4VUserPrimaryGeneratorAction(),
    m_gun(new G4ParticleGun(1))

  {
    G4cout << "Creating PGA" << G4endl;
    m_gun->SetParticleDefinition(G4Gamma::Definition());
    m_gun->SetParticleEnergy(1.*MeV);
    m_gun->SetParticlePosition(G4ThreeVector(0, 0, 0));
    m_gun->SetParticleMomentumDirection(G4ThreeVector(0., -1., 0.));
  }

  PGA::~PGA() {
    G4cout << "Deleting PGA" << G4endl;
    delete m_gun;
  }

  void PGA::GeneratePrimaries(G4Event* event) {
    G4double X0 = 50*cm*(G4UniformRand()-0.5); //rand num between -25 and 25
    G4double Y0 = 30*cm;
    G4double Z0 = 50*cm*(G4UniformRand()-0.5);
    m_gun->SetParticlePosition(G4ThreeVector(X0, Y0, Z0));
    m_gun->GeneratePrimaryVertex(event);
    return;
  }
}