#include "sudoku.h"
/*partners: nroger5, davidrs3, airra2
In this MP we developed a program to solve a sudoku puzzle. For this we checked for an unassigned spot using for loops 
and then looked for a valid value by checking the rows and columns and section of the said unassigned 
spot. Then we checked for a valid number to be placed inside the unassigned spot.
// if it was valid we replaced the value of zero with the valid value. If all spots were already filled the function
 would skip the entire process and return
to the main function
*/
// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
// new functon: unassigned_c
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {// using loops checks for validity
  assert(i>=0 && i<9);
  // BEG TODO
  int j;
  for(j=0; j<9;j++){
    if(sudoku[i][j]==val){
      return 1;
    }
  }
  return 0;
  // END TODO
}
// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {//using loops checks for validity
  assert(j>=0 && j<9);
  // BEG TODO
  int i;
  for(i=0;i<9;i++){
    if(sudoku[i][j]==val){
      return 1;
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {//using loops also checks for validity
  assert(i>=0 && i<9);
    // BEG TODO
    //int starti= i/3*3
    //int startj=j/3*3;
  for (int row =(i/3)*3; row < (i/3)*3+3; row++)//starts the square off at the start of the square
  { 
    for (int col= (j/3)*3; col < (j/3)*3+3; col++)
      { 
            if (sudoku[row][col]==val)
            { 
              return 1;
            }
       }
  }
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {// finds if all statements pass
  assert(i>=0 && i<9 && j>=0 && j<9);
  //BEG TODO
  
  int a;
  int b;
  int c;
    a=is_val_in_3x3_zone (val,i,j,sudoku);//calls all functions to test
    b=is_val_in_col (val, j,sudoku);
    c= is_val_in_row (val,i,sudoku);
      if(a==0 && b==0 && c==0){
        return 1;
      }
   //END TODO 
/*if (!is_val_in_row && !is_val_in_col && !is_val_in_3x3_zone){
	return 1;
  }*/
  return 0;
}

int unassigned_C(int unassigned[2], int sudoku[9][9])
  {
    for( int i = 0; i < 9; i++)//checks for unassigned cell and sends it over in the solve sudoku
    {                                  	
	    for( int j = 0; j < 9; j++)
      {                                	
  	    if(sudoku[i][j] == 0)
        {       
    	    unassigned[0] = i;
        	unassigned[1] = j;
         	return 0;
  	    }
	    }
    }
   return 1;
  }


// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) 
{
  // BEG TODO
 //int unassignedcell=0;
  int i, j,nm;
  int unassigned[2]; 
  if(unassigned_C(unassigned,sudoku)==1)
    {
    return 1;
    }
  else 
    { i=unassigned[0];
      j=unassigned[1];
    }
	  /*for(i=0; i<9;i++)
    {                     //counter for row
		  for(j=0;j<9;j++)
      {
			  if(sudoku[i][j]==0)
        {
			    unassignedcell++;
			  }
		  }
	  }
	if(unassignedcell==0)
  {
		return 1;
	}
  else
  { 
    //int unassigned[2];
    if(unassigned_C(unassigned,sudoku)==0)
    {
      i=unassigned[0];
      j=unassigned[1];
    }
    
  }*/



for(nm=1;nm<=9;nm++)
  {
    int v;
	  v = is_val_valid(nm, i, j,sudoku);
		  if (v == 1)
      { //is_val_valid
			  sudoku[i][j] = nm; //counters
			    if (solve_sudoku(sudoku)==1)
          { //recursive case
				return 1;
			    }
			sudoku[i][j] = 0; //counters cells
		  }
  // END TODO
  }
  return 0;
}
// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
