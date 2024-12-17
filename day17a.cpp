#include "./setup.h"

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int main() {
  // input
  ll regs[3];
  cin.ignore(12); cin >> regs[0]; cin.ignore(100, '\n');
  cin.ignore(12); cin >> regs[1]; cin.ignore(100, '\n');
  cin.ignore(12); cin >> regs[2]; cin.ignore(100, '\n');
  cin.ignore(100, '\n');
  cin.ignore(9);
  vector<int> program(1);
  while (cin >> program.back()) {
    cin.ignore(1);
    program.emplace_back();
  }
  program.pop_back();

  // run program
  int ip = 0;
  bool first = true;
  while (ip < (int)program.size()) {
    int opcode = program[ip];
    int literal = program[ip + 1];
    ll combo = literal <= 3 ? literal : regs[literal-4];
    bool jmp = false;

    switch (opcode) {
      case 0: {
        regs[0] = regs[0] >> combo;
      } break;
      case 1: {
        regs[1] = regs[1] ^ literal;
      } break;
      case 2: {
        regs[1] = combo & 0b111;
      } break;
      case 3: {
        if (regs[0] == 0) break;
        jmp = true;
        ip = literal;
      } break;
      case 4: {
        regs[1] = regs[1] ^ regs[2];
      } break;
      case 5: {
        if (first) {
          first = false;
        } else {
          cout << ",";
        }
        cout << (combo & 0b111);
      } break;
      case 6: {
        regs[1] = regs[0] >> combo;
      } break;
      case 7: {
        regs[2] = regs[0] >> combo;
      } break;
    }
    if (!jmp) ip += 2;
  }
  cout << endl;
}