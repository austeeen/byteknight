#include <iostream>

class Base
{
public:
    Base(const std::string& name): base_name(name) {
        std::cout << "BASE " << base_name << " created" << std::endl;
    }
    ~Base() {
        std::cout << "BASE " << base_name << " destroyed" << std::endl;
    }

protected:
    const std::string base_name;
};

class Child: public Base
{
public:
    Child(const std::string& name): Base(name) {
        std::cout << "CHILD " << base_name << " created" << std::endl;
    }
};


class BaseTwo
{
public:
    BaseTwo(): basetwo_name("") {
        std::cout << "BASE TWO " << basetwo_name << " created" << std::endl;
    }
    virtual ~BaseTwo() {
        std::cout << "BASE TWO " << basetwo_name << " destroyed" << std::endl;
    }

protected:
    std::string basetwo_name;
};

class ChildTwo: public BaseTwo
{
public:
    ChildTwo(const std::string& name) {
        this->basetwo_name = name;
        std::cout << "CHILD TWO " << name << " created" << std::endl;
    }
    ~ChildTwo() {
        std::cout << "CHILD TWO " << basetwo_name << " destroyed" << std::endl;
    }
};

int main()
{
    Child* a = new Child("A");
    ChildTwo* b = new ChildTwo("B");

    delete a;
    delete b;
}
