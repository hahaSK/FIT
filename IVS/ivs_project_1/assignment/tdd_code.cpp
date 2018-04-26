//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Juraj Lahvicka <xlahvi00@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Juraj Lahvicka
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy 
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
  root = NULL;
}

PriorityQueue::~PriorityQueue()
{
  // clears from the root (beginning)
  Element_t *element = GetHead();
  while (element != NULL)
  {
    Element_t *currentElement = element;
    element = element->pNext;

    delete currentElement;
  }
}

void PriorityQueue::Insert(int value)
{
  // cycles from the root element to end
  for (Element_t *element = GetHead(); element != NULL; element = element->pNext)
  {
    switch (InsertCase(value, element))
    {
      case 11:
      {
        root = AllocateNewElement(value, element, NULL);
        element->pPrev = root;
        return;
      }
      case 12:
      {
        element->pNext = AllocateNewElement(value, NULL, element);
        return;
      }
      case 21:
      {
        root = AllocateNewElement(value, element, NULL);
        element->pPrev = root;
        return;
      }
      case 22:
      {
        element->pNext->pPrev = AllocateNewElement(value, element->pNext, element);
        element->pNext = element->pNext->pPrev;
        return;
      }
      case 31:
      {
        element->pPrev->pNext = AllocateNewElement(value, element, element->pPrev);
        element->pPrev = element->pPrev->pNext;
        return;
      }
    }
  }

  if (GetHead() == NULL)
    root = AllocateNewElement(value, NULL, NULL);
}

bool PriorityQueue::Remove(int value)
{
  if (Element_t *element = Find(value))
  {
    if (element->value == value)
    {

      // is root
      if (element->pPrev == NULL && element->pNext == NULL)
      {
        root = NULL;
      }

        // is root, but there is also next
      else if (element == GetHead())
      {
        element->pNext->pPrev = NULL;
        root = element->pNext;
      }

        // somewhe in the middle
      else if (element->pPrev != NULL && element->pNext != NULL)
      {
        element->pPrev->pNext = element->pNext;
        element->pNext->pPrev = element->pPrev;
      }

        // last element
      else if (element->pPrev != NULL && element->pNext == NULL)
      {
        element->pPrev->pNext = NULL;
      }

      delete element;
      return true;
    }
  }
  return false;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
  // cycles from the root element to end
  for (Element_t *element = GetHead(); element != NULL; element = element->pNext)
  {
    if (element->value == value)
      return element;
  }
  return NULL;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{

  return root;
}

PriorityQueue::Element_t *PriorityQueue::AllocateNewElement(int value, Element_t *pNext, Element_t *pPrev)
{
  Element_t *element = new Element_t();
  element->value = value;
  element->pPrev = pPrev;
  element->pNext = pNext;

  return element;
}

int PriorityQueue::InsertCase(int value, Element_t *element)
{
  // case 1.0 - only one is in que
  if (element->pPrev == NULL && element->pNext == NULL)
  {
    if (value < element->value)
      return 11;

    if (value >= element->value)
      return 12;
  }

  // case 2.0 - two are in que, on root
  if (element->pPrev == NULL && element->pNext != NULL)
  {
    if (value < element->value)
      return 21;

    if (value >= element->value && value < element->pNext->value)
      return 22;
  }

  // case 3.0 - two are in que, on the last
  if (element->pPrev != NULL && element->pNext == NULL)
  {
    if (value < element->value)
      return 31;

    if (value >= element->value)
      // case 32 is the same as case 12 so it returns 12
      return 12;
  }

  // case 4.0 - three in que, in middle
  if (element->pPrev != NULL && element->pNext != NULL)
  {
    if (value < element->value)
      // case 41 is the same as case 31 so it returns 31
      return 31;

    if (value >= element->value && value < element->pNext->value)
      // case 42 is the same as case 22 so it returns 22
      return 22;
  }
}

/*** Konec souboru tdd_code.cpp ***/
