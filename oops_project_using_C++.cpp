#include <ctime>
#include <iostream>
#include <string>

using namespace std;

// Base class
class Character
{
protected:
    std:: string name;
    int health;
    int shield;

public:
    // Constructor
    Character(const std::string &NAME, int HEALTH, int SHIELD)
        : name(NAME), health(HEALTH), shield(SHIELD)
        {

        }

    // Virtual destructor
    virtual ~Character()
     {

     }

    // Getter for name
   std:: string GetName() const {
        return name;
    }

    // Getter for health
    int GetHealth() const
    {
        return health;
    }

    // Getter for shield
    int GetShield() const
    {
        return shield;
    }

    // Check if character is defeated
    bool IsDefeated() const
    {
        return (health <= 0);
    }

    // Virtual method for being attacked
    virtual void GetAttacked() = 0; // Pure virtual function

    // Virtual method to print stats
    virtual void PrintStats() const
    {
       std:: cout << "Name: " << name << ", Health: " << health << ", Shield: " << shield << std::endl;
    }
};

// Derived class for Boov
class Boov : public Character
 {
public:
    // Constructor
    Boov(const string &NAME, int HEALTH, int SHIELD)
        : Character(NAME, HEALTH, SHIELD)
         {

         }

    // Override the GetAttacked method
    void GetAttacked()
    {
        int roll = rand() % 100;
        if (roll == 0)
            {
              health = 0;
             }
        else if (roll <= 50)
        {
            shield -= (2 - (rand() % 4));
            if (shield < 0)
            {
                health += shield;
                shield = 0;
            }
         }
        else if (roll <= 79)
          {
            health -= (4 + (rand() % 5));
          }
    }

    // Override the PrintStats method
    void PrintStats() const override
    {
        cout << "Boov Stats - ";
        Character::PrintStats(); // Call base class PrintStats
    }
};

// Derived class for Gorg
class Gorg : public Character
{
private:
    int max_shield;

public:
    // Constructor
    Gorg(const string &NAME, int HEALTH, int SHIELD)
        : Character(NAME, HEALTH, SHIELD), max_shield(SHIELD) {}

    // Override the GetAttacked method
    void GetAttacked() override {
        int roll = rand() % 100;

        // 15% chance to increase shield
        if (roll < 15)
        {
            if (++shield > max_shield)
            {
                shield = max_shield; // Ensure shield does not exceed max_shield
            }
            --shield;
        }

        roll = rand() % 100;

        // 65% chance to decrease shield
        if (roll < 65)
        {
            shield -= (1 + (rand() % 2));
            if (shield < 0)
            {
                health += shield;
                shield = 0;
            }
        }
    }

    // Override the PrintStats method
    void PrintStats() const override
    {
        cout << "Gorg Stats - ";
        Character::PrintStats(); // Call base class PrintStats
    }
};

// Main function
int main()
{
    srand(static_cast<unsigned>(time(0)));

    // Input values for Boov
    cout << "Enter Boov Health value:  ";
    int boovHealth;
    cin >> boovHealth;

    cout << "Enter Boov Shield value:  ";
    int boovShield;
    cin >> boovShield;

    // Input values for Gorg
    cout << "Enter Gorg Health value:  ";
    int gorgHealth;
    cin >> gorgHealth;

    cout << "Enter Gorg Shield value:  ";
    int gorgShield;
    cin >> gorgShield;

    const int NUMBER_OF_SIMULATIONS = 1000000;
    int boovRoundsSurvived = 0;
    int gorgRoundsSurvived = 0;

    for (int i = 0; i < NUMBER_OF_SIMULATIONS; ++i) {
        Character* boov = new Boov("Boov", boovHealth, boovShield);
        Character* gorg = new Gorg("Gorg", gorgHealth, gorgShield);

        // Simulate the rounds for Boov
        while (!boov->IsDefeated())
         {
            ++boovRoundsSurvived;
            boov->GetAttacked();
         }

        // Simulate the rounds for Gorg
        while (!gorg->IsDefeated())
        {
            ++gorgRoundsSurvived;
            gorg->GetAttacked();
        }

        delete boov;
        delete gorg;
    }

    // Calculate and display averages
    cout << "Average number of rounds until Boov is defeated:  ";
    double boovAverage = static_cast<double>(boovRoundsSurvived) / NUMBER_OF_SIMULATIONS;
    cout << boovAverage << endl;

    cout << "Average number of rounds until Gorg is defeated:  ";
    double gorgAverage = static_cast<double>(gorgRoundsSurvived) / NUMBER_OF_SIMULATIONS;
    cout << gorgAverage << endl;

    system("PAUSE");

    return 0;
}
