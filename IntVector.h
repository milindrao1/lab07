#ifndef INTVECTOR_H
#define INTVECTOR_H

#include <string>

class IntVector {
  // Container that provides random access to any element by an index.
  // An IntVector can hold arbitrarily many elements.

public:
  // No constructors here!  This is an abstract base class.

  // We do need a virtual destructor to ensure that whenever
  // delete is used on a pointer to any kind of IntVector, the
  // appropriate polymorphic destructor is called.
  virtual ~IntVector() { };

  //MODIFIES: this IntVector
  //EFFECTS:  Adds value to the end of this IntVector.
  virtual void push_back(int value) = 0;

  //REQUIRES: this IntVector is not empty
  //MODIFIES: this IntVector
  //EFFECTS:  Removes the last element in this IntVector.
  virtual void pop_back() = 0;

  //REQUIRES: 0 <= index < number of elements in this IntVector
  //EFFECTS:  Returns (by reference) the element at the given index.
  virtual int &at(int index) = 0;

  //REQUIRES: 0 <= index < number of elements in this IntVector
  //EFFECTS:  Returns (by reference) the element at the given index.
  virtual const int &at(int index) const = 0;

  //REQUIRES: 0 <= index < number of elements in this IntVector
  //EFFECTS:  Returns (by reference) the element at the given index.
  int &operator[](int index);

  //REQUIRES: 0 <= index < number of elements in this IntVector
  //EFFECTS:  Returns (by reference) the element at the given index.
  const int &operator[](int index) const;

  //EFFECTS:  Returns the number of elements of this IntVector.
  virtual int size() const = 0;

  //EFFECTS:  Returns true if this IntVector is empty, false otherwise.
  virtual bool empty() const = 0;

  //EFFECTS:  Prints to os all elements in this IntVector in the format:
  //          "[ 1, 2, 3, 4, 5 ]" (Note that there is no trailing newline)
  virtual void print(std::ostream &os) const = 0;
};

//EFFECTS:  Prints to os all elements in the IntVector in the format:
//          "[ 1, 2, 3, 4, 5 ]" (Note that there is no trailing newline)
std::ostream &operator<<(std::ostream &os, const IntVector &v);

//REQUIRES: kind == "array"
//EFFECTS:  returns a pointer to a dynamically allocated IntVector
//          of the given kind with the given initial capacity.
IntVector* IntVector_factory(const std::string &kind, int init_capacity);

#endif
