#include <iostream>
#include <bitset>
#include <iomanip>

int main() {
    int decimalNumber = 1234;
    std::bitset<sizeof(int) * 8> binaryNumber(decimalNumber);
    std::cout<<"Decimal number is : "<<decimalNumber<<std::endl;
    std::cout << "Binary: " << binaryNumber << std::endl;
    std::cout << "Octal: " << std::oct << decimalNumber << std::endl;
    std::cout << "Hexadecimal: 0x" << std::hex << std::uppercase << decimalNumber << std::endl;

    return 0;
}