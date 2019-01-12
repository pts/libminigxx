/*#include <typeinfo>*/
#include <stdio.h>
#include <stdlib.h>

class C {
 public:
  C() { puts("+C"); }
  C(int) { puts("+C0"); }
  virtual ~C() { puts("-C"); }
};

class D : public C {
 public:
  D() { puts("+D"); }
  virtual ~D() { puts("-D"); }
};

class E : public C {
 public:
  E() { puts("+E"); }
  virtual ~E() { puts("-E"); }
};

void badcast(C *p) {
  E &r = dynamic_cast<E&>(*p);  /* Triggers __cxa_bad_cast. */
  (void)r;
}

int main(int, char **) {
  E e;
  /*puts(typeid(e).name());*/
  C *p = new D;
  D *q = dynamic_cast<D*>(p);
  if (p != q) abort();
  if (dynamic_cast<D*>((C*)&e)) abort();
  delete p;
  C *a = new D[2];
  delete [] a;
  return 0;
}
 