#include <iostream>
#include <cassert>
#include <string>

#include "IntVector.h"

using namespace std;

class ArrayIntVector : public IntVector {
  // An array based implementation of the IntVector interface.

public:
  //EFFECTS: Creates an empty ArrayIntVector with the specified
  //         initial data capacity, or with the default.
  ArrayIntVector(int init_capacity) : capacity(init_capacity), num_elts(0) {
    data = new int[capacity];
    check_invariants();
  }

  // Destructor
  virtual ~ArrayIntVector() {
    // TASK 2 - YOUR CODE HERE
  }

  //MODIFIES: this IntVector
  //EFFECTS:  Adds value to the end of this IntVector.
  virtual void push_back(int value) {
     check_invariants();

    if (num_elts == capacity) {
          grow();
      }

    data[num_elts++] = value;

    check_invariants();
  }

  //REQUIRES: this IntVector is not empty
  //MODIFIES: this IntVector
  //EFFECTS:  Removes the last element in this IntVector.
  virtual void pop_back() {
    check_invariants();
    assert(!empty());

    --num_elts;

    check_invariants();
  }

  //REQUIRES: 0 <= index < number of elements in this IntVector
  //EFFECTS:  Returns (by reference) the element at the given index.
  virtual int & at(int index) {
    check_invariants();
    assert(0 <= index && index <= size());
    return data[index];
  }

  //REQUIRES: 0 <= index < number of elements in this IntVector
  //EFFECTS:  Returns (by reference) the element at the given index.
  virtual const int & at(int index) const {
    assert(0 <= index && index <= size());
    return data[index];
  }

  //EFFECTS:  Returns the number of elements of this IntVector.
  virtual int size() const {
    return num_elts;
  }

  //EFFECTS:  Returns true if this IntVector is empty, false otherwise.
  virtual bool empty() const {
    return num_elts == 0;
  }

  //EFFECTS:  Prints to os all elements in this IntVector in the format:
  //          "[ 1, 2, 3, 4, 5 ]" (Note that there is no trailing newline)
  virtual void print(std::ostream &os) const {
    os << "[ ";
    for (int i = 0; i < num_elts; i++) {
      os << data[i];
      if (i < num_elts - 1) {
        os << ", ";
      }
    }
    os << " ]";
  }

private:
  // EFFECTS: Doubles the storage capacity of this ArrayIntVector.
  //          More precisely:
  //            1. doubles capacity
  //            2. allocates a new dynamic array with the new capacity
  //            3. copies over the elements from the old data array
  //            4. free the memory for the old data array
  //            5. sets data to point to the new array
  void grow() {
    check_invariants();
      int * ptr = new int[capacity * 2];
      for (int i = 0; i < num_elts; ++i) {
          ptr[i] = data[i];
      }
      delete[] data;
      data = ptr;
      capacity = capacity * 2;
      
    check_invariants();
    cout << "grow() was called. Capacity is now " << capacity << "." << endl;
  }

  // A pointer to an (dynamically allocated) array to hold the N elements
  // stored in this vector, in the first N slots. If the number of elements
  // exceeds its current capacity, data will be reallocated.
  // INVARIANT: data != nullptr (it is a valid pointer)
  int *data;

  // The maximum number of elements data can currently hold.
  // INVARIANT: 0 <= capacity
  int capacity;

  // The number of elements in the IntVector.
  // INVARIANT: 0 <= num_elts <= capacity
  int num_elts;

  // EFFECTS: Contains asserts that fail if the representation
  //          invariants do not hold.
  void check_invariants() const {
    assert(0 <= num_elts && num_elts <= capacity);
    assert(0 <= capacity);
    assert(data);
  }
};

//REQUIRES: kind == "array"
//EFFECTS:  returns a pointer to a dynamically allocated IntVector
//          of the given kind with the given initial capacity.
IntVector * IntVector_factory(const string &kind, int init_capacity) {
  if (kind == "array") {
    return new ArrayIntVector(init_capacity);
  }
  assert(false); // No other kinds of IntVectors exist
}

// Equivalent to calling the at function
//REQUIRES: 0 <= index < number of elements in this IntVector
//EFFECTS:  Returns (by reference) the element at the given index.
int & IntVector::operator[](int index) {
  return at(index);
}

// Equivalent to calling the at function
//REQUIRES: 0 <= index < number of elements in this IntVector
//EFFECTS:  Returns (by reference) the element at the given index.
const int & IntVector::operator[](int index) const {
  return at(index);
}

// Equivalent to calling v.print(os);
//EFFECTS:  Prints to os all elements in the IntVector in the format:
//          "[ 1, 2, 3, 4, 5 ]" (Note that there is no trailing newline)
std::ostream &operator<<(std::ostream &os, const IntVector &v) {
  v.print(os);
  return os;
}
