#include <iostream>
#include <iterator>
#include <initializer_list>
#include <cassert>
#include <vector>


using namespace std;

struct Elem
{
    int dataa; 
    Elem* next, * prev;
};

class List
{
private:
    Elem* first, * last;
    int quantity;
    int* m_data;
    vector<int> dataa;

public:

    class Iterator;

    List()
    {
        first = 0;
        last = 0;
        quantity = 0;
    }

    List(const List& L)
    {
        first = 0;
        last = 0;
        quantity = 0;
        Elem* tem = L.first;
        while (tem != 0)
        {
            Pop_back(tem->dataa);
            tem = tem->next;
        }
    }

    Iterator begin()
    {
        return Iterator(dataa.data());
    }

    Iterator end()
    {
        return Iterator(dataa.data() + dataa.size());
    }

    int Size()
    {
        return quantity;
    }

    bool Empty()
    {
        if (quantity != 0)
            return true;
        else
            return false;
    }

    void Delete(int pos)
    {
        int i = 1;
        Elem* Del = first;
        while (i < pos)
        {
            Del = Del->next;
            i++;
        }
        Elem* PrevDel = Del->prev;
        Elem* AfterDel = Del->next;
        if (pos == 1)
            first = AfterDel;
        if (pos == quantity)
            last = PrevDel;
        delete Del;
        quantity--;
    }

    void Pop_back(int pos)
    {
        Delete(quantity);
    }

    void Pop_front(int pos)
    {
        Delete(1);
    }

    void Push_back(int n)
    {
        Elem* temp = new Elem;
        temp->next = 0;
        temp->dataa = n;
        temp->prev = last;
        if (last != 0)
            last->next = temp;
        if (quantity == 0)
            first = last = temp;
        else
            last = temp;
        quantity++;
    }

    void Push_front(int n)
    {
        Elem* temp = new Elem;
        temp->prev = 0;
        temp->dataa = n;
        temp->next = first;
        if (first != 0)
            first->prev = temp;
        if (quantity == 0)
            first = last = temp;
        else
            first = temp;
        quantity++;
    }

    List& operator= (const std::initializer_list<int>& list)
    {
        delete[] m_data;
        if (list.size() == 0)
        {
            quantity = 0;
            m_data = nullptr;
            return *this;
        }
        quantity = list.size();
        m_data = new int[list.size()];
        for (int x = 0; x < list.size(); x += 1)
        {
            m_data[x] = list.begin()[x];
        }
        return *this;
    }

    ~List()
    {
        while (quantity > 0)
            Delete(1);
    }
};

class List::Iterator : std::iterator<std::bidirectional_iterator_tag, int>
{
private:
    int* obj;
public:
    Iterator() : obj(0) {}

    int* operator->() 
    {
        return obj;
    }

    Iterator& operator++() 
    {
        obj++;
        return *this;
    }

    Iterator& operator--() 
    {
        obj;
        return *this;
    }

    int& operator*() 
    {
        return *obj;
    }

    int operator*() const {
        return *obj;
    }

    bool operator==(const Iterator& rhs) const 
    {
        return obj == rhs.obj;
    }

    bool operator!=(const Iterator& rhs) const 
    {
        return obj!= rhs.obj;
    }

};
