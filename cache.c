/*************************************************************************
*       filename:  config.c
*       description:  implementation for the cache
*
*       author:  Schoonover, Noah
*
*        class:       CSE 331
*        instructor:  Tong
*        assignment:  Lab #2
*       due:           3/21/2022
*************************************************************************/

#include "cache.h"
#include "config.h"

int *tag;       /* tag array */
int *data;      /* data array */
int *dirty;     /* dirty array */
int lines;      /* the number of lines in the cache */

CacheStatus create_cache() {

    int data_size_bytes = cfg.data_size * (1 << 10);
    lines = data_size_bytes / cfg.line_size;
    printf("data_size: %d\n", cfg.data_size);
    printf("data_size_bytes: %d\n", data_size_bytes);
    printf("line_size: %d\n", cfg.line_size);
    printf("lines: %d\n", lines);

    return CACHE_SUCCESS;

}

CacheStatus query_cache() {

    return CACHE_SUCCESS;

}
