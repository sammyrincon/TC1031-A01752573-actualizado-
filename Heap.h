#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <stdexcept>

template <class T>
class Heap {
private:
    std::vector<T> data;

    void heapifyUp(int i) {
        while (i > 0 && data[i] > data[(i - 1) / 2]) {
            std::swap(data[i], data[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void heapifyDown(int i) {
        int size = data.size();
        while (2 * i + 1 < size) {
            int maxChild = 2 * i + 1;
            if (2 * i + 2 < size && data[2 * i + 2] > data[maxChild]) {
                maxChild = 2 * i + 2;
            }
            if (data[i] >= data[maxChild]) break;
            std::swap(data[i], data[maxChild]);
            i = maxChild;
        }
    }

public:
    void push(T val) {
        data.push_back(val);
        heapifyUp(data.size() - 1);
    }

    void pop() {
        if (data.empty()) throw std::runtime_error("Heap vacío");
        data[0] = data.back();
        data.pop_back();
        heapifyDown(0);
    }

    T top() {
        if (data.empty()) throw std::runtime_error("Heap vacío");
        return data[0];
    }

    bool empty() {
        return data.empty();
    }
};

#endif
