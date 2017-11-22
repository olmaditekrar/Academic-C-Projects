#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>
#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>
#include<mach/mach.h>
//https://alphabetizer.flap.tv/

//AVL CODE
struct NodeAVL
{
    char* key[25];
    struct NodeAVL *left;
    struct NodeAVL *right;
    int height;
};

// A utility function to get maximum of two integers
int max(int a, int b);

// A utility function to get height of the tree
int height(struct NodeAVL *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

/* Helper function that allocates a new node with the given key and
 NULL left and right pointers. */
struct NodeAVL* newNode(char* key)
{
    struct NodeAVL* node = (struct NodeAVL*)
    malloc(sizeof(struct NodeAVL));
    strcpy(node->key,key);
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct NodeAVL *rightRotate(struct NodeAVL *y)
{
    struct NodeAVL *x = y->left;
    struct NodeAVL *T2 = x->right;
    
    // Perform rotation
    x->right = y;
    y->left = T2;
    
    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
    
    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct NodeAVL *leftRotate(struct NodeAVL *x)
{
    struct NodeAVL *y = x->right;
    struct NodeAVL *T2 = y->left;
    
    // Perform rotation
    y->left = x;
    x->right = T2;
    
    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
    
    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(struct NodeAVL *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct NodeAVL* insertAVL(struct NodeAVL* node, char* key)
{
    /* 1.  Perform the normal BST rotation */
    if (node == NULL)
        return(newNode(key));
    
    if (strcmp(key , node->key)<0)
        node->left  = insertAVL(node->left, key);
    else if (strcmp(key , node->key)>0)
        node->right = insertAVL(node->right, key);
    else // Equal keys not allowed
        return node;
    
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));
    
    /* 3. Get the balance factor of this ancestor
     node to check whether this node became
     unbalanced */
    int balance = getBalance(node);
    
    // If this node becomes unbalanced, then there are 4 cases
    
    // Left Left Case
    if (balance > 1 && strcmp(key , node->left->key)<0)
        return rightRotate(node);
    
    // Right Right Case
    if (balance < -1 && strcmp(key , node->right->key)>0)
        return leftRotate(node);
    
    // Left Right Case
    if (balance > 1 && strcmp(key , node->left->key)>0)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
    
    // Right Left Case
    if (balance < -1 && strcmp(key , node->right->key)<0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    /* return the (unchanged) node pointer */
    return node;
}

/* Given a non-empty binary search tree, return the
 node with minimum key value found in that tree.
 Note that the entire tree does not need to be
 searched. */
struct NodeAVL * minValueNode(struct NodeAVL* node)
{
    struct NodeAVL* current = node;
    
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
    
    return current;
}

// Recursive function to delete a node with given key
// from subtree with given root. It returns root of
// the modified subtree.
struct NodeAVL* deleteNodeAVL(struct NodeAVL* root, char* key)
{
    // STEP 1: PERFORM STANDARD BST DELETE
    
    if (root == NULL)
        return root;
    
    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if ( strcmp(key , root->key)<0 )
        root->left = deleteNodeAVL(root->left, key);
    
    // If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if( strcmp(key , root->key)>0 )
        root->right = deleteNodeAVL(root->right, key);
    
    // if key is same as root's key, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct NodeAVL *temp = root->left ? root->left :
            root->right;
            
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
                *root = *temp; // Copy the contents of
            // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            struct NodeAVL* temp = minValueNode(root->right);
            
            // Copy the inorder successor's data to this node
            strcpy(root->key , temp->key);
            
            // Delete the inorder successor
            root->right = deleteNodeAVL(root->right, temp->key);
        }
    }
    
    // If the tree had only one node then return
    if (root == NULL)
        return root;
    
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));
    
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);
    
    // If this node becomes unbalanced, then there are 4 cases
    
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
    
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;
}

