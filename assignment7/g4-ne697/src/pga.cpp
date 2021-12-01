#include "pga.hpp"
#include "G4Gamma.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "gunmessenger.hpp"

namespace ne697 {
  PGA::PGA():
    G4VUserPrimaryGeneratorAction(),
    m_gun(new G4ParticleGun(1)),
    m_gunPos(0.*cm, 30.*cm, 0.*cm) //added for gun messenger

  {
    G4cout << "Creating PGA" << G4endl;
    m_gun->SetParticleDefinition(G4Gamma::Definition());
    m_gun->SetParticleEnergy(1.*MeV);
    m_gun->SetParticlePosition(G4ThreeVector(0, 0, 0));
    m_gun->SetParticleMomentumDirection(G4ThreeVector(0., -1., 0.));
    m_messenger = new GunMessenger(this); //added for gun messenger
  }

  PGA::~PGA() {
    G4cout << "Deleting PGA" << G4endl;
    delete m_gun;
    delete m_messenger; //added for gun messenger
  }

  void PGA::GeneratePrimaries(G4Event* event) {
    G4double X0 = 50*cm*(G4UniformRand()-0.5); //rand num between -25 and 25
    G4double Y0 = m_gunPos.getY();
    G4double Z0 = 50*cm*(G4UniformRand()-0.5);
    m_gun->SetParticlePosition(G4ThreeVector(X0, Y0, Z0));
    m_gun->GeneratePrimaryVertex(event);
    return;
  }
  //add for gun messenger
  void PGA::set_gun_pos(G4ThreeVector const& gunpos) {
    m_gunPos = gunpos;
    return;
  }
  G4ThreeVector const& PGA::get_gun_pos() const {
    return m_gunPos;
  }
}