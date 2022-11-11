#include "Table.h"

//Constructors 
Table::Table() : size(0), places_of_the_queens() {}

Table::Table(int _size) : size(_size) {
	srand(time(NULL));
	places_of_the_queens.resize(size,-1);
	conflicts_of_the_queens.resize(size, -1);
	setTable_randomQueens();
	setConflictsOfAllQueens();
}

Table::Table(int _size, std::vector<int> _places) :size(_size),
	places_of_the_queens(_places) {
	conflicts_of_the_queens.resize(size, -1);
	setConflictsOfAllQueens();
}

Table::Table(const Table& other) {
	size = other.size;
	places_of_the_queens = other.places_of_the_queens;
	conflicts_of_the_queens = other.conflicts_of_the_queens;
}

Table::~Table() {}


//Set table methods
void Table::setTable_randomQueens() {
	for (int i = 0; i < size; i++) {
		places_of_the_queens[i] = getRandomNumberInRange(0, size);
	}
}

void Table::setTable_placeQueensByMinConflict() {
	placeQueenRandomly(0);
	for (int i = 1; i < size; i++) {
		setTable_placeQueenRelativeToPreviousQueensByMinConflict(i);
	}
}

//this will make a lot of conflicts because everytime I set a queen, I will increment the conflicts of the other without checking
void Table::setTable_placeQueenRelativeToPreviousQueensByMinConflict(int _queen) {
	int position_minConflict = setTable_getMinConflictPosition(_queen);
	places_of_the_queens[_queen] = position_minConflict;
}

//make copy of this function and make another to return vector of all minimal conflict positions, not just one
int Table::setTable_getMinConflictPosition(int _queen) {
	int position_min_conflicts = -1;
	int min_conflicts = INT_MAX;
	for (int i = 0; i < size; i++) {
		int i_conflicts = 0;
		for (int j = 0; j < _queen; j++) {
			i_conflicts = isThereConflict(_queen, j) ?
				i_conflicts + 1 : i_conflicts;
		}
		if (min_conflicts > i_conflicts) {
			min_conflicts = i_conflicts;
			position_min_conflicts = i;
		}
	}
	assert(position_min_conflicts != -1);
	return position_min_conflicts;
}

//---------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------


//private methods
int Table::maximal(std::vector<int> _vector) {
	int maximal = INT_MIN;
	for (int i = 0; i < _vector.size(); i++) {
		maximal = std::max(_vector[i], maximal);
	}
	return maximal;
}

int Table::minimal(std::vector<int> _vector) {
	int minimal = INT_MAX;
	for (int i = 0; i < _vector.size(); i++) {
		minimal = std::min(_vector[i], minimal);
	}
	return minimal;
}

int Table::returnPositionOfMaximal(std::vector<int> _vector) {
	int maximal = INT_MIN;
	int max_pos = INT_MIN;
	for (int i = 0; i < _vector.size(); i++) {
		if (maximal < _vector[i]) {
			maximal = _vector[i];
			max_pos = i;
		}
	}
	return max_pos;
}

int Table::returnPositionOfMinimal(std::vector<int> _vector) {
	int minimal = INT_MAX;
	int min_pos = INT_MAX;
	for (int i = 0; i < _vector.size(); i++) {
		if (minimal > _vector[i]) {
			minimal = _vector[i];
			min_pos = i;
		}
	}
	return min_pos;
}

int Table::getRandomNumberInRange(int offset, int range) {
	return offset + rand() % range;
}

int Table::chooseQueenRandomly(std::vector<int> _queens) {
	int queen = getRandomNumberInRange(0, _queens.size());
	return _queens[queen];
}

int Table::choosePositionRandomly(std::vector<int> _positions) {
	int position = getRandomNumberInRange(0, _positions.size());
	return _positions[position];
}

//optimization?
bool Table::solved() {
	for (int i = 0; i < size; i++) {
		if (conflicts_of_the_queens[i] != 0)
			return false;
	}
	return true;
}

//Getters
int Table::getPlaceOfQueen(int _queen) {
	return places_of_the_queens[_queen];
}

int Table::getConflictsOfQueen(int _queen) {
	return conflicts_of_the_queens[_queen];
}

std::vector<int> Table::getAllQueensWithMaximalConflict() {
	int maximal_conflicts = maximal(conflicts_of_the_queens);
	std::vector<int> all_maximal_conflict_queens;
	for (int i = 0; i < size; i++) {
		if (conflicts_of_the_queens[i] == maximal_conflicts) {
			all_maximal_conflict_queens.push_back(i);
		}
	}
	return all_maximal_conflict_queens;
}

int Table::chooseQueenWithMaxConflictsRandomly() {
	std::vector<int> max_conflict_queens = getAllQueensWithMaximalConflict();
	int max_conflict_queen = chooseQueenRandomly(max_conflict_queens);
	return max_conflict_queen;
}

