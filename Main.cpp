#include<iostream>
#include<string>
#include<iomanip>

// local function to receive positive double from user
int receivePositiveDouble() {
    // declare local variable
    double number;

    // initialize user number to local var
    std::cin >> number;

    // ask user to reinput number until they input a positive number
    // will not be tripped if player inputs positive number first try
    while (number <= 0) {
        std::cout << "\tNumber must be positive. Input again: ";
        std::cin >> number;
    }

    // return local var
    return number;
}

double calculateVolume(double a, double b, double c){
  return a*b*c;
}

// removed namespace declaration, personal preference

int main(){
  std::cout << "East County Box Company" << std::endl << std::endl;
  std::cout << "Sales Program (Version 1.5)" << std::endl << std::endl;

  // declare variables to be used in program, all doubles representing real properties of the shipment
  double length, width, height, volume, subtotal, minitotal, salestax, total, cfRate;
  double cfRates[] = {1.5,2.5,3};
  std::string response = "";
  do {
    // initializes some variables with input from user
    std::cout << "Enter package dimensions (feet): " << std::endl;
    std::cout << "Length: ";
    length = receivePositiveDouble();
    std::cout << "Width: ";
    width = receivePositiveDouble();
    std::cout << "Height: ";
    height = receivePositiveDouble();
    
    while (calculateVolume(length,width,height) > 65){
      std::cout << "This package exceeds the 65 cubic foot limit. Please input again." << std::endl << std::endl;
      std::cout << "Enter package dimensions (feet): " << std::endl;
      std::cout << "Length: ";
      length = receivePositiveDouble();
      std::cout << "Width: ";
      width = receivePositiveDouble();
      std::cout << "Height: ";
      height = receivePositiveDouble();
    }

    volume = calculateVolume(length,width,height);
    if (volume < 15){
      cfRate = cfRates[0];
    }
    else if (volume <= 45){
      cfRate = cfRates[1];
    }
    else {
      cfRate = cfRates[2];
    }

    // initializes volume, price calculations to the rest of the variables
    std::cout << std::endl << "Package Volume: " << volume << " cubic feet" << std::endl;
    minitotal = volume * cfRate;
    subtotal += minitotal;

    // sets preference of decimal printing
    // only show two numbers after decimal point
    std::cout << std::setprecision(2) << std::fixed;

    // notifies user of price calculations
    std::cout << "Shipping Cost ($" << cfRate << " per cubic foot) " << std::setw(7) << "$ " << std::setw(8) << std::right << minitotal << std::endl << std::endl;

    std::cout << "Add another package (Y/N): ";
    std::cin >> response;
    std::cout << std::endl;
    } while (response != "N" && response != "n");

  salestax = subtotal * 0.0775;
  total = subtotal + salestax;

  std::cout << std::setw(42) << std::left << "Subtotal" << std::setw(2) << std::left << "$ " << std::setw(8) << std::right << subtotal << std::endl;
  std::cout << std::setw(42) << std::left << "Sales Tax (7.75%) " << std::setw(2) << std::left << "$ " << std::setw(8) << std::right << salestax << std::endl << std::endl;
  std::cout << std::setw(42) << std::left << "Total  " << std::setw(2) << std::left << "$ " << std::setw(8) << std::right << total << std::endl;

  return 0;
}