#include<iostream>
#include<string>
#include<vector>

struct Contact {
    std::string name;
    std::string phone;
};

void addVerified(std::vector<Contact>& contacts){
    std::cout << "\n Verified List: \n";
    for (auto& contact : contacts){
        contact.name += "(verified)";
    }
    for (const auto& contact:contacts){
        std::cout << contact.name << "-" << contact.phone << "\n";
    }
}
void copiedContacts(std::vector<Contact>& contacts){
    std::cout << "\n Copied List: \n";
    for (auto& contact : contacts){
        contact.name = "ANON";
    }
    for (const auto& contact:contacts){
        std::cout << contact.name << " - " << contact.phone << "\n";
    }

}

int main(){
    std::vector<Contact> contacts = {
        {"Alice", "123"},
        {"Bob", "456"},
        {"Carl", "789"}
    };
    addVerified(contacts);
    copiedContacts(contacts);
}