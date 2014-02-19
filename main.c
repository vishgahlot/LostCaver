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

int main(){

	int i, j;
	initializeCave();
	readInput();
	displayCave();
	play();	

	return 1;
}

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
	/*The caver is represented by a period*/
		
}

void displayCave(){
	int i,j;
	for(i=0;i<=17;i++){
		for(j=0; j<=21; j++)
			printf("%c", cave[i][j]);	
		printf("\n");
	}
}

int checkBound(){

	if((direction == 'N' && current_row == 0) || (direction == 'S' && current_row == 17) || (direction == 'W' && current_col == 0) || (direction == 'E' && current_col == 21))
	{
		return 0;
		//printf("Cannot go more %c than this", direction);
	}
	return 1;
}

void play(){

	int i;
	for(i = 0; i< strlen(way); i++){
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
	else if(way[i] == 'L'){
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
	
	else if(way[i] == 'R'){
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

void move(){

	cave[start_row][start_col] = ' ';
	cave[current_row][current_col] = '.';
		
	start_row = current_row;
	start_col = current_col;
}

