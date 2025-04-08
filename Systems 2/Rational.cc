#include <iostream>
#include "Rational.h"

Rational::Rational() {
    num = 1;
    dem = 1;
  }
Rational::Rational(int n) {
    num = n;
    dem = 1;
  }
Rational::Rational(int num, int dem) {
  this->num = num;
  this->dem = dem;
}

// Copy constr
Rational::Rational(const Rational& r) {
  this->num = r.num;
  this->dem = r.dem;
  std::cout << "cpy con\n";
}

//Similar to copy constr, except for:
// return value to chain assignment and
// deletion of old data to prevent potential memory leaks (not an issue with 2 ints in this example)
Rational& Rational::operator=(const Rational& r) {
  this->num = r.num;
  this->dem = r.dem;
  std::cout << "assign\n";

  return *this;
}

Rational* Rational::mult(const Rational& r) const {
  Rational* nr = new Rational(this->num * r.num, this->dem * r.dem);
  return nr;
}

Rational* Rational::operator*(const Rational& r) const {
  Rational* nr = new Rational(this->num * r.num, this->dem * r.dem);
  return nr;
}

Rational::~Rational() {
    std::cout << "Dest called\n";
}

bool Rational::operator==(const Rational& r) const {
  return ((this->num == r.num) && (this->dem == r.dem));
}

void Rational::display() {
    std::cout << num << "/" << dem << "\n";
}

std::ostream& operator<<(std::ostream& os, const Rational& r) {
    os << r.num << "/" << r.dem;
    return os;
}


