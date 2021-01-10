#include "declarations.h"

Fields3 *dzejson_explore(char *response)
{
    Fields3 *a = NULL;
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
    a = malloc(sizeof(Fields3));
    cJSON_ArrayForEach(field, list)
    {
        cJSON *x = cJSON_GetObjectItemCaseSensitive(field, "x");
        cJSON *y = cJSON_GetObjectItemCaseSensitive(field, "y");
        cJSON *type = cJSON_GetObjectItemCaseSensitive(field, "type");

        if (!cJSON_IsNumber(x) || !cJSON_IsNumber(y))
        {
            goto end;
        }

        //printf("Payload:x%d: %d\n",i,x->valueint);
        //printf("Payload:y%d: %d\n",i,y->valueint);
        //printf("Payload:Typ pola%d: %s\n",i,type->valuestring);

        //a->x[i] = malloc(sizeof(int));
        a->x[i]=x->valueint;
        //a->y[i] = malloc(sizeof(int));
        a->y[i]=y->valueint;
        a->type[i] = (char*) malloc(sizeof(char) * strlen((type->valuestring) + 1));
        strcpy(a->type[i], type->valuestring);
        i++;
    }

end:
    cJSON_Delete(response_json);
    return a;
}