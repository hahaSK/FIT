//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     Juraj Lahvicka <xlahvi00@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Juraj Lahvicka
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

namespace WhiteBoxTesting
{
    class MatrixTesting : public ::testing::Test
    {
    protected:
        Matrix matrix;

        std::vector<std::vector<double> > matrix4x4Values = {
                {6,  7,  8,  9},
                {12, 22, 5,  2},
                {13, 1,  24, 33},
                {42, 4,  17, 18},

        };

        std::vector<std::vector<double> > matrix2x2Values = {
                {6,  7},
                {12, 22},
        };

        std::vector<std::vector<double> > matrix3x1Values = {
                {6},
                {12},
                {42},
        };

        std::vector<std::vector<double> > matrix1x2Values = {
                {6, 42},
        };

        std::vector<std::vector<double> > matrix4x1Values = {
                {8},
                {13},
                {42},
                {1},
        };

        std::vector<std::vector<double> > matrix3x3Values = {
                {6,  7,  8},
                {12, 22, 5},
                {42, 4,  17},

        };

        std::vector<std::vector<double> > singularMatrix4x4Values = {
                {42, 4,  17, 18},
                {12, 22, 5,  2},
                {13, 1,  24, 33},
                {42, 4,  17, 18},

        };


        Matrix getMatrix4x4()
        {
          Matrix matrix = Matrix(4, 4);
          matrix.set(matrix4x4Values);
          return matrix;
        }

        Matrix getMatrix2x2()
        {
          Matrix matrix = Matrix(2, 2);
          matrix.set(matrix2x2Values);
          return matrix;
        }

        Matrix getMatrix3x1()
        {
          Matrix matrix = Matrix(3, 1);
          matrix.set(matrix3x1Values);
          return matrix;
        }

        Matrix getMatrix1x2()
        {
          Matrix matrix = Matrix(1, 2);
          matrix.set(matrix1x2Values);
          return matrix;
        }

        Matrix getMatrix4x1()
        {
          Matrix matrix = Matrix(4, 1);
          matrix.set(matrix4x1Values);
          return matrix;
        }

        Matrix getMatrix3x3()
        {
          Matrix matrix = Matrix(3, 3);
          matrix.set(matrix3x3Values);
          return matrix;
        }

        Matrix getSingularMatrix4x4()
        {
          Matrix matrix = Matrix(4, 4);
          matrix.set(singularMatrix4x4Values);
          return matrix;
        }

        /**
        * function generates random double number from specified interval
        * @param fMin - the lower value of interval
        * @param fMax - the upper value of interval
        * @return random double number
        */
        double fRand(double fMin, double fMax)
        {
          double f = (double) rand() / RAND_MAX;
          return fMin + f * (fMax - fMin);
        }

        /**
         * resizing 2D vector
         * @param vec - vector
         * @param ROWS
         * @param COLUMNS
         */
        void resizeVec(std::vector<std::vector<double> > &vec, const unsigned int ROWS, const unsigned int COLUMNS)
        {
          vec.resize(ROWS);
          for (std::vector<std::vector<double> >::iterator it = vec.begin(); it != vec.end(); ++it)
          {
            it->resize(COLUMNS);
          }
        }

    };


    TEST_F(MatrixTesting, Constructor)
    {

      ASSERT_NO_THROW(Matrix());
      EXPECT_NO_THROW(Matrix(1, 1));
      EXPECT_NO_THROW(Matrix(5, 7));
      EXPECT_NO_THROW(Matrix(26, 33));

      EXPECT_ANY_THROW(Matrix(0, 1));
      EXPECT_ANY_THROW(Matrix(1, 0));
      EXPECT_ANY_THROW(Matrix(0, 0));
      EXPECT_ANY_THROW(Matrix(-2, -5));

    }

    TEST_F(MatrixTesting, SetValuesVectors)
    {

      int rows = 4, columns = 4;
      ASSERT_NO_THROW(Matrix(rows, columns));

      ASSERT_NO_THROW(matrix.set(matrix4x4Values));

    }

