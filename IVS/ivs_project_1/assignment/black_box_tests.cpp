//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Juraj Lahvicka <xlahvi0000@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Juraj Lahvicka
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

///Visualizaion of Red-Black Tree
///https://www.cs.usfca.edu/~galles/visualization/RedBlack.html

namespace BlackBoxTesting
{
    class TreeTesting : public ::testing::Test
    {
    protected:
        BinaryTree tree;

        std::vector<int> nodes = {10, 7, 22, 4, 9, 13, 3, 19, 27, 16, 12, 42, 20, 33, 35, 29};
        std::vector<std::pair<bool, Node_t *> > outNewNodes;
        std::vector<int> axiomNodes = {2, 1, 5};

    };

    class EmptyTree : public TreeTesting
    {
    };

    class NonEmptyTree : public TreeTesting
    {
        virtual void SetUp()
        {
          tree.InsertNodes(nodes, outNewNodes);
        }
    };

    class TreeAxioms : public TreeTesting
    {
        virtual void SetUp()
        {
          tree.InsertNodes(axiomNodes, outNewNodes);
        }
    };


    TEST_F(EmptyTree, InsertNode)
    {

      /// first node
      // insert first node to tree
      std::pair<bool, BinaryTree::Node_t *> node1 = tree.InsertNode(-5);
      ASSERT_TRUE(node1.second != NULL);
      EXPECT_TRUE(node1.first);

      // same node input
      std::pair<bool, BinaryTree::Node_t *> duplicateNode = tree.InsertNode(-5);
      ASSERT_EQ(duplicateNode.second, node1.second);
      EXPECT_EQ(duplicateNode.second->key, -5);
      EXPECT_FALSE(duplicateNode.first);

      // node state check
      ASSERT_EQ(node1.second->key, -5);
      EXPECT_EQ(node1.second->color, tree.BLACK);
      EXPECT_TRUE(node1.second->pParent == NULL);

      // check right child
      BinaryTree::Node_t *rChildOfNode1 = node1.second->pRight;
      ASSERT_TRUE(rChildOfNode1 != NULL);
      EXPECT_EQ(rChildOfNode1->color, tree.BLACK);
      EXPECT_TRUE(rChildOfNode1->pRight == NULL);
      EXPECT_TRUE(rChildOfNode1->pLeft == NULL);
      EXPECT_TRUE(rChildOfNode1->pParent != NULL);
      EXPECT_EQ(rChildOfNode1->pParent->key, -5);

      // check left child
      BinaryTree::Node_t *lChildOfNode1 = node1.second->pLeft;
      ASSERT_TRUE(lChildOfNode1 != NULL);
      EXPECT_EQ(lChildOfNode1->color, tree.BLACK);
      EXPECT_TRUE(lChildOfNode1->pRight == NULL);
      EXPECT_TRUE(lChildOfNode1->pLeft == NULL);
      EXPECT_TRUE(lChildOfNode1->pParent != NULL);
      EXPECT_EQ(lChildOfNode1->pParent->key, -5);

      /// second node
      // insert second node to tree
      std::pair<bool, BinaryTree::Node_t *> node2 = tree.InsertNode(5);
      ASSERT_TRUE(node2.second != NULL);
      EXPECT_TRUE(node2.first);

      // node state check
      ASSERT_EQ(node2.second->key, 5);
      EXPECT_EQ(node2.second->color, tree.RED);
      EXPECT_TRUE(node2.second->pParent != NULL);

      // check right child
      BinaryTree::Node_t *rChildOfNode2 = node2.second->pRight;
      ASSERT_TRUE(rChildOfNode2 != NULL);
      EXPECT_EQ(rChildOfNode2->color, tree.BLACK);
      EXPECT_TRUE(rChildOfNode2->pRight == NULL);
      EXPECT_TRUE(rChildOfNode2->pLeft == NULL);
      EXPECT_TRUE(rChildOfNode2->pParent != NULL);
      EXPECT_EQ(rChildOfNode2->pParent->key, 5);

      // check left child
      BinaryTree::Node_t *lChildOfNode2 = node2.second->pLeft;
      ASSERT_TRUE(lChildOfNode2 != NULL);
      EXPECT_EQ(lChildOfNode2->color, tree.BLACK);
      EXPECT_TRUE(lChildOfNode2->pRight == NULL);
      EXPECT_TRUE(lChildOfNode2->pLeft == NULL);
      EXPECT_TRUE(lChildOfNode2->pParent != NULL);
      EXPECT_EQ(lChildOfNode2->pParent->key, 5);


      // check state after second node insertion
      ASSERT_EQ(node1.second->pRight, node2.second);
      EXPECT_EQ(node2.second->pParent, node1.second);


      /// third node
      // insert third node to tree
      std::pair<bool, BinaryTree::Node_t *> node3 = tree.InsertNode(2);
      ASSERT_TRUE(node3.second != NULL);
      EXPECT_TRUE(node3.first);

      // node state check
      ASSERT_EQ(node3.second->key, 2);
      EXPECT_EQ(node3.second->color, tree.BLACK);
      EXPECT_TRUE(node3.second->pParent == NULL);

      // check right child
      BinaryTree::Node_t *rChildOfNode3 = node3.second->pRight;
      ASSERT_EQ(rChildOfNode3->key, 5);
      EXPECT_EQ(rChildOfNode3->color, tree.RED);
      EXPECT_EQ(rChildOfNode3, node2.second);

      // check left child
      BinaryTree::Node_t *lChildOfNode3 = node3.second->pLeft;
      ASSERT_EQ(lChildOfNode3->key, -5);
      EXPECT_EQ(lChildOfNode3->color, tree.RED);
      EXPECT_EQ(lChildOfNode3, node1.second);

    }

