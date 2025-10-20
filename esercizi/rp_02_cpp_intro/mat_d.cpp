#include <iostream>
#include <cmath>
#include <cassert>
#include "vec_f.cpp"
using namespace std;

struct MatD{
    int cols, rows;
    float *values;

    float get(int r, int c){
        return this->values[r*this->cols+c];
    }

    void set(int r, int c, float value){
        if (r<= this->rows-1 && c<=this->cols-1){
            this->values[r*this->cols+c] = value;
        }
        else{
            cout << "Error in indicating dimensions" << endl;
        }
    }

    MatD(){ //default constructor
        rows = 0;
        cols = 0;
        values = nullptr;
    }

    MatD(int r, int c){ //constructor with args
        rows = r;
        cols = c;
        values = new float[r*c];
    }

    MatD(const MatD& other){ //copy constructor
        MatD(other.rows, other.cols);
        int size = rows*cols;
        for (int i=0; i<size; i++){
            values[i] = other.values[i];
        }
    }

    ~MatD(){ //destructor
        if (!values) return;
        delete [] values;
    }

    MatD& operator=(const MatD& other){ //overloading of = operator
        if (values) delete [] values;
        rows = 0;
        cols = 0;
        if (!other.values) return *this;
        rows = other.rows;
        cols = other.cols;
        int size = rows*cols;
        values = new float[size];
        for (int i=0; i<size; i++){
            values[i] = other.values[i];
        }
        return *this;
    }

    MatD operator+(const MatD& other){ //addition
        MatD result(*this);
        int size = result.rows*result.cols;
        for (int i=0; i<size; i++){
            result.values[i] += other.values[i];
        }
        return result;
    }

    MatD operator-(const MatD& other){ //subtraction
        MatD result(*this);
        int size = result.rows*result.cols;
        for (int i=0; i<size; i++){
            result.values[i] -= other.values[i];
        }
        return result;
    }

    MatD operator*(float scalar){ //multiplication by scalar
        MatD result(*this);
        int size = result.rows*result.cols;
        for (int i=0; i<size; i++){
            result.values[i] *= scalar;
        }
        return result;
    }

    VecF operator*(const VecF& vector){ //multiplication by vector -> matrix * vector (supposing the vector is a column)
        VecF result(this->rows);
        if (vector.dim != this->cols){
            cout << "The dimensions must be compatible" << endl;
        }
        else{
            int size = this->rows*this->cols;
            for (int i=0; i <rows; ++i) {
                float sum=0;
                for (int j=0; j < cols; ++j) {
                    sum += this->values[i*cols+j] * vector.v[j];
                }
                result.v[i] = sum;
            }
        }
        return result;
    }

    MatD operator*(const MatD& other){ //multiplication by matrix
        MatD result(this->rows, other.cols);
        if (this->cols != other.rows){
            cout << "the dimensions must be compatible" << endl;
        }
        else{
            for (int i=0; i<this->rows; i++) {
                for (int j=0; j<other.cols; j++) {
                    float sum = 0;
                    for (int k=0; k <this->cols; k++) {
                        sum += this->values[i*this->cols+k] * other.values[k*other.cols+j];
                    }
                    result.values[i*result.cols+j]=sum;
                }
            }
        }
        return result;
    }

    void print(){
        cout << "[";
        for (int i=0; i<this->rows*this->cols; ++i) {
            if (i != this->rows*this->cols-1){
                cout << this->values[i] << " ";
            }
            else{
                cout << this->values[i];
            }
        }
        cout << "]" << endl;
    }
};

int main(int argc, char** argv){
    MatD mat(2, 2);
    mat.set(0, 0, 1);
    mat.set(0, 1, 2);
    //mat.set(2, 2, 4); //should give an error
    mat.set(1, 1, 4);
    cout << "Matrix" << endl;
    mat.print();
    VecF v1(5); //initializing a vector of 5 elements
    v1.set(0, 1);
    v1.set(1, 2);
    cout << "Vector v1:" << endl;
    v1.print();
    VecF v2(5);
    v2.set(0, 1);
    v2.set(1, 2);
    v2.set(2, 3);
    v2.set(3, 4);
    v2.set(4, 5);
    cout << "Vector v2:" << endl;
    v2.print();
    VecF v3 = v1 + v2;
    cout << "Vector v3 defined as v1+v2:" << endl;
    v3.print();
    VecF v4 = v2-v1;
    cout << "Vector v4 defined as v2-v1:" << endl;
    v4.print();
    VecF v5 = v1*3;
    cout << "Vector v5 defined as v1*3:" << endl;
    v5.print();
    float dot_product = v1.dot_product(v2);
    cout << "Dot product between v1 and v2: " << dot_product << endl;
    return 0;
}