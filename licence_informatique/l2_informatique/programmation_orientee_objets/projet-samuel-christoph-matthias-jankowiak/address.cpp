/**
 * \file address.cpp
 */
#include <iostream> //for cout
#include <string> // for string
#include <vector> // for vector
#include <cstring> //for str
#include "address.h" //for address_t
using namespace std; // for string
/**
 * Constructs a new address.
 */
address_t::address_t()
{
        this->city = "undefined";
        this->country = "undefined";
        this->name = "undefined";
        this->postal_code = 0;
        this->street = "undefined";
}
/**
 * Gets the city for this address.
 */
string address_t::get_city() const
{
        return this->city;
}
/**
 * Gets the country for this address.
 */
string address_t::get_country() const
{
        return this->country;
}
/**
 * Gets the name for this address.
 */
string address_t::get_name() const
{
        return this->name;
}
/**
 * Gets the postal code for this address.
 */
int address_t::get_postal_code() const
{
        return this->postal_code;
}
/**
 * Gets the street for this address.
 */
string address_t::get_street() const
{
        return this->street;
}
/**
 * Sets the city for this address.
 */
void address_t::set_city(string city)
{
        this->city = city;
}
/**
 * Sets the country for this address.
 */
void address_t::set_country(string country)
{
        this->country = country;
}
/**
 * Sets the name for this address.
 */
void address_t::set_name(string name)
{
        this->name = name;
}
/**
 * Sets the postal code for this address.
 */
void address_t::set_postal_code(int postal_code)
{
        this->postal_code = postal_code;
}
/**
 * Sets the street for this address.
 */
void address_t::set_street(string street)
{
        this->street = street;
}
/**
 * Prints the string "(name, street, postal_code, city, country)" for an address.
 */
ostream &operator<<(ostream &os, const address_t &address)
{
        os << "(" << address.get_name() << ", " << address.get_street() << ", " << address.get_postal_code() << ", " << address.get_city() << ", " << address.get_country() << ")";
        return os;
}