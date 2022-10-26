for i in `seq 14`
do
	num_threads=$((2**i))
	echo $num_threads >> results_add.txt
	export OMP_NUM_THREADS=$num_threads
	./pvector_add >> results_add.txt
done
