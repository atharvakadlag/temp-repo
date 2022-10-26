rm add_matrix.txt
for i in `seq 10`
do
	x=i-1
	num_threads=$((2**x))
	export OMP_NUM_THREADS=$num_threads
	./add_matrix
	echo "$num_threads $(./add_matrix)" >> add_matrix.txt
done
