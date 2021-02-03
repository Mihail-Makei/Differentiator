

#include "Config.h"
#include "MyTree.h"

#define FREELEFT free(node->left);\
        node->left = nullptr;

#define FREERIGHT free(node->right);\
        node->right = nullptr;

#define CONSTTYPE node->data.type = CONST;

#define OPERATORFILL(a) NodeFill(temp, OPERATORCODE, a);

#define NODETEMP NodeLeft(temp, leftnode);\
                NodeRight(temp, rightnode);

#define MEMEPRINT(arg) fprintf(fout, arg);\
fprintf(fout, "\\begin{equation}\n");\
fprintf(fout, "\\[");\
tempone = temp;\
printf("TEMPONE\t%lf\n", tempone->data.data);\
\
while (tempone->parent != nullptr)\
{\
tempcpy = tempone->parent;\
tempone = tempcpy;\
printf("TEMPTWO\t%lf\n", tempone->right->data.data);\
}\
\
\
TeXExport(fout, tempone);\
\
fprintf(fout, "\\]\n");\
fprintf(fout, "\\end{equation}\n\n");

/***********************************************************************************************************************/

OPERATOR(+, PLUS,
{
    node->data.data = node->left->data.data + node->right->data.data;
    CONSTTYPE;
    FREELEFT;
    FREERIGHT;
},
{
    NodeFill(temp, OPERATORCODE, PLUS);

    node_t* leftnode = TreeDiff(node->left);
    node_t* rightnode = TreeDiff(node->right);

    NodeLeft(temp, leftnode);
    NodeRight(temp, rightnode);

    return temp;
},
{
    OPERATORFILL(PLUS);

    node_t* leftnode = NodeCopy(node->left);
    node_t* rightnode = NodeCopy(node->right);

    NodeLeft(temp, leftnode);
    NodeRight(temp, rightnode);

    fprintf(fout, "COPY\n");
    MEMEPRINT("Let's consider the following part of equation\n\n");

    node_t* left = TreeMemes(fout, node->left);
    node_t* right = TreeMemes(fout, node->right);

    NodeLeft(temp, left);
    NodeRight(temp, right);

    MEMEPRINT("After, to be honest, pretty difficult transformations we get\n\n");
})


OPERATOR(-, MINUS,
{
    node->data.data = node->left->data.data - node->right->data.data;
    node->data.type = CONST;
    free(node->left);
    node->left = nullptr;
    free(node->right);
    node->right = nullptr;
},
{
    NodeFill(temp, OPERATORCODE, MINUS);

    node_t* leftnode = TreeDiff(node->left);
    node_t* rightnode = TreeDiff(node->right);

    NodeLeft(temp, leftnode);
    NodeRight(temp, rightnode);

    //return temp;
},
{
    OPERATORFILL(MINUS);

    node_t* leftnode = NodeCopy(node->left);
    node_t* rightnode = NodeCopy(node->right);

    NodeLeft(temp, leftnode);
    NodeRight(temp, rightnode);

    fprintf(fout, "COPY\n");
    MEMEPRINT("Let's consider the following part of equation\n\n");

    node_t* left = TreeMemes(fout, node->left);
    node_t* right = TreeMemes(fout, node->right);

    NodeLeft(temp, left);
    NodeRight(temp, right);

    MEMEPRINT("After some not that obvious transformations we get\n\n");
})
///-----------------------------------------------------------------------------------------------------------------------------------------------------------

