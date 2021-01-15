#ifndef _DECS_H
#define _DECS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../cJSON/cJSON.h"
#include <curl/curl.h>

typedef struct _Memory
{
    char *response;
    size_t size;
} Memory;


typedef struct _Fields3
{
    char *type[3];
    int x[3];
    int y[3];
} Fields3;

typedef struct _Map
{
    char *types[20][20];
    int current_x[20];
    int current_y[20];
    int max_x;
    int max_y;
} Map;


int info(char *token); 
int move(char *token); 
int rotate_right(char *token); 
int rotate_left(char *token);
int explore(char *token);
Map *load_file(char *file);
Map *load_explore(char * response, Map *board);
void wypisz(Map m);





#endif