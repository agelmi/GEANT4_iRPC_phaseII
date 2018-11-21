#ifndef GIFppDetectorConstruction_h
#define GIFppDetectorConstruction_h 1



#include "G4VUserDetectorConstruction.hh"
//#include "GIF++DataManager.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
//class GIFppDataManager;



// Standard includes
#include <list>
#include <string>
#include <cmath>

//G4 includes
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4ProductionCuts.hh"
#include "G4Region.hh"
#include "G4Trd.hh"



/// Detector construction class to define materials and geometry.
///
/// Crystals are positioned in Ring, with an appropriate rotation matrix. 
/// Several copies of Ring are placed in the full detector.

class GIFppDetectorConstruction : public G4VUserDetectorConstruction
{

public:
	GIFppDetectorConstruction();
	virtual ~GIFppDetectorConstruction();
public:
	virtual G4VPhysicalVolume* Construct();


 private:
    
      G4double minorBase; 		//dimensioni trapezio camera (area effettiva)
      G4double majorBase;
      G4double Height;

    // Logical volumes
	G4LogicalVolume* worldLog;		//volume logico world

        std::vector<G4Trd*>           trdCollection ;			//collezione del nome dei volumi
        std::vector<G4LogicalVolume*> trdLogCollection ;		//collezione dei volumi logici

 
   // Physical volumes
  
  	G4VPhysicalVolume* worldPhys;		//volume fisico world

   //per controllare che nessun volume sia sovrapposto ad un altro  

	G4bool  fCheckOverlaps;
};

#endif


