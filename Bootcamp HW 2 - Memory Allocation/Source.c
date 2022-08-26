#include <stdio.h>
#include<stdlib.h>
#pragma warning (default : 4996)

#define FILE3 "Week2_2_File3.txt"
#define SIZE 10

// Function to open file by serving it's name as a parameter.
FILE* openFile(char* fileName)
{
    FILE* f;
    f = fopen(fileName, "r");
    if (f == NULL)
    {
        printf("Error! Can't open the file.");
        return NULL;
    }
    return f;
}

// Function to allocate memory by the parameters:
// numOf blocks = How many bytes to allocate.
// blocksType = type of data to allocate (i for integer ,c for char).

int* allocate(int* intPTR,char* cPtr, int numOfBlocks, char blocksType)
{
    char* pToChar = NULL;
    int* pToInt = NULL;
    if (blocksType == 'i')
    {
        intPTR = malloc(numOfBlocks * sizeof(int));
        pToInt = intPTR;
    }
    else
    {
        cPtr = malloc(numOfBlocks);
        pToChar = cPtr;
    }
    if (intPTR == NULL && cPtr == NULL) {
        printf("Error Allocating memory!");
        return NULL;
    }
    blocksType == 'i' ? printf("Insert %d integers please: \n",
        numOfBlocks) :
        printf("Insert %d chars please:", numOfBlocks);

    for (int i = 0; i < numOfBlocks; i++)
    {
        if (blocksType == 'i')
        {
            scanf_s("%d", pToInt);
            pToInt++;
        }
        else
        {
            scanf_s(" %c", pToChar);
            pToChar++;
        }
    }
    // return pointer to allocated memory according of Type .
    if (blocksType == 'i')
        return intPTR;
    else
        return cPtr;

}


// Main Function - Start of the program.
int main()
{
    FILE * f3;
    f3 = openFile(FILE3);
    int numOfBlocks = fgetc(f3) - '0'; //Convert char digits to int digits.
    char blocksType = fgetc(f3);
    int* intPtrs[SIZE] = { NULL };  // int pointers array
    char* charPtrs[SIZE]; //char pointers array
    int blocks[SIZE];
    char types[SIZE];
    blocks[0] = numOfBlocks;  
    types[0] = blocksType;
    int i = 0,c=0,index=0;
    while (blocksType != EOF)  //get the text from the file char by char.
    {
        printf("------------------------------------------------\n");
        if (blocksType == 'i'){ //allocate memory for integers.
            intPtrs[i] = allocate(intPtrs[i], NULL, numOfBlocks, blocksType);
        printf("allocation number %d (%d%c):\n", i + 1, numOfBlocks, 
            blocksType);
        printf("memory addres: %p\n\n", intPtrs[i]);
        i++;
    }
        else { // allocate char memory.
            charPtrs[c] = allocate(NULL, charPtrs[c], numOfBlocks, blocksType);
            printf("allocation number %d (%d%c):\n", c + 1, numOfBlocks,
                blocksType);
            printf("memory addres: %p\n\n", charPtrs[c]);
            c++;
        }
        numOfBlocks = fgetc(f3) - '0';
        blocksType = fgetc(f3);
        if (index < SIZE)
        {
            blocks[index + 1] = numOfBlocks;
            types[index + 1] = blocksType;
        }
        index++;
    }
    fclose(f3);

    printf("\n********** print values from allocated memory **************\n");
    for (int intIndex = 0,cIndex=0,j=0; j < SIZE; j++)
    {
        for (int k=0; k < blocks[j];k++) {
            if (types[j] == 'i') {
                printf("%d ", intPtrs[intIndex][k]);
            }
            else {
                printf("%c ", charPtrs[cIndex][k]);
            }
        }
        if (types[j] == 'i')
            intIndex++;
        else
            cIndex++;
        printf("\n");
    }

    // Free Allocated Memory before exiting.
    free(charPtrs[0]);
    for (int freeIndex = 0; freeIndex < SIZE; freeIndex++)
    {
        free(intPtrs[freeIndex]);
        
    }
    printf("\n\n\n\n");

}