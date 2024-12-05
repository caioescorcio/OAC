n_iter=10

gcc matrices.c cod2.c -o cod2
gcc -mavx -march=native matrices.c cod3.c -o cod3
gcc -mavx -march=native matrices.c cod4.c -o cod4
gcc -mavx -march=native matrices.c cod5.c -o cod5

rm cod1_time.txt
rm cod2_time.txt
rm cod3_time.txt
rm cod4_time.txt
rm cod5_time.txt


for i in $(seq 1 $n_iter); do
    echo "Running iteration $i"
    start=$(date +%s%N)   # Get current time in nanoseconds
    { time -p python cod1.py; } 
    end=$(date +%s%N)
    elapsed=$((end - start))
    echo "$elapsed" >> cod1_time.txt

    start=$(date +%s%N)   # Get current time in nanoseconds
    { time -p ./cod2; } 
    end=$(date +%s%N)
    elapsed=$((end - start))
    echo "$elapsed" >> cod2_time.txt

    start=$(date +%s%N)   # Get current time in nanoseconds
    { time -p ./cod3; } 
    end=$(date +%s%N)
    elapsed=$((end - start))
    echo "$elapsed" >> cod3_time.txt

    start=$(date +%s%N)   # Get current time in nanoseconds
    { time -p ./cod4; } 
    end=$(date +%s%N)
    elapsed=$((end - start))
    echo "$elapsed" >> cod4_time.txt

    start=$(date +%s%N)   # Get current time in nanoseconds
    { time -p ./cod5; } 
    end=$(date +%s%N)
    elapsed=$((end - start))
    echo "$elapsed" >> cod5_time.txt
done
# { time python cod1.py; } 2> cod1_time.txt

# gcc matrices.c cod2.c -o cod2
# { time ./cod2; } 2> cod2_time.txt
# { time ./cod2; } 2>> cod2_time.txt
# { time ./cod2; } 2>> cod2_time.txt
# { time ./cod2; } 2>> cod2_time.txt
# { time ./cod2; } 2>> cod2_time.txt

# gcc -mavx -march=native matrices.c cod3.c -o cod3
# { time ./cod3; } 2> cod3_time.txt
# { time ./cod2; } 2>> cod2_time.txt
# { time ./cod2; } 2>> cod2_time.txt
# { time ./cod2; } 2>> cod2_time.txt
# { time ./cod2; } 2>> cod2_time.txt

# gcc -mavx -march=native matrices.c cod4.c -o cod4
# { time ./cod4; } 2> cod4_time.txt
# { time ./cod2; } 2>> cod2_time.txt
# { time ./cod2; } 2>> cod2_time.txt
# { time ./cod2; } 2>> cod2_time.txt
# { time ./cod2; } 2>> cod2_time.txt
# { time ./cod2; } 2>> cod2_time.txt

# gcc -mavx -march=native matrices.c cod5.c -o cod5
# { time ./cod5; } 2> cod5_time.txt
# { time ./cod2; } 2>> cod2_time.txt
# { time ./cod2; } 2>> cod2_time.txt
# { time ./cod2; } 2>> cod2_time.txt
# { time ./cod2; } 2>> cod2_time.txt
