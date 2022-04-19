#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
#include <stack>
#include <list>

using namespace std;

template <typename T>
struct Node
{
    T data;
    Node<T> *next;

    Node()
    {
        this->data = NULL;
        this->next = nullptr;
    }

    Node(T value)
    {
        this->data = value;
        this->next = nullptr;
    }

    void killSelf()
    {
        delete this;
    }
};

template <typename T>
class List
{
private:
    Node<T> *head;
    int nodes;

public:
    List()
    {
        head = nullptr;
        nodes = 0;
    }

    virtual ~List()
    {
        delete this;
    }

    void push_front(T data)
    {
        Node<T> *nuevo = new Node<T>(data);
        nuevo->next = head;
        head = nuevo;
        ++nodes;
    }

    T pop_front()
    {
        if (head == nullptr)
            throw("No hay datos");
        Node<T> *temp = head;
        head = head->next;
        T val = temp->data;
        delete temp;
        --nodes;
        return val;
    }

    void display()
    {
        Node<T> *temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    int str2int()
    {
        return 0;
    }
};

struct Result
{
    double result;
    bool error;
};

void removeSpaces(char *s)
{
    *std::remove(s, s + strlen(s), ' ') = 0;
}

Result evaluate(string input)
{
    std::map<char, int> prec = {
            { '*', 3 },
            { '/', 3 },
            { '+', 2 },
            { '-', 2 },
            { '(', 1 }
    };

    Result resultado;
    // 1
    stack<char> *opstack; // Lista para operadores
    list<char> postfixList;
    // 2

    // Creamos una lista para los caracteres
    list<char> tokenList = new list<char>;
    remove(input.begin(), input.end(), ' ');
    for (int i = 0; i < input.size(); i++)
        tokenList.push_front(input[i]);

    // 3
    list<char> tokenList;
    // crear lista de números (operandos)
    list<char> numlist = ['1','2','3','4','5','6','7','8','9','0'];


    for(auto token = tokenList.begin(); token!= tokenList.end(); ++token) {
        // Caso token es operando
        for (auto num = numlist.begin(); num != numlist.end(); ++num)
            if (*num == *token)
                postfixList.pushback(*token);
        // Caso token es (
        if (token == "(")
            opstack.push(*token);
        // Caso token es )
        if (token == ")")
            // Obtener último elemento agregado al stack
            char topToken = opstack.top();
        opstack.pop(); // Elimina el último elemento del stack
        // Mientras el siguiente elemento no sea apertura '(',
        //              Agrega todos los operadores a la lista de salida postfixList
        while (topToken != '(') {
            postfixList.push(topToken);
            topToken = opstack.top;
            opstack.pop();
        }
        else
        while (!opstack.empty() && (prec[opstack.top()] >= prec[token])) {
            postfixList.pushback(opstack.top());
            opstack.pop();
            opstack.push(token);
        }
    }

    while (!opstack.empty()){
        postfixList.pushback(opstack.pop())
    }



    // +
    // 5 8

    // 1- descomponer el input y validar

    // 2- convertir de Infijo a Postfijo

    // 3- resolver la expresion

    //* Si no cumple la validacion retornar Result.error = true;

    return Result();
}
