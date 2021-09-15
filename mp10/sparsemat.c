/*edited by davidrs3 nroger5 airra2
for this MP we implemented the load_tuples, gv_tuples, set_tuples, save_tuples, add_tuples and destroy_tuples functions
the load_tuples function utilized file IO and while loops to iterate over an input file and store that files information in a sparse matrix
the gv_tuples function too in information from the main program and then iterates over the sparse matrix to find the value at the given location and return it to the user
the set tuples function utilizes several helper functions to add nodes and subtract nodes so that the linked list remains sorted.
the save_tuples function takes a completed linked list and stores all of its information in a file determined by the main program
the add_tuples function receives two different sparse matrices as inputs and stores them in a new matrix
this was done by iterating over the two matrices and adding each of their values into the new matrix
the destroy tuples function utilizies loops to go over the sparse matrix and make sure that every cell is deleted
after that the struct for the matrix itself is freed, preventing any memory leak
*/
#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

int linecount(char* input_file); //helper function that is used to make sure the whole file is read
void freeNode(sp_tuples *mat_t, int row, int col); //helper function to delete an unused node

void freeNode(sp_tuples * mat_t, int row, int col){ //if any node within the last maches, they'll be deleted
    sp_tuples_node * current = mat_t->tuples_head; //create and initialize pointers for the sake of keeping a valid current and next pointer after one is deleted
    sp_tuples_node * last;
    sp_tuples_node * follow;

    while(current != NULL){
        if((current->row == row) && (current->col == col)){
            last = current;
            follow = last->next;
            if(follow == NULL){
                return;
            }
            last->next = follow->next;
            free(follow);
        }
        current = current->next;
    }
    return;
}


int linecount(char* input_file){
    FILE * file;
    char test;
    int lines = 0;
    file = fopen(input_file, "r");
    //take a character to test for end of file
    test = getc(file);
    while(test != EOF){
        if(test == '\n'){
            lines++;
        }
        test = getc(file);
    }
    fclose(file); //close the file
    return lines;
}


sp_tuples * load_tuples(char* input_file)
{
    FILE * file;
    file = fopen(input_file, "r");

    int row, col, i;
    double value;
    char valholder[500]; //holds the data read from the input file

    sp_tuples * tuples = (sp_tuples*)malloc(sizeof(sp_tuples)); //allocate space for sp_tuples
    fscanf(file, "%d %d\n", &row, &col);
    tuples->m = row;
    tuples->n = col;

    for(i = 0; i < linecount(input_file); i++){ //iterate over every line in the file
        while(fgets(valholder, sizeof(valholder), file)){
            sscanf(valholder, "%d %d %lf\n", &row, &col, &value);
            set_tuples(tuples, row, col, value);
        }
    }

    sp_tuples_node * current = tuples->tuples_head;
    tuples->nz = 0;

    while(current != NULL){
        tuples->nz++; //for every non-NULL pointer the non-zeros will increase
        current=current->next;
    }

    fclose(file);
    return tuples;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
    sp_tuples_node * current = mat_t->tuples_head;
    while(current != NULL){ //iterate over the matrix, looking for the value held in the matrix at the inputted row annd column values 
        if((row == current->row) && (col == current->col)){
            return current->value;
        }
        current=current->next;
    }
    return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    //sp_tuples_node * current = mat_t->tuples_head;
    if(value == 0){
        freeNode(mat_t, row, col);
    }
    if(mat_t->tuples_head == NULL){
        mat_t->tuples_head = (sp_tuples_node *)malloc(sizeof(sp_tuples_node)); //declare a new node since none exist yet
        mat_t->tuples_head->row = row;
        mat_t->tuples_head->col = col;
        mat_t->tuples_head->value = value;
        mat_t->nz++; //increment non_zero since node was added
        mat_t->tuples_head->next = NULL;
    }
    sp_tuples_node * current = mat_t->tuples_head;
    sp_tuples_node * ph = current;
    sp_tuples_node * last = NULL;
    if((ph != NULL) && (row < ph->row) && (col < ph->col)){ //have not yet found a position to put the node, need to find a node that either has the same value or has not been filled yet 
        last = ph;
        ph = ph->next;
    }
    if((ph != NULL) && (row == ph->row) && (col == ph->col)){ //nodes hat have already been filled
        ph->value = value;
        if(last != NULL){ //deleted node will not be the head node
            last->next = ph->next;
        }
        if(last == NULL){ //head node will be the deleted node
            mat_t->tuples_head = mat_t->tuples_head->next; //change the head pointer so the current pointer can be deleted
        }
        free(ph);
        mat_t->nz--;
    }
    if(last != NULL){ //since adding a node at the head was already covered by the above, this ensures we don't do it again and mess up our work
        last->next = (sp_tuples_node*)malloc(sizeof(sp_tuples_node)); //create space for the new node
        last->next->row = row;
        last->next->col = col;
        last->next->value = value;
        last->next->next = ph;
        mat_t->nz++;
    }
    
    return;
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
    FILE * file;
    sp_tuples_node * current = mat_t->tuples_head;
    int row, col;
    double value;
    file = fopen(file_name, "w");

    while(current != NULL){ //iterate over the matrix and store all the nonzero values in a file that is inputted by the program
        row = current->row;
        col = current->col;
        value = current->value;
        fprintf(file, "%d %d %lf\n", row, col, value);
        current = current->next;
    }
    fclose(file);
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
    //declare matrix C
    //initialize
    sp_tuples * matC = (sp_tuples*)malloc(sizeof(sp_tuples));
    //set matrix C to be the size of matrices A and B
    int m = matA->m;
    int n = matA->n;
    matC->m = m;
    matC->n = n;
    matC->nz = 0;
    int row, col;
    double sum = 0.0;
    sp_tuples_node * currentA = matA->tuples_head;
    sp_tuples_node * currentB = matB->tuples_head;
    while(currentA != NULL){ //iterate over matrix A and add all of its values to matrixC
        row = currentA->row;
        col = currentA->col;
        sum = gv_tuples(matA, row, col);
        set_tuples(matC, row, col, sum);
        currentA = currentA->next;
    }
    while(currentB != NULL){ //iterate over matrix B and add all of its value to matrixC
        row = currentB->row;
        col = currentB->col;
        sum = gv_tuples(matB, row, col) + gv_tuples(matC, row, col);
        set_tuples(matC, row, col, sum);
        currentB = currentB->next;
    }
    /*while(currentC != NULL){
        matC->nz++;
        currentC=currentC->next;
    }*/
	return matC;
}


// Optional (not graded)
sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
  return NULL;
}


	
void destroy_tuples(sp_tuples * mat_t){
	sp_tuples_node *current = mat_t->tuples_head;
    sp_tuples_node *ph;
    
    if(mat_t->tuples_head == NULL){ //if there is no matrix, just free the struct that would have held the dimensions for the list
        free(mat_t);
        return;
    }
    while(current != NULL){ //iterate over the matrix, free all nodes
        ph = current;
        current = current->next;
        free(ph);
    }
    free(mat_t); //finally free the matrix itself
    return;
}  






