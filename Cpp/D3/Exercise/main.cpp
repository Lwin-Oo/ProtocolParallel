#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <algorithm>

// We construct the Contact
struct Contact {
    std::string name;
    std::string phone;
    std::string city;
}; // We group by city, and name + phone is the identity.

// Displaying all Contacts
void displayAllContacts(const std::map<std::string, std::vector<Contact>>& cityGroups){
    for (const auto& [city, people] : cityGroups) {
        std::cout << "\n\U0001f3d9️ " << city << ":\n";
        for (const auto& person : people) {
            std::cout << "- " << person.name << " (" << person.phone << ")\n";
        }
    }
    std::cout << "\n All contacts sorted by name within each city.\n";
}

// Sorting Contacts by Name
void sortContactsByName(std::map<std::string, std::vector<Contact>>& cityGroups){
    for (auto& [city, people] : cityGroups) {
        std::sort(people.begin(), people.end(), [](const Contact& a, const Contact& b) {
            return a.name < b.name;
        });
    }
    std::cout << "\n All contacts sorted by name within each city.\n";
}

// Searching by City
void searchCity(std::map<std::string, std::vector<Contact>>& cityGroups){
    std::string searchCity;
    std::cout << "Enter city to search: ";
    std::cin >> searchCity;

    if (cityGroups.count(searchCity)) {
        std::cout << "\n\U0001f50e People in " << searchCity << ":\n";
        for (const auto& person : cityGroups.at(searchCity)) {
            std::cout << "- " << person.name << " (" << person.phone << ")\n";
        }
    } else {
        std::cout << "⚠️ No contacts in this city.\n";
    }

}

// Counting by City
void countCity(const std::map<std::string, std::vector<Contact>>& cityGroups) {
    std::string targetCity;
    std::cout << "Count in city: ";
    std::cin >> targetCity;

    int count = cityGroups.count(targetCity) ? cityGroups.at(targetCity).size() : 0;
    std::cout << "Total contacts in " << targetCity << ": " << count << "\n";
}

int main(){
    // Declare Data Structures
    std::map<std::string, std::vector<Contact>>cityGroups; // We group ppl by city
    std::set<std::pair<std::string, std::string>>seen; // seen helps prevent duplicate entries (name, phone pair)

    while(true){
        std::cout << "\n[1] Add Contact\n[2] Show All\n[3] Sort by Name\n[4] Search City\n[5] Count City\n[6] Exit\n> ";
        int choice;
        if (!(std::cin >> choice)) {
            std::cout << "❌ Invalid input. Exiting...\n";
            break;
        }

        if(choice == 1){
            std::string name, phone, city;
            std::cout << "Enter name: "; std::cin >> name;
            std::cout << "Enter phone: "; std::cin >> phone;
            std::cout << "Enter city: "; std::cin >> city;

            // Prevent duplicates using seen set
            std::pair<std::string, std::string> identity = {name, phone};
            if (seen.count(identity) == 0) {
                cityGroups[city].push_back(Contact{name, phone, city});
                seen.insert(identity);
                std::cout << "✅ Contact added!\n";
            } else {
                std::cout << "⚠️ Contact already exists.\n";
            }
        }else if(choice == 2){
            std::cout << "Displaying Contacts (by City)...";
            displayAllContacts(cityGroups);
        }else if(choice == 3){
            std::cout << "Sorting Contacts by Name....\n";
            sortContactsByName(cityGroups);
            displayAllContacts(cityGroups);
        }else if(choice == 4){
            std::cout << "Searching Contacts by City....";
            searchCity(cityGroups);
        }else if(choice == 5){
            std::cout << "Counting Ppl by City....";
            countCity(cityGroups);
        }else if(choice == 6){
            std::cout << "Exiting Contact Group Manager++...\n";
            break;
        }else {
            std::cout << "Invalid Option.\n";
        }
    }
    return 0;
}


