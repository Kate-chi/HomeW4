

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iterator>
#include <list>

using namespace std;

template<template<typename, typename> class TContainer, typename TItem, typename TIterator>
void print(const TContainer<TItem, TIterator>& c)
{
    copy (c.begin(), c.end(), ostream_iterator<TItem> {cout, " "} );
    std::cout << std::endl;
}

template<template<typename, typename> class TContainer, typename TItem, typename TIterator>
void insert_sorted(TContainer<TItem, TIterator>& c, const TItem& i)
{
    typename TContainer<TItem, TIterator>::iterator it = find_if(c.begin(), c.end(), [&](const TItem& current)
        {
            return current >= i;
        });
    c.insert(it, i);
}

//==================================

template<template<typename, typename> class TContainer, typename TItem, typename TIterator, typename T>
void generator(TContainer<TItem, TIterator>& c, const T& rangeStart, const T& rangeEnd)
{
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_real_distribution<double> urd(rangeStart, rangeEnd);
    generate(c.begin(), c.end(), [&](){return urd(mersenne);});
}

int main()
{
    std::vector<int> v{ 2, 6, 7, 3, 5, 9 };
    sort(v.begin(), v.end());
    print(v);
    insert_sorted(v, 7);
    print(v);

    std::list<double> l{ 1, 7, 8, 5, 9 };
    l.sort();
    print(l);                             
    insert_sorted(l, 6.3);
    print(l);

    std::cout << std::endl;

    //================================================

    vector<double> a(100);

    double error = 0;
    generator(a, 0.0, 100.0);
    

    print(a);
    std::cout << std::endl;
    copy(a.begin(), a.end(), ostream_iterator<int> { cout, " " });     

    std::cout << std::endl;

    for_each(a.begin(), a.end(), [&](const double& i)
        {
            error += pow(i - static_cast<int>(i), 2);
        });

    std::cout << std::endl;
    std::cout << error << std::endl;

}
