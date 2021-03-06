/*
* Author: Vish Gahlot
* Date: February 14, 2014
* Lost Caver main.c
* This program reads in a text file(input.txt) with the directions 
* for the caver to get out of the cave.
* File format: (0,0) E MMMMMMMMMMMMMMMMMMMM
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h> 
#include "main.h"

	char cave[18][22];
	char way[100];
	char direction;
	char *path;
	int current_row, current_col;
	int start_row = 0;
	int start_col = 0;

/*
* Function: main()
*/
int main(){

	int i, j;
	initializeCave();
	readInput();
	displayCave();
	play();	
	
	return 1;
}

/*
* Function: readInput()
* Reads the input file one character at a time
*/
void readInput(){

	FILE *open;
	open = fopen("input.txt", "r"); 
	char ch;
	int index = 0;	
	
 	while (ch = getc(open) != '(');
	
        while ((ch= getc(open)) != ','){
	   if(isdigit(ch)){
		start_row = start_row * 10;
		start_row = start_row + ch - '0';
	}
       }
 
        while ((ch = getc(open)) != ')'){
	    if(isdigit(ch)){
		start_col = start_col * 10;
		start_col = start_col + ch - '0';
	}
	}

	while ((ch = getc(open)) != ' ');

	while ((ch = getc(open)) != ' '){
	    if(isalpha(ch) ){
		direction = ch;
		}
	}

	while ((ch = getc(open)) != EOF){
	    if(isalpha(ch)){
		way[index]=ch;	
		printf("%c", way[index]);
		index++;
		//printf("%c ", way[index]);
		}
	}
	
	start_row = 16 - start_row;	//the last row is 0 row
	start_col = 1 + start_col;
	current_row = start_row;
	current_col = start_col ;
	cave[start_row][start_col] = '.';
      
	printf("Start row = %d and start column = %d\n", start_row, start_col);
	//printf("%c\n",&way);
}

/*
* Function: initializeCave()
* Initializes teh cave array with spaces and marks its boundary
*/
void initializeCave(){

	int i,j;
	/*Initialize with spaces*/
	for(i=0;i<=17;i++)
		for(j=0; j<=21; j++)
			cave[i][j] = ' ';

	/*Draw a horizontal border*/
	for(i=1;i<21;i++){
		cave[0][i] = '-';
		cave[17][i] = '-';
	}

	/*Draw a vertical border*/
	for(i=1;i<17;i++){
		cave[i][0] = '|';
		cave[i][21] = '|';
	}

	/*Initial condition for the caver*/	
}

/*
* Function: displayCave()
* displays the cave after every move to show the location of the caver
*/
void displayCave(){
	int i,j;
	for(i=0;i<=17;i++){
		for(j=0; j<=21; j++)
			printf("%c", cave[i][j]);	
		printf("\n");
	}
}
/*
* Function: checkBound()
* Checks for the boundary conditions to the caver does not die
* returns 0 if the move will kill the cave
*/
int checkBound(){

	if((direction == 'N' && current_row == 0) || (direction == 'S' && current_row == 17) || (direction == 'W' && current_col == 0) || (direction == 'E' && current_col == 21))
	{
		return 0;
	}
	return 1;
}

/*
* Function: play()
* Changes and manages directions as requested. 
*/
void play(){

	int i;
	for(i = 0; i< strlen(way)-1; i++){
	if(way[i] == 'M'){	
		switch(direction){
	
		case 'N':
			current_row--;
			if(checkBound()==0){
				printf("Illegal move... Try Again!\n");
				current_row++;
				break;}
			else break;	
		case 'S':
			current_row++;
			if(checkBound()==0){
				printf("Illegal move... Try Again!\n");
				current_row--;
				break;}
			else break;	
		case 'E':
			current_col++;
			if(checkBound()==0){
				printf("Illegal move... Try Again!\n");
				current_col--;
				break;}
			else break;	
		case 'W':
			current_col--;
			if(checkBound()==0){
				printf("Illegal move... Try Again!\n");
				current_col++;
				break;}
			else break;	
		}
	} //end of if
	else if(way[i] == 'L'){	// turn left
		switch(direction){
		
		case 'N':
			direction = 'W';
			break;	
		case 'S':
			direction = 'E';
			break;	
		case 'E':
			direction = 'N';
			 break;	
		case 'W':
			direction = 'S';
			break;	
		}
	}// end of if
	
	else if(way[i] == 'R'){	// turn right
		switch(direction){
		
		case 'N':
			direction = 'E';
			break;	
		case 'S':
			direction = 'W';
			break;	
		case 'E':
			direction = 'S';
			 break;	
		case 'W':
			direction = 'N';
			break;	
		}
	}// end of if

	move();
	displayCave();
	printf("Direction: %c (%d, %d)\n", direction, (16-current_row), (current_col+1));
	}	// end of for
	
}

/*
* Function: move*()
* makes the period move one cell a time
* The caver is represented by a period	
*/
void move(){

	cave[start_row][start_col] = '.';
	cave[current_row][current_col] = '.';
		
	start_row = current_row;
	start_col = current_col;
}