//Setters
void Table::placeQueenRandomly(int _queen) {
	places_of_the_queens[_queen] = getRandomNumberInRange(0, size);
}

void Table::setConflictsOfQueen(int _queen) {
	int total_conflicts = 0;
	for (int i = 0; i < size; i++) {
		if (i != _queen) {
			total_conflicts += isThereConflict(_queen, i);
		}
	}
	conflicts_of_the_queens[_queen] = total_conflicts;
}

void Table::setConflictsOfAllQueens() {
	for (int i = 0; i < size; i++) {
		setConflictsOfQueen(i);
	}
}


//Others
bool Table::isThereConflict(int _queen, int other_queen) {
	int queen_position = places_of_the_queens[_queen];
	int other_queen_position = places_of_the_queens[other_queen];
	return (queen_position == other_queen_position ||
		queen_position - _queen == other_queen_position - other_queen ||
		queen_position + _queen == other_queen_position + other_queen);
}


void Table::printTable() {
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			if (places_of_the_queens[col] == row) {
				std::cout << 'Q' << ' ';
			}
			else {
				std::cout << '*' << ' ';
			}
		}
		std::cout << '\n';
	}
}


//In progress
int Table::placeQueenOnMinConflictPosition() {
	int max_conflict_queen = chooseQueenWithMaxConflictsRandomly();
	int max_queen_pos = places_of_the_queens[max_conflict_queen];
	int max_queen_conflicts = conflicts_of_the_queens[max_conflict_queen];
	decreaseConflictsByRemovingQueenAndResetQueen(max_conflict_queen);

	std::pair<int, int> newPos_newConfl = findMinimalPositionForQueen(max_conflict_queen, max_queen_pos, max_queen_conflicts);
	int newPos = newPos_newConfl.first;
	int newConfl = newPos_newConfl.second;
 	setQueenAndIncreaseConflictsByPlacingQueen(max_conflict_queen, newPos, newConfl);
	return newPos;
}

//optimisation - you can count down the number of conflicts and stop when it is 0
void Table::setQueenAndIncreaseConflictsByPlacingQueen(int _queen, int _new_position, int _new_conflicts) {
	places_of_the_queens[_queen] = _new_position;
	conflicts_of_the_queens[_queen] = _new_conflicts;
	for (int i = 0; i < size; i++) {
		if (i != _queen && isThereConflict(_queen, i)) {
			conflicts_of_the_queens[i]++;
		}
	}
}

void Table::decreaseConflictsByRemovingQueenAndResetQueen(int _queen) {
	for (int i = 0; i < size; i++) {
		if (i != _queen && isThereConflict(_queen, i)) {
			conflicts_of_the_queens[i]--;
		}
	}
	places_of_the_queens[_queen] = -1;
	conflicts_of_the_queens[_queen] = -1;
}

std::pair<int, int> Table::findMinimalPositionForQueen(int _queen, int _previous_position, int _previous_conflicts) {
	std::pair<std::vector<int>, int> conflictsPerPosition_minimalConflicts = calculateConflictsForEachPosition(
		_queen,
		_previous_position,
		_previous_conflicts
	);

	std::vector<int> conflicts_for_each_position_in_row = conflictsPerPosition_minimalConflicts.first;
	int new_conflicts = conflictsPerPosition_minimalConflicts.second;

	std::vector<int> positions_with_min_conflicts;
	for (int i = 0; i < size; i++) {
		if (conflicts_for_each_position_in_row[i] == new_conflicts) {
			positions_with_min_conflicts.push_back(i);
		}
	}
	int new_position = choosePositionRandomly(positions_with_min_conflicts);

	return std::make_pair(new_position, new_conflicts);
}

//optimize - no need to calculate for _previous position, we know the conflicts
std::pair<std::vector<int>, int> Table::calculateConflictsForEachPosition(int _queen, int _previous_position, int _previous_conflicts) {
	std::vector<int> conflicts_for_each_position_in_row;
	int minimal_conflict_position = _previous_position;
	int minimal_conflicts = _previous_conflicts;

	for (int pos = 0; pos < size; pos++) {
		places_of_the_queens[_queen] = pos;
		int conflicts = 0;
		for (int queen = 0; queen < size; queen++) {
			if (queen != _queen) {
				conflicts += isThereConflict(_queen, queen);
			}
		}
		if (minimal_conflicts >= conflicts) {
			minimal_conflict_position = pos;
			minimal_conflicts = conflicts;
		}
		conflicts_for_each_position_in_row.push_back(conflicts);
	}
	return std::make_pair(conflicts_for_each_position_in_row, minimal_conflicts);
}
