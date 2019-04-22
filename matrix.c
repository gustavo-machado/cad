#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

    //matrix size
    int n = 2000;

    int i, j; // iterators
    int a[n][n], b[n], result1[n], result2[n];

    srand(time(NULL));

    // first matrix initialization
    for(i = 0; i<n; i++)
    {
        for(j = 0; j<n; j++)
        {
         a[j][i] = rand() % 100;
        }
    }

    //second matrix initialization
    for(i = 0; i<n; i++)
    {
        b[i] = rand() % 100;
    }

    // Initializing all elements of result1 matrix to 0
    for(i=0; i<n; ++i)
      {
        result1[i] = 0;
      }


    // Multiplying matrices a and b and storing result in result matrix
    // initialize clock time
    clock_t begin = clock();
    for(j=0; j<n; ++j)
        for(i=0; i<n; ++i)
          {
              result1[j]+=a[j][i]*b[i];
          }
    //Stop clock time
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    // Initializing all elements of result2 matrix to 0
    for(i=0; i<n; ++i)
      {
        result2[i] = 0;
      }

    //initialize clock time
    begin = clock();
    for(i=0; i<n; ++i)
        for(j=0; j<n; ++j)
          {
              result2[j]+=a[j][i]*b[i];
          }
    //Stop clock time
    end = clock();
    double time_spent2 = (double)(end - begin) / CLOCKS_PER_SEC;
    // Displaying the result
    /*
    printf("\nOutput Matrix:\n");
    for(i=0; i<n; ++i)
        {
            printf("%d  ", result1[i]);
        }
    printf("\n");
    for(i=0; i<n; ++i)
        {
            printf("%d  ", result2[i]);
        }
    */
    //Displaying time time_spent
    printf("\n\nExecution time: %e s\n", time_spent);
    printf("\n\nExecution time: %e s\n", time_spent2);

  return 0;
}
