#include<G4Isotope.hh>
#include<globals.hh>
#include<G4Element.hh>
#include<G4Material.hh>

#include<G4SystemOfUnits.hh>
#include<G4NistManager.hh>

int main(){
	G4Isotope* iso12C = new G4Isotope("C12",6,12);  // khi tao mot doi tuong thuoc bo nho Heap thi chuogn trinh tra ve con 
	G4Isotope* iso13C = new G4Isotope("C13",6,13);
	G4cout<<iso12C<<G4endl;     					// In ra thông tin trong con trỏ iso12C thông qua hàm operator<< được định nghĩa trong lớp G4cout 

	G4Element* element = new G4Element("Carbon", "C", 6, 12.011*g/mole);
	G4cout<<element<<G4endl;

	G4int num_isotopes = 2;
	G4Element* eleC_Custom = new G4Element("user_Carbon", "user_C", num_isotopes);
	G4double abudance ;
	eleC_Custom->AddIsotope(iso12C, abudance = 0.5);
	eleC_Custom->AddIsotope(iso13C, abudance = 0.5);
	G4cout<<eleC_Custom<<G4endl;

	// example showing creation of material, letting Geant4 guess the element
	G4double density,z,molar_mass;
	G4Material * matC = new G4Material("matCarbon",
								z=6,
								molar_mass=12*CLHEP::g/CLHEP::mole,
								density=2.6*CLHEP::g/CLHEP::cm3 );

	// example showing creation of material, specifying the components
	G4int numberOfComponents;
	G4Material * matCustomCarbon = new G4Material("matCustomCarbon",
								density = 2.6*CLHEP::g/CLHEP::cm3,
								numberOfComponents=1
								);

	G4double massFraction;
	matCustomCarbon->AddElement(eleC_Custom, massFraction=1.0);
	G4cout << matC << G4endl;
	G4cout << matCustomCarbon << G4endl;
	//------------------------------------
	// Example of using GEANT4 NIST Manager to get material
	G4NistManager* nist = G4NistManager::Instance();

	// Retrieve a Element from the NIST database by name
	G4Element* elH = nist->FindOrBuildElement("H");
	G4Element* elO = nist->FindOrBuildElement("O");

	G4double density_water = 1.0*g/cm3;
	G4int nComponents = 2;
	G4Material * myWater = new G4Material("Water", density_water, nComponents);
	myWater->AddElement(elH, 2);
	myWater->AddElement(elO, 1);
	G4cout<<myWater<<G4endl;

	// Retrive a Material from the NIST database by name
	G4Material* nistWater = nist->FindOrBuildMaterial("G4_WATER");
	if(nistWater != nullptr){
				G4cout<<nistWater<<G4endl;	
	}
	else{
		G4cout<<"Error: NIST Water not found"<<G4endl;
		return 1;
	}
	return 0;	
	}

