rm main.txt
for i in `seq 10`
do
	x=i-1
	num_threads=$((2**x))
	export OMP_NUM_THREADS=$num_threads
	./main
	echo "$num_threads $(./main)" >> main.txt
done
