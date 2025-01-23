
#include <iostream>
#include <stack>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;
int precedence(char o)
{
    if (o == '+' || o == '-')
        return 1;
    if (o == '*' || o == '/')
        return 2;
    if (o == '^')
        return 3;
    return 0;
}
bool isOperators(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}
string infixToPrefix(string infix)
{
    stack<char> operators;
    stack<string> operands;
    for (int i = 0; i < infix.size(); i++)
    {
        char c = infix[i];
        if (isdigit(c))
        {
            string operand = "";
            while (i < infix.size() && isdigit(infix[i]))
            {
                operand += infix[i];
                i++;
            }
            i--;
            operands.push(operand);
        }
        else if (c == '(' || c == '[' || c == '{')
        {
            operators.push(c);
        }
        else if (c == ')' || c == ']' || c == '}')
        {
            char matchingBracket = (c == ')') ? '(' : (c == ']') ? '['
                                                                 : '{';
            while (!operators.empty() && operators.top() != matchingBracket)
            {
                char op = operators.top();
                operators.pop();
                string op2 = operands.top();
                operands.pop();
                string op1 = operands.top();
                operands.pop();
                string expr = op + op1 + op2;
                operands.push(expr);
            }
            operators.pop();
        }
        else if (isOperators(c))
        {
            while (!operators.empty() && precedence(operators.top()) >= precedence(c))
            {
                char op = operators.top();
                operators.pop();
                string op2 = operands.top();
                operands.pop();
                string op1 = operands.top();
                operands.pop();

                string expr = op + op1 + op2;
                operands.push(expr);
            }
            operators.push(c);
        }
    }
    while (!operators.empty())
    {
        char op = operators.top();
        operators.pop();
        string op2 = operands.top();
        operands.pop();
        string op1 = operands.top();
        operands.pop();
        string expr = op + op1 + op2;
        operands.push(expr);
    }
    return operands.top();
}
int evaluatePrefix(string prefix)
{
    stack<int> samia;
    for (int i = prefix.size() - 1; i >= 0; i--)
    {
        char c = prefix[i];
        if (isdigit(c))
        {
            string operand = "";
            while (i >= 0 && isdigit(prefix[i]))
            {
                operand = prefix[i] + operand;
                i--;
            }
            i++;
            samia.push(stoi(operand));
        }
        else if (isOperators(c))
        {
            int op1 = samia.top();
            samia.pop();
            int op2 = samia.top();
            samia.pop();
            switch (c)
            {
            case '+':
                samia.push(op1 + op2);
                break;
            case '-':
                samia.push(op1 - op2);
                break;
            case '*':
                samia.push(op1 * op2);
                break;
            case '/':
                samia.push(op1 / op2);
                break;
            case '^':
                samia.push(pow(op1, op2));
                break;
            }
        }
    }

    return samia.top();
}
int main()
{
    string infix = "(34*2)-[{40/(4-2)}+2]";
    string prefix = infixToPrefix(infix);
    cout << "Prefix Expression: " << prefix << endl;
    int result = evaluatePrefix(prefix);
    cout << "Result: " << result << endl;
    return 0;
}
