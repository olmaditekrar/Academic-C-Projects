#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct node {
    char x[25];
    struct node *next;
};

typedef struct node node;
typedef struct node* nodePtr;
typedef struct node** nodePtrPtr;

FILE *inpf1,*inpf2;
nodePtr createLinkedListFromInputFile(FILE *inputFile);
int insert_sorted(nodePtrPtr, char[]);
nodePtr delete(nodePtrPtr, char[]);
nodePtr search(nodePtr, char[]);
void showTheList (nodePtr header);
int insert_original(nodePtrPtr header , char x[]); //Insert the node without sort or any other comparements . For input files !
void buildOneGrams(nodePtrPtr header1 ,nodePtrPtr one_gr_hdr, char currentString[]);




int main() {
    
    nodePtr hdr1,hdr2, p, q, r , one_gr_hdr , two_gr_hdr;
    char word[10],word2[10];  // I am creating a new word variable because it is crashing the main thread when try to kill the program .
    char op;
    int posn;
    
    // read file and construct LL
    if((inpf1 = fopen("/Users/onur/Desktop/Projects/Academic-C-Projects/TextSimilarityNGrams-150116825/TextSimilarityNGrams-150116825/input1.txt","r")) == NULL){
        printf("Input1 File Could Not Be Opened!\n");
        return 0;
    }
    if((inpf2 = fopen("/Users/onur/Desktop/Projects/Academic-C-Projects/TextSimilarityNGrams-150116825/TextSimilarityNGrams-150116825/input2.txt","r")) == NULL){
        printf("Input2 File Could Not Be Opened!\n");
        return 0;
    }
    hdr1,hdr2 ,one_gr_hdr,two_gr_hdr= NULL;
    one_gr_hdr = malloc(sizeof(node));
    two_gr_hdr = malloc(sizeof(node));
    strcpy(one_gr_hdr -> x ,"None");
    strcpy(two_gr_hdr -> x ,"None");
    
    while (!feof(inpf1)) {
        while (fscanf(inpf1, " %1023s", word) == 1) {
            //printf("\nCurrent Word in Input1 : %s \n",word);
            word[0] = tolower(word[0]); //LowerCase Implementation !
            if(insert_original(&hdr1, word)!=1){
                printf("\nInsert Original went wrong !") ;
            }
        }
        
    }
    
    
    while (!feof(inpf2)) {
        while (fscanf(inpf2, " %1023s", word2) == 1) {
            //printf("Current Word in Input2 : %s \n",word);
            word2[0] = tolower(word2[0]); //LowerCase Implementation !
            if(insert_original(&hdr2, word2)!=1){
                printf("\nInsert Original went wrong !") ;
            }
            else{ //We won't compare these two lists in another method , by doing that we will save "N" inputSize/time .
                buildOneGrams(&hdr1, &one_gr_hdr, word2);
                

            }
        }
        
        printf("\n-- Linked List 1 for Input1 File --\n");
        showTheList(hdr1);
        
        
        

        printf("\n-- Linked List 2 for Input2 File --\n");
        showTheList(hdr2);
        printf("\n-- Linked List One Gram Header --\n");
        
        showTheList(one_gr_hdr);
    }
    
    
    
    
    fclose(inpf1);
    fclose(inpf2);
    
    return 0;
}


int insert_original(nodePtrPtr header , char x[]){ //Insert the node without sort or any other comparements . For input files !
    
    nodePtr newNode, temp, prev;
    
    // create node to insert and assign values to its fields
    newNode= malloc(sizeof(node));
    strcpy(newNode->x,x);
    newNode->next=NULL;
    
    // if LL empty
    if (*header == NULL)
        *header=newNode;
    // if LL not empty
    else {
        temp=*header;
        while (temp != NULL ) {
            prev=temp;
            temp=temp->next;
        }
        prev->next=newNode;
    }
    
    return 1;
   
}
int insert_sorted(nodePtrPtr header, char x[]){
    
    nodePtr newNode, temp, prev;
    
    // create node to insert and assign values to its fields
    newNode=malloc(sizeof(node));
    strcpy(newNode->x,x);
    newNode->next=NULL;
    
    // if LL empty
    if (*header == NULL)
        *header=newNode;
    // if LL not empty
    else {
        temp=*header;
        while (temp != NULL && strcmp(temp->x,newNode->x) < 0 ) {
            prev=temp;
            temp=temp->next;
        }
        
        if (temp!=NULL && strcmp(temp->x,newNode->x)==0 ) {
            printf("existent key");
            return 0;
        }
        
        // insert node in a sorted fashion
        if (temp!=NULL)
            newNode->next=temp;
        
        // if value to insert is the least in LL then have header point to node
        if (temp==*header)
            *header=newNode;
        // otherwise insert node in correct position
        else
            prev->next=newNode;
    }
    
    return 1;
    
}






void showTheList (nodePtr header){
    nodePtr iterator = header;
    printf("\nNodes :");
    while(iterator != NULL && strcmp(iterator->x , "") != 0){
        printf(" %s ->",iterator->x);
        iterator = iterator->next;
    }
    printf("\n");
    
    
}

nodePtr search(nodePtr header, char x[]){

    nodePtr temp, prev;
    temp=header;

    while (temp != NULL && strcmp(temp->x,x) != 0 ){
        temp=temp->next;
    }

    if (temp==NULL) {
        // end of LL ... key non-existent ...
        printf("non-existent key ");
        return NULL;
    }
    if (strcmp(temp->x,x)==0 && strcmp(temp->x, "None") !=0)
        // search successful ...
        return temp;
    else {    // key non-existent ...
        printf("non-existent key ");
        return NULL;
    }

}

void buildOneGrams(nodePtrPtr header1 ,nodePtrPtr one_gr_hdr, char currentString[]){
    
    
    if(search(*one_gr_hdr, currentString) != NULL){
        
        printf("%s already exists in : one_gr_hdr ! ", currentString);
        return ;
    }else{
        if (search(*header1, currentString) == NULL) {
            printf("%s is not exists in : header1 ! ", currentString);
            return ;
        }else {
            insert_sorted(one_gr_hdr, currentString) ;
        }
        
        
    }
    
    
    
    
    
    
    
    
    
   
    
    
    
    
    
    
}




//nodePtr delete(nodePtrPtr header, char word[]){
//
//    nodePtr temp, prev;
//
//    // if LL empty ...
//    if (*header == NULL) {
//        printf("empty list!...");
//        return NULL;
//    }
//    // if LL not empty ...
//    else {
//        // search key in list ...
//        temp=*header;
//        while (temp != NULL && temp->x<word) {
//            prev=temp;
//            temp=temp->next;
//        }
//
//        // end of LL ... key non-existent ...
//        if (temp==NULL) {
//            printf("non-existent key");
//            return NULL;
//        }
//        // key existent ...
//        else if (temp->x==num) {
//            // first record to remove ...
//            if (temp==*header)
//                *header=temp->next;
//            // a subsequent record to remove ...
//            else
//                prev->next=temp->next;
//
//            return temp;
//        }
//        // key non-existent ...
//        else {
//            printf("non-existent key");
//            return NULL;
//        }
//    }
//}
//

