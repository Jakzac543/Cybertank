#include "declarations.h"

 Map *load_file(char *file)
 {
    Map *board = (Map*) malloc (sizeof(Map));

    int i = 0;
    char buffer[2048];
    FILE *g = fopen(file, "r");

    fread(buffer,sizeof(char),2047,g);
    //printf("%s", buffer);
    //printf("%ld",strlen(buffer));
    for(i=0; i<strlen(buffer); i++)
      {
         printf("{%c}", buffer[i]);
         //printf("%ld!\n", strlen(buffer));
      }
     fclose(g);
  
     return board;
 }


Map *load_explore(char * response, Map *board)
{
    //Map *board = (Map*) malloc (sizeof(Map));

    int i=0;
    const cJSON *status = NULL;
    const cJSON *payload = NULL;
    const cJSON *list = NULL;
    const cJSON *field = NULL;
    cJSON *response_json = cJSON_Parse(response);
    if (response_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        goto end;
    }

    status = cJSON_GetObjectItemCaseSensitive(response_json, "status");
    payload = cJSON_GetObjectItemCaseSensitive(response_json, "payload");
    list = cJSON_GetObjectItemCaseSensitive(payload, "list");

    cJSON_ArrayForEach(field, list)
    {
        cJSON *x = cJSON_GetObjectItemCaseSensitive(field, "x");
        cJSON *y = cJSON_GetObjectItemCaseSensitive(field, "y");
        cJSON *type = cJSON_GetObjectItemCaseSensitive(field, "type");

        if (!cJSON_IsNumber(x) || !cJSON_IsNumber(y))
        {
            goto end;
        }



        board->x[i] = x->valueint;
        board->y[i] = y->valueint;
        


        board->types[x->valueint][y->valueint] = (char*) malloc(sizeof(char) * strlen((type->valuestring) + 1));
        if (strcmp(type->valuestring, "grass") == 0) board->types[x->valueint][y->valueint] = '1';
        else if (strcmp(type->valuestring, "wall")==0) board->types[x->valueint][y->valueint] = '2';
        else if (strcmp(type->valuestring, "sand")==0) board->types[x->valueint][y->valueint] = '3';
    
        i++;
    }

end:
    cJSON_Delete(response_json);
    return board;
}

void wypisz(Map m)
{
    FILE *fin = fopen("game.txt", "w+");
    char g[6] = "grass";
    char w[5] = "wall";
    char s[5] = "sand";
    char *a;
    int d = 0;
    int i,j;
    //printf("%d %d !!!\n",m.max_x, m.max_y);
    for(i=0;i<20;i++)
    {
        for(j=0;j<20;j++)
        {   
            if (m.types[j][i]) printf(" %s ", m.types[j][i]);
            else printf ("[  ]");
            
            if (m.types[j][i]) fprintf(fin," %s ", m.types[j][i]);
            else fprintf (fin,"[  ]");
        }
        printf("\n");
        fprintf(fin,"\n");
    }
}



