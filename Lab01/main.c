#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char *word;
    int count;
    char *line;
} Data;
typedef struct Nodes
{
    Data data;
    struct Nodes *right, *left;
} node;
typedef struct Nodes *bst;
void insertnode(bst *root, Data x)
{
    if ((*root) == NULL)
    {
        *root = (node *)malloc(sizeof(node));
        (*root)->data = x;
        (*root)->right = NULL;
        (*root)->left = NULL;
    }
    else if (strcmp(x.word, ((*root)->data).word) > 0)
    {
        insertnode(&(*root)->right, x);
    }
    else if (strcmp(x.word, ((*root)->data).word) < 0)
    {
        insertnode(&(*root)->left, x);
    }
    else
    {
        ((*root)->data).count++;
        if (strstr(((*root)->data).line, x.line) == NULL)
            strcat(((*root)->data).line, x.line);
    }
}

bst searchnode(bst root, char *x)
{
    if (root == NULL)
        return NULL;
    else if (strcmp(x, (root->data).word) > 0)
        searchnode(root->right, x);
    else if (strcmp(x, (root->data).word) < 0)
        searchnode(root->left, x);
    else
        return root;
}

char *tolowerstr(char *str)
{
    int len = strlen(str);
    char *strlower = (char *)malloc(sizeof(char) * len);
    for (int i = 0; i <= strlen(str); i++)
    {
        if (str[i] >= 65 && str[i] <= 90)
        {
            strlower[i] = str[i] + 32;
        }
        else
        {
            strlower[i] = str[i];
        }
    }
    return strlower;
}

int havenumber(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            return 1;
        }
    }
    return 0;
}
int checkdot(char *str)
{
    int len = strlen(str);
    if (str[len - 1] == '.')
    {
        str[len - 1] = '\0';
        return 1;
    }
    return 0;
}
int checkname(char *str)
{
    if (str[0] >= 'A' && str[0] <= 'Z')
    {
        return 1;
    }
    return 0;
}
int compare(char *str1, char *str2)
{
    return strcmp(tolowerstr(str1), tolowerstr(str2));
}
int checkstopw(char **liststopw, int numstopword, char *word)
{
    for (int i = 0; i < numstopword; i++)
    {
        if (compare(liststopw[i], word) == 0)
            return 1;
    }
    return 0;
}
void readtxt(char *filename, char **liststopw, int numstopword, bst *root)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Open file error!");
        exit(1);
    }
    char *textline = (char *)malloc(sizeof(char) * 200);
    char *token = (char *)malloc(sizeof(char) * 50);
    char s[20] = " \n'`;?,()-;:*\"!";
    int linenumber = 0;
    int nextsentence = 0;
    while (fgets(textline, 200, fp) != NULL)
    {

        linenumber++;
        token = strtok((textline), s);
        while (token != NULL)
        {
            if (nextsentence == 0)
            {
                if (checkdot(token))
                {
                    nextsentence = 1;
                }
            }
            else
            {
                nextsentence = 0;
                if (checkstopw(liststopw, numstopword, token) == 0 && havenumber(token) == 0)
                {
                    inserttree(token, linenumber, root);
                }
                continue;
            }
            if (checkstopw(liststopw, numstopword, token) == 0 && havenumber(token) == 0 && checkname(token) == 0)
            {
                inserttree(token, linenumber, root);
            }
            token = strtok(NULL, s);
        }
    }

    fclose(fp);
    free(token);
    free(textline);
}
void inserttree(char *token, int linenumber, bst *root)
{
    token = tolowerstr(token);
    bst a = searchnode(*root, token);
    if (a != NULL)
    {
        char *str = (char *)malloc(sizeof(char) * 20);
        sprintf(str, ", %d", linenumber);
        strcat((a->data).line, str);
        a->data.count++;
        free(str);
    }
    else
    {
        Data x;
        x.word = (char *)malloc(sizeof(char) * 50);
        x.line = (char *)malloc(sizeof(char) * 10000);
        x.count = 1;
        strcpy(x.word, token);
        sprintf(x.line, ", %d", linenumber);
        insertnode(root, x);
    }
}

char **getliststopw(char *filename, int *numstopw)
{
    char str[50];
    char **textlinestopw = (char **)malloc(50 * sizeof(char *));
    for (int i = 0; i < 50; i++)
    {
        textlinestopw[i] = (char *)malloc(50 * sizeof(char));
    }
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Open file error!");
        exit(1);
    }
    int num = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%s\n", str);
        strcpy(textlinestopw[num], str);
        num++;
    }
    *numstopw = num;

    fclose(fp);
    return textlinestopw;
}
void displaytree(bst root)
{
    if (root != NULL)
    {
        displaytree(root->left);
        printf("\n%-20s%-2i%s", (root->data).word, (root->data).count, (root->data).line);
        displaytree(root->right);
    }
}
int main(int argc, char const *argv[])
{
    bst root = NULL;
    int *numStopWord = (int *)malloc(sizeof(int));
    char **liststopw = getliststopw("completed/stopw.txt", numStopWord);
    readtxt("completed/vanban.txt", liststopw, *numStopWord, &root);
    displaytree(root);
    free(numStopWord);
    free(root);
    return 0;
}