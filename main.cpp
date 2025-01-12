#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm> // For min/max
using namespace std;

// Function prototypes
int getChoice();

class Kitty {
private:
    string name;
    int happiness;
    int hunger;
    int energy;
    int cleanliness;
    int age;
    int level;
    int gardenCrops; // Number of crops in the garden
    int tomatoes;
    int carrots;
    int potatoes;
    string favoriteFood;
    string favoritePlay;

public:
    // Constructor
    Kitty(string kittyName)
        : name(kittyName), happiness(50), hunger(50), energy(50), cleanliness(50), age(1), level(1), gardenCrops(0),
          tomatoes(0), carrots(0), potatoes(0), favoriteFood("Salmon"), favoritePlay("Chasing a ball of yarn") {}

    // Display kitty status
    void displayStatus() {
        cout << "\n✨🐾 --- Kitty Status --- 🐾✨\n";
        cout << "Name: " << name << endl;
        cout << "Age: " << age << " years" << endl;
        cout << "Happiness: "; displayBar(happiness);
        cout << "Hunger: "; displayBar(hunger, false);
        cout << "Energy: "; displayBar(energy);
        cout << "Cleanliness: "; displayBar(cleanliness, false);
        cout << "Garden Crops: " << gardenCrops << " (Tomatoes: " << tomatoes << ", Carrots: " << carrots << ", Potatoes: " << potatoes << ")" << endl;
        cout << "Level: " << level << endl;
        cout << "Favorite Food: " << favoriteFood << endl;
        cout << "Favorite Activity: " << favoritePlay << endl;
        cout << "🐾✨💖🌟💖✨🐾\n";
    }

    // Display a status bar
    void displayBar(int value, bool showHearts = true) {
        int blocks = value / 10;
        for (int i = 0; i < blocks; i++) cout << "█";
        for (int i = blocks; i < 10; i++) cout << "░";
        if (showHearts) cout << " ❤️ (" << value << "/100)";
        else cout << " (" << value << "/100)";
        cout << endl;
    }

