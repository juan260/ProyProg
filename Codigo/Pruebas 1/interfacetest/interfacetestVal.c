#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <termios.h>
#include "../../interface.h"

/*
  Initializes the terminal in such a way that we can read the input
  without echo on the screen
*/

struct termios initial;

void _term_init() {
	struct termios new;	          /*a termios structure contains a set of attributes about
					  how the terminal scans and outputs data*/

	tcgetattr(fileno(stdin), &initial);    /*first we get the current settings of out
						 terminal (fileno returns the file descriptor
						 of stdin) and save them in initial. We'd better
						 restore them later on*/
	new = initial;	                      /*then we copy them into another one, as we aren't going
						to change ALL the values. We'll keep the rest the same */
	new.c_lflag &= ~ICANON;	              /*here we are setting up new. This line tells to stop the
						canonical mode (which means waiting for the user to press
						enter before sending)*/
	new.c_lflag &= ~ECHO;                 /*by deactivating echo, we tell the terminal NOT TO
						show the characters the user is pressing*/
	new.c_cc[VMIN] = 1;                  /*this states the minimum number of characters we have
					       to receive before sending is 1 (it means we won't wait
					       for the user to press 2,3... letters)*/
	new.c_cc[VTIME] = 0;	              /*I really have no clue what this does, it must be somewhere in the book tho*/
	new.c_lflag &= ~ISIG;                 /*here we discard signals: the program won't end even if we
						press Ctrl+C or we tell it to finish*/

	tcsetattr(fileno(stdin), TCSANOW, &new);  /*now we SET the attributes stored in new to the
						    terminal. TCSANOW tells the program not to wait
						    before making this change*/
}


/*
  Reads a key from the keyboard. If the key is a "regular" key it
  returns its ascii code; if it is an arrow key, it returns one of the
  four interface directions with the "minus" sign
*/
int _read_key() {
  char choice;
  choice = fgetc(stdin);


  if (choice == 27 && fgetc(stdin) == '[') { /* The key is an arrow key */
    choice = fgetc(stdin);

    switch(choice) {
    case('A'):
      return NORTH;
    case('B'):
      return SOUTH;
    case('C'):
      return EAST;
    case('D'):
      return WEST;
    default:
      return HERE;
    }
  }
  else
    return choice;
}



int main(){
   Interface *i;
  int c,k,flag1,flag2,flag3;
	char **s;
	/*Inicializamos un mapa vacio*/
	s=(char **)malloc(sizeof(char *)*19);
	for(c=0;c<19;c++)
		s[c]=(char *)malloc(sizeof(char)*60);
	for(c=0;c<19;c++)
		strcpy(s[c],"                                                           ");
	_term_init();/*Initializes the terminal for the interface*/
	i=i_create(4,4,4,4,'x',40,37,40,37,40,37);
  i_drawAll(i);/*Draws limits*/
	char string[30];
	strcpy(string, "helow");
	i_setMap(i,s);/*sets and draws the board*/
	i_drawPl(i,1,1);
	flag1=0;
	flag2=0;
	flag3=0;
	while(1){
		c=_read_key();
		if(c=='q'){
				break;
		}
		if(c=='w'){
			if(flag1==0){
			i_setBackgroundColor(i, 41, 1);
			flag1=1;
			}else{
			i_setBackgroundColor(i, 40, 1);
			flag1=0;
			}
		}
		if(c=='e'){
			if(flag2==0){
			i_setBackgroundColor(i, 42, 2);
			flag2=1;
			}else{
			i_setBackgroundColor(i, 40, 2);
			flag2=0;
			}
		}
		if(c=='r'){
			if(flag3==0){
			i_setBackgroundColor(i, 43, 3);
			flag3=1;
			}else{
			i_setBackgroundColor(i, 40, 3);
			flag3=0;
			}
		}
		if(c=='t'){
			i_setForegroundColor(i, 31, 1);
		}
		if(c=='y'){
			i_setForegroundColor(i, 32, 2);
		}
		if(c=='u'){
			i_setForegroundColor(i, 33, 3);
		}
		if(c=='i'){
			i_setForegroundColor(i, 32, 3);
			i_setForegroundColor(i, 32, 2);
			i_setForegroundColor(i, 32, 1);
		}
		
		if(c=='a'){
			i_writeChar(i,'a',2, 3, 1);
		}
		if(c=='s'){
			i_writeChar(i,'s',2, 3, 1);
		}
		if(c=='d'){
			i_writeChar(i,'d',2, 3, 2);
		}
		if(c=='f'){
			i_writeChar(i,'f',2, 3, 2);
		}
		if(c=='g'){
			i_writeChar(i,'g',2, 3, 3);
		}
		if(c=='h'){
			i_writeChar(i,'h',2, 3, 3);
		}
		if(c=='j'){
			i_drawStrMap(i,string,2, 3, 3);
		}
		if(c=='k'){
			i_drawStrMap(i,"It's me",2, 3, 1);
			i_drawStrMap(i,"It's me",2, 3, 2);
			i_drawStrMap(i,"It's me",2, 3, 3);
		}
		move(i,c);
	}

	for(c=0;c<19;c++)

		free(s[c]);
	free(s);
  	i_free(i);
  	tcsetattr(fileno(stdin), TCSANOW, &initial);
  return 0;

}

/*CODIGO UTIL
int c = _read_key();
if (c == 'q') {
  tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
            so that the termial behaves normally when
            the program ends */
/*  exit(0);
}
*/
