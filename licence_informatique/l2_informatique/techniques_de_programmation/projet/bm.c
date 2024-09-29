/**
 * \file bm.c
 */
#include <stdio.h> /* standard Input/Output Header */
#include <stdlib.h> /* standard library defined by ANSI */
#include <string.h> /* defines variables type, macro, and various functions for manipulating arrays of characters */
#include "base.h" /* for function heading and definitions of base.c */
#include "facility.h" /* for function heading and definitions of facility.c */
#include <libxml/parser.h> /* for function in xml (xmlGetProp...) */
/**
 * -------------------------Other-control-functions----------------------------
 */
/**
 * Handles the v command for a base.
 * Function that displays the database version.
 */
void bm_handle_v()
{
  int version = 20211114;
  printf("BM (Base Manager) %d\n", version);
  printf("\nCopyright (C) 2021 Samuel Christoph and Matthias Jankowiak.\n");
  printf("\nWritten by Samuel Christoph <christoph.samuel@etud.univ-pau.fr> and Matthias Jankowiak <matthias.jankowiak@etud.univ-pau.fr>\n");
}
/**
 * Handles the h command for a base.
 * Function that displays all available commands.
 */
void bm_handle_h()
{
  printf("b: Prints the base\n");
  printf("c: Prints the base country\n");
  printf("d: Prints the base date\n");
  printf("f: Prints the base facilities\n");
  printf("fc COST: Prints the base facilities with the cost equal to COST\n");
  printf("fcge COST: Prints the base facilities with the cost greater than or equal to COST\n");
  printf("fcgt COST: Prints the base facilities with the cost greater than COST\n");
  printf("fcle COST: Prints the base facilities with the cost less than or equal to COST\n");
  printf("fclt COST: Prints the base facilities with the cost less than COST\n");
  printf("fn NAME: Prints the base facilities with the name containing NAME\n");
  printf("h: Prints this help\n");
  printf("n: Prints the base name\n");
  printf("t: Prints the base total cost\n");
  printf("v: Prints the BM version\n");
  printf("q: Quits BM\n");
}
/**
 * Handles the q command for a base.
 * Function to exit the program.
 */
void bm_handle_q()
{
  printf("Goodbye!\n");
}
/**
 * ----------------------------------Xml---------------------------------------
 */
/**
 * Registers the name of the base.
 */
void namexml(xmlDocPtr doc, xmlNodePtr cur, base_t *base)
{
  while(cur != NULL)
  {
    if((!xmlStrcmp(cur->name, (const xmlChar *) "base")))
    {
      base->name = (char *)xmlGetProp(cur, (const xmlChar *) "name");
    }
    cur = cur->next;
  }
}
/**
 * Registers the country where the base is installed.
 */
void countryxml(xmlDocPtr doc, xmlNodePtr cur, base_t *base)
{
  cur = cur->xmlChildrenNode;
  while(cur != NULL)
  {
    if((!xmlStrcmp(cur->name, (const xmlChar *) "country")))
    {
      base->country = (char *)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
    }
    cur = cur->next;
  }
}
/**
 * Registers the date of creation of a base (day, month and year).
 */
void datexml(xmlDocPtr doc, xmlNodePtr cur, base_t *base)
{
  xmlChar *key;
  char *ptr;
  cur = cur->xmlChildrenNode;
  while(cur != NULL)
  {
    /**
     * Registers the day.
     */
    if((!xmlStrcmp(cur->name, (const xmlChar *) "day")))
    {
      key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
      base->day = strtol((char *)key, &ptr, 10);
      xmlFree(key);
    }
    /**
     * Registers the month.
     */
    if((!xmlStrcmp(cur->name, (const xmlChar *) "month")))
    {
      key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
      base->month = strtol((char *)key, &ptr, 10);
      xmlFree(key);
    }
    /**
     * Registers the year.
     */
    if((!xmlStrcmp(cur->name, (const xmlChar *) "year")))
    {
      key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
      base->year = strtol((char *)key, &ptr, 10);
      xmlFree(key);
    }
    cur = cur->next;
  }
  return;
}
/**
 * Registers a facility (name, area and cost).
 */
void facilityxml(xmlDocPtr doc, xmlNodePtr cur, base_t *base)
{
  double stock;
  xmlChar *key;
  xmlChar *fname;
  facility_t *facility;
  facility = facility_create();  
  fname = xmlGetProp(cur, (const xmlChar *) "name");
  facility->name = (char *) fname;
  cur = cur->xmlChildrenNode;
	while(cur != NULL) 
  {
	  if((!xmlStrcmp(cur->name, (const xmlChar *) "area"))) 
    {
      key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
      stock = strtol((char *)key, NULL, 10);
      facility->area = stock;
		}
		if((!xmlStrcmp(cur->name, (const xmlChar *) "cost")))
		{
      key = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
      stock = strtod((char *)key, NULL);
      facility->cost = stock;
		} 
    cur = cur->next;
	}
	base_add_facility(base, facility);
  return;
  free(fname);
  free(key);
}
/**
 * Registers facilities.
 */
void facilitiesxml(xmlDocPtr doc, xmlNodePtr cur, base_t *base)
{
  cur = cur->xmlChildrenNode;
  while(cur != NULL)
  {
    if((!xmlStrcmp(cur->name, (const xmlChar *) "facility")))
    {
      facilityxml(doc, cur, base);
    }
    cur = cur->next;
  }
  return;
}
/**
 * ------------------------------Main-program----------------------------------
 */
