/**		TO-DO
 * Fix memory leaks in your code
 * Write function: split_path()
 	* truncates our path variable gotten from get_path()
	* uses strtok(buffer, ":") to split them
	* store each one as elements of an array
 * Write function: find_path()
 	* concatenates our first argument with each PATH
 	* finds the location of our command function in PATH
	* returns a buffer containing the location
 * We then pass this buffer to our execve command
 * Done: get_path()
 	* Finds the PATH variable in our environment array and executes
 */
#include "main.h"

