#include<iostream>
#include<stack>
#include<list>
#include<queue>
#include<string>
#include<math.h>
#define SPACE 10
using namespace std;


/* FINAL PROJECT
   MEMBERS:
  1) NAME: MUHAMMAD USAMA ANJUM
     REG NO: 201968
  2) NAME: ASAD ULLAH
     REG NO: 201310
  3) NAME: MUHAMMAD HAMZA TAHIR
     REG NO:201967

*/

//Node class
class node {
public:
    char value = 0;
    node* left;
    node* right;
    node* next = NULL;
    node(char c)
    {
        value = c;
        left = NULL;
        right = NULL;
    }
    node()
    {
        left = NULL;
        right = NULL;
    }
    friend class Stackk;
    friend class expression_tree;
};

//stack class with linked list implementation for expression tree
class Stackk {
    node* top = NULL;

public:
    void push(node*);
    node* pop();
    friend class expression_tree;

};
void Stackk::push(node* x)
{
    if (top == NULL) {
        top = x;
    }
    else {
        x->next = top;
        top = x;
    }
}
node* Stackk::pop()
{
    node* p = top;
    top = top->next;
    return p;
}
class expression_tree {
public:

    //breadth first traversal function
    void BreadthTraversasl(node* r)
    {

        if (r == NULL)
            return;

        //creating a queue using stl library
        queue<node*> q;


        q.push(r);

        while (!q.empty()) {

            node* n = q.front();
            cout << n->value << " ";
            q.pop();


            if (n->left != NULL)
                q.push(n->left);


            if (n->right != NULL)
                q.push(n->right);
        }
    }

    node* newNode(int data)
    {
        node* temp = new node;
        temp->value = data;
        temp->left = temp->right = NULL;
        return temp;
    }

    //function to print 2D expression tree
    void print2D(node* r, int space) {
        if (r == NULL)
            return;
        space += SPACE;
        print2D(r->right, space);
        cout << endl;
        for (int i = SPACE; i < space; i++)
            cout << " ";
        cout << r->value << "\n";
        print2D(r->left, space);
    }
};

//checking if it is operator or not
bool isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
    {
        return true;
    }
    else
    {
        return false;
    }
}

//checking precedence
int precedence(char c)
{
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

//converting infix to postfix by using stack stl library
string InfixToPostfix(stack<char> s, string infix)
{
    string postfix;
    for (int i = 0; i <= infix.length(); i++)
    {
        if ((infix[i] >= 'a' && infix[i] <= 'z')
            || (infix[i] >= 'A' && infix[i] <= 'Z') || (infix[i] >= '0' && infix[i] <= '100'))
        {
            postfix += infix[i];
        }
        else if (infix[i] == '(')
        {
            s.push(infix[i]);
        }
        else if (infix[i] == ')')
        {
            while ((s.top() != '(') && (!s.empty()))
            {
                char temp = s.top();
                postfix += temp;
                s.pop();
            }
            if (s.top() == '(')
            {
                s.pop();
            }
        }
        else if (isOperator(infix[i]))
        {
            if (s.empty())
            {
                s.push(infix[i]);
            }
            else
            {
                if (precedence(infix[i]) > precedence(s.top()))
                {
                    s.push(infix[i]);
                }
                else if ((precedence(infix[i]) == precedence(s.top())) && (infix[i] == '^'))
                {
                    s.push(infix[i]);
                }
                else
                {
                    while ((!s.empty()) && (precedence(infix[i]) <= precedence(s.top())))
                    {
                        postfix += s.top();
                        s.pop();
                    }
                    s.push(infix[i]);
                }
            }
        }
    }
    while (!s.empty())
    {
        postfix += s.top();
        s.pop();
    }

    return postfix;
}

//evaluation function of expression using stl library of stack
int evaluate(string s)
{
    stack<int> st;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] >= '0' && s[i] <= '100')
        {
            st.push(s[i] - '0');
        }
        else
        {
            int operand2 = st.top();
            st.pop();
            int operand1 = st.top();
            st.pop();

            switch (s[i])
            {
            case '+':
                st.push(operand1 + operand2);
                break;
            case '-':
                st.push(operand1 - operand2);
                break;
            case '*':
                st.push(operand1 * operand2);
                break;
            case '/':
                st.push(operand1 / operand2);
                break;
            case '^':
                st.push(pow(operand1, operand2));
                break;
            }
        }
    }

    return st.top();
}

