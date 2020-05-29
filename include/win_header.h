#pragma once



#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <map>
#include <unordered_map>

#include <windowsx.h>
#include <commctrl.h>
#include <commctrl.rh>



#include <gsl\gsl>
#include <wil\resource.h>
#include <wil\result.h>

#define NN(T) gsl::not_null<T>

#include "win_msg.h"
#include "win_util.h"
#include "win_app.h"
#include "win_window.h"
#include "win_menu_bar.h"
#include "win_panel.h"
