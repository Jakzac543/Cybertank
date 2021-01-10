#include "declarations.h"


Fields3 *load_explore(char * response, Map *board)
{
    Fields3 *a = NULL;
    a = (Fields3*) malloc(sizeof(Fields3));
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


        board->current_x[i] = x->valueint;
        board->current_y[i] = y->valueint;

        board->types[x->valueint][y->valueint] = (char*) malloc(sizeof(char) * strlen((type->valuestring) + 1));
        strcpy(board->types[x->valueint][y->valueint], type->valuestring);
        i++;
    }

end:
    cJSON_Delete(response_json);
    return a;
}

void wypisz(Map *m)
{
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {   
            if (m->types[i][j] == "(null)") m->types[i][j] = " ";
            else printf("[%6s ] ", m->types[i][j]);
            
        }
        printf("\n");
    }
}



