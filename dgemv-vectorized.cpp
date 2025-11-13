const char* dgemv_desc = "Vectorized implementation of matrix-vector multiply.";

/*
 * This routine performs a dgemv operation
 * Y :=  A * X + Y
 * where A is n-by-n matrix stored in row-major format, and X and Y are n by 1 vectors.
 * On exit, A and X maintain their input values.
 */
void my_dgemv(int n, double* A, double* x, double* y) {
   double row;
   for(int i = 0; i < n; i++) {
      row = 0; // resets/ initialize the start of row i
      for (int j = 0; j < n; j++) {
         // i * n + j is the the pysical version of A[i][j]
         // each row is n elements so we have n x n
         // ex. n = 5, if we are in row 3rd number in row 2, it would be 2n + 3; 2(5) + 3
         row += (A[i * n + j] * x[j]); // adds each column in the row to get Ax[i]
      }
      y[i] += row; // save Ax + whatever Y was into Y
   }
}
