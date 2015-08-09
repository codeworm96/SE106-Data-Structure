/**
 * Homework 2: Using Template
 * Assigned: September 13
 * Due: September 23 24:00
 **/

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <string>
#include <stdexcept>

using namespace std;

template <typename T>
class Vector {
    private:
        // [TODO] Add private variables and methods here
        T * elements;                      //pointer to allocated space
        size_t theSize;                    //actual # of data
        size_t theCapacity;                //total allocated size of space

        //Note: we use new to allocate the space, rather than allocator used in a
        //industry STL implementation.
        //So, here *ALL* allocated space is initialized, while in the industry STL
        //implementation *ONLY USED* space is initialized.
        //it will cause some differences.

        void reserve(size_t newCapacity);   //asked the vector to reserve space for newCapacity elements
                                            //will ignored when newCapacity < theSize
    public:
        // Do NOT modify following interfaces
        Vector();
        Vector(int size, const T& val = T());
        Vector(const Vector& x);
        ~Vector();
        Vector<T>& operator=(const Vector<T>& x);
        int size() const;
        bool empty() const;
        T& operator [](int pos);
        void resize(size_t n, T val = T());
        void push_back(const T& val);

        // Iterator implementation

        class iterator :
            public std::iterator<std::random_access_iterator_tag, T> {

                private:
                    const Vector *vp; //which vector it belongs to
                    int index;        //position

                public:
                    //constructors:
                    iterator() {
                        this->vp = NULL;
                    }
                    //copy constructor
                    iterator(const iterator & it) {
                        this->vp = it.vp;
                        this->index = it.index;
                    }

                    iterator(const Vector *vp, int index) {
                        this->vp = vp;
                        this->index = index;
                    }
                    //++iter;
                    iterator & operator++() {
                        ++index;
                        return *this;
                    }
                    //iter++
                    iterator operator++(int)
                    {
                        iterator tmp(*this);
                        ++index;
                        return tmp;
                    }
                    //--iter
                    iterator & operator--()
                    {
                        --index;
                        return *this;
                    }
                    //iter--
                    iterator operator--(int)
                    {
                        iterator tmp(*this);
                        --index;
                        return tmp;
                    }
                    //compare
                    bool operator==(const iterator & rhs)
                    {
                        return ((vp==rhs.vp)&&(index==rhs.index));
                    }

                    bool operator!=(const iterator & rhs)
                    {
                        return ((vp!=rhs.vp)||(index!=rhs.index));
                    }

                    bool operator<(const iterator & rhs)
                    {
                        if(vp != rhs.vp){
                            throw std::runtime_error("iterators cannot compare");
                        }
                        return (index < rhs.index);
                    }

                    bool operator<=(const iterator & rhs)
                    {
                        if(vp != rhs.vp){
                            throw std::runtime_error("iterators cannot compare");
                        }
                        return (index <= rhs.index);
                    }

                    bool operator>(const iterator & rhs)
                    {
                        if(vp != rhs.vp){
                            throw std::runtime_error("iterators cannot compare");
                        }
                        return (index > rhs.index);
                    }

                    bool operator>=(const iterator & rhs)
                    {
                        if(vp != rhs.vp){
                            throw std::runtime_error("iterators cannot compare");
                        }
                        return (index >= rhs.index);
                    }
                    //iterator arithmetic
                    iterator operator+(const int & rhs)
                    {
                        return iterator(vp, index + rhs);
                    }

                    iterator operator-(const int & rhs)
                    {
                        return iterator(vp, index - rhs);
                    }

                    int operator-(const iterator & rhs)
                    {
                        if(vp != rhs.vp){
                            throw std::runtime_error("these iterators cannot substract");
                        }
                        return (index - rhs.index);
                    }

                    T & operator*() {
                        return vp->elements[index];
                    }
                    //this function likes pointer
                    //p[n] (p is a pointer)
                    T & operator[](int k)
                    {
                        return vp->elements[index + k];
                    }

            };

        iterator begin() const
        {
            return iterator(this, 0);
        }

        iterator end() const
        {
            return iterator(this, theSize);
        }

};

