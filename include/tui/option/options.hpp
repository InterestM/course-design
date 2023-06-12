#ifndef _OPTION_HPP
#define _OPTION_HPP

#include "ftxui/component/component.hpp"  // for Menu, Renderer, Vertical

using namespace ftxui;
//-----Planing to use a separate file to save configuration-------
class Options {
 public:
  static Options &GetInstance() {
    static Options instance;
    return instance;
  }
  const MenuOption &GetOption() const { return option; }
  void DelayOn();
  void DelayOff();

 private:
  Options();
  Options(Options const &) = delete;
  MenuOption option;
};
#endif
