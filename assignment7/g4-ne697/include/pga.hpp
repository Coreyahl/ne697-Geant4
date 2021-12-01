#ifndef PGA_HPP
#define PGA_HPP
#include "G4ParticleGun.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

namespace ne697 {
  class GunMessenger; //added for gun messenger

  class PGA: public G4VUserPrimaryGeneratorAction {
    public:
      PGA();
      ~PGA();

      void GeneratePrimaries(G4Event* event) override final;

      //added for gun messenger
      void set_gun_pos(G4ThreeVector const& gunpos);
      G4ThreeVector const& get_gun_pos() const;

    private:
      GunMessenger* m_messenger; //added for gun messenger
      G4ParticleGun* m_gun;
      G4ThreeVector m_gunPos; //added for gun messenger
  };
}

#endif