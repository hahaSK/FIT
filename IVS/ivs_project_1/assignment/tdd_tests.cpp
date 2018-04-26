//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue tests
//
// $NoKeywords: $ivs_project_1 $tdd_tests.cpp
// $Authors:    Filip Vaverka <ivaverka@fit.vutbr.cz>
//              David Grochol <igrochol@fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file tdd_tests.cpp
 * @author Filip Vaverka
 * @author David Grochol
 * 
 * @brief Testy implementace prioritni fronty.
 */

#include "gtest/gtest.h"
#include "tdd_code.h"

class NonEmptyQueue : public ::testing::Test
{
protected:
    virtual void SetUp() {
        int values[] = { 12, 87, 17, 72, 22, 62, 32, 52, 67, 82, 92, 42, 7, 57 };

        for(int i = 0; i < 14; ++i)
            queue.Insert(values[i]);
    }

    PriorityQueue queue;
};

class EmptyQueue : public ::testing::Test
{
protected:
    PriorityQueue queue;
};

TEST_F(NonEmptyQueue, Insert)
{
    queue.Insert(2);
    EXPECT_EQ(queue.GetHead()->value, 2);

    queue.Insert(102);
    EXPECT_EQ(queue.GetHead()->value, 2);
}

TEST_F(NonEmptyQueue, RemoveAllForward)
{
    EXPECT_FALSE(queue.Remove(0));

    int values[] = { 7, 12, 17, 22, 32, 42, 52, 57, 62, 67, 72, 82, 87, 92 };
    for(int i = 0; i < 13; ++i)
    {
        EXPECT_TRUE(queue.Remove(values[i]));
        EXPECT_EQ(queue.GetHead()->value, values[i + 1]);
    }

    queue.Remove(92);
    EXPECT_TRUE(queue.GetHead() == NULL);
}

TEST_F(NonEmptyQueue, RemoveAllBackward)
{
    EXPECT_FALSE(queue.Remove(0));

    int values[] = { 92, 87, 82, 72, 67, 62, 57, 52, 42, 32, 22, 17, 12, 7 };
    for(int i = 0; i < 13; ++i)
    {
        EXPECT_TRUE(queue.Remove(values[i]));
        EXPECT_EQ(queue.GetHead()->value, 7);
    }

    queue.Remove(7);
    EXPECT_TRUE(queue.GetHead() == NULL);
}

TEST_F(NonEmptyQueue, Find)
{
    int values[] = { 7, 12, 17, 22, 32, 42, 52, 57, 62, 67, 72, 82, 87, 92 };
    for(int i = 0; i < 14; ++i)
    {
        PriorityQueue::Element_t *pElem = queue.Find(values[i]);
        ASSERT_TRUE(pElem != NULL);
        EXPECT_EQ(pElem->value, values[i]);

        EXPECT_TRUE(pElem->pPrev == NULL || pElem->pPrev->value <= pElem->value);
        EXPECT_TRUE(pElem->pNext == NULL || pElem->pNext->value >= pElem->value);
    }

    EXPECT_TRUE(queue.Find(0) == NULL);
}

TEST_F(EmptyQueue, Insert)
{
    EXPECT_TRUE(queue.GetHead() == NULL);

    queue.Insert(102);
    ASSERT_TRUE(queue.GetHead() != NULL);
    EXPECT_EQ(queue.GetHead()->value, 102);

    queue.Insert(2);
    ASSERT_TRUE(queue.GetHead() != NULL);
    EXPECT_EQ(queue.GetHead()->value, 2);
}

TEST_F(EmptyQueue, Remove)
{
    EXPECT_FALSE(queue.Remove(2));
}

TEST_F(EmptyQueue, Find)
{
    EXPECT_TRUE(queue.Find(2) == NULL);
}

/*** Konec souboru tdd_tests.cpp ***/
