#include <stdio.h>
#include <string.h>
//question 2
#define L 9
unsigned int Etat;
unsigned int Polynome = 0xc9;

void Initialise(unsigned int e){
  Etat = e;
}

void AfficheEtat(){
  int i;
  for (i=L-1;i>=0;i--) printf("%2d",(Etat >> i) & 1);
  printf("\n");
}

unsigned int Rebouclage(){
  unsigned int x;
  x=Etat & Polynome;
  x^=(x>>8);
  x^=(x>>4);
  x^=(x>>2);
  return (x^(x>>1))&1;
}

void Avance(){
  Etat = Etat>>1 | Rebouclage()<<8;
}

void VingtIteration(){
  for(int i = 0; i < 20; i++){
    Avance();
    //printf("%d: ",i);AfficheEtat();
  }
}

int Periode(){
  int periode = 0;
  int bound = 1000;
  unsigned int seen[bound];
  while(1){
    seen[periode] = Etat;
    periode++;
    Avance();
    for(int i = 0; i < periode;i++){
      if(seen[i] == Etat){
        periode -= i;
        return periode;
      }
    }
    if(periode == bound){break;}
  }
  return periode;
}


int main(){
  unsigned int EtatInitial = 0x1;
  printf("EtatInitial:\n");
  Initialise(EtatInitial);
  AfficheEtat(Etat);
  VingtIteration();
  printf("Après 20 iterations:\n");
  AfficheEtat();
  //determiner la periode:
  Initialise(EtatInitial);
  printf("Periode = %d\n",Periode());
}
