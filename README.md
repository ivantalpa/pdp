# Project Title

## Overview

This project is a parallel computing application that uses Message Passing Interface (MPI) for communication between processes. The application is containerized using Docker, and uses MPICH, an implementation of the MPI standard.

The project is managed using Docker and Docker Compose. It contains exercises and program examples from "PROGRAMARE PARALELĂ ȘI DISTRIBUITĂ" course of UTM.

## Prerequisites

Ensure you have Docker and Docker Compose installed on your system.

## Setup and Run

1. **Build the Docker image**

   You can build the Docker image using Docker Compose with the following command:

   ```bash
   docker-compose build
This command will pull the latest Ubuntu image, install MPICH and bash, and set up the working directory.

2. **Start the Docker container**

   After the image has been built, you can start the Docker container with the following command:

   ```bash
   docker-compose up -d
    ```
    This command will pull the latest Ubuntu image, install MPICH and bash, and set up the working directory.


3. **Compile the program**

   To compile your MPI program, you can execute the following command:

   ```bash
   docker exec -it pdp-mpich_container bash -c "mpicxx home_exercise_3_1.cpp -o home_exercise_3_1"
    ```
   To compile your MPI program, you can execute the following command:

   ```bash
   docker exec -it pdp-mpich_container bash -c "mpicxx home_exercise_3_1.cpp -fopenmp -o home_exercise_3_1"

2. **Run the program**

   You can then run your program with the desired number of processes using the following command:

   ```bash
   docker exec -it pdp-mpich_container bash -c "mpirun -n 12 ./home_exercise_3_1"
    ```
   This command will run the home_exercise_3_1 program with 12 processes.
