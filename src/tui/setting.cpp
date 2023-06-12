#include <string>

#include "ftxui/component/component.hpp" // for Checkbox, Renderer, Horizontal, Vertical, Input, Menu, Radiobox, ResizableSplitLeft, Tab
#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"
#include "ftxui/screen/color.hpp" // for Color, Color::BlueLight, Color::RedLight, Color::Black, Color::Blue, Color::Cyan, Color::CyanLight, Color::GrayDark, Color::GrayLight, Color::Green, Color::GreenLight, Color::Magenta, Color::MagentaLight, Color::Red, Color::White, Color::Yellow, Color::YellowLight, Color::Default, Color::Palette256, ftxui

#include "tui/option/options.hpp"

namespace {
int count = 0;
auto buttons = Container::Horizontal({
    Button("test",
           [] {
             Options::GetInstance().DelayOn();
             count++;
           }),
    Button("关闭标签延时效果 现在同样没有用",
           [] {
             Options::GetInstance().DelayOff();
             count++;
           }),
});
} // namespace

// Modify the way to render them on screen:
auto settings = Renderer(buttons, [] {
  std::string underlineColor;
  if (Options::GetInstance().GetOption().underline.color_inactive ==
      Color::Red) {
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
