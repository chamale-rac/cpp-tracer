#ifndef lVECTOR_H
#define lVECTOR_H

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

template <class T>
class lVector
{
public:
    lVector();
    lVector(std::vector<T> v);

    ~lVector();

    // Return the parameters of the vector
    int GetNumDims();

    // Handle vector elements
    T GetElement(int index);

    // Vector operations
    lVector<T> operator+(const lVector<T> &rhs) const;
    lVector<T> operator-(const lVector<T> &rhs) const;
    lVector<T> operator*(const T &rhs) const;

    // Friend functions
    template <class U>
    friend lVector<U> operator*(const U &lhs, const lVector<U> &rhs);

    // Static functions
    static T dot(const lVector<T> &a, const lVector<T> &b);
    static lVector<T> cross(const lVector<T> &a, const lVector<T> &b);

private:
    std::vector<T> vectorData;
    int numDims;
};

// Default constructor
template <class T>
lVector<T>::lVector()
{
    numDims = 0;
    vectorData = std::vector<T>();
}
// Constructor with vector data
template <class T>
lVector<T>::lVector(std::vector<T> v)
{
    numDims = v.size();
    vectorData = v;
}
// Destructor
template <class T>
lVector<T>::~lVector()
{
    // Nothing to do here, because vectorData is a vector.
}

// Getters functions
template <class T>
int lVector<T>::GetNumDims()
{
    return numDims;
}
template <class T>
T lVector<T>::GetElement(int index)
{
    return vectorData[index];
}

// Overloaded operators

#endif