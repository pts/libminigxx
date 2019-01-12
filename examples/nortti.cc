#include <stdio.h>

class C {
 public:
  C() { puts("+C"); }
  ~C() { puts("-C"); }
  virtual void F() = 0;
};

class D : public C {
 public:
  D() { puts("+D"); }
  D(int) { puts("+D0"); }
  D(bool) { puts("+D?"); }
  virtual ~D() { puts("-D"); }
  virtual void F() {}
};

D global_d(true);

int main(int, char **) {
  D d(-1);
  D *p = new D(-2);
  delete p;
  D *a = new D[2];
  a->F();  /* Adds dependency to __cxa_pure_virtual. */
  delete [] a;
  return 0;
}
  