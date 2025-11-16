#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

const char* dgemv_desc = "OpenMP dgemv.";

/*
 * This routine performs a dgemv operation
 * Y :=  A * X + Y
 * where A is n-by-n matrix stored in row-major format, and X and Y are n by 1 vectors.
 * On exit, A and X maintain their input values.
 */

void my_dgemv(int n, double* A, double* x, double* y) {

   #pragma omp parallel
   {
      int nthreads = omp_get_num_threads();
      int thread_id = omp_get_thread_num();
      printf("my_dgemv(): Hello world: thread %d of %d checking in. \n", thread_id, nthreads);
      printf("my_dgemv(): For actual timing runs, please comment out these printf() and omp_get_*() statements. \n");
   }

   double row;
   #pragma omp parallel for
   for(int i = 0; i < n; i++) {
      double row = 0; // resets/ initialize the start of row i
      for (int j = 0; j < n; j++) {
         // i * n + j is the the pysical version of A[i][j]
         // each row is n elements so we have n x n
         // ex. n = 5, if we are in row 3rd number in row 2, it would be 2n + 3; 2(5) + 3
         row += (A[i * n + j] * x[j]); // adds each column in the row to get Ax[i]
      }
      y[i] += row; // save Ax + whatever Y was into Y
   }
   // insert your dgemv code here. you may need to create additional parallel regions,
   // and you will want to comment out the above parallel code block that prints out
   // nthreads and thread_id so as to not taint your timings

}