    TEST_F(MatrixTesting, SetValue)
    {
      int rows = 4, columns = 4;

      Matrix setValueMatrix = Matrix(rows, columns);

      for (int r = 0; r < rows; r++)
      {
        for (int c = 0; c < columns; c++)
        {
          // fRand randomly generates double number
          EXPECT_TRUE(setValueMatrix.set(r, c, fRand(-10, 10)));
        }
      }

      EXPECT_FALSE(setValueMatrix.set(rows + 1, 0, -5.0));
      EXPECT_FALSE(setValueMatrix.set(0, columns + 1, -5.0));
      EXPECT_FALSE(setValueMatrix.set(rows + 1, columns + 1, -5.0));

    }

    TEST_F(MatrixTesting, GetValue)
    {
      int rows = 4, columns = 4;
      ASSERT_NO_THROW(getMatrix4x4());
      Matrix matrix4x4 = getMatrix4x4();

      for (int r = 0; r < rows; r++)
      {
        for (int c = 0; c < columns; c++)
        {
          EXPECT_NO_THROW(matrix4x4.get(r, c));
          EXPECT_EQ(matrix4x4.get(r, c), matrix4x4Values[r][c]);
        }
      }

      // non-existing index
      EXPECT_TRUE(std::isnan(matrix4x4.get(rows + 1, 0))) << "Should throw an exception";
      EXPECT_TRUE(std::isnan(matrix4x4.get(0, columns + 1))) << "Should throw an exception";
      EXPECT_TRUE(std::isnan(matrix4x4.get(rows + 1, columns + 1))) << "Should throw an exception";

    }

    TEST_F(MatrixTesting, Equal)
    {
      Matrix matrix2x2 = getMatrix2x2();
      Matrix matrix4x4 = getMatrix4x4();
      Matrix matrix3x1 = getMatrix3x1();

      EXPECT_ANY_THROW(matrix3x1 == matrix2x2);
      EXPECT_ANY_THROW(matrix4x4 == matrix2x2);
      EXPECT_ANY_THROW(matrix3x1 == matrix4x4);

      ASSERT_TRUE(matrix3x1 == matrix3x1);
      ASSERT_TRUE(matrix4x4 == matrix4x4);
      ASSERT_TRUE(matrix2x2 == matrix2x2);

      Matrix modifiedMatrix4x4 = matrix4x4;
      EXPECT_TRUE(modifiedMatrix4x4.set(1, 2, 1.7));
      EXPECT_FALSE(matrix4x4 == modifiedMatrix4x4);

    }

    TEST_F(MatrixTesting, Summing)
    {
      Matrix matrix2x2 = getMatrix2x2();
      Matrix matrix4x4 = getMatrix4x4();
      Matrix matrix3x1 = getMatrix3x1();

      EXPECT_ANY_THROW(matrix3x1 + matrix2x2);
      EXPECT_ANY_THROW(matrix4x4 + matrix2x2);
      EXPECT_ANY_THROW(matrix3x1 + matrix4x4);

      /// 4x4
      EXPECT_NO_THROW(matrix4x4 + matrix4x4);

      int rows = 4, columns = 4;
      std::vector<std::vector<double> > summingResult;
      resizeVec(summingResult, rows, columns);

      for (int r = 0; r < rows; r++)
      {
        for (int c = 0; c < columns; c++)
        {
          summingResult[r][c] = matrix4x4Values[r][c] * 2;
        }
      }

      Matrix matrix4x4SummingResult = Matrix(rows, columns);
      matrix4x4SummingResult.set(summingResult);

      EXPECT_TRUE(matrix4x4SummingResult == matrix4x4 + matrix4x4);


      /// 2x2
      EXPECT_NO_THROW(matrix2x2 + matrix2x2);
      rows = 2, columns = 2;
      resizeVec(summingResult, rows, columns);

      for (int r = 0; r < rows; r++)
      {
        for (int c = 0; c < columns; c++)
        {
          summingResult[r][c] = matrix2x2Values[r][c] * 2;
        }
      }

      Matrix matrix2x2SummingResult = Matrix(rows, columns);
      matrix2x2SummingResult.set(summingResult);

      EXPECT_TRUE(matrix2x2SummingResult == matrix2x2 + matrix2x2);


      /// 3x1
      EXPECT_NO_THROW(matrix3x1 + matrix3x1);
      rows = 3, columns = 1;
      resizeVec(summingResult, rows, columns);

      for (int r = 0; r < rows; r++)
      {
        for (int c = 0; c < columns; c++)
        {
          summingResult[r][c] = matrix3x1Values[r][c] * 2;
        }
      }

      Matrix matrix3x1SummingResult = Matrix(rows, columns);
      matrix3x1SummingResult.set(summingResult);

      EXPECT_TRUE(matrix3x1SummingResult == matrix3x1 + matrix3x1);

    }

