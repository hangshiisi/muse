/*
 ============================================================================
 Name        : LS.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <string.h>

#include "muse_list.h"

void list_with_ints();
void list_with_strings();

bool iterate_int(void *data);
bool iterate_string(void *data);
void free_string(void *data);

int main(int argc, char *argv[])
{
  printf("Loading int demo...\n");
  list_with_ints();
  list_with_strings();
}

void list_with_ints()
{
  int numbers = 10;
  printf("Generating list with the first %d positive numbers...\n", numbers);

  int i;
  list list;
  list_new(&list, sizeof(int), NULL);

  for(i = 1; i <= numbers; i++) {
    list_append(&list, &i);
  }

  list_for_each(&list, iterate_int);

  list_destroy(&list);
  printf("Successfully freed %d numbers...\n", numbers);
}

void list_with_strings()
{
  int numNames = 5;
  const char *names[] = { "David", "Kevin", "Michael", "Craig", "Jimi" };

  int i;
  list list;
  list_new(&list, sizeof(char *), free_string);

  char *name;
  for(i = 0; i < numNames; i++) {
    name = strdup(names[i]);
    list_append(&list, &name);
  }

  list_for_each(&list, iterate_string);

  list_destroy(&list);
  printf("Successfully freed %d strings...\n", numNames);
}

bool iterate_int(void *data)
{
  printf("Found value: %d\n", *(int *)data);
  return TRUE;
}

bool iterate_string(void *data)
{
  printf("Found string value: %s\n", *(char **)data);
  return TRUE;
}

void free_string(void *data)
{
  free(*(char **)data);
}
