all:
	cc commands.c matrix.c main.c -o main -lcurl ../../cJSON/cjson.o

test: all
	./main E RR M E