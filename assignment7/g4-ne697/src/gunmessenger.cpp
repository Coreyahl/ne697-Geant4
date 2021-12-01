#include "gunmessenger.hpp"
#include "pga.hpp"
#include "G4UnitsTable.hh"

namespace ne697 {
  GunMessenger::GunMessenger(PGA* pg):
    m_pg(pg)
    {
        // Directory: /ne697/geometry
        m_directory = new G4UIdirectory("/ne697/gun/");
        m_directory->SetGuidance("Change position of gun.");

        // Set detector size: /ne697/gun/offset
        m_gunPosCmd = new G4UIcmdWith3VectorAndUnit("/ne697/gun/offset", this);
        m_gunPosCmd->SetGuidance("Set gun position.");
        m_gunPosCmd->SetParameterName("x", "y", "z", true);
        m_gunPosCmd->SetDefaultValue(m_pg->get_gun_pos());
        m_gunPosCmd->AvailableForStates(G4State_Idle);
    }

  GunMessenger::~GunMessenger() {
    delete m_directory;
    delete m_gunPosCmd;
  }

  void GunMessenger::SetNewValue(G4UIcommand* cmd, G4String val) {
    if (cmd == m_gunPosCmd) {
      G4ThreeVector parsed_val = m_gunPosCmd->GetNew3VectorValue(val);
      // This is fine too - just being clear above
      //auto parsed_val = m_detSizeCmd->GetNew3VectorValue(val);
      m_pg->set_gun_pos(parsed_val);
      G4cout << "Gun position set to" << G4BestUnit(parsed_val, "Length")
        << G4endl;
    }
    
    return; //not for thickness
  }
}