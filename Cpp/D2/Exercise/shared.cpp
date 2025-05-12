#include<iostream>
#include<string>
#include<memory>

struct Contact{
    std::string name;
    std::string phone;

    // Constructor
    Contact(const std::string& n, const std::string& p) : name(n), phone(p){
        std::cout << "Contact Created: " << name << "\n";
    }

    //Destructor
    ~Contact(){
        std::cout << "Contact Destroyed: " << name << "\n";
    }
};

int main(){
    std::shared_ptr<Contact> ownerA = std::make_shared<Contact>("Alice", "123");
    {
        std::shared_ptr<Contact>ownerB = ownerA;
        std::cout << "Ref count: " << ownerA.use_count() << "\n"; // 2
    }
    std::cout << "Ref count: " << ownerA.use_count() << "\n"; // 1
}; // object destroyed here
