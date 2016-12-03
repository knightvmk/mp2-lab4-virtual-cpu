#include "cpu.h"
#include <gtest.h>

TEST(TCpu, can_create_cpu)
{
	ASSERT_NO_THROW(TCpu a(1));
}

TEST(TCpu, throw_create_overmax_cpu)
{
	ASSERT_ANY_THROW(TCpu a(max_cores + 1));
}

TEST(TCpu, throw_create_with_zero_cores)
{
	ASSERT_ANY_THROW(TCpu a(0));
}

TEST(TCpu, throw_invalid_iterator_isbusy)
{
	TCpu a(3);
	ASSERT_ANY_THROW(a.IsBusy(4));
}

TEST(TCpu, throw_invalid_iterator_setstat)
{
	TCpu a(2);
	ASSERT_ANY_THROW(a.SetStat(3));
}

TEST(TCpu, throw_can_set_overdrive_freq)
{
	TCpu a(3);
	ASSERT_ANY_THROW(a.SetFreq(max_freq + 100));
}

TEST(TCpu, throw_can_set_overdrive_cores)
{
	TCpu a(4);
	ASSERT_ANY_THROW(a.SetCore(max_cores+1));
}