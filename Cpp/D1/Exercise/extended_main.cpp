#include<iostream>
#include<vector>
#include<string>

struct Contact {
    std::string name;
    std::string phone;
    std::string email;
};

void displayContacts(const std::vector<Contact> & contacts){
    std::cout << "\n Contact List: \n";
    for ( const auto& contact : contacts){
        std:: cout << "-" << contact.name << "(" << contact.phone << ")\n" << contact.email;
    }

}

int main(){
    std:: vector<Contact> contacts;

    while(true){
        std::cout << "\n[1] Add Contact\n[2] Show All \n[3] Exit\n> ";
        int choice;
        std::cin >> choice;
        
        if ( choice == 1){
            Contact c;
            std::cout << "Enter name: ";
            std::cin >> c.name;
            std::cout << "Enter Phone: ";
            std::cin >> c.phone;
            std::cout << "Enter email: ";
            std::cin >> c.email;
            contacts.push_back(c);
        } else if( choice == 2){
            displayContacts(contacts);
        } else if( choice == 3){
            std::cout << "Exiting ContactBook++...\n";
            break;
        } else {
            std::cout << "X Invalid Option.\n";
        }
    }
    return 0;
}