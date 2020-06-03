#include <iostream>
#include <utility>

struct A {
    int i;
    int j;
    int* p;
    
    A() {
        p = new int(10);
        std::cout << "Default constructor of A" << std::endl;
    }

    A(const A& a)
      : i(a.i)
      , j(a.j)
      , p(new int(*a.p)) {
        std::cout << "Copy constructor of A" << std::endl;
    }

    A(A&& a)
      : i(std::exchange(a.i, 0))
      , j(std::exchange(a.j, 0))
      , p(std::exchange(a.p, nullptr)) {
        std::cout << "Move constructor of A" << std::endl;
    }

    A& operator=(A&& a) {
        i = std::exchange(a.i, 0);
        j = std::exchange(a.j, 0);
        p = std::exchange(a.p, nullptr);
        std::cout << "Move assignment of A" << std::endl;
        return *this;
    }

    ~A() {
        std::cout << "A is being destroyed" << std::endl;
        delete p;
    }
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

    int getValue() const { return mValue; }

private:
    const int mValue;
    int j{20}; // default member initializer
};

int main() {
    A* pa = new A(); // new object
    pa->i = 1;
    pa->j = 2;

    A a(*pa); // copy constructor
    A a1{std::move(a)}; // move constructor

    B* pb = new B();

    std::cout << "a->i = " << pa->i << ", a->j = " << pa->j << std::endl;
    std::cout << "b->i = " << pb->i << ", b->j = " << pb->j << std::endl;
    delete pa;
    delete pb;

    //C c{2.5f}; // error! implicit conversion float -> int
    //C c = 1; // error! implicit conversion isn't allowed
    C c{10};
    std::cout << "c = " << c.getValue() << std::endl;

    return 0;
}
