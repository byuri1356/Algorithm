#include <bits/stdc++.h>
#define fastio cin.tie(0)->ios::sync_with_stdio(0); cout.tie(0); setvbuf(stdout, nullptr, _IOFBF, BUFSIZ);
#define INF 109876543210
using namespace std;
using int64 = int64_t;
//BOJ_14502_G4_연구소
//

int N, M, ans;
int first_Map[8][8], copy_Map[8][8];
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, 1, 0, -1 };

vector<pair<int, int>> v;
queue<pair<int, int>> q;

inline bool isValid(int x, int y) {
	return (x >= 0 && x < N&& y >= 0 && y < M);
}

inline void BFS() {
	int res = 0;

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;

		q.pop();

		for (int i = 0; i < 4; ++i) {
			int next_x = x + dx[i];
			int next_y = y + dy[i];

			if (isValid(next_x, next_y)) {
				if (!copy_Map[next_x][next_y]) {
					copy_Map[next_x][next_y] = 2;
					q.push({ next_x, next_y });
				}
			}
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (!copy_Map[i][j]) res++;
		}
	}

	ans = max(ans, res);
}

inline void initMap() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			copy_Map[i][j] = first_Map[i][j];
		}
	}

	for (auto iter : v) {
		q.push({ iter.first, iter.second });
	}
}

inline void makeWall(int cur, int dep, int cur_x, int cur_y) {
	if (cur == dep) {
		initMap();
		BFS();
		return;
	}

	for (int i = cur_x; i < N; ++i) {
		int j;
		if (i == cur_x) j = cur_y;
		else j = 0;
		for (; j < M; ++j) {
			if (!first_Map[i][j]) {
				first_Map[i][j] = 1;
				makeWall(cur + 1, dep, i, j + 1);
				first_Map[i][j] = 0;
			}
		}
	}


}

int main() {
	fastio;

	cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			cin >> first_Map[i][j];
			if (first_Map[i][j] == 2) {
				v.push_back({ i,j });
			}
		}
	}

	makeWall(0, 3, 0, 0);

	cout << ans;

	return EXIT_SUCCESS;
}