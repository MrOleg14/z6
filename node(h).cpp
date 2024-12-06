#ifndef NODE
#define NODE

#include "includes.h"

_clstyping  // объявление шаблона
class Node
{
private:
    _T data;
    Node<_T>* next;
    Node<_T>* prev;

public:
    Node(_T);
    ~Node();

    Node* get_next();
    _T get_data();

    void set_next(Node*);  // установить значение
    void set_prev(Node*);

    Node* get_prev();  // взять знач
    void set_data(_T);
};

_clstyping
Node<_T>::Node(_T _data)
{
    // этому классу присвоить это значение
    this->data = _data;
    this->next = nullptr;  // nullptr пустой указатель
    this->prev = nullptr;
}

_clstyping
Node<_T>::~Node()  // деструктор вызывается, когда объект выходит из области видимости
{}

_clstyping
Node<_T>* Node<_T>::get_next()  // обращение к next
{
    return this->next;
}

_clstyping
Node<_T>* Node<_T>::get_prev()
{
    return this->prev;
}

_clstyping
_T Node<_T>::get_data()
{
    return this->data;
}

_clstyping
void Node<_T>::set_next(Node<_T>* _next)  // установить 
{
    this->next = _next;
}

_clstyping
void Node<_T>::set_prev(Node<_T>* _prev)
{
    this->prev = _prev;
}

#endif
