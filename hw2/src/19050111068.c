#include <stdio.h>
#include <time.h>
#include <stdlib.h>


void fillVector(int val1, double *array){

    double random;
    long int  number= 1870241884;


    srand (number);
    

    for(int i = 0; i < val1; i++)
    {

            random = ((double) rand() / RAND_MAX) * (100 - 1) + 1;
            array[i] =  random;
                    
    }


}


double* calculate(int val1, int val2, double **array){

    double vector[val2];
    double *result =  malloc(val1 * sizeof(double));;


    fillVector(val2,vector);

    for(int i = 0; i < val1; i++)
    {
        for(int j = 0; j < val2; j++)
        {

            result[i] += array[i][j] * vector[j];
        }                  
    }

    return result;

}


void fillArray(int val1, int val2, double **array){

    double random;
    long int  number= 1870241884;

    srand (number);
    

    for(int i = 0; i < val1; i++)
    {
        for(int j = 0; j < val2; j++)
        {

            random = ((double) rand() / RAND_MAX) * (100 - 1) + 1;
            array[i][j] =  random;
        }                  
    }


}



void createMatrix(int val1, int val2, char *outFile){

    // Create to dimentional 

    double **arr = malloc( (val1 * val2) * sizeof(double));
    
    fillArray(val1,val2,arr);

    double *result;
    
    result = calculate( val1, val2,arr);


    FILE *f = fopen("client.data", "w");

    for(int i = 0 ; i< val1 ; i++){
        fprintf(f,"%f",result[i]);
    }
    fclose(f);


}


int main(int argc, char *argv[]){


    if(argc < 3 ){
        printf("You must give input");
    }
    else{
        int val1 = atoi(argv[1]);
        int val2 = atoi(argv[2]);
        char *outFile = argv[3];


        createMatrix(val1, val2,outFile );
        
    }

    return 0;
}