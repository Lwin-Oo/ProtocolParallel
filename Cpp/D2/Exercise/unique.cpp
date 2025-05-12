#include<iostream>
#include<memory> //smart pointers live here
#include<string>

struct Contact{
    std::string name;
    std::string phone;

    // Constructor
    Contact(const std::string& n, const std::string& p) : name(n), phone(p){
        std::cout << "Contact Created: " << name << "\n";
    }

    // Destructor
    ~Contact(){
        std::cout << "Contact Destroyed: " << name << "\n";
    }
};

int main(){
    // Giving ownership to A
    std::unique_ptr<Contact> ownerA = std::make_unique<Contact>("Alice", "123");
    std::cout << "Owner A has: " << ownerA->name << "\n";

    //Transfer ownership to B
    std::unique_ptr<Contact> ownerB = std::move(ownerA);

    std::cout << "Owner A now has: " << (ownerA ? ownerA->name : "nothing") << "\n";
    std::cout << "Owner B has: " << ownerB->name << "\n";

    // Contact will be destroyed here when ownerB goes out of scope
}