int main(int argc, char const *argv[])
{
  char *command = malloc(sizeof(char *));
  char *end = NULL;
  base_t *base = base_create();
  facility_t *facilities = facility_create();
  xmlDocPtr doc;
  xmlNodePtr cur;
  double cost;
  /**
   * Checks that the file is usable (not empty, readable) and displays xml infomations.
   */
  if(argc != 2)
  {
    fprintf(stderr, "./bm.out: Invalid number of arguments\n");
    return 1;
  }
  else
  {
    doc = xmlParseFile(argv[1]);
  }
  if(doc == NULL)
  {
    fprintf(stderr, "./bm.out: Unable to parse the document\n");
    return 1;
  }
  else
  {
    cur = xmlDocGetRootElement(doc);
  }
  /**
   * Returns the recovered information in the xml file.
   */
  namexml(doc, cur, base);
  countryxml(doc, cur, base);
  cur = cur->xmlChildrenNode;
  while(cur != NULL)
  {
    if((!xmlStrcmp(cur->name, (const xmlChar *) "date")))
    {
      datexml(doc, cur, base);
    }
    if((!xmlStrcmp(cur->name, (const xmlChar *) "facilities")))
    {
      facilitiesxml(doc, cur, base);
    }
    cur = cur->next;
  }
  /**
   * Infinite loop that displays the requested information according to the input command.
   */
  do
  {
    printf("BM> ");
    fgets(command, 19, stdin);
    if(command[strlen(command)-1] != '\n')
    {
      while(getchar() != '\n');
      fprintf(stderr, "./bm.out: Too many characters for the command\n");
    }
    else
    {
      command[strlen(command)-1] = '\0';
      if(!strcmp(command, "h"))
      {
        bm_handle_h();
      }
      else
      {
        if(!strcmp(command, "b"))
        {
          base_handle_b( *base);
        }
        else
        {
          if(!strcmp(command, "c"))
          {
            base_handle_c( *base);
          }
          else
          {
            if(!strcmp(command, "d"))
            {
              base_handle_d( *base);
            }
            else
            {
              if(!strcmp(command, "f"))
              {
                base_handle_f( *base);
              }
              else
              {
                if(strstr(command, "fcge"))
                {
                  if(strlen(command) == 4 || strlen(command) == 5)
                  {
                    fprintf(stderr, "./bm.out: Missing parameter for the fcge command\n");
                  }
                  else
                  {
                    cost = strtod( &command[5], &end);
                    if( *end == '\0')
                    {
                      base_handle_fcge( *base, cost);
                    }
                    else
                    {
                      fprintf(stderr, "./bm.out: Invalid parameter for the fcge command\n");
                    }
                  } 
                }
                else
                {
                  if(strstr(command, "fcgt"))
                  {
                    if(strlen(command) == 4 || strlen(command) == 5)
                    {
                      fprintf(stderr, "./bm.out: Missing parameter for the fcgt command\n");
                    }
                    else
                    {
                      cost = strtod( &command[5], &end);
                      if( *end == '\0')
                      {
                        base_handle_fcgt( *base, cost);
                      }
                      else
                      {
                        fprintf(stderr, "./bm.out: Invalid parameter for the fcgt command\n");
                      }
                    }
                  }
                  else
                  {
                    if(strstr(command, "fcle"))
                    {
                      if(strlen(command) == 4 || strlen(command) == 5)
                      {
                        fprintf(stderr, "./bm.out: Missing parameter for the fcle command\n");
                      }
                      else
                      {
                        cost = strtod( &command[5], &end);
                        if( *end == '\0')
                        {
                          base_handle_fcle( *base, cost);
                        }
                        else
                        {
                          fprintf(stderr, "./bm.out: Invalid parameter for the fcle command\n");
                        }
                      }
                    }
                    else
                    {
                      if(strstr(command, "fclt"))
                      {
                        if(strlen(command) == 4 || strlen(command) == 5)
                        {
                          fprintf(stderr, "./bm.out: Missing parameter for the fclt command\n");
                        }
                        else
                        {
                          cost = strtod( &command[5], &end);
                          if( *end == '\0')
                          {
                            base_handle_fclt( *base, cost);
                          }
                          else
                          {
                            fprintf(stderr, "./bm.out: Invalid parameter for the fclt command\n");
                          }
                        }
                      }
                      else
                      {
                        if(strstr(command, "fn"))
                        {
                          if(strlen(command) == 2 || strlen(command) == 3)
                          {
                            fprintf(stderr, "./bm.out: Missing parameter for the fn command\n");
                          }
                          else
                          {
                            base_handle_fn( *base, &command[3]);
                          }
                        }
                        else
                        {
                          if(strstr(command, "fc"))
                          {
                            if(strlen(command) == 2 || strlen(command) == 3)
                            {
                              fprintf(stderr, "./bm.out: Missing parameter for the fc command\n");
                            }
                            cost = strtod( &command[3], &end);
                            if( *end == '\0')
                            {
                              base_handle_fc( *base, cost);
                            }
                            else
                            {
                              fprintf(stderr, "./bm.out: Invalid parameter for the fc command\n");
                            }
                          }
                          else
                          {
                            if(!strcmp(command, "n"))
                            {
                              base_handle_n( *base);
                            }
                            else
                            {
                              if(!strcmp(command, "t"))
                              {
                                base_handle_t( *base);
                              }
                              else
                              {
                                if(!strcmp(command, "v"))
                                {
                                  bm_handle_v();
                                }
                                else
                                {
                                  if(!strcmp(command, "q"))
                                  {
                                    bm_handle_q();
                                  }
                                  else
                                  {
                                    printf("./bm.out: Invalid command\n");
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
      }
    }
  }while(strcmp(command, "q"));
  /**
   * Frees the memory of all files, used structures...
   */
  base_free(base);
  facility_free(facilities);
  xmlFreeDoc(doc);
  xmlCleanupParser();
  return 0;
}
