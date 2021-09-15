//edited by davidrs3 airra2 nroger5
/* For this MP we created various functions for a maze.
The first function allocated memory for the array
and the maze. The second destroyed the set memory after usage and
freed the data. the third function printed the solved solution in a
maze format and the last function went through the process
of solving the maze by recursively going through the maze's possible directions
and backtracking if a dead end has been reached, the function would return 0 if no
solution has been determined.
*/
#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    int height, width; //declare variables to store the dimensions read from the first line
    int i, j; //loop variables for filling the cells
    char blank, value; //blank will take care of any garbage values in the text files like newlines, value will hold the characters we want

    FILE * file; //declare a FILE pointer to do file IO
    file = fopen(fileName, "r"); //open up the imported file for read only

    maze_t * maze = (maze_t*)malloc(sizeof(maze_t)); //allocate space for a maze_t pointer called maze, the size of maze_t struct
    fscanf(file, "%d %d", &width, &height); //read in the two integers from the file that represent the dimensions of the maze.

    maze->height = height; //set the maze's height to that read by fscanf
    maze->width = width; //set the maze's width to that read by fscanf
    maze->cells = (char**)malloc(sizeof(char*) * height); //allocate space for the row pointer lookup table that is the size of a char*xheight(#ofrows)

    for(i=0; i<height; i++){ //run a for loop to create create space for each cell, each cell being a single char pointer
        maze->cells[i] = (char*)malloc(sizeof(char) * width);
    }
    for(i=0; i<height; i++){ //run a double for loop to fill each cell of the maze with it's value imported from the text file
        fscanf(file, "%c", &blank); //get rid of any garbage at the start of a row i.e newline characters
        for(j=0; j<width; j++){
            fscanf(file, "%c", &value);
            maze->cells[i][j] = value;
            if(maze->cells[i][j] == START){ //if the value read is S set the startRow and startColumn 
                maze->startRow = i;
                maze->startColumn = j;
            }
            if(maze->cells[i][j] == END){ //if the value read is E set the endRow and endColumn
                maze->endRow = i;
                maze->endColumn = j;
            }
        }
    }
    fclose(file); //close the file
    return maze; 
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze) //free the memory held in each cell and free the maze itself, checked in valgrind leaves nothing unfreed
{
    // Your code here.
    int i;
    for(i=0; i<maze->height; i++){
        free(maze->cells[i]);
    }
    free(maze);
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    int i, j, height, width; //initialize variables
    height = maze->height;
    width = maze->width;
    //run a double for loop to iterate over the entire maze and print it out, newline after the innerloop so the maze looks as seen in the text file
    for(i=0; i<height; i++){
        for(j=0; j<width; j++){
            printf("%c", maze->cells[i][j]);
        }
        printf("\n");
    }
}

int baseCase(maze_t * maze, int col, int row){ //helper function that checks out all the base cases
    if((col >= maze->width) || (col < 0) || (row >= maze->width) || (row < 0)){
        return 0;
    }
    if(maze->cells[row][col] == START){
        return 1;
    }
    if(maze->cells[row][col] == END){
        return 1;
    }
    if(maze->cells[row][col] != EMPTY){
        return 0;
    }
    return 1;
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search, 
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.

    if(baseCase(maze, col, row) == 0){
        return 0;
    } //if the helper function returns 0 that means a base case condition was met and 0 has to be returned
    
    if(maze->cells[row][col] == END){ //maze has been solved
        
        return 1;
    }
    if(maze->cells[row][col] != START){ //set the current location to be part of the path until otherwise proven by the code
        maze->cells[row][col] = PATH;
    }

    if(solveMazeDFS(maze, col-1, row) == 1){ //first recursive case, if its true, the function can end with success
        if(maze->cells[row][col-1] == START){
            maze->cells[row][col] = VISITED; //updates failed cells as visited and not part of the path
        }
        return 1;
    }else if(solveMazeDFS(maze, col+1, row) == 1){ //next recursive case
        if(maze->cells[row][col+1] == START){
            maze->cells[row][col] = VISITED;// same as first recursive case
        }
        return 1;
    }else if(solveMazeDFS(maze, col, row-1) == 1){
        if(maze->cells[row-1][col] == START){
            maze->cells[row][col] = VISITED; //same as first recursive case
        }
        return 1;
    }else if(solveMazeDFS(maze, col, row+1) == 1){ //next recursive case
        if(maze->cells[row+1][col] == START){
            maze->cells[row][col] = VISITED; //same as first recursive case
        }
        return 1;
    }
    if(maze->cells[row][col] != START){ //if all recursive cases fail and the current position is not the starting position mark the current position as a failed position
        maze->cells[row][col] = VISITED;
    }
    return 0; //if this point has been reached the maze is unsolvable and zero must be returned
}
