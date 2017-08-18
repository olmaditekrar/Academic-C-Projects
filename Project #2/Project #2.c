#include <stdio.h>
#include <stdlib.h>
struct node{
    long int key1;
    char key2[6];
    struct node *left_node;
    struct node *right_node;
    int depth;
};
struct node *pack(FILE *input_file);//Dosyadan bir satir okuyup node paketleyip adresini geri yollar.
struct node *  insertion(struct node **root,struct node *input_node,struct node *parent_node,int current_depth);//Tree ye node insertler.
int insert_remove_file (struct node *input_node,int insRe);//Dosya yazma islemlerini yonetir.
struct node * erase(struct node *delete_node,struct node *parent_node,struct node *root);//Tree den node siler.
int main()
{
    struct node *root,*input_node,*delete_node,*parent_node;
    delete_node=malloc(sizeof(struct node));
    char useless_char;
    FILE *input_file=fopen("input.txt","r+");
    root=pack(input_file);
    while(!feof(input_file))
    {
        struct node *new_node ;
        new_node = pack(input_file);
        parent_node=insertion(&root,new_node,parent_node,0);
    }
    printf("\n");
    printPaths(root);
    int choice;
    printf("\n\tHow can I serve you ?\n\t  1.Insert a node to tree.\n\t  2.Delete a node from tree.\n\t  3.Print the tree.\n\t  4.I have seen enough , thanks   :");
    scanf("%d",&choice);
    fclose(input_file);
    while(choice<5&&choice>0)
    {
        switch(choice)
        {
            case 1: {
                        printf("\n\tPlease give another input for insert to tree : ");
                        input_node=(struct node*)malloc(sizeof(struct node));
                        scanf("%ld%c%s",&input_node->key1,&useless_char,input_node->key2);
                        parent_node=insertion(&root,input_node,root,0);
                        printPaths(root);
                        insert_remove_file(input_node,0);
                        printf("\n\tHow can I serve you ?\n\t  1.Insert a node to tree.\n\t  2.Delete a node from tree.\n\t  3.Print the tree.\n\t  4.I have seen enough , thanks   :");
                        scanf("%d",&choice);
                        break;
                    }

            case 2: {
                        printf("\n\tPlease give another input for delete from tree :");
                        scanf("%ld%c%s",&delete_node->key1,&useless_char,delete_node->key2);
                        //Dosyadan silme..
                        if(insert_remove_file(delete_node,1))
                        {
                            printf("\nTree is not here , you delete it !\n");
                            return;
                        }
                        parent_node=root;
                        parent_node=insertion(&root,delete_node,parent_node,0);//1..
                        root = erase(delete_node,parent_node,root);
                        printPaths(root);
                        printf("\n\tHow can I serve you ?\n\t  1.Insert a node to tree.\n\t  2.Delete a node from tree.\n\t  3.Print the tree.\n\t  4.I have seen enough , thanks   :");
                        scanf("%d",&choice);
                        fclose(input_file);
                        break;
                    }
            case 3: {
                        printPaths(root);
                        printf("\n\tHow can I serve you ?\n\t  1.Insert a node to tree.\n\t  2.Delete a node from tree.\n\t  3.Print the tree.\n\t  4.I have seen enough , thanks   :");
                        scanf("%d",&choice);
                        break;
                    }
            case 4 : break;
        }
    }
}
struct node *pack(FILE *input_file)//OKUR.
{
    struct node *new_node =(struct node *)malloc(sizeof(struct node));
    fscanf(input_file, "%ld", &new_node->key1);
    fgetc(input_file);
    fscanf(input_file, "%s", new_node->key2);
    new_node->depth=0;
    new_node->left_node=NULL;
    new_node->right_node=NULL;
    return new_node;
}
struct node *  insertion(struct node **root,struct node *input_node,struct node *parent_node,int current_depth)
{
    if(!(*root))
        {
           *root= input_node;
           (*root)->depth=current_depth;
           (*root)->left_node=NULL;
           (*root)->right_node=NULL;
           return (*root);//Yeni node olusturmak gerekeiyor , input node herhangi bir tree node'uyla eslesmedi.
        }
       if(current_depth%2==0)
            {
                if(input_node->key1>(*root)->key1)
                {
                    parent_node=(*root);
                    insertion(&(*root)->right_node, input_node,parent_node,current_depth+1);
                }
                else if(input_node->key1<(*root)->key1)
                {
                    parent_node=(*root);
                    insertion(&(*root)->left_node, input_node,parent_node,current_depth+1);
                }
                else if(strcmp(input_node->key2,(*root)->key2)==0)//Iký sayinin key2 lari esit ise..
                {
                    printf("\n\tI think you want to delete it , so that's the thing I must for you.\n\n");
                    return parent_node;//Boyle bir node var.
                }
            }
            else
            {
               if(strcmp(input_node->key2,(*root)->key2)>0)//input->key2 > *root->key2 ise....
                {
                    parent_node=(*root);
                    insertion(&(*root)->right_node, input_node,parent_node,current_depth+1);
                }
                else if (strcmp(input_node->key2,(*root)->key2)<0)//input->key2 < *root->key2 ise....
                {
                    parent_node=(*root);
                    insertion(&(*root)->left_node, input_node,parent_node,current_depth+1);
                }
                else if(input_node->key1==(*root)->key1)
                {
                     printf("\n\tI think you want to delete it , so that's the thing I must for you.\n\n");
                     return parent_node;//Boyle bir node var .
                }
            }
}
int insert_remove_file (struct node *input_node,int insRe)
{
    FILE *input_file;
    struct node *new_node=(struct node*)malloc(sizeof(struct node));
    if(insRe==0)//insertleyeceksek veriyi dosyanin sonuna.
    {
        input_file=fopen("input.txt","a+");//sonuna yazdiracagimizdan a+ ile actik.
        fprintf(input_file,"\n%ld,%s",input_node->key1,input_node->key2);
        fclose(input_file);
    }
    else //eger o node'u sileceksek dosyadan.
    {
        FILE *input_file_temp=fopen("input_temp.txt","w+");
        input_file=fopen("input.txt","r+");
        fscanf(input_file, "%ld", &new_node->key1);
        fgetc(input_file);
        fscanf(input_file, "%s", new_node->key2);
        if(input_node->key1!=new_node->key1||strcmp(input_node->key2,new_node->key2)!=0)//Eger input_node'dan farklı ise ilk satirimiz.
            {
                fprintf(input_file_temp,"%ld,%s",new_node->key1,new_node->key2);
            }
            else if(input_node->key1==new_node->key1||strcmp(input_node->key2,new_node->key2)==0)//Eger ilk satir ile ayni ise input_node.
            {
                if(!feof(input_file))//Eger sadece bir node kalmamışsa tree'de.
                {
                    fscanf(input_file, "%ld", &new_node->key1);
                    fgetc(input_file);
                    fscanf(input_file, "%s", new_node->key2);
                    fprintf(input_file_temp,"%ld,%s",new_node->key1,new_node->key2);
                }
                else//Eger bir adet node kalmışsa.
                    {
                        fclose(input_file);
                        fclose(input_file_temp);
                       if(remove("input.txt")!=0)
                        {
                            printf("***Error : Can't delete 'input.txt'...");
                        }
                        rename("input_temp.txt","input.txt");
                        return 1;
                    }
            }
        while(!feof(input_file))
        {
            fscanf(input_file, "%ld", &new_node->key1);
            fgetc(input_file);
            fscanf(input_file, "%s", new_node->key2);
            if(input_node->key1!=new_node->key1||strcmp(input_node->key2,new_node->key2)!=0)
            {
                fprintf(input_file_temp,"\n%ld,%s",new_node->key1,new_node->key2);
            }
        }
        fclose(input_file);
        fclose(input_file_temp);
        if(remove("input.txt")!=0)
        {
            printf("***Error : Can't delete 'input.txt'...");
        }
        rename("input_temp.txt","input.txt");
        return 0;
    }
}
int isSame(struct node *node1,struct node * node2)
{
    if(node1->key1==node2->key1&&strcmp(node1->key2,node2->key2)==0)
    {
        return 1;
    }
    return 0;
}
int traversal(struct node * root, struct node * input_node)
{
    struct node *iterator;
    iterator=root;
    if(iterator==NULL)
    {
        return 0;
    }
       else
       {
           if(isSame(iterator,input_node)==1)
           {
               return 1;
           }
            traversal(iterator->left_node,input_node);
            traversal(iterator->right_node,input_node);
       }
       return 0;
}
struct node * erase(struct node *delete_node,struct node *parent_node,struct node *root)
{
    FILE *input_file=fopen("input.txt","r+");
    char lft_rgt;
    struct node *iterator;
    iterator=delete_node;
    if(parent_node->depth%2==0)
    {
        if(iterator->key1>parent_node->key1)
        {
            delete_node=parent_node->right_node;
            lft_rgt='r';
        }
        else  if(iterator->key1<parent_node->key1)
        {
            delete_node=parent_node->left_node;
            lft_rgt='l';
        }
        else if(strcmp(iterator->key2,parent_node->key2)==0)
        {
            struct node *new_root =malloc(sizeof(struct node));
            new_root->left_node=NULL;
            new_root->right_node=NULL;
            new_root->depth=0;
            long int key1;
            char useless,key2[6];
            fscanf(input_file,"%ld%c%s",&new_root->key1,&useless,new_root->key2);
            root=new_root;
            while(!feof(input_file))
            {
                struct node *temp =(struct node*)malloc(sizeof(struct node));
                fscanf(input_file,"%ld%c%s",&temp->key1,&useless,temp->key2);
                parent_node =insertion((&root),temp,root,0);
            }
            return new_root;
        }
    }
    else {

        if(strcmp(iterator->key2,parent_node->key2)>0)
        {
            delete_node=parent_node->right_node;
            lft_rgt='r';
        }
        else if(lft_rgt='l')
        {
            delete_node=parent_node->left_node;
            lft_rgt='l';
        }
    }
    if(lft_rgt=='r')
    {
        parent_node->right_node=NULL;
    }
    else if (lft_rgt='l')parent_node->left_node=NULL;

