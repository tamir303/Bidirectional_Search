#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "glut.h"
#include <queue>
#include "BFSHandler.h"
#include <iostream>

using namespace std;

Maze* pm; // maze object
BFSHandler* pbfs; // BFS handler object

// initialize maze and start cell
void init()
{
	glClearColor(0.5, 0.5, 0.5, 0);// color of window background
	glOrtho(0, MSZ, 0, MSZ, -1, 1); // set the coordinates system
	srand(time(0));

	// create maze properties
	int rows = MSZ, cols = MSZ;
	int startRow = MSZ / 2, startCol = MSZ / 2;
	int targetRow = rand() % MSZ, targetCol = rand() % MSZ;

	// create maze object
	pm = new Maze(rows, cols, startRow, startCol, targetRow, targetCol);

	// create BFS handler object
	pbfs = new BFSHandler(pm);
}

// drawings are here
void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer with background color

	pm->DrawMaze(); // draw maze

	glutSwapBuffers(); // show all
}

// idle function - glut calls it when nothing happens
void idle() 
{
	if (pbfs->getRunBFS())
		pbfs->RunBidirectionalBFS();

	glutPostRedisplay(); // call to display indirectly
}

// menu 
void menu(int)
{
	pbfs->setRunBFSTrue();
}

void main(int argc, char* argv[]) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("Bi-BFS Example");

	glutDisplayFunc(display); // refresh function
	glutIdleFunc(idle);  // updates function

	// menu
	glutCreateMenu(menu);
	glutAddMenuEntry("run Bi-BFS", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();
	glutMainLoop();
}