#include <iostream>
using namespace std;

struct A{
    int my_value;

    A(int v){
        cerr << "A [" << this << "]" << " ctor" << endl;
        my_value=v;
    }

    ~A(){
        cerr << "A [" << this << "]" << " dtor" << endl;
    }

    void print() {
        cerr << "A::print() [" << this << "]: my_value=" << my_value << endl;
    }
};


struct B: public A{ //B inherits all the elements of A and has the other value
    int my_other_value;

    /*Writing
        B(){
            my_other_value = -1;
        }
    would be an error cause A doesn't have a default constructor, so A would not be initialized.
    Since A doesn't have a default constructor, we have to use the initialization list, which has this syntax:
        ClassName(args) : member1(value1), member2(value2), ... {
            corpo del costruttore
        }
    */
    B(): A(0), my_other_value(-1){ //calls the constructor of the base class (like super in java) and sets the other value with -1
            cerr << "B [ " << this << "] ctor " << endl;
    }

    ~B(){
        cerr << "B [" << this << "]" << " dtor" << endl;
    }

    void print(){
        A::print(); //calls method of the base class using scoping <classname>::<method_or_variable> AND overrides it
        cerr << "B::print() [" << this << "]: my_other_value=" << my_other_value << endl;
    }

};

int main(int argc, char** argv) {
    for (int i=0; i<argc; ++i) {
        cerr << i << ":" << argv[i] << endl;
    }
    
    cerr << endl;
    cerr << "create A " << endl;
    A a(3);
    a.print();
    
    cerr << "create B " << endl;
    B b;
    b.print();

    A a1=b; //legal assignment a is base class of b, only common member vars are copied -> b identity is lost -> object slicing
    a1.print();
}

