#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "../../thpool.h"

/* 
 * THIS TEST NEEDS TO BE TIMED TO BE MEANINGFULL
 * 
 * main:    sleep 3 secs   sleep 2 secs
 *                      
 * thpool:                 sleep 4 secs
 * 
 * Thus the program should take just a bit more than 7 seconds.
 * 
 * */

void sleep_4_secs(){
	sleep(4);
	puts("SLEPT");
}

int main(int argc, char *argv[]){

	char* p;
	if (argc != 2){
		puts("This testfile needs excactly one arguments");
		exit(1);
	}
	int num_threads = strtol(argv[1], &p, 10);

	thpool threadpool = thpool_init(num_threads);
	
	thpool_pause(threadpool);
	
	thpool_add_work(threadpool, (void*)sleep_4_secs, NULL);
	thpool_add_work(threadpool, (void*)sleep_4_secs, NULL);
	
	sleep(3);
	
	thpool_resume(threadpool);
	// If it works, then the threadpool starts working NOW
	
	sleep(2); // Give some time to threads to get the work
	
	thpool_destroy(threadpool); // Wait for work to finish

	return 0;
}
