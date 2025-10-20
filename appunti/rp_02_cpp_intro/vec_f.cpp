#include <iostream>
using namespace std;
#pragma once

struct VecF{
    int dim;
    float *v;

    float get(int pos){
        return v[pos];
    }

    void set(int pos, float value){
        v[pos] = value;
    }

    VecF(){ //default constructor
        dim = 0;
        v = nullptr;
    }

    VecF(int size){ //constructor with args that overrides the default one
        this->dim = size;
        this->v = new float[size]; //declaration with "new" -> dynamic allocation
    }

    VecF(const VecF& other){ //copy constructor
        dim = 0;
        v = nullptr;
        if (!other.dim) return;
        dim = other.dim;
        v = new float[dim];
        for (int i=0; i<dim; i++){
            v[i] = other.v[i];
        }
    }

    ~VecF(){ //destructor -> automatically called when the life cycle of the object ends
        if (dim) delete [] v;
    }

    VecF& operator=(const VecF& other){ //overload of = operator
        if (dim){
            delete [] v;
        }
        dim = 0;
        v = nullptr;
        if (!other.dim){
            return *this;
        }
        dim = other.dim;
        v = new float[dim];
        for (int i=0; i<dim; i++){
            v[i] = other.v[i];
        }
        return *this;
    }

    VecF operator+(const VecF& src){
        VecF result(this->dim);
        /*I could have also initialized the resulting VecF as a copy of the current VecF,
        using the copy constructor:
            VecF result(*this)
        and then in the cycle i could have added just src.v[i]:
            result.v[i] += src.v[i]*/
        for (int i=0; i<this->dim; i++){
            result.v[i] = this->v[i] + src.v[i];
        }
        return result;
    }

    VecF operator-(const VecF& second_member){
        VecF result(*this);
        for (int i=0; i<this->dim; i++){
            result.v[i] -= second_member.v[i];
        }
        return result;
    }

    VecF operator*(const float scalar){
        VecF result(*this);
        for (int i=0; i<this->dim; i++){
            result.v[i] = result.v[i]*scalar;
        }
        return result;
    }

    float dot_product(const VecF& vec2){
        float result = 0;
        if (this->dim != vec2.dim){
            cout << "Vectors must have the same size" << endl;
        }
        else{
            for (int i=0; i<this->dim; i++){
                result += this->v[i]*vec2.v[i];
            }
        }
        return result;
    }

    void print(){
        cout << "[";
        for (int i=0; i<dim; ++i) {
            if (i != dim-1){
                cout << v[i] << " ";
            }
            else{
                cout << v[i];
            }
        }
        cout << "]" << endl;
    }
};