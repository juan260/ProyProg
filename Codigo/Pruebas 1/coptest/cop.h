#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

/*Parameters of pfun are a world, the object, the possible answers and the 
number of possible answers*/
typedef Status (*pfun)(void*, char*, char**, int);

typedef struct _Assoc Assoc;
typedef struct _Ext Ext; 
typedef struct _CoP CoP;




/*Function: adds assoc between a COPY of a string and a function to the CoP   */
/*Parameter: string and pointer to the function, CoP where assoc will be added*/
/*Returns:  number of assocs in CoP after execution/ -1 in case of error      */
/*Revision: 5/11/16                                             	      */
int assoc_add(CoP *c, char *int_name, pfun f);

/*Function: creates CoP from file                             */
/*Parameter: Pointer to a OPEN file that will be rerurned OPEN*/
/*Returns: pointer to CoP/ NULL when error                    */
/*Revision: 5/11/16		                              */
CoP *cop_ini(FILE *f);

/*Function: frees CoP and all its members*/
/*Parameter: CoP to free		 */
/*Returns:                 		 */
/*Revision: 18/11/16			 */
void cop_free(CoP *c);

/*Function: executes a typed command */
/*Parameter: CoP, command to execute, world where the cmd will be executed*/
/*Return: value of the executed function/ -1 when memory error 		  */
/*Revision: 11/11/16							  */
int cop_execute(CoP *c, char *cmd, void *world);
