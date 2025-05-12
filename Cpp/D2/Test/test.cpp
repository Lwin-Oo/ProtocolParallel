#include<iostream>
#include<string>
#include<memory>

struct Contact{
    std::string name;
    std::string phone;

    // Constructor
    Contact(const std::string& n, const std::string& p) : name(n), phone(p){
        std::cout << "📦 Contact Created: " << name << "\n";
    }
    // Destructor
    ~Contact(){
        std::cout << "💥 Contact Destroyed: " << name << "\n";
    }
};

void displayContacts(const std::vector<std::unique_ptr<Contact>> & contacts){
    std::cout << "\n Contact List: \n";
    for (const auto& c : contacts){
        std:: cout << "-" << c->name << "(" << c->phone << ")"; // take out back from pointer
    }
};

int main(){
    std:: vector<std::unique_ptr<Contact>> contacts;

    while(true){
        std::cout << "\n[1] Add Contact\n[2] Show All \n[3] Exit\n>";
        int choice;
        std::cin >> choice;

        if (choice == 1){
            std::string name, phone;
            std::cout << "Enter name (no space): ";
            std::cin >> name;
            std::cout << "Enter phone: ";
            std::cin >> phone;

            // use make_unique to construct on heap
            contacts.push_back(std::make_unique<Contact>(name, phone));

        } else if (choice == 2){
            displayContacts(contacts);
        } else if (choice == 3){
            std::cout << "Exiting ContactBook++...\n";
            break;
        }else {
            std::cout << "X Invalid Option.\n";
        }
    }
    return 0;
}