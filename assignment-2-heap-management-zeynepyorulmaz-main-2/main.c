// Write your full name: ZEYNEP YORULMAZ, write your KU ID: 83684

#include <stdio.h>
#include <stdlib.h>

#define EMPTY '-'
#define HERBIVORE 'H'
#define CARNIVORE 'C'
#define PLANT 'P'

// Function Prototypes
char** read_map_from_txt(const char* filename, int *width, int *height);
void print_grid(char** grid, int width, int height);
char** create_temp_grid(char** grid, int width, int height);
void cleanup_grid(char** grid, int height);
void simulate(char** grid, int width, int height, int numSteps);
void grow_plants(char** grid, int width, int height);
void move_herbivores(char** grid, int width, int height);
void move_carnivores(char** grid, int width, int height);


int main(int argc, char **argv) {
    int width, height;
    char *filename = argv[1];
    int numSteps = atoi(argv[2]);
    char **grid = read_map_from_txt(filename, &width, &height);

    printf("Initial Grid:\n");
    print_grid(grid, width, height);
    printf("\n\n");


    simulate(grid, width, height,numSteps);

    
    cleanup_grid(grid, height);

    return 0;
}



char** read_map_from_txt(const char* filename, int *width, int *height) {
    
    //Reads the map from the file and returns a 2D array of characters.
    
    FILE *file = fopen(filename, "r");

    fscanf(file, "%d", width);
    fscanf(file, "%d", height);

    char** grid = (char**)malloc(*height * sizeof(char*)); // Allocate memory for the rows
    for (int i = 0; i < *height; i++) { // Read the grid from the file
        grid[i] = (char*)malloc((*width + 1) * sizeof(char)); // Allocate memory for the columns
        fscanf(file, "%s", grid[i]); // Read the row
    }

    fclose(file);
    return grid;
}

void print_grid(char** grid, int width, int height) {
    
    //Print grid to the console with one extra new line at the end for readability.
    
    for (int i = 0; i < height; i++) { // Loop through each row
        for (int j = 0; j < width; j++) {
            printf("%c ", grid[i][j]);// Print each cell
        }
        printf("\n");
    }
    printf("\n");
}

void cleanup_grid(char** grid, int height) {
    
    //Free the memory allocated for the grid.
    
    for (int i = 0; i < height; i++) {
        free(grid[i]); // Free the memory for each row
    }
    free(grid);
}
char** create_temp_grid(char** grid, int width, int height) {
    
    //Create a temporary grid to store the state of the grid.
    
    char** tempGrid = (char**)malloc(height * sizeof(char*)); // Allocate memory for the rows
    for (int i = 0; i < height; i++) {
        tempGrid[i] = (char*)malloc((width + 1) * sizeof(char)); // Allocate memory for the columns
        for (int j = 0; j < width; j++) {
            tempGrid[i][j] = grid[i][j]; // Copy the cells of the grid
        }
        tempGrid[i][width] = '\0'; // Null-terminate the string
    }
    return tempGrid;
}

void grow_plants(char** grid, int width, int height) {
    char** tempGrid = create_temp_grid(grid, width, height); // Create a temporary grid to store the new state

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (grid[i][j] == PLANT) { // If the cell is a plant
                if (i > 0 && j > 0 && grid[i - 1][j - 1] == EMPTY) tempGrid[i - 1][j - 1] = PLANT; 
                if (i > 0 && j < width - 1 && grid[i - 1][j + 1] == EMPTY) tempGrid[i - 1][j + 1] = PLANT;
                if (i < height - 1 && j > 0 && grid[i + 1][j - 1] == EMPTY) tempGrid[i + 1][j - 1] = PLANT;
                if (i < height - 1 && j < width - 1 && grid[i + 1][j + 1] == EMPTY) tempGrid[i + 1][j + 1] = PLANT;
            }
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            grid[i][j] = tempGrid[i][j]; // Copy the new state to the original grid
        }
    }

    cleanup_grid(tempGrid, height); // Free the memory for the temporary grid
}