OPERATOR(*, MUL,
{
    node->data.data = node->left->data.data * node->right->data.data;
    node->data.type = CONST;
    free(node->left);
    node->left = nullptr;
    free(node->right);
    node->right = nullptr;
},
{
    OPERATORFILL(PLUS);

    node_t* leftnode = NodeCreate(MUL, OPERATORCODE);
    node_t* rightnode = NodeCreate(MUL, OPERATORCODE);

    NodeLeft(temp, leftnode);
    NodeRight(temp, rightnode);

    node_t* leftone = TreeDiff(node->left);
    node_t* lefttwo = NodeCopy(node->right);

    node_t* rightone = NodeCopy(node->left);
    node_t* righttwo = TreeDiff(node->right);

    NodeLeft(leftnode, leftone);
    NodeRight(leftnode, lefttwo);
    NodeLeft(rightnode, rightone);
    NodeRight(rightnode, righttwo);

    //return temp;
},
{
    NodeFill(temp, OPERATORCODE, PLUS);

    node_t* leftnode = NodeCreate(MUL, OPERATORCODE);
    node_t* rightnode = NodeCreate(MUL, OPERATORCODE);

    NodeLeft(temp, leftnode);
    NodeRight(temp, rightnode);

    node_t* leftone = NodeCopy(node->left);
    node_t* lefttwo = NodeCopy(node->right);

    node_t* rightone = NodeCopy(node->left);
    node_t* righttwo = NodeCopy(node->right);

    NodeLeft(leftnode, leftone);
    NodeRight(leftnode, lefttwo);
    NodeLeft(rightnode, rightone);
    NodeRight(rightnode, righttwo);

    MEMEPRINT("Now let's differentiate the multiplication of two functions\n\n");

    leftone = TreeMemes(fout, node->left);
    lefttwo = NodeCopy(node->right);

    rightone = NodeCopy(node->left);
    righttwo = TreeMemes(fout, node->right);

    NodeLeft(leftnode, leftone);
    NodeRight(leftnode, lefttwo);
    NodeLeft(rightnode, rightone);
    NodeRight(rightnode, righttwo);

    MEMEPRINT("After some very easy transformations we get\n\n");
})

OPERATOR_DIV(/, DIV,
{
    node->data.data = node->left->data.data / node->right->data.data;
    node->data.type = CONST;
    free(node->left);
    node->left = nullptr;
    free(node->right);
    node->right = nullptr;
},
{
    NodeFill(temp, OPERATORCODE, DIV);

    node_t* leftnode = NodeCreate(MINUS, OPERATORCODE);
    node_t* rightnode = NodeCreate(MUL, OPERATORCODE);

    NodeLeft(temp, leftnode);
    NodeRight(temp, rightnode);

    node_t* leftone = NodeCreate(MUL, OPERATORCODE);
    node_t* lefttwo = NodeCreate(MUL, OPERATORCODE);

    node_t* rightone = NodeCopy(node->right);
    node_t* righttwo = NodeCopy(node->right);

    NodeLeft(leftnode, leftone);
    NodeRight(leftnode, lefttwo);
    NodeLeft(rightnode, rightone);
    NodeRight(rightnode, righttwo);

    node_t* leftoneone = TreeDiff(node->left);
    node_t* leftonetwo = NodeCopy(node->right);
    node_t* lefttwoone = NodeCopy(node->left);
    node_t* lefttwotwo = TreeDiff(node->right);

    NodeLeft(leftone, leftoneone);
    NodeRight(leftone, leftonetwo);
    NodeLeft(lefttwo, lefttwoone);
    NodeRight(lefttwo, lefttwotwo);

    //return temp;




},
{
OPERATORFILL(DIV);

node_t* leftnode = NodeCreate(MINUS, OPERATORCODE);
node_t* rightnode = NodeCreate(MUL, OPERATORCODE);

NodeLeft(temp, leftnode);
NodeRight(temp, rightnode);

node_t* leftone = NodeCreate(MUL, OPERATORCODE);
node_t* lefttwo = NodeCreate(MUL, OPERATORCODE);

node_t* rightone = NodeCopy(node->right);
node_t* righttwo = NodeCopy(node->right);

NodeLeft(leftnode, leftone);
NodeRight(leftnode, lefttwo);
NodeLeft(rightnode, rightone);
NodeRight(rightnode, righttwo);

node_t* leftoneone = NodeCopy(node->left);
node_t* leftonetwo = NodeCopy(node->right);
node_t* lefttwoone = NodeCopy(node->left);
node_t* lefttwotwo = NodeCopy(node->right);

NodeLeft(leftone, leftoneone);
NodeRight(leftone, leftonetwo);
NodeLeft(lefttwo, lefttwoone);
NodeRight(lefttwo, lefttwotwo);

MEMEPRINT("Now let's differentiate the division\n\n");

leftoneone = TreeMemes(fout, node->left);
leftonetwo = NodeCopy(node->right);
lefttwoone = NodeCopy(node->left);
lefttwotwo = TreeMemes(fout, node->right);

NodeLeft(leftone, leftoneone);
NodeRight(leftone, leftonetwo);
NodeLeft(lefttwo, lefttwoone);
NodeRight(lefttwo, lefttwotwo);

MEMEPRINT("As it can easily be shown, we get\n\n");
})

