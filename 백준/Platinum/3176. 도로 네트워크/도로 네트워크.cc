#include <bits/stdc++.h>
#define fastio cin.tie(0)->ios::sync_with_stdio(0); cout.tie(0); setvbuf(stdout, nullptr, _IOFBF, BUFSIZ);
#define INF INT32_MAX
// INT32_MIN, INT64_MIN, INT32_MAX, INT64_MAX
using namespace std;
using int64 = int64_t;

int N, K, maxx, minn;
int depthTree[100001];
int parentTree[100001][18];
int maxTree[100001][18];
int minTree[100001][18];
vector<pair<int, int>> vp[100001];

inline void LCA(int a, int b) {
	if (depthTree[a] > depthTree[b]) {
		int dif = log2(depthTree[a] - depthTree[b]);

		maxx = max(maxx, maxTree[a][dif]);
		minn = min(minn, minTree[a][dif]);

		LCA(parentTree[a][dif], b);
		return;
	}
	else if (depthTree[a] < depthTree[b]) {
		int dif = log2(depthTree[b] - depthTree[a]);

		maxx = max(maxx, maxTree[b][dif]);
		minn = min(minn, minTree[b][dif]);

		LCA(a, parentTree[b][dif]);
		return;
	}
	if (a != b) {
		for (int i = 1; i < 18; ++i) {
			if (parentTree[a][i] == parentTree[b][i]) {
				maxx = max(maxx, maxTree[a][i - 1]);
				maxx = max(maxx, maxTree[b][i - 1]);
				minn = min(minn, minTree[a][i - 1]);
				minn = min(minn, minTree[b][i - 1]);

				LCA(parentTree[a][i - 1], parentTree[b][i - 1]);
				return;
			}
		}
	}

}

inline void initMinTree(int cur, int dis) {
	minTree[cur][0] = dis;

	for (int i = 1; i < 18; ++i) {
		minTree[cur][i] = min(minTree[parentTree[cur][i - 1]][i - 1], minTree[cur][i - 1]);
	}

	for (auto& iter : vp[cur]) {
		if (iter.first == parentTree[cur][0]) continue;

		initMinTree(iter.first, iter.second);
	}
}

inline void initMaxTree(int cur, int dis) {
	maxTree[cur][0] = dis;

	for (int i = 1; i < 18; ++i) {
		maxTree[cur][i] = max(maxTree[parentTree[cur][i - 1]][i - 1], maxTree[cur][i - 1]);
	}

	for (auto& iter : vp[cur]) {
		if (iter.first == parentTree[cur][0]) continue;

		initMaxTree(iter.first, iter.second);
	}
}

inline void initTree(int cur, int parent, int dep) {
	parentTree[cur][0] = parent;
	depthTree[cur] = dep;

	for (int i = 1; i < 18; ++i) {
		parentTree[cur][i] = parentTree[parentTree[cur][i - 1]][i - 1];
	}

	for (auto& iter : vp[cur]) {
		if (iter.first == parent) continue;

		initTree(iter.first, cur, dep + 1);
	}
}

int main() {
	fastio;

	cin >> N;
	for (int i = 0; i < N - 1; ++i) {
		int a, b, c;
		cin >> a >> b >> c;

		vp[a].push_back({ b, c });
		vp[b].push_back({ a,c });
	}

	initTree(1, 1, 1);
	initMaxTree(1, 0);
	initMinTree(1, INF);

	cin >> K;  //maxTree[0][0]; minTree[0][0]; parentTree[0][0]; depthTree[0];
	for (int i = 0; i < K; ++i) {
		int a, b;
		cin >> a >> b;

		minn = INF; maxx = 0;
		LCA(a, b);
	
		cout << minn << " " << maxx << "\n";
	}

	return EXIT_SUCCESS;
}