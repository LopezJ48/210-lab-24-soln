#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <vector>
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();
void count_goats_by_age(list<Goat> &trip);
void find_goat_by_name(list<Goat> &trip);
void display_youngest_oldest_goat(list<Goat> &trip);
void sort_goat_age(list<Goat> &trip);
void remove_goat_color(list<Goat> &trip);
void increase_age_of_goats(list<Goat> &trip);
void shuffle_goats(list<Goat> &trip);
void find_avg_age(list<Goat> &trip);

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 12) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4: 
            cout << "Counting by age.\n";
            count_goats_by_age(trip);
            break;
            case 5: 
            cout << "Find goat by name.\n";
            find_goat_by_name(trip);
            break;
            case 6: 
            cout << "show youngest to oldest goat.\n";
            display_youngest_oldest_goat(trip);
            break;
            case 7: 
            cout << "sort goats by age.\n";
            sort_goat_age(trip);
            break;
            case 8: 
            cout << "remove colors of goats.\n";
            remove_goat_color(trip);
            break;
            case 9: 
            cout << "increase age of goats.\n";
            increase_age_of_goats(trip);
            break;
            case 10: 
            cout << "shuffle the goats.\n";
            shuffle_goats(trip);
            break;
            case 11: 
            cout << "find the average age of goats.\n";
            find_avg_age(trip);
            break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] count goats by age\n";
    cout << "[5] Find goat by name\n";
    cout << "[6] show youngest to oldest goat\n";
    cout << "[7] sort goats by age\n";
    cout << "[8] remove colors of goats\n";
    cout << "[9] increase age of goats\n";
    cout << "[10] shuffle the goats\n";
    cout << "[11] find the average age of goats\n";
    cout << "[12] quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

void count_goats_by_age(list<Goat> &trip){
    int age;
    cout << "Enter an age to count: ";
    cin >> age;
    int count = count_if(trip.begin(),trip.end(),[age](Goat& g){return g.get_age() == age;});
    cout << "number of goats with age " << age << count << endl;
}

void find_goat_by_name(list<Goat> &trip){
    string name;
    cout << "Enter name: ";
    cin >> ws;
    getline(cin, name);
    auto it = find_if(trip.begin(), trip.end(), [name](Goat& g){return g.get_name() == name;});
    if (it != trip.end()) {
        cout << "found " << it -> get_name() << "," << it->get_age() << "," << it->get_color() << endl;
    } else{
        cout << "Goat not found.";
    }
}

void display_youngest_oldest_goat(list<Goat> &trip){
    auto youngest = min_element(trip.begin(), trip.end(), [](const Goat& a, const Goat& b){return a.get_age() < b.get_age();});
    auto oldest = max_element(trip.begin(), trip.end(), [](const Goat& a, const Goat& b){return a.get_age() < b.get_age();});
    cout << " youngest goat is: " << youngest -> get_name()<< youngest-> get_age();
    cout << "Oldest goat is: " << oldest -> get_name()<< oldest -> get_age();
}

void sort_goat_age(list<Goat> &trip){
    trip.sort([](const Goat& a, const Goat& b) {return a.get_age() < b.get_age(); });
    cout << "Goats have been sorted.";
}

void remove_goat_color(list<Goat> &trip){
    string color;
    cout << "Pick a color you want to remove: ";
    cin >> ws;
    getline(cin, color);
    trip.remove_if([color](const Goat& g){return g.get_color() == color; });
    cout << "The color " << color << "has been removed." << endl;
}

void increase_age_of_goats(list<Goat> &trip){
    for_each(trip.begin(), trip.end(),[](Goat& g){g.set_age(g.get_age() + 1); });
    cout << "Increased the goats age by 1";
}

void shuffle_goats(list<Goat> &trip){
vector<Goat> goatVector(trip.begin(),trip.end());
random_shuffle(goatVector.begin(),goatVector.end());
trip.assign(goatVector.begin(), goatVector.end());
cout << "Goats shuffled.";
}

void find_avg_age(list<Goat> &trip){
    int totalAge = accumulate(trip.begin(), trip.end(), 0, [](int sum, const Goat& g) {return sum + g.get_age(); });
    double averageAge = static_cast<double>(totalAge) / trip.size();
    cout << "Average age: " << fixed << setprecision(2) << averageAge << endl;
}