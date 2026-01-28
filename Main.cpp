#include<iostream>
#include<string>
#include<iomanip>
#include <stdexcept>

// Prompts the user to enter a positive double value
// Repeats input until a valid positive number is provided
int receivePositiveDouble();

// Calculates the volume of a rectangular package given length, width, and height
double calculateVolume(double, double, double);

// Removed namespace declaration, personal preference

int main(){
  std::cout << "East County Box Company" << std::endl << std::endl;
  std::cout << "Sales Program (Version 1.5)" << std::endl << std::endl;

  // Declare variables for package dimensions, pricing, totals, and rates
  double length, width, height, volume, subtotal, minitotal, salestax, total, cfRate, shipTotal;
  double cfRates[] = {1.5,2.5,3};
  int paymentType, shipmentType;
  int numCountainers = 1;
  std::string response = "";

  // Loop allows user to enter multiple packages until they choose to stop
  do {
    // Prompt user for package dimensions (must be positive values)
    std::cout << "Enter package #" << numCountainers << " dimensions (feet): " << std::endl;
    std::cout << "Length: ";
    length = receivePositiveDouble();
    std::cout << "Width: ";
    width = receivePositiveDouble();
    std::cout << "Height: ";
    height = receivePositiveDouble();

    // Ensure package volume does not exceed the 65 cubic foot limit
    while (calculateVolume(length,width,height) > 65){
      std::cout << "This package exceeds the 65 cubic foot limit. Please input again." << std::endl << std::endl;
      std::cout << "Enter package #" << numCountainers << " dimensions (feet): " << std::endl;
      std::cout << "Length: ";
      length = receivePositiveDouble();
      std::cout << "Width: ";
      width = receivePositiveDouble();
      std::cout << "Height: ";
      height = receivePositiveDouble();
    }

    volume = calculateVolume(length,width,height);

    // Calculate cost for this package and add to running subtotal
    std::cout << std::endl << "Package #" << numCountainers << " Volume: " << volume << " cubic feet" << std::endl;
    minitotal = volume * cfRate;

    // Determine cost per cubic foot based on package volume
    if (volume < 15){
      cfRate = cfRates[0];
      std::cout << "Small";
    }
    else if (volume <= 45){
      cfRate = cfRates[1];
      std::cout << "Medium";
    }
    else {
      cfRate = cfRates[2];
      std::cout << "Large";
    }
    minitotal = volume * cfRate;
    subtotal += minitotal;

    // Format monetary output to two decimal places
    std::cout << std::setprecision(2) << std::fixed;

    // notifies user of price calculations
    std::cout << " Package ($" << cfRate << " per cubic foot) " << std::setw(7) << "$ " << std::setw(8) << std::right << minitotal << std::endl << std::endl;

    // notifies user of shipping options
    std::cout << "(1) Standard - (one to two weeks) - No change to the price\n(2) Fast Ground - (3 to 5 business days) - Extra $1.50 per cubic foot\n";
    if (volume <= 30) {
      std::cout << "(3) Air - (1 to 2 business days) - Only applies to packages under 30 cubic feet - Extra $3.00 per cubic foot";
    }

    // receives delivery method from user
    std::cout << std::endl << std::endl << "Delivery Method: ";
    std::cin >> shipmentType;

    // parses shipment type and assigns rate
    switch (shipmentType) {
      case 1: {
        cfRate = 0;
        std::cout << "Standard";
        break;
      }
      case 2: {
        cfRate = 1.5;
        std::cout << "Fast Ground";
        break;
      }
      case 3: {
        // if 3 is inputted, but volume is over 30, throw error
        if (volume >= 30) {
          throw std::runtime_error("\n\nShipping option input must be 1 or 2");
        }
        cfRate = 3;
        std::cout << "Air";
        break;
      }
      // if shipping type is invalid throw error
      default:
        throw std::runtime_error("\n\nShipping option input must be 1, 2, or 3");
    }

    minitotal = volume * cfRate;
    shipTotal += minitotal;

    std::cout << " (Extra $" << cfRate << " per cubic foot) " << std::setw(7) << "$ " << std::setw(8) << std::right << minitotal << std::endl << std::endl;
    // Ask user whether they want to enter another package
    std::cout << "Add another package (Y/N): ";
    std::cin >> response;
    std::cout << std::endl;
    numCountainers++;
  } while (response != "N" && response != "n");

  // Print info to user
  std::cout << std::setw(42) << std::left << "Container Total" << std::setw(2) << std::left << "$ " << std::setw(8) << std::right << subtotal << std::endl;
  std::cout << std::setw(42) << std::left << "Shipping Total" << std::setw(2) << std::left << "$ " << std::setw(8) << std::right << shipTotal << std::endl << std::endl;

  // Final sales tax and total cost calculations
  subtotal += shipTotal;
  salestax = subtotal * 0.0775;
  total = subtotal + salestax;

  std::cout << std::setw(42) << std::left << "Subtotal" << std::setw(2) << std::left << "$ " << std::setw(8) << std::right << subtotal << std::endl;
  std::cout << std::setw(42) << std::left << "Sales Tax (7.75%) " << std::setw(2) << std::left << "$ " << std::setw(8) << std::right << salestax << std::endl << std::endl;
  std::cout << std::setw(42) << std::left << "Total  " << std::setw(2) << std::left << "$ " << std::setw(8) << std::right << total << std::endl;

  // Grab payment type from player
  std::cout << std::endl << "Payment (1. Cash, 2. Check, 3. Credit): ";
  std::cin >> paymentType;
  switch (paymentType) {
    // Cash case
    case 1: {
      // receive accepted cash double from user
      // print out change
      double accepted;
      std::cout << std::endl << std::setw(42) << std::left << "Accepted" << "$";
      std::cin >> accepted;
      // if received less money than total, throw error
      if (accepted < total) {
        throw std::runtime_error("\n\nReceived money must not be less than total");
      }
      std::cout << std::setw(42) << std::left << "Change  " << std::setw(2) << std::left << "$ " << std::setw(8) << std::right << accepted-total << std::endl;
      break;
    }
    // Check case
    case 2: {
      // receive driver's license ID from user
      std::string driversLicenseNum;
      std::cout << std::endl << std::setw(43) << std::left << "Driver License Number";
      std::cin >> driversLicenseNum;
      // if ID is not of correct length, throw error
      if (driversLicenseNum.length() != 8) {
        throw std::runtime_error("\n\nDrivers License ID must have 8 characters");
      }
      // if ID's first character is not a letter, throw error
      if (std::isalpha(driversLicenseNum[0]) == false) {
        throw std::runtime_error("\n\nFirst letter of Drivers License ID must be a letter");
      }
      // if ID's second or beyond character is not a number, throw error
      for (int i = 1; i < 8; i++) {
        if (std::isalpha(driversLicenseNum[i]) == true) {
          throw std::runtime_error("\n\nCharacters 2-8 of Drivers License ID must be numbers");
        }
      }
      // print payment to user
      std::cout << std::setw(42) << std::left << "Accepted Check Payment  " << std::setw(2) << std::left << "$ " << std::setw(8) << std::right << total << std::endl;
      break;
    }
    // Card case
    case 3: {
      // receive card type from user
      std::string cardType;
      std::cout << std::endl << std::setw(43) << std::left << "Visa (V) or Mastercard (M)";
      std::cin >> cardType;
      // if cardType input is not valid, throw an error
      if (!(cardType == "V" || cardType == "M" || cardType == "v" || cardType == "m")) {
        throw std::runtime_error("\n\nInvalid card type input");
      }
      // receive card digits from user
      std::cout << std::setw(43) << std::left << "Last 4 digits of Card";
      std::string cardDigits;
      std::cin >> cardDigits;
      for (int i = 1; i < cardDigits.length(); i++) {
        if (std::isdigit(cardDigits[i]) != true) {
          throw std::runtime_error("\n\nCard digits must be all numbers");
        }
      }
      if (cardDigits.length() != 4) {
        throw std::runtime_error("\n\nInvalid card digit length");
      }
      // print payment to user
      std::cout << std::setw(42) << std::left << "Accepted Credit Card Payment  " << std::setw(2) << std::left << "$ " << std::setw(8) << std::right << total << std::endl;
      break;
    }
    default: {
        throw std::runtime_error("\n\nInvalid payment type");
    }
  }

  return 0;
}

// Function: receivePositiveDouble
// Takes doubles from input and returns the first positive one
int receivePositiveDouble() {
  // declare local variable
  double number;

  // initialize user number to local var
  std::cin >> number;

  // throws error if number is not positive
  if (number < 0) {
    throw std::runtime_error("\n\nNumber must be positive");
  }
  if (number == 0) {
    throw std::runtime_error("\n\nNumber must be non-zero");
  }

  // return local var
  return number;
}

// Function: calculateVolume
// Returns the volume of a box using length * width * height
double calculateVolume(double a, double b, double c){
  return a*b*c;
}