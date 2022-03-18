#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node* temp=NULL;

typedef struct Node
{
    char data[50];
    struct Node* left;
    struct Node* right;
} Node;

Node* NewNode(char x[])
{
    Node* myNode =malloc(sizeof(Node));
    strcpy(myNode->data, x);
    myNode->left = NULL;
    myNode->right = NULL;
    return myNode;
}

Node* insert(Node* node, char key[])
{
    if (node == NULL)
    {
        return NewNode(key);
    }
    if (strcasecmp(key,node->data)==-1)
    {
        node->left  = insert(node->left, key);
    }
    else if (strcasecmp(key,node->data)==1 )
    {
        node->right = insert(node->right, key);
    }
    return node;
}

Node* search(Node *root , char key[])
{
        if(root==NULL)
            return NULL;
        else if(strcasecmp(root->data,key)==0)
            return root;
        else if(strcasecmp(key,root->data)<0)
            {
                if(root->left!=NULL)
                    temp=root->left;
            return search(root->left,key);
            }
        else
        {
            if(root->right!=NULL)
                temp=root->right;
            return search(root->right,key);
        }
}

int numberOfLines(char *filename)
{
    FILE *f=fopen(filename,"r");
    int count = 0;
    while(!feof(f))
    {
        char word1[50];
        fscanf(f,"%s\n",word1);
        count++;
    }
    return count;
}

int count(Node *root)
{
    if ( root == NULL)
        return 0;
    else
        return 1 + count(root->left) + count(root->right);
}

int max(int a, int b)
{
    return a>b?a:b;
}

int height(Node *root)
{
    if ( root == NULL)
        return -1;
    else
        return 1 + max(height(root->left), height(root->right));
}

Node* fileReader(Node* myNode, char filename[])
{
    int num,i;
    num = numberOfLines(filename);
    FILE*f = fopen(filename,"r");
    if(f==NULL)
    {
        printf("File Not Found\n");
    }
    else
        printf("Dictionary Loaded Successfully...!\n");

    for(i=0; i<num; i++)
    {
        char word1[50];
        fscanf(f,"%s\n",word1);
        myNode = insert(myNode, word1);
    }
    return myNode;
}

Node* FindMin(Node* root)
{
    if(!root) return NULL;
    while(root->left)
        root = root->left;
    return root;
}

Node* getSuccessor(Node* root, Node* n)
{
    if(n->right!=NULL)
        return FindMin(n->right);

    Node* successor = NULL;
    while(root)
    {
        if(strcasecmp(n->data,root->data)==-1)
        {
            successor=root;
            root=root->left;
        }
        else if(strcasecmp(n->data,root->data)==1)
            root=root->right;
        else
            break;
    }
    return successor;
}

Node* FindMaximum(Node *root){
    if(!root)
        return NULL;

    while(root->right) root = root->right;
    return root;
}

Node* getPredecessor(Node* root, Node* x)
{
    if( x->left != NULL )
        return FindMaximum(x->left);

    Node *predecessor = NULL;

    while (root)
    {
        if (strcasecmp(x->data,root->data)==1)
        {
            predecessor = root;
            root = root->right;
        }
        else if (strcasecmp(x->data,root->data)==-1)
            root = root->left;
        else
           break;
    }
    return predecessor;
}

int main()
{
    Node* myNode = NULL;
    Node* myWord = NULL;
    Node* successor = NULL;
    Node* predeccessor = NULL;

    char sentence[1000];
    myNode = fileReader(myNode,"EN-US-Dictionary.txt");
    printf("..................................\n");

    int treeSize = count(myNode);
    printf("Size = %d\n",treeSize);
    printf("..................................\n");

    int treeHeight = height(myNode);
    printf("Height = %d\n",treeHeight);
    printf("..................................\n");

    printf("Enter a sentence: \n");
    gets(sentence);

    char *token;
    token = strtok(sentence," ");

    while(token!=NULL)
    {
        myWord = search(myNode,token);

        if(myWord==NULL){
                printf("%s - Incorrect, Suggestions : ",token);

                successor = getSuccessor(myNode,temp);
                predeccessor = getPredecessor(myNode,temp);

                if(temp==NULL)
                    printf("incorrect");
                else
                    printf("%s, ",temp->data);

                if(successor==NULL)
                    printf("incorrect");
                else
                    printf("%s, ",successor->data);

                if(predeccessor==NULL)
                    printf("incorrect");
                else
                    printf("%s\n",predeccessor->data);
        }
        else
            {
                printf("%s - Correct\n",myWord->data);
            }
        token = strtok(NULL," ");
    }
    return 0;
}

