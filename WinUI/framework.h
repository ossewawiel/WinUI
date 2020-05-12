// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <map>

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#ifndef NOMINMAX
# define NOMINMAX
#endif
#include <windows.h>
#include <windowsx.h>
#include <commctrl.rh>
// C RunTime Header Files
#include <cstdlib>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <gsl\gsl>
#include <wil\resource.h>
#include <wil\result.h>

#include "win_msg.h"
#include "win_util.h"



#define NN(T) gsl::not_null<T>