    long int key1;
    char useless,key2[6];

    while(!feof(input_file))
    {
        struct node *temp =(struct node*)malloc(sizeof(struct node));
        fscanf(input_file,"%ld%c%s",&temp->key1,&useless,temp->key2);
        if(traversal(delete_node->left_node,temp)==1||traversal(delete_node->right_node,temp)==1)
        {
            parent_node =insertion((&root),temp,parent_node,0);
        }
    }
    return root;
}
void printPaths(struct node * node)
{
  long int path1[100];
  char path2[100][6];
  printPathsRecur(node, path1,path2, 0);
}
/* Recursive helper function -- given a node, and an array containing
 the path from the root node up to but not including this node,
 print out all the root-leaf paths.*/
void printPathsRecur(struct node* node, long int path1[],char path2[][6], int pathLen)
{
  if (node==NULL)
    return;
  // append this node to the path array
    path1[pathLen] = node->key1;
    strcpy(path2[pathLen],node->key2);
    pathLen++;

  // it's a leaf, so print the path that led to here
  if (node->left_node==NULL && node->right_node==NULL)
  {
    printArray(path1,path2, pathLen);
  }
  else
  {
    // otherwise try both subtrees
    printPathsRecur(node->left_node, path1,path2, pathLen);
    printPathsRecur(node->right_node, path1,path2, pathLen);
  }
}

