/**
 * \file company.cpp
 */
#include <iostream> //for cout
#include <string> // for string
#include <vector> // for vector
#include "envelope.h" // for envelope_t
#include "company.h" // for company_t
using namespace std; // for string
/**
 * Constructs a new company.
 */
company_t::company_t()
{
        this->name = "undefined";
        this->web = "undefined";
}
/**
 * Gets the name for this company.
 */
string company_t::get_name() const
{
        return this->name;
}
/**
 * Gets the web address for this company.
 */
string company_t::get_web() const
{
        return this->web;
}
/**
 * Prints the envelopes.
 */
void company_t::handle_e() const
{
        for(int i = 0; i < this->envelopes_size(); i++)
        {
                this->envelopes_at(i).handle_e();
        }
}
/**
 * Prints information about the company.
 */
void company_t::handle_i() const
{
        cout << *this << endl;
}
/**
 * Prints the company name.
 */
void company_t::handle_n() const
{
        cout << this->name << endl;
}
/**
 * Returns the postcodes of the senders for the ec command.
 */
void company_t::handle_ec(int postal_code) const
{
        for(int i = 0; i < this->envelopes_size(); i++)
        {
                this->envelopes_at(i).handle_ec(postal_code);
        }
}
/**
 * Returns the postcodes of the senders for the ecge command.
 */
void company_t::handle_ecge(int postal_code) const
{
        for(int i = 0; i < this->envelopes_size(); i++)
        {
                this->envelopes_at(i).handle_ecge(postal_code);
        }
}
/**
 * Returns the postcodes of the senders for the ecgt command.
 */
void company_t::handle_ecgt(int postal_code) const
{
        for(int i = 0; i < this->envelopes_size(); i++)
        {
                this->envelopes_at(i).handle_ecgt(postal_code);
        }
}
/**
 * Returns the postcodes of the senders for the ecle command.
 */
void company_t::handle_ecle(int postal_code) const
{
        for(int i = 0; i < this->envelopes_size(); i++)
        {
                this->envelopes_at(i).handle_ecle(postal_code);
        }
}
/**
 * Returns the postcodes of the senders for the eclt command.
 */
void company_t::handle_eclt(int postal_code) const
{
        for(int i = 0; i < this->envelopes_size(); i++)
        {
                this->envelopes_at(i).handle_eclt(postal_code);
        }
}
/**
 * Returns the name of the senders for the en command.
 */
void company_t::handle_en(string name) const
{
        for(int i = 0; i < this->envelopes_size(); i++)
        {
                this->envelopes_at(i).handle_en(name);
        }
}
/**
 * Prints the company web address.
 */
void company_t::handle_w() const
{
        cout << this->web << endl;
}
/**
 * Accesses to the element of envelopes at the specified index for this company.
 */
envelope_t company_t::envelopes_at(int index) const
{
        return this->envelopes[index];
}
/**
 * Adds an element at the end of envelopes for this company.
 */
void company_t::envelopes_push_back(envelope_t envelope)
{
        this->envelopes.push_back(envelope);
}
/**
 * Gets the size of envelopes for this company.
 */
int company_t::envelopes_size() const
{
        return this->envelopes.size();
}
/**
 * Sets the name for this company.
 */
void company_t::set_name(string name)
{
        this->name = name;
}
/**
 * Sets the web address for this company.
 */
void company_t::set_web(string web)
{
        this->web = web;
}
/**
 * Prints the string "(name, web, (envelopes1, envelopes2, ...))" for a company.
 */
ostream &operator<<(ostream &os, const company_t &company)
{
        int i;
        os << "(" << company.get_name() << ", " << company.get_web() << ", (";
        for(i = 0; i < company.envelopes_size(); i++)
        {
                if(i == company.envelopes_size() - 1)
                {
                        os << company.envelopes_at(i) << "))";
                }
                else
                {
                        os << company.envelopes_at(i) << ", ";
                }
        }
        return os;
}