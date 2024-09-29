/**
 * \file base.c
 */
#include <stdio.h> /* standard Input/Output Header */
#include <stdlib.h> /* standard library defined by ANSI */
#include <string.h> /* defines variables type, macro, and various functions for manipulating arrays of characters */
#include "base.h" /* for function heading and definitions of base.c */
#include "facility.h" /* for function heading and definitions of facility.c */
/**
 * Function that adds a facility to the base.
 */
int base_add_facility(base_t *base, facility_t *facility)
{
  base->facilities = realloc(base->facilities, (base->nfacilities+1) *sizeof(facility_t *));
  if(base->facilities == NULL)
  {
    return -1;
  }
  base->facilities[base->nfacilities] = facility;
  base->nfacilities++;
  return 0;
}
/**
 * Function that creates a base.
 */
base_t *base_create()
{
  base_t *bs = NULL;
  bs = malloc(sizeof(base_t));
  bs -> country = NULL;
  bs -> day = 0;
  bs -> facilities = NULL;
  bs -> month = 0;
  bs -> name = NULL;
  bs -> nfacilities = 0;
  bs -> year = 0;
  return bs;
  free(bs);
}
/**
 * Function that frees the base memory.
 */
void base_free(base_t *base)
{
  free(base);
}
/**
 * Function that displays the base.
 */
void base_handle_b(base_t base)
{
  printf("%s (%d-%d-%d, %s)\n", base.name, base.year, base.month, base.day, base.country);
}
/**
 * Function that displays the base country.
 */
void base_handle_c(base_t base)
{
  printf("%s\n", base.country);
}
/**
 * Function that displays the base date.
 */
void base_handle_d(base_t base)
{
  printf("%d-%d-%d\n", base.year, base.month, base.day);
}
/**
 * Function that displays base facility.
 */
void base_handle_f(base_t base)
{
  int i;
  for(i=0; i<base.nfacilities; i++)
  {
    facility_handle_f( *base.facilities[i]);
  }
}
/**
 * Function that displays a facility with the corresponding price.
 */
void base_handle_fc(base_t base, double cost)
{
  int i;
  for(i=0; i<base.nfacilities; i++)
  {
    facility_handle_fc( *base.facilities[i], cost);
  }
}
/**
 * Function that displays facilities with the corresponding higher or equal price.
 */
void base_handle_fcge(base_t base, double cost)
{
  int i;
  for(i=0; i<base.nfacilities; i++)
  {
    facility_handle_fcge( *base.facilities[i], cost);
  }
}
/**
 * Function that displays facilities with the corresponding higher price.
 */
void base_handle_fcgt(base_t base, double cost)
{
  int i;
  for(i=0; i<base.nfacilities; i++)
  {
    facility_handle_fcgt( *base.facilities[i], cost);
  }
}
/**
 * Function that displays facilities with the corresponding lower or equal price.
 */
void base_handle_fcle(base_t base, double cost)
{
  int i;
  for(i=0; i<base.nfacilities; i++)
  {
    facility_handle_fcle( *base.facilities[i], cost);
  }
}
/**
 * Function that displays facilities with the corresponding higher price.
 */
void base_handle_fclt(base_t base, double cost)
{
  int i;
  for(i=0; i<base.nfacilities; i++)
  {
    facility_handle_fclt( *base.facilities[i], cost);
  }
}
/**
 * Function that displays facilities with NAME in their name.
 */
void base_handle_fn(base_t base, const char *name)
{
  int i;
  for(i=0; i<base.nfacilities; i++)
  {
    facility_handle_fn( *base.facilities[i], name);
  }
}
/**
 * Function that displays the name of the base.
 */
void base_handle_n(base_t base)
{
  printf("%s\n", base.name);
}
/**
 * Function that displays the total cost of the base.
 */
void base_handle_t(base_t base)
{
  int i;
  double b;
  for(i=0; i<base.nfacilities; i++)
  {
    b += base.facilities[i]->cost;
  }
  printf("%.2f USD\n", b);
}