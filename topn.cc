#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <vector>

using namespace std;

void usage() { cout << "Usage: ./topn [<in_size> <N>]" << endl; }

int main(int argc, char* argv[]) {
  if (argc != 3 && argc != 1) {
    usage();
    return -1;
  }
  int in_size = 1000;
  int N = 5;
  if (argc == 3) {
    try {
      in_size = stoi(argv[1]);
      N = stoi(argv[2]);
    } catch (...) {
      usage();
      return -1;
    }
  }
  cout << "input size: " << in_size << endl;
  cout << "N: " << N << endl;
  // init random generator
  default_random_engine rnd_eng(clock());
  uniform_int_distribution<int> dstr{-in_size, in_size};
  auto int_rnd_gen = [&dstr, &rnd_eng]() { return dstr(rnd_eng); };
  // create input dataset
  vector<int> vv(in_size);
  std::generate(vv.begin(), vv.end(), int_rnd_gen);

  // Top N accumulator. Top elem will have the smallest element
  priority_queue<int, vector<int>, greater<int>> q;
  vector<int> res(N);
  // scan input dataset
  const auto& t1 = chrono::high_resolution_clock::now();
  for (int v : vv) {
    if (q.size() < N) {
      q.push(v);
    // remove the smalest element and push new one
    } else if (v > q.top()) {
      q.pop();
      q.push(v);
    }
  }

  // copy the result to vector
  for (int i = N - 1; i >= 0; i--) {
    res[i] = q.top();
    q.pop();
  }
  const chrono::duration<double, milli> tt =
      chrono::high_resolution_clock::now() - t1;
  cout << "Ton N:" << endl;
  for (int v : res) cout << v << ",";
  cout << endl;
  cout << "Exec time: " << tt.count() << " ms" << endl;
  return 0;
}
