#include <iostream>
#include <memory>
#include <string>

struct Contact {
    std::string name;
    Contact(const std::string& n) : name(n) {
        std::cout << "📦 Created: " << name << "\n";
    }
    ~Contact() {
        std::cout << "💥 Destroyed: " << name << "\n";
    }
};

int main() {
    std::shared_ptr<Contact> ownerA = std::make_shared<Contact>("Alice");
    std::weak_ptr<Contact> observer = ownerA;

    std::cout << "Ref count: " << ownerA.use_count() << "\n";

    if (auto locked = observer.lock()) {
        std::cout << "Observer sees: " << locked->name << "\n";
    }

    ownerA.reset();

    if (auto locked = observer.lock()) {
        std::cout << "Observer sees: " << locked->name << "\n";
    } else {
        std::cout << "Observer sees: [expired]\n";
    }
}