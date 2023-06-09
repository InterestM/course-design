#include "ftxui/component/component.hpp"         // for Menu, Renderer, Vertical
#include "ftxui/component/component_options.hpp" // for MenuOption, UnderlineOption
#include "ftxui/screen/color.hpp" // for Color, Color::Blue, Color::Red
#include <chrono>                 // for operator""ms, literals
#include <iostream>

#include "include/options.hpp"
using namespace ftxui;
//-----Planing to use a separate file to save configuration-------
Options::Options() : option{MenuOption::HorizontalAnimated()} {
  using namespace std::literals; // for operator""ms
  option = MenuOption::HorizontalAnimated();
  // option.underline.SetAnimationFunction(animation::easing::BackOut);
  option.underline.color_inactive = Color::IndianRed;
  ;
  // option.underline.SetAnimationDuration(350ms);
}
void Options::delay_on() {
  using namespace std::literals;
  option.underline.follower_delay = 250ms;
  option.underline.color_inactive = Color::Red;
}
void Options::delay_off() {
  using namespace std::literals;
  option.underline.follower_delay = 0ms;
  option.underline.color_inactive = Color::Yellow;
}
