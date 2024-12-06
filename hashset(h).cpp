#ifndef HSET
#define HSET

#include "LinkedList.h"

_clstyping  // список с уникальными значениями 
class HashSet {
private:
    LinkedList<_T>* llst;
public:
    HashSet(std::initializer_list<_T>);
    HashSet();
    ~HashSet();

    bool is_empty();  // проверяем, пусто ли множество

    // возвращаem указатели на первый и последний узлы связного списка
    Node<_T>* get_begin();
    Node<_T>* get_end();

    bool append(_T);  // добавляем
    void remove(_T);  // удаляем 

    LinkedList<_T>* get_keys();  // возвращаеm указатель на список
    _T get_elem(_T);

    HashSet<_T>* union_with(HashSet<_T>*);
    void except(HashSet<_T>*);
    HashSet<_T>* intersect(HashSet<_T>*);
    bool contains(_T);

    void println();
};

_clstyping  // проверяем, если вставляемый эл-нт на уникальность 
bool is_repeat(Node<_T>_begin, Node<_T> _end, _T _elem)
{
    for (  // итерируем по узлам
        auto iter = _begin;
        iter != _end;
        ++iter
        )
    {
        if (iter->get_data() == _elem) return true;  // проверяем
    }
    return false;
}

_clstyping  // удаляем эл-нт
void remove(LinkedList<_T>& llst, int _pos)  // делаем ссылку на объект во избежание копирования списка
{
    if (_pos >= 0 && _pos < llst->size())  // проверяем позицию на положительность
        llst->remove(_pos);
}

_clstyping  // создаем новый список
HashSet<_T>::HashSet()  
{
    this->llst = new LinkedList<_T>();  // указываем на текущий объект 
}

_clstyping  // создаем список с эл-ами initializer_list
HashSet<_T>::HashSet(std::initializer_list<_T> _init)  // принимаем инициализирующий список
{
    this->llst = new LinkedList<_T>();

    for (  // проходим по эл-ам списка
        auto iter = _init.begin();
        iter != _init.end();
        ++iter
        )
    {
        if (!is_repeat(_init.begin(), _init.end(), *iter))  // проверяем, является ли текущ эл-нт повторяющимся
            this->llst->push_back(*iter);
    }
}

_clstyping  // проверяем на существование списка
bool HashSet<_T>::is_empty()
{
    return this->llst->is_empty();  // возвращаем результат 
}

_clstyping  // чистим список
HashSet<_T>::~HashSet()
{
    delete this->llst;
}

_clstyping  // получаем начало списка
Node<_T>* HashSet<_T>::get_begin()
{
    return this->llst->get_begin();
}

_clstyping  // получаем конец
Node<_T>* HashSet<_T>::get_end()
{
    return this->llst->get_end();
}

_clstyping  // добавляем нвый эл-нт
bool HashSet<_T>::append(_T _elem)
{
    if (!this->contains(_elem))
    {
        this->llst->push_back(_elem);
        return true;
    }
    return false;
}

_clstyping  // удаляем эл-нт
void HashSet<_T>::remove(_T _elem)
{
    int pos = 0;
    bool is_find = false;
    for (auto iter = this->get_begin();  // итерируем эл-ты набора
        iter != this->get_end() && !is_find; ++iter
        )
    {
        if (*iter.get_data() == _elem) is_find = true;  // проверка текущего эл-та
        ++pos;
    }
    remove<_T>(this->llst, --pos);
}

_clstyping  // получаем укказатель на список
LinkedList<_T>* HashSet<_T>::get_keys()
{
    return this->llst;
}

_clstyping  // объединение двух списков 
HashSet<_T>* HashSet<_T>::union_with(HashSet<_T>* _h_set) // принимаем указатель и возвращаем на новый объект
{
    LinkedList<_T>* tmp_lst = new LinkedList<_T>();  // создаем временный список
    for (
        auto iter = _h_set->get_begin();
        iter != _h_set->get_end();
        iter = iter->get_next()
        )
    {
        if (!is_repeat(this->get_begin(),
            this->get_end(), *iter)
            )
            this->tmp_lst->push_back(*iter);
    }
    HashSet<_T>* tmp_set = new HashSet<_T>(  // после завершения создаем новый объект и инициализируем 
        tmp_lst->get_begin(), tmp_lst->end()
    );
    delete tmp_lst;

    return tmp_set;
}

_clstyping  // удаляем из текущ списка эл-нт из HashSet
void HashSet<_T>::except(HashSet<_T>* _h_set)
{
    int pos = 0;
    for (  // итерируем по эл-ам
        auto iter = _h_set->get_begin();
        iter != _h_set->get_end();
        )
    {
        if (is_repeat(this->get_begin(), this->get_end(), *iter))
        {
            iter = iter->get_next(); // следующий шаг перед удалением
            this->llst->remove(pos); // метод remove удалил итератор
        }
        else
        {
            iter = iter->get_next();
            ++pos;
        }
    }
}

_clstyping  // получаем новый список из совпадающих эл-ов
HashSet<_T>* HashSet<_T>::intersect(HashSet<_T>* _h_set)
{
    LinkedList<_T>* tmp_lst = new LinkedList<_T>();  // создаем временный список
    for (  // цикл для итерации по эл-ам
        auto iter = _h_set->get_begin();
        iter != _h_set->get_end();
        iter = iter->get_next()
        )
    {
        if (is_repeat(this->get_begin(),  // проверка на присутствие в множестве
            this->get_end(), *iter)
            )
            this->tmp_lst->push_back(*iter);
    }
    HashSet<_T>* tmp_set = new HashSet<_T>(  // создаем новый объект для инициализации эл-ов из временного списка
        tmp_lst->get_begin(), tmp_lst->end()
    );
    delete tmp_lst;

    return tmp_set;
}

_clstyping  // проверка на существование эл-та в списке
bool HashSet<_T>::contains(_T _elem)  // принимаем эл-ты и возвращаем логическое значение
{
    Node<_T>* curr = this->get_begin();  // указатель на первый узел
    while (curr != nullptr)
    {
        if (curr->get_data() == _elem) return true;  // проверка на равенство искомого эл-та
        curr = curr->get_next();
    }

    return false;
}

_clstyping  // вывод
void HashSet<_T>::println()
{
    this->llst->println();
}

#endif
