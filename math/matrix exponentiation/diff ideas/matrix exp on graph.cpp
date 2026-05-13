/**
* Graph Adjacency Matrix Exponentiation
 * ------------------------------------------------------------------
 * 1) Count Number of Paths with exact length K from (i -> j)
 * -> A[i][j] = 1 if edge exists, 0 otherwise.
 * -> Standard Matrix Multiplication: C[i][j] = sum( A[i][k] * B[k][j] )
 * -> (A^k)[i][j] = number of walks of exactly length K from i to j.
 * ------------------------------------------------------------------
 * 2) Minimum Path Cost with exact length K from (i -> j)
 * -> A[i][j] = weight of edge if exists, INF otherwise.
 * -> Min-Plus Matrix Multiplication: C[i][j] = min( A[i][k] + B[k][j] )
 * -> (A^k)[i][j] = shortest path of exactly length K from i to j.
 * * * Notes for Min-Plus:
 * -> Base matrix: Diagonal A[i][i] is INF if you MUST move.
 * (If staying at the same node is allowed, A[i][i] = 0).
 * -> Identity Matrix (T^0): Diagonal is 0, everything else is INF.
 */