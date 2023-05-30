#include "ftxui/component/component.hpp" // for Checkbox, Renderer, Horizontal, Vertical, Input, Menu, Radiobox, ResizableSplitLeft, Tab
#include "ftxui/screen/color.hpp" // for Color, Color::BlueLight, Color::RedLight, Color::Black, Color::Blue, Color::Cyan, Color::CyanLight, Color::GrayDark, Color::GrayLight, Color::Green, Color::GreenLight, Color::Magenta, Color::MagentaLight, Color::Red, Color::White, Color::Yellow, Color::YellowLight, Color::Default, Color::Palette256, ftxui
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>

using namespace ftxui;

Component homescreen = Renderer([] {
  auto tank = hbox({
      vbox({
          text("░░░░░░███████ ]▄▄▄▄▄▄▄▄▃"),
          text("▂▄▅█████████▅▄▃▂"),
          text("I███████████████████]."),
          text("◥⊙ ▲⊙ ▲⊙ ▲⊙ ▲⊙ ▲⊙ ▲⊙◤..."),
      }),
  });

  return vbox({
      vbox({
          tank | hcenter,
          text("Open Source Information Management System for Equipment Loss "
               "in Armed Conflict") |
              hcenter | bold,
      }) | borderRounded,
      text("Losses") | underlined | hcenter,
      hbox({text("Red"), filler(), text("Blue")}),
      separatorDashed(),
      hbox({
          gauge(0.2) | color(Color::Blue),
          text("300"),
          text(" Tank ") | hcenter,
          text("400"),
          gaugeLeft(0.3) | color(Color ::Red),
      }),
      hbox({
          gauge(0.5) | color(Color::Blue),
          text("750"),
          text(" Infantry Fighting Vehicles ") | hcenter,
          text("1200"),
          gaugeLeft(0.8) | color(Color ::Red),
      }),
  });
});
