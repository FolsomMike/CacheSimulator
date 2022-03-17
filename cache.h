/*************************************************************************
*      	filename:  cache.h
*   	description:  Header file for cache.c
*       author:  Schoonover, Noah
*
*	    class:       CSE 331
*    	instructor:  Tong
*    	assignment:  Lab #2
*       due:  	     3/21/2022
*************************************************************************/
#ifndef CACHE_H
#define CACHE_H

#include <stdio.h>
#include <stdlib.h>

typedef enum { CACHE_SUCCESS, CACHE_FAILURE } CacheStatus;

CacheStatus create_cache();

#endif
