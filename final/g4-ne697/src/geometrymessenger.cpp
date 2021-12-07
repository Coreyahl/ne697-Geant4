#include "geometrymessenger.hpp"
#include "detectorconstruction.hpp"
#include "G4UnitsTable.hh"

namespace ne697 {
  GeometryMessenger::GeometryMessenger(DetectorConstruction* dc):
    m_dc(dc)
    {
        // Directory: /ne697/geometry
        m_directory = new G4UIdirectory("/ne697/geometry/");
        m_directory->SetGuidance("Change parameters of the geometry.");

        // Set detector size: /ne697/geometry/det_size
        m_detOffsetCmd = new G4UIcmdWith3VectorAndUnit("/ne697/geometry/det_offset", this);
        m_detOffsetCmd->SetGuidance("Set the diamond detector offset.");
        m_detOffsetCmd->SetParameterName("x", "y", "z", true);
        m_detOffsetCmd->SetDefaultValue(m_dc->get_det_offset());
        m_detOffsetCmd->AvailableForStates(G4State_PreInit);
        // Set detector thickness:  /ne697/geometry/det_thickness
        //m_detThickCmd = new G4UIcmdWith3VectorAndUnit("/ne697/geometry/det_thickness",this);
        //m_detThickCmd->SetGuidance("Set the detector thickness.");
        //m_detThickCmd->SetParameterName("x","y","z",true);
        //m_detThickCmd->SetDefaultValue(m_dc->get_det_thickness());
        //m_detThickCmd->AvailableForStates(G4State_PreInit);
    }

  GeometryMessenger::~GeometryMessenger() {
    delete m_directory;
    delete m_detOffsetCmd;
    //delete m_detThickCmd; //added for thickness
  }

  void GeometryMessenger::SetNewValue(G4UIcommand* cmd, G4String val) {
    if (cmd == m_detOffsetCmd) {
      G4ThreeVector parsed_val = m_detOffsetCmd->GetNew3VectorValue(val);
      // This is fine too - just being clear above
      //auto parsed_val = m_detSizeCmd->GetNew3VectorValue(val);
      m_dc->set_det_offset(parsed_val);
      G4cout << "Diamond detector offset set to " << G4BestUnit(parsed_val, "Length")
        << G4endl;
    } //else if (cmd == m_detThickCmd) {
      //G4ThreeVector parsed_val = m_detThickCmd->GetNew3VectorValue(val);
      //m_dc->set_det_thickness(parsed_val);
      //G4cout << "Detector thickness set to " << G4BestUnit(parsed_val, "Length")
      //  << G4endl;
    //}
    
    return; //not for thickness
  }
}