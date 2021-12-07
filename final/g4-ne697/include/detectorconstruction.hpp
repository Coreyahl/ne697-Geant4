#ifndef DETECTOR_CONSTRUCTION_HPP
#define DETECTOR_CONSTRUCTION_HPP
#include "G4VUserDetectorConstruction.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"

namespace ne697 {
  class GeometryMessenger;
  //class MaterialMessenger; //added for materials

  class DetectorConstruction: public G4VUserDetectorConstruction {
    public:
      DetectorConstruction();
      ~DetectorConstruction();
      // Solids, Logical Volumes, and Placements
      G4PVPlacement* Construct() override final;
      // SensitiveDetectors (and fields, which we aren't using)
      void ConstructSDandField() override final;

      void set_det_offset(G4ThreeVector const& detsize);
      G4ThreeVector const& get_det_offset() const;

      //added for thickness
      //void set_det_thickness(G4ThreeVector const& detthick);
      //G4ThreeVector const& get_det_thickness() const;

      //added for material
      void set_det_material(G4String const& detmaterial);
      G4String const& get_det_material() const;

    private:
      // List of G4LogicalVolumes we want to connect to the SensitiveDetector
      std::vector<G4LogicalVolume*> m_trackingVols;

      GeometryMessenger* m_messenger;
      //MaterialMessenger* m_mmessenger;
      G4ThreeVector m_detOffset;
      //G4ThreeVector m_detThick; //added for thickness
      G4String m_detMaterial; //added for material

      void build_materials();
  };
}

#endif
