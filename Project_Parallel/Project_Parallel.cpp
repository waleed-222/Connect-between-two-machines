// Project_Parallel.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
  Waleed Ebrahem Mohamed Ebrahem
  Sec.3
*/
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

// Function to find maximum in each processor (Local)
int find_local_max(int data[], int local_datasize)
{
    int local_max = data[0];
    for (int i = 1; i < local_datasize; i++)
    {
        if (data[i] > local_max)
            local_max = data[i];
    }
    return local_max;
}

// Find maximum across all processors (Global)
int find_global_max(int local_max)
{
    int global_max;
    MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    return global_max;
}

// Main
int main()
{
    // MPI initialize
    MPI_Init(NULL, NULL);

    // Initialize rank and size
    int rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Initialize data size (30 numbers)
    int global_datasize = 30;

    // Create array of 30 numbers
    int local_datasize = global_datasize / world_size;
    int* data = new int[local_datasize];

    // Find local maximum
    int local_max = find_local_max(data, local_datasize);

    // Find global maximum
    int global_max = find_global_max(local_max);

    // Print result through processor with rank = 0
    if (rank == 0)
    {
        printf("Maximum = %d\n", global_max);
    }

    // Finalize
    MPI_Finalize();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
