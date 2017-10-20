#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "string.h"
#include <unistd.h>

struct node {
    char x[50];
    struct node *next;
    struct node *prev;
};

typedef struct node node;
typedef struct node* nodePtr;
typedef struct node** nodePtrPtr;

FILE *inpf1,*inpf2;
nodePtr createLinkedListFromInputFile(FILE *inputFile);
nodePtr insert_sorted(nodePtrPtr, char[]);
nodePtr delete(nodePtrPtr, char[]);
nodePtr search(nodePtr, char[]);
void showTheList (nodePtr header);
nodePtr insert_original(nodePtrPtr header , char x[]); //Insert the node without sort or any other comparements . For input files !
nodePtr buildOneGrams(nodePtrPtr header1 ,nodePtrPtr one_gr_hdr, char currentString[]);
nodePtr buildTwoGrams (nodePtrPtr header1 , nodePtrPtr header2 , nodePtrPtr two_gr_hdr);
void showTheReversedList ( nodePtr header) ;
char* convertToAlphabet(char line[]);
char* concat(const char *s1, const char *s2);


int main() {
    
    nodePtr hdr1,hdr2, one_gr_hdr , two_gr_hdr;
    char *word,*word2;  // I am creating a new word variable for input2 current word pointer because it is crashing the main thread when try to kill the program .
    
    word = malloc(sizeof(char[50]));
    word2 = malloc(sizeof(char[50]));
    
    
    
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("Current working dir: %s\n", cwd); //Want to see the path.

    // read file and construct LL
    if((inpf1 = fopen("/Users/onur/Desktop/Projects/Academic-C-Projects/TextSimilarityNGrams-150116825/TextSimilarityNGrams-150116825/input1.txt","r")) == NULL){
        printf("Input1 File Could Not Be Opened!\n");
        return 0;
    }
    if((inpf2 = fopen("/Users/onur/Desktop/Projects/Academic-C-Projects/TextSimilarityNGrams-150116825/TextSimilarityNGrams-150116825/input2.txt","r")) == NULL){
        printf("Input2 File Could Not Be Opened!\n");
        return 0;
    }
    hdr1 = malloc(sizeof(nodePtr)) ;
    hdr2 = malloc(sizeof(nodePtr));
    one_gr_hdr = malloc(sizeof(nodePtr)) ;
    two_gr_hdr= malloc(sizeof(nodePtr)) ;
    
    hdr1 ->next = NULL;
    hdr2 ->next = NULL;
    one_gr_hdr ->next = NULL;
    two_gr_hdr ->next = NULL;
    
    hdr1 ->prev = NULL;
    hdr2 ->prev = NULL;
    one_gr_hdr ->prev = NULL;
    two_gr_hdr ->prev = NULL;
    
    while (!feof(inpf1)) {
        while (fscanf(inpf1, " %1023s", word) == 1) {
            //printf("\nCurrent Word in Input1 : %s \n",word);
            word = convertToAlphabet(word); //LowerCase Implementation !
            if(insert_original(&hdr1, word)==NULL){
                printf("\nInsert Original went wrong !") ;
            }
        }
        
    }
    while (!feof(inpf2)) {
        while (fscanf(inpf2, " %1023s", word2) == 1) {

            word2 = (convertToAlphabet(word)); //LowerCase Implementation !
            nodePtr currentNodeHdr2 = insert_original(&hdr2, word2);
            if(currentNodeHdr2==NULL){
                printf("\nInsert Original went wrong !") ;
            }
            else{
                    nodePtr searchResultHdr1 = search(hdr1, word2);

                    while (searchResultHdr1!=NULL && strcmp(searchResultHdr1->x,word2)==0) {
                    insert_sorted(&one_gr_hdr, word2) ;
                    
                    if (currentNodeHdr2->prev == NULL ) { // If any node is the starter node , we will search the nextS !
                        
                        printf("HDR2 node is the starter node !");
                        break;
                        
                        
                    }else if (searchResultHdr1->prev != NULL && strcmp(searchResultHdr1->prev->x,currentNodeHdr2->prev->x)==0 ){
                        
                        char *result = concat(searchResultHdr1->prev->x,searchResultHdr1->x);
                        printf("\nTwo Gram is found! : %s" , result);
                        insert_sorted(&two_gr_hdr,result );
                        break;
                        
                        
                    }
                    else {
                        
                        if (searchResultHdr1->next != NULL){
                            
                            searchResultHdr1 = search(searchResultHdr1->next, word2);
                            
                        }else {
                            searchResultHdr1 = NULL;
                        }
                        
                    }
                   
                }
            }

        }
    }
    
            printf("\n-- Linked List 1 for Input1 File --\n");
            showTheList(hdr1->next);
    
            printf("\n-- Linked List 2 for Input2 File --\n");
            showTheList(hdr2->next);
    
            printf("\n\n-- Linked List One Gram Header --\n");
            showTheList(one_gr_hdr->next);
    
           printf("\n-- Linked List Two Gram Header --\n");
           showTheList(two_gr_hdr->next);
    
    fclose(inpf1);
    fclose(inpf2);
    
    return 0;
}

