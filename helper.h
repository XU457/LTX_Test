#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <cctype>

int stoint(const std::string& str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[i] == '-') {
        sign = -1;
        i++;
    }

    for (; i < str.length(); i++) {
        if (isdigit(str[i])) {
            result = result * 10 + (str[i] - '0');
        } else {
            std::cerr << "Invalid character in the string." << std::endl;
            return 0;
        }
    }

    return result * sign;
}

#endif // HELPER_H
