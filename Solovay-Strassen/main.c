#include <stdio.h>

int residu(unsigned long a,unsigned long p){
  if(a == 1){return 1;}
  if(a%p == 0){return 0;}
  if(a%2==0){
    return residu(a>>1,p)*(((((p*p)-1)/8)%2==0)?1:-1);
  }else{
    return residu(p%a,a)*(((((p-1)*(a-1))/4)%2==0)?1:-1);
  }
}

long unsigned mulmod(long unsigned a, long unsigned b, long unsigned n){
  return ((a%n)*(b%n))%n;
}

long unsigned sqrmod(long unsigned a, long unsigned n){
  return ((a%n)*(a%n))%n;
}

long unsigned expmod(long unsigned a,long unsigned n, long unsigned m){
  if(n==1){
    return a%m;
  }
  if(n%2==0){
    return sqrmod(expmod(a,n/2,m),m);
  }else{
    return mulmod(expmod(a,n-1,m),a,m);
  }
}

int Test(int n, int a){
  if((residu(a,n)+n)%n != expmod(a,(n-1)/2,n)){
    printf("%d n'est pas premier",n);
    return 1;
  }
  return 0;
}

int SolorayStrassen(int n){
  for(unsigned long i = 2; i*i < n; i+=2){
    if(i == 4){i--;}
    if(Test(n,i)){return 0;}
  }
  printf("%d est premier",n);
  return 1;
}



int main(){
  printf("55^100 mod 101 = %lu \n",expmod(55,100,101));
  printf("5^596 mod 1234 = %lu \n",expmod(5,596,1234));
  SolorayStrassen(101);
  printf("\n");
  SolorayStrassen(33317);
  printf("\n");
  SolorayStrassen(33317*33403);
  printf("\n");
  SolorayStrassen(113915369);
  printf("\n");
  return 0;
}
