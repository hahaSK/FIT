# CMake generated Testfile for 
# Source directory: /home/juraj/FIT/IVS/ivs_project_1/assignment
# Build directory: /home/juraj/FIT/IVS/ivs_project_1/assignment/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(EmptyTree.InsertNode "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/black_box_test" "--gtest_filter=EmptyTree.InsertNode")
add_test(EmptyTree.DeleteNode "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/black_box_test" "--gtest_filter=EmptyTree.DeleteNode")
add_test(EmptyTree.FindNode "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/black_box_test" "--gtest_filter=EmptyTree.FindNode")
add_test(NonEmptyTree.InsertNode "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/black_box_test" "--gtest_filter=NonEmptyTree.InsertNode")
add_test(NonEmptyTree.DeleteNode "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/black_box_test" "--gtest_filter=NonEmptyTree.DeleteNode")
add_test(NonEmptyTree.FindNode "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/black_box_test" "--gtest_filter=NonEmptyTree.FindNode")
add_test(TreeAxioms.Axiom1 "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/black_box_test" "--gtest_filter=TreeAxioms.Axiom1")
add_test(TreeAxioms.Axiom2 "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/black_box_test" "--gtest_filter=TreeAxioms.Axiom2")
add_test(TreeAxioms.Axiom3 "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/black_box_test" "--gtest_filter=TreeAxioms.Axiom3")
add_test(MatrixTesting.Constructor "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/white_box_test" "--gtest_filter=MatrixTesting.Constructor")
add_test(MatrixTesting.SetValuesVectors "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/white_box_test" "--gtest_filter=MatrixTesting.SetValuesVectors")
add_test(MatrixTesting.SetValue "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/white_box_test" "--gtest_filter=MatrixTesting.SetValue")
add_test(MatrixTesting.GetValue "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/white_box_test" "--gtest_filter=MatrixTesting.GetValue")
add_test(MatrixTesting.Equal "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/white_box_test" "--gtest_filter=MatrixTesting.Equal")
add_test(MatrixTesting.Summing "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/white_box_test" "--gtest_filter=MatrixTesting.Summing")
add_test(MatrixTesting.ScalarMultiplication "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/white_box_test" "--gtest_filter=MatrixTesting.ScalarMultiplication")
add_test(MatrixTesting.Multiplication "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/white_box_test" "--gtest_filter=MatrixTesting.Multiplication")
add_test(MatrixTesting.SolveEquation "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/white_box_test" "--gtest_filter=MatrixTesting.SolveEquation")
add_test(NonEmptyQueue.Insert "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/tdd_test" "--gtest_filter=NonEmptyQueue.Insert")
add_test(NonEmptyQueue.RemoveAllForward "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/tdd_test" "--gtest_filter=NonEmptyQueue.RemoveAllForward")
add_test(NonEmptyQueue.RemoveAllBackward "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/tdd_test" "--gtest_filter=NonEmptyQueue.RemoveAllBackward")
add_test(NonEmptyQueue.Find "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/tdd_test" "--gtest_filter=NonEmptyQueue.Find")
add_test(EmptyQueue.Insert "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/tdd_test" "--gtest_filter=EmptyQueue.Insert")
add_test(EmptyQueue.Remove "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/tdd_test" "--gtest_filter=EmptyQueue.Remove")
add_test(EmptyQueue.Find "/home/juraj/FIT/IVS/ivs_project_1/assignment/build/tdd_test" "--gtest_filter=EmptyQueue.Find")
subdirs("googletest-build")
