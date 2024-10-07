#include <iostream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>

typedef int Rank;          // 秩
#define DEFAULT_CAPACITY 3 // 默认的初始容量

template<typename T>
class Vector
{
protected:
    Rank _size;
    int _capacity;
    T* _elem;

    void copyFrom(T const* A, Rank lo, Rank hi)
    {
        _elem = new T[_capacity = 2 * (hi - lo)];
        _size = 0;
        while (lo < hi)
        {
            _elem[_size++] = A[lo++];
        }
    }

    void expand()
    {
        if (_size < _capacity) return;
        T* oldElem = _elem;
        _elem = new T[_capacity *= 2];
        for (int i = 0; i < _size; i++)
        {
            _elem[i] = oldElem[i];
        }
        delete[] oldElem;
    }

public:
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
    {
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v)
            ;
    }

    ~Vector()
    {
        delete[] _elem;
    }

    Rank size() const
    {
        return _size;
    }
    bool empty() const
    {
        return !_size;
    }

    T& operator[](Rank r) const
    {
        return _elem[r];
    }

    Rank insert(Rank r, T const& e)
    {
        expand();
        for (Rank i = _size; i > r; i--)
        {
            _elem[i] = _elem[i - 1];
        }
        _elem[r] = e;
        return ++_size;
    }

    T remove(Rank r)
    {
        T e = _elem[r];
        for (Rank i = r + 1; i < _size; i++)
        {
            _elem[i - 1] = _elem[i];
        }
        --_size;
        return e;
    }

    void bubbleSort(Rank lo, Rank hi)
    {
        for (Rank i = hi - 1; i > lo; i--)
        {
            for (Rank j = lo; j < i; j++)
            {
                if (_elem[j] > _elem[j + 1])
                {
                    std::swap(_elem[j], _elem[j + 1]);
                }
            }
        }
    }

    void sort(Rank lo, Rank hi)
    {
        bubbleSort(lo, hi);
    }

    void traverse(void (*visit)(T&))
    {
        for (Rank i = 0; i < _size; i++)
        {
            visit(_elem[i]);
        }
    }
};
