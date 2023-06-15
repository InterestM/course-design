#ifndef _EDIT_HPP
#define _EDIT_HPP

#include <ftxui/component/component_base.hpp>
extern int front_window; // There are two layers. One at window = 0 and the
                         // modal window at front_window = 1 or 2 or 3;
extern ftxui::Component insertWindow;
extern ftxui::Component deleteWindow;
extern ftxui::Component updateWindow;
#endif
