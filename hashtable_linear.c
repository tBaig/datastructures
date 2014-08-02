#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Hash Table with linear probing*/

#define HASH_TAB 100

typedef struct{
    char *key;
}hashtable;

//hash function
unsigned int hash (char *value){
    
    unsigned int hashAddress = 0;
    for (int counter = 0; value[counter] != '\0'; counter++){
        hashAddress = value[counter] + (hashAddress << 6) + (hashAddress << 16) - hashAddress;
    }
    return hashAddress%HASH_TAB;
}


/*search hash table to see if value already exists*/
int member (hashtable table[], char *value){
    int j = hash(value);
    if(table[j].key != NULL){
        if(strcmp(table[j].key,value) == 0){
            return 0;
        }
    }
    for(int i = 0; i < HASH_TAB; i++){
        if(table[i].key != NULL){
            if(strcmp(table[i].key,value) == 0){
                return 0;
            }
        }      
    }
    return 1;
}


char *cpy (char *s) {
    char *d = malloc (strlen (s) + 1);   // Space for length plus nul
    if (d == NULL) 
        return NULL;          // No memory
    strcpy (d,s);                        // Copy the characters
    return d;                            // Return the new string
}

//insert function
int insert (hashtable table[], char *value){
    unsigned int i;
    i  = hash(value); //assign i to be hash key of value
    /*Check if value already exists in hash table*/
    if(member(table, value) == 0){
        return 0;
    }
    /* if not already a member check the key to see if a null value exists*/
    if(table[i].key == NULL){
        table[i].key = cpy(value); //copy the value into hash table
        return 0;
    }
    /*if value already exists at hash key then linear probe for next available slot*/
    else{ 
        for(int j = i; j < HASH_TAB; j ++){ //loop from hash value until end of table
            if(table[j].key == NULL){
                table[j].key = cpy(value);
                return 0;
            }        
        }
        /*there isnt an available slot then start at beginning of hash table until hash value*/
        for(int k = 0; k < i; k ++){
            if(table[k].key == NULL){
                table[k].key = cpy(value);
                return 0;
            }
        }

    }
    return 1; //return 1 indicating hash table is full
}


//print contents of hashtable
void content (hashtable table[]){
    for(int j = 0; j < HASH_TAB; j++){
        if(table[j].key != NULL){
            printf("%s\n", table[j].key, j);
        }
    }
}



/*Delete an individual value from the hash table*/
void delete(hashtable table [], char *value){
    int i = hash(value);
    /*if value happens to exist at hash key, remove it*/
    if(strcmp(table[i].key,value) == 0){
        free(table[i].key);
        table[i].key = NULL;
    }
    /* if value isn't at hash key do a linear probe to find it*/
    else
    {
        for(int j = 0; j < HASH_TAB; j++){
            if(table[j].key != NULL){
                if(strcmp(table[j].key,value) == 0){
                    free(table[j].key);
                    table[j].key = NULL;
                }
            }      
        }   
    }
}

//create the hash table an initialize all possible keys with NULL
void init(hashtable table[]){
    unsigned int i;
    for(i = 0; i < HASH_TAB; i++){
        table[i].key = NULL;
    }
}

/*Destroy the hash table*/
void destroy(hashtable table[]){
    for(int i = 0; i < HASH_TAB; i++){
        free(table[i].key);
    }
}  

int main() {

}

