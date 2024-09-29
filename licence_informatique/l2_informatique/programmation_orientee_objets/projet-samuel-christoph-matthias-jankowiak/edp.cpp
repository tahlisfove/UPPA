/**
 * \file edp.cpp
 */
#include <pugixml.hpp> // for pugi
#include <iostream> // for cout
#include <stdlib.h> // for strtol
#include <string> // for string
#include <cstdio> // for stdin
#include <cstring> // for str
#include <climits> // for int and long min/max values
#include "company.h" // for company_t
#include "envelope-c4.h" // for envelope_c4_t
#include "envelope-dl.h" // for envelope_dl_t
#include "str2i-error.h" // for str2i-error
#include "str2l-error.h" // for str2l-error
/**
 * Defines used in the program.
 */
#define VERSION "20220404" // edp version date
#define YEAR "2022" // year of file creation
#define NAME1 "Samuel Christoph" // first developer name
#define NAME2 "Matthias Jankowiak" // second developer name
#define MAIL1 "christoph.samuel@etud.univ-pau.fr" // first developer email
#define MAIL2 "matthias.jankowiak@etud.univ-pau.fr" // second developer email
#define BUFFER_SIZE 20 // for buf
/**
 * Using namespaces.
 */
using namespace std; // for string
using namespace pugi; // for pugi
/**
 * Defines functions used in the program.
 */
/**
 * Handles the h command for this edp.
 * Function that displays all available commands.
 */
void handle_h()
{
        cout << "e: prints the envelopes" << endl;
        cout << "ec CODE: prints the envelopes with the sender postal code equal to CODE" << endl;
        cout << "ecge CODE: prints the envelopes with the sender postal code greater than or equal to CODE" << endl;
        cout << "ecgt CODE: prints the envelopes with the sender postal code greater than CODE" << endl;
        cout << "ecle CODE: prints the envelopes with the sender postal code less than or equal to CODE" << endl;
        cout << "eclt CODE: prints the envelopes with the sender postal code less than CODE" << endl;
        cout << "en NAME: prints the envelopes with the sender name containing NAME" << endl;
        cout << "h: prints this help" << endl;
        cout << "i: prints information about the company" << endl;
        cout << "n: prints the company name" << endl;
        cout << "q: quits EDP" << endl;
        cout << "v: prints the EDP version" << endl;
        cout << "w: prints the company web address" << endl;
}
/**
 * Handles the v command for this edp.
 * Function that displays the EDP version.
 */
void handle_v()
{
        cout << "EDP (Envelope Delivery Program) " << VERSION << "\n" << endl;
        cout << "Copyright (C) " << YEAR << " " << NAME1 << " and " << NAME2 << ".\n" << endl;
        cout << "Written by " << NAME1 << " <" << MAIL1 << "> and " << NAME2 << " <" << MAIL2 << ">." << endl;
}
/**
 * Reading the XML file.
 */
/**
 * Analyses and returns the postal_code.
 */
int postal_code_xml(xml_node node)
{
        char *endptr;
        long postal_code = strtol(node.child_value(), &endptr, 0);
        if(*endptr != '\0' || postal_code <= LONG_MIN || postal_code >= LONG_MAX)
        {
                throw str2l_error(node.child_value());
        }
        else
        {
                if(postal_code < INT_MIN || postal_code > INT_MAX)
                {
                        throw str2i_error(node.child_value());
                }
                else
                {
                        return postal_code;
                }
        }
}
/**
 * Registers an address (city, country, name, postal_code and street).
 */
void address_xml(xml_document &doc, xml_node node, address_t *address)
{
        int postal_code;
        node = node.first_child();
        address->set_city(node.child_value());
        node = node.next_sibling();
        address->set_country(node.child_value());
        node = node.next_sibling();
        address->set_name(node.child_value());
        node = node.next_sibling();
        postal_code = postal_code_xml(node);
        address->set_postal_code(postal_code);
        node = node.next_sibling();
        address->set_street(node.child_value());
}
/**
 * Registers a envelope (prioriry, recipient and sender).
 */
void envelope_xml(xml_document &doc, xml_node node, envelope_t *envelope)
{
        address_t *sender_address;
        address_t *recipient_address;
        node = node.first_child();
        if(!strcmp(node.child_value(), "high"))
        {
                envelope->set_priority(high);
        }
        else
        {
                if(!strcmp(node.child_value(), "low"))
                {
                        envelope->set_priority(low);
                }
                else
                {
                        if(!strcmp(node.child_value(), "medium"))
                        {
                                envelope->set_priority(medium);
                        }
                        else
                        {
                                envelope->set_priority(undefined);
                        }
                }
        }
        node = node.next_sibling();
        recipient_address = new address_t;
        address_xml(doc, node, recipient_address);
        envelope->set_recipient(*recipient_address);
        delete recipient_address;
        node = node.next_sibling();
        sender_address = new address_t;
        address_xml(doc, node, sender_address);
        envelope->set_sender(*sender_address);
        delete sender_address;
}
/**
 * Registers a company (name, envelopes and web).
 */
