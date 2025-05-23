#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <windows.h>

const int FIELD_SIZE = 10;


void printFields(char playerField[FIELD_SIZE][FIELD_SIZE], char aiVisibleField[FIELD_SIZE][FIELD_SIZE]) {
	std::cout << "\nВаше поле:\t\tПоле противника:\n";
	std::cout << "  A B C D E F G H I J\t  A B C D E F G H I J\n";


	for (int row = 0; row < FIELD_SIZE; row++) {
		std::cout << row << (row < 10 ? " " : " ");
		for (int col = 0; col < FIELD_SIZE; col++) {
			std::cout << playerField[row][col] << " ";

		}


		std::cout << "\t" << row << (row < 10 ? " " : " ");
		for (int col = 0; col < FIELD_SIZE; col++) {
			std::cout << aiVisibleField[row][col] << " ";

		}
		std::cout << std::endl;
	}
}






void placeShip(char field[FIELD_SIZE][FIELD_SIZE], int coords[4][2]) {
	int direction = rand() % 2;
	int row, col;


	if (direction == 0) {
		row = rand() % FIELD_SIZE;
		col = rand() % (FIELD_SIZE - 3);
		for (int i = 0; i < 4; i++) {
			coords[i][0] = row;
			coords[i][1] = col + i;
			field[row][col + i] = 'O';
		}
	}
	else {
		row = rand() % (FIELD_SIZE - 3);
		col = rand() % FIELD_SIZE;
		for (int i = 0; i < 4; i++) {
			coords[i][0] = row + i;
			coords[i][1] = col;
			field[row + i][col] = 'O';
		}
	}
}


bool processMove(char field[FIELD_SIZE][FIELD_SIZE], char visibleField[FIELD_SIZE][FIELD_SIZE], int coords[4][2], bool hits[4], int& hitCount, int row, int col, bool isAi) {
	for (int i = 0; i < 4; i++) {
		if (coords[i][0] == row && coords[i][1] == col && !hits[i]) {
			hits[i] = true;
			field[row][col] = 'X';
			visibleField[row][col] = 'X';
			hitCount++;
			if (isAi)
				std::cout << "ИИ попал!\n";
			else
				std::cout << "Попадание!\n";
			return true;
		}
	}

	if (field[row][col] == '~') {
		field[row][col] = '*';
		visibleField[row][col] = '*';

	}


	if (isAi)
		std::cout << "ИИ промахнулся.\n";
	else
		std::cout << "Мимо.\n";
	return false;

}


void aiTurn(char playerField[FIELD_SIZE][FIELD_SIZE], char aiFieldVisible[FIELD_SIZE][FIELD_SIZE], int playerCoords[4][2], bool playerHits[4], int& playerHitCount) {
	int row, col;
	do {
		row = rand() % FIELD_SIZE;
		col = rand() % FIELD_SIZE;
	} while (playerField[row][col] == 'X' || playerField[row][col] == '*');


	std::cout << "Ход ИИ: " << (char)('A' + col) << row << std::endl;
	processMove(playerField, aiFieldVisible, playerCoords, playerHits, playerHitCount, row, col, true);
	Sleep(1000);
			
}


void startNewGame() {
	char playerField[FIELD_SIZE][FIELD_SIZE], aiField[FIELD_SIZE][FIELD_SIZE], aiVisibleField[FIELD_SIZE][FIELD_SIZE];
	int playerShip[4][2], aiShip[4][2];
	bool playerHits[4] = { false }, aiHits[4] = { false };
	int playerHitCount = 0, aiHitCount = 0;

	for (int row = 0; row < FIELD_SIZE; row++) {
		for (int col = 0; col < FIELD_SIZE; col++) {
			playerField[row][col] = '~';
			aiField[row][col] = '~';
			aiVisibleField[row][col] = '~';

		}
	}



	placeShip(playerField, playerShip);
	placeShip(aiField, aiShip);


	std::cout << "\nИгра началась!\n";


	while (playerHitCount < 4 && aiHitCount < 4) {
		printFields(playerField, aiVisibleField);

		char colChar;
		int row;
		std::cout << "\nВведите координаты: ";
		std::cin >> colChar >> row;
		colChar = std::toupper(colChar);
		int col = colChar - 'A';

		if (col < 0 || col >= FIELD_SIZE || row < 0 || row >= FIELD_SIZE) {
			std::cout << "Неверные координаты. Повторите попытку.\n";
			continue;

		}


		processMove(aiField, aiVisibleField, aiShip, aiHits, playerHitCount, row, col, false);

		if (playerHitCount < 4) {
			aiTurn(playerField, aiVisibleField, playerShip, playerHits, aiHitCount);

		}

	}


	printFields(playerField, aiVisibleField);
	if (playerHitCount == 4)
		std::cout << "\n Вы победили!\n";
	else
		std::cout << "\n Победа!\n";
}






int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(static_cast<unsigned int>(time(0)));


	int choice = 0;


	while (choice != 3) {

		std::cout << "===== МОРСКОЙ БОЙ ====" << std::endl;
		std::cout << "1. Новая игра" << std::endl;
		std::cout << "2. Загрузить игру" << std::endl;
		std::cout << "3. Выйти" << std::endl;
		std::cout << "Выберите пункт: " << std::endl;

		std::cin >> choice;



		if (choice == 1) {
			startNewGame();
		}
		else if (choice == 2) {
			std::cout << "Вы выбрали: Загрузить игру" << std::endl;

		}
		else if (choice == 3) {
			std::cout << "Выход..." << std::endl;
		}
		else {
			std::cout << "Неверный выбор!" << std::endl;
		}

	}


	return 0;
}