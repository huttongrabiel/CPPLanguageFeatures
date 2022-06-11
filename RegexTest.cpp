#include <iostream>
#include <regex>
#include <vector>
#include <string>

void is_valid_postal_code() {
    std::regex postal_pattern { R"([A-Z]{2}\s*\d{5}(-\d{4})?)" } ;
    
    std::string user_postal_code;
    std::cout << "Enter the desired postal code: ";
    std::cin >> user_postal_code;
    
    std::smatch match;
    std::regex_match(user_postal_code, match, postal_pattern);

    if (!match.empty())
        std::cout << match[0] << " is a valid postal address!" << std::endl;
    else
        std::cout << "Sorry, that postal address is invalid." << std::endl;
}

void is_valid_US_phone_number() {
    std::regex US_phone_number{ R"((\+1)?\d{3}-*\d{3}-*\d{4})" };
    // US_phone_number(R"((+1)?\d{3}-\d{3}-\d{4})") is also valid though I find
    // it has too many parentheses.

    std::string phone_number;
    std::cout << "Enter a phone number: ";
    std::cin >> phone_number;

    std::smatch match;
    std::regex_search(phone_number, match, US_phone_number);

    if (!match.empty())
        std::cout << phone_number << " is a valid US phone number!" << std::endl;
    else
        std::cout << "Sorry, that phone number is invalid." << std::endl;
}

int main() {
    is_valid_postal_code();
    is_valid_US_phone_number();
    return 0;
}
