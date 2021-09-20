#include <stdio.h>
#include <stdlib.h>
#define MAX 100

/* Return true (non-zero) if c is a whitespace characer
   ('\t' or ' ').
   Zero terminators are not printable (therefore false) */
int delim_character(char c){
    if(c == '\t' || c == ' ' || c == '\r')
        return 1;
    else
        return 0;
}

/* Return true (non-zero) if c is a non-whitespace
   character (not tab or space).
   Zero terminators are not printable (therefore false) */
int non_delim_character(char c){
    if(c != '\t' && c != ' ')
        return 1;
    else
        return 0;
}

/* Returns a pointer to the first character of the next
   space-separated word*/
char *word_start(char* str){
    while(delim_character(*str) == 1)
        str++;
    
    return str;
}

/* Returns a pointer to the first space character of the zero
terminated string*/
char *end_word(char* str){
    while(*str != '\0' && delim_character(*str) == 0){
        str++;
    }
    return str;
}

// counts the number of words or tokens
int count_tokens(char* str){
    int count = 1;
    str = end_word(str);
    while(delim_character(*str) == 1){
        count++;
        printf("%s\n", str);
        str = word_start(str);
        str = end_word(str);
    }

    return count;
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated
   space-separated tokens from zero-terminated str.
   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string"
     tokens[3] = 0
*/
char *copy_str(char *inStr, short len){
    char* ans=(char*) malloc((len + 1) * sizeof(char)); // one byte for null(zero termination)
    char *temp = ans;
    for(int i = 0; i < len; i++,temp++,inStr++){
        *temp = *inStr;
    }
    *temp = '\0'; // include the terminating null character
    return ans;
}

int countCharsInWord(char* str){
    int count = 0;
    while(*str != '\0' && delim_character(*str) == 0){
        str++;
        count++;
    }
    return count;
}

char** tokenize(char* str){
    int countOfTokens = count_tokens(str);
    char** new_string = (char**) malloc((countOfTokens+1) * sizeof(char*));
    char** copy = new_string;
    int count = 0;
    for(int i = 0; i < countOfTokens; i++, copy++){
        str = word_start(str);
        count = countCharsInWord(str);
        *copy = copy_str(str,count);
        str = end_word(str);
    }

    return new_string;
}


void print_all_tokens(char** tokens, int count){
    for(int i = 0; i < count; i++){
        printf("Tokens[%d] = %s", i,*(tokens+i));
        if(i < count-1)
            printf("\n");
    }
}

int main(void){
    char buf[MAX];
    printf("Please enter input string:\n");

    fgets(buf, MAX, stdin);
    
    int count = count_tokens(&buf[0]);
    print_all_tokens(tokenize(&buf[0]), count);
}
