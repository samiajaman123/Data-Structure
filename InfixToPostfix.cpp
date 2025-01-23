#include <iostream>
#include <string>
using namespace std;

struct N
{
    char d;
    N *next;
    N(char val) : d(val), next(nullptr) {}
};

class Stack
{
private:
    N *top;

public:
    Stack() : top(nullptr) {}
    void push(char val)
    {
        N *newN = new N(val);
        newN->next = top;
        top = newN;
    }
    char pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty!" << endl;
            return '\0';
        }
        char val = top->d;
        N *temp = top;
        top = top->next;
        delete temp;
        return val;
    }
    char peek()
    {
        if (isEmpty())
            return '\0';
        return top->d;
    }
    bool isEmpty()
    {
        return top == nullptr;
    }
};

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

bool isOperand(char c)
{
    return (isalpha(c) || isdigit(c));
}

string infixToPostfix(string infix)
{
    Stack stack;
    string postfix = "";
    for (char c : infix)
    {
        if (isOperand(c))
        {
            postfix += c;
        }
        else if (c == '(')
        {
            stack.push(c);
        }
        else if (c == ')')
        {
            while (!stack.isEmpty() && stack.peek() != '(')
            {
                postfix += stack.pop();
            }
            stack.pop();
        }
        else if (isOperator(c))
        {
            while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(c))
            {
                postfix += stack.pop();
            }
            stack.push(c);
        }
    }
    while (!stack.isEmpty())
    {
        postfix += stack.pop();
    }
    return postfix;
}

int main()
{
    string infix;
    cout << "Enter an infix expression: ";
    cin >> infix;
    string postfix = infixToPostfix(infix);
    cout << "Postfix Expression: " << postfix << endl;
    return 0;
}

