#include <iostream>
#include <vector>
using namespace std;
int main() {
  vector<int> v(20);
  v[0] = 10;
  v[1] = 20;
  cout << "V sizeof: " << sizeof(v) << "\n";
  cout << "V size: " << v.size() << "\n";
  cout << "V front: " << v.front() << "\n";
  cout << "V back: " << v.back() << "\n";

  vector<int> vR;
  vR.reserve(20);
  vR.push_back(10);
  //  vR[1] = 20;
  cout << " vR sizeof: " << sizeof(vR) << "\n";
  cout << " vR size: " << vR.size() << "\n";
  cout << " vR front: " << vR.front() << "\n";
  cout << " vR back: " << vR.back() << "\n";
  for (auto i : vR) cout << i;
  return 0;
}
