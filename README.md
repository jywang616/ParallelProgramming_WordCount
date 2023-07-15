# ParallelProgramming_WordCount
Using pthread/openmp/mpi to solve the problem

Environment:
Visual Studio 2019

### To start with parallel programming:
#### Pthread:

[Building environment of Pthread](https://blog.csdn.net/sijia5135/article/details/115356079)

[Pthread.zip](https://github.com/jywang616/ParallelProgramming_WordCount/blob/main/packages/pthread.zip)

#### Mpi：
[Building environment of Mpi](https://www.jianshu.com/p/c74cf04ca415)

[Introduction of Mpi(with demo)](https://zhuanlan.zhihu.com/p/355652501)

[Download](https://www.mpich.org/downloads/)

Test code:
```C++
#include<stdio.h>
#include<mpi.h>

int main(int argc, char* argv[])
{
    int myid, numprocs, namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Get_processor_name(processor_name, &namelen);
    if (myid == 0) printf("number of processes: %d\n", numprocs);
    printf("%s: Hello world from process %d \n", processor_name, myid);
    MPI_Finalize();
    return 0;
}
```

Q：MPI是可以传map类型的吗sos 套娃失败————

