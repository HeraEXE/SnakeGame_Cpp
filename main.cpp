#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>

using namespace std;

bool game_over;
const unsigned width{ 40 };
const unsigned height{ 20 };
int xsnake{};
int ysnake{};
std::vector<int> xtail(800);
std::vector<int> ytail(800);
unsigned ntail{};
int xfruit{};
int yfruit{};
unsigned score{};
enum eDirection {STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir{};

void setup()
{
	game_over = false;
	dir = STOP;
	xsnake = width / 2;
	ysnake = height / 2;
	xfruit = rand() % (width - 2) + 1;
	yfruit = rand() % (height - 2) + 1;
	score = 0;
}
void draw()
{
	system("cls");
	cout << "SCORE: " << score << '\n';
	for (size_t x{}; x < width; ++x) {
		cout << '#';
	}
	cout << '\n';
	for (size_t y{}; y < height; ++y) {
		for (size_t x{}; x < width; ++x) {
			if ((x == 0) || (x + 1 == width)) {
				cout << '#';
			}
			else if (y == ysnake && x == xsnake) {
				cout << '@';
			}
			else if (y == yfruit && x == xfruit) {
				cout << '$';
			}
			else {
				bool space{ true };
				for (size_t i{}; i < ntail; ++i) {
					if (x == xtail[i] && y == ytail[i]) {
						cout << 'O';
						space = false;
					}
				}
				if (space) {
					cout << ' ';
				}
	
			}
		}
		cout << '\n';
	}
	for (size_t x{}; x < width; ++x) {
		cout << '#';
	}
}
void input()
{
	if (_kbhit()) {
		switch (_getch()) {
			case 'w':
				if (dir != DOWN) {
					dir = UP;
				}
				break;
			case 's':
				if (dir != UP) {
					dir = DOWN;
				}
				break;
			case 'a':
				if (dir != RIGHT) {
					dir = LEFT;
				}
				break;
			case 'd':
				if (dir != LEFT) {
					dir = RIGHT;
				}
				break;  
			case 'x':
				game_over = true;
				break;
		}
	}
}
void logic()
{
	int xprev{ xtail[0] };
	int yprev{ ytail[0] };
	int x2prev;
	int y2prev;
	xtail[0] = xsnake;
	ytail[0] = ysnake;
	for (size_t i{ 1 }; i < ntail; ++i) {
		x2prev = xtail[i];
		y2prev = ytail[i];
		xtail[i] = xprev;
		ytail[i] = yprev;
		xprev = x2prev;
		yprev = y2prev;
	}
	switch (dir) {
		case LEFT:
			--xsnake;
			break;
		case RIGHT:
			++xsnake;
			break;
		case UP:
			--ysnake;
			break;
		case DOWN:
			++ysnake;
			break;
	}
	if (xsnake == width - 1) {
		xsnake = 1;
	}
	if (xsnake == 0) {
		xsnake = width - 1;
	}
	if (ysnake == height) {
		ysnake = 0;
	}
	if (ysnake == -1) {
		ysnake = height - 1;
	}
	if (xsnake == xfruit && ysnake == yfruit) {
		++ntail;
		++score;
		xfruit = rand() % (width - 2) + 1;
		yfruit = rand() % (height - 2) + 1;
	}
	for (size_t i{}; i < ntail; ++i) {
		if (xsnake == xtail[i] && ysnake == ytail[i]) {
			game_over = true;
		}
	}
}

int main()
{
	setup();
	while (!game_over) {
		draw();
		input();
		logic();
		Sleep(50);
	}
	return 0;
}