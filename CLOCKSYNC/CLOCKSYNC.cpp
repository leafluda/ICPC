#include <iostream>


using namespace std;

int clockHour[16];
int Switch[10][16] = {
	{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
	{1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1},
	{0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0}
};
bool check() {
	for (int i = 0; i < 16; i++) {
		if (clockHour[i] != 12) {
			return false;
		}
	}
	return true;
}
void pushSwitch(int SwitchNum, int pushNum) {
	for (int j = 0; j < pushNum; j++) {
		for (int i = 0; i < 16; i++) {
			if (Switch[SwitchNum][i] == 1) {
				clockHour[i] += 3;
				if (clockHour[i] == 15) clockHour[i] = 3;
			}
		}
	}
}
int sync(int currentSwitch) {
	int ret = 99999;

	if (currentSwitch == 10) {
		if (check()) {
			return 0;
		} else {
			return 99999;
		}
	}

	for (int i = 0; i < 4; i++) {
		pushSwitch(currentSwitch, i);	//i번 스위치를 누르고
		ret = min(ret, i + sync(currentSwitch + 1)); // 최소값을 찾는다.
		pushSwitch(currentSwitch, 4 - i); //시계를 다시 원상복구
	}
	return ret;
}

int main() {
	int input;

	cin >> input;

	while (input--) {
		for (int i = 0; i < 16; i++)
			cin >> clockHour[i];
		int res = sync(0);
		if (res == 99999) {
			cout << "-1\n";
		} else {
			cout << res << "\n";
		}
	}
}
