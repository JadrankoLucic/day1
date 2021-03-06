#include "stdafx.h"
#include "..\lib\public.h"
#include "..\dll2\public.h"
#include <iostream>
#include <windows.h> 
#include <stdio.h>

double get_value_from_dynamic_library(const int i, double &o)
{
  LPCWSTR _dynamic_library_dll = L"dynamic_library.dll";
  //load library handle
    const HMODULE dllHandle = LoadLibrary(_dynamic_library_dll);

  //check if handle is null
  if (dllHandle == NULL) {
    std::cout << "Cannot find file:" << _dynamic_library_dll << std::endl;
    return 1;
  }

  typedef double(*LPGETVALUE)(int x);
  LPGETVALUE getValueFunction = (LPGETVALUE)GetProcAddress((HMODULE)dllHandle, "get_value");

  //check if function is null
  if (getValueFunction == NULL) 
  {
    std::cout << "Function cannot be fetched:" << "get_value" << std::endl;
    return 2;
  }

  o = getValueFunction(i);

  FreeLibrary(dllHandle);
  return 0;
}

int main()
{
  const int input = 5;
  std::cout << "value = " << input << std::endl;

  //static library
  double ret1 = static_lib::get_value(input);
  std::cout << "static_library::get_value = " << ret1 << std::endl;

  //dynamic library with lib
  double ret2 = get_value(5);
  std::cout << "dynamic_library_with_implib::get_value = " << ret2 << std::endl;

  double ret3 = 0;
  const int err = get_value_from_dynamic_library(input, ret3);
  if (err == 0)
  {
    std::cout << "dynamic_library::get_value = " << ret3 << std::endl;
  }

  std::cout << "Press ENTER to continue..." << std::endl << std::endl;
  std::cin.get();
}
