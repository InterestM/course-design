#ifndef OPTION_HPP
#define OPTION_HPP

#include "ftxui/component/component.hpp" // for Menu, Renderer, Vertical

using namespace ftxui;
//-----Planing to use a separate file to save configuration-------
class Options {
public:
  static Options &get_instance() {
    static Options instance;
    return instance;
  }
  MenuOption option;
  void delay_on();
  void delay_off();
private:
  Options();
  Options(Options const &) = delete;
};
#endif