    // Feed the kitty
    void feed() {
        cout << "\n🍽️ What would you like to feed " << name << "?\n";
        cout << "1. Salmon (+20 Hunger, +15 Happiness)\n";
        cout << "2. Tuna (+15 Hunger, +10 Happiness)\n";
        cout << "3. Milk (+10 Hunger, +20 Happiness)\n";
        cout << "4. Gourmet Cat Treats (+30 Hunger, +30 Happiness)\n";
        cout << "5. Home-cooked meal from garden (+25 Hunger, +25 Happiness)\n";
        cout << "Choose an option: ";
        int choice = getChoice();

        switch (choice) {
        case 1:
            hunger = min(hunger + 20, 100);
            happiness = min(happiness + 15, 100);
            cout << name << " purrs happily while enjoying salmon!\n";
            break;
        case 2:
            hunger = min(hunger + 15, 100);
            happiness = min(happiness + 10, 100);
            cout << name << " devours the tuna and looks content!\n";
            break;
        case 3:
            hunger = min(hunger + 10, 100);
            happiness = min(happiness + 20, 100);
            cout << name << " laps up the milk with a delighted expression!\n";
            break;
        case 4:
            hunger = min(hunger + 30, 100);
            happiness = min(happiness + 30, 100);
            cout << name << " feels like royalty eating gourmet treats!\n";
            break;
        case 5:
            if (tomatoes > 0 && carrots > 0 && potatoes > 0) {
                tomatoes--;
                carrots--;
                potatoes--;
                hunger = min(hunger + 25, 100);
                happiness = min(happiness + 25, 100);
                cout << name << " enjoys a delicious home-cooked meal from fresh garden produce!\n";
            } else {
                cout << "Not enough garden produce to cook a meal. Plant and harvest more!\n";
            }
            break;
        default:
            cout << "Invalid choice. No food for now.\n";
        }
        cout << R"(
       /\_/\
      ( o.o )
      > ^ <
    )" << endl;
        checkLevelUp();
    }

    // Play with the kitty
    void play() {
        cout << "\n🎮 How would you like to play with " << name << "?\n";
        cout << "1. Chase a ball of yarn (+20 Happiness, -10 Energy)\n";
        cout << "2. Dress-up time (+30 Happiness, -15 Energy)\n";
        cout << "3. Laser pointer fun (+25 Happiness, -20 Energy)\n";
        cout << "Choose an option: ";
        int choice = getChoice();

        switch (choice) {
        case 1:
            energy = max(energy - 10, 0);
            happiness = min(happiness + 20, 100);
            cout << name << " is chasing the ball of yarn with endless energy!\n";
            break;
        case 2:
            energy = max(energy - 15, 0);
            happiness = min(happiness + 30, 100);
            cout << name << " looks adorable in their princess costume!\n";
            break;
        case 3:
            energy = max(energy - 20, 0);
            happiness = min(happiness + 25, 100);
            cout << name << " is bouncing around chasing the laser pointer light!\n";
            break;
        default:
            cout << "Invalid choice. No playtime for now.\n";
        }
        cout << R"(
       /\_/\
      ( ^_^ )
       > ^ <
    )" << endl;
        checkLevelUp();
    }

    // Bathe the kitty
    void bathe() {
        cout << "\n🚱 How would you like to bathe " << name << "?\n";
        cout << "1. Bubble bath (+30 Cleanliness, -15 Happiness)\n";
        cout << "2. Quick clean-up (+20 Cleanliness, -5 Happiness)\n";
        cout << "Choose an option: ";
        int choice = getChoice();

        switch (choice) {
        case 1:
            cleanliness = min(cleanliness + 30, 100);
            happiness = max(happiness - 15, 0);
            cout << name << " is squeaky clean but not thrilled about the bath!\n";
            break;
        case 2:
            cleanliness = min(cleanliness + 20, 100);
            happiness = max(happiness - 5, 0);
            cout << name << " tolerates the quick clean-up and looks refreshed.\n";
            break;
        default:
            cout << "Invalid choice. No bath for now.\n";
        }
        cout << R"(
       /\_/\
     ~( ^.^ )~
        > ^ <
    Bath time!
    )" << endl;
        checkLevelUp();
    }

    // Let the kitty sleep
    void sleep() {
        cout << "\n🛌 Where would you like " << name << " to sleep?\n";
        cout << "1. Cozy bed (+30 Energy, -10 Hunger)\n";
        cout << "2. Sunny nap spot (+20 Energy, +10 Happiness, -5 Hunger)\n";
        cout << "Choose an option: ";
        int choice = getChoice();

        switch (choice) {
        case 1:
            energy = min(energy + 30, 100);
            hunger = max(hunger - 10, 0);
            cout << name << " curls up in their cozy bed and purrs softly.\n";
            break;
        case 2:
            energy = min(energy + 20, 100);
            hunger = max(hunger - 5, 0);
            happiness = min(happiness + 10, 100);
            cout << name << " stretches out in the warm sunlight and naps peacefully.\n";
            break;
        default:
            cout << "Invalid choice. No nap for now.\n";
        }
        cout << R"(
       |\_/|  
      ( -.- ) Zzz...
      > ^ <
    )" << endl;
    }

    // Garden with the kitty
    void garden() {
        cout << "\n🌾 How would you like to garden with " << name << "?\n";
        cout << "1. Plant tomatoes (+2 Tomatoes, -10 Energy)\n";
        cout << "2. Plant carrots (+2 Carrots, -10 Energy)\n";
        cout << "3. Plant potatoes (+2 Potatoes, -10 Energy)\n";
        cout << "4. Harvest tomatoes (+1 Tomato, +5 Happiness)\n";
        cout << "5. Harvest carrots (+1 Carrot, +5 Happiness)\n";
        cout << "6. Harvest potatoes (+1 Potato, +5 Happiness)\n";
        cout << "Choose an option: ";
        int choice = getChoice();

        switch (choice) {
        case 1:
            if (energy >= 10) {
                tomatoes += 2;
                energy = max(energy - 10, 0);
                cout << name << " plants tomatoes and enjoys gardening!\n";
            } else {
                cout << name << " is too tired to plant tomatoes. Let them rest first.\n";
            }
            break;
        case 2:
            if (energy >= 10) {
                carrots += 2;
                energy = max(energy - 10, 0);
                cout << name << " plants carrots and has fun digging!\n";
            } else {
                cout << name << " is too tired to plant carrots. Let them rest first.\n";
            }
            break;
        case 3:
            if (energy >= 10) {
                potatoes += 2;
                energy = max(energy - 10, 0);
                cout << name << " plants potatoes and feels accomplished!\n";
            } else {
                cout << name << " is too tired to plant potatoes. Let them rest first.\n";
            }
            break;
        case 4:
            if (tomatoes > 0) {
                tomatoes--;
                happiness = min(happiness + 5, 100);
                cout << name << " harvests tomatoes and looks happy!\n";
            } else {
                cout << "No tomatoes to harvest. Plant some first!\n";
            }
            break;
        case 5:
            if (carrots > 0) {
                carrots--;
                happiness = min(happiness + 5, 100);
                cout << name << " harvests carrots and feels proud!\n";
            } else {
                cout << "No carrots to harvest. Plant some first!\n";
            }
            break;
        case 6:
            if (potatoes > 0) {
                potatoes--;
                happiness = min(happiness + 5, 100);
                cout << name << " harvests potatoes and smiles!\n";
            } else {
                cout << "No potatoes to harvest. Plant some first!\n";
            }
            break;
        default:
            cout << "Invalid choice. No gardening for now.\n";
        }
        checkLevelUp();
    }

    // Check if kitty levels up
    void checkLevelUp() {
        if (happiness >= 100 && hunger >= 80 && energy >= 80 && cleanliness >= 80) {
            level++;
            age++;
            happiness = 70;
            hunger = 70;
            energy = 70;
            cleanliness = 70;
            cout << name << " leveled up to Level " << level << "! They're growing up!\n";
        }
    }
};

// Input validation function
int getChoice() {
    int choice;
    while (true) {
        cout << "Choose an action: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
        } else {
            return choice;
        }
    }
}

// Main function
int main() {
    string kittyName;
    cout << "Welcome to Kitty Sims! What's your kitty's name? ";
    cin >> kittyName;

    Kitty myKitty(kittyName);

    int choice;
    do {
        cout << "\n✨🐾 --- Menu --- 🐾✨\n";
        cout << "1. Display Status\n";
        cout << "2. Feed\n";
        cout << "3. Play\n";
        cout << "4. Bathe\n";
        cout << "5. Sleep\n";
        cout << "6. Garden\n";
        cout << "7. Exit\n";

        choice = getChoice();

        switch (choice) {
        case 1:
            myKitty.displayStatus();
            break;
        case 2:
            myKitty.feed();
            break;
        case 3:
            myKitty.play();
            break;
        case 4:
            myKitty.bathe();
            break;
        case 5:
            myKitty.sleep();
            break;
        case 6:
            myKitty.garden();
            break;
        case 7:
            cout << "Goodbye! Take care of " << kittyName << "!\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
