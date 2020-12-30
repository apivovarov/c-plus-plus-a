#include <algorithm>
#include <codecvt>
#include <iostream>
#include <locale>
#include <string>

using namespace std;

template <typename Func>
std::string wtransform(const std::string& s, Func func) {
  static std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> wconv;
  std::wstring ws = wconv.from_bytes(s);
  std::transform(ws.begin(), ws.end(), ws.begin(), func);
  return wconv.to_bytes(ws);
}

int main(void) {
  const char* locale_c = setlocale(LC_ALL, "");
  const std::locale loc(locale_c);
  cout << "Locale: " << locale_c << endl;

  std::string s = "\u0431\u0432\u0433_abc";
  auto toupper_f = [loc](wchar_t c) { return std::toupper(c, loc); };
  std::string out_s = wtransform(s, toupper_f);
  cout << s << " -> " << out_s << endl;

  return 0;
}
