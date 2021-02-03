#ifndef TREE_MYTREE_H
#define TREE_MYTREE_H

#include <string.h>
#include "Config.h"
//#include "Errors.h"


typedef char elem_t;


typedef struct NodeData
{
    int type;
    double data;
} data_t;


typedef struct TreeNode
{
    data_t data;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
} node_t;


typedef struct Tree
{
    node_t* head;
    int err;
} tree_t;



node_t* NodeCreate(double data, int type)
{
    node_t* node = (node_t*) calloc(1, sizeof(node_t));

    node->data.type = type;
    node->data.data = data;

    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;
    return node;
}


node_t* TreeCreate(tree_t* tree)
{
    tree->err = 0;
    tree->head = NodeCreate(0, 0);

    return tree->head;
}


node_t* TreeHead(const tree_t* tree)
{
    return tree->head;
}


node_t* TreeLeft(const node_t* node)
{
    return node->left;
}


node_t* TreeRight(const node_t* node)
{
    return node->right;
}


void NodeFill(node_t* node, int type, double data)
{
    node->data.type = type;
    node->data.data = data;
}


/*void NodePrint(const node_t* node)
{
    switch (node->data.type)
    {
        case CONST:
            printf(" %.3lf ", node->data.data);
            break;

        case VAR:
            printf(" %c ", (char) node->data.data);
            break;

        case OPERATOR:
            switch ((int) node->data.data)
            {
            #define OPERATOR(name, num, operation)\
                case num:\
                    printf(" %s ", #name);\
                    break;

            #include "Operator.h"

            #undef OPERATOR
            }
    }
}*/

void FileNodePrint(FILE* fout, const node_t* node)
{
    switch (node->data.type)
    {
        case CONST:
            fprintf(fout, " %.3lf ", node->data.data);
            break;

        case VAR:
            fprintf(fout, " %c ", (char) node->data.data);
            break;

        case OPERATORCODE:
            switch ((int) node->data.data)
            {
            #define OPERATOR(name, num, operation, diffcode, meme)\
                case num:\
                    fprintf(fout, " %s ", #name);\
                    break;

            #define OPERATOR_DIV(name, num, operation, diffcode, meme)\
                case num:\
                    fprintf(fout, " %s ", #name);\
                    break;

            #define OPERATOR_ONE(name, num, operation, diffcode, meme)\
                case num:\
                    break;

            #include "Operator.h"

            #undef OPERATOR_ONE
            #undef OPERATOR
            #undef OPERATOR_DIV
            }
    }
}

void NodeCpy(node_t* node1, node_t* node2)
{
    node_t* temp = node2;

    node1->data.type = temp->data.type;
    node1->data.data = temp->data.data;
    node1->left = temp->left;
    node1->right = temp->right;
    node1->parent = temp->parent;
}

void FileNodePrintOne(FILE* fout, const node_t* node)
{
    switch (node->data.type)
    {
        case CONST:
            break;

        case VAR:
            break;

        case OPERATORCODE:
            switch ((int) node->data.data)
            {
#define OPERATOR(name, num, operation, diffcode, meme)\
                case num:\
                    break;

#define OPERATOR_DIV(name, num, operation, diffcode, meme)\
                case num:\
                    break;

#define OPERATOR_ONE(name, num, operation, diffcode, meme)\
                case num:\
                    fprintf(fout, " %s ", #name);\
                    break;

#include "Operator.h"

#undef OPERATOR_ONE
#undef OPERATOR
#undef OPERATOR_DIV
            }
    }
}

void NodeRight (node_t* parent, node_t* child)
{
    parent->right = child;
    child->parent = parent;
}


void NodeLeft (node_t* parent, node_t* child)
{
    parent->left = child;
    child->parent = parent;
}


void NodeDelete(node_t* node)
{
    node->parent = nullptr;
    free(node);
}


void BranchDelete(node_t* node)
{
    if (node->left == nullptr)
        NodeDelete(node->left);
    else
        BranchDelete(node->left);

    if (node->right == nullptr)
        NodeDelete(node->right);
    else
        BranchDelete(node->right);
}


void FilePrintTree(FILE* fout, node_t* node)
{
    if (!node)
        return;

    fprintf(fout, " ( ");

    FileNodePrintOne(fout, node);

    FilePrintTree(fout, node->left);

    FileNodePrint(fout, node);

    FilePrintTree(fout, node->right);

    fprintf(fout, " ) ");
}




/*void TreeGraph(FILE* fout, node_t* node)
{
    if (!node)
    {
        return;
    }

    if (node->parent != nullptr)
    {
        //printf("PARENT\t%s\tDATA\t%s\n", node->parent->data, node->data);
        fprintf(fout, "\"");
        fputs(node->parent->data, fout);
        fprintf(fout, "\" -- \"");
        fputs(node->data, fout);
        fprintf(fout, "\";\n");
    }
    TreeGraph(fout, node->left);
    TreeGraph(fout, node->right);
}*/
#endif //TREE_MYTREE_H
