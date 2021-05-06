#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXCHAR 1000
#define WHITESPACE " \t\n"
#define DELIM ";,"

int codeline = 0;
char errors[100] = "";

int read_line(FILE* fp, char* line ){
	 if( fscanf(fp, " %[^\n]\n", line) == 1)
	 	return 1;
	else return 0;
}
char* get_lexeme( char* line){
	char new_line[MAXCHAR] = "";
	char str[100];
	int n = 0;
	int off = 0;
	int j;
	char c = '0';
	int i;
	
	//DFA implementation
	for(i=0; i < strlen(line); i++){
		//printf("%c", line[i]);
		c = line[i];
		strcpy(str, "");
		
		
		if(c == '('  || c == ')' || c == ',' || c == ';' || c == '.' || c == '[' || c == ']' ){
		   	strncat(str, &c, 1);
		   	strcat(str, " ");
		}else if(isalpha(c)){
	
			strncat(str, &c, 1);
			while(isalpha(line[i+1]) || isdigit(line[i+1])){
				i+=1;
				c = line[i]; 
				strncat(str, &c, 1);
			}strcat(str, " ");
		
		}else if(isdigit(c) || ((c == '-' || c == '+' ) && isdigit(line[i+1]))){
			strncat(str, &c, 1);
			
			while( line[i+1] != ' ' || line[i+1] == '-' ||  line[i+1] == '+'  || line[i+1] == '*' 
			|| line[i+1] == '/' || line[i+1] == '%'){
				i+=1;
				c = line[i]; 
				strncat(str, &c, 1);
			}strcat(str, " ");

		}else if(c == '-' ||  c == '+'  || c == '*' || c == '/' || c == '%'){
			strncat(str, &c, 1);
		   	strcat(str, " ");
		}else if(c == '<' || c == '>' || c == '='){
			strncat(str, &c, 1);
			if(c != '=' && line[i+1] == '='){
				i+=1;
				c = line[i]; 
				strncat(str, &c, 1);
			}strcat(str, " ");
		}else if(c == ':'){
			strncat(str, &c, 1);
			if(line[i+1] == '='){
				i+=1;
				c = line[i]; 
				strncat(str, &c, 1);
			}strcat(str, " ");
		}else if(c == '\''){
			strncat(str, &c, 1);
			while(line[i+1] != '\''){
				i+=1;
				if(i<strlen(line)){
					c = line[i]; 
					if(c == ' ') c = '_';
					strncat(str, &c, 1);
					if(line[i+1] == '\''){	
						i+=1; 
						c = line[i]; 
						strncat(str, &c, 1);
						break;
					}	
				}else{
					break;
				}
			}
			strcat(str, " ");
		}else if(c == '{'){
			strncat(str, &c, 1);
			while(line[i+1] != '}'){
				i+=1;
				if(i<strlen(line)){
					c = line[i]; 
					strncat(str, &c, 1);
					if(line[i+1] == '}'){	
						i+=1; 	
						c = line[i]; 
						strncat(str, &c, 1);
						break;
					}else{
						break;
					}
				}
			}
		}else if(c != '\t' && c!= ' '){
			str[0] = c;
		}
			strcat(str, " ");
			strcat(new_line, str);
		}
	 strcpy(line, new_line);
	 return strtok(line, " ");
}

int isidentifier(char* lexeme){
	int i;
	if(!isalpha(lexeme[0])){
		return 0;
	}
	for (i = 1; i < strlen(lexeme); i++) {
		if( !isalnum(lexeme[i]) )
			return 0;
	}
	return 1;
}

int isInvalidIdentifier(char* lexeme){
	if(strlen(lexeme) > 1)
		return 1;
	else return 0;
}

int isstring(char* lexeme){
	if(lexeme[0] == '\'' && lexeme[strlen(lexeme) -1 ] == '\'' && strlen(lexeme) > 3)
	{
		return 1;
	}
	else return 0;
	
}

int ischaracter(char* lexeme){
	if(lexeme[0] == '\'' && lexeme[strlen(lexeme) -1 ] == '\'' && strlen(lexeme) == 3) {
		return 1;
	}else return 0;
}

int isinteger(char* lexeme){
	int i;
	for (i = 0; i < strlen(lexeme); i++) {
		if( !isdigit(lexeme[i])) return 0;
	}
	return 1;
}

int isreal(char* lexeme){
	int i;
	for (i = 0; i < strlen(lexeme); i++) {
		if( !isdigit(lexeme[i]) && ! lexeme[i] != '.'){
				return 0;
		}
	}
	return 1;
}

int iscomment(char* lexeme){
	if(lexeme[0] == '{' && 
	   lexeme[strlen(lexeme)-1] == '}'){
		return 1;
	}
	return 0;
}

int console_dump( char* lexeme, char* token_class ){
	printf( "%s\t\t%s\n", lexeme, token_class);
}



void print_error(char* code){
	FILE *fp;
	int line;
	char* filename = "error.txt";
    fp = fopen(filename, "r");
    
    while(fgets(code, MAXCHAR, fp)){
    	printf("Line %s",code);
	}fclose(fp);
}

