#ifndef MATERIAL_MESSENGER_HPP
#define MATERIAL_MESSENGER_HPP
#include "G4UImessenger.hh"
#include "G4UIcmdWithAString.hh" //with a string instead of With3VectorAndUnit

namespace ne697 {
  // Forward declaration, to resolve circular dependency with DetectorConstruction
  // You still need to #include "detectorconstruction.hpp" in
  // geometrymessenger.cpp
  class DetectorConstruction;

  // User-facing part of the UI: just for the user
  class MaterialMessenger: public G4UImessenger {
  public:
    MaterialMessenger(DetectorConstruction* dm);
    ~MaterialMessenger();

    void SetNewValue(G4UIcommand* cmd, G4String val) override final;

  private:
    DetectorConstruction* m_dm;
    G4UIdirectory* m_mdirectory;
    G4UIcmdWithAString* m_detMatCmd;
  };  
}

#endif