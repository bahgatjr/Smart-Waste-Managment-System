#include <iostream>
#include <string>
#include <cassert>
using namespace std;

// Base User Class
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

    virtual void login() { cout << name << " logged in.\n"; }
    virtual void logout() { cout << name << " logged out.\n"; }
    virtual ~User() {}
};

// Derived User Roles
class Driver : public User
{
private:
    string assignedRoute;

public:
    Driver(string id, string n, string e, string p, string route)
        : User(id, n, e, p), assignedRoute(route) {}

    void confirmTask() { cout << name << " confirmed task" << endl; }
    void viewRoute() { cout << "Route: " << assignedRoute << endl; }
};

class Citizen : public User
{
public:
    Citizen(string id, string n, string e, string p) : User(id, n, e, p) {}
    void submitComplaint() { cout << name << " submitted a complaint." << endl; }
    void viewBinStatus() { cout << name << " viewed bin status." << endl; }
};

class Supervisor : public User
{
public:
    Supervisor(string id, string n, string e, string p) : User(id, n, e, p) {}
    void assignComplaint() { cout << name << " assigned a complaint.\n"; }
    void reviewComplaints() { cout << name << " reviewed complaints.\n"; }
};

class Technician : public User
{
public:
    Technician(string id, string n, string e, string p) : User(id, n, e, p) {}
    void resolveComplaint() { cout << name << " resolved a complaint.\n"; }
    void submitReport() { cout << name << " submitted a report.\n"; }
};

// Bin and Sensor
enum BinStatus
{
    OK,
    FULL,
    FAULTY
};

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
    int batteryLevel;
    int threshold;

public:
    Sensor(string id, int battery, int thresh)
        : sensorID(id), batteryLevel(battery), threshold(thresh) {}

    int detectFillLevel()
    {
        return rand() % 101;
    }

    void sendData()
    {
        cout << "Sensor " << sensorID << " sent data.\n";
    }
};

// ===== Complaint =====
enum ComplaintStatus
{
    PENDING,
    ASSIGNED,
    RESOLVED,
    REJECTED
};

class Complaint
{
private:
    string complaintID;
    string description;
    ComplaintStatus status;
    string timeStamp;

public:
    Complaint(string id, string desc, string ts)
        : complaintID(id), description(desc), status(PENDING), timeStamp(ts) {}

    void updateStatus(ComplaintStatus newStatus)
    {
        status = newStatus;
    }

    ComplaintStatus getStatus() const { return status; }

    void assignTechnician(string techID)
    {
        cout << "Complaint " << complaintID << " assigned to technician " << techID << "\n";
    }
};

// Route
class Route
{
private:
    string routeID;
    string driverID;
    Bin *binList[10];
    int binCount;
    double distance;

public:
    Route(string id, string driver, double dist)
        : routeID(id), driverID(driver), binCount(0), distance(dist) {}

    void addBin(Bin *b)
    {
        if (binCount < 10)
        {
            binList[binCount++] = b;
        }
    }

    int getBinCount() const { return binCount; }

    void generateOptimalRoute()
    {
        cout << "Optimal route generated for driver " << driverID << "\n";
    }

    void updateRoute()
    {
        cout << "Route " << routeID << " updated.\n";
    }
};

// ===== System Controller =====
class SystemController
{
public:
    void verifyTask() { cout << "Task verified.\n"; }
    void generateNotification() { cout << "Notification generated.\n"; }
    void generateRoute() { cout << "Route generated.\n"; }
    void recordPenalty() { cout << "Penalty recorded.\n"; }
};

// ===== Main Unit Tests =====
int main()
{
    cout << "Running Unit Tests for Waste Management System...\n\n";

    // Test User creation and login
    cout << "Test 1: User Creation and Login\n";
    Driver d("D1", "Omar", "omar@mail.com", "1234", "Route-1");
    assert(d.getUserID() == "D1");
    assert(d.getName() == "Omar");
    cout << "User created successfully.\n";

    // Test Bin status update
    cout << "\nTest 2: Bin Status Update\n";
    Bin b1("B1", "Street 1", 95);
    assert(b1.getStatus() == OK); // Initial status
    b1.updateStatus();
    assert(b1.getStatus() == FULL); // Should be FULL since 95 >= 90
    cout << "Bin status updated to FULL.\n";

    Bin b2("B2", "Street 2", 40);
    b2.updateStatus();
    assert(b2.getStatus() == OK); // Should remain OK
    cout << "Bin status remains OK for low fill level.\n";

    // Test Complaint status update
    cout << "\nTest 3: Complaint Status Update\n";
    Complaint comp("C1", "Bin overflow", "2025-12-22");
    assert(comp.getStatus() == PENDING);
    comp.updateStatus(ASSIGNED);
    assert(comp.getStatus() == ASSIGNED);
    cout << "Complaint status updated to ASSIGNED.\n";

    // Test Route bin addition
    cout << "\nTest 4: Route Bin Addition\n";
    Route r("R1", "D1", 12.5);
    assert(r.getBinCount() == 0);
    r.addBin(&b1);
    assert(r.getBinCount() == 1);
    r.addBin(&b2);
    assert(r.getBinCount() == 2);
    cout << "Bins added to route successfully.\n";

    // Test Sensor fill level detection
    cout << "\nTest 5: Sensor Fill Level Detection\n";
    Sensor s("S1", 100, 80);
    int level = s.detectFillLevel();
    assert(level >= 0 && level <= 100); // Random value within range
    cout << "Sensor detected fill level: " << level << "%\n";

    cout << "\nAll unit tests passed successfully!\n";
    return 0;
}