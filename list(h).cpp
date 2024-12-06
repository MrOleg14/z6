#ifndef LST
#define LST

#include "includes.h" 
#include "Node.h"

// работа со след эл-ом
_clstyping
class List
{
private:
    Node<_T>* head;  // указатель на голову
    int size;  // размер списка, кол-во эл

public:
    List(std::initializer_list<_T>);  // конструктор
    ~List();

    Node<_T>* get_begin();
    Node<_T>* get_end();
    Node<_T>* get_by_pos(int);

    int get_size();

    void insert(_T, int);
    void push_back(_T);

    void remove(int);

    void println();
};

// заполняем List эл-ами data
_clstyping

List<_T>::List(std::initializer_list<_T> _data)
{
    this->head = new Node<_T>(*(_data.begin()));
    Node<_T>* current = this->head;
    this->size = 1;
    for (auto iter = _data.begin() + 1;
        iter != _data.end();
        ++iter)
    {
        current->set_next(new Node<_T>(*iter));
        current = current->get_next();
        this->size += 1;
    }
}

// чистим память
_clstyping
List<_T>::~List()
{
    Node<_T>* candidat = this->head;
    if (this->size == 1)
    {
        delete candidat;
    }
    else
    {
        Node<_T>* current = candidat->get_next();
        while (current != nullptr)
        {
            delete candidat;
            candidat = current;
            current = current->get_next();
        }
        delete candidat;
    }
}

// получаем начало списка
_clstyping
Node<_T>* List<_T>::get_begin()
{
    return this->head;
}

// получаем конец списка
_clstyping
Node<_T>* List<_T>::get_end()
{
    Node<_T>* current = this->head;
    while (current->get_next() != nullptr)
        current = current->get_next();
    return current;
}

// получаем узел на позиции 
_clstyping
Node<_T>* List<_T>::get_by_pos(int _pos)
{
    if (_pos < 0 || _pos >= this->size)
        return nullptr;

    Node<_T>* current = this->head;
    int curr_pos = 0;
    while (curr_pos < _pos)
    {
        current = current->get_next();
        ++curr_pos;
    }
    return current;
}

// узнаем размер
_clstyping
int List<_T>::get_size()
{
    return this->size;
}

// вставляем новый узел в конец списка
_clstyping
void List<_T>::push_back(_T _data)
{
    Node<_T>* newnode = new Node<_T>(_data);

    Node<_T>* endnode = this->get_end();
    endnode->set_next(newnode);
}

// пример newnd to pos 2  
// list: 0->1->2->...
// after: 0->1->newnd->2->...

_clstyping
// вставляем элемент новый на позицию _pos
void List<_T>::insert(_T _data, int _pos)
{
    Node<_T>* newnode = new Node<_T>(_data); // создаем новый объект

    if (_pos == 0)
    {   
        // указываем голову списка след элементом
        newnode->set_next(this->head);
        this->head = newnode;
    }
    else
    {
        Node<_T>* current = this->get_by_pos(_pos - 1);  // текущ эл-нт это предыдущий от текущ позиции 

        newnode->set_next(current->get_next());  // делаем перепривязку
        current->set_next(newnode);  // вставляем эл-нт
    }
    this->size += 1;
}

// удаляем узел на позиции _pos
_clstyping
void List<_T>::remove(int pos)
{
    Node<_T>* candidat = nullptr;
    if (pos == 0)
    {
        candidat = this->head;
        this->head = this->head->get_next();
    }
    else
    {
        Node<_T>* current = this->get_by_pos(pos - 1);
        candidat = current->get_next();
        current->set_next(candidat->get_next());
    }
    this->size -= 1;

    delete candidat;
}

// выводим список
_clstyping
void List<_T>::println()
{
    Node<_T>* current = this->head;
    while (current != nullptr)
    {
        std::cout << current->get_data() << ' ';
        current = current->get_next();
    }
    std::cout << std::endl;
}

#endif