template<class T>
class TreeNode
{
public:
    T value;
    TreeNode <T>* left;
    TreeNode <T>* right;



};

template<class T>
class BinaryTree {
private:

    TreeNode <T>* root; // Pointer to the root of BST

    void displayInOrder(TreeNode <T>*);
public:
    BinaryTree() { root = NULL; }
    void insertNode(T);
    bool find(T);
    void showNodesInOrder() { displayInOrder(root); }

};
template<typename T>
bool BinaryTree<T>::find(T num) {
    // The function starts from the root
    TreeNode <T>* nodePtr = root;

    while (nodePtr) {
        if (nodePtr->value == num)
            return true; // value is found
        else if (num < nodePtr->value)
            nodePtr = nodePtr->left;
        else
            nodePtr = nodePtr->right;

    }
    return false; // value not found
}

template<typename T>
void BinaryTree<T>::insertNode(T num) {
    TreeNode <T>* newNode, * nodePtr; // Pointer to create new node & traverse tree
    newNode = new TreeNode<T>; // Create a new node
    newNode->value = num;
    newNode->left = newNode->right = NULL;
    if (!root) root = newNode; // If tree is empty.
    else { // Tree is not empty
        nodePtr = root;
        while (nodePtr != NULL) {
            if (num < nodePtr->value) { // Left subtree
                if (nodePtr->left) { nodePtr = nodePtr->left; }
                else { nodePtr->left = newNode; break; }
            }
            else if (num > nodePtr->value) { // Right subtree
                if (nodePtr->right) nodePtr = nodePtr->right;
                else { nodePtr->right = newNode; break; }
            }
            else { cout << "Duplicate value found in tree.\n"; break; }
        }
    }
}

template<typename T>
void BinaryTree<T>::displayInOrder(TreeNode <T>* ptr) {
    if (ptr != NULL) {
        displayInOrder(ptr->left);
        cout << "  " << ptr->value << "     ";
        displayInOrder(ptr->right);
    }
}



int main()
{

    Stackk s;
    expression_tree a;
    string infix_exp, postfix_exp;
    cout << "\nENTER INFIX EXPRESSION :" << endl;
    cout << endl;
    cin >> infix_exp;
    cout << endl;
    stack <char> k;
    cout << "\nINFIX EXPRESSION: " << infix_exp << endl;
    cout << endl;
    postfix_exp = InfixToPostfix(k, infix_exp);
    cout << endl << "\nPOSTFIX EXPRESSION: " << postfix_exp << endl;
    cout << endl;

    node* x, * y, * z = 0;
    int l = postfix_exp.length();
    for (int i = 0; i < l; i++) {
        if (postfix_exp[i] == '+' || postfix_exp[i] == '-' || postfix_exp[i] == '*'
            || postfix_exp[i] == '/' || postfix_exp[i] == '^') {
            z = new node(postfix_exp[i]);
            x = s.pop();
            y = s.pop();
            z->left = y;
            z->right = x;
            s.push(z);
        }
        else {
            z = new node(postfix_exp[i]);
            s.push(z);
        }
    }
    cout << " \nTHE BREADTH FIRST TRAVERSAL OF EXPRESSION TREE: ";
    a.BreadthTraversasl(z);
    cout << endl;
    cout << endl;

    cout << "\nEVALUATION OF EXPRESSION : ";
    cout << evaluate(postfix_exp) << endl;
    cout << endl;
    cout << "\n2D VIEW OF EXPRESSION TREE : " << endl;
    a.print2D(z, 5);
    return 0;
}