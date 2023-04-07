#include <iostream>
using namespace std;

void calTotal(int total[], int* cells[]) {
	for (int i = 0; i < 16; i++) {
		total[i] = 0;
		for (int k = 0; k < 4; k++)
			total[i] += *(cells[i] + k);
	}
}

void displayTotal(int total[]) {
	int k = 0;
	cout << "4x4 checkerboard: " << endl;
	for (int i = 0; i < 16; i++) {
		cout << total[i] << " ";
		k++;
		if (k == 4) {
			cout << endl;
			k = 0;
		}
	}
	cout << endl;
}

void sort(int* total, int* cells[]) {
	int tmp, k;
	int* tmpPos;
	for (int j = 0; j < 16 - 1; j++)   // outer loop
		for (k = 16 - 1; k > j; k--) // bubbling
			if (total[k] > total[k - 1]) {
				tmp = total[k];   // swap total
				total[k] = total[k - 1];
				total[k - 1] = tmp;
				tmpPos = cells[k]; // swap cells
				cells[k] = cells[k - 1];
				cells[k - 1] = tmpPos;
			}
}

void compare(int& v1, int& v2) {
	int diff = v1 - v2;
	if (diff > 0) {
		v1 += v2;
		v2 = 0;
	}
	else if (diff < 0) {
		v2 += v1;
		v1 = 0;
	}
}

int main() {
	int sheets[16][2][2] = { {{3,16},{13,15}},  {{9,5},{18,3}} ,  {{13,3},{13,9}},   {{9,0},{4,7}},
							 {{20,10},{16,20}}, {{14,19},{13,3}}, {{14,9},{1,14}},   {{12,7},{3,0}},
							 {{1,12},{17,3}},   {{1,4},{0,11}},   {{17,20},{17,14}}, {{20,10},{5,3}},
							 {{1,1},{1,1}},     {{2,15},{5,12}},  {{9,3},{9,12}},    {{8,16},{1,4}} };
	int* cells[16];
	int total[16] = { 0 }, tmp, i, k;

	for (i = 0; i < 16; i++)
		cells[i] = sheets[i][0];

	calTotal(total, cells);
	sort(total, cells);
	displayTotal(total);

	//PART 2
	int col, row, diff;
	int selected[3] = {};
	cout << "Please select three cells (0,0) to (3,3): " << endl;
	for (i = 0; i < 3; i++) {
		cin >> col >> row;
		selected[i] = col * 4 + row;
	}
	cout << endl;

	for (i = 0; i < 16; i++) {
		for (k = 0; k < 3; k++)
			if (i == selected[k]) {
				tmp = *cells[i];
				*cells[i] = *(cells[i] + 2);
				*(cells[i] + 2) = *(cells[i] + 3);
				*(cells[i] + 3) = *(cells[i] + 1);
				*(cells[i] + 1) = tmp;
			}

		if (i >= 4) { //doNorth
			compare(*cells[i], *(cells[i - 4] + 2));
			compare(*(cells[i] + 1), *(cells[i - 4] + 3));
		}
		if (i % 4 != 3) { //doEast
			compare(*(cells[i] + 1), *(cells[i + 1]));
			compare(*(cells[i] + 3), *(cells[i + 1] + 2));
		}
		if (i <= 11) { //doSouth
			compare(*(cells[i] + 2), *(cells[i + 4]));
			compare(*(cells[i] + 3), *(cells[i + 4] + 1));
		}
		if (i % 4 != 0) { //doWest
			compare(*(cells[i]), *(cells[i - 1] + 1));
			compare(*(cells[i] + 2), *(cells[i - 1] + 3));
		}
	}

	calTotal(total, cells);
	sort(total, cells);
	displayTotal(total);

	return 0;
}