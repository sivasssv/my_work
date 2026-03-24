#include <iostream>
#include <string>
using namespace std;

class Person
{
    private:
        int socialID;
        string name;
    public:

        Person(string n, int id) : name(n), socialID(id){}

        string getName() const
        {
            return name;
        }

        void setName(string newName)
        {
            name = newName;
        }

        bool validateID()
        {
            return (socialID >= 0 && socialID <= 1001);
        }
};


int main()
{
    Person p1("Siva", 508);

    if (!p1.validateID())
    {
        cout << "Invalid Social ID\n";
    }

    cout << "Name: " << p1.getName() << endl;

    return 0;
}
