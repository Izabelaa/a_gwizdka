#include <fstream>
#include<iostream>

using namespace std;

int main()
{
	int G[20][20];
	float H[20][20];
	float F[20][20];
	short typ_pola[20][20];
	short rodzic[20][20];

	fstream plik;
	plik.open("grid.txt");

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			plik >> typ_pola[i][j];
		}
	}
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			cout << typ_pola[i][j] << " ";
		}

		cout << endl;
	}
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (typ_pola[i][j] == 0)
			{
				H[i][j] = (float) sqrt((19 - i)*(19 - i) + (19 - j)*(19 - j));
			}
		}
	}

	typ_pola[0][0] = 1;
	G[0][0] = 0;
	F[0][0] = G[0][0] + H[0][0];
	rodzic[0][0] = 0;

	while (true)
	{
		float min = 9999.0f;
		int minX, minY;
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (typ_pola[i][j] == 1) {
					if (min > F[i][j])
					{
						min = F[i][j];
						minX = i;
						minY = j;
					}
					else if (min == F[i][j]) {
						if (H[i][j] < H[minX][minY]) {
							min = F[i][j];
							minX = i;
							minY = j;
						}
					}
				}
			}
		}

		if (min == 9999.0f) {
			cout << "brak sciezki ";//
			getchar();
			return 0;
		}
		else if (minX == 19 && minY == 19) {


			cout << "znaleziono sciezke: (19, 19) ";
			do {
				typ_pola[minX][minY] = 3;
				if (rodzic[minX][minY] == 1) minX--;
				else if (rodzic[minX][minY] == 2) minY--;
				else if (rodzic[minX][minY] == 3) minX++;
				else if (rodzic[minX][minY] == 4) minY++;
				cout << "-> (" << minX << ", " << minY << ")";
			} while (!(minX == 0 && minY == 0));
			cout << endl << endl;

			for (int i = 0; i < 20; i++)
			{
				for (int j = 0; j < 20; j++)
				{
					cout << typ_pola[i][j] << " ";
				}

				cout << endl;
			}
			getchar();
			return 0;
		}
		else {
			typ_pola[minX][minY] = 2;
			if (minX >= 1) {
				if (typ_pola[minX - 1][minY] == 0 || (typ_pola[minX - 1][minY] == 1 && (G[minX - 1][minY] > G[minX][minY] + 1))) {
					typ_pola[minX - 1][minY] = 1;
					G[minX - 1][minY] = G[minX][minY] + 1;
					F[minX - 1][minY] = G[minX - 1][minY] + H[minX - 1][minY];
					rodzic[minX - 1][minY] = 3;
				}
			}

			if (minX <= 18) {
				if (typ_pola[minX + 1][minY] == 0 || (typ_pola[minX + 1][minY] == 1 && (G[minX + 1][minY] > G[minX][minY] + 1))) {
					typ_pola[minX + 1][minY] = 1;
					G[minX + 1][minY] = G[minX][minY] + 1;
					F[minX + 1][minY] = G[minX + 1][minY] + H[minX + 1][minY];
					rodzic[minX + 1][minY] = 1;
				}
			}
			if (minY >= 1) {
				if (typ_pola[minX][minY - 1] == 0 || (typ_pola[minX][minY + 1] == 1 && (G[minX][minY + 1] > G[minX][minY] + 1))) {
					typ_pola[minX][minY - 1] = 1;
					G[minX][minY - 1] = G[minX][minY] + 1;
					F[minX][minY - 1] = G[minX][minY - 1] + H[minX][minY - 1];
					rodzic[minX][minY - 1] = 4;
				}
			}
			if (minY <= 18) {
				if (typ_pola[minX][minY + 1] == 0 || (typ_pola[minX][minY + 1] == 1 && (G[minX][minY + 1] > G[minX][minY] + 1))) {
					typ_pola[minX][minY + 1] = 1;
					G[minX][minY + 1] = G[minX][minY] + 1;
					F[minX][minY + 1] = G[minX][minY + 1] + H[minX][minY + 1];
					rodzic[minX][minY + 1] = 2;
				}
			}
		}
	}
}