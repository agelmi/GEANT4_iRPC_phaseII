//PRIMARY GENERATOR PER NEUTRONI


// camera posizionata metà al di sopra del centro e metà al di sotto (coordinata Y). cosi come metà a desta e metà a sinistra (coordinata X). Mentre per la profondità (coordinata Z) è tutta nella parte positiva. 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

#include "GE1PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Geantino.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
//#include "TrGEMAnalysis.hh"

#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include <fstream>



// metodi per accere da ALTRI FILE
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GE1PrimaryGeneratorAction* GE1PrimaryGeneratorAction::fgInstance = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GE1PrimaryGeneratorAction* GE1PrimaryGeneratorAction::Instance()
{
// Static acces function via G4RunManager 

  return fgInstance;
}      

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GE1PrimaryGeneratorAction::GE1PrimaryGeneratorAction(
      const G4String& particleName,
      G4double energy,
      G4ThreeVector position,
      G4ThreeVector momentumDirection) :
   G4VUserPrimaryGeneratorAction(),
   fParticleGun(0)

{

  fgInstance = this;    //metodo per accere da altri file

  G4int n_particle = 1;										//setta numero particelle (possibile farlo anche da macro)
//  fParticleGun  = new G4ParticleGun(n_particle);
 G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particlen = particleTable -> FindParticle("neutron");			//setta tipo di particelle (possibile farlo anche da macro)
 fParticleGun  = new G4ParticleGun(particlen,n_particle);
   
// set energy
 
  fParticleGun->SetParticleEnergy(energy);  //setta energia particelle (prende quella default definita in file .hh) modificata poi a start event (fine file). Se non si setta anche qua (valore 0 settato in .hh) la prima particella lanciata ha valore di default 1000 MeV 
   

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GE1PrimaryGeneratorAction::~GE1PrimaryGeneratorAction()
{
  delete fParticleGun;

 fgInstance = 0;  //metodo per accedere da altri file
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GE1PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{    

     //set direction
     G4double cosx,cosy;
     G4double segnoZ;
     CX=0;CY=0;CZ=0;
     G4double fracBehind=0.5;   //fraction of particles coming from behind, 50 % di possibilità di particelle dal davanti e dal dietro 
     
     segnoZ=G4UniformRand();	//genera segno casuale di z (se esce numero da 0 a 0.5 allora è dietro, da 0.5 a 1 davanti)



     if (segnoZ<fracBehind)  {  // se minore di 0.5 Z viene settato negativo quindi particella viene da dietro, se invece maggiore di 0.5 Z settato positivo particella dal davanti 
       


// si utilizza metodo HIT OR MISS (si costruisce rettangolo intorno a istogramma, prendendo il valore massimo della y per trovare l'altezza del rettangolo. Se il valore estratto a caso è dentro il rettangolo si tiene, altrimenti si scarta e si ripesca
 
        cosx=-1+G4UniformRand()*2;		// genera valore casuale del coseno, tra -1 e 1 (se esce 1 da random -> cosx=-1+1*2=1  + il massimo che può uscir
        CX = cosx; 					//CX è variabile assegnata nei file .hh 
 
     while (1){
        cosy=-1+G4UniformRand()*2;

         if((cosy*cosy+CX*CX)<1) break;
      }

       CY = cosy; 
       CZ = -sqrt(1-CX*CX-CY*CY);		//si calcola il cosZ a partire dagli altri 2. Negativo perchè deve venire da dietro
 }



else {						//else, nel caso del segno positivo di Z

        cosx=-1+G4UniformRand()*2;
        CX = cosx; 
   
 
     while (1){
        cosy=-1+G4UniformRand()*2;
         if((cosy*cosy+CX*CX)<1) break;
       }

       CY = cosy; 
       CZ = sqrt(1-CX*CX-CY*CY);		//Z POSITIVO
}

   
  
   fParticleGun->SetParticleMomentumDirection((G4ThreeVector(+CX,+CY,+CZ))); 
   

//Uniform generation on the detector surface,		scelta casuale della sorgente, ma che deve rientrare nell'area del rivelatore

 gX =0;						//solo inizializzazione variabili, numeri senza significato
 gY = 0;
 gZ = 0;
 G4double gXtemp=99999; 		 
 G4double gYtemp=99999; 
  
 while(1){
  
  gYtemp = G4UniformRand()*1613-806.5;					//scelta a caso della coordinata y (la dimensione della camera va da -503.5 a 503.5   messa a metà dell'asse, metà sopra e metà sotto)		
  gXtemp = G4UniformRand()*836.3-418.15;  
   if(fabs(gXtemp)<(gYtemp+3338.6)/11.4316) break; 		// y=mx+q  la variazione di y e x è lineare, quindi si trovano i coefficienti m=11.066 e q=2002.93 in modo che la sorgente quando scende di y e la camera si restringe di larghezza x, ne tiene conto.
 
 }
 gX=gXtemp;
 gY=gYtemp;


if(segnoZ<fracBehind){ gZ=29;}			//in base al segno della camera si posiziona la sorgente, appena dietro o appena davanti (29 perchè 28 è spessore rivelatore)
else {gZ=-1;}

  //create vertex
  //   
  fParticleGun->SetParticlePosition(G4ThreeVector(gX,gY,gZ));
  fParticleGun->GeneratePrimaryVertex(anEvent);

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