// (default constructor)
// Constructs an empty container, with no elements.
template <typename T>
Vector<T>::Vector() :theSize(0), theCapacity(0), elements(0)
{	
}

// (fill constructor)
// Constructs a container with n elements.
// Each element is a copy of val.
template <typename T>
Vector<T>::Vector(int size, const T& val) :theSize(size), theCapacity(size)
{
    elements = new T[size];
    for (int i = 0; i < size; ++i){
        elements[i] = val;
    }
}

// (copy constructor)
// Constructs a container with a copy of each of the
// elements in x, in the same order.
template <typename T>
Vector<T>::Vector(const Vector& x) :theSize(x.theSize), theCapacity(x.theSize)
{
    elements = new T[theCapacity];      //allocate space
    for (int i = 0; i < theSize; ++i){  //copy elements
        elements[i] = x.elements[i];
    }
}

// (destructor)
// Destroys the container object.
template <typename T>
Vector<T>::~Vector()
{
    if(elements){
        delete [] elements;
    }
}

// operator=
// Assigns new contents to the container, replacing its
// current contents, and modifying its size accordingly.
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& x)
{
    if (theCapacity < x.theSize){ //note: excluding self-assignment, so it is safe
        //ensure enough space
        T * newElements = new T[x.theSize];
        delete [] elements;
        elements = newElements;
        theCapacity = x.theSize;
    }

    theSize = x.theSize;
    for (int i = 0; i < theSize; ++i){
        elements[i] = x.elements[i];
    }

    return *this;
}

// size
// Returns the number of elements in the vector.
// This is the number of actual objects held in the
// vector, which is not necessarily equal to its
// storage capacity.
template <typename T>
int Vector<T>::size() const
{
    return theSize;
}

// empty
// Returns whether the vector is empty
template <typename T>
bool Vector<T>::empty() const
{
    return (theSize == 0);
}

// operator[]
// Returns a reference to the element at position n
// in the vector container.
// if the requested position is out of range, the
// behavior is undefined
template <typename T>
T& Vector<T>::operator[](int pos)
{
    return elements[pos];   //note: when pos out of range, the behavior is undefined
                            //to consist with the STL (and for performance), there is no range check
}

// resize
// Resizes the container so that it contains n elements.
// If n is smaller than the current container size, the 
// content is reduced to its first n elements, removing 
// those beyond (and destroying them).
// If n is greater than the current container size, the 
// content is expanded by inserting at the end as many 
// elements as needed to reach a size of n. If val is 
// specified, the new elements are initialized as copies 
// of val, otherwise, they are value-initialized.
//
// Note:if n < size, we must re-allocate the space to destroy those beyond.
// because we use new, so *ALL* reserved space must be initialized.(invariant)
// it maybe slow, but the specification requires it.
template <typename T>
void Vector<T>::resize(size_t n, T val)
{
    if(n < theSize){
        T * newElements = new T[n];
        for (int i = 0; i < n; ++i){
            newElements[i] = elements[i];
        }
        delete [] elements; //here those beyond is destroyed.
        elements = newElements;
        theSize = n;
        theCapacity = n;
    }else{ // n >= theSize
        if (n > theCapacity){ //expand when needed
            reserve(n);
        }
        //insert val
        for (int i = theSize; i < n; ++i){
            elements[i] = val;
        }
        theSize = n;
    }
}

// push_back
// Adds a new element at the end of the vector, after its
// current last element. The content of val is copied (or
// moved) to the new element.
template <typename T>
void Vector<T>::push_back(const T& val)
{
    if (theSize == theCapacity){
        reserve(2 * theCapacity + 1); //allocate more space
    }
    elements[theSize] = val;
    ++theSize;
}

template <typename T>
void Vector<T>::reserve(size_t newCapacity)
{
    if (newCapacity < theSize){  //the case to ignore
        return;
    }

    T * newElements = new T[newCapacity];
    //copy old elements
    for (int i = 0; i < theSize; ++i){
        newElements[i] = elements[i];
    }
    //dispose old space
    delete [] elements;
    //update
    elements = newElements;
    theCapacity = newCapacity;
}

#endif

