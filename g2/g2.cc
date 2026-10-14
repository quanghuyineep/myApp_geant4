#include <DetectorConstruction.hh>
#include <G4RunManager.hh>
#include <G4UImanager.hh>
#include <G4VisExecutive.hh>
#include <G4UIExecutive.hh>
#include <G4NistManager.hh>

int main(int argc, char** argv){
  G4UIExecutive* ui = nullptr;
  if (argc == 1) {
    ui = new G4UIExecutive(argc, argv);
} 
}