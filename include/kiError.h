#ifndef __KIERROR_H_
#define __KIERROR_H_

#include <string>

void
kiFatal();

void
kiFatal(std::string const& msg);

void
kiWarning(std::string const& msg);

void
kiInfo(std::string const& msg);

void
kiDebug(std::string const& msg);

#endif // __KIERROR_H_
