#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "MyTree.h"
#include "Differentiator.h"

void testdatafprintf();

void test();

void testtree();

void testcopy();

void testdiff();

int main() {
    //test();
    //testtree();
    //testcopy();
    testdiff();
    return 0;
}

void testdiff()
{
    node_t* head = NodeCreate(0, 0);

    FILE* fin = fopen("output2.txt", "r");
    FileRestoreTree(fin, head);
    fclose(fin);

    FILE* foutold = fopen("test.tex", "w");
    TeXExport(foutold, head);
    fclose(foutold);

    node_t* headnew = TreeDiff(head);

    Simplify(headnew);
    Simplify(headnew);
    Simplify(headnew);
    Simplify(headnew);

    FILE* fout = fopen("output5.txt", "w");
    FilePrintTree(fout, headnew);
    fclose(fout);

    FILE* fouttex = fopen("equation.tex", "w");
    TeXExport(fouttex, headnew);
    fclose(fouttex);

    FILE* foutmemes = fopen("memes.tex", "w");
    TreeMemes(fout, head);
    fclose(foutmemes);
}

void testcopy()
{
    node_t* head = NodeCreate(0, 0);

    FILE* fin = fopen("output2.txt", "r");
    FileRestoreTree(fin, head);
    fclose(fin);

    node_t* headnew = NodeCopy(head);

    FILE* fout = fopen("output4.txt", "w");
    FilePrintTree(fout, headnew);
    fclose(fout);
}

void testtree()
{
    node_t* head = NodeCreate(0, 0);
    FILE* fin = fopen("output2.txt", "r");
    FileRestoreTree(fin, head);
    fclose(fin);

    FILE* fout = fopen("output3.txt", "w");
    FilePrintTree(fout, head);
    fclose(fout);
}

void test()
{
    node_t* node2 = NodeCreate(3, CONST);
    node_t* head = NodeCreate(3, OPERATORCODE);
    node_t* node1 = NodeCreate('x', VAR);
    NodeLeft(head, node1);
    NodeRight(head, node2);
    FILE* fout = fopen("output2.txt", "w");
    FilePrintTree(fout, head);
    fclose(fout);
}


void testdatafprintf()
{
    tree_t tree = {};
    FILE* fout = fopen("output.txt", "w");
    node_t* head = NodeCreate(10, 1);
    FileNodePrint(fout, head);

    NodeFill(head, 2, 'x');
    FileNodePrint(fout, head);

    NodeFill(head, 3, 1);
    FileNodePrint(fout, head);

    NodeFill(head, 3, 2);
    FileNodePrint(fout, head);

    NodeFill(head, 3, 3);
    FileNodePrint(fout, head);

    NodeFill(head, 3, 4);
    FileNodePrint(fout, head);

    NodeFill(head, 3, 5);
    FileNodePrint(fout, head);

    fclose(fout);
}