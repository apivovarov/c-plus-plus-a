// Homework 1: Convert a C program to C++
#include <iostream>
#include <vector>

const int N = 40;

using namespace std;

template <class summable>
inline void sum(summable &p, const vector<summable> &d) {
  for (summable v : d)
    p += v;
}

int main(void) {
  int accum = 0;
  vector<int> data(N);
  for (int i = 0; i < N; i++)
    data[i] = i;
  sum(accum, data);
  cout << "sum is " << accum << endl;
  return 0;
}
