#include "kiError.h"

#include <cstdlib>
#include <iostream>

void
kiFatal()
{
  kiFatal("I think I'm dying here man...");
}

void
kiFatal(std::string const& msg)
{
  std::cerr << "[!] " << msg << std::endl;
  exit(-1);
}

void
kiWarning(std::string const& msg)
{
  std::cerr << "[*] " << msg << std::endl;
}

void
kiInfo(std::string const& msg)
{
  std::cerr << "[I] " << msg << std::endl;
}

void
kiDebug(std::string const& msg)
{
  std::cerr << "[D] " << msg << std::endl;
}