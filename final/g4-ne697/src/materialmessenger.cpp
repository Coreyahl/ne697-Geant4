#include "materialmessenger.hpp"
#include "detectorconstruction.hpp"
#include "G4UnitsTable.hh"

namespace ne697 {
  MaterialMessenger::MaterialMessenger(DetectorConstruction* dm):
    m_dm(dm)
    {
        // Directory: /ne697/material
        m_mdirectory = new G4UIdirectory("/ne697/material/");
        m_mdirectory->SetGuidance("Change detector material.");

        // Set detector size: /ne697/material/det_material
        m_detMatCmd = new G4UIcmdWithAString("/ne697/material/det_material", this);
        m_detMatCmd->SetGuidance("Set the detector material.");
        m_detMatCmd->SetParameterName("material", true);
        m_detMatCmd->SetDefaultValue(m_dm->get_det_material());
        m_detMatCmd->AvailableForStates(G4State_PreInit);
    }

  MaterialMessenger::~MaterialMessenger() {
    delete m_mdirectory;
    delete m_detMatCmd;
  }


  void MaterialMessenger::SetNewValue(G4UIcommand* cmd, G4String val) {
    if (cmd == m_detMatCmd) {
      //G4String parsed_val = m_detMatCmd->GetG4UIcmdWithAString(val);
      // This is fine too - just being clear above
      //auto parsed_val = m_detSizeCmd->GetNew3VectorValue(val);
      m_dm->set_det_material(val);
      G4cout << "Detector material set to " << val //removed best unit portion
        << G4endl;
    }

    return;
  }
}