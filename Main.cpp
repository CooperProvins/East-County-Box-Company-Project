#include<iostream>
#include<string>
#include<iomanip>

using namespace std;

int main(){
    cout << "East County Box Company" << endl << endl;
    cout << "Sales Program (Version 1.5)" << endl << endl;

    double length, width, height, volume, subtotal, salestax, total;

    cout << "Enter package dimensions (feet): " << endl;
    cout << "Length: ";
    cin >> length;
    cout << "Width: ";
    cin>> width;
    cout << "Height: ";
    cin >> height;
    volume = length * width * height;
    cout << endl << "Package Volume: " << volume << " cubic feet" << endl << endl;
    subtotal = volume * 2.5;
    salestax = subtotal * .0775;
    total = subtotal + salestax;
    cout << setprecision(2) << fixed;
    cout << setw(42) << left << "Shipping Cost ($2.50 per cubic foot) " << setw(2) << left << "$ " << setw(8) << right << subtotal << endl;
    cout << setw(42) << left << "Sales Tax (.0775) " << setw(2) << left << "$ " << setw(8) << right << salestax << endl << endl;
    cout << setw(42) << left << "Total  " << setw(2) << left << "$ " << setw(8) << right << total << endl;

    return 0;
}