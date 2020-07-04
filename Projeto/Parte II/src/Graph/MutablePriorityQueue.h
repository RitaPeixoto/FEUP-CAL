#ifndef SRC_MUTABLEPRIORITYQUEUE_H_
#define SRC_MUTABLEPRIORITYQUEUE_H_

#include <vector>


using namespace std;

/**
 * class T must have: (i) accessible field int queueIndex; (ii) operator< defined.
 */

template <class T>
class MutablePriorityQueue {
    bool inv = false;
    vector<T *> H;
    void heapifyUp(unsigned i);
    void heapifyDown(unsigned i);
    inline void set(unsigned i, T * x);
public:
    MutablePriorityQueue(bool inv = false);
    void insert(T * x);
    T * extractMin();
    void decreaseKey(T * x);
    bool empty();
};

// Index calculations
#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)

template <class T>
MutablePriorityQueue<T>::MutablePriorityQueue(bool inv): inv(inv) {
    H.push_back(nullptr);
    // indices will be used starting in 1
    // to facilitate parent/child calculations
}

template <class T>
bool MutablePriorityQueue<T>::empty() {
    return H.size() == 1;
}

template <class T>
T* MutablePriorityQueue<T>::extractMin() {
    auto x = H[1];
    H[1] = H.back();
    H.pop_back();
    heapifyDown(1);
    (inv)? x->queueIndexInv = 0 : x->queueIndex = 0;
    return x;
}

template <class T>
void MutablePriorityQueue<T>::insert(T *x) {
    H.push_back(x);
    heapifyUp(H.size()-1);
}

template <class T>
void MutablePriorityQueue<T>::decreaseKey(T *x) {
    heapifyUp((inv)? x->queueIndexInv : x->queueIndex);
}

template <class T>
void MutablePriorityQueue<T>::heapifyUp(unsigned i) {
    auto x = H[i];
    while (i > 1 && (*x).compare(*H[parent(i)],inv)) {
        set(i, H[parent(i)]);
        i = parent(i);
    }
    set(i, x);
}

template <class T>
void MutablePriorityQueue<T>::heapifyDown(unsigned i) {
    auto x = H[i];
    while (true) {
        unsigned k = leftChild(i);
        if (k >= H.size())
            break;
        if (k+1 < H.size() && (*H[k+1]).compare(*H[k], inv))
            ++k; // right child of i
        if ( ! ((*H[k]).compare(*x, inv)) )
            break;
        set(i, H[k]);
        i = k;
    }
    set(i, x);
}

template <class T>
void MutablePriorityQueue<T>::set(unsigned i, T * x) {
    H[i] = x;
    (inv)? (x->queueIndexInv = i) : (x->queueIndex = i);
}

#endif /* SRC_MUTABLEPRIORITYQUEUE_H_ */