//
// Created by kaptch on 3/21/18.
//

#ifndef PRIORITY_QUEUE_PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_PRIORITY_QUEUE_H

#include <vector>
#include <functional>

template<typename T, typename Container = std::vector<T>, typename Compare = std::less<typename Container::value_type> >
class priority_queue_f {
    Compare comp = Compare();
    Container cont;
    unsigned int max_size;
public:
    priority_queue_f(unsigned int s) : max_size(s) {}

    ~priority_queue_f() {}

    typename Container::size_type size() { return cont.size(); }

    void add(T x) {
        if (size() == max_size) {
            if (comp(x, cont[size() - 1]))
                return;
            else
                cont.pop_back();
        }
        cont.push_back(x);
        int i = size() - 1;
        int parent = (i - 1) / 2;
        while (i > 0 && comp(cont[parent], cont[i])) {
            T temp = cont[i];
            cont[i] = cont[parent];
            cont[parent] = temp;
            i = parent;
            parent = (i - 1) / 2;
        }
    }

    void heapify(int i) {
        int left;
        int right;
        int largest;
        while (true) {
            left = 2 * i + 1;
            right = 2 * i + 2;
            largest = i;
            if (left < size() && comp(cont[largest], cont[left])) { largest = left; }
            if (right < size() && comp(cont[largest], cont[right])) { largest = right; }
            if (largest == i) { break; }
            T temp = cont[i];
            cont[i] = cont[largest];
            cont[largest] = temp;
            i = largest;
        }
    }

    T max() {
        T res = cont[0];
        cont[0] = cont[size() - 1];
        cont.pop_back();
        heapify(0);
        return res;
    }
};

#endif //PRIORITY_QUEUE_PRIORITY_QUEUE_H
