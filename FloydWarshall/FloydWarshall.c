#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define oo (INT_MAX) // Infinity

/*Nahian Alam
    1001552659
    Compile:
        gcc -o main alam_nahian_lab6.c
    Run:
        ./main
*/

// There is an error while outputting output b paths. For some reason the code runs into an infinite loop.
// The Tables are being formed correctly for all the data inputs.

int n;              // Number of vertices
int **dist,**successor_odd, **even_successor, **evenD;  // Distance and even_successor matrices

void readInput()
{
// Read weighted edges into adjacency matrix.
    int i,j,k;

    scanf("%d",&n);

    dist=(int**) malloc(n*sizeof(int*));
    successor_odd=(int**) malloc(n*sizeof(int*));
    even_successor=(int**) malloc(n*sizeof(int*));
    evenD = (int**) malloc(n*sizeof(int*));
    if (!dist || !successor_odd)
    {
        printf("dist or succ malloc failed %d\n",__LINE__);
        exit(0);
    }
    for (i=0; i<n; i++)
    {
        dist[i]=(int*) malloc(n*sizeof(int));
        successor_odd[i]=(int*) malloc(n*sizeof(int));
        even_successor[i]=(int*) malloc(n*sizeof(int));

        evenD[i] = (int*) malloc(n*sizeof(int));
        if (!dist[i] || !successor_odd[i])
        {
            printf("dist or succ row malloc failed %d\n",__LINE__);
            exit(0);
        }
    }

    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
        {
            dist[i][j]=oo;
            evenD[i][j] = oo;
            successor_odd[i][j]=j;
            even_successor[i][j]=j;
        }
    while (1)
    {
        scanf("%d %d %d",&i,&j,&k);
        if (i==(-1))
            break;
        dist[i][j]=k;
    }
    printf("Initialized odd matrix:\n");
    for (i=0; i<n; i++)
    {
        printf("%3d ",i);
        for (k=0; k<n; k++)
            if (dist[i][k]<oo)
                printf("%3d %d ",dist[i][k],successor_odd[i][k]);
            else
                printf(" oo   ");
        printf("\n");
    }
}

void printMatrix(int counter)
{
    int i,k;

    printf("Process column %d\nodd matrix\n    ",counter);
    for (i=0; i<n; i++)
        printf("%3d   ",i);
    printf("\n");
    for (i=0; i<n; i++)
    {
        printf("%3d ",i);
        for (k=0; k<n; k++)
            if (dist[i][k]<oo)
                printf("%3d %d ",dist[i][k],successor_odd[i][k]);
            else
                printf(" oo   ");
        printf("\n");
    }
    printf("even matrix\n    ");
    for (i=0; i<n; i++)
        printf("%3d   ",i);
    printf("\n");

    for (i=0; i<n; i++)
    {
        printf("%3d ",i);
        for (k=0; k<n; k++)
            if (evenD[i][k]<oo)
                printf("%3d %d ",evenD[i][k],even_successor[i][k]);
            else
                printf(" oo   ");
        printf("\n");
    }
}

void floydWarshall()
{
    int i,j,k;
    int newDist, newEdist;

    printf("----------------------------------\n");
    /* Floyd-Warshall */
    for (j=0; j<n; j++)
    {

        for (i=0; i<n; i++)
        {


            if (dist[i][j]<oo)
            {


                for (k=0; k<n; k++)
                {


                    if (dist[j][k]<oo)
                    {
                        newDist=dist[i][j]+dist[j][k];

                        if (newDist<evenD[i][k])                //Set Even Matrix Distances and successors.
                        {
                            evenD[i][k]=newDist;
                            even_successor[i][k]=successor_odd[i][j];
                        }

                    }
                if(evenD[j][k]<oo)
                {
                    newDist = dist[i][j]+evenD[j][k];
                    if(newDist<dist[i][k])
                    {
                        dist[i][k] = newDist;
                        successor_odd[i][k] = successor_odd[i][j];
                    }
                }
                }
        }
        }
        for (i=0; i<n; i++)
        {
            if(evenD[i][j]<oo)
            {
                for(k=0; k<n; k++)
                {


                    if (dist[j][k]<oo)
                    {
                        newDist=evenD[i][j]+dist[j][k];

                        if (newDist<dist[i][k])
                        {
                            dist[i][k]=newDist;
                            successor_odd[i][k]=even_successor[i][j];
                        }
                    }
                    if(evenD[j][k]<oo)
                    {
                        newDist = evenD[i][j] + evenD[j][k];
                        if(newDist<evenD[i][k])
                        {
                            evenD[i][k] = newDist;
                            even_successor[i][k] = evenD[i][j];
                        }
                    }
                }
            }
        }
        printMatrix(j);
        printf("----------------------------------\n");
    }
}

void printPaths()
{
    int i,j,k;
    // odd path
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            if (dist[i][j]==oo)
                printf("No odd path from %d to %d\n",i,j);
            else
            {
                printf("Distance %d for %d ",dist[i][j],i);
                for (k=successor_odd[i][j];
                        k!=j;
                        k=successor_odd[k][j])
                    printf("%d ",k);
                printf("%d\n",j);
            }
            //even path
            for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            if (evenD[i][j]==oo)
                printf("No even path from %d to %d\n",i,j);
            else
            {
                printf("Distance %d for %d ",evenD[i][j],i);
                for (k=even_successor[i][j];
                        k!=j;
                        k=even_successor[k][j])
                    printf("%d ",k);
                printf("%d\n",j);
            }
}

void deallocate()
{
    int i;

    for (i=0; i<n; i++)
    {
        free(dist[i]);
        free(successor_odd[i]);
        free(evenD[i]);
        free(even_successor[i]);
    }
    free(dist);
    free(successor_odd);
    free(evenD);
    free(even_successor);
}

int main()
{

    readInput();
    floydWarshall();
    printPaths();
    deallocate();

}
