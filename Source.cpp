#include <iostream>
#include "Table.h"
int main() {
	Table table(10);
	table.printTable();
	for (int i = 0; i < 6; i++) {
		std::cout << table.getConflictsOfQueen(i) << ' ';
	}
	std::cout << '\n'<<"----------------------------\n----------------------------\n";

	while (!table.solved()) {
		table.placeQueenOnMinConflictPosition();
	}
	table.printTable();

	// what is left to do:
	// 1. set table by min conflict idea
	// 2. for too many steps -> restart table
	// 3. optimize where can be optimized
	return 0;
}