#ifndef WORLD_H
#define WORLD_H
#include <stdlib.h>
#include "types.h"
#include "space.h"
#include "player.h"
#include "object.h"

typedef struct _World World;


/*Function: Initializes a World given a Player, an    */
/*array of objects, an array of spaces, number of objs*/
/*and number of spaces				      */
/*Parameters: explained above 			      */
/*Returns: a World with the given data		      */
/*COMMENT: THE ARRAY OF OBJECTS AND THE ARRAY OF SPACES*/
/*IS NOT COPIED AND WILL BE FREED IN WORLD FREE	      */
World *world_ini(Object **obj, Player *p, Space **space, int numobj, int numspaces);



/*Function: frees world and ALL its variables INCLUIDING  */
/*THE ARRAY OF SPACES AND THE ARRAY OF OBJECT WHEN CREATED*/
/*Parameters: Pointer to world				  */
/*Returns: -						  */
void world_free(World *);



/*Funcitions: Gives back a space given the spaceid*/
/*Parameters: World and int>0 which is the spaceid*/
/*Return: The pointer DIRECTLY to the space asked */
/*DO NOT FREE THE SPACE 	  		  */
Space *World_getSpace(World *w, int sid);



/*Function: Gives back the number of spaces of the World*/
/*Parameters: Pointer to World				*/
/*Return: integer with the num of spaces  		*/
int world_getNumSpaces(World *w);



/*Funcition: Gives back an object given the objectid*/
/*Parameters: World and int>0 which is the objectid*/
/*Return: The pointer DIRECTLY to the object asked */
/*DO NOT FREE THE OBJECT			   */
Object *World_getObjects(World *w, int oid);



/*Function: Gives back the number of objects in the World */
/*Parameter: Pointer to World				   */
/*Return: integer with the number of objects		   */
int world_getNumObjects(World *w);



/*Function: Gives back a pointer to the player*/
/*Parameter: Pointer to world                 */
/*Return: the pointer DIRECTLY to the player  */
/*DO NOT FREE THIS PLAYER		      */
Player *World_getPlayer(World *w);




#endif
