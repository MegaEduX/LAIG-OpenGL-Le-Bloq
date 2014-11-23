//
//  Additions.h
//  Code taken from: Radio Station
//
//  T3G12 - MIEIC 2012/2013
//  Eduardo Almeida, Joao Almeida and Joao Ramos
//
//  This namespace contains functions used on various parts of the program.
//

#ifndef AdditionsHeader
#define AdditionsHeader

#include <iostream>
#include <sstream>
#include <fstream>
#include <cerrno>
#include <vector>

namespace Additions {
    std::vector<std::string> explode(const std::string &delimiter, const std::string &str);
}

#endif
