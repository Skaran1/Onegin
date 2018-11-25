#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


unsigned int Number_symbols()
{
    unsigned int Num = 0;
    FILE*f3 = fopen("Shekspir.txt", "rb");
    assert(f3);
    char symbol = 0;
    while (fscanf(f3,"%c", &symbol) != EOF)
    {
        Num ++;
    }

    fclose(f3);
    assert(Num);
    return Num;
}


char* Read_text (unsigned int NumSym)
{
    FILE*f1 = fopen("Shekspir.txt", "rb");
    assert(f1);
    char* pointer = (char*)calloc(NumSym,sizeof(pointer));
    assert(pointer);
    fread (pointer, NumSym, sizeof(char), f1);
    fclose(f1);
    return pointer;
}


int Number_strings (char* pointer)
{
    char symbol = pointer[0];
    int NumStr = 0, i = 0;
    while (symbol != '\0') 
	{
        if (symbol == '\n') 
		{
            NumStr ++;
        }
        i ++;
        symbol = pointer[i];
    }
    return NumStr + 1;
}


char** Divide_text (char* pointer, unsigned int NumSym, int NumStr) 
{
    int i = 0;
    int current_number = 1;
    char** start_str = (char**)calloc (NumStr + 1, sizeof(char*));
    start_str[0] = &pointer[0];
    while (pointer[i] != '\0') 
	{
        if (pointer[i] == '\n')
		{
            start_str[current_number] = &pointer[i+1];
            current_number ++;
        }
        i ++;
    }
    return start_str;
}


void Write_smth (char** start_str, char* pointer, int NumStr) 
{
    FILE*f2 = fopen("Smotri_chto_poluchilos.txt", "a+");

    int i = 0;
    for ( i = 0; i < NumStr; i ++ ) 
	{
        fprintf (f2,"%s\n", start_str[i]);
    }
    fprintf(f2,"\n\n");
    fclose(f2);
}


void Change (char* pointer, unsigned int NumSym, int NumStr) 
{
    int i = 0;
    int current_number = 1;
    char** start_str = (char**)calloc (NumStr + 1, sizeof(char*));
    start_str[0] = &pointer[0];
    while (pointer[i] != '\0') 
	{
        if (pointer[i] == '\n') pointer[i] = '\0';
        if (pointer[i] == '\r') pointer[i] = '\0';
        i ++;
    }
}


int comporator_1 (const void* str1, const void* str2)
{
    char symbol1 = **(char**)str1;
    char symbol2 = **(char**)str2;
    do
    {
        while (symbol1 != '\0')
        {
            if (symbol1 == '.'||
                symbol1 == ','||
                symbol1 == ':'||
                symbol1 == ';'||
                symbol1 == '"'||
                symbol1 == '!'||
                symbol1 == '\''||
                symbol1 == '?'||
                symbol1 == ' ')
                symbol1 = *(&symbol1 + sizeof(char));
            else break;
        }
        while (symbol2 != '\0')
        {
            if (symbol2 == '.'||
                symbol2 == ','||
                symbol2 == ':'||
                symbol2 == ';'||
                symbol2 == '"'||
                symbol2 == '\''||
                symbol2 == '!'||
                symbol2 == '?'||
                symbol2== ' ')
                symbol2 = *(&symbol2 + sizeof(char));
            else break;
        }

        if (symbol1 <= 90 && symbol1 >=65) symbol1 = symbol1 + 32;
        if (symbol2 <= 90 && symbol2 >=65) symbol2 = symbol2 + 32;
        if (symbol1 < symbol2) return -1;
        if (symbol1 == '\0' && symbol2 == '\0') return 0;
        if (symbol1 > symbol2) return 1;
        symbol1 = *(&symbol1 + sizeof(char));
        symbol2 = *(&symbol2 + sizeof(char));
    } while(1);
}


int comporator_2 (const void* str1,const void* str2)
{
    char* symbol1 = *(char**) str1;
    char* symbol2 = *(char**) str2;

    while (*symbol1 != '\0')
    {
        (symbol1)++;
    }
    while (*symbol2 != '\0')
    {
        (symbol2)++;
    }

    (symbol1)-=1;
    (symbol2)-=1;

    do
    {
        while (*symbol1 != '\0')
        {
            if (*symbol1 == '.'||
                *symbol1 == ','||
                *symbol1 == ':'||
                *symbol1 == ';'||
                *symbol1 == '"'||
                *symbol1 == '!'||
                *symbol1 == '?'||
                *symbol1 == ' ')
                symbol1 = (symbol1 - sizeof(char));
            else break;
        }
        while (*symbol2 != '\0')
        {
            if (*symbol2 == '.'||
                *symbol2 == ','||
                *symbol2 == ':'||
                *symbol2 == ';'||
                *symbol2 == '"'||
                *symbol2 == '!'||
                *symbol2 == '?'||
                *symbol2== ' ')
                symbol2 = (symbol2 - sizeof(char));
            else break;
        }


        if (*symbol1 <= 90 && *symbol1 >=65) *symbol1 = *symbol1 + 32;
        if (*symbol2 <= 90 && *symbol2 >=65) *symbol2 = *symbol2 + 32;
        if (*symbol1 < *symbol2) return -1;
        if (*symbol1 == '\0' && *symbol2 == '\0') return 0;
        if (*symbol1 > *symbol2) return 1;
        if (*symbol1 == *symbol2)
        {
       		 symbol1 = symbol1 - sizeof(char);
        	 symbol2 = symbol2 - sizeof(char);
   		 }
    }while(1);
}



int main () 
{
    unsigned int NumSym = Number_symbols();

    char* pointer = Read_text(NumSym);

    int NumStr = Number_strings (pointer);

    char** start_str = Divide_text (pointer,NumSym,NumStr);

    char** copy = Divide_text (pointer,NumSym,NumStr);
	Change(pointer,NumSym,NumStr);

    qsort(start_str, NumStr, sizeof(char*),comporator_1);
    Write_smth (start_str,pointer,NumStr);
    
    qsort(start_str, NumStr, sizeof(char*),comporator_2);
    Write_smth (start_str,pointer,NumStr);

	Write_smth (copy,pointer,NumStr);
    
    return 0;
}

