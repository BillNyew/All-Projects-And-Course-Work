#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <stdbool.h>

class Rational {
private:
  int num;
  int dem;

public:
 
  Rational(); 
  Rational(int n);
  Rational(int n, int d);
  Rational(const Rational& r);

  ~Rational();

  Rational* mult(const Rational& r) const;
  Rational* operator*(const Rational& r) const;

  Rational& operator=(const Rational& r);

  bool operator==(const Rational& r) const;

  void display();
  friend std::ostream& operator<<(std::ostream& os, const Rational& r);

};

#endif
