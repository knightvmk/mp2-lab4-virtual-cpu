#include "program.h"
#include <gtest.h>

TEST(TProg, can_create_object)
{
	ASSERT_NO_THROW(TProg a(1, 1, 1));
}

TEST(TProg, throw_can_create_invalid_count)
{
	ASSERT_ANY_THROW(TProg a(max_t_count + 1, 1, 1));
}

TEST(TProg, throw_can_create_zero_count)
{
	ASSERT_ANY_THROW(TProg a(0, 1, 1));
}

TEST(TProg, throw_second_can_create_invalid_count)
{
	ASSERT_ANY_THROW(TProg a(0, 1, 1, 1));
}

TEST(TProg, throw_second_can_create_zero_count)
{
	ASSERT_ANY_THROW(TProg a(0, 1, 1,1));
}

TEST(TProg, throw_can_create_invalid_size_cluster)
{
	ASSERT_ANY_THROW(TProg a(1, 1, max_size + 1, 1));
}

TEST(TProg, throw_can_create_zero_size_cluster)
{
	ASSERT_ANY_THROW(TProg a(1, 1, 0, 1));
}

TEST(TProg, throw_can_create_invalid_cores_cluster)
{
	ASSERT_ANY_THROW(TProg a(1, 1, 1, max_num_cores + 1));
}

TEST(TProg, throw_can_create_zero_cores_cluster)
{
	ASSERT_ANY_THROW(TProg a(1, 1, 1, 0));
}

TEST(TProg, throw_can_create_invalid_complex)
{
	ASSERT_ANY_THROW(TProg a(1, max_t_complex+1, 1, 1));
}

TEST(TProg, throw_can_create_zero_complex)
{
	ASSERT_ANY_THROW(TProg a(1, 0, 1, 1));
}

TEST(TProg, throw_cant_set_invalid_count)
{
	TProg a(1, 1, 1);
	ASSERT_ANY_THROW(a.SetCount(max_t_count + 1));
}

TEST(TProg, throw_cant_set_zero_count)
{
	TProg a(1, 1, 1);
	ASSERT_ANY_THROW(a.SetCount(0));
}

TEST(TProg, throw_cant_set_negative_count)
{
	TProg a(1, 1, 1);
	ASSERT_ANY_THROW(a.SetCount(-1));
}

TEST(TProg, throw_cant_set_invalid_complex)
{
	TProg a(1, 1, 1);
	ASSERT_ANY_THROW(a.SetComplex(max_t_complex+1));
}

TEST(TProg, throw_cant_set_negative_complex)
{
	TProg a(1, 1, 1);
	ASSERT_ANY_THROW(a.SetComplex(-1));
}

TEST(TProg, throw_cant_set_zero_complex)
{
	TProg a(1, 1, 1);
	ASSERT_ANY_THROW(a.SetComplex(0));
}