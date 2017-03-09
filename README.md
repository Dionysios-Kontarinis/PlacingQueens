PlacingQueens
=============

In this project we have developed an A.I. module which finds a way to **put a maximum number of Queens on a chessboard**,
without any pair of Queens attacking each other.

* The *queens.c* file contains code which translates this problem into *Dimacs* format (https://en.wikipedia.org/wiki/Boolean_satisfiability_problem),
  thus creating a file named *rules.txt*.
  That file contains all the constraints which must be satisfied by the Queens' placements.
  In order to run this, the user enters a parameter (positive integer), representing the size of the chessboard he / she wishes to use.

* Once the *rules.txt* file is produced, the user can use the **SAT solver** of his / her choice, 
  in order to compute a solution (placement of Queens which satisfies all the constraints).
  This solution is a number of integers (positive and negative) ending with a (single) zero,
  and it must be written in a file named *results.txt*, in order to be translated as follows.

* The *queens_solution.c* file contains code which takes the *results.txt* file and it translates the solution into an understandable format:
  it prints a chessboard (containing all the Queens on their respective squares) on the console. 

