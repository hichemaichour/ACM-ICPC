#include <iostream>
#include <string>
#include <cassert>
#include <fstream>

using namespace std;

long long area2(const string &code) {
	int dr[8] = {0, -1, -1, -1, 0, 1, 1, 1};
	int dc[8] = {1, 1, 0, -1, -1, -1, 0, 1};

	int n = code.length();
	long long sum = 0;

	long long r = 0, c = 0;

	for (int i = 0; i < n; i++) {
		int val = code[i] - '0';
		long long nr = r + dr[val];
		long long nc = c + dc[val];

		sum += r * nc - c * nr;
		r = nr;
		c = nc;
	}

	assert(r == 0 && c == 0);
	return sum;
}

int main(void) {
	ifstream cin("chaincode.in");
	string code;
	while (cin >> code) {
		long long A2 = area2(code);
		long long B = code.length();

		// pick's theorem says A = I + B/2 - 1, or 2A = 2I + B - 2
		long long I2 = A2 - B + 2;
		assert(I2 % 2 == 0);
		cout << B + I2 / 2 << endl;
	}
	return 0;
}
