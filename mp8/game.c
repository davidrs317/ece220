//written by davidrs3, airra2 and nrgoer5
//for this MP we dynamically allocated memory for the game strucure in the make_game function
//we then wrote a get_cell function that would retrieve a certain cell based on a set of parameters
//from there we wrote functions to move the board up, down, left, and right
//these functions worked by scanning through the board and compoaring the values of each cell based on the direction it had to go
//The board was scanned through using iterative for loops that stored cells in other arrays to be copied later
//upon finding whether or not a move was valid, the functions would perform the transformation and adjust the cells and score accrodingly
//there was also a function that checked if moves were legal by iterating through the cboard
//and checking if there were empty spaces or identical spaces

#include "game.h"


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure)
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
	int locs; //for memory locations
	(*mygame).rows = rows;
	(*mygame).cols = cols;
	(*mygame).score = 0;
	for(locs = 0; locs < rows*cols; locs++){
		mygame -> cells[locs] = -1;
	}

    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any
	memory previously allocated is not lost in this function.
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
	int locs; //for memory locations
	(**_cur_game_ptr).rows = new_rows;
	(**_cur_game_ptr).cols = new_cols;
	(**_cur_game_ptr).score = 0;
	for(locs = 0; locs < new_rows * new_cols; locs++){
		(*_cur_game_ptr) -> cells[locs] = -1;
	}

	return;
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
	int mrows, mcols;
	mrows = (cur_game) -> rows;
	mcols = (cur_game) -> cols;
	if((row >= 0) && (row < mrows) && (col >= 0) && (col < mcols)){
		int curr_cell = (row*mcols) + col;
		return &(cur_game -> cells[curr_cell]);
	}
    return NULL;
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can
   not merge twice in one turn. If sliding the tiles up does not cause any
   cell to change value, w is an invalid move and return 0. Otherwise, return 1.
