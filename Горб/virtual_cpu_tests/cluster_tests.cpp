#include "cluster.h"
#include <gtest.h>

TEST(TCluster, can_create_cluster)
{
	ASSERT_NO_THROW(TCluster a(1));
}

TEST(TCluster, throw_create_to_big_cluster)
{
	ASSERT_ANY_THROW(TCluster a(max_size + 1));
}

TEST(TCluster, throw_create_with_negative_size)
{
	ASSERT_ANY_THROW(TCluster a(-2));
}

TEST(TCluster, throw_create_with_zero_size)
{
	ASSERT_ANY_THROW(TCluster a(0));
}

TEST(TCluster, throw_create_overdrive_num_cpu)
{
	ASSERT_ANY_THROW(TCluster a(1, max_num_cores + 1));
}

TEST(TCluster, throw_create_with_zero_cpu)
{
	ASSERT_ANY_THROW(TCluster a(1, 0));
}

TEST(TCluster, throw_set_overdrive_freq)
{
	TCluster a(4);
	ASSERT_ANY_THROW(a.SetFreq(max_freq+100));
}

TEST(TCluster, throw_set_less_freq)
{
	TCluster a(2);
	ASSERT_ANY_THROW(a.SetFreq(min_freq - 100));
}

TEST(TCluster, throw_cant_set_overdrive_size)
{
	TCluster a(3);
	ASSERT_ANY_THROW(a.SetSize(max_size + 1));
}

TEST(TCluster, throw_cant_set_zero_size)
{
	TCluster a(1);
	ASSERT_ANY_THROW(a.SetSize(0));
}

TEST(TCluster, throw_cant_negative_size)
{
	TCluster a(4);
	ASSERT_ANY_THROW(a.SetSize(-5));
}

TEST(TCluster, throw_cant_set_overdrive_cores)
{
	TCluster a(3);
	ASSERT_ANY_THROW(a.SetCores(max_num_cores + 1));
}

TEST(TCluster, throw_cant_set_negative_cores)
{
	TCluster a(6);
	ASSERT_ANY_THROW(a.SetCores(-3));
}

TEST(TCluster, throw_cant_set_zero_cores)
{
	TCluster a(2);
	ASSERT_ANY_THROW(a.SetCores(0));
}

