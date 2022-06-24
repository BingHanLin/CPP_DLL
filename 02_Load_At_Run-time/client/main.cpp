#include <iostream>
#include <windows.h>

int main() {

  typedef int(CALLBACK * FUNC_PTR)(const int &, const int &);

  HINSTANCE hDLL;   // handle to DLL
  FUNC_PTR funcPtr; // function pointer
  int result;

  hDLL = LoadLibrary("mathLibraryAdd.dll");

  if (nullptr != hDLL) {
    funcPtr = (FUNC_PTR)GetProcAddress(hDLL, "intOper");
    if (nullptr != funcPtr) {
      result = funcPtr(2, 3);
      std::cout << "result: " << result << std::endl;

    } else {
      std::cout << " load function pointer error." << std::endl;
      return 0;
    }
    FreeLibrary(hDLL);
  } else {
    std::cout << " load dll error." << std::endl;
    return 0;
  }
  return 0;
}