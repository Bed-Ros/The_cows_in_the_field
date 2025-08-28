#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <windows.h>

int eda = 10, max_eda = 10, x_korovi, y_korovi, kolichestvo_xodov = 0;
double porog_goloda = 0.4, porog_sitosti = 0.8;
const int n = 10, m = 20;
int pole[n + 1][m + 1];
char korova[n + 1][m + 1];

void vvod_massiva() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			pole[i][j] = 0;
			korova[i][j] = ' ';
		}
	}
	korova[x_korovi][y_korovi] = 'K';
}

void vivod_massiva() {
	for (int j = 1; j <= m; j++) {
		std::cout << "----";
	}
	std::cout << "-\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			std::cout << "| " << korova[i][j] << ' ';
		}
		std::cout << "|\n";
		for (int j = 1; j <= m; j++) {
			std::cout << "| " << pole[i][j] << ' ';
		}
		std::cout << "|\n";
		for (int j = 1; j <= m; j++) {
			std::cout << "----";
		}
		std::cout << "-\n";
	}
	std::cout << "Еда: " << eda << " из " << max_eda << '\n';
	if (eda >= (max_eda*porog_sitosti)) { std::cout << "Корова спит\n"; }
	if (eda > (max_eda*porog_goloda) && eda < (max_eda*porog_sitosti)) { std::cout << "Корова бродит\n"; }
	if (eda <= (max_eda*porog_goloda) && eda > 0) { std::cout << "Корова ищет еду\n"; }
	if (eda == 0) { std::cout << "Корова умерла x_x\n"; }
	std::cout << "Количество ходов " << kolichestvo_xodov << '\n';
}

void pereity(int a) {
	int x_korovi_minus1, y_korovi_minus1, x_korovi_plus1, y_korovi_plus1, max;
	x_korovi_minus1 = x_korovi - 1;
	y_korovi_minus1 = y_korovi - 1;
	x_korovi_plus1 = x_korovi + 1;
	y_korovi_plus1 = y_korovi + 1;
	if (x_korovi_minus1 < 1) { x_korovi_minus1 = n; }
	if (y_korovi_minus1 < 1) { y_korovi_minus1 = m; }
	if (x_korovi_plus1 > n) { x_korovi_plus1 = 1; }
	if (y_korovi_plus1 > m) { y_korovi_plus1 = 1; }
	korova[x_korovi][y_korovi] = ' ';
	if (a == 1) {
		if (pole[x_korovi_plus1][y_korovi] == pole[x_korovi_minus1][y_korovi] == pole[x_korovi][y_korovi_plus1] == pole[x_korovi][y_korovi_minus1]) { a = 2; }
		else {
			max = pole[x_korovi][y_korovi];
			if (max < pole[x_korovi_plus1][y_korovi]) { max = pole[x_korovi_plus1][y_korovi]; }
			if (max < pole[x_korovi_minus1][y_korovi]) { max = pole[x_korovi_minus1][y_korovi]; }
			if (max < pole[x_korovi][y_korovi_plus1]) { max = pole[x_korovi][y_korovi_plus1]; }
			if (max < pole[x_korovi][y_korovi_minus1]) { max = pole[x_korovi][y_korovi_minus1]; }
			if (max == pole[x_korovi_plus1][y_korovi]) { x_korovi = x_korovi_plus1; }
			else {
				if (max == pole[x_korovi_minus1][y_korovi]) { x_korovi = x_korovi_minus1; }
				else {
					if (max == pole[x_korovi][y_korovi_plus1]) { y_korovi = y_korovi_plus1; }
					else {
						if (max == pole[x_korovi][y_korovi_minus1]) { y_korovi = y_korovi_minus1; }
					}
				}
			}
		}
	}
	if (a == 2) {
		srand(time(0));
		switch (rand() % 4 + 1)
		{
		case 1: x_korovi = x_korovi_plus1; break;
		case 2: x_korovi = x_korovi_minus1; break;
		case 3: y_korovi = y_korovi_plus1; break;
		case 4: y_korovi = y_korovi_minus1; break;
		default: break;
		}
	}
	korova[x_korovi][y_korovi] = 'K';
}

int main() {
	int smert = 0;
	setlocale(0, "");
	x_korovi = n / 2;
	y_korovi = m / 2;
	vvod_massiva();
	vivod_massiva();
	system("pause");
	while (smert != 1) {
		system("cls");
		//Рост травы
		srand(time(0));
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (((rand()*x_korovi*y_korovi) % 1000 + 1) == 1 && pole[i][j] < 3) {
					pole[i][j]++;
				}
			}
		}
		//Каждый ход еда уменьшается на 1
		eda--;
		//Мозги коровы
		//Если корова сыта то спит 
		if (eda >= (max_eda*porog_sitosti)) {}
		//Если корова не голодна то бродит
		if (eda > (max_eda*porog_goloda) && eda < (max_eda*porog_sitosti)) {
			pereity(2);
		}
		//Если корова голодна то ищет еду
		if (eda <= (max_eda*porog_goloda) && eda > 0) {
			pereity(1);
			if ((eda + pole[x_korovi][y_korovi]) > max_eda) {
				pole[x_korovi][y_korovi] = eda + pole[x_korovi][y_korovi] - max_eda;
				eda = max_eda;
			}
			else {
				eda = eda + pole[x_korovi][y_korovi];
				pole[x_korovi][y_korovi] = 0;
			}
		}
		//Если еды нет то корова мертва
		if (eda == 0) { smert = 1; }
		kolichestvo_xodov++;
		vivod_massiva();
		system("pause");
		//Sleep(50);
	}
	system("pause");
	return 0;
}