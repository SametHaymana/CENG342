#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <mpi.h>

void generateVector(double **vect, int cols) {
    srand(200501);
    *vect = (double *)malloc(cols * sizeof(double));
    for (int i = 0; i < cols; i++) {
        (*vect)[i] = ((double)rand() / RAND_MAX) * (100 - 1) + 1;
    }
}

void generateMatrix(double ***mat, int rows, int cols) {
    srand(11074);
    *mat = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        (*mat)[i] = (double *)malloc(cols * sizeof(double));
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            (*mat)[i][j] = ((double)rand() / RAND_MAX) * (100 - 1) + 1;
        }
    }
}

void writeToFile(char *filename, double *arr, int length) {
    FILE *file;
    file = fopen(filename, "w");
    for (int i = 0; i < length; i++) {
        fprintf(file, "%.2f\n", arr[i]);
    }
    fclose(file);
}

double *multiplyMatrixVector(double **matrix, double *vector, int rows, int cols, int processRank, int processCount) {
    double *res = (double *)malloc(rows * sizeof(double));
    MPI_Barrier(MPI_COMM_WORLD);
    double start = MPI_Wtime();
    for (int i = processRank; i < rows; i += processCount) {
        res[i] = 0;
        for (int j = 0; j < cols; j++) {
            res[i] += matrix[i][j] * vector[j];
        }
    }
    double *finalRes = NULL;
    if (processRank == 0) {
        finalRes = (double *)malloc(rows * sizeof(double));
        for(int b = 0; b < rows; b++){
            finalRes[b] = 0;
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Reduce(res, finalRes, rows, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (processRank == 0) {
        double end = MPI_Wtime();
        printf("Process Amount: %d, Time: %f seconds\n", processCount, end - start);
    }
    return finalRes;
}

int main(int argc, char **argv) {
    int processRank, processCount;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &processRank);
    MPI_Comm_size(MPI_COMM_WORLD, &processCount);

    if (argc < 4) {
        printf("Not enough data.");
        return 1;
    }
    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    char *outputFilename = argv[3];

    double **matrix, *vector;

    generateMatrix(&matrix, rows, cols);
    generateVector(&vector, cols);
    double *result = multiplyMatrixVector(matrix, vector, rows, cols, processRank, processCount);

    if (processRank == 0) {
        writeToFile(outputFilename, result, rows);
    }

    MPI_Finalize();

    return 0;
}