    TEST_F(EmptyTree, DeleteNode)
    {
      EXPECT_FALSE(tree.DeleteNode(0));
      EXPECT_FALSE(tree.DeleteNode(60));

      tree.InsertNode(-5);
      ASSERT_TRUE(tree.DeleteNode(-5));

    }

    TEST_F(EmptyTree, FindNode)
    {
      EXPECT_TRUE(tree.FindNode(0) == NULL);
      EXPECT_TRUE(tree.FindNode(60) == NULL);

      tree.InsertNode(-5);
      ASSERT_TRUE(tree.FindNode(-5) != NULL);
      EXPECT_TRUE(tree.FindNode(-5)->key == -5);

    }


    TEST_F(NonEmptyTree, InsertNode)
    {

      /// bonus testing
      // checks if all the nodes were added
      for (int i = 0; i < nodes.size(); i++)
      {
        EXPECT_TRUE(outNewNodes[i].first);
      }

      // adding the same node vector
      tree.InsertNodes(nodes, outNewNodes);
      // checks for the same nodes
      std::vector<std::pair<bool, Node_t *> > saveOutNodes = outNewNodes;
      for (int i; i < nodes.size(); i++)
      {
        EXPECT_FALSE(outNewNodes[i].first);
        EXPECT_EQ(outNewNodes[i].second, saveOutNodes[i].second);
      }

      ///

      // same node input
      std::pair<bool, BinaryTree::Node_t *> duplicateNode = tree.InsertNode(10);
      ASSERT_FALSE(duplicateNode.first);
      EXPECT_EQ(duplicateNode.second->key, 10);

      // insert new node
      std::pair<bool, BinaryTree::Node_t *> newNode = tree.InsertNode(30);
      ASSERT_TRUE(newNode.first);
      EXPECT_EQ(newNode.second->color, tree.BLACK);

      // check parent
      EXPECT_EQ(newNode.second->pParent->key, 35);
      EXPECT_EQ(newNode.second->pParent->color, tree.RED);

      // check right child
      EXPECT_EQ(newNode.second->pRight->key, 33);
      EXPECT_EQ(newNode.second->pRight->color, tree.RED);

      // check left child
      EXPECT_EQ(newNode.second->pLeft->key, 29);
      EXPECT_EQ(newNode.second->pLeft->color, tree.RED);

    }

    TEST_F(NonEmptyTree, DeleteNode)
    {

      for (int i; i < nodes.size(); i++)
      {
        if (i == 6 or i == 12)
          EXPECT_TRUE(tree.DeleteNode(outNewNodes[i].second->key));
      }

      EXPECT_FALSE(tree.DeleteNode(-5));
      EXPECT_FALSE(tree.DeleteNode(4242));

    }

    TEST_F(NonEmptyTree, FindNode)
    {

      for (int i; i < nodes.size(); i++)
      {
        if (i == 2 or i == 10)
          EXPECT_EQ(tree.FindNode(outNewNodes[i].second->key), outNewNodes[i].second);
      }

      EXPECT_TRUE(tree.FindNode(-5) == NULL);
      EXPECT_TRUE(tree.FindNode(4242) == NULL);

    }

    /// Axiom 1 - all leaf nodes are black
    TEST_F(TreeAxioms, Axiom1)
    {
      std::vector<BinaryTree::Node_t *> leafNodes;
      tree.GetLeafNodes(leafNodes);

      // for each
      for (BinaryTree::Node_t *node : leafNodes)
      {
        EXPECT_EQ(node->color, BinaryTree::BLACK);
      }
    }

    /// Axiom 2 - if node is black, both of his children are black
    TEST_F(TreeAxioms, Axiom2)
    {
      std::vector<BinaryTree::Node_t *> allNodes;
      tree.GetAllNodes(allNodes);

      // for each
      for (BinaryTree::Node_t *node : allNodes)
      {
        if (node->color == BinaryTree::RED)
        {
          EXPECT_EQ(node->pLeft->color, BinaryTree::BLACK);
          EXPECT_EQ(node->pRight->color, BinaryTree::BLACK);
        }
      }
    }

    /// Axiom 3 - every path from every leaf node to root has the same number of black nodes
    TEST_F(TreeAxioms, Axiom3)
    {
      // looks for leaf nodes
      std::vector<BinaryTree::Node_t *> leafNodes;
      tree.GetLeafNodes(leafNodes);

      BinaryTree::Node_t *currentNode;

      int expectedBlackNodesCount = -1;

      // for each leaf node
      for (BinaryTree::Node_t *node : leafNodes)
      {
        int currentBlackNodesCount = 0;
        currentNode = node;

        // counts the number of black nodes on the path to root
        while (currentNode)
        {
          if (currentNode->color == BinaryTree::BLACK)
          {
            currentBlackNodesCount++;
          }
          currentNode = currentNode->pParent;
        }

        // compares the results between last two, if there are two or more leafs that were checked
        if (expectedBlackNodesCount >= 0)
        {
          EXPECT_EQ(expectedBlackNodesCount, currentBlackNodesCount);
        }

        expectedBlackNodesCount = currentBlackNodesCount;
      }
    }
}


/*** Konec souboru black_box_tests.cpp ***/
