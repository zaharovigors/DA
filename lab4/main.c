#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include <stdbool.h>

#define WRD_LEN 16
#define EXMPL_LEN 10

typedef struct {
    char word[WRD_LEN + 1];
    int word_number;
    int string_number;
    bool string_end;
} TNote;

TNote** ReadExample(FILE *in) {
    int len = EXMPL_LEN, i = 0;
    char c;
    TNote **string = (TNote**)malloc(sizeof(TNote*) * len);
    for(int j = 0; j < len; j++){
        string[j] = NULL;
    }
    while((c = fgetc(in)) == '\n' || c == ' ' || c == '\t');

    while((c != '\n') && (c != EOF)){
        int k = 0;
        TNote* tmp = (TNote*)malloc(sizeof(TNote));
        if(i == len - 1){
            string = (TNote**)realloc(string, len * 2 * sizeof(TNote*));
            len = len * 2;
        }
        tmp->word[k++] = tolower(c);
        while(((c = fgetc(in)) != ' ') && c != '\t' && c != '\n' && k < 16){
            tmp->word[k++] = tolower(c);
        }
        if (k == 16 && c != ' ' && c != '\t' && c != '\n'){
            while(((c = fgetc(in)) != ' ') && c != '\t' && c != '\n');
        }
        for(int a = k; a <= WRD_LEN; a++){
            tmp->word[a] = '\0';
        }
        string[i++] = tmp;
        if(c == '\n'){
            break; 
        }
        while((c = fgetc(in)) == ' ' || c == '\t');
    }
    return string;
}

bool IsEqual(TNote *a, TNote *b){
    if(a == NULL || b == NULL){
        return 0;
    } 
    else if (a->word[0] == '?' || b->word[0] == '?' || strcmp(a->word, b->word) == 0){
            return 1;
    }
    return 0;
}

void Del(TNote ***text){
    if (*text == NULL){
        return;
    }
    TNote *tmp = (*text)[0];
    for(int i = 0; (*text)[i] != NULL; i++){
        if ((*text)[i] != tmp){
            free((*text)[i]);
        }
    }
    free(tmp);
    free(*text);
}

bool ReadTNote(FILE *in, TNote *note){
    char c;
    if (note->string_end) {
        note->string_number = note->string_number + 1;
        note->word_number = 0;
        note->string_end = 0;
    }
    while((c = fgetc(in)) == ' ' || c == '\t' || c == '\n'){
        if(c == '\n'){
            note->word_number = 0;
            note->string_number = note->string_number + 1;
        }
    }
    if(c != EOF){
        int k = 0;
        note->word_number = note->word_number + 1;
        note->word[k++] = tolower(c);
        while(((c = fgetc(in)) != ' ') && c != '\t' && c != '\n' && c != EOF){
            note->word[k++] = tolower(c);
        }
        for(int a = k; a <= WRD_LEN; a++){
            note->word[a] = '\0';
        }
        if(c == '\n'){
           note->string_end = 1; 
        }
    }
    else {
        return 0;
    }
    //printf("%s: (%d, %d)\n", note->word, note->string_number, note->word_number);
    return 1;
}

void SearchMatch(TNote **example, FILE *in) {
    TNote *note = (TNote*)malloc(sizeof(TNote));
    note->string_number = 1;
    note->word_number = 0;
    note->string_end = 0;
    int l = 0, a = 0;
    while(example[++l] != NULL);
    int pref[l];
    pref[0] = 0;   
    for (int i = 1; i < l; ++i) {
        int j = pref[i - 1];
        while ((j > 0) && !IsEqual(example[i], example[j])){
            j = pref[j - 1]; 
        } 
        if (IsEqual(example[i], example[j])){
            ++j;
        }
        pref[i] = j;
    }
    int j = 0;
    while (ReadTNote(in, note)) {
                //printf("%d\n", a);
                example[a]->string_number = note->string_number;
                example[a]->word_number = note->word_number;
                ++a;
                if(a == l){
                    a = 0;
                }
        while ((j > 0) && !IsEqual(note, example[j])){
            j = pref[j - 1];
        }
        if (IsEqual(note, example[j])){
            ++j;
        }  
        if (j == l){
            //printf("%d\n", a);
            printf("%d, %d\n", example[a]->string_number, example[a]->word_number);
        }
    }
    free(note);
}

int main(void){
    TNote** example = ReadExample(stdin);
    SearchMatch(example, stdin);
    Del(&example);
    return 0;
} 

