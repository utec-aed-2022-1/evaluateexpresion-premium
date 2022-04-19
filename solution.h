#include <iostream>
#include <algorithm>
#include <cstring>

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

Result evaluate(string input)
{
    Result resultado;
    List<char> *char_list = new List<char>; // Creamos una lista para los caracteres
    int *array = new int;
    int c = 0;

    char *ptr;
    ptr = strtok(, ' ');

    for (int i = 0; i < input.size(); i++) // Mapeamos todo el string
    {
        if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') // Guardamos operadores en la lista
            char_list->push_front(input[i]);
        else if ((int)input[i] > 0) // Guardamos los números en un array
            array[c++] = input[i];
    }

    // +
    // 5 8

    // 1- descomponer el input y validar

    // 2- convertir de Infijo a Postfijo

    // 3- resolver la expresion

    //* Si no cumple la validacion retornar Result.error = true;

    return Result();
}
