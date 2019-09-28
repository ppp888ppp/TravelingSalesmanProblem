#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int minWeight = 1000000; // set to "huge" number for compare

void swap(int array[], int i, int j)
{
    if (i != j)
    {
        int swap = array[i];
        array[i] = array[j];
        array[j] = swap;
    }
}

void permutation(int i, int n, int weight, int* path, int distance[][n], int* bestPath) //  it can be int path[] or int* path. those are same
{
	int j;
    
    if (i == n)                 //base case for recursion, ONCE IT EXAMINE ONE  POSSIBLE ROUTE, AND CHECK THE IF STATEMENT AND IF IT IS TRUE, THEN UPDATE THE MINWEIGHT AND BESTPATH
    {
        if(minWeight > weight) // IF THE ROUTE IS SMALLER THAN THE PREVIOUS ONE, THEN 
        {
            minWeight = weight; // REPlACE THE MINWEIGHT 
            
            for(j = 0 ; j < n; j++)
            {
                bestPath[j] = path[j]; 
            }  
        }
    }
    else 
    {
        for (j = i; j < n; j++)                      
        {
            int w = 0;                              
    
            w = distance[path[i - 1]][path[j]];     
            
            swap(path, i, j);                       
            permutation(i + 1, n, weight + w, path, distance, bestPath);       
            swap(path, i, j);                       
            
        }
    }
}

void printingResult(int n, int* bestPath, int minWeight)
{	
	int i;
	
	printf("Shortest path is:\n");
    for(i = 0 ; i < n; i++)
    {
        printf("%d ", bestPath[i]);
    }
    printf("\n");
    printf("total weight = %d\n", minWeight);
}

int main(int argc, char* argv[]) // tsm 5 citis5.txt     argv[0] = tsm 		argv[1] = 5 	argv[2] = cities5.txt
{
    int i;
    int j;
    
    int n = atoi(argv[1]); // FROM THE COMMAND LINE INPUT, TAKE THE CITY NUMBER, AND CHANGE THE "STRING" TYPE TO INT
    
	int path[n]; // path 
    int distance[n][n]; // WE READ THE FILE AND PUT IT IN TO 2D ARRAY
    
    int bestPath[n]; // bestpath

	//INITIALIZING THE PATH AND BESTPATH
    for (i = 0; i < n; i++)
    {
        path[i] = i;      // INITIALIZING THE PATH WITH THE NUMBER OF CITY
        bestPath[i] = 0; // initialize the bestPath
    }
    
	//FILE SCANNING PART
	FILE *fptr;
    char* filename = argv[2];
    fptr = fopen(filename, "r"); // now the file pointer fp pointing to the filename
    
    if (fptr == NULL){
        printf ("failed to open the file: %s", filename);
    }
    for (i = 0; i < n; i++) {

        for (j = 0; j < n; j++) 
		{
            fscanf (fptr, "%d", &distance[i][j]);  // fp scan decimal values and put those into 2darray 
        }
    }
    fclose(fptr);

    //CALLING PERMUTATION RECUSRIVELY
    permutation(1, n, 0, path, distance, bestPath); //   start, number of city, weight,  path , 2d array, bestPath )
    
    // PRINT the result
    printingResult(n, bestPath, minWeight); 
    
    return 0;
}

