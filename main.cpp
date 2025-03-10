#include <iostream>
#include <stdexcept>

template <typename T>
class MyVector {
private:
    T* data;
    size_t size;
    size_t capacity;

    // Увеличение размера массива
    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    MyVector() : data(nullptr), size(0), capacity(0) {}

    ~MyVector() {
        delete[] data;
    }

    // Получение размера вектора
    size_t getSize() const {
        return size;
    }

    // Проверка, пустой ли вектор
    bool isEmpty() const {
        return size == 0;
    }

    // Доступ к элементу по индексу
    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Добавление элемента в конец
    void pushBack(const T& value) {
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2); // Увеличиваем размер в 2 раза
        }
        data[size++] = value;
    }

    // Удаление последнего элемента
    void popBack() {
        if (size == 0) {
            throw std::out_of_range("No elements to remove");
        }
        --size;
    }

    // Вставка элемента в середину
    void insert(size_t index, const T& value) {
        if (index > size) {
            throw std::out_of_range("Index out of range");
        }
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        for (size_t i = size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++size;
    }

    // Удаление элемента из середины
    void erase(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
    }

    // Печать элементов вектора
    void print() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    MyVector<int> vec;

    // Добавляем элементы
    vec.pushBack(10);
    vec.pushBack(20);
    vec.pushBack('a');
    vec.pushBack(40);

    std::cout << "Vector after pushBacks: ";
    vec.print();

    // Вставка элемента в середину
    vec.insert(2, 25);
    std::cout << "Vector after inserting 25 at index 2: ";
    vec.print();

    // Удаление элемента из середины
    vec.erase(3);
    std::cout << "Vector after erasing element at index 3: ";
    vec.print();

    // Удаляем последний элемент
    vec.popBack();
    std::cout << "Vector after popBack: ";
    vec.print();

    // Доступ к элементу
    std::cout << "Element at index 1: " << vec[1] << std::endl;

    return 0;
}
