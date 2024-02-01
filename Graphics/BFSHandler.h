#pragma once

#include <queue>
#include "Maze.h"
#include "Cell.h"

enum Status { NO_RUN_YET, FOUND, NOT_FOUND };

class BFSHandler {
private :
	Maze* maze;

	// startQueue is the queue from the start point
	std::queue <Cell*> *startQueue = new std::queue <Cell*>;

	// targetQueue is the queue from the target point
	std::queue <Cell*> *targetQueue = new std::queue <Cell*>;

	// BFS run flags
	bool runBFS;
	Status status;

	// Run BFS from a specific point
	void RunDirectionalBFS(CellType);

	// Find a cell in a queue
	Cell* findCellInQueue(std::queue <Cell*>* queue, int row, int col);
public:
	BFSHandler(Maze* pm) : maze(pm), runBFS(false), status(NO_RUN_YET)
	{
		Cell* pc_start = new Cell(maze->getStartRow(), maze->getStartCol(), nullptr);
		Cell* pc_end = new Cell(maze->getTargetRow(), maze->getTargetCol(), nullptr);
		startQueue->push(pc_start);
		targetQueue->push(pc_end);
	}

	// Get the queue based on the type (start or target)
	std::queue <Cell*>* getQueueByType(CellType type) {
		if (type == START_POINT)
			return startQueue;
		else return targetQueue;
	}

	bool getRunBFS() { 
		return runBFS; 
	}

	Status getStatus() {
		return status;
	}

	void setRunBFSTrue() {
		if (status == NO_RUN_YET)
			runBFS = true;
	}
	
	// Draw the path from the target to the start
	void RestorePath(Cell* pc);

	// BFS a cell on row,col can be either WHITE or TARGET
	bool CheckNeighbour(int row, int col, Cell* pc, CellType type);

	// Run BFS from the start and from the target
	void RunBidirectionalBFS();
};