#include <chrono>
#include <iostream>

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/screen/color.hpp>

#include "tui/option/options.hpp"
////外观选项
using namespace ftxui;
//-----Planing to use a separate file to save configuration-------
Options::Options() : option{MenuOption::HorizontalAnimated()} {
  // using namespace std::literals; // for operator""ms
  // option = MenuOption::HorizontalAnimated();
  option.underline.SetAnimationFunction(animation::easing::BackOut);
  option.underline.color_active = Color::NavajoWhite1;
  option.underline.color_inactive = Color::IndianRed;
  // option.underline.SetAnimationDuration(350ms);
}
