// =============================
// 📁 File: main.cpp
// Description: مجموعة برامج C++ لتعلم مفاهيم OOP + Bitwise + ملفات
// =============================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

// =======================================================
// 🔹 مثال: Constructor و Destructor وإدارة الذاكرة
// =======================================================
class MemoryDemo {
private:
    int* data;

public:
    MemoryDemo() {
        data = new int[5];
        cout << "Constructor: Memory allocated." << endl;
    }

    ~MemoryDemo() {
        delete[] data;
        cout << "Destructor: Memory released." << endl;
    }
};

// =======================================================
// 🔹 مثال: Overloading و Overriding
// =======================================================
class Shape {
public:
    virtual void draw() {
        cout << "Drawing a shape" << endl;
    }

    void draw(int times) {  // Overloading
        for (int i = 0; i < times; i++) draw();
    }
};

class Circle : public Shape {
public:
    void draw() override {  // Overriding
        cout << "Drawing a circle" << endl;
    }
};

// =======================================================
// 🔹 مثال: أنواع Constructors مع الوراثة
// =======================================================
class Parent {
public:
    Parent() { cout << "Parent default constructor\n"; }
    Parent(int x) { cout << "Parent parameterized constructor: " << x << "\n"; }
};

class Child : public Parent {
public:
    Child() : Parent(10) {
        cout << "Child constructor\n";
    }
};

// =======================================================
// 🔹 Interface class (Pure abstract class)
// =======================================================
class IWorker {
public:
    virtual void doWork() = 0;
    virtual void estimateCost() = 0;
};

class Electrician : public IWorker {
public:
    void doWork() override { cout << "Fixing wires...\n"; }
    void estimateCost() override { cout << "Estimated cost: $100\n"; }
};

// =======================================================
// 🔹 Static و this و scope variables
// =======================================================
class Counter {
private:
    static int count;
    string name;

public:
    Counter(string name) {
        this->name = name;  // استخدام this
        count++;
    }

    static int getCount() { return count; }
};
int Counter::count = 0;

// =======================================================
// 🔹 Operator Overloading
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
// 🔹 Exception Handling Example
// =======================================================
void divide(int a, int b) {
    if (b == 0)
        throw runtime_error("Cannot divide by zero");
    cout << "Result: " << a / b << endl;
}

// =============================
// 📌 كلاس الطالب Student: حفظ واسترجاع البيانات من ملف
// =============================
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

// =============================
// 📌 كلاس تحليل البتات: BitAnalyzer
// =============================
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

// =============================
// ✅ main function لتجربة جميع الأجزاء
// =============================
int main() {
    // ✅ Memory Management Demo
    MemoryDemo m;

    // ✅ Inheritance + Overloading + Overriding
    Shape* shape = new Circle();
    shape->draw(); // overriding
    shape->draw(2); // overloading
    delete shape;

    // ✅ Inheritance with Constructors
    Child c;

    // ✅ Interface class
    Electrician e;
    e.doWork();
    e.estimateCost();

    // ✅ Static + this
    Counter a("A"), b("B");
    cout << "Object count: " << Counter::getCount() << endl;

    // ✅ Operator Overloading
    Complex c1(2, 3), c2(1, 4);
    Complex sum = c1 + c2;
    sum.display();

    // ✅ Exception Handling
    try {
        divide(10, 0);
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    // ✅ Student File I/O
    Student s;
    s.input();
    s.saveToFile("students.txt");
    Student::readFromFile("students.txt");

    // ✅ BitAnalyzer
    int input;
    cout << "\nEnter a number to analyze bits: ";
    cin >> input;
    BitAnalyzer analyzer(input);
    analyzer.displayResults();

    return 0;
}
