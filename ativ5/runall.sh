#!/bin/bash

# Defina o número de iterações
n_iter=10

# Compile os programas com as opções corretas
gcc cod1.c -O3 -o cod1
gcc -mavx -march=native cod2.c -O3 -o cod2 
gcc -mavx -march=native cod3.c -O3 -o cod3
gcc -mavx -march=native cod4.c -O3 -o cod4
gcc -mavx -march=native cod5.c -O3 -o cod5

# Remova arquivos antigos de tempos de execução, se existirem
rm -f execution_times_cod1.txt
rm -f execution_times_cod2.txt
rm -f execution_times_cod3.txt
rm -f execution_times_cod4.txt
rm -f execution_times_cod5.txt

# Execute os programas e registre os tempos
for i in $(seq 1 $n_iter); do
    echo "Running iteration $i"
    echo "Execution $i" >> execution_times_cod1.txt
    echo "Execution $i" >> execution_times_cod2.txt
    echo "Execution $i" >> execution_times_cod3.txt
    echo "Execution $i" >> execution_times_cod4.txt
    echo "Execution $i" >> execution_times_cod5.txt
    ./cod1 >> execution_times_cod1.txt
    ./cod2 >> execution_times_cod2.txt
    ./cod3 >> execution_times_cod3.txt
    ./cod4 >> execution_times_cod4.txt
    ./cod5 >> execution_times_cod5.txt
done
