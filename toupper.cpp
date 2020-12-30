#include <algorithm>
#include <codecvt>
#include <iostream>
#include <locale>
#include <string>
#include "utf8.h"

using namespace std;

template <typename Func>
std::string transform16(const std::string& s, Func func) {
  std::u16string ws = utf8::utf8to16(s);
  std::transform(ws.begin(), ws.end(), ws.begin(), func);
  return utf8::utf16to8(ws);
}

template <typename Func>
std::string wtransform(const std::string& s, Func func) {
  static std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> wconv;
  std::wstring ws = wconv.from_bytes(s);
  std::transform(ws.begin(), ws.end(), ws.begin(), func);
  return wconv.to_bytes(ws);
}

int main(void) {
    const char* locale_c = setlocale(LC_ALL, "en_US.UTF-8");
    const std::locale loc(locale_c);
    cout << "Locale: " << locale_c << endl;

    std::string s = "\u0431\u0432\u0433_abc_\u00DF";
    auto toupper_f = [loc](wchar_t c) { return std::toupper(c, loc); };
    auto toupper16_f = [](char16_t c) { return (char16_t)std::toupper(c); };
    std::string out_s = wtransform(s, toupper_f);
    std::string out2_s = transform16(s, toupper16_f);
    cout << s << " -> " << out_s << endl;
    cout << s << " -> " << out2_s << endl;

    return 0;
}

