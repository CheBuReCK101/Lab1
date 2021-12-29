// Lab1CPP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
#include <cstdlib> // для функций rand() и srand()
#include <ctime> // для функции time()
int flag1, flag2;
bool flag3=0;
struct element {

    int value;
    element* next;
};
class Queue {
public:
    element* head;
    Queue() {
        head = 0;
    }
    ~Queue();
    unsigned long n_op;
    void N_op(unsigned long x) // функция для увеличения числа операций + 1
    {
        n_op = n_op + x + 4; // + 3
    }

    void enQueue(int n) {
        if (head == 0) {
            head = new element;
            head->value = n;
            head->next = 0;
         }
        else if (head->next == 0) {
            element* tmpElement = new element;
            tmpElement->value = n;
            tmpElement->next = 0;
            head->next = tmpElement;
        }
        else {
            element* currentElement = head->next;
            while (currentElement->next != 0) {
                currentElement = currentElement->next;
                N_op(4);
            }
            element* tmpElement = new element;
            tmpElement->value = n;
            tmpElement->next = 0;
            currentElement->next = tmpElement;
        }
    }
    void deQueue() {
        if (getSizeQueue() == 0) {
            return;
        }
        else {
            head = head->next;
        }
    }
    int deQueueReturn() {
        int n = 0;
        if (getSizeQueue() == 0) {
            cin.get();
        }
        else {
            n = head->value;
            head = head->next;
        }
        return n;
    }
    int getSizeQueue() {
        int i = 0;
        element* currentElement = head;
        while (currentElement != 0) {
            currentElement = currentElement->next;
            ++i;
        }
        return i;
    }
    void showQueue() {
        element* currentElement = head;
        while (currentElement != 0) {
            cout << currentElement->value << " ";
            currentElement = currentElement->next;
        }
        cout << endl;
    }


    void Counts(int* Array, int Min, int Max) {//4
        element* currentElement = head;/// Снова в начало очереди  + 6
        while (currentElement != 0) {//1
            Array[(currentElement->value) - Min]++ ;// TEMP_Counts - показывает сколько раз встречается то или иное число +4
            currentElement = currentElement->next;// к следующему элементу +2
            N_op(7); //+1
        }
         N_op(11); //+1
    }

    void RefillQueue(int* Array, int Min, int Max) {//4
        element* currentHead = head;/// Запоминаем начало очереди + 6
        for (int i = 0; i <= (Max-Min)+1; i++) {//4
            if (Array[i] == 0) {//2
                N_op(3); //+1
                continue; }
            if (!flag3) {//1
                currentHead->value = i + Min;
                flag3 = 1;
                N_op(5); //+1
            }
            for (int j = 0; j < Array[i]; j++) {
                head->value = i+Min;
                head = head->next;// к следующему элементу
                N_op(9); //+1
            }
            N_op(9); //+1                         
        }
        head = currentHead;//2
        N_op(16); //+1
    }

    //Сортировка Очереди Распределяющим Подсчетом
    void sortQueue() {//1
        int Max, Min;//2
        Max = Min = head->value;//3
        element* currentElement = head;// В начало очереди +6
        N_op(12); //+1
        while (currentElement != 0) {//1
            if (currentElement->value > Max) { //2
                Max = currentElement->value;//2
                N_op(4); //+1
            }
            if (currentElement->value < Min) {//2
                Min = currentElement->value;//2
                N_op(4); //+1
            }
            currentElement = currentElement->next;// к следующему элементу +2
            N_op(7); //+1
        }
        //+1
        int* TEMP_Counts = new int[Max-Min+1];//3
        for (int i = 0; i < (Max - Min) + 1; i++) {
            TEMP_Counts[i] = 0;// обнуление массива
            N_op(5); //+1
        }
        //+3
        Counts(TEMP_Counts, Min, Max);//Считаем числа +1
        N_op(3);
        //Перезаполняем очередь
        RefillQueue(TEMP_Counts, Min, Max);
        //+1
        
        
        delete[] TEMP_Counts;//+1
        N_op(10); //+1
    }


