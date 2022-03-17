/*************************************************************************
*      	filename:  trace.c
*   	description:  functions for reading the trace file
*			trace line info is stored in a global struct
*
*       author:  Schoonover, Noah
*
*	    class:       CSE 331
*    	instructor:  Tong
*    	assignment:  Lab #2
*       due:  	     3/21/2022
*************************************************************************/

#include "trace.h"
#include "config.h"

#include <string.h>


/*
 * these globals are defined here to limit visibility to trace.c functions
 * trace_file and line are globals by necessity,
 * len and read are globals to increase read function call efficiency
 */
FILE *trace_file;
char *line;
size_t len;
ssize_t read;

#define mod_line_size 100
char mod_line_buf[mod_line_size];

int num_cycles;

int debug_line_count; //debug mks

/**
 * opens the trace file for reading, stores the file pointer globally
 * @param  filename               the trace filename
 * @return          TRACE_FAILURE or TRACE_SUCCESS
 */
TraceStatus begin_trace(char *filename) {

	num_cycles = 0;

	debug_line_count = 0; //debug mks

	// open trace file
	if ((trace_file = fopen(filename, "r")) == NULL) {
		printf("error: can't open trace file %s\n", filename);
		return TRACE_FAILURE;
	}

	return TRACE_SUCCESS;

}

/**
 * get the next line from the trace file, store details in global memacc struct
 * @return TRACE_SUCCESS, TRACE_FAILURE, or TRACE_END
 */

TraceStatus get_next_trace(int *cycle_count) {

	int load_store;
	unsigned address;
	int num_cycles;

	char *mod_line = mod_line_buf;

	// get the next line from the trace file
	if ((read = getline(&line, &len, trace_file)) != -1) {

		//get rid of any newline so printf won't go to next line and will concatenate instead
		if(line[read-1] == '\n') { line[read-1] = ' '; }

		#if CONFIG_VERBOSE == 1
		printf("Line length %zu:  ", read);
	    printf("%s | ", line);
		#endif // CONFIG_VERBOSE

		//safe copy to a new string for modification
		if (mod_line_size > 0){
			mod_line[0] = '\0';
			strncat(mod_line, line, mod_line_size - 1);
		}

		//some trace programs start each line with # ~ if present remove it and the following space

		if(mod_line[0] == '#'){ mod_line++; mod_line++; }

		#if CONFIG_VERBOSE == 1
	    printf("%s | ", mod_line);
		#endif // CONFIG_VERBOSE

		//some trace programs use '0' for a load and '1' for a store
		//and some use 'l' (lowercase L) for load and 's' for store
		//convert 'l' and 's' to '0' and '1' to allow for simple sscanf of the line elements

		if(mod_line[0] == 'l'){ mod_line[0] = '0'; }
		if(mod_line[0] == 'S'){ mod_line[0] = '1'; }

		// sscanf(line, "%d", &d)

		for (int i = 0; i < NTRACE_LINE_PARAMS; i++) {
			sscanf(mod_line, "%d %x %d", &load_store, &address, &num_cycles);
		}

		#if CONFIG_VERBOSE == 1
		printf("%d           ", load_store);
		printf("%x    ", address);
		printf("%d \n", num_cycles);
		#endif // CONFIG_VERBOSE

		*cycle_count += num_cycles;

//		if(debug_line_count++ == 5) { return TRACE_END; } //debug mks

	} else {
		// end of file reached
		return TRACE_END;
	}

	return TRACE_SUCCESS;

}

/**
 * closes the trace file and releases resources
 * @return TRACE_SUCCESS, TRACE_FAILURE, or TRACE_END
 */

TraceStatus end_trace() {

	if (line) free(line);
	fclose(trace_file);
	return TRACE_SUCCESS;

}
