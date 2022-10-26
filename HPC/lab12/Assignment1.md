Assignment1: Vector Addition and Multiplication using Parallel Processing
---

##### `hello_world.c`
```c
#include <stdlib.h>
#include <stdio.h>

int main() {
	#pragma omp parallel
	{
		printf("Hello");
		printf("World");
	}
	printf("\n");
	return(0);
}
```

The above program 
