#ifndef OPTION_HPP
#define OPTION_HPP

#include "ftxui/component/component.hpp" // for Menu, Renderer, Vertical

using namespace ftxui;
//-----Planing to use a separate file to save configuration-------
class Options {
public:
  MenuOption option = MenuOption::HorizontalAnimated();
  Options();
  void delay_on();
  void delay_off();
};
extern Options option;
#endif
