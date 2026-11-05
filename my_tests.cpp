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