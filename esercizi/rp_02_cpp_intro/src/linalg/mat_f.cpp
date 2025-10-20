#include "mat_f.h"
#include <assert.h>
#include <iostream>

using namespace std;

//default ctor
MatF::MatF():
  rows(0),
  cols(0),
  dimension(0),
  v(nullptr){}

// ctor with dim
MatF::MatF(int rows_, int cols_):
  rows(rows_),
  cols(cols_),
  dimension(rows*cols),
  v(new float[dimension]){}

// copy ctor
MatF::MatF(const MatF& other):
  MatF(other.rows, other.cols){
  for (int i=0; i<dimension; ++i)
    v[i]=other.v[i];
}

// dtor
MatF::~MatF() {
  if (dimension)
    delete [] v;
}

void MatF::fill(float f) {
  for (int i=0; i<dimension; ++i)
    v[i]=f;
}

void MatF::randFill() {
  for (int i=0; i<dimension; ++i)
    v[i]=drand48();
}

// read/write access to element at pos
float& MatF::at(int pos) {
  return v[pos];
}
  
// read access to element at pos
// const after () means that the method does not modify the invoking object
const float& MatF::at(int pos) const {
  return v[pos];
}

// read/write access to element at pos
float& MatF::at(int r, int c) {
  return v[r*cols+c];
}
  
// read access to element at pos
// const after () means that the method does not modify the invoking object
const float& MatF::at(int r, int c) const {
  return v[r*cols+c];
}

// op =, deep copy
MatF& MatF::operator =(const MatF& other) {
  if (this->v) delete [] v;
  this->rows = 0;
  this->cols = 0;
  if (!other.v) return *this;

  this->rows = other.rows;
  this->cols = other.cols;
  int size = this->rows*this->cols;
  this->v = new float[size];
  for (int i=0; i<size; i++){
    this->v[i] = other.v[i];
  }
  return *this;
}

// returns the sum this + other
MatF MatF::operator +(const MatF& other) const {
  assert (other.cols==cols && other.rows==rows && "dim mismatch");
  MatF returned (*this);

  int size = this->cols*this->rows;
  for (int i=0; i<size; i++){
    returned.v[i] += other.v[i];
  }

  return returned;
}

// returns the difference this - other
MatF MatF::operator -(const MatF& other) const {
  assert (other.cols==cols && other.rows==rows && "dim mismatch");
  MatF returned (*this);

  int size = this->cols*this->rows;
  for (int i=0; i<size; i++){
    returned.v[i] -= other.v[i];
  }

  return returned;

}  

// returns this*f
MatF MatF::operator* (float f) const {
  MatF returned (*this);

  int size = this->cols*this->rows;
  for (int i=0; i<size; i++){
    returned.v[i] *= f;
  }

  return returned;
}
// returns this * other
VecF MatF::operator *(const VecF& other) const {
  assert(other.dim==cols && "dim mismatch");
  VecF returned (rows);
  int size = this->rows*this->cols;
  for (int i=0; i <rows; ++i) {
    float sum=0;
      for (int j=0; j < cols; ++j) {
        sum += this->v[i*cols+j] * other.v[j];
      }
      returned.v[i] = sum;
  }
  return returned;
}

// returns this* other
MatF MatF::operator *(const MatF& other) const {
  assert(cols==other.rows && "dimension mismatch");
  MatF returned(rows, other.cols);
  for (int i=0; i<this->rows; i++){
    for (int j=0; j<other.cols; j++) {
      float sum = 0;
      for (int k=0; k <this->cols; k++) {
        sum += this->v[i*this->cols+k] * other.v[k*other.cols+j];
      }
      returned.v[i*returned.cols+j]=sum;
    }
  }
  return returned;
}

MatF MatF::transpose() const {
  MatF returned(cols, rows);
  for (int r=0; r<rows; ++r)
    for (int c=0; c<cols; ++c)
      returned.at(c,r)=at(r,c);
  return returned;
}


std::ostream& operator <<(std::ostream& os, const MatF& m) {
  os << "{ ptr: " << &m <<", rows: " << m.rows << ",  cols: " << m.cols << endl;
  os << "  values:[ " << endl;
  for (int r=0; r<m.rows; ++r) {
    os << "\t";
    for (int c=0; c<m.cols; ++c) {
      os << m.at(r,c) <<  " ";
    }
    os << endl;
  }
  os << " ]" << endl << "}";
  return os;
}
