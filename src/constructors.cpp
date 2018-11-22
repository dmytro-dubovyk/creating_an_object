#include <iostream>
#include <utility>

struct A {
    int i;
    int j;
    int* p;
    
    A() { p = new int(10); }

    A(const A& a)
      : i(a.i), j(a.j), p(new int(*a.p)) { std::cout << "Copy constructor of A" << std::endl; }

    A(A&& a)
      : i(std::exchange(a.i, 0)), j(std::exchange(a.j, 0)), p(std::exchange(a.p, nullptr)) {
        std::cout << "Move constructor of A" << std::endl;
    }

    A& operator=(A&& a) {
        i = std::exchange(a.i, 0);
        j = std::exchange(a.j, 0);
        p = std::exchange(a.p, nullptr);
        return *this;
    }

    ~A() { delete p; }
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
        A a(*pa);
        A a1{std::move(a)};
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
