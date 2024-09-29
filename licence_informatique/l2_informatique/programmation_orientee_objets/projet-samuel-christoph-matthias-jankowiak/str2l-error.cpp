/**
 * \file str2l-error.cpp
 */
#include <string> // for string
#include <sstream> // for stream
#include "str2l-error.h" // for str2l-error
using namespace std; // for string
/**
 * Constructs a new string to long conversion exception.
 */
str2l_error::str2l_error(string str)
{
        ostringstream err;
        err << "str2l_error: unable to convert the string\"" << str << "\" to a long" << endl;
}
/**
 * Destroys an existing string to long conversion exception.
 */
str2l_error::~str2l_error() throw (){}
/**
 * Return the string describing this string to long conversion exception.
 */
const char *str2l_error::what() const throw ()
{
        return this->str.c_str();
}