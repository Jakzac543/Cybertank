#include "declarations.h"


static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp)
{

    size_t realsize = size * nmemb;


    Memory *mem = (Memory *) userp;

    char *ptr = NULL;


    if (mem->response != NULL)
        ptr = realloc(mem->response, mem->size + realsize + 1);
    else
        ptr = malloc(mem->size + realsize + 1);

    if (ptr == NULL)
        return 0; 

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;

    return realsize;
}

 void * make_request(char *url, char *name)
 {
    CURL *curl;
    CURLcode res;
    Memory chunk;
    chunk.size = 0;
    chunk.response = NULL;
    FILE *fin = fopen(name, "w");

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);


        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);



        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);


        res = curl_easy_perform(curl);

 
        if (res != CURLE_OK)
            fprintf(stderr, "Błąd! curl_easy_perform() niepowodzenie: %s\n", curl_easy_strerror(res));
        else
        {
            fprintf(fin, "%s", chunk.response);
        }


        free(chunk.response);
        curl_easy_cleanup(curl);
    }
}
int info(char *token) 
{
    char url[100] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/";
    strcat(url, token);
        make_request(url, "command.json");
    return 0;
}

 int move(char *token) 
 {
    char url[100] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/";
    strcat(url, token);
        make_request(url, "command.json");
    return 0;

 }

 int rotate_right(char *token) 
 {
     char url[100] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/";
    strcat(url, token);
    char url2[100] ="/right";
    strcat(url, url2);
        make_request(url, "command.json");
        return 0;
}
 int rotate_left(char *token) 
 {
     char url[100] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/";
    strcat(url, token);
    char url2[100] ="/left";
    strcat(url, url2);
        make_request(url, "command.json");
        return 0;
 }

 int explore(char *token) 
 {
    char url[201] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/";
    strcat(url, token);
    make_request(url, "ex_command.json");
    return 0;

 }

// int main(int argc, char **argv)
// {
//     for(int i=0; i<argc; i++)
//     {
//     if(strcmp(argv[i], "M") == 0) move("qwerty_35");
//     else if (strcmp(argv[i], "RL") == 0) rotate_left("qwerty_35");
//     else if (strcmp(argv[i], "E") == 0) explore("qwerty_35");
//     else if (strcmp(argv[i], "RR") == 0) rotate_right("qwerty_35");
//     else if (strcmp(argv[i], "I") == 0) info("qwerty_35");
//     }
//     return 0;
// }