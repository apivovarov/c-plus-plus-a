#include<iostream>
#include<cstdint>
using namespace std;

enum class days:std::uint8_t {SUNDAY,MONDAY,TUESDAY,WEDNESDAY,THURSDAY,FRIDAY,SATURDAY};

enum class hours:std::uint8_t {ONE, TWO};

ostream& operator<<(ostream& out, const days& d)
 { out << static_cast<int>(d); return out; }

ostream& operator<<(ostream& out, const hours& d)
 { out << static_cast<int>(d); return out; }

int main() {
  days today{days::MONDAY};
  hours now{hours::ONE};
  cout << "Demonstrate class enum" << endl;
  std::cout << "MONDAY VALUE IS " << today << std::endl;
  std::cout << "ONE VALUE IS " << now << std::endl;
  return 0;
}
