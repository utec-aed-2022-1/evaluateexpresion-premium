#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
#include <stack>
#include <list>

using namespace std;

struct Result
{
    double result;
    bool error;
};

float doMath(char op, int op1, int op2)
{
    switch (op) 
    {
        case '+':
            return (float)op1 + (float)op2;
        case '-':
            return (float)op1 - (float)op2;
        case '*':
            return (float)op1 * (float)op2;
        case '/':
            return (float)op1 / (float)op2;
    }
}

Result evaluate(string input)
{
    std::map<char, int> prec = {
            { '*', 2 },
            { '/', 2 },
            { '+', 1 },
            { '-', 1 }
    };

    Result resultado;
    // 1
    stack<char> *opstack = new stack<char>; // pila para operadores
    list<char> postfixList; // lista para el orden postfijo
    // 2

    // Creamos una lista para los caracteres
    list<char> *tokenList = new list<char>;
    // remove(input.begin(), input.end(), ' ');
    for (int i = 0; i < input.size(); i++)
        tokenList->push_back(input[i]);

    // crear lista de números (operandos)
    list<char> *numlist = new list<char>;
    numlist->push_front('0');
    numlist->push_front('1');
    numlist->push_front('2');
    numlist->push_front('3');
    numlist->push_front('4');
    numlist->push_front('5');
    numlist->push_front('6');
    numlist->push_front('7');
    numlist->push_front('8');
    numlist->push_front('9');

    // FOR que recorre el input para ser analizado
    for(auto token = tokenList->begin(); token!= tokenList->end(); ++token) {
        // Caso token es operando
        for (auto num = numlist->begin(); num != numlist->end(); ++num)
            if (*num == *token)
                postfixList.push_back(*token);
        // Caso token es (
        if (*token == '(')
            opstack->push(*token);
        // Caso token es )
        if (*token == ')')
        {
            // Obtener último elemento agregado al stack
            char topToken = opstack->top();
            opstack->pop(); // Elimina el último elemento del stack
            // Mientras el siguiente elemento no sea apertura '(',
            // Agrega todos los operadores a la lista de salida postfixList
            while (topToken != '(')
            {
                postfixList.push_back(topToken);
                topToken = opstack->top();
                opstack->pop();
            }
        }
        // Caso sea operador
        if (prec.count(*token))
        {
            while (!(opstack->empty()) && (prec.find(opstack->top())->second >= prec.find(*token)->second))
            {
                postfixList.push_back(opstack->top());
                opstack->pop();
            }
            opstack->push(*token);
        }
    }

    while (!opstack->empty()){
        char temp = opstack->top();
        opstack->pop();
        postfixList.push_back(temp);
    }

    stack<float> *restack = new stack<float>;
    float result = 0.0;

    while (!postfixList.empty())
    {
        // Si hay error
        if (postfixList.front() == '(')
        {
            resultado.error = true;
            return resultado;
        }
        // Si es operando
        if (!prec.count(postfixList.front()))
        {
            restack->push((float)postfixList.front() - '0');
        }
        // si es operador
        else
        {
            if (restack->empty())
            {
                resultado.error = true;
                return resultado;
            }
            float operand2 = restack->top();
            restack->pop();
            if (restack->empty())
            {
                resultado.error = true;
                return resultado;
            }
            float operand1 = restack->top();
            restack->pop();

            result = doMath(postfixList.front(), operand1, operand2);
            restack->push(result);
        }
        postfixList.pop_front();
    }

    resultado.result = result;
    return resultado;
}
