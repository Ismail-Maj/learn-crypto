#include <stdio.h>

typedef struct{
  long int a,b,d; // x = a+bV5 / d
}GaussType;

long int pgcd(long int a, long int b){
  if(a<0) a=-a;
  if(b<0) b=-b;
  if(b==0) return a;

  while(a){
    b = b%a;
    if(b==0) return a;
    a = a%b;
  }
  return b;
}

void GaussAffiche(GaussType x,int cr){
  printf("(%ld %s %ld V5) / %ld%s",
    x.a,
    x.b<0?"-":"+",
    x.b<0?-x.b:x.b,
    x.d,
    cr?"\n":" "
  );
}

void Reduire(GaussType* x){
  long int pgcdAB = pgcd(x->a,x->b);
  long int  pgcdAll = pgcd(pgcdAB,x->d);
  if(pgcdAll == 0){ return;}
  x->a = x->a / pgcdAll;
  x->b = x->b / pgcdAll;
  x->d = x->d / pgcdAll;
  if(x->d < 0){
    x->a = -x->a;
    x->b = -x->b;
    x->d = -x->d;
  }
}

void GaussAdd(GaussType* s, GaussType x, GaussType y){
  s->a = (x.a * y.d) + (y.a * x.d);
  s->b = (x.b * y.d) + (y.b * x.d);
  s->d = x.d * y.d;
  Reduire(s);
}

void GaussMul(GaussType* p, GaussType x, GaussType y){
  p->a = (x.a*y.a) + (5*x.b*y.b);
  p->b = (x.a*y.b) + (x.b*y.a);
  p->d = x.d * y.d;
  Reduire(p);
}

void GaussOpp(GaussType* o, GaussType x){
  o->a = -(x.a);
  o->b = -(x.b);
  o->d = x.d;
  Reduire(o);
}

void GaussInv(GaussType* i, GaussType x){
  i->a = (x.d*x.a);
  i->b = -(x.d*x.b);
  i->d = x.a*x.a - x.b*x.b*5;
  Reduire(i);
}

void GaussSoustrait(GaussType* s, GaussType x, GaussType y){
  GaussType tmp = {0,0,0};
  GaussOpp(&tmp,y);
  GaussAdd(s,x,tmp);
  Reduire(s);
}

void GaussDivise(GaussType* s, GaussType x, GaussType y){
  GaussType tmp = {0,0,0};
  GaussInv(&tmp,y);
  GaussMul(s,x,tmp);
  Reduire(s);
}

void GaussPuiss(GaussType* r, GaussType  x, unsigned int n){
  GaussType y = x;
  GaussType Produit = {1,0,1};
  unsigned int exp = n;
  while(exp != 0){
    if(exp%2 == 1){
      GaussMul(&Produit,Produit,y);
    }
    GaussMul(&y,y,y);
    exp = exp/2;
  }
  Reduire(&Produit);
  r->a = Produit.a;
  r->b = Produit.b;
  r->d = Produit.d;
}

GaussType Phi = {1,1,2};
GaussType PhiB = {1,-1,2};
GaussType racineDeCinq = {0,1,1};
GaussType deux = {2,0,1};
GaussType quatre = {4,0,1};

unsigned long int Fibonacci1(unsigned int n){
  GaussType Phin = {0,0,0};
  GaussPuiss(&Phin,Phi,n);
  GaussType PhiBn = {0,0,0};
  GaussPuiss(&PhiBn,PhiB,n);
  GaussType res = {0,0,0};
   GaussSoustrait(&res,Phin,PhiBn);
  GaussDivise(&res,res,racineDeCinq);
  return (res.a/res.d);
}

int Fibonacci2(int x){
  if(x < 2){return 1;}
  GaussType vn = {1,0,2};//v2
  GaussType vnPlusUn = {1,0,2};//v3
  GaussType tmp = {0,0,0};//v3
  int n = 1;
  while(n*2<=x){
    GaussType v2n = {0,0,0};
    GaussType v2nPlusUn = {0,0,0};
    GaussMul(&v2n,quatre,vnPlusUn);
    GaussMul(&tmp,deux,vn);
    GaussSoustrait(&v2n,v2n,tmp);
    GaussMul(&v2n,v2n,vn);
    GaussMul(&tmp,vnPlusUn,vnPlusUn);
    GaussMul(&v2nPlusUn,vn,vn);
    GaussAdd(&v2nPlusUn,v2nPlusUn,tmp);
    GaussMul(&v2nPlusUn,v2nPlusUn,deux);
    vn = v2n;
    vnPlusUn = v2nPlusUn;
    n = n*2;
  }
  while(n < x){
    tmp = vnPlusUn;
    GaussAdd(&vnPlusUn,vn,vnPlusUn);
    vn = tmp;
    n++;
  }
  GaussMul(&vn,vn,deux);
  return (vn.a/vn.d);
}
int main(){
  for(int i = 1 ; i < 22; i++){
    printf("%d ",Fibonacci1(i));
  }
  for(int i = 1 ; i < 22; i++){
    printf("%d ",Fibonacci2(i));
  }
  printf("\n");
}
