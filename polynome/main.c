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

void printPol(long unsigned x){
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



int main(){
  printBinary(0x123);
  printf("\n");
  printPol(0x123);
  printf("\n");
  printf("degree = %d\n",Degree(0x0123));
}