// A utility function to print preorder traversal of
// the tree.
// The function also prints height of every node
void preOrder(struct NodeAVL *root)
{
    if(root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

/* Drier program to test above function*/



            //AVL CODE





//BST CODE ====
typedef struct BstTreeNode
{
    char* data[25];
    struct BstTreeNode *left;
    struct BstTreeNode *right;
    
    
    
}BstTreeNode;
BstTreeNode* FindMinBST(BstTreeNode *node);
BstTreeNode * DeleteBST(BstTreeNode *node, char* data)
{
    BstTreeNode *temp;
    if(node==NULL)
    {
        
    }
    else if(strcmp(data, node->data)<0)
    {
        node->left = DeleteBST(node->left, data);
    }
    else if(strcmp(data, node->data)>0)
    {
        node->right = DeleteBST(node->right, data);
    }
    else
    {
        /* Now We can delete this node and replace with either minimum element
         in the right sub tree or maximum element in the left subtree */
        if(node->right && node->left)
        {
            /* Here we will replace with minimum element in the right sub tree */
            temp = FindMinBST(node->right);
            strcpy(node -> data,temp->data);
            /* As we replaced it with some other node, we have to delete that node */
            node -> right = DeleteBST(node->right,temp->data);
        }
        else
        {
            /* If there is only one or zero children then we can directly
             remove it from the tree and connect its parent to its child */
            temp = node;
            if(node->left == NULL)
                node = node->right;
            else if(node->right == NULL)
                node = node->left;
            free(temp); /* temp is longer required */
        }
    }
    return node;
    
}

BstTreeNode* FindMinBST(BstTreeNode *node)
{
    if(node==NULL)
    {
        /* There is no element in the tree */
        return NULL;
    }
    if(node->left) /* Go to the left sub tree to find the min element */
        return FindMinBST(node->left);
    else
        return node;
}
BstTreeNode* FindMaxBST(BstTreeNode *node)
{
    if(node==NULL)
    {
        /* There is no element in the tree */
        return NULL;
    }
    if(node->right) /* Go to the left sub tree to find the min element */
        return FindMaxBST(node->right);
    else
        return node;
    
}

BstTreeNode * InsertBST(BstTreeNode *node,char* data)
{
    if(node==NULL)
    {
        BstTreeNode *temp;
        temp = (BstTreeNode *)malloc(sizeof(BstTreeNode));
        strcpy(temp -> data , data);
        temp -> left = temp -> right = NULL;
        return temp;
    }
    
    if(strcmp(data ,(node->data)) > 0)
    {
    
        node->right = InsertBST(node->right,data);
    }
    else if(strcmp(data ,(node->data)) < 0)
    {
        node->left = InsertBST(node->left,data);
    }
    /* Else there is nothing to do as the data is already in the tree. */
    return node;
    
}


BstTreeNode * FindBST(BstTreeNode *node, int data)
{
    if(node==NULL)
    {
        /* Element is not found */
        return NULL;
    }
    if(strcmp(data , node->data)>0)
    {
        /* Search in the right sub tree. */
        return FindBST(node->right,data);
    }
    else if(strcmp(data , node->data)<0)
    {
        /* Search in the left sub tree. */
        return FindBST(node->left,data);
    }
    else
    {
        /* Element Found */
        return node;
    }
}


void PrintInorder(BstTreeNode *node)
{
    if(node==NULL)
    {
        return;
    }
    PrintInorder(node->left);
    printf("%1023s ",node->data);
    PrintInorder(node->right);
}


//BST CODE ===





long long getUsedMemory(){
    
    
    
    
    //Returns the all ram currently used by BST-AVL-DataStructures Project
    struct task_basic_info t_info;
    mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

    if (KERN_SUCCESS != task_info(mach_task_self(),
                                  TASK_BASIC_INFO, (task_info_t)&t_info,
                                  &t_info_count))
    {
        return -1;
    }
    return (long long)t_info.resident_size;
    
    
    
 //Returns the all ram currently used !
        //
        //
        //    vm_size_t page_size;
        //    mach_port_t mach_port;
        //    mach_msg_type_number_t count;
        //    vm_statistics64_data_t vm_stats;
        //
        //    mach_port = mach_host_self();
        //    count = sizeof(vm_stats) / sizeof(natural_t);
        //    if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
        //        KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
        //                                          (host_info64_t)&vm_stats, &count))
        //    {
        //        long long free_memory = (int64_t)vm_stats.free_count * (int64_t)page_size;
        //
        //        long long used_memory = ((int64_t)vm_stats.active_count +
        //                                 (int64_t)vm_stats.inactive_count +
        //                                 (int64_t)vm_stats.wire_count) *  (int64_t)page_size;
        //        return used_memory;
        //    }
        //
        //    return 0;
    
    
}







int main()
{
    struct NodeAVL *rootAVL = NULL;
    BstTreeNode* rootBST = NULL ;
    double timeBSTinsertion=0.0 ,timeBSTdeletion = 0.0,timeAVLinsertion=0.0,timeAVLdeletion=0.0;
    long long memUsageBSTinsertion=0.0,memUsageBSTdeletion=0.0,memUsageAVLinsertion=0.0,memUsageAVLdeletion =0.0i,memUsageBase=0.0;
    clock_t  startTime;
    char* word = malloc(sizeof(char[25]));
    FILE *doc;
    
    
    
    //PREPROCESSING WITH PYTHON (GENERATING  "worstCase.txt" )
    
    //system("python /Users/mac/Desktop/Projects/Academic-C-Projects/BST-vs-AVL-DataStructures/convertToProcessedOnurCanYucedag.py");
    
    //
    
    //INSERTION TO BST !
    if((doc = fopen("/Users/mac/Desktop/Projects/Academic-C-Projects/BST-vs-AVL-DataStructures/worstCase.txt", "r"))!=NULL){
        printf("\n##Constructing BST ##");
        startTime = clock();
        memUsageBase = getUsedMemory();
        while (!feof(doc)) {
            
            while (fscanf(doc, " %1023s", word) == 1) {
                
                
                rootBST = InsertBST(rootBST, word);
            }

        }
        memUsageBSTinsertion = getUsedMemory() - memUsageBase;
        timeBSTinsertion = ((double)clock() - startTime) / CLOCKS_PER_SEC ;
        printf("\n Time elapsed in BST Insertion: %f\n",timeBSTinsertion );
        printf(" Memory Used in BST Insertion: %lld\n",memUsageBSTinsertion );

        rewind(doc);
        
        // DELETION FROM BST !
        
        
        startTime = clock();
        memUsageBase = getUsedMemory();
        while (fscanf(doc, " %1023s", word) == 1 && !feof(doc)) {
            
            if(strcmp(".",&word[strlen(word)-1]) == 0){ //If the word has a "." in it, it is the last word of this sentence so we have to add the next word's sentenceNo by 1.
                
                rootBST = DeleteBST(rootBST, word);
                break;
                
                
            }
            rootBST = DeleteBST(rootBST, word);
        
        }
        memUsageBSTdeletion = getUsedMemory() - memUsageBase;
        if(memUsageBSTdeletion == 0){
            memUsageBSTdeletion = memUsageBSTinsertion;
        }
        timeBSTdeletion = ((double)clock() - startTime) / CLOCKS_PER_SEC ;
        printf(" Time elapsed in BST Deletion: %f\n",timeBSTdeletion );
        printf(" Memory Used in BST Deletion: %lld\n",memUsageBSTdeletion );


    
    }

    
    //INSERTION TO AVL !
    free(rootBST);//We don't need BSTree anymore .
    if((doc = fopen("/Users/mac/Desktop/Projects/Academic-C-Projects/BST-vs-AVL-DataStructures/worstCase.txt", "r"))!=NULL){
        printf("\n\n##Constructing and Deleting Nodes From AVL ##");
        startTime = clock();
        memUsageBase = getUsedMemory();
        while (!feof(doc)) {
            while (fscanf(doc, " %1023s", word) == 1) {
                
                
                rootAVL = insertAVL(rootAVL, word);
            }
            
        }
        memUsageAVLinsertion = getUsedMemory()-memUsageBase;
        if(memUsageAVLinsertion == 0.0){
            memUsageAVLinsertion = memUsageBSTdeletion;
        }
        timeAVLinsertion = ((double)clock() - startTime) / CLOCKS_PER_SEC ;
        printf("\n Time elapsed in AVL Insertion: %f",timeAVLinsertion );
        printf("\n Memory Used in AVL Insertion: %lld\n",memUsageAVLinsertion );
        //DELETION FROM AVL !
        
        startTime = clock();
        rewind(doc);
        memUsageBase = getUsedMemory();
        while (fscanf(doc, " %1023s", word) == 1) {
            
            if(strcmp(".",&word[strlen(word)-1]) == 0){ //If the word has a "." in it, it is the last word of this sentence so we have to add the next word's sentenceNo by 1.
                
                rootAVL = deleteNodeAVL(rootAVL, word);
                break;
                
                
            }
            rootAVL = deleteNodeAVL(rootAVL, word);
            
        }
        memUsageAVLdeletion = getUsedMemory()-memUsageBase;
        if(memUsageAVLdeletion == 0.0){
            memUsageAVLdeletion = memUsageAVLinsertion;
        }
        timeAVLdeletion = ((double)clock() - startTime)/CLOCKS_PER_SEC ;
        printf(" Time elapsed in AVL Deletion: %f\n",timeAVLdeletion );
        printf(" Memory Used in AVL Deletion: %lld\n",memUsageAVLdeletion );


    }
    double coefficentAVLTimeInsertion = ((double)timeBSTinsertion/(double)timeAVLinsertion);
    double coefficentAVLTimeDeletion = ((double)timeBSTdeletion/(double)timeAVLdeletion);

    printf("\nTIME COMPLEXITIES");
    printf("\nTime Difference Between BST-AVL Insertion:> %f\n",(timeBSTinsertion-timeAVLinsertion));
    printf("Time Difference Between BST-AVL Deletion:> %f\n",(timeBSTdeletion-timeAVLdeletion));
    printf("Execution Time Equation Between Algorithms Insertion :> BST(execTime) = AVL(execTime)*(%.3f)\n",coefficentAVLTimeInsertion);
    printf("Execution Time Equation Between Algorithms Deletion :> BST(execTime) = AVL(execTime)*(%.3f)\n",coefficentAVLTimeDeletion);


    
    double coefficentAVLMemoryInsertion = ((double)memUsageBSTinsertion/(double)memUsageAVLinsertion);
    double coefficentAVLMemoryDeletion = ((double)memUsageBSTdeletion/(double)memUsageAVLdeletion);
    
    printf("\nMEMORY USAGES");
    printf("\nMemory Usages Difference Between BST-AVL Insertion:> %lld\n",(memUsageBSTinsertion-memUsageAVLinsertion));
    printf("Memory Usages Difference Between BST-AVL Deletion:> %lld\n",(memUsageBSTdeletion-memUsageAVLdeletion));
    printf("Memory Usage Equation Between Algorithms Insertion :> BST(memUsage) = AVL(memUSage)*(%.4lf)\n",coefficentAVLMemoryInsertion);
    printf("Memory Usage Equation Between Algorithms Deletion :> BST(memUsage) = AVL(memUsage)*(%.4lf)\n",coefficentAVLMemoryDeletion);
    
    
    
    
    
    free(rootAVL);
    return 0;
}



