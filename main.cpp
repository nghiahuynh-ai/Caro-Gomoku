#include "Board.h"

int main() {
	int x, y;
	do {
		Board b;
		b.play();
		b.~Board();
		
		cout << "New game?" << "    ";
		setColor(BLUE);
		cout << "YES" << "    ";
		setColor(RED);
		cout << "NO";
		setColor(WHITE);

		x = 13;
		y = b.getBoardSize() * 2 + 2;
		gotoXY(x, y);

		while (true){
			int key = getKey();
			if (key == 13) {
				x = getX();
				break;
			}
			else if (key == 75 || key == 77) {
				x = getX();
				if (x == 13) gotoXY(20, y);
				else gotoXY(13, y);
			}
			else continue;
		}
		system("cls");
	} while (x == 13);
	return 0;
}