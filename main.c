#include "declarations.h"

int main(int argc, char **argv) 
{

    Map *board = (Map*) malloc(sizeof(Map));
    char buffer[2048];
	FILE *f = fopen("ex_command.json", "r");
    fread(buffer,1,2048,f);
    fclose(f);
	

    for(int i=0; i<argc; i++)
    {
        if(strcmp(argv[i], "M") == 0) 
        {
            move("qwerty_35");
        }
        else if (strcmp(argv[i], "RL") == 0) 
        {
            rotate_left("qwerty_35");
        }
        else if (strcmp(argv[i], "E") == 0) 
        {
            explore("qwerty_35");
            printf("|%s|\n", buffer);
	        load_explore(buffer, board);
            wypisz(board);
        }
        else if (strcmp(argv[i], "RR") == 0) 
        {
            rotate_right("qwerty_35");
        }
        else if (strcmp(argv[i], "I") == 0) 
        {
            info("qwerty_35");
        }
    }
}