//! SrC: https://stackoverflow.com/questions/8824587/what-is-the-purpose-of-the-final-keyword-in-c11-for-functions

// FIXME: tget this to compile

struct A {
    virtual int foo(); // #1 <-- note: if we changes "virtual" => "final" then a comiaon-error is raised at "struct B : A"
};
struct B : A {
    int foo();
};


/*    if you make a virtual method in base class as final, it cannot be overridden in the derived class. It will show a compilation error: */

class Base {
public:
    virtual void display() final  {
        cout << "from base" << endl;
    }
};
class Child : public Base {
public:
    void display() {
        cout << "from child" << endl;
    }
};
int main() {
    Base *b = new Child();
    b->display();
    cin.get();
    return 0;
}

/*    If we make a class as final, it cannot be inherited by its child classes: */

class _Base final {
public:
    void displayBase()   {
        cout << "from base" << endl;
    }
};
class _Child : public _Base {
public:
    void displayChild() {
        cout << "from child" << endl;
    }
};

