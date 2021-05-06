#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXCHAR 1000
#define WHITESPACE " \t\n"
#define DELIM ";,"


int main(){
	FILE *fp;
    char str[MAXCHAR];
    char line[MAXCHAR][MAXCHAR];
    char code[MAXCHAR];
   	char c = '0';
   	char* filename = "test.pas";
   	
    fp = fopen(filename, "r");
    while ( c != EOF  ){
    	c = fgetc ( fp ) ; 
     	printf ( "%c", c ) ;
     	
   	}
    fclose(fp);
    return 0;
}