    TEST_F(MatrixTesting, ScalarMultiplication)
    {
      Matrix matrix4x4 = getMatrix4x4();
      Matrix matrix3x1 = getMatrix3x1();

      /// 4x4
      double multiply = 5;
      int rows = 4, columns = 4;
      std::vector<std::vector<double> > multiplicationResult;
      resizeVec(multiplicationResult, rows, columns);

      for (int r = 0; r < rows; r++)
      {
        for (int c = 0; c < columns; c++)
        {
          multiplicationResult[r][c] = matrix4x4Values[r][c] * multiply;
        }
      }

      Matrix matrix4x4MultiplicationResult = Matrix(rows, columns);
      matrix4x4MultiplicationResult.set(multiplicationResult);

      EXPECT_TRUE(matrix4x4MultiplicationResult == matrix4x4 * multiply);

      multiply = 2;

      for (int r = 0; r < rows; r++)
      {
        for (int c = 0; c < columns; c++)
        {
          multiplicationResult[r][c] = matrix4x4Values[r][c] * multiply;
        }
      }

      matrix4x4MultiplicationResult.set(multiplicationResult);

      EXPECT_TRUE(matrix4x4MultiplicationResult == matrix4x4 * multiply);


      /// 3x1
      multiply = 5;
      rows = 3, columns = 1;
      resizeVec(multiplicationResult, rows, columns);

      for (int r = 0; r < rows; r++)
      {
        for (int c = 0; c < columns; c++)
        {
          multiplicationResult[r][c] = matrix3x1Values[r][c] * multiply;
        }
      }

      Matrix matrix3x1MultiplicationResult = Matrix(rows, columns);
      matrix3x1MultiplicationResult.set(multiplicationResult);

      EXPECT_TRUE(matrix3x1MultiplicationResult == matrix3x1 * multiply);

      multiply = 2;
      resizeVec(multiplicationResult, rows, columns);

      for (int r = 0; r < rows; r++)
      {
        for (int c = 0; c < columns; c++)
        {
          multiplicationResult[r][c] = matrix3x1Values[r][c] * multiply;
        }
      }

      matrix3x1MultiplicationResult.set(multiplicationResult);

      EXPECT_TRUE(matrix3x1MultiplicationResult == matrix3x1 * multiply);

    }

