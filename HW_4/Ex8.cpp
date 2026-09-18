#include <string>
#include <iostream>
#include <utility>

//------------------------------------------------CLASS DEFINITIONS---------------------------------------------
class Person {
public:
    Person(const char *name = "nobody");
    virtual ~Person() = default;
    virtual void identity() const;
    virtual void interrogate();

private:
    std::string name;
};

class Spy:public Person {
public:
    Spy(const std::string& name,std::string alias, int resistance) ;

    void set_identity(const char *alias) {
        this->alias = alias;
    };
    void identity() const override { // changes the identity based on if the resitance of the spy is above 0.
        if (resistance > 0) {
            std::cout << "My name is: " << alias << std::endl;
        } else if ( resistance <= 0) {
            Person::identity();
            std::cout <<"My alias is: " << alias << std::endl;
        }
    }
    void interrogate() override{
        Person::interrogate();
        resistance = resistance -1;
    }

private:
    std::string alias;
    int resistance;
};
//----------------------------------------------------CLASS METHODS ETC.-------------------------------------------
void Person::identity() const{
    std::cout << "My name is: " << name << std::endl;
}
Person::Person(const char *name) {
    this->name = name;
}
void Person::interrogate() { }

Spy::Spy(const std::string& name,std::string alias, int resistance) : Person(name.c_str()) {
    this-> alias = std::move(alias);
    this->resistance = resistance;
}

//------------------------------------------------------------MAIN----------------------------------------------------
int main(int argc, char** argv) {
    Person agent("James Bond");
    Spy spy("Emilio Largo", "William Johnson", 3);
    Spy spy2("Ernst Blofield", "John Keats", 5);
    std::cout << std::endl << "Nice to meet you. ";
    agent.identity();
    for (int i = 0; i < 6; ++i) {
        std::cout << "Who are you?" << std::endl;
        spy.interrogate();
        spy.identity();
    }
    spy.set_identity("Bill Munny");
    spy.identity();
    std::cout << std::endl << "Nice to meet you. ";
    agent.identity();
    for (int i = 0; i < 6; ++i) {
        std::cout << "Who are you?" << std::endl;
        spy2.interrogate();
        spy2.identity();
    }
    return 0;
}