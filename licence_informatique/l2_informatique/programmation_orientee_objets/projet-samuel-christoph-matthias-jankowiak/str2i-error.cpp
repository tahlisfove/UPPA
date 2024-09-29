/**
 * \file str2i-error.cpp
 */
#include <string> // for string
#include <sstream> // for stream
#include "str2i-error.h" // for str2i-error
using namespace std; // for string
/**
 * Constructs a new string to int conversion exception.
 */
str2i_error::str2i_error(string str)
{
        ostringstream err;
        err << "str2i_error: unable to convert the string\"" << str << "\" to an int" << endl;
}
/**
 * Destroys an existing string to int conversion exception.
 */
str2i_error::~str2i_error() throw (){}
/**
 * Return the string describing this string to int conversion exception.
 */
const char *str2i_error::what() const throw ()
{
        return this->str.c_str();
}