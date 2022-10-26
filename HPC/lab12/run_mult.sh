for i in `seq 14`
do
	num_threads=$((2**i))
	echo $num_threads >> results_mult.txt
	export OMP_NUM_THREADS=$num_threads
	./pvector_mult >> results_mult.txt
done
