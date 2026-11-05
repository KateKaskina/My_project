#include <gtest/gtest.h>
#include "main.h" 


// ТЕСТЫ ДЛЯ КЛАССА STACK

// Тест инициализации и начального состояния
TEST(StackTest, InitialState) {
    Stack<int> st;
    EXPECT_TRUE(st.IsEmpty());
    EXPECT_EQ(st.size(), 0);
    EXPECT_THROW(st.Pop(), std::underflow_error);
}

TEST(StackTest, PopPushOperations) {
    Stack<int> st;
    
    st.Push(10);
    st.Push(20);

    EXPECT_EQ(st.size(),2);
    EXPECT_FALSE(st.IsEmpty());

    EXPECT_EQ(st.Pop(), 20);
    EXPECT_EQ(st.Pop(), 10);
    EXPECT_TRUE(st.IsEmpty());
}

TEST(StackTest, AutoResize) {
    Stack<int> st; // memSize=1
    st.Push(1); 
    st.Push(2); // здесь должен вызываться resize()
    st.Push(3);

    EXPECT_EQ(st.size(), 3);
    EXPECT_EQ(st.Pop(), 3);
}

TEST(StackTest, OperatorIndex) {
    Stack<int> st;  
    st.Push(100);
    st.Push(200);  

    // Проверка чтения
    EXPECT_EQ(st[0], 100);
    EXPECT_EQ(st[1], 200);

    // Проверка записи
    st[0] = 500;
    EXPECT_EQ(st[0], 500);

    // Проверка генерации исключений при выходе за границы
    EXPECT_THROW(st[2], std::out_of_range);
    EXPECT_THROW(st[10], std::out_of_range);
}


// ТЕСТЫ ДЛЯ КЛАССА QUEUE

// Тест инициализации и начального состояния
TEST(QueueTest, InitialState) {
    Queue<int> q;
    EXPECT_TRUE(q.IsEmpty());
    EXPECT_EQ(q.size(), 0);
    EXPECT_THROW(q.Pop(), std::underflow_error);
}

TEST(QueueTest, PopPushOperations) {
    Queue<int> q;

    q.Push(10);
    q.Push(20);

    EXPECT_EQ(q.size(), 2);
    EXPECT_EQ(q.Pop(), 10);
    EXPECT_EQ(q.Pop(), 20);
    EXPECT_TRUE(q.IsEmpty());
}

// Тест логики кольцевого буфера (Wrap Around)
TEST(QueueTest, CircularBufferWrapAround) {
    Queue<int> q; // memSize = 2 
    q.Push(1);
    q.Push(2);    // Очередь заполнена [1, 2]

    q.Pop();      // Удалили 1. Теперь `first` указывает на индекс 1.

    // Добавляем элемент. Он должен зациклиться и встать на освободившийся индекс 0.
    EXPECT_NO_THROW(q.Push(3));
    EXPECT_EQ(q.size(), 2);

    // Проверяем, что элементы извлекаются в верном порядке (2, затем 3)
    EXPECT_EQ(q.Pop(), 2);
    EXPECT_EQ(q.Pop(), 3);
    EXPECT_TRUE(q.IsEmpty());
}

// Тест resize в момент, когда очередь "разорвана" по кольцу
TEST(QueueTest, ResizeWhenWrapped) {
    Queue<int> q; // memSize = 2
    q.Push(1);
    q.Push(2);
    q.Pop();      // Очередь: [_, 2], буфер сдвинут
    q.Push(3);    

    EXPECT_NO_THROW(q.Push(4));

    EXPECT_EQ(q.size(), 3);
    EXPECT_EQ(q.Pop(), 2);
    EXPECT_EQ(q.Pop(), 3);
    EXPECT_EQ(q.Pop(), 4);
}

TEST(QueueTest, OperatorIndex) {
    Queue<int> q; // memSize = 2
    q.Push(10);
    q.Push(20);
    q.Pop();
    q.Push(30);   // Элементы в памяти физически расположены как [30, 20]

    // Логически под индексом 0 идет элемент 20 (голова очереди), под индексом 1 - 30.
    EXPECT_EQ(q[0], 20);
    EXPECT_EQ(q[1], 30);

    // Изменение элемента по индексу
    q[0] = 99;
    EXPECT_EQ(q[0], 99);

    // Проверка исключений
    EXPECT_THROW(q[2], std::out_of_range);
}