#include "detectorconstruction.hpp"
#include "globals.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "sensitivedetector.hpp"
#include "G4SDManager.hh"

namespace ne697 {
  DetectorConstruction::DetectorConstruction():
    G4VUserDetectorConstruction(),
    m_trackingVols()
  {
    G4cout << "Creating DetectorConstruction" << G4endl;
    build_materials();
  }

  DetectorConstruction::~DetectorConstruction() {
    G4cout << "Deleting DetectorConstruction" << G4endl;
  }
//create world of G4 air... comment out portion that previously made it liquid O
  G4PVPlacement* DetectorConstruction::Construct() {
    auto world_solid = new G4Box("world_solid", 0.5*2*m, 0.5*2*m, 0.5*2*m);
    auto nist = G4NistManager::Instance();
    auto world_mat = nist->FindOrBuildMaterial("G4_AIR");
    //auto world_mat = nist->FindOrBuildMaterial("NE697_LIQUID_OXYGEN");
    auto world_log = new G4LogicalVolume(
        world_solid,
        world_mat,
        "world_log"
    );
    // Commented since we don't want to record Hits in the world's air volume
    //m_trackingVols.push_back(world_log);
    auto world_phys = new G4PVPlacement(
        nullptr,
        G4ThreeVector(0, 0, 0),
        world_log,
        "world_phys",
        nullptr,
        false,
        0,
        true
    );
    //create NaI detector volume
    auto det_solid = new G4Box("det_solid", 0.5*50*cm, 0.5*5*cm, 0.5*50*cm);
    auto det_mat = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");
    auto det_log = new G4LogicalVolume(det_solid, det_mat, "det_log");
    // Tracking Hits in this volume
    m_trackingVols.push_back(det_log);
    new G4PVPlacement(
      nullptr,
      G4ThreeVector(0, -30*cm, 0),
      det_log,
      "det_phys",
      world_log,
      false,
      0,
      true
    );
    //create Tungsten T central Pillar
    auto T_solid = new G4Box("T_solid", 0.5*10*cm, 0.5*2*cm, 0.5*40*cm);
    auto T_mat = nist->FindOrBuildMaterial("G4_W");
    auto T_log = new G4LogicalVolume(T_solid, T_mat, "T_log");
    // NO tracking Hits in this volume
    //m_trackingVols.push_back(det_log);
    new G4PVPlacement(
      nullptr,
      G4ThreeVector(0, 0, 0),
      T_log,
      "T_phys",
      world_log,
      false,
      0,
      true
    );
    //create tungsten T "wings" (sides of the T)
    //wing 1
    auto T_wing_solid = new G4Box("T_wing_solid", 0.5*10*cm, 0.5*2*cm, 0.5*10*cm);
    //use same material as the central pillar
    auto T_wing_log = new G4LogicalVolume(T_wing_solid, T_mat, "T_wing_log");
    new G4PVPlacement(
      nullptr,
      G4ThreeVector(100,0,150), //these are in mm
      T_wing_log,
      "T_wing1_phys",
      world_log,
      false,
      0,
      true
    );
    //wing 2
    //has same dimensions as wing 1, same material/log as pillar (and wing 1)
    new G4PVPlacement(
      nullptr,
      G4ThreeVector(-100,0,150), //these are in mm
      T_wing_log,
      "T_wing2_phys",
      world_log,
      false,
      0,
      true
    );

    return world_phys;
  }

  void DetectorConstruction::ConstructSDandField() {
    // We will ask for "world_sd_hits" later in Run::RecordEvent()
    auto sd = new SensitiveDetector("world_sd");
    G4SDManager::GetSDMpointer()->AddNewDetector(sd);
    // Connect the sensitive detector to all of the logical volumes on the list
    for (auto& log : m_trackingVols) {
      SetSensitiveDetector(log, sd);
    }
    return;
  }
  //The code below builds a new material... we dont need this material right now
  void DetectorConstruction::build_materials() {
    auto o16 = new G4Isotope("NE697_O16", 8, 16, 15.99491463*g/mole);
    auto o17 = new G4Isotope("NE697_O17", 8, 17, 16.9991312*g/mole);
    auto o18 = new G4Isotope("NE697_O18", 8, 18, 17.9991603*g/mole);
  
    auto nat_o = new G4Element("NE697_natO", "O_ne697", 3);
    nat_o->AddIsotope(o16, 99.757*perCent);    
    nat_o->AddIsotope(o17, 0.038*perCent);    
    nat_o->AddIsotope(o18, 0.205*perCent);
  
    auto liq_o = new G4Material("NE697_LIQUID_OXYGEN", 1.141*g/cm3, 1);
    liq_o->AddElement(nat_o, 1);
    G4cout << "OUR MATERIAL: " << liq_o << G4endl;
  
    auto nist_man = G4NistManager::Instance();
    auto nist_o = nist_man->FindOrBuildElement("O");
    auto nist_liq_o = new G4Material("NIST_LIQUID_OXYGEN", 1.141*g/cm3, 1);
    nist_liq_o->AddElement(nist_o, 1);
    G4cout << "NIST MATERIAL: " << nist_liq_o << G4endl;
    return;
  }
}
