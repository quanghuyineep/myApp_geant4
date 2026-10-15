#include "DetectorConstruction.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"    
#include "G4RunManager.hh"   

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction(){
    SetTargetMaterial ("G4_Si");
    SetTargetThickness (1.0 *CLHEP::cm);
    }
DetectorConstruction::~DetectorConstruction(){}

// void DetectorConstruction::SetTargetMaterial(const G4String& materialName)
// {
//     G4Material* mat = G4NistManager::Instance();    
//     if (!mat) {
//         G4Exception("DetectorConstruction::SetTargetMaterial",
//                     "InvalidMaterial", FatalException,
//                     ("Material " + materialName + " not found.").c_str());
//     }
//     if (mat != fTargetMaterial) {
//         fTargetMaterial = mat->FindOrBuildMaterial(materialName);
//         G4RunManager::GetRunManager()->PhysicsHasBeenModified();    
//     }
//     exit(-1);
// }

void DetectorConstruction::SetTargetMaterial(const G4String& materialName)
{
    G4NistManager* nistManager = G4NistManager::Instance();
    if (!nistManager) {
        G4Exception("DetectorConstruction::SetTargetMaterial",
                    "InvalidMaterial", FatalException,
                    "NIST material manager is unavailable.");
        return;
    }

    G4Material* material = nistManager->FindOrBuildMaterial(materialName);
    if (!material) {
        G4Exception("DetectorConstruction::SetTargetMaterial",
                    "InvalidMaterial", FatalException,
                    ("Material " + materialName + " not found.").c_str());
        return;
    }

    if (material != fTargetMaterial) {
        fTargetMaterial = material;
        G4RunManager::GetRunManager()->PhysicsHasBeenModified();
    }
}

void DetectorConstruction::SetTargetThickness(G4double thickness)
{
    if (thickness <= 0) {
        G4Exception("DetectorConstruction::SetTargetThickness",
                    "InvalidThickness", FatalException,
                    "Target thickness must be positive.");
    }
    fTargetThickness = thickness;
    G4RunManager::GetRunManager()->ReinitializeGeometry();
}   

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // 1.Create material  
    const G4String worldMaterialName = "G4_Galactic";
    G4Material* worldMaterial = G4NistManager::Instance()->FindOrBuildMaterial(worldMaterialName);
    

    //fTargetMaterial is set in the SetTargetMaterial method, so we can use it directly here.

    //2. Creating solids
    G4double targetXsize = 1.2 * fTargetThickness;
    G4double targetZsize = 1.2 * fTargetThickness;
    G4double worldSizeXY = 1.5 * fTargetThickness;
    G4double worldSizeZ = 1.5 * fTargetThickness;

    G4Box* target_solid = new G4Box("target_solid", targetXsize / 2, targetXsize / 2, targetZsize / 2); 
    G4Box* world_solid = new G4Box("world_solid", worldSizeXY / 2, worldSizeXY / 2, worldSizeZ / 2);

    //3. Logical volumes
    G4LogicalVolume* logicTarget = new G4LogicalVolume(target_solid, fTargetMaterial, "target_logical");
    G4LogicalVolume* logicWorld = new G4LogicalVolume(world_solid, worldMaterial, "world_logical");

    // 4. Physical volumes
    G4VPhysicalVolume* target_physical_volume = new G4PVPlacement(nullptr, // Rotation 
                                                                G4ThreeVector(0,0,0), // Position
                                                                logicTarget, // Logical volume
                                                                "target_physical", // Name 
                                                                logicWorld, // Mother volume
                                                                false, // No boolean operation
                                                                0); // Copy number  
    G4VPhysicalVolume* world_physical_volume = new G4PVPlacement(nullptr, // Rotation 
                                                                G4ThreeVector(0,0,0), // Position
                                                                logicWorld, // Logical volume
                                                                "world_physical", // Name 
                                                                nullptr, // No mother volume
                                                                false, // No boolean operation
                                                                0); // Copy number

    fTargetPhysicalVolume = target_physical_volume; // Store the target physical volume for later access
    return fTargetPhysicalVolume;
}