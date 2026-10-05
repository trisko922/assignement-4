#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;



// PROPERTY / NODE
// =======================================

struct Property
{
    string name;
    int cost;
    string owner;

    Property* next;

    Property(string propertyName, int propertyCost)
    {
        name = propertyName;
        cost = propertyCost;
        owner = "None";
        next = nullptr;
    }
};



class LinkedList
{
private:
    Property* head;

public:

    LinkedList()
    {
        head = nullptr;
    }


    
    void add(string name, int cost)
    {
        Property* newProperty = new Property(name, cost);


        if (head == nullptr)
        {
            head = newProperty;
            return;
        }

        Property* current = head;

        while (current->next != nullptr)
        {
            current = current->next;
        }

        current->next = newProperty;
    }


    
    Property* search(string name)
    {
        Property* current = head;

        while (current != nullptr)
        {
            if (current->name == name)
            {
                return current;
            }

            current = current->next;
        }

        return nullptr;
    }


    
    void remove(string name)
    {
        if (head == nullptr)
        {
            return;
        }

        
        if (head->name == name)
        {
            Property* temp = head;

            head = head->next;

            delete temp;

            return;
        }

        Property* current = head;

        while (current->next != nullptr)
        {
            if (current->next->name == name)
            {
                Property* temp = current->next;

                current->next = current->next->next;

                delete temp;

                return;
            }

            current = current->next;
        }
    }


    
    void print()
    {
        Property* current = head;

        while (current != nullptr)
        {
            cout << current->name
                 << " | Cost: $" << current->cost
                 << " | Owner: " << current->owner
                 << endl;

            current = current->next;
        }
    }


    
    void makeCircular()
    {
        if (head == nullptr)
        {
            return;
        }

        Property* current = head;

        while (current->next != nullptr)
        {
            current = current->next;
        }

        
        current->next = head;
    }


    Property* getHead()
    {
        return head;
    }
};




class Player
{
public:

    string name;

    int money;

    Property* position;


    Player(string playerName, Property* startingPosition)
    {
        name = playerName;

        money = 1500;

        position = startingPosition;
    }


    // Move around the circular board
    void move(int spaces)
    {
        for (int i = 0; i < spaces; i++)
        {
            position = position->next;
        }
    }


    
    void buyProperty()
    {
        
        if (position->owner == "None")
        {
            if (money >= position->cost)
            {
                money -= position->cost;

                position->owner = name;

                cout << name
                     << " buys "
                     << position->name
                     << " for $"
                     << position->cost
                     << endl;
            }

            else
            {
                cout << name
                     << " cannot afford "
                     << position->name
                     << endl;
            }
        }

        else
        {
            cout << position->name
                 << " is already owned by "
                 << position->owner
                 << endl;
        }
    }
};



int main()
{
    LinkedList board;


    

    board.add("Mediterranean Avenue", 60);
    board.add("Baltic Avenue", 60);
    board.add("Oriental Avenue", 100);
    board.add("Vermont Avenue", 100);
    board.add("Connecticut Avenue", 120);
    board.add("St. Charles Place", 140);
    board.add("States Avenue", 140);
    board.add("Virginia Avenue", 160);
    board.add("St. James Place", 180);
    board.add("Tennessee Avenue", 180);


    cout << "==============================" << endl;
    cout << "MONOPOLY BOARD" << endl;
    cout << "==============================" << endl;

    board.print();


    

    cout << endl;

    cout << "Searching for Vermont Avenue..." << endl;

    Property* result = board.search("Vermont Avenue");


    if (result != nullptr)
    {
        cout << "Property found!" << endl;
        cout << result->name
             << " costs $"
             << result->cost
             << endl;
    }

    else
    {
        cout << "Property not found." << endl;
    }


    
    cout << endl;

    cout << "Adding Test Property..." << endl;

    board.add("Test Property", 500);


    cout << endl;

    cout << "Removing Test Property..." << endl;

    board.remove("Test Property");


    cout << endl;

    cout << "Updated board:" << endl;

    board.print();


    

    board.makeCircular();


    // Create players

    Player player1("Alice", board.getHead());

    Player player2("Bob", board.getHead());


    // Random number generator

    srand(time(0));


    cout << endl;

    cout << "==============================" << endl;
    cout << "MONOPOLY GAME START" << endl;
    cout << "==============================" << endl;


    

    for (int turn = 1; turn <= 10; turn++)
    {
        cout << endl;

        cout << "---------- TURN "
             << turn
             << " ----------"
             << endl;


        

        int roll1 = rand() % 6 + 1;

        cout << endl;

        cout << player1.name
             << " rolls "
             << roll1
             << endl;

        player1.move(roll1);


        cout << player1.name
             << " lands on "
             << player1.position->name
             << endl;


        player1.buyProperty();


        cout << player1.name
             << " has $"
             << player1.money
             << " remaining."
             << endl;


        

        int roll2 = rand() % 6 + 1;


        cout << endl;

        cout << player2.name
             << " rolls "
             << roll2
             << endl;


        player2.move(roll2);


        cout << player2.name
             << " lands on "
             << player2.position->name
             << endl;


        player2.buyProperty();


        cout << player2.name
             << " has $"
             << player2.money
             << " remaining."
             << endl;
    }


    cout << endl;

    cout << "==============================" << endl;
    cout << "GAME OVER" << endl;
    cout << "==============================" << endl;


    cout << endl;

    cout << "Alice final money: $"
         << player1.money
         << endl;


    cout << "Bob final money: $"
         << player2.money
         << endl;


    return 0;
}