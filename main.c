//
//  main.c
//  Trees-Project
//
//  Created by Ziad Hindawy on 15/05/2026.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

typedef struct Node
{
    int id;
    char name[30];
    float gpa;
    struct Node *left;
    struct Node *right;
    int height;
} Node;
int max(int a,int b)
{
    return (a>b) ? a:b;
}
int height(Node *N)
{
    if(N == NULL)
        return 0;
    return N->height;
}
Node *newNode(int id, char *name,float gpa)
{
    while(gpa < 0 || gpa > 4)
    {
        printf("Error: GPA must be between 0.0 and 4.0\n");
        printf("Enter the GPA again for student ID:%d \n",id);
        scanf("%f",&gpa);
    }
    Node *node = malloc(sizeof(Node));
    node->id = id;
    strcpy(node->name,name);
    node->gpa = gpa;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left),height(y->right))+1;
    x->height = max(height(x->left),height(x->right))+1;
    return x;
}
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left),height(x->right))+1;
    y->height = max(height(y->left),height(y->right))+1;
    return y;
}
int getBalance(Node *N)
{
    if(N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node *searchById(Node *node,int id)
{
    if(node == NULL){
        return NULL;
    }
    if(node->id == id)
        return node;
    else if(id < node->id)
        return searchById(node->left,id);
    else
        return searchById(node->right,id);
}

Node *insert(Node *node,int id,char *name,float gpa)
{

    if(searchById(node,id))
    {
        printf("Error: Duplicate ID is not allowed\n");
        return node;
    }

    while(gpa < 0 || gpa > 4)
    {
        printf("Error: GPA must be between 0.0 and 4.0\n");
        printf("Enter the GPA again for student ID:%d \n",id);
        scanf("%f",&gpa);
    }

    if(node == NULL)
        return newNode(id,name,gpa);

    if(id < node->id)
        node->left = insert(node->left,id,name,gpa);

    else if(id > node->id)
        node->right = insert(node->right,id,name,gpa);

    else
        return node;

    node->height = 1 + max(height(node->left),height(node->right));

    int balance = getBalance(node);

    if(balance > 1 && id < node->left->id)
        return rightRotate(node);

    if(balance < -1 && id > node->right->id)
        return leftRotate(node);

    if(balance > 1 && id > node->left->id)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if(balance < -1 && id < node->right->id)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void displayBySearchByID(Node *node,int id)
{

    Node *s = searchById(node,id);
    if(s != NULL)
    {
        printf("ID: %d\n",s->id);
        printf("Name: %s\n",s->name);
        printf("GPA: %f\n",s->gpa);
    }
    else
    {
        printf("NOT FOUND\n");
    }
}

Node *searchByName(Node *node, char *name)
{

    if(node == NULL)
        return NULL;

    if(strcasecmp(node->name, name) == 0)
        return node;

    Node *leftResult = searchByName(node->left, name);

    if(leftResult != NULL)
        return leftResult;

    return searchByName(node->right, name);
}

void displayBySearchBName(Node *node,char *name)
{
    Node *s = searchByName(node,name);
    if(s != NULL)
    {
        printf("%d\t",s->id);
        printf("%s\t",s->name);
        printf("%f\t",s->gpa);
    }
    else
    {
        printf("NOT FOUND");
    }
}

Node *FindMin(Node *node)
{
    if(node == NULL)
        return NULL;
    else if(node->left != NULL)
        return FindMin(node->left);
    else
        return node;
}

Node *delete(Node *node,int id)
{
    Node *temp;
    if(node == NULL)
    {
        printf("NOT FOUND\n");
        return NULL;
    }
    else if(id < node->id)
        node->left = delete(node->left, id);
    else if(id > node->id)
        node->right = delete(node->right, id);
    else
    {
        if(node->left != NULL && node->right != NULL)
        {
            temp = FindMin(node->right);
            node->id = temp->id;
            strcpy(node->name, temp->name);
            node->gpa = temp->gpa;
            node->right = delete(node->right, temp->id);
        }
        else
        {
            temp = node;
            if(node->left == NULL)
                node = node->right;
            else if(node->right == NULL)
                node = node->left;
            free(temp);
        }
    }

    if(node == NULL)
        return NULL;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if(balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);

    else if(balance > 1 && getBalance(node->left) < 0)
    {

        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    else if(balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);

    else if(balance < -1 && getBalance(node->right) > 0)
    {

        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Node *update(Node *node,int id)
{
    Node *s = searchById(node,id);
    if(s != NULL)
    {
        int choice;
        while(1)
        {
            printf("\nEnter 1 to update Id\n");
            printf("Enter 2 to update Name\n");
            printf("Enter 3 to update GPA\n");
            printf("Enter 4 to Exit\n");
            printf("Enter your choice: ");
            scanf("%d",&choice);

            if(choice == 1)
            {
                int newId;
                printf("Enter new Id: ");
                scanf("%d",&newId);

                if(searchById(node,newId))
                {
                    printf("Duplicate Id\n");
                    return node;
                }

                char tempName[30];
                float tempGpa;
                strcpy(tempName,s->name);
                tempGpa = s->gpa;
                node = delete(node,id);
                node = insert(node,newId,tempName,tempGpa);
                s = searchById(node,newId);
                id = newId;
            }
            else if(choice == 2)
            {

                printf("Enter new Name: ");
                getchar();
                fgets(s->name, sizeof(s->name), stdin);

                s->name[strcspn(s->name,"\n")] = '\0';

            }
            else if(choice == 3)
            {
                printf("Enter new GPA: ");
                scanf("%f",&s->gpa);

                while(s->gpa < 0 || s->gpa > 4)
                {
                    printf("Invalid GPA\n");
                    printf("Enter GPA again between 0 and 4: ");
                    scanf("%f",&s->gpa);
                }
            }

            else if(choice == 4)
            {
                break;
            }

            else
            {
                printf("Invalid Choice\n");
            }
        }
    }

    else
    {
        printf("NOT FOUND\n");
    }

    return node;
}

int DislpayAllStudents(Node *node)
{
     int c=0;
    if(node != NULL)
    {
        c++;
        DislpayAllStudents(node->left);
        printf("Id: %d - Name: %s - Gpa: %.2f \n",node->id,node->name,node->gpa);
        DislpayAllStudents(node->right);
    }
    return c;
}

int count(Node *node)
{
    if(node == NULL)
        return 0;
    else
        return 1+count(node->left)+count(node->right);
}

void DisplayTreeStatistics(Node *node)
{
    if(node == NULL)
    {
        printf("Tree is Empty");
        return;
    }
    printf("Tree height is: %d \t",height(node));
    printf("Total students is: %d \t",count(node));
}

void GpaStatistics(Node *node,int *totalStudents,float *SumGpa,float *MinimumGpa,float *MaximumGpa)
{
    if(node==NULL)
        return;
    (*totalStudents)++;
    (*SumGpa)+= node->gpa;

    if(node->gpa < *MinimumGpa)
        *MinimumGpa=node->gpa;
    if(node->gpa > *MaximumGpa)
        *MaximumGpa=node->gpa;

    GpaStatistics(node->left,totalStudents,SumGpa,MinimumGpa,MaximumGpa);
    GpaStatistics(node->right,totalStudents,SumGpa,MinimumGpa,MaximumGpa);

}

void AboveBelowAverage(Node *node,float AverageGpa,int *AboveAverage,int *BelowAverage)
{
    if(node==NULL)
        return;

    if(node->gpa < AverageGpa)
        (*BelowAverage)++;

    else if(node->gpa > AverageGpa)
        (*AboveAverage)++;

    AboveBelowAverage(node->left,AverageGpa,AboveAverage,BelowAverage);
    AboveBelowAverage(node->right,AverageGpa,AboveAverage,BelowAverage);
}

void DisplayGpaStatistics(Node *node)
{
    if(node==NULL)
    {
        printf("\nSystem is empty");
        return;
    }

    int totalStudents=0;
    float SumGpa=0,MinimumGpa=4.0,MaximumGpa=0;

    GpaStatistics(node,&totalStudents,&SumGpa,&MinimumGpa,&MaximumGpa);

    float AverageGpa = SumGpa/totalStudents;
    int AboveAverage=0,BelowAverage=0;

    AboveBelowAverage(node,AverageGpa,&AboveAverage,&BelowAverage);

    printf("\n**Gpa Statistics**\n");
    printf("\nMinimum Gpa: %f",MinimumGpa);
    printf("\nMaximum Gpa: %f",MaximumGpa);
    printf("\nAverage Gpa: %f",AverageGpa);
    printf("\nNo of students above average: %d",AboveAverage);
    printf("\nNo of students Below average: %d",BelowAverage);
}


Node *deleteAllStudents(Node *node)
{
    if(node != NULL)
    {
        deleteAllStudents(node->left);
        deleteAllStudents(node->right);
        free(node);
    }
    return NULL;
}

Node *FindPredecessor(Node *node, int id)
{
    Node *s = searchById(node,id);
    if(s != NULL)
    {
        // case 1 : Lw fi left subtree
        if(s->left != NULL)
        {
            Node *temp = s->left;
            while(temp->right != NULL)
                temp = temp->right;
            return temp;
        }
        // case 2 : Lw mafeesh left subtree
        else
        {
            Node *predecessor = NULL;
            while(node != NULL)
            {
                if(id > node->id)
                {
                    predecessor = node;
                    node = node->right;
                }
                else if(id < node->id)
                    node = node->left;
                else
                    break;
            }
            return predecessor;
        }
    }
    else
    {
        printf("NOT FOUND\n");
    }
    return NULL;
}

Node *FindSuccessor(Node *node, int id)
{
    Node *s = searchById(node,id);
    if(s != NULL)
    {
        // case 1 : Lw fi right subtree
        if(s->right != NULL)
        {
            Node *temp = s->right;
            while(temp->left != NULL)
            {
                temp = temp->left;
            }
            return temp;
        }
        // case 2 : Lw mafeesh right subtree
        else
        {
            Node *successor = NULL;
            while(node != NULL)
            {
                if(id < node->id)
                {
                    successor = node;
                    node = node->left;
                }
                else if(id > node->id)
                    node = node->right;
                else
                    break;
            }
            return successor;
        }
    }
    else
    {
        printf("NOT FOUND\n");
    }
    return NULL;
}

void DisplayPredecessorAndSuccessor(Node *node, int id)
{
    Node *s = searchById(node, id);
    if(s == NULL)
    {
        printf("NOT FOUND\n");
        return;
    }
    Node *predecessor = FindPredecessor(node, id);
    Node *successor = FindSuccessor(node, id);
    if(predecessor != NULL)
        printf("Predecessor: %d\n", predecessor->id);
    else
        printf("Predecessor: This is the first record\n");

    if(successor != NULL)
        printf("Successor: %d\n", successor->id);
    else
        printf("Successor: This is the last record\n");
}

int main(void)
{

    Node *root = NULL;
    int choice = -1 ;
    while (1)
    {

        printf("1-  add student\n");
        printf("2-  search student by ID\n");
        printf("3-  Search by Name\n");
        printf("4-  Update student\n");
        printf("5-  delete student by ID\n");
        printf("6-  Display All Students\n");
        printf("7-  Display Tree Statistics\n");
        printf("8-  Display GPA Statistics\n");
        printf("9-  Display Predecessor and Successor\n");
        printf("10- Delete all student\n");
        printf("0-  exit\n");
        printf("enter your choice:");
        scanf("%d",&choice);
        while(choice <0 || choice >10)
        {
            printf("enter valid choice");
            scanf("%d",&choice);
        }
        switch(choice)
        {
        case 0:
        {
            root=deleteAllStudents(root);
            exit(0);
        }
        case 1:
            {

                int id;
                char name[30];
                float gpa;
                printf("Enter ID: ");
                scanf("%d",&id);
                getchar();
                printf("Enter Name: ");
                fgets(name,sizeof(name),stdin);
                name[strcspn(name,"\n")] = '\0';
                printf("Enter GPA: ");
                scanf("%f",&gpa);
                root= insert(root,id,name,gpa);
                break;
            }
        case 2 :
            {
                int id;
                printf("Enter ID: ");
                scanf("%d",&id);
                displayBySearchByID(root,id);
                break;
            }
        case 3 :
            {
                char name[30];
                getchar();
                printf("Enter Name: ");
                fgets(name,sizeof(name),stdin);
                name[strcspn(name,"\n")] = '\0';
                displayBySearchBName(root,name);
                break;
            }
        case 4 :
            {
                int id;
                printf("Enter ID: ");
                scanf("%d",&id);
                root = update(root,id);
                break;
            }
        case 5:
            {
                int id;
                printf("Enter ID: ");
                scanf("%d",&id);
                root = delete(root,id);
                break;
            }
        case 6:
            {

                int x=DislpayAllStudents(root);
                    if(!x)
                    printf("empty");
                break;
            }
        case 7:
            {
                DisplayTreeStatistics(root);
                break;
            }
        case 8:
            {
                DisplayGpaStatistics(root);
                break;
            }
        case 9:
            {
                int id;
                printf("Enter ID: ");
                scanf("%d",&id);
                DisplayPredecessorAndSuccessor(root,id);
                break;
            }
        case 10:
            {
                root = deleteAllStudents(root);
                printf("all students deleted successfully\n");
                break;
            }

        }
        printf("\n\n\n");
    }


    return 0;
}