    TEST_F(MatrixTesting, Multiplication)
    {
      Matrix matrix2x2 = getMatrix2x2();
      Matrix matrix4x4 = getMatrix4x4();
      Matrix matrix3x1 = getMatrix3x1();
      Matrix matrix1x2 = getMatrix1x2();
      Matrix matrix4x1 = getMatrix4x1();

      EXPECT_ANY_THROW(matrix2x2 * matrix4x4);
      EXPECT_ANY_THROW(matrix3x1 * matrix4x4);
      EXPECT_ANY_THROW(matrix3x1 * matrix2x2);

      /// 2x2 * 2x2
      Matrix matrixMultiplicationResult = Matrix(2, 2);
      matrixMultiplicationResult.set(std::vector<std::vector<double> >{
              {120, 196},
              {336, 568},
      });

      EXPECT_NO_THROW(matrixMultiplicationResult == matrix2x2 * matrix2x2);
      EXPECT_TRUE(matrixMultiplicationResult == matrix2x2 * matrix2x2);


      /// 3x1 * 1x2
      matrixMultiplicationResult = Matrix(3, 2);
      matrixMultiplicationResult.set(std::vector<std::vector<double> >{
              {36,  252},
              {72,  504},
              {252, 1764},
      });

      EXPECT_NO_THROW(matrixMultiplicationResult == matrix3x1 * matrix1x2);
      EXPECT_TRUE(matrixMultiplicationResult == matrix3x1 * matrix1x2);


      /// 4x4 * 4x1
      matrixMultiplicationResult = Matrix(4, 1);
      matrixMultiplicationResult.set(std::vector<std::vector<double> >{
              {484},
              {594},
              {1158},
              {1120},
      });

      EXPECT_NO_THROW(matrixMultiplicationResult == matrix4x4 * matrix4x1);
      Matrix testsssss = matrix4x4 * matrix4x1;
      EXPECT_TRUE(matrixMultiplicationResult == matrix4x4 * matrix4x1);

    }

    TEST_F(MatrixTesting, SolveEquation)
    {
      Matrix matrix4x4 = getMatrix4x4();
      Matrix matrix3x1 = getMatrix3x1();
      Matrix matrix2x2 = getMatrix2x2();
      Matrix matrix3x3 = getMatrix3x3();
      Matrix singularMatrix4x4 = getSingularMatrix4x4();

      // right side of equation should have same number of parameters as matrix rows
      EXPECT_ANY_THROW(matrix4x4.solveEquation(std::vector<double>{}));
      EXPECT_ANY_THROW(matrix4x4.solveEquation(std::vector<double>{2, 1}));

      // matrix needs to be square
      ///FIXME right side of equation should have same number of parameters as matrix rows,
      /// but in white_box_code.cpp the first if checks, if the COLUMNS are equal with number of paramters on the right side of equation
      EXPECT_ANY_THROW(matrix3x1.solveEquation(std::vector<double>{2}));

      // singular matrix
      EXPECT_ANY_THROW(singularMatrix4x4.solveEquation(std::vector<double>{2, 1, 3, 4}));

      /// Cramer's rule http://matrix.reshish.com/cramSolution.php
      // solve equation for matrix 4x4
      std::vector<double> equationResult = {-832.0 / 5601.0, -2599.0 / 11202.0, 11965.0 / 5601.0, -5217.0 / 3734.0};
      EXPECT_NO_THROW(matrix4x4.solveEquation(std::vector<double>{2, 1, 3, 4}));
      EXPECT_EQ(matrix4x4.solveEquation(std::vector<double>{2, 1, 3, 4}), equationResult);

      // solve equation for matrix 2x2
      equationResult = {37.0 / 48.0, -3.0 / 8.0};
      EXPECT_NO_THROW(matrix2x2.solveEquation(std::vector<double>{2, 1}));
      EXPECT_EQ(matrix2x2.solveEquation(std::vector<double>{2, 1}), equationResult);

      // solve equation for matrix 1x1
      Matrix matrix1x1 = Matrix();
      matrix1x1.set(0, 0, 2);
      equationResult = {1.0 / 2.0};
      EXPECT_NO_THROW(matrix1x1.solveEquation(std::vector<double>{1}));
      EXPECT_EQ(matrix1x1.solveEquation(std::vector<double>{1}), equationResult);

      // solve equation for matrix 3x3
      equationResult = {-19.0 / 1614.0, -7.0 / 807.0, 215.0 / 807.0};
      EXPECT_NO_THROW(matrix3x3.solveEquation(std::vector<double>{2, 1, 4}));
      EXPECT_EQ(matrix3x3.solveEquation(std::vector<double>{2, 1, 4}), equationResult);

    }

}

/*** Konec souboru white_box_tests.cpp ***/
