/**
 * \file envelope.cpp
 */
#include <iostream> //for cout
#include <string> // for string
#include <vector> // for vector
#include <cstring> //for str
#include "envelope.h" //for envelope_t
using namespace std; // for string
/**
 * Constructs a new envelope.
 */
envelope_t::envelope_t()
{
        this->height = 0;
        this->width = 0;
}
/**
 * Gets the height for this envelope.
 */
int envelope_t::get_height() const
{
        return this->height;
}
/**
 * Gets the priority for this envelope.
 */
priority_t envelope_t::get_priority() const
{
        return this->priority;
}
/**
 * Gets the recipient address for this envelope.
 */
address_t envelope_t::get_recipient() const
{
        return this->recipient;
}
/**
 * Gets the sender address for this envelope.
 */
address_t envelope_t::get_sender() const
{
        return this->sender;
}
/**
 * Gets the width for this envelope.
 */
int envelope_t::get_width() const
{
        return this->width;
}
/**
 * Prints the envelopes.
 */
void envelope_t::handle_e() const
{
        cout << *this << endl;
}
/**
 * Prints the envelopes with the sender postal code equal to CODE.
 */
void envelope_t::handle_ec(int postal_code) const
{
        if(this->get_sender().get_postal_code() == postal_code)
        {
                this->handle_e();
        }
}
/**
 * Prints the envelopes with the sender postal code greater than or equal to CODE.
 */
void envelope_t::handle_ecge(int postal_code) const
{
        if(this->get_sender().get_postal_code() >= postal_code)
        {
                this->handle_e();
        }
}
/**
 * Prints the envelopes with the sender postal code greater than CODE.
 */
void envelope_t::handle_ecgt(int postal_code) const
{
        if(this->get_sender().get_postal_code() > postal_code)
        {
                this->handle_e();
        }
}
/**
 * Prints the envelopes with the sender postal code less than or equal to CODE.
 */
void envelope_t::handle_ecle(int postal_code) const
{
        if(this->get_sender().get_postal_code() <= postal_code)
        {
                this->handle_e();
        }
}
/**
 * Prints the envelopes with the sender postal code less than CODE.
 */
void envelope_t::handle_eclt(int postal_code) const
{
        if(this->get_sender().get_postal_code() < postal_code)
        {
                this->handle_e();
        }
}
/**
 * Prints the envelopes with the sender name containing NAME.
 */
void envelope_t::handle_en(string name) const
{
        if(strstr(this->get_sender().get_name().c_str(), name.c_str()) != NULL)
        {
                this->handle_e();
        }
}
/**
 * Sets the priority for this envelope.
 */
void envelope_t::set_priority(priority_t priority)
{
        this->priority = priority;
}
/**
 * Sets the recipient address for this envelope.
 */
void envelope_t::set_recipient(address_t recipient)
{
        this->recipient = recipient;
}
/**
 * Sets the sender address for this envelope.
 */
void envelope_t::set_sender(address_t sender)
{
        this->sender = sender;
}
/**
 * Prints the string "(sender -> recipient [priority] widthxheight)" for an envelope.
 */
ostream &operator<<(ostream &os, const envelope_t &envelope)
{
        const char *priorities[] = {"undefined", "high", "low", "medium"};
        os << "(" << envelope.get_sender() << " -> " << envelope.get_recipient() << " [" << priorities[envelope.get_priority()] << "] " << envelope.get_width() << "x" << envelope.get_height() << " mm)";
        return os;
}