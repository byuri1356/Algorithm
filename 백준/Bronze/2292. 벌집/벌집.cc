#include<iostream>
#define fastio cin.tie(0)->ios::sync_with_stdio(0); cout.tie(0); setvbuf(stdout, nullptr, _IOFBF, BUFSIZ);
using namespace std;
using int64 = int64_t;



int main() {

	fastio;

	int N;
	cin >> N;

	int ans = 1, cnt = 1, n = 1;

	while (n < N) {
		n += cnt * 6;
		ans++, cnt++;
	}

	cout << ans;

	return EXIT_SUCCESS;
}