void move_herbivores(char** grid, int width, int height) {
    char** tempGrid = create_temp_grid(grid, width, height); // Create a temporary grid to store the new state

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (grid[i][j] == HERBIVORE) { // If the cell is a herbivore
                if ((i > 0 && grid[i - 1][j] == PLANT) || (i < height - 1 && grid[i + 1][j] == PLANT) || 
                    (j > 0 && grid[i][j - 1] == PLANT) || (j < width - 1 && grid[i][j + 1] == PLANT) ||
                    (i > 0 && j > 0 && grid[i - 1][j - 1] == PLANT) || (i > 0 && j < width - 1 && grid[i - 1][j + 1] == PLANT) ||
                    (i < height - 1 && j > 0 && grid[i + 1][j - 1] == PLANT) || (i < height - 1 && j < width - 1 && grid[i + 1][j + 1] == PLANT)) {
                    if (i > 0 && grid[i - 1][j] == PLANT) tempGrid[i - 1][j] = HERBIVORE;
                    if (i < height - 1 && grid[i + 1][j] == PLANT) tempGrid[i + 1][j] = HERBIVORE;
                    if (j > 0 && grid[i][j - 1] == PLANT) tempGrid[i][j - 1] = HERBIVORE;
                    if (j < width - 1 && grid[i][j + 1] == PLANT) tempGrid[i][j + 1] = HERBIVORE;
                    if (i > 0 && j > 0 && grid[i - 1][j - 1] == PLANT) tempGrid[i - 1][j - 1] = HERBIVORE;
                    if (i > 0 && j < width - 1 && grid[i - 1][j + 1] == PLANT) tempGrid[i - 1][j + 1] = HERBIVORE;
                    if (i < height - 1 && j > 0 && grid[i + 1][j - 1] == PLANT) tempGrid[i + 1][j - 1] = HERBIVORE;
                    if (i < height - 1 && j < width - 1 && grid[i + 1][j + 1] == PLANT) tempGrid[i + 1][j + 1] = HERBIVORE;
                } else {
                    tempGrid[i][j] = EMPTY; // If there is no plant nearby, the herbivore dies
                }
            }
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            grid[i][j] = tempGrid[i][j]; // Copy the new state to the original grid
        }
    }

    cleanup_grid(tempGrid, height); // Free the memory for the temporary grid
}

void move_carnivores(char** grid, int width, int height){
    char** tempGrid = create_temp_grid(grid, width, height); // Create a temporary grid to store the new state

    for (int i = 0; i < height; i++){
    	for (int j = 0; j < width; j++){
		if (grid[i][j] == CARNIVORE){ // If the cell is a carnivore
			if ((i > 0 && grid[i - 1][j] == HERBIVORE) || (i < height - 1 && grid[i + 1][j] == HERBIVORE) | (j > 0 && grid[i][j - 1] == HERBIVORE) || (j < width - 1 && grid[i][j + 1] == HERBIVORE) || (i > 0 && j > 0 && grid[i - 1][j - 1] == HERBIVORE) || (i > 0 && j < width - 1 && grid[i - 1][j + 1] == HERBIVORE) || (i < height - 1 && j > 0 && grid[i + 1][j - 1] == HERBIVORE) || (i < height - 1 && j < width - 1 && grid[i + 1][j + 1] == HERBIVORE)){
				if (i > 0 && grid[i - 1][j] == HERBIVORE)
					tempGrid[i-1][j] = PLANT;
				if (i < height - 1 && grid[i + 1][j] == HERBIVORE)
					tempGrid[i+1][j] = PLANT;

				if (j > 0 && grid[i][j - 1] == HERBIVORE)
					tempGrid[i][j-1] = PLANT;

				if (j < width - 1 && grid[i][j + 1] == HERBIVORE)
					tempGrid[i][j+1] = PLANT;

				if (i > 0 && j > 0 && grid[i - 1][j - 1] == HERBIVORE)
					tempGrid[i-1][j-1] = CARNIVORE;

				if (i > 0 && j < width - 1 && grid[i - 1][j + 1] == HERBIVORE)
					tempGrid[i-1][j+1] = CARNIVORE;
				if (i < height - 1 && j > 0 && grid[i + 1][j - 1] == HERBIVORE)
					tempGrid[i+1][j-1] = CARNIVORE;
				if (i < height - 1 && j < width - 1 && grid[i + 1][j + 1] == HERBIVORE)
					tempGrid[i+1][j+1] = CARNIVORE;


		}
        else{
			tempGrid[i][j] = EMPTY; // If there is no herbivore nearby, the carnivore dies
		}


	}
        }
   }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            grid[i][j] = tempGrid[i][j]; // Copy the new state to the original grid
        }
    }

    cleanup_grid(tempGrid, height); // Free the memory for the temporary grid
}


void simulate(char** grid, int width, int height, int numSteps) {  
    /**Simulate the grid for numSteps.
    At each step, grow plants, move herbivores, and move carnivores in the order. 
    You are encouraged to write seperate functions for each of these tasks.
    You can copy the grid to a temporary grid and then update the grid for each movement.
    You can write helper functions to use common in the movement of herbivores and carnivores.
    Make sure you print the grid 3 times (after each movement) for each step.
    Make sure you free all the allocated memory. (Valgrind can be useful for this)
    Try to code step by step and clearly understandable which will make both the task easier for you and grading easier for us.
    Good Luck*/
 

        for (int step = 0; step < numSteps; step++) { // Loop through each step
        printf("\n");
        grow_plants(grid, width, height); // Grow plants
        print_grid(grid, width, height); // Print the grid
        printf("\n");

        move_herbivores(grid, width, height); // Move herbivores
        print_grid(grid, width, height);
        printf("\n");

        move_carnivores(grid, width, height); // Move carnivores
        print_grid(grid, width, height);
        printf("\n");
        printf("----------------------------------\n");
	}

}
