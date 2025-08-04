// ================================================
// 📁 File: oop_master.cpp
// Description: جميع مفاهيم OOP + Bitwise + ملفات C++ في ملف واحد
// Author: Abdelrahman Ramadan
// ================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

// =======================================================
// 🧠 المفهوم: Abstraction + Encapsulation + Inheritance + Polymorphism + Access Modifiers
// 📝 البرنامج: Employee with Developer & Manager subclasses
// =======================================================
class Employee {
private:
    string name;
    int id;
    double salary;

protected:
    string role;

public:
    Employee(string n, int i, double s) {
        name = n;
        id = i;
        salary = s;
    }

    string getName() {
        return name;
    }

    void setName(string n) {
        name = n;
    }

    double getSalary() {
        return salary;
    }

    void setSalary(double s) {
        if (s >= 0)
            salary = s;
    }

    virtual void work() {
        cout << name << " is working as a general employee.\n";
    }

    void showInfo() {
        cout << "Name: " << name << ", ID: " << id << ", Salary: " << salary << ", Role: " << role << endl;
    }
};

class Developer : public Employee {
private:
    string programmingLanguage;

public:
    Developer(string n, int i, double s, string lang)
        : Employee(n, i, s) {
        role = "Developer";
        programmingLanguage = lang;
    }

    void work() override {
        cout << getName() << " is coding in " << programmingLanguage << ".\n";
    }
};

class Manager : public Employee {
private:
    int teamSize;

public:
    Manager(string n, int i, double s, int t)
        : Employee(n, i, s) {
        role = "Manager";
        teamSize = t;
    }

    void work() override {
        cout << getName() << " is managing a team of " << teamSize << " people.\n";
    }
};

// =======================================================
// 🧠 المفهوم: Static Variables + this Pointer
// 📝 البرنامج: Counter class
// =======================================================
class Counter {
private:
    static int count;
    string name;

public:
    Counter(string name) {
        this->name = name;
        count++;
    }

    static int getCount() {
        return count;
    }
};
int Counter::count = 0;

// =======================================================
// 🧠 المفهوم: Operator Overloading
// 📝 البرنامج: Complex number addition
// =======================================================
class Complex {
private:
    float real, imag;

public:
    Complex(float r = 0, float i = 0) : real(r), imag(i) {}

    Complex operator + (const Complex& other) {
        return Complex(real + other.real, imag + other.imag);
    }

    void display() {
        cout << real << "+" << imag << "i\n";
    }
};

// =======================================================
// 🧠 المفهوم: Exception Handling
// 📝 البرنامج: قسمة عددين مع التعامل مع القسمة على صفر
// =======================================================
void divide(int a, int b) {
    if (b == 0)
        throw runtime_error("Cannot divide by zero");
    cout << "Result: " << a / b << endl;
}

// =======================================================
// 🧠 المفهوم: File Handling (Read/Write)
// 📝 البرنامج: Student class to save and read data from file
// =======================================================
class Student {
private:
    string name;
    int age;
    string id;

public:
    Student() {}
    Student(string n, int a, string i) : name(n), age(a), id(i) {}

    void input() {
        cout << "Enter name: ";
        getline(cin, name);
        cout << "Enter age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter ID: ";
        getline(cin, id);
    }

    void display() const {
        cout << "Name: " << name << ", Age: " << age << ", ID: " << id << endl;
    }

    void saveToFile(const string& filename) {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << name << "\n" << age << "\n" << id << "\n";
            file.close();
        } else {
            cout << "Failed to open file!\n";
        }
    }

    static void readFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string name, id;
            int age;
            while (getline(file, name)) {
                file >> age;
                file.ignore();
                getline(file, id);
                Student s(name, age, id);
                s.display();
            }
            file.close();
        } else {
            cout << "File not found!\n";
        }
    }
};

// =======================================================
// 🧠 المفهوم: Bitwise Operations + Analysis
// 📝 البرنامج: BitAnalyzer class
// =======================================================
class BitAnalyzer {
private:
    int number;
    string binaryString;
    int onesCount;
    int zerosCount;

public:
    BitAnalyzer(int num) {
        number = num;
        binaryString = "";
        onesCount = 0;
        zerosCount = 0;
        convertToBinary();
        countBits();
    }

    void convertToBinary() {
        int n = number;
        if (n == 0) {
            binaryString = "0";
            return;
        }
        while (n > 0) {
            binaryString = char((n % 2) + '0') + binaryString;
            n /= 2;
        }
    }

    void countBits() {
        for (char c : binaryString) {
            if (c == '1') onesCount++;
            else if (c == '0') zerosCount++;
        }
    }

    void displayResults() {
        int totalBits = onesCount + zerosCount;
        double onesRatio = (double)onesCount / totalBits * 100;
        double zerosRatio = (double)zerosCount / totalBits * 100;

        cout << "\nDecimal number: " << number << endl;
        cout << "Binary: " << binaryString << endl;
        cout << "Number of 1s: " << onesCount << endl;
        cout << "Number of 0s: " << zerosCount << endl;
        cout << fixed << setprecision(2);
        cout << "Percentage of 1s: " << onesRatio << "%" << endl;
        cout << "Percentage of 0s: " << zerosRatio << "%" << endl;
    }
};

// =======================================================
// 🔚 main function لتشغيل جميع الأجزاء
// =======================================================
int main() {
    // Employee demo
    Developer dev("Alice", 101, 5000, "C++");
    Manager mgr("Bob", 102, 7000, 5);
    Employee* staff[2] = { &dev, &mgr };
    for (int i = 0; i < 2; i++) {
        staff[i]->showInfo();
        staff[i]->work();
        cout << endl;
    }

    // Static + this pointer
    Counter a("A"), b("B");
    cout << "Object count: " << Counter::getCount() << endl;

    // Operator Overloading
    Complex c1(2, 3), c2(1, 4);
    Complex sum = c1 + c2;
    sum.display();

    // Exception Handling
    try {
        divide(10, 0);
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    // File Handling
    Student s;
    s.input();
    s.saveToFile("students.txt");
    Student::readFromFile("students.txt");

    // Bitwise Analysis
    int input;
    cout << "\nEnter a number to analyze bits: ";
    cin >> input;
    BitAnalyzer analyzer(input);
    analyzer.displayResults();

    return 0;
}
