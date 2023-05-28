#include "ftxui/component/component.hpp" // for Checkbox, Renderer, Horizontal, Vertical, Input, Menu, Radiobox, ResizableSplitLeft, Tab
#include "ftxui/screen/color.hpp" // for Color, Color::BlueLight, Color::RedLight, Color::Black, Color::Blue, Color::Cyan, Color::CyanLight, Color::GrayDark, Color::GrayLight, Color::Green, Color::GreenLight, Color::Magenta, Color::MagentaLight, Color::Red, Color::White, Color::Yellow, Color::YellowLight, Color::Default, Color::Palette256, ftxui
using namespace ftxui;
auto render_gauge = [](int delta) {
  float progress = (delta) % 500 / 500.f;
  return hbox({
      text(std::to_string(int(progress * 100)) + "% ") | size(WIDTH, EQUAL, 5),
      gauge(progress),
  });
};

auto mainTab = Renderer([] {
  return vbox({
      render_gauge(0) | color(Color::Black),
      render_gauge(100) | color(Color::GrayDark),
      render_gauge(50) | color(Color::GrayLight),
      render_gauge(6894) | color(Color::White),
      separator(),
      render_gauge(6841) | color(Color::Blue),
      render_gauge(9813) | color(Color::BlueLight),
      render_gauge(98765) | color(Color::Cyan),
      render_gauge(98) | color(Color::CyanLight),
      render_gauge(9846) | color(Color::Green),
      render_gauge(1122) | color(Color::GreenLight),
      render_gauge(84) | color(Color::Magenta),
      render_gauge(645) | color(Color::MagentaLight),
      render_gauge(568) | color(Color::Red),
      render_gauge(2222) | color(Color::RedLight),
      render_gauge(220) | color(Color::Yellow),
      render_gauge(348) | color(Color::YellowLight),
  });
});
