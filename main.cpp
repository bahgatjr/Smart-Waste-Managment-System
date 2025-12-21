#include <iostream>
#include <string>
using namespace std;

             //Base User Class
class User {
protected:
    string userID;
    string name;
    string email;
    string password;
public:
    User(string id, string n, string e, string p)
        : userID(id), name(n), email(e), password(p) {}

    virtual void login() { cout << name << " logged in.\n"; }
    virtual void logout() { cout << name << " logged out.\n"; }
    virtual ~User() {}
};

            //Derived User Roles
class Driver : public User {
private:
    string assignedRoute;
public:
    Driver(string id, string n, string e, string p, string route)
        : User(id, n, e, p), assignedRoute(route) {}

    void confirmTask() { cout << name << " confirmed task"<<endl; }
    void viewRoute() { cout << "Route: " << assignedRoute << endl; }

};

class Citizen : public User {
public:
    Citizen(string id, string n, string e, string p) : User(id, n, e, p) {}
    void submitComplaint() { cout << name << " submitted a complaint."<<endl; }
    void viewBinStatus()  { cout << name << " viewed bin status."<<endl; }
};

class Supervisor : public User {
public:
    Supervisor(string id, string n, string e, string p) : User(id, n, e, p) {}
    void assignComplaint() { cout << name << " assigned a complaint.\n"; }
    void reviewComplaints() { cout << name << " reviewed complaints.\n"; }
};

class Technician : public User {
public:
    Technician(string id, string n, string e, string p) : User(id, n, e, p) {}
    void resolveComplaint() { cout << name << " resolved a complaint.\n"; }
    void submitReport() { cout << name << " submitted a report.\n"; }
};

      // Bin and Sensor
enum BinStatus { OK, FULL, FAULTY };

class Bin {
private:
    string binID;
    string location;
    int fillLevel;
    BinStatus status;
public:
    Bin(string id, string loc, int level)
        : binID(id), location(loc), fillLevel(level), status(OK) {}

    void updateStatus() {
        status = (fillLevel >= 90) ? FULL : OK;
    }

    void getSensorData() {
        cout << "Bin " << binID << " fill level: " << fillLevel << "%\n";
    }
};

class Sensor {
private:
    string sensorID;
    int batteryLevel;
    int threshold;
public:
    Sensor(string id, int battery, int thresh)
        : sensorID(id), batteryLevel(battery), threshold(thresh) {}

    int detectFillLevel() {
        return rand() % 101;
    }

    void sendData() {
        cout << "Sensor " << sensorID << " sent data.\n";
    }
};

// ===== Complaint =====
enum ComplaintStatus { PENDING, ASSIGNED, RESOLVED, REJECTED };

class Complaint {
private:
    string complaintID;
    string description;
    ComplaintStatus status;
    string timeStamp;
public:
    Complaint(string id, string desc, string ts)
        : complaintID(id), description(desc), status(PENDING), timeStamp(ts) {}

    void updateStatus(ComplaintStatus newStatus) {
        status = newStatus;
    }

    void assignTechnician(string techID) {
        cout << "Complaint " << complaintID << " assigned to technician " << techID << "\n";
    }
};

                        // Route
class Route {
private:
    string routeID;
    string driverID;
    Bin* binList[10];
    int binCount;
    double distance;
public:
    Route(string id, string driver, double dist)
        : routeID(id), driverID(driver), binCount(0), distance(dist) {}

    void addBin(Bin* b) {
        if (binCount < 10) {
            binList[binCount++] = b;
        }
    }

    void generateOptimalRoute() {
        cout << "Optimal route generated for driver " << driverID << "\n";
    }

    void updateRoute() {
        cout << "Route " << routeID << " updated.\n";
    }
};

// ===== System Controller =====
class SystemController {
public:
    void verifyTask() { cout << "Task verified.\n"; }
    void generateNotification() { cout << "Notification generated.\n"; }
    void generateRoute() { cout << "Route generated.\n"; }
    void recordPenalty() { cout << "Penalty recorded.\n"; }
};

// ===== Main Simulation =====
int main() {
    Driver d("D1", "Omar", "omar@mail.com", "1234", "Route-1");
    Citizen c("C1", "Ali", "ali@mail.com", "5678");
    Supervisor s("S1", "Sara", "sara@mail.com", "9999");
    Technician t("T1", "Mahmoud", "mah@mail.com", "abcd");

    Bin b1("B1", "Street 1", 95);
    Bin b2("B2", "Street 2", 40);

    Route r("R1", "D1", 12.5);
    r.addBin(&b1);
    r.addBin(&b2);

    d.login();
    d.viewRoute();
    c.submitComplaint();
    s.assignComplaint();
    t.resolveComplaint();
    b1.getSensorData();
    r.generateOptimalRoute();

    return 0;
}
