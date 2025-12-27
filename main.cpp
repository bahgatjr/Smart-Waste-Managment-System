#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// ================= Base User =================
class User
{
protected:
    string userID;
    string name;
    string email;
    string password;

public:
    User(string id, string n, string e, string p)
        : userID(id), name(n), email(e), password(p) {}

    string getUserID() const { return userID; }
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getPassword() const { return password; }

    virtual void login() { cout << name << " logged in.\n"; }
    virtual void logout() { cout << name << " logged out.\n"; }

    virtual ~User() {}
};

// ================= Derived Users =================
class Driver : public User
{
private:
    string assignedRoute;

public:
    Driver(string id, string n, string e, string p, string route)
        : User(id, n, e, p), assignedRoute(route) {}

    void confirmTask() { cout << name << " confirmed task.\n"; }
    void viewRoute() { cout << "Route: " << assignedRoute << endl; }
};

class Citizen : public User
{
public:
    Citizen(string id, string n, string e, string p)
        : User(id, n, e, p) {}

    void submitComplaint() { cout << name << " submitted a complaint.\n"; }
    void viewBinStatus() { cout << name << " viewed bin status.\n"; }
};

class Supervisor : public User
{
public:
    Supervisor(string id, string n, string e, string p)
        : User(id, n, e, p) {}

    void assignComplaint() { cout << name << " assigned a complaint.\n"; }
    void reviewComplaints() { cout << name << " reviewed complaints.\n"; }
};

class Technician : public User
{
public:
    Technician(string id, string n, string e, string p)
        : User(id, n, e, p) {}

    void resolveComplaint() { cout << name << " resolved a complaint.\n"; }
    void submitReport() { cout << name << " submitted a report.\n"; }
};

// ================= Bin & Sensor =================
enum BinStatus { OK, FULL };

class Bin
{
private:
    string binID;
    string location;
    int fillLevel;
    BinStatus status;

public:
    Bin(string id, string loc, int level)
        : binID(id), location(loc), fillLevel(level), status(OK) {}

    void updateStatus()
    {
        status = (fillLevel >= 90) ? FULL : OK;
    }

    BinStatus getStatus() const { return status; }

    void getSensorData()
    {
        cout << "Bin " << binID << " fill level: " << fillLevel << "%\n";
    }
};

class Sensor
{
private:
    string sensorID;

public:
    Sensor(string id) : sensorID(id) {}

    int detectFillLevel()
    {
        return rand() % 101;
    }
};

// ================= Global Users Vector =================
vector<User*> users;

// ================= Login Function =================
User* loginUser()
{
    string email, pass;
    cout << "Email: ";
    cin >> email;
    cout << "Password: ";
    cin >> pass;

    for (User* u : users)
    {
        if (u->getEmail() == email && u->getPassword() == pass)
        {
            cout << "Login successful!\n";
            u->login();
            return u;
        }
    }

    cout << "Login failed! Invalid credentials.\n";
    return nullptr;
}

// ================= Automated Tests =================
void runAutomatedTests()
{
    cout << "\nRunning automated tests...\n";

    Bin b("B1", "Street1", 95);
    b.updateStatus();
    cout << "Bin status: " << (b.getStatus() == FULL ? "FULL" : "OK") << endl;

    Sensor s("S1");
    cout << "Sensor detected fill level: " << s.detectFillLevel() << "%\n";

    cout << "Tests completed.\n";
}

// ================= Main =================
int main()
{
    srand((unsigned)time(nullptr));

    while (true)
    {
        cout << "\n--- Smart Waste Management System ---\n";
        cout << "1) Run automated tests\n";
        cout << "2) Create Driver\n";
        cout << "3) Create Citizen\n";
        cout << "4) Create Supervisor\n";
        cout << "5) Create Technician\n";
        cout << "6) Create Bin\n";
        cout << "7) Login\n";
        cout << "0) Exit\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;

        if (choice == 0)
            break;

        else if (choice == 1)
            runAutomatedTests();

        else if (choice == 2)
        {
            string id, name, email, pass, route;
            cout << "Driver ID: "; cin >> id;
            cout << "Name: "; cin >> name;
            cout << "Email: "; cin >> email;
            cout << "Password: "; cin >> pass;
            cout << "Route: "; cin >> route;

            users.push_back(new Driver(id, name, email, pass, route));
            cout << "Driver created successfully.\n";
        }

        else if (choice == 3)
        {
            string id, name, email, pass;
            cout << "Citizen ID: "; cin >> id;
            cout << "Name: "; cin >> name;
            cout << "Email: "; cin >> email;
            cout << "Password: "; cin >> pass;

            users.push_back(new Citizen(id, name, email, pass));
            cout << "Citizen created successfully.\n";
        }

        else if (choice == 4)
        {
            string id, name, email, pass;
            cout << "Supervisor ID: "; cin >> id;
            cout << "Name: "; cin >> name;
            cout << "Email: "; cin >> email;
            cout << "Password: "; cin >> pass;

            users.push_back(new Supervisor(id, name, email, pass));
            cout << "Supervisor created successfully.\n";
        }

        else if (choice == 5)
        {
            string id, name, email, pass;
            cout << "Technician ID: "; cin >> id;
            cout << "Name: "; cin >> name;
            cout << "Email: "; cin >> email;
            cout << "Password: "; cin >> pass;

            users.push_back(new Technician(id, name, email, pass));
            cout << "Technician created successfully.\n";
        }

        else if (choice == 6)
        {
            string id, loc;
            int lvl;
            cout << "Bin ID: "; cin >> id;
            cout << "Location: "; cin >> loc;
            cout << "Fill level: "; cin >> lvl;

            Bin b(id, loc, lvl);
            b.getSensorData();
            b.updateStatus();
            cout << "Status: " << (b.getStatus() == FULL ? "FULL" : "OK") << endl;
        }

        else if (choice == 7)
        {
            User* u = loginUser();
            if (!u) continue;

            if (Driver* d = dynamic_cast<Driver*>(u))
            {
                d->viewRoute();
                d->confirmTask();
            }
            else if (Citizen* c = dynamic_cast<Citizen*>(u))
            {
                c->submitComplaint();
                c->viewBinStatus();
            }
            else if (Supervisor* s = dynamic_cast<Supervisor*>(u))
            {
                s->assignComplaint();
                s->reviewComplaints();
            }
            else if (Technician* t = dynamic_cast<Technician*>(u))
            {
                t->resolveComplaint();
                t->submitReport();
            }

            u->logout();
        }

        else
            cout << "Invalid choice!\n";
    }

    // cleanup
    for (User* u : users)
        delete u;

    return 0;
}