    /*
    int getItemQueue(int position) {
        int i = 0, item;
        element* currentElement = head;
        while (i < position) {  // дропаем очередь до первого элемента
            currentElement = currentElement->next;
            i++;
        }
        item = currentElement->value;
        return item;
    }
    void swap(int position1, int position2) {//делит на 3 очереди
        if (position2 - position1 > 1) {
            Queue* beginQueue = new Queue();
            Queue* middleQueue = new Queue();
            Queue* endQueue = new Queue();
            int i = 0, value1, value2;
            element* currentElement = head;
            while (i < position1) {  // дропаем очередь до первого элемента
                beginQueue->enQueue(deQueueReturn());
                currentElement = currentElement->next;
                i++;
            }
            value1 = deQueueReturn(); // дропаем первый нужный элемент
            currentElement = head;
            i = 0;
            do { // дропаем очередь от первого до второго элемента
                middleQueue->enQueue(deQueueReturn());
                currentElement = currentElement->next;
                i++;
            } while (i < position2 - position1 - 1);
            value2 = deQueueReturn(); // дропаем второй элемент
            currentElement = head;
            while (currentElement) { // дропаем конец очереди для сохранения порядка очереди
                endQueue->enQueue(deQueueReturn());
                currentElement = currentElement->next;
            }
            currentElement = beginQueue->head;
            while (currentElement) { // заливаем начало очереди
                enQueue(beginQueue->deQueueReturn());
                currentElement = currentElement->next;
            }
            enQueue(value2); // ставим второй элемент на место первого
            currentElement = middleQueue->head;
            while (currentElement) { // заливаем очередь от первоого до второго элементов
                enQueue(middleQueue->deQueueReturn());
                currentElement = currentElement->next;
            }
            enQueue(value1); // ставим первый элемент на место второго
            currentElement = endQueue->head;
            while (currentElement) { // дозаливаем конец очереди
                enQueue(endQueue->deQueueReturn());
                currentElement = currentElement->next;
            }
        }
        else {
            Queue* beginQueue = new Queue();
            Queue* endQueue = new Queue();
            int i = 0, value1, value2;
            element* currentElement = head;
            while (i < position1) { // дропаем очередь до первого элемента
                beginQueue->enQueue(deQueueReturn());
                currentElement = currentElement->next;
                i++;
            }
            value1 = deQueueReturn(); // дропаем первый нужный элемент
            currentElement = head;
            value2 = deQueueReturn(); // дропаем второй нужный элемент
            currentElement = head;
            i = 0;
            while (currentElement) { // дропаем остаток очереди
                endQueue->enQueue(deQueueReturn());
                currentElement = currentElement->next;
            }
            currentElement = beginQueue->head;
            while (currentElement) { // заливаем начало очереди
                enQueue(beginQueue->deQueueReturn());
                currentElement = currentElement->next;
            }
            enQueue(value2); // ставим нужные элементы на места друг друга
            enQueue(value1);
            currentElement = endQueue->head;
            while (currentElement) { // дозаливаем конец очереди
                enQueue(endQueue->deQueueReturn());
                currentElement = currentElement->next;
            }
        }
    }
    */
};

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    auto Q = new Queue();
    int n = 0;
    cout << "Введите количество элементов " << endl;
    cin >>  n ;
    
    for (int i = 0; i < n; i++) {
        Q->enQueue(rand() % 1000+1);
    }
    unsigned int start_time = clock(); // начальное время
    Q->sortQueue();
    unsigned int end_time = clock(); // конечное время
    unsigned int sortTime = (end_time - start_time);
    cout << "Отсортирован за " << sortTime << endl; // время работы программы    
    cout << "До сортировки " << start_time << endl; // время работы программы до сортироваки
    cout << "После сортировки " << end_time << endl; // время работы программы после сортировки
    cout << "Операций: " << Q->n_op << endl;
    system("pause");
    return 0;
}