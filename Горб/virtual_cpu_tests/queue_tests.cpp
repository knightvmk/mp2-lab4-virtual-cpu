#include "queue.h"
#include <gtest.h>

TEST(TQueue, can_create_queue_by_default) //for example
{
	ASSERT_NO_THROW(TQueue<int> a());
}

TEST(TQueue, can_create_queue_with_true_size)
{
	ASSERT_NO_THROW(TQueue<char> a(5));
}

TEST(TQueue, cant_create_queue_with_override_size)
{
	ASSERT_ANY_THROW(TQueue<char> a(MAX_SIZE+1));
}

TEST(TQueue, cant_create_queue_with_negative_size)
{
	ASSERT_ANY_THROW(TQueue<long float> a(-15));
}

TEST(TQueue, can_copy_queue)
{
	TQueue<int> a(2);
	ASSERT_NO_THROW(TQueue<int> b(a));
}

TEST(TQueue, copied_queue_has_own_memory)
{
	TQueue<int> a(2);
	a.Push(5);
	TQueue<int> b(a);
	b.Pop();
	b.Push(7);
	EXPECT_NE(a.Pop(), b.Pop());
}

TEST(TQueue, operation_peek_cant_change_queue)
{
	TQueue<double> a(3);
	a.Push(5);
	a.Peek();
	EXPECT_EQ(5, a.Peek());
}

TEST(TQueue, throw_operation_peek_queue_is_empty)
{
	TQueue<int> b(3);
	ASSERT_ANY_THROW(b.Peek());
}

TEST(TQueue, operation_pop_can_change_queue)
{
	TQueue<double> b(2);
	b.Push(7);
	b.Pop();
	b.Push(3);
	EXPECT_EQ(3,b.Pop());
}

TEST(TQueue, throw_operation_pop_queue_is_empty)
{
	TQueue<double> a(2);
	ASSERT_ANY_THROW(a.Pop());
}

TEST(TQueue, operation_push_can_to_full_queue)
{
	TQueue<int> a(2);
	a.Push(3);
	a.Push(4);
	a.Push(5);
	EXPECT_EQ(5, a.GetLast());
}

TEST(TQueue, operation_isfull_return_true_in_full_queue)
{
	TQueue<int> a(2);
	a.Push(1);
	a.Push(4);
	EXPECT_EQ(true, a.IsFull());
}

TEST(TQueue, operation_isfull_return_true_in_nofull_queue)
{
	TQueue<int> a(2);
	a.Push(5);
	a.Push(8);
	a.Pop();
	EXPECT_EQ(false, a.IsFull());
}

TEST(TQueue, operation_isempty_return_true_in_empty_queue)
{
	TQueue<double> a(3);
	a.Push(9);
	a.Pop();
	EXPECT_EQ(true, a.IsEmpty());
}

TEST(TQueue, operation_isempty_return_false_in_noempty_queue)
{
	TQueue<double> a(2);
	a.Push(1);
	EXPECT_EQ(false, a.IsEmpty());
}

TEST(TQueue, throw_operaiton_GetLast_queue_is_empty)
{
	TQueue<int> a(2);
	ASSERT_ANY_THROW(a.GetLast());
}

TEST(TQueue, operation_GetLast_real_return_last)
{
	TQueue<int> a(5);
	a.Push(10);
	a.Push(3);
	EXPECT_EQ(3, a.GetLast());
}

TEST(TQueue, operation_GetLast_cant_change_queue)
{
	TQueue<char> b(5);
	b.Push('v');
	b.Push('m');
	b.Push('k');
	char k = b.GetLast();
	b.Push('0');
	EXPECT_EQ(b.GetLast(), '0');
}

TEST(TQueue, operation_Get_is_real_iterator)
{
	TQueue<int> a(4);
	a.Push(4);
	a.Push(6);
	a.Push(12);
	a.Push(9);
	EXPECT_EQ(6, a.Get(2));
}

TEST(TQueue, operation_Get_cant_change_queue)
{
	TQueue<int> a(2);
	a.Push(4);
	int ex = a.Get(1);
	a.Push(5);
	EXPECT_EQ(4, a.Get(1));
}


