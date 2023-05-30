#include "ftxui/component/component.hpp" // for Checkbox, Renderer, Horizontal, Vertical, Input, Menu, Radiobox, ResizableSplitLeft, Tab
#include "ftxui/screen/color.hpp" // for Color, Color::BlueLight, Color::RedLight, Color::Black, Color::Blue, Color::Cyan, Color::CyanLight, Color::GrayDark, Color::GrayLight, Color::Green, Color::GreenLight, Color::Magenta, Color::MagentaLight, Color::Red, Color::White, Color::Yellow, Color::YellowLight, Color::Default, Color::Palette256, ftxui
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <string>

#include "include/options.hpp"
using namespace ftxui;
int count = 0;
auto buttons = Container::Horizontal({
    Button("打开标签延时效果 但是现在没有用",
           [] {
             option.delay_on();
             count++;
           }),
    Button("关闭标签延时效果 现在同样没有用",
           [] {
             option.delay_off();
             count++;
           }),
});

// Modify the way to render them on screen:
auto settings = Renderer(buttons, [] {
  std::string underlineColor;
  if (option.option.underline.color_inactive == Color::Red) {
    underlineColor = "Red";
  } else {
    underlineColor = "Other";
  }
  return vbox({
             text(std::to_string(count)),
             buttons->Render(),
             text(underlineColor),
         }) |
         border;
});
