#ifndef _EDIT_HPP
#define _EDIT_HPP

#include <ftxui/component/component_base.hpp>
extern int depth; // There are two layers. One at depth = 0 and the modal
                  // window at depth = 1 or 2;
extern ftxui::Component insertWindow;
extern ftxui::Component deleteWindow;
extern ftxui::Component updateWindow;
#endif
