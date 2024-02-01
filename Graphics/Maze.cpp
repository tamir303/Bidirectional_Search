#include <stdlib.h>
#include <iostream>
#include "glut.h"
#include "Maze.h"

void Maze::InitMaze() {
	int i, j;

	for (i = 0; i < MSZ; i++)
	{
		maze[0][i] = WALL;
		maze[MSZ - 1][i] = WALL;
		maze[i][0] = WALL;
		maze[i][MSZ - 1] = WALL;
	}

	for (i = 1; i < MSZ - 1; i++)
		for (j = 1; j < MSZ - 1; j++)
		{
			if (i % 2 == 1) // mostly spaces
			{
				if (rand() % 10 < 2) // WALL
					maze[i][j] = WALL;
				else maze[i][j] = EMPTY_SPACE;
			}
			else // even lines
			{
				if (rand() % 10 < 4) // space
					maze[i][j] = EMPTY_SPACE;
				else
					maze[i][j] = WALL;
			}
		}
	maze[startRow][startCol] = START_POINT;
	maze[targetRow][targetCol] = TARGET_POINT;

	std::cout << "Start point: " << startRow << ", " << startCol << std::endl;
	std::cout << "Target point: " << targetRow << ", " << targetCol << std::endl;
}

void Maze::DrawMaze() {
	int i, j;

	for (i = 0; i < MSZ; i++)
		for (j = 0; j < MSZ; j++)
		{
			switch (maze[i][j]) // set convinient color of a cell
			{
			case EMPTY_SPACE:
				glColor3d(1, 1, 1); // White
				break;
			case WALL:
				glColor3d(0, 0, 0); // Black
				break;
			case START_POINT:
				glColor3d(0.5, 0.5, 1); // Light Blue
				break;
			case TARGET_POINT:
				glColor3d(1, 0, 0); // Red
				break;
			case CURRENT_CELL:
				glColor3d(1, 0.7, 0); // Orange
				break;
			case BACK_CURRENT_CELL:
				glColor3d(0.2, 0.2, 0.7); // Dark Blue
				break;
			case VISITED_CELL:
				glColor3d(0.8, 1, 0.8); // Light Green
				break;
			case BACK_VISITED_CELL:
				glColor3d(0, 1, 1); // Cyan
				break;
			case PATH:
				glColor3d(1, 0, 1); // Magenta
				break;

			}

			glBegin(GL_POLYGON);
			glVertex2d(j, i);
			glVertex2d(j, i + 1);
			glVertex2d(j + 1, i + 1);
			glVertex2d(j + 1, i);
			glEnd();
		}
}