OPERATOR_ONE(Sin, SINE,
{
    node->data.data = sin(node->left->data.data);
    node->data.type = CONST;
    free(node->left);
    node->left = nullptr;
    free(node->right);
    node->right = nullptr;
},
{
    NodeFill(temp, OPERATORCODE, MUL);

    node_t* leftnode = NodeCreate(COSINE, OPERATORCODE);
    node_t* rightnode = TreeDiff(node->left);

    NodeLeft(temp, leftnode);
    NodeRight(temp, rightnode);

    node_t* leftone = NodeCopy(node->left);

    NodeLeft(leftnode, leftone);

    //return temp;


},
{
    OPERATORFILL(MUL);

    node_t* leftnode = NodeCreate(COSINE, OPERATORCODE);
    node_t* rightnode = NodeCopy(node->left);

    NodeLeft(temp, leftnode);
    NodeRight(temp, rightnode);

    node_t* leftone = NodeCopy(node->left);

    NodeLeft(leftnode, leftone);

    MEMEPRINT("Now let's differentiate the sine\n\n");

    leftnode = NodeCreate(COSINE, OPERATORCODE);
    rightnode = TreeMemes(fout, node->left);

    NodeLeft(temp, leftnode);
    NodeRight(temp, rightnode);

    leftone = NodeCopy(node->left);

    NodeLeft(leftnode, leftone);

    MEMEPRINT("Now, after two pages of different transformations, we get\n\n");
})

OPERATOR_ONE(Cos, COSINE,
{
    node->data.data = cos(node->left->data.data);
    node->data.type = CONST;
    free(node->left);
    node->left = nullptr;
    free(node->right);
    node->right = nullptr;
},
{
    NodeFill(temp, OPERATORCODE, MUL);

    node_t* leftnode = NodeCreate(-1, CONST);
    node_t* rightnode = NodeCreate(MUL, OPERATORCODE);

    NodeLeft(temp, leftnode);
    NodeRight(temp, rightnode);

    node_t* rightone = NodeCreate(SINE, OPERATORCODE);
    node_t* righttwo = TreeDiff(node->left);

    NodeLeft(rightnode, rightone);
    NodeRight(rightnode, righttwo);

    node_t* value = NodeCopy(node->left);
    NodeLeft(rightone, value);
},
{
    NodeFill(temp, OPERATORCODE, MUL);

    node_t* leftnode = NodeCreate(-1, CONST);
    node_t* rightnode = NodeCreate(MUL, OPERATORCODE);

    NodeLeft(temp, leftnode);
    NodeRight(temp, rightnode);

    node_t* rightone = NodeCreate(SINE, OPERATORCODE);
    node_t* righttwo = NodeCopy(node->left);

    NodeLeft(rightnode, rightone);
    NodeRight(rightnode, righttwo);

    node_t* value = NodeCopy(node->left);
    NodeLeft(rightone, value);

    MEMEPRINT("Now let's differentiate the cosine\n\n");

    righttwo = TreeMemes(fout, node->left);

    NodeRight(rightnode, righttwo);

    value = NodeCopy(node->left);
    NodeLeft(rightone, value);

    MEMEPRINT("Now as every spring-2020 army recruit knows\n\n");
})

