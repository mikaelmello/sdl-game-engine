#include "Helpers.hpp"
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <memory>
#include <algorithm>

template<typename Out>
void Helpers::split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> Helpers::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    Helpers::split(s, delim, std::back_inserter(elems));
    return elems;
}

std::vector<std::string> Helpers::split(const std::string& text, 
                                         const std::string& delims) {
    std::vector<std::string> tokens;
    std::size_t start = text.find_first_not_of(delims), end = 0;

    while((end = text.find_first_of(delims, start)) != std::string::npos)
    {
        tokens.push_back(text.substr(start, end - start));
        start = text.find_first_not_of(delims, end);
    }
    if(start != std::string::npos)
        tokens.push_back(text.substr(start));

    return tokens;
}

bool Helpers::is_whitespace(const std::string& s) {
  return std::all_of(s.begin(), s.end(), isspace);
}