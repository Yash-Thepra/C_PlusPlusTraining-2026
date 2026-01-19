#include<iostream>

int main() 
{
    //std::cout << atof("dsffds");
    //std::cout << atof("0.0");
    std::cout << atof("13.43") << "\n";
    std::cout << atof("12adf") << "\n";
    std::cout << atof("0.24") << "\n";
    std::cout << atof("12.34.2") << "\n";
    std::cout << atof("12.3assf") << "\n";
    std::cout << atof("12.3.adfd") << "\n";
    std::cout << atof("-12.34.2") << "\n";
    std::cout << atof("-34.23") << "\n";
    std::cout << atof("1eas") << "\n";
    std::cout << atof("1e9") << "\n";
    double answer = atof("dsfs");
    std::cout << answer << "\n";
    std::cout << atof("0.0") << "\n";
    std::cout << atof("1e23") << "\n";
    std::cout << atof("1e-99") << "\n";
    std::cout << atof("1ea99") << "\n";
    std::cout << atof("1e.9sa09") << "\n";
    std::cout << atof("1e32.44") << "\n";
    std::cout << atof("e99") << "\n";
    std::cout << atof("12.34e99") << "\n";
    std::cout << atof("0.023e9") << "\n";
}