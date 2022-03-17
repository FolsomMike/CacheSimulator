/*************************************************************************
*      	filename:  lab2.c
*   	description:  main function implements the cache simulator
*
*       author:  Schoonover, Noah
*
*	    class:       CSE 331
*    	instructor:  Tong
*    	assignment:  Lab #2
*       due:  	     3/21/2022
*************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "trace.h"
#include "cache.h"

int cycle_count;


int main(int argc, char *argv[]) {

	if (argc != 3) {

		printf("Usage: ./lab2 [config file] [trace file]\n");
      	exit(EXIT_FAILURE);

   	} else {

		if (read_config(*++argv) == CONFIG_FAILURE) {
			printf("error reading config file\n");
			exit(EXIT_FAILURE);
		}

		#if CONFIG_VERBOSE == 1
		printf("\n");
		printf("--------------------------------------------------------------------------\n");
		printf("Reading trace file:\n\n");
		printf("                 Raw               Cleaned         ");
		printf("Load/Store  Address     Cycles\n\n");
		#endif // CONFIG_VERBOSE

		cycle_count = 0;

		if (begin_trace(*++argv) == TRACE_FAILURE) {
			printf("error opening trace file\n");
			exit(EXIT_FAILURE);
		}

		int lines = 0; // temp counter for testing
		while (get_next_trace(&cycle_count) != TRACE_END) {
			lines++;
		}

		#if CONFIG_VERBOSE == 1
		printf("\n");
		printf("--------------------------------------------------------------------------\n");
		#endif // CONFIG_VERBOSE

		printf("\n");
		printf("Statistics\n");
		printf("\n");
		printf("Cycle count: %d\n", cycle_count);
		printf("Trace file line count: %d\n", lines);
		printf("\n");
		printf("\n");

		end_trace();

		create_cache();

		exit(EXIT_SUCCESS);

	}


    return 0;
}
