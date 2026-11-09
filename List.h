#ifndef LIST_H
#define LIST_H

template <typename T>
class List {
public:
    virtual ~List() {}
    virtual void insert(int index, T e) = 0;
    virtual void append(T e) = 0;
    virtual void prepend(T e) = 0;
    virtual T remove(int index) = 0;
    virtual T get(int index) const = 0;
    virtual int search(T e) const = 0;
    virtual bool empty() const = 0;
    virtual int size() const = 0;
};

#endif
