/*************************************************************************
*      	filename:  config.c
*   	description:  functions for reading the config file
*			config parameters are stored in a global struct
*
*       author:  Schoonover, Noah
*
*	    class:       CSE 331
*    	instructor:  Tong
*    	assignment:  Lab #2
*       due:  	     3/21/2022
*************************************************************************/

#include "config.h"

/**
 * reads config, stores config parameters in global config struct
 * @param  filename               config filename
 * @return          CONFIG_SUCCESS or CONFIG_FAILURE
 */
ConfigStatus read_config(char *filename) {

	FILE *config_file = NULL;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;

	// open config file
	if ((config_file = fopen(filename, "r")) == NULL) {
		printf("error: can't open config file %s\n", filename);
		return CONFIG_FAILURE;
	}

	// read parameters from config file
	// use temporary array for cleaner code
	int temp_configs[NCONFIG_PARAMS];
	for (int i = 0; i < NCONFIG_PARAMS; i++) {
		if ((read = getline(&line, &len, config_file)) == -1) {
			printf("config file missing parameters.");
			if (line) free(line);
			fclose(config_file);
			return CONFIG_FAILURE;
		}
		printf("line: %s\n", line);
		sscanf(line, "%d", &temp_configs[i]);
	}

	// set the permanent config parameters from the temp array
	cfg.line_size      = temp_configs[0];
	cfg.associativity  = temp_configs[1];
	cfg.data_size      = temp_configs[2];
	cfg.replace_policy = temp_configs[3];
	cfg.miss_penalty   = temp_configs[4];
	cfg.write_alloc    = temp_configs[5];

	// print the config params to verify success
	#if CONFIG_VERBOSE
	printf("line_size: %d\n", cfg.line_size);
	printf("associativity: %d\n", cfg.associativity);
	printf("data_size: %d\n", cfg.data_size);
	printf("replace_policy: %d\n", cfg.replace_policy);
	printf("miss_penalty: %d\n", cfg.miss_penalty);
	printf("write_alloc: %d\n", cfg.write_alloc);
	#endif // CONFIG_VERBOSE

	if (line) free(line);
	fclose(config_file);
	return CONFIG_SUCCESS;

}
