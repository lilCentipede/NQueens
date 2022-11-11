#pragma once
#include <vector>
#include <limits>
#include <assert.h>
#include <iostream>

//columns represent queens, rows represent their place on the table
class Table
{
private:
	int size;
	std::vector<int> places_of_the_queens;
	std::vector<int> conflicts_of_the_queens;
	int getRandomNumberInRange(int begin, int end);
	int maximal(std::vector<int> _vector);
	int minimal(std::vector<int> _vector);
	int returnPositionOfMaximal(std::vector<int> _vector);
	int returnPositionOfMinimal(std::vector<int> _vector);

	void placeQueenRandomly(int _queen);
	int chooseQueenRandomly(std::vector<int> _queens);
	int choosePositionRandomly(std::vector<int> _positions);

public:
	Table();
	Table(int _size);
	Table(int _size,std::vector<int> _places);
	Table(const Table& other);
	~Table();

	void setTable_randomQueens();
	//create another class for initialization?
	void setTable_placeQueensByMinConflict();
	void setTable_placeQueenRelativeToPreviousQueensByMinConflict(int _queen);
	int setTable_getMinConflictPosition(int _queen);

	void printTable();


	int getPlaceOfQueen(int _queen);
	int getConflictsOfQueen(int _queen);
	std::vector<int> getAllQueensWithMaximalConflict();
	std::pair<int, int> findMinimalPositionForQueen(int _queen, int _previous_position, int _previous_conflicts);
	std::pair<std::vector<int>, int> calculateConflictsForEachPosition(int _queen, int _previous_position, int _previous_conflicts);

	int chooseQueenWithMaxConflictsRandomly();

	int placeQueenOnMinConflictPosition();

	void setConflictsOfQueen(int _queen);
	void setConflictsOfAllQueens();

	bool solved();

	bool isThereConflict(int _queen, int other_queen);

	void setQueenAndIncreaseConflictsByPlacingQueen(int _queen, int _new_posiiton, int _new_conflicts);
	void decreaseConflictsByRemovingQueenAndResetQueen(int _queen);

};

