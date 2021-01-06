#include <stdio.h>

unsigned long IndicatricePuissancePremier(unsigned long p, unsigned long x){
  unsigned long tmp = 1;
  while(x>1){
    tmp*=p;
    x--;
  }
  return tmp*(p-1);
}

unsigned long IndicatriceEuler(unsigned long n){
  unsigned long resultat = 1;
  unsigned long pointer = 2;
  unsigned long reste = n;
  while(pointer*pointer <= n && reste != 0){
    if(reste%pointer == 0){
      unsigned long puissance = 0;
      while(reste % pointer == 0){
        puissance++;
        reste = reste/pointer;
      }
      resultat *= IndicatricePuissancePremier(pointer,puissance);
    }
    pointer++;
  }
  if(reste!=1){
    resultat*=IndicatricePuissancePremier(reste,1);
  }
  return resultat;
}

void Sqr(unsigned long n){
  int ar[n];
  for(unsigned long i = 1; i < n; i++){
    ar[i] = 0;
  }
  for(unsigned long i = 1; i < n; i++){
    ar[(i*i)%n] = 1;
  }
  printf("residu quadratique de %lu: ",n);
  for(unsigned long i = 0; i < n;i++){
    if(ar[i] == 1){
      printf("%lu ",i);
    }
  }
  printf("\n");
}

int legendre(unsigned long a,unsigned long p){
  if(a == 1){return 1;}
  if(a%p == 0){return 0;}
  if(a%2==0){
    return legendre(a>>1,p)*(((((p*p)-1)/8)%2==0)?1:-1);
  }else{
    return legendre(p%a,a)*(((((p-1)*(a-1))/4)%2==0)?1:-1);
  }
}

void SqrLegendre(unsigned long n){
  printf("residu quadratique de %lu: ",n);
  for(unsigned long i = 1; i < n; i++){
    if(legendre(i,n) == 1){
      printf("%lu ",i);
    }
  }
}

int main(){
  printf("Phi(%d) = %lu\n",10205,IndicatriceEuler(10205));
  printf("\n");
  Sqr(29);
  printf("\n");
  SqrLegendre(29);
  printf("\n");
}
