#include <stdio.h>
#include <string.h>
#define MAXCHAR 1000
#define DELIM " " 

char* get_lexeme( char* line ){
	return strtok(line, DELIM);
}

int main(){
	FILE *fp;
    char str[MAXCHAR];
    char* filename = "test.txt";
   	char* token = "";
   	
    fp = fopen(filename, "r");
    
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    
    //read
    while (fgets(str, MAXCHAR, fp) != NULL){
    	printf("line: %s\n", str);
    	token = get_lexeme(str);
    	//walk through tokens
    	while( token != NULL ) {
      		printf( "Token: %s\n", token );
      		token = strtok(NULL, DELIM);
   		}
	}
        
    fclose(fp);
    return 0;
    
}


//https://www.educative.io/edpresso/splitting-a-string-using-strtok-in-c
