/*
    Nahian Alam
    1001552659
    Compile:
        gcc -o main alam_nahian_lab_1.c
    Run:
        ./main
*/

#include<stdlib.h>
#include<stdio.h>
#include <math.h>
int *input; // Array declared globally to store input table from text file
int *linker; // Array declared globally to keep track of the index table
int mergeSort(int start, int count) // Function which breaks down the main tree to corresponding sub trees.
//Start is where the starting point of left tree and count is the end point of the right sub tree.
{

    int left, right, smallest; // Variable left breaks down and handles the left sub tree. Right handles right sub tree.
    // Variable smallest returns the subscript of the sorted smallest value.

    //base case
    if(count == 1) //Sets the linker index to -1 when the tree reaches the bottom.
    {
        linker[start] = -1;
        return start;
    }

    left = mergeSort(start,count/2);  // Breaks down the left subtree recursively
    right = mergeSort(start+(count/2), count-count/2); // Breaks down the right subtree recursively

    smallest = merge(left,right); // Returns the smallest subscript of the sorted tree

    return smallest;
}


int merge(int left,int right)  // Puts back the broken down tree back to its original form
{
    int result;
    if(left == -1)
    {
        return right;
    }
    if(right==-1)
    {
        return left;
    }
    if(input[left]<=input[right])  // If left is <= right, linker is set to the index of the smaller value
    {
        result = left;
        linker[result] = merge(linker[left], right);
    }
    else
    {
        result = right;
        linker[result] = merge(left, linker[right]); // Linker is set to the index of the smaller value
    }
    return result;
}


/* Function to print the desired output arrays */
void printArray(int n,int size)
{
    int i;
    printf("First element is at subscript %d\n",n);
    for (i=0; i < size; i++)
        printf("%d %d %d \n",i, input[i],linker[i]);
    printf("\n");
}




int main()
{

    int length,i;
    scanf("%d",&length);

    input = malloc(sizeof(int)*length); // Sets the size of the dynamically allocated array
    linker = malloc(sizeof(int)*length); // Sets the size of the dynamically allocated array which links the values.

    for(i=0; i<length; i++)
    {
        scanf("%d",input+i); //Takes input from file.
    }



    int n = mergeSort(0,length); // Returns the subscript of the smallest element after the Merge Sort is complete.

    printArray(n, length); // The links are printed.


    return 0;


}
