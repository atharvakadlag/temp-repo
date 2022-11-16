#include <bits/stdc++.h>
#include <mpi.h>

#define MASTER 0
#define FROM_MASTER 1
#define FROM_WORKER 2

using namespace std;

float w1[12] = {0.5, 1.5, 0.8, 0.9, -1.7, 1.6, 0.5, 1.5, 0.8, 0.9, -1.7, 1.6};
float w2[12] = {0.8, 0.2, -1.6, 1.2, 2.1, -0.2, 0.8, 0.2, -1.6, 1.2, 2.1, -0.2,};

float x[15];

float _true[15];
float layer1[15];
float layer2[15];

int main((int argc, char *argv[]){
	int numtasks, taskid, numworkers, source, dest, mtype, rowsPerWorker;
	int extraRows, offset, rows;
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
	MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
	numworkers = numtasks - 1;
    
	if (taskid == MASTER) {
		for (int i = 0; i < 36; i++) {
        	w1[i] = int(w1[i])%10/10;
			w2[i] = int(w2[i])%10/10;
    	}
    	for (int i = 0; i < 15; i++) {
        	x[i] = int(x[i])%10/10;
    	}

		double start = MPI_Wtime();
		rowsPerWorker = 15/numworkers;
		extraRows = 15%numworkers;
		offset = 0;
		mtype = FROM_MASTER;

		for (int dest=1; dest<=numworkers; dest++)
		{
			rows = (dest <= extraRows) ? rowsPerWorker+1 : rowsPerWorker;
			printf("Sending %d rows to %d worker\n", rows, dest);
			MPI_Send(&offset , 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
			MPI_Send(&rows , 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
			MPI_Send(&x , 15, MPI_DOUBLE, dest, mtype, MPI_COMM_WORLD);
			MPI_Send(&w1 , 36, MPI_DOUBLE, dest, mtype, MPI_COMM_WORLD);
			MPI_Send(&w2 , 36, MPI_DOUBLE, dest, mtype, MPI_COMM_WORLD);
			printf("data sent to Worker%d",dest);

			offset = offset + rows;
		}

		mtype = FROM_WORKER;
		for (int i=1; i<=numworkers; i++){
			source = i;
			MPI_Recv(&offset, 1, MPI_INT, source, mtype,
			MPI_COMM_WORLD,&status);
			MPI_Recv(&rows, 1, MPI_INT, source, mtype,
			MPI_COMM_WORLD,&status);
			MPI_Recv(&layer2, rows, MPI_DOUBLE, source, mtype, MPI_COMM_WORLD, &status);
		}

		double finish = MPI_Wtime();
		printf("Done in %f seconds.\n", finish - start);

	} else if (taskid > MASTER) {
		mtype = FROM_MASTER;
		MPI_Recv(&offset, 1, MPI_INT, MASTER, mtype,
		MPI_COMM_WORLD,&status);
		MPI_Recv(&rows, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD,
		&status);
		MPI_Recv(&x, 15, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD,&status);
		MPI_Recv(&w1, 36, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD,&status);
		MPI_Recv(&w2, 36, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD,&status);

    	int iter;
        for (int i = 0; i < rows; i++) {
      		float sum = 0;
          	for (int j = 0; j < 36; j++) {
				sum += x[i] * w1[j];
           	}
            	layer1[i] = sum;
       	}

       	for (int i = 0; i < rows; i++) {
      		float sum = 0;
          	for (int j = 0; j < 36; j++) {
				sum += layer1[i] * w2[j];
           	}
            	layer2[i] = sum;
       	}
       	mtype = FROM_WORKER;
		MPI_Send(&offset, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD);
		MPI_Send(&rows, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD);
		MPI_Send(&layer2, rows, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD);


    }
}

