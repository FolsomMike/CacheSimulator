/*************************************************************************
*      	filename:  trace.h
*   	description:  Header file for trace.c
*       author:  Schoonover, Noah
*
*	    class:       CSE 331
*    	instructor:  Tong
*    	assignment:  Lab #2
*       due:  	     3/21/2022
*************************************************************************/
#ifndef TRACE_H
#define TRACE_H

#include <stdio.h>
#include <stdlib.h>

#define NTRACE_LINE_PARAMS 4

typedef enum { TRACE_SUCCESS, TRACE_FAILURE, TRACE_END } TraceStatus;
typedef enum { LOAD, STORE } AccessType;

/**
 * memacc - a global memory_access struct for storing information from
 * each line in the trace file.
 */
struct memory_access {
    AccessType type;    /* access type: load or store */
    int address;        /* memory access address */
    int islma;          /* instructions since last memory access */
} memacc;

TraceStatus begin_trace(char *filename);
TraceStatus get_next_trace(int *cycle_count);
TraceStatus end_trace();

#endif
