#include <iostream>
using namespace std;

int main() {
  int w, l, h; cin >> w >> l >> h;
  if (min(w, l) >= h * 2 && max(w, l) <= min(w, l) * 2) {
    cout << "good";
  } else {
    cout << "bad";
  }
  
  return 0;
}