#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXCHAR 1000
#define WHITESPACE " \t\n"
#define DELIM ";,"


char* get_lexeme( char* line ){
	char new_line[MAXCHAR] = "";
	char str[100];
	int n = 0;
	int off = 0;
	int j;
	char c;
	
	for(i=0; i < strlen(line); i++){
		c = line[i];
		
		if(c == '{' || c == '}' ||  c == '('  || c == ')' || c == ',' || c == ';'){
		   	str[0] = c;
		   	strcat(str, "**");
		}else if(isalpha(c)){
			str[0] = c;
			while(isalpha(line[i+1])){
				c = line[i+1]; i++;
				strcat(new_line, c);
			}strcat(str, "**");
		}else if(isdigit(c)){
			str[0] = c;
			while(isdigit(line[i+1])){
				c = line[i+1]; i++;
				strcat(new_line, c);
			}strcat(str, "**");
		}else if(c == '-' ||  c == '+'  || c == '*' || c == '/' || c == '%'){
			str[0] = c;
		   	strcat(str, "**");
		}else if(c == '<' || c == '>' || c == '='){
			str[0] = c;
			if(c != '=' && line[i+1] == '='){
				c = line[i+1]; i++;
				strcat(str, c);
			}strcat(str, "**");
		}else if(c == ':'){
			str[0] = c;
			if(line[i+1] == '='){
				c = line[i+1]; i++;
				strcat(str, c);
			}strcat(str, "**");
		}
		
	  }
	 strcpy(line, new_line);
	 return strtok(line, "**");
}

int main(){
	
	FILE *fp;
    char str[MAXCHAR];
    char line[MAXCHAR];
    char temp[MAXCHAR];
    char* filename = "test.pas";
   	char* token = "";
   	int n;
   	int off;
   	char* type;
   	int i;
   	char c;
   	
   	int count = 1;
   	
    fp = fopen(filename, "r");
    
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    
    	while( read_line(fp, line) == 1){
    	//	puts(line);
    		token = get_lexeme(line);
    	
    		while( token != NULL ) {
      			printf( "\nTOkEN: %s\n", token );
      			token = strtok(NULL, " ");
   			}
		}
    
    fclose(fp);
    return 0;
}

