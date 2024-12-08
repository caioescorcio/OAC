n_iter=10


gcc cod1.c -o cod1
gcc -mavx -march=native cod2.c -o cod2
gcc -mavx -march=native cod3.c -o cod3
gcc -mavx -march=native cod4.c -o cod4
gcc -mavx -march=native cod5.c -o cod5

rm execution_times_cod1.txt
rm execution_times_cod2.txt
rm execution_times_cod3.txt
rm execution_times_cod4.txt
rm execution_times_cod5.txt


for i in $(seq 1 $n_iter); do
    echo "Running iteration $i"
    echo "Execution $i" >> execution_times_cod1.txt
    echo "Execution $i" >> execution_times_cod2.txt
    echo "Execution $i" >> execution_times_cod3.txt
    echo "Execution $i" >> execution_times_cod4.txt
    echo "Execution $i" >> execution_times_cod5.txt
    ./cod1
    ./cod2
    ./cod3
    ./cod4
    ./cod5
done
