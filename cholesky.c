#include <stdio.h>
#include <math.h>

int main(){
    float A[100][100], B[100][100], V[100], U[100], X[100], S, F, E, P;
    int i, j, k, n;

    printf("give n:");
    scanf("%d", &n);

    // Enter matrix A
    for (i = 1; i <= n; i++){
        for (j = 1; j <= n; j++){
            printf("give A[%d][%d]:", i, j);
            scanf("%f", &A[i][j]);
        }
    }

    // Display matrix A
    printf("\nMatrix A:\n");
    for (i = 1; i <= n; i++){
        for (j = 1; j <= n; j++)
            printf("%.2f  ", A[i][j]);
        printf("\n");
    }

    // Enter vector U
    for (i = 1; i <= n; i++){
        printf("give U[%d]: ", i);
        scanf("%f", &U[i]);
    }

    // Display vector U
    printf("\nVector U:\n");
    for (i = 1; i <= n; i++)
        printf("%.2f\n", U[i]);

    // Initialize B and X to 0
    for (i = 1; i <= n; i++){
        X[i] = 0;
        for (j = 1; j <= n; j++)
            B[i][j] = 0;
    }

    // Compute B
    for (i = 1; i <= n; i++){
        for (j = 1; j <= n; j++){
            if (i == j){
                // Diagonal element
                S = 0;
                for (k = 1; k <= i-1; k++)
                    S = S + B[i][k] * B[i][k];
                if (A[i][j] - S <= 0){
                    printf("Error: matrix is not positive definite!\n");
                    return 1;
                }
                B[i][j] = sqrt(A[i][j] - S);
            }
            else{
                if (i > j){
                    // Lower triangular element
                    P = 0;
                    for (k = 1; k <= j-1; k++)
                        P = P + B[i][k] * B[j][k];
                    B[i][j] = (A[i][j] - P) / B[j][j];
                }
                else
                    // Upper triangular = 0
                    B[i][j] = 0;
            }
        }
    }

    // Display matrix B
    printf("\nMatrix B:\n");
    for (i = 1; i <= n; i++){
        for (j = 1; j <= n; j++)
            printf("%.2f  ", B[i][j]);
        printf("\n");
    }

    // Forward substitution : B * V = U
    for (i = 1; i <= n; i++){
        E = 0;
        for (k = 1; k <= i-1; k++)
            E = E + B[i][k] * V[k];
        V[i] = (U[i] - E) / B[i][i];
    }

    // Display vector V
    printf("\nVector V:\n");
    for (i = 1; i <= n; i++)
        printf("%.2f\n", V[i]);

    // Backward substitution : Bt * X = V
    for (i = n; i >= 1; i--){
        F = 0;
        for (k = i+1; k <= n; k++)
            F = F + B[k][i] * X[k];
        X[i] = (V[i] - F) / B[i][i];
    }

    // Display solution X
    printf("\nSolution X:\n");
    for (i = 1; i <= n; i++)
        printf("X[%d] = %.2f\n", i, X[i]);

    getchar();
    return 0;
}