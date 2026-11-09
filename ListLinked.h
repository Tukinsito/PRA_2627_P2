#ifndef LIST_LINKED_H
#define LIST_LINKED_H

#include <ostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {

    private:
        Node<T>* first; // Puntero al primer nodo
        int n;          // Número de elementos en la lista

    public:
        // Constructor sin argumentos
        ListLinked() : first(nullptr), n(0) {}

        // Destructor para liberar la memoria dinámica de todos los nodos
        ~ListLinked() {
            Node<T>* current = first;
            while (current != nullptr) {
                Node<T>* nextNode = current->next;
                delete current;
                current = nextNode;
            }
        }

        // Inserta el elemento e en la posición pos
        void insert(int pos, T e) override {
            if (pos < 0 || pos > n) {
                throw std::out_of_range("Posición fuera de rango");
            }
            if (pos == 0) {
                first = new Node<T>(e, first);
            } else {
                Node<T>* prev = first;
                for (int i = 0; i < pos - 1; ++i) {
                    prev = prev->next;
                }
                prev->next = new Node<T>(e, prev->next);
            }
            n++;
        }

        // Inserta el elemento e al final de la lista
        void append(T e) override {
            insert(n, e);
        }

        // Inserta el elemento e al principio de la lista
        void prepend(T e) override {
            insert(0, e);
        }

        // Elimina y devuelve el elemento en la posición pos
        T remove(int pos) override {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posición fuera de rango");
            }
            Node<T>* toDelete;
            T data;

            if (pos == 0) {
                toDelete = first;
                first = first->next;
            } else {
                Node<T>* prev = first;
                for (int i = 0; i < pos - 1; ++i) {
                    prev = prev->next;
                }
                toDelete = prev->next;
                prev->next = toDelete->next;
            }

            data = toDelete->data;
            delete toDelete;
            n--;
            return data;
        }

        // Devuelve el elemento en la posición pos
        T get(int pos) const override {
            return (*this)[pos];
        }

        // Busca la primera ocurrencia del elemento e y devuelve su índice (-1 si no está)
        int search(T e) const override {
            Node<T>* current = first;
            int index = 0;
            while (current != nullptr) {
                if (current->data == e) {
                    return index;
                }
                current = current->next;
                index++;
            }
            return -1;
        }

        // Indica si la lista está vacía
        bool empty() const override {
            return n == 0;
        }

        // Devuelve el número de elementos en la lista
        int size() const override {
            return n;
        }

        // Sobrecarga del operador [] para lectura/escritura
        T& operator[](int pos) {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posición fuera de rango");
            }
            Node<T>* current = first;
            for (int i = 0; i < pos; ++i) {
                current = current->next;
            }
            return current->data;
        }

        // Sobrecarga del operador [] constante
        T operator[](int pos) const {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posición fuera de rango");
            }
            Node<T>* current = first;
            for (int i = 0; i < pos; ++i) {
                current = current->next;
            }
            return current->data;
        }

        // Sobrecarga del operador << para imprimir la lista
        friend std::ostream& operator<<(std::ostream &out, const ListLinked<T> &list) {
            Node<T>* current = list.first;
            while (current != nullptr) {
                out << current->data << " ";
                current = current->next;
            }
            return out;
        }
};

#endif // LIST_LINKED_H