void company_xml(xml_document &doc, xml_node node, company_t *company)
{
        xml_attribute format;
        xml_node subnode;
        envelope_c4_t *c4;
        envelope_dl_t *dl;
        node = doc.first_child();
        if(!strcmp(node.name(), "company"))
        {
                company->set_name(node.first_attribute().value());
        }
        for(node = node.first_child(); node; node = node.next_sibling())
        {
                if(!strcmp(node.name(), "envelopes"))
                {
                        for(subnode = node.first_child(); subnode; subnode = subnode.next_sibling())
                        {
                                format = subnode.first_attribute();
                                if(!strcmp(format.value(), "c4"))
                                {
                                        c4 = new envelope_c4_t;
                                        envelope_xml(doc, subnode, c4);
                                        company->envelopes_push_back(*c4);
                                        delete c4;
                                }
                                if(!strcmp(format.value(), "dl"))
                                {
                                        dl = new envelope_dl_t;
                                        envelope_xml(doc, subnode, dl);
                                        company->envelopes_push_back(*dl);
                                        delete dl;
                                }
                        }
                }
                if(!strcmp(node.name(), "web"))
                {
                        company->set_web(node.child_value());
                }
        }
}
/**
 * Main program.
 */
int main(int argc, char *argv[])
{
        /**
         * Classes needed for xml reading (pugi).
         */
        pugi::xml_node node;
        pugi::xml_document doc;
        pugi::xml_parse_result result;
        /**
         * Other classes used in our program.
         */
        company_t company;
        address_t address;
        envelope_t envelope;
        /**
         * Definition of the different variables used in the do{ }while loop.
         */
        char buf[BUFFER_SIZE] = "\0";
        char *parameter, *command;
        char *endptr = NULL;
        int postal_code;
        int out = 0;
        /**
         * Verifies that the number of arguments and files entered is correct.
         */
        result = doc.load_file(argv[1]);
        if(argc != 2)
        {
                cerr << argv[0] << ": invalid number of arguments" << endl;
                return 1;
        }
        /**
         * Verifies that the file can be analyzed.
         */ 
        if(!result)
        {
                cerr << argv[0] << ": unable to parse the document" << endl;
                return 1;
        }
        /**
         * Returns and handles errors when parsing the XML file.
         */
        try
        {
                company_xml(doc, node, &company);
        }
        catch(str2l_error &err)
        {
                cerr << argv[0] << ": an exception occured (" << err.what() << ")" << endl;
                return 1;
        }
        catch(str2i_error &err)
        {
                cerr << argv[0] << ": an exception occured (" << err.what() << ")" << endl;
                return 1;
        }
        /**
         * Infinite loop that displays the requested information according to the input command.
         */
        do
        {
                cout << "EDP> ";
                fgets(buf, 20, stdin);
                if(buf[(strlen(buf) - 1)] != '\n')
                {
                        cerr << argv[0] << ": too many characters for the command" << endl;
                        while(getchar() != '\n');
                }
                else
                {
                        command = &buf[0];
                        buf[(strlen(buf) - 1)] = '\0';
                        for(int i = 0; i < (int)strlen(buf); i++)
                        {
                                if(buf[i] == ' ')
                                {
                                        buf[i] = '\0';
                                        if(buf[i + 1] != '\0')
                                        {
                                                parameter = &buf[i + 1];
                                        }
                                }
                        }
                        if(!strcmp(command, "e"))
                        {
                                company.handle_e();
                        }
                        else
                        {
                                if(!strcmp(command, "ec"))
                                {
                                        if(parameter == NULL)
                                        {
                                                cerr << argv[0] << ": missing parameter for the " << command << " command" << endl;
                                        }
                                        else
                                        {
                                                postal_code = strtol(parameter, &endptr, 0);
                                                if(*endptr == '\0' && postal_code > INT_MIN && postal_code < INT_MAX)
                                                {
                                                        company.handle_ec(postal_code);
                                                }
                                                else
                                                {
                                                        cerr << argv[0] << ": invalid parameter for the " << command << " command" << endl;
                                                }
                                        }
                                }
                                else
                                {
                                        if(!strcmp(command, "ecge"))
                                        {
                                                if(parameter == NULL)
                                                {
                                                        cerr << argv[0] << ": missing parameter for the " << command << " command" << endl;
                                                }
                                                else
                                                {
                                                        postal_code = strtol(parameter, &endptr, 0);
                                                        if(*endptr == '\0' && postal_code > INT_MIN && postal_code < INT_MAX)
                                                        {
                                                                company.handle_ecge(postal_code);
                                                        }
                                                        else
                                                        {
                                                                cerr << argv[0] << ": invalid parameter for the " << command << " command" << endl;
                                                        }
                                                }
                                        }
                                        else
                                        {
                                                if(!strcmp(command, "ecgt"))
                                                {
                                                        if(parameter == NULL)
                                                        {
                                                                cerr << argv[0] << ": missing parameter for the " << command << " command" << endl;
                                                        }
                                                        else
                                                        {
                                                                postal_code = strtol(parameter, &endptr, 0);
                                                                if(*endptr == '\0' && postal_code > INT_MIN && postal_code < INT_MAX)
                                                                {
                                                                        company.handle_ecgt(postal_code);
                                                                }
                                                                else
                                                                {
                                                                        cerr << argv[0] << ": invalid parameter for the " << command << " command" << endl;
                                                                }
                                                        }
                                                }
                                                else
                                                {
                                                        if(!strcmp(command, "ecle"))
                                                        {
                                                                if(parameter == NULL)
                                                                {
                                                                        cerr << argv[0] << ": missing parameter for the " << command << " command" << endl;
                                                                }
                                                                else
                                                                {
                                                                        postal_code = strtol(parameter, &endptr, 0);
                                                                        if(*endptr == '\0' && postal_code > INT_MIN && postal_code < INT_MAX)
                                                                        {
                                                                                company.handle_ecle(postal_code);
                                                                        }
                                                                        else
                                                                        {
                                                                                cerr << argv[0] << ": invalid parameter for the " << command << " command" << endl;
                                                                        }
                                                                }
                                                        }
                                                        else
                                                        {
                                                                if(!strcmp(command, "eclt"))
                                                                {
                                                                        if(parameter == NULL)
                                                                        {
                                                                                cerr << argv[0] << ": missing parameter for the " << command << " command" << endl;
                                                                        }
                                                                        else
                                                                        {
                                                                                postal_code = strtol(parameter, &endptr, 0);
                                                                                if(*endptr == '\0' && postal_code > INT_MIN && postal_code < INT_MAX)
                                                                                {
                                                                                        company.handle_eclt(postal_code);
                                                                                }
                                                                                else
                                                                                {
                                                                                        cerr << argv[0] << ": invalid parameter for the " << command << " command" << endl;
                                                                                }
                                                                        }
                                                                }
                                                                else
                                                                {
                                                                        if(!strcmp(command, "en"))
                                                                        {
                                                                                if(parameter == NULL)
                                                                                {
                                                                                        cerr << argv[0] << ": missing parameter for the " << command << " command" << endl;
                                                                                }
                                                                                else
                                                                                {
                                                                                        company.handle_en(parameter);
                                                                                }
                                                                        }
                                                                        else
                                                                        {
                                                                                if(!strcmp(command, "h"))
                                                                                {
                                                                                        handle_h();
                                                                                }
                                                                                else
                                                                                {
                                                                                        if(!strcmp(command, "i"))
                                                                                        {
                                                                                                company.handle_i();
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                                if(!strcmp(command, "n"))
                                                                                                {
                                                                                                        company.handle_n();
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                        if(!strcmp(command, "q"))
                                                                                                        {
                                                                                                                out = 1;
                                                                                                        }
                                                                                                        else
                                                                                                        {
                                                                                                                if(!strcmp(command, "v"))
                                                                                                                {
                                                                                                                        handle_v();
                                                                                                                }
                                                                                                                else
                                                                                                                {
                                                                                                                        if(!strcmp(command, "w"))
                                                                                                                        {
                                                                                                                                company.handle_w();
                                                                                                                        }
                                                                                                                        else
                                                                                                                        {
                                                                                                                                cerr << argv[0] << ": invalid command" << endl;
                                                                                                                        }
                                                                                                                }
                                                                                                        }
                                                                                                }
                                                                                        }
                                                                                }
                                                                        }
                                                                }
                                                        }
                                                }
                                        }
                                }
                        }
                }
            command = NULL;
            parameter = NULL;
        }while(!out);
        return 0;
}