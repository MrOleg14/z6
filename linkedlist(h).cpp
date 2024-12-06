#ifndef LLST
#define LLST

#include "includes.h"
#include "Node.h"
#include "List.h"

// такой же, как и List, но с последним и текущим эл-ом
_clstyping
class LinkedList
{
private:
    Node<_T>* head;
    Node<_T>* last;
    Node<_T>* current;
    int size;

public:
    LinkedList(std::initializer_list<_T>);
    LinkedList();
    ~LinkedList();

    bool is_empty();

    Node<_T>* get_begin();
    Node<_T>* get_end();
    Node<_T>* get_current();

    Node<_T>* get_by_pos(int);

    int get_size();

    void insert(_T, int);
    void push_back(_T);

    void remove(int);

    void println();
};

_clstyping
LinkedList<_T>::LinkedList(std::initializer_list<_T> _data)
{
    this->head = new Node<_T>(*(_data.begin()));
    Node<_T>* curr = this->head;
    this->size = 1;
    for (auto iter = _data.begin() + 1;
        iter != _data.end();
        ++iter)
    {
        curr->set_next(new Node<_T>(*iter));
        curr = curr->get_next();
        this->size += 1;
    }
    this->current = curr;
    this->last = curr;
}

_clstyping
bool LinkedList<_T>::is_empty()
{
    if (this->head == nullptr)
        return true;
    return false;
}

_clstyping
LinkedList<_T>::LinkedList()
{
    this->head = nullptr;
    this->current = nullptr;
    this->last = nullptr;
    this->size = 0;
}

_clstyping
LinkedList<_T>::~LinkedList()
{
    if (!this->is_empty())
    {
        Node<_T>* candidat = this->head;
        if (this->size == 1)
        {
            delete candidat;
        }
        else
        {
            Node<_T>* curr = candidat->get_next();
            while (curr != nullptr)
            {
                delete candidat;
                candidat = curr;
                curr = curr->get_next();
            }
            delete candidat;
        }
    }
}

_clstyping
Node<_T>* LinkedList<_T>::get_begin()
{
    return this->head;
}

_clstyping
Node<_T>* LinkedList<_T>::get_end()
{
    return this->last;
}

_clstyping
Node<_T>* LinkedList<_T>::get_current()
{
    return this->current;
}

_clstyping
Node<_T>* LinkedList<_T>::get_by_pos(int _pos)
{
    if (_pos < 0 || _pos >= this->size)
        return nullptr;

    Node<_T>* curr = this->head;
    int curr_pos = 0;
    while (curr_pos < _pos)
    {
        curr = curr->get_next();
        ++curr_pos;
    }
    this->current = curr;
    return curr;
}

_clstyping
int LinkedList<_T>::get_size()
{
    return this->size;
}

_clstyping
void LinkedList<_T>::push_back(_T _data)
{
    Node<_T>* newnode = new Node<_T>(_data);
    if (!this->is_empty())
    {
        Node<_T>* endnode = this->get_end();
        endnode->set_next(newnode);
    }
    else
    {
        this->head = newnode;
    }
    this->last = newnode;
    this->current = newnode;
    this->size += 1;
}

// newnd to pos 2  
// LinkedList: 0->1->2->...
// after: 0->1->newnd->2->...
_clstyping
void LinkedList<_T>::insert(_T _data, int _pos)
{
    Node<_T>* newnode = new Node<_T>(_data);

    if (_pos == 0)
    {
        newnode->set_next(this->head);
        this->head = newnode;
    }
    else
    {
        Node<_T>* curr = this->get_by_pos(_pos - 1);

        newnode->set_next(curr->get_next());
        curr->set_next(newnode);
    }
    this->size += 1;
    this->current = newnode;
}

_clstyping
void LinkedList<_T>::remove(int pos)
{
    if (pos >= 0 && pos <= this->size)
    {
        Node<_T>* candidat = nullptr;
        if (pos == 0)
        {
            candidat = this->head;
            this->head = this->head->get_next();
        }
        else
        {
            Node<_T>* curr = this->get_by_pos(pos - 1);
            candidat = curr->get_next();

            curr->set_next(candidat->get_next());

            if (pos != this->size - 1)
                candidat->get_next()->set_prev(curr);
        }
        this->size -= 1;

        this->current = new Node<_T>(candidat->get_data());
        this->current->set_prev(candidat->get_prev());
        this->current->set_next(candidat->get_next());

        delete candidat;
    }
}

_clstyping
void LinkedList<_T>::println()
{
    Node<_T>* curr = this->head;
    while (curr != nullptr)
    {
        std::cout << curr->get_data() << ' ';
        curr = curr->get_next();
    }
    std::cout << std::endl;
}

#endif
