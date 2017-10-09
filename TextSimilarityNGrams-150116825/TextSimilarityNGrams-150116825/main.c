#include <stdio.h>
#include <stdlib.h>
struct node {
    char x[10];
    int count ;
    struct node *next;
};

typedef struct node node;
typedef struct node* nodePtr;
typedef struct node** nodePtrPtr;

FILE *inpf,*inpf2;
nodePtr createLinkedListFromInputFile(FILE *inputFile);
int insert_sorted(nodePtrPtr, char[]);
nodePtr delete(nodePtrPtr, char[]);
nodePtr search(nodePtr, char[], int *);
//void read_words (FILE *f) {
//    char x[1024];
//    /* assumes no word exceeds length of 1023 */
//    while (fscanf(f, " %1023s", x) == 1) {
//        puts(x);
//        insert(nodePtrPtr, x);
//    }
//}
int main(){
    
    nodePtr hdr, p, q, r;
    char word[10];
    char op;
    int posn;
    
    // read file and construct LL
    if((inpf = fopen("/Users/onur/Desktop/Projects/Academic-C-Projects/TextSimilarityNGrams-150116825/TextSimilarityNGrams-150116825/input.txt","r")) == NULL){
        printf("Input File Could Not Be Opened!\n");
        return 0;
    }
    
    
    
    
    hdr = NULL;
    while (!feof(inpf)) {
        while (fscanf(inpf, " %1023s", word) == 1) {
            puts(word);
            printf(word);

            insert_sorted(&hdr, word);
        }
        //insert_sorted(&hdr,word);
    }
    fclose(inpf);
    
    p = hdr;
    while (p != NULL) {
        printf("%s ",p->x);
        
        

        p=p->next;
    }
    
    printf("\n>>");
    
    
    
    
    
    
    
//    do {
//        scanf("%c",&op);
//        switch (op) {
//            case 'd':
//                scanf("%lf",&word);
//                free(p = delete(&hdr,word));
//                if(p == NULL)
//                    printf("\n");
//                printf(">>");
//                break;
//
//            case 's':
//                scanf("%lf", &word);
//                p = search(hdr, word, &posn);
//                (posn>0)*printf("record #%d",posn+1);
//                printf("\n>>");
//                break;
//
//            case 'i':
//                scanf("%lf", &word);
//                posn = insert(&hdr,word);
//                if(!posn)
//                    printf("\n");
//                printf(">>");
//                break;
//
//            case 'e': break;
//
//            case 'l':
//    {
//                p=hdr;
//                while(p != NULL){
//                    printf("%5.4lf ",p->x);
//                    p = p->next;
//                }
//                printf("\n>>");
//    }
 //               break;
//        }
//    }while (op!='e');
    
}

//nodePtr createLinkedListFromInputFile(FILE *inputFile ) {
//
//
//}


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
        
        if (temp!=NULL && strcmp(temp->x,newNode->x)==0) {
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
nodePtr search(nodePtr header, char x[], int *ctr){

    nodePtr temp, prev;
    *ctr=0;
    temp=header;

    while (temp != NULL && strcmp(temp->x,x) != 0 ){
        temp=temp->next;
        (*ctr)++;
    }

    if (temp==NULL) {
        // end of LL ... key non-existent ...
        *ctr=-1;
        printf("non-existent key ");
        return NULL;
    }
    if (strcmp(temp->x,x)==0)
        // search successful ...
        return temp;
    else {    // key non-existent ...
        *ctr=-1;
        printf("non-existent key ");
        return NULL;
    }

}

