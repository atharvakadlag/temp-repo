for i in `seq 14`
do
	num_threads=$((2**i))
	echo $num_threads >> main_parallel_results.txt
	export OMP_NUM_THREADS=$num_threads
	./main_parallel >> main_parallel_results.txt
done
