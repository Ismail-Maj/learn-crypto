#include <stdio.h>
#include <string.h>

#define L 9
int Etat[L];
int Polynome[L] = {1,0,0,1,0,0,1,1,0};//{1,1,1,1,1,0,0,0,0};//{1,0,0,1,0,0,1,1,0};


void Initialise(int* e){
  for(int i = 0; i<L;i++){
    Etat[i] = e[i];
  }
}

void AfficheEtat(){
  for(int i = L-1; i >= 0; i--){
    printf("%2d",Etat[i]);
  }
  printf("\n");
}

void Avance(){
  int El = 0;
  for(int i = 0; i < L;i++){
    El+=Polynome[i]*Etat[i];
  }
  for(int i = 0; i < L-1;i++){
    Etat[i] = Etat[i+1];
  }
  Etat[L-1] = El%2;
}

int SontEgaux(int*a,int*b){
  for(int i = 0; i < L;i++){
    if(a[i] != b[i]){
      return 0;
    }
  }
  return 1;
}

void VingtIteration(){
  for(int i = 0; i < 20 ; i++){
    Avance();
    //printf("%d: ",i);AfficheEtat();
  }
}

int Periode(){
  int periode = 0;
  int bound = 1000;
  int seen[bound][L];
  while(1){
    memcpy(seen[periode],Etat,L*sizeof(int));
    periode++;
    Avance();
    for(int i = 0; i < periode;i++){
      if(SontEgaux(seen[i],Etat)){
        periode -= i;
        return periode;
      }
    }
    if(periode == bound){break;}
  }
  return periode;
}

int main(){
  int EtatInitial[L] = {1,0,0,0,0,0,0,0,0};
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
