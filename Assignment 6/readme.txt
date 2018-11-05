readme.txt
Name: Jingjing Nie
UID: 304567417

The main purpose of this assignment is to improve the execution
time through the use of multi-threading. One of the problems I 
had was to figure out what the program was doing so that I can
modify it to enable multi-threading. I then realized that I need
to modify the for loop in the main.c file for parallelism, and I
need to use library functions pthread_create and pthread_join to
create and join the threads. Then, according to the argument types
of the pthread_create function, I moved the for loop into an 
independent function for solor rendering, and then use for loops in
the main function to create an array of threads. Then, in order to
avoid race condition problems, I used an for loop to join the
threads and another for loop to print out the outputs.

Original version:
time ./srt 1-test.ppm >1-test.ppm.tmp
real	0m40.945s
user	0m40.938s
sys		0m0.002s

Modified version:
time ./srt 1-test.ppm >1-test.ppm.tmp
real    0m44.393s
user    0m44.383s
sys     0m0.002s

time ./srt 2-test.ppm >2-test.ppm.tmp
real    0m22.432s
user    0m44.694s
sys     0m0.002s

time ./srt 4-test.ppm >4-test.ppm.tmp
real    0m11.270s
user    0m44.752s
sys     0m0.002s

time ./srt 8-test.ppm >8-test.ppm.tmp
real    0m5.775s
user    0m44.721s
sys     0m0.002s

The results have shown that after using multithreads, the execution 
time has been greatly shortened as the number of threads increase.
I have also realized that the real time can be approximately calculated
by using the user time to be divided by the number of threads used.