#ifndef STRINGIFY_HXX
#define STRINGIFY_HXX

#include "../include/stringify.hxx"
#include "../../dialogs/include/dialogs.hxx"

#include <sstream>

/* Use a template here */
std::string stringifyNumber(const double val, const int n)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << val;
    return out.str();
}

std::string stringifyETA()
{
    return "TODO";
}

#endif
