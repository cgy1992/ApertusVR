#include "pch.h"
#include "gtest/gtest.h"
#include "../../include/apeDoubleQueue.h"

TEST(apeDoubleQueueClass, Default_Constructor) {
	ape::DoubleQueue<int> dq;

	EXPECT_EQ(true, dq.empty());
	EXPECT_EQ(true, dq.emptyPop());
	EXPECT_EQ(true, dq.emptyPush());
	EXPECT_EQ(0, dq.size());
	EXPECT_EQ(0, dq.sizePop());
	EXPECT_EQ(0, dq.sizePush());
}

TEST(apeDoubleQueueClass, push) {
	ape::DoubleQueue<int> dq;
	dq.push(5);
	EXPECT_FALSE( dq.empty());
	EXPECT_TRUE(dq.emptyPop());
	EXPECT_FALSE(dq.emptyPush());
	EXPECT_EQ(1, dq.size());
	EXPECT_EQ(0, dq.sizePop());
	EXPECT_EQ(1, dq.sizePush());
}

TEST(apeDoubleQueueClass, pop_swap_front) {
	ape::DoubleQueue<int> dq;
	dq.push(5);
	dq.pop();
	EXPECT_FALSE(dq.empty());
	EXPECT_TRUE(dq.emptyPop());
	EXPECT_FALSE(dq.emptyPush());
	EXPECT_EQ(1, dq.size());
	EXPECT_EQ(0, dq.sizePop());
	EXPECT_EQ(1, dq.sizePush());

	dq.swap();
	EXPECT_FALSE(dq.empty());
	EXPECT_FALSE(dq.emptyPop());
	EXPECT_TRUE(dq.emptyPush());
	EXPECT_EQ(1, dq.size());
	EXPECT_EQ(1, dq.sizePop());
	EXPECT_EQ(0, dq.sizePush());
	EXPECT_EQ(5, dq.front());


	dq.pop();
	EXPECT_TRUE(dq.empty());
	EXPECT_TRUE(dq.emptyPop());
	EXPECT_TRUE(dq.emptyPush());
	EXPECT_EQ(0, dq.size());
	EXPECT_EQ(0, dq.sizePop());
	EXPECT_EQ(0, dq.sizePush());
}

TEST(apeDoubleQueueClass, operators) {
	ape::DoubleQueue<int> dq, dq1;
	dq.push(5);
	dq1 = dq;
	EXPECT_FALSE(dq.empty());
	EXPECT_TRUE(dq.emptyPop());
	EXPECT_FALSE(dq.emptyPush());
	EXPECT_EQ(1, dq.size());
	EXPECT_EQ(0, dq.sizePop());
	EXPECT_EQ(1, dq.sizePush());

	EXPECT_FALSE(dq1.empty());
	EXPECT_TRUE(dq1.emptyPop());
	EXPECT_FALSE(dq1.emptyPush());
	EXPECT_EQ(1, dq1.size());
	EXPECT_EQ(0, dq1.sizePop());
	EXPECT_EQ(1, dq1.sizePush());
}
