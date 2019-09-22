/*
    Nahian Alam
    1001552659
    Compile:
        gcc -o main alam_nahian_lab2.c
    Run:
        ./main
*/



#include <stdio.h>
#include <stdlib.h>


int *start;
int *finish;
int *weight;
int **M;
int *p;

void build_table(int length);
void arrange_final_table(int length);
int max(int a,int b) // Function that returns the higher of the two values
{
    if (a>b)
        return a;
    return b;
}


// Function to print the 2D Dynamic Table M
void print_Array(int length)
{
    int i, j = 0;
    printf("  M");
    for (i = 0; i <= length; i++)
        printf("%3d", i);
    for (i = 0; i <= length; i++)
    {
        printf("\n%3d", i);
        for (j = 0; j <= length; j++)
            printf("%3d", M[i][j]);
    }
    printf("\n");
}

int binSearchLast(int *a,int n,int key)
{

    int low,high,mid;
    low=0;
    high=n-1;
    while (low<=high)
    {
        mid=(low+high)/2;
        if (a[mid]<=key)
            low=mid+1;
        else
            high=mid-1;
    }
    return high;
}

//deallocate a 2D array
void deallocate2D(int** arr2D,int rows)
{
    int i;

    for(i=0;i<rows+1;i++)
    {
        free(arr2D[i]);
    }

    free(arr2D);
}

int main()
{
    int i,length;
    scanf("%d",&length);
    finish = malloc( length*sizeof(int *) ); // Allocating the length of finish array
    start = malloc( length*sizeof(int *) ); // Allocating the length of start array
    weight = malloc( length*sizeof(int *) ); // Allocating the length of weight array
    p = malloc( length*sizeof(int *) ); // Allocating the length of p array
    M =  malloc( length*sizeof(int *) ); // Allocating the length of M 2D array dynamically
    for(i=0; i<=length; i++)
    {
        M[i] = (int *)malloc(length*sizeof(int)); // 2D Dynamic allocation

    }
    //Getting input from the text files using UNIX shell
    for (i=1; i<=length; i++)
        scanf("%d %d %d",&start[i],&finish[i],&weight[i]);
    for (i=2; i<=length && finish[i-1]<=finish[i]; i++);

    for (i=1; i<=length; i++)
        p[i]=binSearchLast(finish,length+1,start[i]);
    printf("%d\n",length);
    for (i=1; i<=length; i++)
        printf("%d %d %d\n",start[i],finish[i],weight[i]); //Printing the input that was just taken in


    // build dynamic programming table M using the weight

    build_table(length);

    print_Array(length); //Print the M Array

    arrange_final_table(length); //Rearranging the M array and making sub tables to print final table that provides sum


    //Prevention of memory leaks!

    free(start);
    free(finish);
    free(weight);
    free(p);
    return 0;

}
void build_table(int length) // Function that builds the 2D Dynamic Table M
{
    int i,j;
    for (i = 0; i <= length; i++)
    {
        for (j = 0; j <= length; j++)
        {
            if (j<i)
                M[i][j] = max(weight[i] + M[p[i]][j], M[i - 1][j]);
            else if (i<j)
                M[i][j] = max(weight[j] + M[i][p[j]], M[i][j - 1]);
            else if (i != 0 && j != 0)
                M[i][j] = M[i - 1][j];
            else
                M[i][j] = 0;
        }
    }
}
void arrange_final_table(int length) // Function that Arranges the final weight and tabulates it for final output requirement
{
    int i;
    int final_table1[length], final_table2[length];
    int Tracker1 = 0, Tracker2 = 0;
    int table1 = finish[length];
    int table2 = finish[length];
    for (i = length; i > 0; i--)
    {
        if (M[i][i] > M[i - 1][i - 1])
        {
            if (table1 >= finish[i])
            {
                final_table1[Tracker1] = i;
                Tracker1++;
                table1 = start[i];
            }
            else if (table2 >= finish[i])
            {


                final_table2[Tracker2] = i;
                Tracker2++;
                table2 = start[i];
            }
        }
    }
    printf("%d\n", Tracker1);
    for (i = Tracker1 - 1; i >= 0; i--)
        printf("%d %d %d\n", start[final_table1[i]], finish[final_table1[i]], weight[final_table1[i]]);
    printf("%d\n", Tracker2);
    for (i = Tracker2 - 1; i >= 0; i--)
        printf("%d %d %d\n", start[final_table2[i]], finish[final_table2[i]], weight[final_table2[i]]);
    printf("%d\n", M[length][length]);
}
