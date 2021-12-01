#ifndef GUN_MESSENGER_HPP
#define GUN_MESSENGER_HPP
#include "G4UImessenger.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"

namespace ne697 {
  // Forward declaration, to resolve circular dependency with DetectorConstruction
  // You still need to #include "detectorconstruction.hpp" in
  // geometrymessenger.cpp
  class PGA;

  // User-facing part of the UI: just for the user
  class GunMessenger: public G4UImessenger {
  public:
    GunMessenger(PGA* pg);
    ~GunMessenger();

    void SetNewValue(G4UIcommand* cmd, G4String val) override final;

  private:
    PGA* m_pg;
    G4UIdirectory* m_directory;
    G4UIcmdWith3VectorAndUnit* m_gunPosCmd;
  };  
}

#endif