#pragma once

enum CellType
{
	EMPTY_SPACE,
	WALL,
	START_POINT,
	TARGET_POINT,
	CURRENT_CELL,
	VISITED_CELL,
	BACK_CURRENT_CELL,
	BACK_VISITED_CELL,
	PATH
};

const int MSZ = 40;

class Maze
{
	private:
		int maze[MSZ][MSZ] = {0};
		int rows, cols;
		int startRow, startCol;
		int targetRow, targetCol;

	public:
		Maze(int rows, int cols, int startRow, int startCol, int targetRow, int targetCol) : 
			rows(rows),
			cols(cols),
			startRow(startRow),
			startCol(startCol),
			targetRow(targetRow),
			targetCol(targetCol)
		{
			InitMaze();
		};


		void InitMaze();
		void DrawMaze();

		int (*getMaze())[MSZ] { 
			return maze; 
		}

		int getStartRow() {
			return startRow; 
		}

		int getStartCol() {
			return startCol; 
		}

		int getTargetRow() {
			return targetRow; 
		}

		int getTargetCol() {
			return targetCol; 
		}
};