char* classify_lexeme( char* lexeme ){
	//reserved words
	char c = codeline + '0';
    if (!strcmp(lexeme, "program") ||  !strcmp(lexeme, "and")  || !strcmp(lexeme, "array")  || !strcmp(lexeme, "for")  
		|| !strcmp(lexeme, "while")  || !strcmp(lexeme, "begin")  || !strcmp(lexeme, "or")  ||!strcmp(lexeme, "of")  
		|| !strcmp(lexeme, "to")  || !strcmp(lexeme, "do")  || !strcmp(lexeme, "end")  || !strcmp(lexeme, "not") 
		|| !strcmp(lexeme, "if")  || !strcmp(lexeme, "downto")  || !strcmp(lexeme, "mod")  || !strcmp(lexeme, "function")
		|| !strcmp(lexeme, "var")  || !strcmp(lexeme, "then")  || !strcmp(lexeme, "repeat")  || !strcmp(lexeme, "div")
		|| !strcmp(lexeme, "procedure")  || !strcmp(lexeme, "const")  || !strcmp(lexeme, "else")  || !strcmp(lexeme, "until")
		|| !strcmp(lexeme, "return"))
        return "RESERVED";
	else if (!strcmp(lexeme, "boolean") ||  !strcmp(lexeme, "real")  || !strcmp(lexeme, "true")  || !strcmp(lexeme, "read")  
		|| !strcmp(lexeme, "write")  || !strcmp(lexeme, "char")  || !strcmp(lexeme, "integer")  ||!strcmp(lexeme, "false")  
		|| !strcmp(lexeme, "readln")  || !strcmp(lexeme, "writeln")  || !strcmp(lexeme, "string"))
        return "PREDECLARED IDENTIFIER";
	else if (!strcmp(lexeme, ";"))
        return "SEMICOLON";
    else if (!strcmp(lexeme, "."))
        return "END";
    else if (!strcmp(lexeme, ","))
        return "COMMA";
    else if (!strcmp(lexeme, ":"))
        return "COLON";
    else if (!strcmp(lexeme, "["))
        return "RIGHT BRACKET";
    else if (!strcmp(lexeme, "]"))
        return "LEFT BRACKET";
    else if (!strcmp(lexeme, "+") || !strcmp(lexeme, "-") || !strcmp(lexeme, "/") || !strcmp(lexeme, "*") || 
	!strcmp(lexeme, "%") || !strcmp(lexeme, "<") || !strcmp(lexeme, ">") || !strcmp(lexeme, "<=") || !strcmp(lexeme, ">=")
		|| !strcmp(lexeme, "=") || !strcmp(lexeme, ":=")  ) 
        return "OPERATOR";
    else if(isidentifier(lexeme))
    	return "IDENTIFIER";
    else if (!strcmp(lexeme, "("))
        return "RIGHT PARENTHESIS";
    else if (!strcmp(lexeme, ")"))
        return "LEFT PARENTHESIS";
    else if (lexeme[0] == '{' && lexeme[strlen(lexeme)-1] == '}')
        return "COMMENT";
    else if(isinteger(lexeme) == 1){
    	return "INTEGER";
	}else if(isreal(lexeme) ==1 ){
		return "REAL";
	}else if(isstring(lexeme) == 1){
		return "STRING";
	}else if(ischaracter(lexeme) == 1){
		return "CHARACTER";
	}else if(isInvalidIdentifier(lexeme) == 1){
		strncat(errors, &c, 1);
		strcat(errors, "\tINVALID IDENTIFIER\n");
		return "INVALID IDENTIFIER";
	}
	else  if(isInvalidIdentifier(lexeme) == 0){
		strncat(errors, &c, 1);
		strcat(errors, "\tUNIDENTIFIED SYMBOL\n");
		return "UNINDENTIFIED SYMBOL";
	} 
}

int file_dump( FILE* outputFile, char* lexeme, char* token_class){
	fprintf (outputFile, "%s %s\n",lexeme, token_class);
}



int main(){
	FILE *fp, *fp2, *fp3;
    char str[MAXCHAR];
    char line[MAXCHAR];
    char temp[MAXCHAR];
    char* filename = "Team4_1.pas";
    char* filename2 = "output.txt";
    char* filename3 = "error.txt";
   	char* token = "";
   	char* token_type = "";
   	int n;
   	int off;
   	char* type;
   	int i;
   	char c;
   	int count = 1;
   	
    fp = fopen(filename, "r");
    fp2 = fopen(filename2, "w");
    
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    
    if (fp2 == NULL){
        printf("Could not open file %s",filename2);
        return 1;
    }
    
    if (fp3 == NULL){
        printf("Could not open file %s",filename3);
        return 1;
    }
    
    
    	while( read_line(fp, line) == 1){
    	//	puts(line);
    		codeline++;
    		token = get_lexeme(line);
    		while( token != NULL ) {
      			token_type = classify_lexeme(token);
      			console_dump(token, token_type);
      			file_dump(fp2, token, token_type);
      			token = strtok(NULL, " ");
   			}
		}
		strcpy(line, "");
		fclose(fp2);
		
		fp3 = fopen(filename3, "w");
		puts("=====================================");
		fprintf (fp3, "%s",errors);
		fclose(fp3);
		print_error(str);
    	fclose(fp);
    return 0;
}


//https://www.educative.io/edpresso/splitting-a-string-using-strtok-in-c
