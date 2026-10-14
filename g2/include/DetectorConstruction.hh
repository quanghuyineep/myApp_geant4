#ifndef DetectorConstruction_hh
#define DetectorConstruction_hh

#include "G4VUserDetectorConstruction.hh"
class G4Material;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction();
    ~DetectorConstruction() override;

    G4VPhysicalVolume* Construct() override;

    //Declare getters
    const G4Material* GetTargetMaterial() const { return fTargetMaterial; }
    G4double GetTargetThickness() const { return fTargetThickness; }

    //Declare setters
    void SetTargetMaterial(const G4String& materialName);
    void SetTargetThickness(G4double thickness);
private:    
    G4Material* fTargetMaterial;
    G4double fTargetThickness;
    G4VPhysicalVolume* fTargetPhysicalVolume;

};

#endif // DetectorConstruction_h    