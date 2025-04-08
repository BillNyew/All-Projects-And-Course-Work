#include <iostream>
#include <vector>
#include "Rational.h"

//void foo(Rational r) {
//}
//void foo(Rational& r) {
//}

int main() { 
  
  Rational* r1 = new Rational(5, 3);
  //  r1->display();

  //Rational r2;  // Note no () for default on runtime stack
  Rational r2(5, 3);
  //  r2.display();

  Rational* r4 = new Rational(5, 8);

  //  foo(*r1);

  //Rational* r3 = new Rational(r2);
  //  Rational* r3 = r1->mult(&r2);
  //  Rational* r3 = r1->mult(r4);
  Rational* r3 = *r1 * *r4;  // r1.operator*(r4);

  //  Rational* r3 = r2 * r2;  // r1.operator*(r4);

  if (r2 == *r1) {
    std::cout << "Rationals equal\n";
  } else {
    std::cout << "Rationals NOT equal\n";
  }

  std::cout << "testing of assignment\n";
  Rational r5 = r2;  //  r5(r2)  <-- copy constr since making new one
  r5 = *r1;  // r5.operator=(*r1)

  std::cout << "display test\n";
  r3->display();
  std::cout << r2 << "\n";
  //  std::cout.operator<<(r2);   (1)
  //  operator<<(std::cout, r2);   (2)

  // Make a list of Rationals
  std::cout << "List testing\n";

  // I would personally make it a vector of Rational*
  //  to avoid all the copies
  std::vector<Rational> ratRS;  // default constr
  std::cout << " adding 1\n";
  ratRS.push_back(r2);  // Put a copy of r2 on vector
  std::cout << " adding 2\n";
  ratRS.push_back(*r4);
  std::cout << " adding 3\n";
  ratRS.push_back(r2);
  

  std::cout << "List loop testing\n";
  // Standard loop
  for (int i=0; i<ratRS.size(); i++) {
   
    //Rational r7 = ratRS.at(i);  // r7 is a copy
    Rational r7 = ratRS[i];  // [] has been overloaded to work on vectors
    std::cout << r7 << "\n";
  }

  std::cout << "List iterator testing\n";
  // Iterators
  // i is a iterator wrapper around a pointer to the Rational
  // If you deference it, you get the Rational
  // auto is much better than trying to remember the actual name
  //for (std::__wrap_iter<Rational*> i=ratRS.begin(); i!=ratRS.end(); i++) {
  for (auto i=ratRS.begin(); i!=ratRS.end(); i++) {
    std::cout << *i << "\n";
  }
  
  std::cout << "deleting\n";
  delete r1;
  //delete r2;  // NO
}
