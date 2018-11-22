#include <iostream>

struct A {
    A() { p = new int(10); }
    ~A() { delete p; }

    int i;
    int j;
    int* p;
};

struct B {
    B() = default;
    ~B() = default;

    int i;
    int j;
};

class C {
public:
    C() = delete;
    //C(int i) { mValue = i; } // error!
    explicit C(int i)
     : mValue(i) {} // member initializer list

private:
    const int mValue;
    int j{20}; // default member initializer
};

int main() {
    for(int i = 0; i < 100; ++i) {
        A* pa = new A();
        B* pb = new B();
        //C c{2.5}; // error! implicit conversion float -> int
        C c{10};
        std::cout << "a->i = " << pa->i << ", a->j = " << pa->j << std::endl;
        std::cout << "b->i = " << pb->i << ", b->j = " << pb->j << std::endl;
        delete pa;
        delete pb;
    }

    return 0;
}