*/
{
  //YOUR CODE STARTS HERE
    int maxrow = cur_game->rows;
    int maxcols = cur_game->cols;
    int i,j,k;
    int cpy_c;
    int cpy_r;
    int board1[maxrow*maxcols];
    int board2[maxrow*maxcols];
      for (cpy_c=0; cpy_c< maxcols;cpy_c++)
      {
        for (cpy_r=0; cpy_r < maxrow; cpy_r++)
        {
          board1[cpy_r*maxcols+cpy_c]=(*get_cell(cur_game,cpy_r,cpy_c));
        }
      }
  ////////check to see if the value is valid
int check(int rr, int cc, int mm) //check to see if the value is valid
 {
  int i;
  for(i=rr+1;i<cc;i++)
  {
    if((*get_cell(cur_game,i,mm)) != -1)
    {
      return 1;
    }
  }
  return 0;
}
///////////////////////////////////////
  for ( cpy_c=0; cpy_c < maxcols; cpy_c++)
  {
    for (cpy_r = 0; cpy_r < maxrow; cpy_r++)
    {
      if((*get_cell(cur_game, cpy_r, cpy_c))!= -1)
      {
        board2[cpy_r*maxcols+cpy_c]=1; //counts the number of cells that can be merged
      }
      else
      {
        board2[cpy_r*maxcols+cpy_c]=0; //counts the number of cells that can be merged
      }
    }
  }




    for (j = 0; j <maxcols; j++)//all columns
    {
      for (i = 0; i <maxrow; i++) //all rows
      {
      for (k = 0; k < maxrow; k++)
      {
        if ((*get_cell(cur_game, i, j)) != -1)//if not empty
        {
          if((*get_cell(cur_game,k,j))!= -1) //if new cell also not empty
          {
            if ((*get_cell(cur_game,i, j)) == (*get_cell(cur_game, k, j)))
             {
              if (board2[i * maxcols + j] == 1 && board2[k * maxcols + j] == 1)//if current cell is equal to the one above it
              {
                if (i!=k && i>k)
                {
                  if(check(k,i,j)==0)
                  { (*get_cell(cur_game, i, j))= (*get_cell(cur_game, k, j))+(*get_cell(cur_game, i,j));
                      (*get_cell(cur_game, k, j))=-1;
                      cur_game-> score+= (*get_cell(cur_game,i,j));
                      board2[i*maxcols+j]=0;
                      board2[k*maxcols+j]=0;
              //  cur_game->cells[i*maxcols+j]=cur_game->cells[(i-1)*maxcols+j]*2; //merge cells
                //cur_game->cells[(i-1)*maxcols+j]=-1;//erase the cell c merged from
                //cur_game->score=cur_game->score+cur_game->cells[i*maxcols+j];//update score
                //score_count=1; //tell program merging has already happened
                  }
                  }
                }
              }
             }
           }
          }
        }
      }
  for (size_t j = 0; j < maxcols; j++) {
    for (size_t i = 0; i < maxrow; i++) {
      if (*get_cell(cur_game,i,j)!= -1) {
        for (size_t k = 0; k < i; k++) {
          if((*get_cell(cur_game, k, j))==-1){
            (*get_cell(cur_game, k, j))=(*get_cell(cur_game,i,j));
            (*get_cell(cur_game,i,j))=-1;
          }
        }
      }
    }
  }
        /*  for (k = 0; k < i; k++)//iterate through every row in that column to slide up
          {
            if(cur_game->cells[k*maxcols+j]==-1)//if that cell is empty
            {
              cur_game->cells[k*maxcols+j]=cur_game->cells[i*maxcols+j];//merge cells
              cur_game->cells[i*maxcols+j]=-1; //empty cell
              break; */
  int changes=0;
    for (j = 0; j <maxcols; j++)
    {
      for (i = 0;  i < maxrow;  i++)
      {
        if (board1[i*maxcols+j]==(*get_cell(cur_game, i, j)))
        {
          changes++;
        }
      }
    }
        if (maxrow*maxcols==changes) {
          return 0;
        }
        else{
          return 1;
        }
}

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
	int row = (cur_game) -> rows;
	int col = (cur_game) -> cols;
	int osize = row*col; //original size
	int cboard[osize];
	int oboard[osize];
	int checkrow, checkcol, merge, init, counter;

	//fill the array oboard with all the values in the current game for comparison later on
	for(checkcol = 0; checkcol < col; checkcol++){
		for(checkrow = 0; checkrow < row; checkrow++){
			oboard[checkrow * col + checkcol] = (*get_cell(cur_game, checkrow, checkcol));
		}
	}

	//a function to see if their are values within the space of two cells being inspected
	int within(int x, int y, int z){
		for(init = x + 1; init < y; init++){
			if((*get_cell(cur_game, init, z)) != -1){
				return 1;
			}
		}
		return 0;
	}

	//set markers for whether or not a cell is mergeable. 0 is non-mergeable, 1 is mergeable
	for(checkcol = 0; checkcol < col; checkcol++){
		for(checkrow = 0; checkrow < row; checkrow++){
			if((*get_cell(cur_game, checkrow, checkcol)) == -1){
				cboard[checkrow *col + checkcol] = 0;
			}
			else{
				cboard[checkrow * col + checkcol] = 0;
			}
		}
	}

	//merge cells if they have a value other than one, are equal and if there is not a different value within their space
	for(checkcol = 0; checkcol < col; checkcol++){
		for(checkrow = row - 1; checkrow >= 0; checkrow--){
			for(merge = 0; merge < row; merge++){
				if(((*get_cell(cur_game, checkrow, checkcol)) != -1) && (*get_cell(cur_game, merge, checkcol)) != -1){
					if((*get_cell(cur_game, checkrow, checkcol)) == (*get_cell(cur_game, merge, checkcol))){
						if((cboard[checkrow * col + checkcol] == 1) && (cboard[merge * col + checkcol] == 1)){
							if(within(checkrow, merge, checkcol) == 0){
								//if the cell passes all the conditions set the lower cell to the sum of the two cells
								(*get_cell(cur_game, checkrow, checkcol)) = (*get_cell(cur_game, checkrow, checkcol)) + (*get_cell(cur_game, merge, checkcol));
								//reset the value of the upper cell to empty
								(*get_cell(cur_game, merge, checkcol)) = -1;
                //update teh score with the new value
                (cur_game) -> score += (*get_cell(cur_game, checkrow, checkcol));
								//reset the array that checks for mergeability for reuse
								cboard[checkrow * col + checkcol] = 0;
								cboard[merge * col + checkcol] = 0;
							}
						}
					}
				}
			}
		}
	}

	//shift cells down once more to make sure no extra space is left unused
	for(checkcol = 0; checkcol < col; checkcol++){
		for(checkrow = row -1; checkrow >=0; checkrow--){
			if((*get_cell(cur_game, checkrow, checkcol)) != -1){
				for(init = row -1; init >= 0; init--){
					if((*get_cell(cur_game, init, checkcol)) == -1){
						(*get_cell(cur_game, init, checkcol)) = (*get_cell(cur_game, checkrow, checkcol));
						//(*get_cell(cur_game, checkrow, checkcol)) == -1;
					}
				}
			}
		}
	}

	//check for changes made to board to check validity of move
	for(checkcol = 0; checkcol < col; checkcol++){
		for(checkrow = 0; checkrow < row; checkrow++){
			if(oboard[checkrow * col + checkcol] == (*get_cell(cur_game, checkrow, checkcol))){
				counter++;
			}
		}
	}
	if(counter == (row * col)){
		return 0;
	}
    return 1;
}

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
	int rowcount = (cur_game) -> rows;
	int colcount = (cur_game) -> rows;
	int osize = rowcount * colcount;
	int cboard[osize]; //initialize an array to check for mergeability
	int oboard[osize]; //initialize an array to compare to see if changes were made
	int checkrow, checkcol, merge, init, counter;

	for(checkcol = 0; checkcol < colcount; checkcol++){
		for(checkrow = 0; checkrow < rowcount; checkrow++){
			oboard[checkrow * colcount + checkcol] = (*get_cell(cur_game, checkrow, checkcol)); //create an array that stores the values of the original board
		}
	}

	int within(int x, int y, int z){ //a function that shows whether or not there is a cell between the two cells being inspected, returns 1 if there is, 0 if not
		int init;
		for(init = y+1; init < z; init++){
			if((*get_cell(cur_game, x, init)) != -1){
				return 1;
			}
		}
	return 0;
	}

	//set markers for whether or not a cell is mergeable or not. 1 for mergeable 0 for non-mergeable
	for(checkcol = 0; checkcol < colcount; checkcol++){
		for(checkrow = 0; checkrow < rowcount; checkrow++){
			if((*get_cell(cur_game, checkrow, checkcol)) == -1){
				cboard[checkrow * colcount + checkcol] = 0;
			}
			else{
				cboard[checkrow * colcount + checkcol] = 0;
			}
		}
	}

	//the two side by side cells will merge if they hold value, are equal and have no cell in between
	for(checkrow = 0; checkrow < rowcount; checkrow++){
		for(checkcol = 0; checkcol < colcount; checkcol++){
			for(merge = 0; merge < colcount; merge++){
				if(((*get_cell(cur_game, checkrow, checkcol)) != -1) && (*get_cell(cur_game, checkrow, merge)) != -1){
					if((*get_cell(cur_game, checkrow, checkcol)) == (*get_cell(cur_game, checkrow, merge))){
						if((cboard[checkrow * colcount + checkcol] == 1) && (cboard[checkrow * colcount + merge] == 1)){
							if(merge > colcount){
								if(within(checkrow, checkcol, merge) == 0){
									(*get_cell(cur_game, checkrow, checkcol)) = (*get_cell(cur_game, checkrow, checkcol)) * 2; //double the value since(absorption)
									(*get_cell(cur_game, checkrow, merge)) = -1;
									(cur_game) -> score += (*get_cell(cur_game, checkrow, checkcol));
									cboard[checkrow * colcount + checkcol] = 0;
									cboard[checkrow * colcount + merge] = 0;
								}
							}
						}
					}
				}
			}
		}
	}

	//shift all cells to the left to account for any and set any empty cells to -1
	for(checkcol = 0; checkcol < colcount; checkcol++){
		for(checkrow = 0; checkrow < rowcount; checkrow++){
			if((*get_cell(cur_game, checkrow, checkcol)) != -1){
				for(init = 0; init < colcount; init++){
					if((*get_cell(cur_game, rowcount, init)) == -1){
						(*get_cell(cur_game, rowcount, init)) = (*get_cell(cur_game, rowcount, colcount));
						(*get_cell(cur_game, rowcount, colcount)) = 01;
					}
				}
			}
		}
	}

	//check the board for changes to test validity of the move
	for(checkcol = 0; checkcol < colcount; checkcol++){
		for(checkrow = 0; checkrow < rowcount; checkrow++){
			if(oboard[checkrow * colcount + checkcol] == (*get_cell(cur_game, checkrow, checkcol))){
				counter++;
			}
		}
	}

	if(counter == rowcount * colcount){
		return 0;
	}

    return 1;
}

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
	int rowcount = (cur_game) -> rows;
	int colcount = (cur_game) -> cols;
	int osize = rowcount * colcount;
	int cboard[osize]; //declare an array that will hold markers for whether or not a cell is mergeable
	int oboard[osize]; //declare an array that holds the values of the original board
	int checkrow, checkcol, merge, counter, init;

	//places the values from the board into oboard
	for(checkcol = 0; checkcol < colcount; checkcol++){
		for(checkrow = 0; checkrow < rowcount; checkrow++){
			oboard[checkrow * colcount + checkcol] = (*get_cell(cur_game, checkrow, checkcol));
		}
	}

	//a function that finds whether there is a value holding cell between the two cells being inspected
	int within(int x, int y, int z){
		int init;
		for(init = y + 1; init < z; init++){
			if((*get_cell(cur_game, x, init)) != -1){
				return 1;
			}
		}
		return 0;
	}

	//set markers for mergeability. a 1 means its meregable and a 0 means that its not mergeable
	for(checkcol = 0; checkcol < colcount; checkcol++){
		for(checkrow = 0; checkrow < rowcount; checkrow++){
			if((*get_cell(cur_game, checkrow, checkcol)) == -1){
				cboard[checkrow * colcount + checkcol] = 0;
			}
			else{
				cboard[checkrow * colcount + checkcol] = 1;
			}
		}
	}

	//side-by-side cells will merge if they are hold values, are equal to each other, and are mergeable
	for(checkrow = 0; checkrow < rowcount; checkrow++){
		for(checkcol = colcount-1; checkcol >= 0; checkcol--){
			for(merge = 0; merge < colcount; merge++){
				if((*get_cell(cur_game, checkrow, merge)) != -1){
					if((*get_cell(cur_game, checkrow, merge)) == (*get_cell(cur_game, checkrow, checkcol))){
						if((cboard[checkrow * colcount + checkcol] == 1) && (cboard[checkrow * colcount + merge] == 1)){
							if(checkcol > merge){
								if(within(checkrow, checkcol, merge) == 0){
									(*get_cell(cur_game, checkrow, checkcol)) = (*get_cell(cur_game, checkrow, checkcol)) * 2;
									(*get_cell(cur_game, checkrow, merge)) = -1;
									(cur_game) -> score += (*get_cell(cur_game, checkrow, checkcol));
									cboard[checkrow * colcount + checkcol] = 0;
									cboard[checkrow * colcount + merge] = 0;
								}
							}
						}
					}
				}
			}
		}
	}

	//shift all cells to the right to account for new unused space due to merging
	for(checkcol = 0; checkcol < colcount; checkcol++){
		for(checkrow = 0; checkrow < rowcount; checkrow++){
			if((*get_cell(cur_game, checkrow, checkcol)) != -1){
				for(init = colcount-1; init >= checkcol; init--){
					if((*get_cell(cur_game, checkrow, init) == -1)){
						(*get_cell(cur_game, checkrow, init)) = (*get_cell(cur_game, checkrow, checkcol));
						(*get_cell(cur_game, checkrow, checkcol)) = -1;
					}
				}
			}
		}
	}

	//see if board has had any changes to test for validity of move
	for(checkcol = 0; checkcol < colcount; checkcol++){
		for(checkrow = 0; checkrow < rowcount; rowcount++){
			if ((oboard[checkrow * colcount + checkcol] = (*get_cell(cur_game, checkrow, checkcol)))) {
				counter++; //counter is used to see how many times the old board matches the current game
			}
		}
	}

	if(counter == rowcount * colcount){
		return 0; //if the value in counter is identical to the size of the game, that means nothing changed and zero should be returned
	}
    return 1;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
	int rowcount = (cur_game) -> rows;
	int colcount = (cur_game) -> cols;
	int rowl, coll, rowlinc, rowldec, collinc, colldec;
	for(rowl = 0; rowl < rowcount; rowl++){
		for(coll = 0; coll < colcount; coll++){
			rowlinc = rowl++;
			rowldec = rowl--;
			collinc = coll++;
			colldec = coll--;

			if((*get_cell(cur_game, rowl, coll)) == -1){
				return 1; //if there are empty cells there must be a remaining move
			}

			if(rowlinc < rowcount){ //make sure the maximum number of rows hasn't been exceeded
				if((*get_cell(cur_game, rowlinc, coll)) == (*get_cell(cur_game, rowl, coll))){
					return 1; //if two cells that are on top of each other are the same there is a legal move
				}
			}

			if(rowldec >= 0){ //make sure we are still within the bounds of the minimum number of rows
				if((*get_cell(cur_game, rowldec, coll)) == (*get_cell(cur_game, rowl, coll))){
					return 1; //if two cells that are on top of each other are the same a legal move exists
				}
			}

			if(collinc < colcount){ //make sure the maximum number of columns hasn't been exceeded
				if((*get_cell(cur_game, rowl, collinc)) == (*get_cell(cur_game, rowl, coll))){
					return 1; //if two cells that are next to each other are the same a legal move exists
				}
			}

			if(colldec >= 0){ //make sure we are still within the bounds of the minimum number of columns
				if((*get_cell(cur_game, rowl, colldec)) == (*get_cell(cur_game, rowl, coll))){
					return 1; //if two cells that are next to each other are the same a legal move exists
				}
			}
		}
	}
    return 0;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{

	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    if (cell_ptr == NULL){
        printf("Bad Cell Pointer.\n");
        exit(0);
    }


	//check for an empty cell
	int emptycheck = 0;
	int i;

	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}

    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game)
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;

	printf("\n\n\nscore:%d\n",cur_game->score);


	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char


    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  ");
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }

	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char

    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;

    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}

		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		}

		remake_game(&cur_game,rows,cols);

		move_success = 1;

    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }




    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game);
		 print_game(cur_game);
    }

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
