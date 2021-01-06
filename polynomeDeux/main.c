#include <stdio.h>

void printMonome(int unsigned decalage){
  if(decalage == 0){
    printf("1");
  }else{
    printf("X^%u",decalage);
  }
}

void printBinary(long unsigned x){
  unsigned int decalage = 0;
  while((x>>decalage) != 0){
    printf("%lu",(x>>decalage)&1);
    decalage++;
  }
}

void printPol(long unsigned x,short newline){
  unsigned int decalage = 0;
  short first = 1;
  while((x>>decalage) != 0){
    if((x>>decalage) & 1){
      if(!first){
        printf("+");
      }else{
        first = 0;
      }
      printMonome(decalage);
    }
    decalage++;
  }
  if(newline){
    printf("\n");
  }else{
    printf(" ");
  }
}

int Degree(long unsigned x){
  if(x == 0){
    return -1;
  }
  unsigned int decalage = 0;
  short first = 1;
  while((x>>decalage) != 0){
    decalage++;
  }
  return (decalage>0)?decalage-1:decalage;
}

long unsigned polAdd(long unsigned a, long unsigned b){
  return a^b;
}

long unsigned PolMul(long unsigned a, long unsigned b){
  if(b>a){
    long unsigned tmp = a;
    a = b;
    b = tmp;
  }
  // ici deg a >= deg b
  int decalage = 0;
  long unsigned resultat = 0;
  while((b>>decalage) != 0){
    if((b>>decalage) & 1){
      resultat = resultat ^ (a<<decalage);
    }
    decalage++;
  }
  return resultat;
}

long unsigned PolSqr(long unsigned a){
  long unsigned resultat = 0;
  unsigned int decalage = 0;
  while((a>>decalage) != 0){
    if((a>>decalage) & 1){
      resultat = resultat ^ (1<<(decalage<<1));
    }
    decalage++;
  }
  return resultat;
}

long unsigned PolModDiv(long unsigned* r, long unsigned a, long unsigned b){
  if(a==b){
    *r=0;
    return 1;
  }
  if(b>a){
    *r = a;
    return 0;
  }
  long unsigned tmp = a;
  long unsigned resultat = 0;
  while(tmp > b){
    long unsigned decalage = Degree(tmp) - Degree(b);
    tmp = tmp ^ (b<<decalage);
    resultat = resultat ^ (1<<decalage);
  }
  *r = tmp;
  return resultat;
}

long unsigned PowerSerial(long unsigned a, long unsigned b){
  long unsigned tmp = a;
  long unsigned res = 0;
  while(1){
    unsigned int decalage = 0;
    while(!((tmp>>decalage) & 1)){
      decalage++;
      if(decalage>(32-Degree(b))){
        return res;
      }
    }
    tmp = tmp ^ (b<<decalage);
    res = res ^ (1<<decalage);
  }
  return res;
}

long unsigned PolPowerMod(long unsigned a, long unsigned n, long unsigned p){
  long unsigned r = 0;
  if(n==1){
    PolModDiv(&r,a,p);
    return r;
  }
  if(n % 2 == 0){
    PolModDiv(&r,PolMul(PolPowerMod(a,n-1,p),a),p);
  }else{
    PolModDiv(&r,PolPowerMod(PolSqr(a),n/2,p),p);
  }
  return r;
}

int main(){
  printPol(0xa2,0);
  printf("* ");
  printPol(0x144,0);
  printf("= ");
  printPol(PolMul(0xa2,0x144),1);
  printf("\n");
  printPol(0x1a,0);
  printf("^ 2 = ");
  printPol(PolSqr(0x1a),1);
  printf("\ndivision euclidienne de ");
  printPol(0x33a,0);
  printf("par ");
  printPol(0xb,1);
  printf("quotient: ");
  long unsigned r = 0;
  printPol(PolModDiv(&r,0x33a,0xb),1);
  printf("reste: ");
  printPol(r,1);
  printf("\n32 termes:");
  printPol(PowerSerial(0x1252,0x19),1);
  printf("\nX^255 mod ");
  printPol(0x11b,0);
  printf("= ");
  printPol(PolPowerMod(0x2,255,0x11b),1);
}
