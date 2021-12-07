#include "detectorconstruction.hpp"
#include "globals.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "sensitivedetector.hpp"
#include "G4SDManager.hh"
#include "geometrymessenger.hpp"
#include "materialmessenger.hpp"

namespace ne697 {
  DetectorConstruction::DetectorConstruction():
    G4VUserDetectorConstruction(),
    m_trackingVols(),
    m_detOffset(0*cm, 0*cm, 0*cm) //added diamond position for geometry UI default
    //m_detThick(50.*cm, 5.*cm, 50.*cm), //added thickness for geomtry UI default
    //m_detMaterial("G4_Ge") //added for material
  {
    G4cout << "Creating DetectorConstruction" << G4endl;
    m_messenger = new GeometryMessenger(this); //added for geometry UI
    //m_mmessenger = new MaterialMessenger(this); //for material UI
    build_materials();
  }

  DetectorConstruction::~DetectorConstruction() {
    G4cout << "Deleting DetectorConstruction" << G4endl;
    delete m_messenger; //added for geometry UI
    //delete m_mmessenger; //for material UI
  }
//create world of G4 air... comment out portion that previously made it liquid O
  G4PVPlacement* DetectorConstruction::Construct() {
    auto world_solid = new G4Box("world_solid", 0.5*2.5*cm, 0.5*2.5*cm, 0.5*2.5*cm);
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
    //create diamond detector volume
    auto det_solid = new G4Box("det_solid",0.5*0.5*cm,0.5*0.5*cm,0.5*0.05*cm);
    auto det_mat = nist->FindOrBuildMaterial("NIST_DIAMOND");
    //auto det_mat = nist->FindOrBuildMaterial(m_detMaterial); //for materialmessenger
    auto det_log = new G4LogicalVolume(det_solid, det_mat, "det_log");
    // Tracking Hits in this volume
    m_trackingVols.push_back(det_log);
    new G4PVPlacement(
      nullptr,
      //position can be changed by using m_detSize
      //made so that a positive input in the UI results in increasing distance
      //between the scintillator and diamond detector
      G4ThreeVector(0.*cm, 0.*cm, -(0.001+0.3+0.15+0.025)*cm - m_detOffset.getZ() ),
      det_log,
      "det_phys",
      world_log,
      false,
      0,
      true
    );
    //create scintillator
    auto scintillator_solid = new G4Box("scintillator_solid", 0.5*0.5*cm, 0.5*0.5*cm, 0.5*0.001*cm);
    auto scintillator_mat = nist->FindOrBuildMaterial("NIST_SCINTILLATOR");
    auto scintillator_log = new G4LogicalVolume(scintillator_solid, scintillator_mat, "scintillator_log");
    //tracking Hits in this volume
    m_trackingVols.push_back(scintillator_log);
    new G4PVPlacement(
      nullptr,
      G4ThreeVector(0, 0, 0),
      scintillator_log,
      "scintillator_phys",
      world_log,
      false,
      0,
      true
    );
    //create light guides
    //top light guide
    auto lightguide_solid = new G4Tubs("lightguide_solid", 
      0.05*cm, //inner radius
      0.7*cm, //outer radius
      0.5*0.15*cm, //z half length
      0*degree, 360*degree); //start phi and segment angle
    auto lightguide_mat = nist->FindOrBuildMaterial("NIST_LIGHTGUIDE");
    auto lightguide_log = new G4LogicalVolume(lightguide_solid, lightguide_mat, "lightguide_log");
    new G4PVPlacement(
      nullptr,
      G4ThreeVector(0.*cm, 0.*cm, (0.5*0.15+0.001)*cm), //these are in cm
      lightguide_log,
      "top_lightguide_phys",
      world_log,
      false,
      0,
      true
    );
    //lower light guide
    //has same dimensions and material as top light guide
    new G4PVPlacement(
      nullptr,
      G4ThreeVector(0.*cm,0.*cm,-(0.5*0.15+0.001)*cm), //these are in cm
      lightguide_log,
      "bottom_lightguide_phys",
      world_log,
      false,
      0,
      true
    );
    //PCB (make of Al)
    auto pcb_solid = new G4Tubs("pcb_solid", 
      0.139*cm, //inner radius
      1.*cm, //outer radius
      0.5*0.15*cm, //z half length
      0*degree, 360*degree); //start phi and segment angle
    auto pcb_mat = nist->FindOrBuildMaterial("G4_Al");
    auto pcb_log = new G4LogicalVolume(pcb_solid, pcb_mat, "pcb_log");
    new G4PVPlacement(
      nullptr,
      //position can be changed by using m_detSize
      //made so that a positive input in the UI results in increasing distance
      //between the scintillator and diamond detector
      G4ThreeVector(0.*cm,0.*cm,-(0.001+0.3+0.15*0.5)*cm - m_detOffset.getZ() ),
      pcb_log,
      "pcb_phys",
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
    //auto o16 = new G4Isotope("NE697_O16", 8, 16, 15.99491463*g/mole); //making isotopes
    //auto o17 = new G4Isotope("NE697_O17", 8, 17, 16.9991312*g/mole);
    //auto o18 = new G4Isotope("NE697_O18", 8, 18, 17.9991603*g/mole);
  
    //auto nat_o = new G4Element("NE697_natO", "O_ne697", 3);
    //nat_o->AddIsotope(o16, 99.757*perCent);   //making elements from isotopes 
    //nat_o->AddIsotope(o17, 0.038*perCent);    
    //nat_o->AddIsotope(o18, 0.205*perCent);
  
    //auto liq_o = new G4Material("NE697_LIQUID_OXYGEN", 1.141*g/cm3, 1);
    //liq_o->AddElement(nat_o, 1); //making material from elements
    //G4cout << "OUR MATERIAL: " << liq_o << G4endl;
    
    auto nist_man = G4NistManager::Instance();
    auto nist_o = nist_man->FindOrBuildElement("O"); //oxygen
    auto nist_h = nist_man->FindOrBuildElement("H"); //hydrogen
    auto nist_c = nist_man->FindOrBuildElement("C"); //carbon
    auto nist_lightguide = new G4Material("NIST_LIGHTGUIDE", 1.18*g/cm3, 3); //make light guide
    nist_lightguide->AddElement(nist_o, 33.8*perCent ); //add O element to light guide material
    nist_lightguide->AddElement(nist_h,2.2*perCent); //percent by mass bc inputing a G4double
    nist_lightguide->AddElement(nist_c,64*perCent); //if input a G4int, it uses atomic fraction
    auto nist_scintillator = new G4Material("NIST_SCINTILLATOR", 1.02*g/cm3, 2);
    nist_scintillator->AddElement(nist_h,8.6*perCent); //mass fraction
    nist_scintillator->AddElement(nist_c,93.7*perCent); //atomic fraction is 0.5254 and 0.4746
    auto nist_diamond = new G4Material("NIST_DIAMOND", 3.51*g/cm3, 1);
    nist_diamond->AddElement(nist_c, 1);
    G4cout << "NIST MATERIALS: " << nist_lightguide << nist_scintillator << nist_diamond << G4endl;
    return;
  }

  void DetectorConstruction::set_det_offset(G4ThreeVector const& detsize) {
    m_detOffset = detsize;
    return;
  }

  G4ThreeVector const& DetectorConstruction::get_det_offset() const {
    return m_detOffset;
  }

  //add this for thickness
  //void DetectorConstruction::set_det_thickness(G4ThreeVector const& detthick) {
  //  m_detThick = detthick;
  //  return;
  //} //and add this for thickness
  //G4ThreeVector const& DetectorConstruction::get_det_thickness() const {
  //  return m_detThick;
  //}

  //add this for material
  void DetectorConstruction::set_det_material(G4String const& detmaterial) {
    m_detMaterial = detmaterial;
    return;
  }
  //and add this for material
  G4String const& DetectorConstruction::get_det_material() const {
    return m_detMaterial;
  }
}
