
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

#ifndef GE1PrimaryGeneratorAction_h
#define GE1PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4Event;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class GE1PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    GE1PrimaryGeneratorAction(
            const G4String& particleName = "neutron",				//settata di defaul per inizializzarla.. modificata poi nei file src	
            G4double energy = 0*MeV,						//settata di defaul per inizializzarla.. modificata poi nei file src	
            G4ThreeVector position = G4ThreeVector(0,0,0),
            G4ThreeVector momentumDirection = G4ThreeVector(0,0,1)) ;
        
   ~GE1PrimaryGeneratorAction();

  public:
    virtual void GeneratePrimaries(G4Event*);
    G4ParticleGun* GetParticleGun() { return fParticleGun;} ;

    // static access method (per accedere a stepping da altri file)
    static GE1PrimaryGeneratorAction* Instance();
            
  private:

// static method (per accere da altri file)
 static GE1PrimaryGeneratorAction* fgInstance;  

    G4ParticleGun*  fParticleGun;
    G4double CX;
    G4double CY;
    G4double CZ;
    G4double gX;
    G4double gY;
    G4double gZ;
    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