char* concat(const char *s1, const char *s2){ //For string combining in 2_grams.
    char *result = malloc(strlen(s1)+strlen(s2)+strlen(" ")+1);//+1 for the null-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result," ");
    strcat(result, s2);
    return result;
}


char* convertToAlphabet(char *line){//Deletes all the unused data in strings.
    int i ,j;
    line[0] = tolower(line[0]);
    for(i = 0; line[i] != '\0'; ++i)
    {
        while (!( (line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z') || line[i] == '\0') )
        {
            for(j = i; line[j] != '\0'; ++j)
            {
                line[j] = line[j+1];
            }
            line[j] = '\0';
        }
    }
    
    
    return line;
}


nodePtr insert_original(nodePtrPtr header , char x[]){ //Insert the node without sort or any other comparements . For input files !
    
    nodePtr newNode, temp, prev;
    
    // create node to insert and assign values to its fields
    newNode= malloc(sizeof(node));
    strcpy(newNode->x,x);
    newNode->next=NULL;
    newNode->prev=NULL;
    prev = *header ;
    // if LL empty
    if ((*header)->next == NULL)
        (*header)->next = newNode;
    // if LL not empty
    else {
        temp=(*header)->next;
        while (temp != NULL ) {
            prev=temp;
            temp=temp->next;
        }
        newNode->prev = prev ;
        prev->next=newNode;
        
    }
    
    return newNode;
   
}

nodePtr insert_sorted(nodePtrPtr header, char x[]){ //Insert ith sorted fashion , eliminate the similarities.
    
    nodePtr newNode, temp, prev;
    
    // create node to insert and assign values to its fields
    newNode = malloc(sizeof(node));
    strcpy(newNode->x,x);
    newNode->next=NULL;
    newNode->prev =NULL;
    prev = *header;
    // if LL empty
    if ((*header)->next == NULL){
        (*header)->next=newNode;
        newNode->prev = (*header);
    }
    // if LL not empty
    else {
        temp=(*header)->next;
        while (temp != NULL && strcmp(temp->x,newNode->x) < 0 ) {
            prev=temp;
            temp=temp->next;
        }
        
        if (temp!=NULL && strcmp(temp->x,newNode->x)==0 ) {
            // Existent key !
            return NULL;
        }
        
        // insert node in a sorted fashion
        if (temp!=NULL){
            
            newNode->prev = prev;
            newNode->next=temp;
            temp->prev = newNode ;
            prev->next = newNode ;
            
        }else { //If the node is supposed to be the last node .
            
            newNode->prev = prev ;
            prev->next=newNode;
        }
    
        
        
    }
    
    return newNode;
    
}

void showTheReversedList ( nodePtr header) { //For demo if we want to see the reversed list .
    
    nodePtr iterator = header;
    while (iterator->next != NULL) {
        
        iterator = iterator->next;
        
    }
   // iterator = iterator->prev;
    while(iterator != NULL && strcmp(iterator->x , "") != 0){
        printf(" %s ->",iterator->x);
        iterator = iterator->prev;
    }
    
    
    
}

void showTheList (nodePtr header){ //Listing function for showing the results.
    nodePtr iterator = header;
    printf("\nNodes :");
    int counter = 0 ;
    while(iterator != NULL && strcmp(iterator->x , "") != 0){
        printf(" %s ->",iterator->x);
        iterator = iterator->next;
        counter++;
    }
    printf("\nNumber of Common Words : %d\n",counter);
    
    
}

nodePtr search(nodePtr header, char x[]){ //Searching the lists for desired input.

    nodePtr temp;
    temp=header;

    while (temp != NULL && strcmp(temp->x,x) != 0 ){
        temp=temp->next;
    }

    if (temp==NULL) {
        // end of LL ... key non-existent ...
        // Non - Existent key !
        return NULL;
    }
    if (strcmp(temp->x,x)==0 )
        // search successful ...
        return temp;
    else {    // key non-existent ...
        // Non - Existent key !
         return NULL;
    }

}
