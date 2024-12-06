#include "List.h"
#include "LinkedList.h"
#include "HashSet.h"

// 1 задание
// поиск дубликатов в списке
template <typename _T>
bool find_dublicates(List<_T>& lst)  // принимает ссылку на объект
{
    int count = 0;
    _T elem;
    for (int pos = 0; pos < lst.get_size(); ++pos)
    {
        elem = lst.get_by_pos(pos)->get_data();  // возвращает узел по заданной позиции
        for (Node<_T>* node = lst.get_by_pos(pos + 1);
            node != nullptr; node = node->get_next()
            )
        {
            if (node->get_data() == elem) return true; 
        }
    }
    return false;
}

// 2 задание
// удаление первого эл-та из связанного списка
template<typename _T>
void delete_first_step(LinkedList<_T>& llst, _T elem)
{
    bool flag = true;
    for (int pos = 0; pos < llst.get_size() && flag; ++pos)
    {
        if (llst.get_by_pos(pos)->get_data() == elem)  // проверка внутри цикла
        {
            llst.remove(pos);  // если эл-нт найден, то вызывае метод для удаления эл-та по текущ pos
            flag = false;
        }
    }
}

// 3 задание
void music()
{
    int meolomans = 500000;  
    // создаем вектор, который содержит пары значений
    std::vector<std::pair<int, const char*>> mus_chart(
        {
            {0, "Garage Pivo"},
            {0, "HardMegaPop"},
            {1, "10-hours VK-trends"},
            {123000, "Pop Music 1"},
            {11300, "Rock special edit"},
            {123000, "Pop Music 2"},
            {meolomans, "Sergey Trofimov. Dalnoboynya"}
        }
    );

    // выводим название треков и прослушиваний
    std::cout << "Track name : Number auditions\n";
    for (const auto& data : mus_chart)
    {
        std::cout << data.second << " : " << data.first << std::endl;
    }
    std::cout << std::endl;

    HashSet<int> unique_audit;  // создается объект для хранения значений
    for (  // перебор эл-ов вектора
        auto iter = mus_chart.begin();
        iter != mus_chart.end(); ++iter)
    {
        unique_audit.append(iter->first);
    }

    std::cout << "Number all melomans: " << meolomans << std::endl;
    Node<int>* curr = unique_audit.get_begin();
    while (curr != nullptr)
    {
        std::cout << "  Number melomans: " << curr->get_data() << std::endl;
        for (const auto& iter : mus_chart)
        {
            if (iter.first == curr->get_data())
                std::cout << "      Track name: "
                << iter.second << std::endl;
        }
        curr = curr->get_next();
    }
}

// общий вывод
int main()
{
    using namespace std;

    List<int> lst({ 0, 1, 2, 3, 4, 5, 5, 10, 0 });
    List<int> lst1({ -1, 2, 3, 100 });

    cout << "1.6:\n";
    cout << "  List1: "; lst.println();
    cout << "       Have dublicates?: " << find_dublicates(lst) << endl;
    cout << "  List2: "; lst1.println();
    cout << "       Have dublicates?: " << find_dublicates(lst1) << endl;
    cout << endl << endl;


    LinkedList<int> llst({ 0, 1, 2, 3, 4, 2, 5, 5, 10, 0 });
    cout << "2.6:\n";
    cout << "  List1: "; llst.println();
    cout << "       List1 removed 2: ";
    delete_first_step(llst, 2);
    llst.println();

    cout << "       List1 removed 11000: ";
    delete_first_step(llst, 11000);
    llst.println();

    cout << endl;
    cout << endl;

    cout << "3.6:\n";
    music();


    return 0;
}
