#include <iostream>
#include "BFSHandler.h"

void BFSHandler::RunBidirectionalBFS() {
	// Run BFS from start point
	RunDirectionalBFS(START_POINT);

	// Run BFS from target point
	RunDirectionalBFS(TARGET_POINT);

	// If there is no solution or we found a path
	if (!runBFS) {
		if (status == FOUND)
			std::cout << "Found a path\n";
		else // status == NOT_FOUND
			std::cout << "There is no solution\n";
	}
}

void BFSHandler::RunDirectionalBFS(CellType type) {
	Cell* pc;
	int row, col;
	bool go_on = true;

	std::queue <Cell*> *queue = getQueueByType(type);

	if (queue->empty())
	{
		runBFS = false;
		return;
	}
	else // grays is not empty
	{
		// pick the first Cell from queue
		pc = queue->front();
		queue->pop();

		row = pc->getRow();
		col = pc->getCol();

		// Paint it visited color
		if (maze->getMaze()[row][col] != START_POINT &&
			maze->getMaze()[row][col] != TARGET_POINT) {
			maze->getMaze()[row][col] = (type == START_POINT) ? VISITED_CELL : BACK_VISITED_CELL;
		}

		// up
		if (maze->getMaze()[row + 1][col] != WALL)
			CheckNeighbour(row + 1, col, pc, type);
		// down
		if (maze->getMaze()[row - 1][col] != WALL)
			CheckNeighbour(row - 1, col, pc, type);
		// left
		if (maze->getMaze()[row][col - 1] != WALL)
			CheckNeighbour(row, col - 1, pc, type);
		// right
		if (maze->getMaze()[row][col + 1] != WALL)
			CheckNeighbour(row, col + 1, pc, type);

	}
}

// BFS a cell on row,col can be either WHITE or TARGET
bool BFSHandler::CheckNeighbour(int row, int col, Cell* pc, CellType type)
{
	Cell* pn = nullptr;
	std::queue <Cell*>* queue = getQueueByType(type);

	if (maze->getMaze()[row][col] == EMPTY_SPACE) {
		// create new Cell
		pn = new Cell(row, col, pc);
		queue->push(pn);
		// paint it current color
		maze->getMaze()[row][col] = type == TARGET_POINT ? BACK_CURRENT_CELL : CURRENT_CELL;
		return true; // go_on = true
	}
	// if the cell is current or back current
	// checks if both searches met in the same cell
	else if ((maze->getMaze()[row][col] == CURRENT_CELL && type == TARGET_POINT) ||
		(maze->getMaze()[row][col] == BACK_CURRENT_CELL && type == START_POINT)) {
		pn = findCellInQueue((type == TARGET_POINT) ? startQueue : targetQueue, row, col);
	}
	// if the cell is blocked or was visited
	else {
		return false; // go_on = false
	}

	// found a path, restore it, change flags and return
	RestorePath(pc);
	RestorePath(pn);
	runBFS = false;
	status = FOUND;

	return false;
}

// Draw the path from the target to the start
void BFSHandler::RestorePath(Cell* pc)
{
	while (pc != nullptr)
	{
		// Draw the path if not start or target
		if (maze->getMaze()[pc->getRow()][pc->getCol()] != START_POINT &&
			maze->getMaze()[pc->getRow()][pc->getCol()] != TARGET_POINT) {

			// Paint it path color
			maze->getMaze()[pc->getRow()][pc->getCol()] = PATH;
		}

		pc = pc->getParent();
	}
}

// Find a cell in a queue
Cell* BFSHandler::findCellInQueue(std::queue <Cell*>* queue, int row, int col) {
	Cell* pc = nullptr;

	while (!queue->empty()) {
		pc = queue->front();

		if (pc->getRow() == row && pc->getCol() == col)
			return pc;

		queue->pop();
	}

	return nullptr;
}