/**
 * \file facility.c
 */
#include <stdio.h> /* standard Input/Output Header */
#include <stdlib.h> /* standard library defined by ANSI */
#include <string.h> /* defines variables type, macro, and various functions for manipulating arrays of characters */
#include "facility.h" /* for function heading and definitions of facility.c */
/**
 * Function that creates a facility.
 */
facility_t *facility_create()
{
  facility_t *inst = NULL;
  inst = malloc(sizeof(facility_t));
  inst -> area = 0;
  inst -> cost = 0.00;
  inst -> name = NULL;
  return inst;
  free(inst);
}
/**
 * Function that frees the memory of a facility.
 */
void facility_free(facility_t *facility)
{
  free(facility);
}
/**
 * Function that displays information about the facilities of the base.
 */
void facility_handle_f(facility_t facility)
{
  printf("%s, %d m2, %.2f USD\n", facility.name, facility.area, facility.cost);
}
/**
 * Function that displays a facility with the corresponding price.
 */
void facility_handle_fc(facility_t facility, double cost)
{
  if(facility.cost == cost)
  {
    printf("%s, %d m2, %.2f USD\n", facility.name, facility.area, facility.cost);
  }
}
/**
 * Function that displays a facility with the corresponding higher or equal price.
 */
void facility_handle_fcge(facility_t facility, double cost)
{
  if(facility.cost >= cost)
  {
    printf("%s, %d m2, %.2f USD\n", facility.name, facility.area, facility.cost);
  }
}
/**
 * Function that displays a facility with the corresponding higher price.
 */
void facility_handle_fcgt(facility_t facility, double cost)
{
  if(facility.cost > cost)
  {
    printf("%s, %d m2, %.2f USD\n", facility.name, facility.area, facility.cost);
  }
}
/**
 * Function that displays a facility with the corresponding lower or equal price.
 */
void facility_handle_fcle(facility_t facility, double cost)
{
  if(facility.cost <= cost)
  {
    printf("%s, %d m2, %.2f USD\n", facility.name, facility.area, facility.cost);
  }
}
/**
 * Function that displays a facility with the corresponding lower price.
 */
void facility_handle_fclt(facility_t facility, double cost)
{
  if(facility.cost < cost)
  {
    printf("%s, %d m2, %.2f USD\n", facility.name, facility.area, facility.cost);
  }
}
/**
 * Function that displays a facility with NAME in its name.
 */
void facility_handle_fn(facility_t facility, const char *name)
{
  if(strstr(facility.name, name) != NULL)
  {
    printf("%s, %d m2, %.2f USD\n", facility.name, facility.area, facility.cost);
  }
}