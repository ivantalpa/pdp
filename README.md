# PROGRAMARE PARALELĂ ȘI DISTRIBUITĂ

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



### Exempluri
- [Exemplul 10.1](exercises/exercise_10_1.cpp)
- [Exemplul 10.1](exercises/exercise_10_1_worker.cpp)
- [Exemplul 10.2](exercises/exercise_10_2.cpp)
- [Exemplul 10.2](exercises/exercise_10_2_spawn_worker1.cpp)
- [Exemplul 10.3](exercises/exercise_10_3.cpp)
- [Exemplul 10.3](exercises/exercise_10_3_comunication_worker.cpp)
- [Exemplul 10.4](exercises/exercise_10_4.cpp)
- [Exemplul 10.4](exercises/exercise_10_4_comunication_worker_v1.cpp)
- [Exemplul 11.1](exercises/exercise_11_1.cpp)
- [Exemplul 12.1](exercises/exercise_12_1.cpp)
- [Exemplul 13.1](exercises/exercise_13_1.cpp)
- [Exemplul 13.2](exercises/exercise_13_2.cpp)
- [Exemplul 13.3](exercises/exercise_13_3.cpp)
- [Exemplul 13.4](exercises/exercise_13_4.cpp)
- [Exemplul 14.1.1](exercises/exercise_14_1_1.cpp)
- [Exemplul 14.1.2](exercises/exercise_14_1_2.cpp)
- [Exemplul 14.1.3](exercises/exercise_14_1_3.cpp)
- [Exemplul 14.1.4](exercises/exercise_14_1_4.cpp)
- [Exemplul 14.1.5](exercises/exercise_14_1_5.cpp)
- [Exemplul 14.1.6](exercises/exercise_14_1_6.cpp)
- [Exemplul 14.1.7](exercises/exercise_14_1_7.cpp)
- [Exemplul 15.2.1](exercises/exercise_15_2_1.cpp)
- [Exemplul 15.4.1](exercises/exercise_15_4_1.cpp)
- [Exemplul 15.4.2](exercises/exercise_15_4_2.cpp)
- [Exemplul 15.5.1](exercises/exercise_15_5_1.cpp)
- [Exemplul 15.6.1](exercises/exercise_15_6_1.cpp)
- [Exemplul 16.2.1](exercises/exercise_16_2_1.cpp)
- [Exemplul 16.2.2](exercises/exercise_16_2_2.cpp)
- [Exemplul 16.2.3](exercises/exercise_16_2_3.cpp)
- [Exemplul 5.2.a](exercises/exercise_52a.cpp)

### Exercitii
- [Exercițiul 3.1](exercises/home_exercise_3_1.cpp)
- [Exercițiul 3.2](exercises/home_exercise_3_2.cpp)
- [Exercițiul 3.3](exercises/home_exercise_3_3.cpp)
- [Exercițiul 3.4](exercises/home_exercise_3_4.cpp)
- [Exercițiul 3.5](exercises/home_exercise_3_5.cpp)
- [Exercițiul 4.1](exercises/home_exercise_4_1.cpp)
- [Exercițiul 4.2](exercises/home_exercise_4_2.cpp)
- [Exercițiul 4.3.a](exercises/home_exercise_4_3a.cpp)
- [Exercițiul 4.3.b](exercises/home_exercise_4_3b.cpp)
- [Exercițiul 4.4.a](exercises/home_exercise_4_4a.cpp)
- [Exercițiul 4.4.b](exercises/home_exercise_4_4b.cpp)
- [Exercițiul 5.1](exercises/home_exercise_5_1.cpp)
- [Exercițiul 5.2](exercises/home_exercise_5_2.cpp)
- [Exercițiul 5.3](exercises/home_exercise_5_3.cpp)
- [Exercițiul 5.4](exercises/home_exercise_5_4.cpp)
- [Exercițiul 7.1](exercises/home_exercise_7_1.cpp)
- [Exercițiul 7.2](exercises/home_exercise_7_2.cpp)
- [Exercițiul 7.3](exercises/home_exercise_7_3.cpp)
- [Exercițiul 7.4](exercises/home_exercise_7_4.cpp)
- [Exercițiul 7.5](exercises/home_exercise_7_5.cpp)
- [Exercițiul 7.6](exercises/home_exercise_7_6.cpp)