OPERATOR_ONE(Ln, LN,
{
    node->data.data = log(node->left->data.data);
    FREELEFT;
    CONSTTYPE;
},
{
    OPERATORFILL(MUL);

    node_t* leftnode = TreeDiff(node->left);
    node_t* rightnode = NodeCreate(DIV, OPERATORCODE);

    NodeLeft(temp, leftnode);
    NodeRight(temp, rightnode);

    node_t* left = NodeCreate(1, CONST);
    node_t* right = NodeCopy(node->left);

    NodeLeft(rightnode, left);
    NodeRight(rightnode, right);
},
{
    OPERATORFILL(MUL);

    node_t* leftnode = NodeCopy(node->left);
    node_t* rightnode = NodeCreate(DIV, OPERATORCODE);

    NodeLeft(temp, leftnode);
    NodeRight(temp, rightnode);

    node_t* left = NodeCreate(1, CONST);
    node_t* right = NodeCopy(node->left);

    NodeLeft(rightnode, left);
    NodeRight(rightnode, right);

    MEMEPRINT("Now let's differentiate the logarythm\n\n");

    leftnode = TreeMemes(fout, node->left);

    NodeLeft(temp, leftnode);

    MEMEPRINT("Now as every razdolbay knows\n\n");
})

OPERATOR(^, DEG,
{
    node->data.data = pow(node->left->data.data, node->right->data.data);
    FREELEFT;
    FREERIGHT;
    CONSTTYPE;
},
{
    OPERATORFILL(MUL);

    node_t* leftnode = NodeCopy(node);
    node_t* rightnode = NodeCreate(PLUS, OPERATORCODE);

    NODETEMP;

    node_t* left = NodeCreate(MUL, OPERATORCODE);
    node_t* right = NodeCreate(MUL, OPERATORCODE);

    NodeLeft(rightnode, left);
    NodeRight(rightnode, right);

    node_t* leftleft = NodeCreate(DIV, OPERATORCODE);
    node_t* leftright = TreeDiff(node->left);

    NodeLeft(left, leftleft);
    NodeRight(left, leftright);

    node_t* leftleftone = NodeCopy(node->right);
    node_t* leftlefttwo = NodeCopy(node->left);

    NodeLeft(leftleft, leftleftone);
    NodeRight(leftleft, leftlefttwo);

    node_t* rightleft = NodeCreate(LN, OPERATORCODE);
    node_t* rightright = TreeDiff(node->right);

    NodeLeft(right, rightleft);
    NodeRight(right, rightright);

    node_t* rightleftleft = NodeCopy(node->left);

    NodeLeft(rightleft, rightleftleft);
},
{
OPERATORFILL(MUL);

node_t* leftnode = NodeCopy(node);
node_t* rightnode = NodeCreate(PLUS, OPERATORCODE);

NODETEMP;

node_t* left = NodeCreate(MUL, OPERATORCODE);
node_t* right = NodeCreate(MUL, OPERATORCODE);

NodeLeft(rightnode, left);
NodeRight(rightnode, right);

node_t* leftleft = NodeCreate(DIV, OPERATORCODE);
node_t* leftright = NodeCopy(node->left);

NodeLeft(left, leftleft);
NodeRight(left, leftright);

node_t* leftleftone = NodeCopy(node->right);
node_t* leftlefttwo = NodeCopy(node->left);

NodeLeft(leftleft, leftleftone);
NodeRight(leftleft, leftlefttwo);

node_t* rightleft = NodeCreate(LN, OPERATORCODE);
node_t* rightright = NodeCopy(node->right);

NodeLeft(right, rightleft);
NodeRight(right, rightright);

node_t* rightleftleft = NodeCopy(node->left);

NodeLeft(rightleft, rightleftleft);

MEMEPRINT("Now let's do the transformations you must have learned during your high school studies\n\n");

leftright = TreeMemes(fout, node->left);
rightright = TreeMemes(fout, node->right);

NodeRight(left, leftright);
NodeRight(right, rightright);

MEMEPRINT("Now, after some obvious transformations we get\n\n");
})
