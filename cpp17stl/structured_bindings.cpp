#include <iostream>
#include <utility>
#include <string>

using namespace std;

pair<int, int> GetNumbers()
{
    return pair<int, int>(10,20);
}

struct EmployeeDetails
{
    int id_{0};
    string name_;
    string address_;
    string phoneNo_;
};

EmployeeDetails GetEmployee()
{
    EmployeeDetails employee;

    employee.id_ = 5;
    employee.name_ = "John Henry Smith";
    employee.address_ = "60 Moon Crescemt";
    employee.phoneNo_ = "+353871237895";

    return employee;
}

int main(int argc, char** argv)
{
    // Unpack the returned pair
    auto[a,b] = GetNumbers();

    cout << a << " - " << b << endl;

    auto[id,name,address,phoneNo] = GetEmployee();

    cout << "ID: " << id << endl
         << "Name: " << name << endl
         << "Address: " << address << endl
         << "Phone No. " << phoneNo << endl;

    exit(0);
}
