#include <stdio.h>

#define B 3   
#define M 12   


void input(double arr[B][M]);
double getTotal(double arr[B][M]);
void printShares(double arr[B][M], double total);
void sortData(double arr[B][M], int type); 

int main() {
    double sales[B][M] = {0};
    int choice;
    char cont = 'y';

    while (cont == 'y' || cont == 'Y') {
        printf("\n1.Input | 2.Total | 3.Shares | 4.Peak | 5.Sort Branches | 6.Sort Months | 7.Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 7) break;

        if (choice == 1) input(sales);
        else if (choice == 2) printf("Total: $%.2f\n", getTotal(sales));
        else if (choice == 3) printShares(sales, getTotal(sales));
        else if (choice == 4) {
            
            double maxS = -1; int peak = 0;
            for (int j = 0; j < M; j++) {
                double sum = 0;
                for (int i = 0; i < B; i++) sum += sales[i][j];
                if (sum > maxS) { maxS = sum; peak = j; }
            }
            printf("Peak Month is: %d ($%.2f)\n", peak + 1, maxS);
        }
        else if (choice == 5) sortData(sales, 5);
        else if (choice == 6) sortData(sales, 6);
        else printf("Invalid!\n");

        printf("Continue? (y/n): ");
        scanf(" %c", &cont);
    }
    return 0;
}


void input(double arr[B][M]) {
    for (int i = 0; i < B; i++) {
        for (int j = 0; j < M; j++) {
            printf("Branch %d, Month %d: ", i + 1, j + 1);
            scanf("%lf", &arr[i][j]);
        }
    }
}


double getTotal(double arr[B][M]) {
    double t = 0;
    for (int i = 0; i < B; i++)
        for (int j = 0; j < M; j++) t += arr[i][j];
    return t;
}


void printShares(double arr[B][M], double total) {
    if (total == 0) { printf("No data!\n"); return; }
    for (int i = 0; i < B; i++) {
        double bSum = 0;
        for (int j = 0; j < M; j++) bSum += arr[i][j];
        printf("Branch %d Share: %.2f%%\n", i + 1, (bSum / total) * 100);
    }
}


void sortData(double arr[B][M], int type) {
    int size = (type == 5) ? B : M;
    double val[12]; int idx[12];
    int target;

    printf("Enter Index: ");
    scanf("%d", &target);
    target--; 


    for (int i = 0; i < size; i++) {
        idx[i] = i + 1;
        val[i] = (type == 5) ? arr[i][target] : arr[target][i];
    }


    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (val[j] < val[j + 1]) {
                double tV = val[j]; val[j] = val[j + 1]; val[j + 1] = tV;
                int tI = idx[j]; idx[j] = idx[j + 1]; idx[j + 1] = tI;
            }
        }
    }


    for (int i = 0; i < size; i++) 
        printf("%s %d: $%.2f\n", (type == 5) ? "Branch" : "Month", idx[i], val[i]);
}
