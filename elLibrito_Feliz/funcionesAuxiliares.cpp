#include <iostream>
#include <regex>
#include <algorithm>
#include <cctype>
#include <string>

using namespace std;

std::string toLower(const std::string& s) {
        std::string s_lower = s;
        std::transform(s_lower.begin(), s_lower.end(), s_lower.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return s_lower;
}

