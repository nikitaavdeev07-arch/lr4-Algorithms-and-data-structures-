// LR4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdexcept>
#include <string>


// Шаблонный класс двусвязного списка

template <typename T>
class DoublyLinkedList {
private:
    // Узел двусвязного списка
    struct Node {
        T data;           // данные
        Node* prev;       // указатель на предыдущий узел
        Node* next;       // указатель на следующий узел

        Node(const T& value)
            : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;   // «голова» списка
    Node* tail;   // «хвост» списка
    int count;    // количество элементов

public:
    // ---------- Конструктор / деструктор ----------
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

    ~DoublyLinkedList() { clear(); }

    // ---------- Вставка в начало O(1) ----------
    void push_front(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;         
        }
        else {
            newNode->next = head;        
            head->prev = newNode;         
            head = newNode;              
        }
        count++;
    }

    // ---------- Вставка в конец O(1) ----------
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (tail == nullptr) {
            head = tail = newNode;      
        }
        else {
            tail->next = newNode;           
            newNode->prev = tail;          
            tail = newNode;                 
        }
        count++;
    }

    // ---------- Удаление из начала O(1) ----------
    void pop_front() {
        if (head == nullptr)
            throw std::underflow_error("List is empty");
        Node* temp = head;
        head = head->next;
        if (head != nullptr)
            head->prev = nullptr;
        else
            tail = nullptr;                
        delete temp;
        count--;
    }

    // ---------- Удаление из конца O(1) ----------
    void pop_back() {
        if (tail == nullptr)
            throw std::underflow_error("List is empty");
        Node* temp = tail;
        tail = tail->prev;
        if (tail != nullptr)
            tail->next = nullptr;
        else
            head = nullptr;                 
        delete temp;
        count--;
    }

    // ---------- Поиск по значению O(n) ----------
    Node* find(const T& value) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) return current;
            current = current->next;
        }
        return nullptr;
    }

    // ---------- РЕВЕРС СПИСКА (вариант 1) O(n) ----------
    void reverse() {
        if (head == nullptr) return;        

        Node* current = head;
        Node* temp = nullptr;

        while (current != nullptr) {
            // Меняем местами prev и next у текущего узла
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;

            // Переходим к следующему узлу (в старой нумерации — prev)
            current = current->prev;
        }

        // Меняем местами head и tail
        temp = reinterpret_cast<Node*>(head);
        head = tail;
        tail = reinterpret_cast<Node*>(temp);
    }

    // ---------- Вывод в прямом порядке O(n) ----------
    void print() const {
        Node* current = head;
        std::cout << "[";
        while (current != nullptr) {
            std::cout << current->data;
            if (current->next != nullptr) std::cout << ", ";
            current = current->next;
        }
        std::cout << "]" << std::endl;
    }

    // ---------- Вывод в обратном порядке O(n) ----------
    void printReverse() const {
        Node* current = tail;
        std::cout << "[";
        while (current != nullptr) {
            std::cout << current->data;
            if (current->prev != nullptr) std::cout << ", ";
            current = current->prev;
        }
        std::cout << "]" << std::endl;
    }

    // ---------- Очистка списка ----------
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        count = 0;
    }

    int size() const { return count; }
    bool empty() const { return head == nullptr; }
};

int main() {
    setlocale(LC_ALL, "ru");

    DoublyLinkedList<int> list;

    // Заполняем список: 10 20 30 40 50
    for (int i = 1; i <= 5; i++)
        list.push_back(i * 10);

    std::cout << "== Двусвязный список (Средний уровень, вариант 1) ==\n";
    std::cout << "Исходный список:       ";  list.print();
    std::cout << "Обратный порядок:      ";  list.printReverse();
    std::cout << "Размер: " << list.size() << "\n\n";

    // --- Применяем reverse ---
    list.reverse();
    std::cout << "После reverse():        ";  list.print();
    std::cout << "Обратный порядок:      ";  list.printReverse();
    std::cout << "Размер: " << list.size() << "\n\n";

    // --- Проверяем базовые операции ---
    list.push_front(5);
    list.push_back(60);
    std::cout << "После push_front(5) и push_back(60): ";
    list.print();

    list.pop_front();
    list.pop_back();
    std::cout << "После pop_front() и pop_back():       ";
    list.print();

    // --- Повторный реверс возвращает исходный порядок ---
    list.reverse();
    std::cout << "После повторного reverse():           ";
    list.print();

    // --- Поиск ---
    auto* node = list.find(30);
    if (node)
        std::cout << "Найдено значение 30\n";
    else
        std::cout << "Значение 30 не найдено\n";

    // --- Очистка ---
    list.clear();
    std::cout << "После clear(): размер = " << list.size()
        << ", пуст = " << (list.empty() ? "да" : "нет") << std::endl;

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
