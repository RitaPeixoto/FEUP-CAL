#include <gtest/gtest.h>
#include <gmock/gmock.h>

//#include "Defs.h"
#include "Factorial.h"
#include "Change.h"
#include "Sum.h"
#include "Partitioning.h"

using namespace std;
using testing::Eq;


TEST(CAL_FP01, FactorialTest) {
	EXPECT_EQ(120,factorialRecurs(5));
	EXPECT_EQ(3628800,factorialRecurs(10));
	EXPECT_EQ(120,factorialDinam(5));
	EXPECT_EQ(3628800,factorialDinam(10));
}


TEST(CAL_FP01, CalcChangeTest) {
	int numCoins = 3;
	int coinValues[] = {1, 2, 5};


	EXPECT_EQ("5;",calcChange(5, numCoins, coinValues));
	EXPECT_EQ("5;5;5;1;",calcChange(16, numCoins, coinValues));
	EXPECT_EQ("",calcChange(0, numCoins, coinValues));

	int numCoins2 = 2;
	int coinValues2[] = {2, 5};
	EXPECT_EQ("-", calcChange(1, numCoins2, coinValues2));
	EXPECT_EQ("5;2;",calcChange(7, numCoins2, coinValues2));

	int numCoins3 = 3;
	int coinValues3[] = {1, 4, 5};
	EXPECT_EQ("4;4;",calcChange(8, numCoins3, coinValues3));
}


TEST(CAL_FP01, CalcSumArrayTest) {
	int sequence[5] = {4,7,2,8,1};
	int sequence2[9] = {6,1,10,3,2,6,7,2,4};

	EXPECT_EQ("1,4;9,1;11,2;18,1;22,0;",calcSum(sequence, 5));
	EXPECT_EQ("1,1;5,3;11,3;16,1;20,3;24,3;31,1;35,1;41,0;",calcSum(sequence2, 9));
}


TEST(CAL_FP01, PartitioningTest) {
	EXPECT_EQ(3025,s_recursive(9,3));
	EXPECT_EQ(22827,s_recursive(10,6));
	EXPECT_EQ(3025,s_dynamic(9,3));
	EXPECT_EQ(22827,s_dynamic(10,6));
	EXPECT_EQ(22827,s_dynamic(10,6));
	EXPECT_EQ(5,b_recursive(3));
	EXPECT_EQ(1382958545,b_recursive(15));
	EXPECT_EQ(5,b_dynamic(3));
	EXPECT_EQ(203,b_dynamic(6));
	EXPECT_EQ(1382958545,b_dynamic(15));
}

