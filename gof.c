#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 100
#define HEIGHT 100

unsigned char grid_a[HEIGHT][WIDTH];
unsigned char grid_b[HEIGHT][WIDTH];

unsigned char (*current)[WIDTH] = grid_a;
unsigned char (*next)[WIDTH] = grid_b;

void initialize_grid(unsigned char grid[HEIGHT][WIDTH])
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			grid[i][j] = rand() % 2;
		}
	}
}

void print_grid(unsigned char grid[HEIGHT][WIDTH])
{
	printf("\033[H");
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			printf("%s", grid[i][j] ? "X" : " ");
		}
		printf("\n");
	}

	fflush(stdout);
}

int count_alive_neighbours(unsigned char grid[HEIGHT][WIDTH], int i, int j)
{
	int count = 0;

	int up = (i + HEIGHT -1) % HEIGHT;
	int down = (j + 1) % HEIGHT;

	int left = (j + WIDTH - 1) % WIDTH;
	int right = (j + 1) % WIDTH;

	count += grid[up][left];
	count += grid[up][j];
	count += grid[up][right];
	
	count += grid[i][left];
	count += grid[i][right];
	
	count += grid[down][left];
	count += grid[down][j];
	count += grid[down][right];
	
	return count;
}

void update_grid()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			int count = count_alive_neighbours(current, i, j);

			if (current[i][j])
			{
				next[i][j] = count == 2 || count == 3;
			} else {
				next[i][j] = count == 3;
			}
		}
	}
}

int main()
{
	srand(time(NULL));
	initialize_grid(current);

	printf("\033[2J\033[H");

	for(;;)
	{
		print_grid(current);
		update_grid(current, next);

		int (*temp)[WIDTH] = current;
		current = next;
		next = temp;

		usleep(1000000);
	}

	return 0;
}