// Utility that prints out an array on a line.
void printArray(long int ints[],char strings[][6], int len)
{
  int i;
    printf("\t");
  for (i=0; i<len; i++)
  {
    printf("(%ld,%s) ", ints[i],strings[i]);
  }
  printf("\n");
}
//Normalde uzerine calistigim silme kodu :
/*
struct node* Delete(struct node *node_delete,long int key1,char key2[]) {
    printf("DELETE");
	if(node_delete == NULL) return node_delete;
	else if(node_delete->depth%2==0)
	{
	    if(key1 < node_delete->key1)
      {

          node_delete->left_node = Delete(node_delete->left_node,key1,key2);
      }
      else if(key1 > node_delete->key1)
            node_delete->right_node = Delete(node_delete->right_node,key1,key2);
	}

      else if(node_delete->depth%2!=0)
	{
	    if(strcmp(node_delete->key2,key2))
        {

            node_delete->left_node = Delete(node_delete->left_node,key1,key2);
        }
        else  if(0>strcmp(node_delete->key2,key2)) node_delete->right_node = Delete(node_delete->right_node,key1,key2);

	}

	else {
		// Case 1:  No child
		if(node_delete->left_node == NULL && node_delete->right_node == NULL) {
			free(node_delete);
			node_delete = NULL;
		}
		//Case 2: One child
		else if(node_delete->left_node == NULL) //Only right child..
        {

			struct node *temp = node_delete;
        if(node_delete->depth%2==0)//Cift ise derinlik.
			{
			    //Key1 a göre en kucukleri ile yer degistirecek.
			    struct node *temp = FindMin(node_delete->right_node,1);
                node_delete->key1 = temp->key1;
                strcpy(node_delete->key2, temp->key2);
                node_delete->right_node = Delete(node_delete->right_node,temp->key1,temp->key2);
            }
			else{//Tek ise derinlik.
			    //Key2 ya gore en buyugu ile yer degistirecek.
                    struct node *temp = FindMax(node_delete->right_node,2);
                node_delete->key1 = temp->key1;
                strcpy(node_delete->key2, temp->key2);
                node_delete->right_node = Delete(node_delete->right_node,temp->key1,temp->key2);
			}
		}



		//Only left child..
		else if(node_delete->right_node == NULL) {
			struct node *temp = node_delete;
        if(node_delete->depth%2==0)//Cift ise derinlik.
			{
			    //Key1 a göre en buyukleri ile yer degistirecek.
			    struct node *temp = FindMax(node_delete->left_node,1);
                node_delete->key1 = temp->key1;
                strcpy(node_delete->key2, temp->key2);
                node_delete->left_node = Delete(node_delete->left_node,temp->key1,temp->key2);
            }
			else{//Tek ise derinlik.
			    //Key2 ya gore en kucugu ile yer degistirecek.
                struct node *temp = FindMin(node_delete->left_node,2);//left subtree nin en buyugu gecmeli silinenin yerine
                node_delete->key1 = temp->key1;
                strcpy(node_delete->key2, temp->key2);
                node_delete->left_node = Delete(node_delete->left_node,temp->key1,temp->key2);
			}
		}






		// case 3: 2 children
		else {
                struct Node *temp = node_delete;
                if(node_delete->depth%2!=0)//TEK ISE
                {

                    struct node *temp = FindMin(node_delete->right_node,2);
                    node_delete->key1 = temp->key1;
                    strcpy(node_delete->key2, temp->key2);
                    node_delete->right_node = Delete(node_delete->right_node,temp->key1,temp->key2);
                }
                else{//CIFT ISE

                    struct node *temp = FindMin(node_delete->right_node,1);
                    node_delete->key1 = temp->key1;
                    strcpy(node_delete->key2, temp->key2);
                    node_delete->right_node = Delete(node_delete->right_node,temp->key1,temp->key2);
                }


		}
	}
	return node_delete;
}
*/
