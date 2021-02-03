//
// Created by User on 17.11.2019.
//

#ifndef DIFFERENTIATOR_DIFFERENTIATOR_H
#define DIFFERENTIATOR_DIFFERENTIATOR_H

#define OPERATOR(name, num, operation, diff, meme)\
                    if (strcmp(str, #name) == 0)\
        {\
            NodeFill(temp, OPERATORCODE, num);\
            continue;\
        }

#define OPERATOR_DIV(name, num, operation, diff, meme)\
                    if (strcmp(str, #name) == 0)\
        {\
            NodeFill(temp, OPERATORCODE, num);\
            continue;\
        }

#define OPERATOR_ONE(name, num, operation, diff, meme)\
                    if (strcmp(str, #name) == 0)\
        {\
            NodeFill(temp, OPERATORCODE, num);\
            continue;\
        }

#include <math.h>
#include "MyTree.h"
#include "Config.h"


void FileRestoreTree (FILE* fin, node_t* node)
{
    node_t* temp = node;
    node_t* tempcpy = nullptr;
    char str[STR_MAX] = "";

    fscanf(fin, "%s", str);

    while (fscanf(fin, "%s", str) != EOF)
    {

        if (strcmp(str, "(") == 0)
        {
            tempcpy = NodeCreate(10, 0);

            if (temp->left == nullptr)
            {
                NodeLeft(temp, tempcpy);
                temp = tempcpy;
                continue;
            }
            else if (temp->right == nullptr)
            {
                NodeRight(temp, tempcpy);
                temp = tempcpy;
                continue;
            }
            else
                printf("Expression error\n");
        }

        if (strcmp(str, ")") == 0)
        {
            tempcpy = temp->parent;
            temp = tempcpy;
            continue;
        }

        if ((str[0] >= 'a') && (str[0] <= 'z'))
        {
            NodeFill(temp, VAR, str[0]);
            continue;
        }

        #include "Operator.h"

        double tempnum = 0;
        if ((str[0] >= '0') && (str[0] <= '9'))
        {
            tempnum = std::stod(&str[0]);
            NodeFill(temp, CONST, tempnum);
        }
    }
}

#undef OPERATOR
#undef OPERATOR_ONE
#undef OPERATOR_DIV

node_t* NodeCopy (node_t* node1)
{
    if (!node1)
        return nullptr;
    node_t* node2 = NodeCreate(0, 0);
    node2->data.type = node1->data.type;
    node2->data.data = node1->data.data;
    node2->left = NodeCopy(node1->left);
    node2->right = NodeCopy(node1->right);
    return node2;
}

#define OPERATOR(name, num, operation, diff, meme)\
    case num:\
        diff\
        break;

#define OPERATOR_DIV(name, num, operation, diff, meme)\
    case num:\
        diff\
        break;

#define OPERATOR_ONE(name, num, operation, diff, meme)\
    case num:\
        diff\
        break;

node_t* TreeDiff (node_t* node)
{
    node_t* temp = NodeCreate(0, 0);

    if (node->data.type == CONST)
    {
        NodeFill(temp, CONST, 0);
        return temp;
    }

    if (node->data.type == VAR)
    {
        NodeFill(temp, CONST, 1);
        return temp;
    }

    if (node->data.type == OPERATORCODE)
    {
        switch ((int) node->data.data)
        {
#include "Operator.h"
        }
    }

    return temp;
}

#undef OPERATOR
#undef OPERATOR_ONE
#undef OPERATOR_DIV


#define OPERATOR(name, num, operation, diff, meme)\
    case num:\
        operation\
        break;

#define OPERATOR_ONE(name, num, operation, diff, meme)\
    case num:\
        operation\
        break;

#define OPERATOR_DIV(name, num, operation, diff, meme)\
    case num:\
        operation\
        break;

void Simplify(node_t* node) {
    if (node == nullptr) {
        return;
    }
    int ind = 0;

    if ((node->data.type == OPERATORCODE) && (node->left->data.type == CONST) && ((node->right == nullptr) || (node->right->data.type == CONST)))
        switch ((int) node->data.data)
        {
#include "Operator.h"
        }

    if (node->data.type == OPERATORCODE && node->data.data == MUL && ((node->left->data.type == CONST && node->left->data.data == 0) || (node->right->data.type == CONST && node->right->data.data == 0)))
    {
        node->data.type = CONST;
        node->data.data = 0;
        //BranchDelete(node->left);
        node->left = nullptr;
        //BranchDelete(node->right);
        node->right = nullptr;
    }

    if (node->data.type == OPERATORCODE && node->data.data == MUL && node->left->data.type == CONST && node->left->data.data == 1)
    {
        NodeCpy(node, node->right);
    }

    if (node->data.type == OPERATORCODE && node->data.data == MUL && node->right->data.type == CONST && node->right->data.data == 1)
    {
        NodeCpy(node, node->left);
    }

    if (node->data.type == OPERATORCODE && node->data.data == PLUS && node->left->data.type == CONST && node->left->data.data == 0)
    {
        NodeCpy(node, node->right);
    }

    if (node->data.type == OPERATORCODE && node->data.data == PLUS && node->right->data.type == CONST && node->right->data.data == 0)
    {
        NodeCpy(node, node->left);
    }

    if (node->data.type == OPERATORCODE && node->data.data == MINUS && node->right->data.type == CONST && node->right->data.data == 0)
    {
        NodeCpy(node, node->left);
    }

        Simplify(node->left);
    Simplify(node->right);

}

#undef OPERATOR
#undef OPERATOR_ONE
#undef OPERATOR_DIV

#define CHECKOPERATOR (node->data.type == OPERATORCODE && node->parent->data.type == OPERATORCODE && (node->data.data == PLUS || node->data.data == MINUS || node->data.data == MUL || node->data.data == DEG) && (node->parent->data.data == MUL || node->parent->data.data == DEG))

#define CHECKPRIORITY (((node->data.data == PLUS || node->data.data == MINUS) && (node->parent->data.data == MUL || node->parent->data.data == DEG)) || (node->data.data == MUL && node->parent->data.data == DEG))


void TeXExport(FILE* fout, node_t* node)
{
    if (!node)
        return;

    int temp = 0;
    if (node->parent)
        if (CHECKOPERATOR && CHECKPRIORITY)
        {
            temp = fprintf(fout, "(");
            ///printf("BAAAAA!\tDATA\t%lf\tPARENT\t%lf\tPARENTRIGHT\t%lf\tTEMP\t%d\n", node->data.data, node->parent->data.data, node->parent->right->data.data, temp);
        }

    switch(node->data.type)
    {
        case CONST:
            fprintf(fout, "%.3lf", node->data.data);
            break;

        case VAR:
            fprintf(fout, "%c", (char)node->data.data);
            break;

        case OPERATORCODE:
            switch((int)node->data.data)
            {

#define OPERATOR_ONE(name, num, operation, diffcode, meme)\
                case num:\
                    fprintf(fout, "%s(", #name);\
                    break;

#define OPERATOR(name, num, operation, diffcode, meme)\
                case num:\
                    break;

#define OPERATOR_DIV(name, num, operation, diffcode, meme)\
                case num:\
                    fprintf(fout, "\\frac{");\
                    break;

#include "Operator.h"

#undef OPERATOR
#undef OPERATOR_ONE
#undef OPERATOR_DIV

            }
            break;
    }

    TeXExport(fout, node->left);

    if (node->data.type == OPERATORCODE)
        switch((int) node->data.data)
        {
#define OPERATOR_DIV(name, num, operation, diffcode, meme)\
                case num:\
                    fprintf(fout, "}{");\
                    break;

#define OPERATOR_ONE(name, num, operation, diffcode, meme)\
                case num:\
                    fprintf(fout, ")");\
                    break;

#define OPERATOR(name, num, operation, diffcode, meme)\
                case num:\
                fprintf(fout, "%s", #name);\
                    break;

#include "Operator.h"

#undef OPERATOR
#undef OPERATOR_ONE
#undef OPERATOR_DIV
        }

    TeXExport(fout, node->right);

    if (node->data.type == OPERATORCODE && node->data.data == DIV)
        fprintf(fout, "}");

    if (node->parent)
        if (CHECKOPERATOR && CHECKPRIORITY)
            fprintf(fout, ")");

}

#define OPERATOR(name, num, operation, diff, meme)\
    case num:\
        meme\
        break;

#define OPERATOR_DIV(name, num, operation, diff, meme)\
    case num:\
        meme\
        break;

#define OPERATOR_ONE(name, num, operation, diff, meme)\
    case num:\
        meme\
        break;

    node_t* TreeMemes (FILE* fout, node_t* node)
    {
        if (!node->parent)
            fprintf(fout, "\\documentclass{article}\n"
                      "\\usepackage[utf8]{inputenc}\n"
                      "\\usepackage{amsmath}\n"
                      "\n"
                      "\\title{How to count the derivative?}\n"
                      "\\date{December 2019}\n"
                      "\n"
                      "\\begin{document}\n"
                      "\n"
                      "\\maketitle\n");
        node_t* temp = NodeCreate(0, 0);
        node_t* tempone = nullptr;
        node_t* tempcpy = nullptr;

        if (node->data.type == CONST)
        {
            NodeFill(temp, CONST, 0);
            //return temp;
        }

        if (node->data.type == VAR)
        {
            NodeFill(temp, CONST, 1);
            //return temp;
        }

        if (node->data.type == OPERATORCODE)
        {
            switch ((int) node->data.data)
            {
#include "Operator.h"
            }
        }


        if(!node->parent)
        {
            Simplify(temp);
            Simplify(temp);
            Simplify(temp);
            Simplify(temp);
            fprintf(fout, "And finally after conducting several simplifications we get\n");
            fprintf(fout, "\\begin{equation}\n");
            fprintf(fout, "\\[");
            TeXExport(fout, temp);
            fprintf(fout, "\\]\n");
            fprintf(fout, "\\end{equation}\n\n");
            fprintf(fout, "\\end{document}\n");
        }
        return temp;
    }



#undef OPERATOR
#undef OPERATOR_ONE
#undef OPERATOR_DIV


#undef FREELEFT
#undef FREERIGHT
#undef CONSTTYPE


#endif //DIFFERENTIATOR_DIFFERENTIATOR_H
