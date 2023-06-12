#include "data/database.hpp"
#include "ftxui/component/component.hpp" // for Checkbox, Renderer, Horizontal, Vertical, Input, Menu, Radiobox, ResizableSplitLeft, Tab
#include "ftxui/screen/color.hpp" // for Color, Color::BlueLight, Color::RedLight, Color::Black, Color::Blue, Color::Cyan, Color::CyanLight, Color::GrayDark, Color::GrayLight, Color::Green, Color::GreenLight, Color::Magenta, Color::MagentaLight, Color::Red, Color::White, Color::Yellow, Color::YellowLight, Color::Default, Color::Palette256, ftxui
#include <data/database.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <string>

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

  auto container = Container::Vertical({});
  std::vector<std::string> types = Database::QueryType();
  int sum = {Database::CalcSum()};

  for (auto i = types.begin(); i != types.end(); ++i) {
    std::string str = "tank";
    int blueNum = {Database::CalcSum(str, "BLUE")};
    container->Add(Renderer([&] {
      return hbox({
                 gauge(1.0 * blueNum / sum) | color(Color::Blue),
                 text(std::to_string(blueNum)), text(str) | hcenter,
                 // text(std::to_string(Database::CalcSum(str, "RED"))),
                 //  gaugeLeft(1.0 * Database::CalcSum(str, "RED") / sum) |
                 //  color(Color ::Red),
             }) |
             flex;
    }));
  }

  return vbox({
      vbox({
          tank | hcenter,
          text("Open Source Information Management System for Equipment Loss "
               "in Armed Conflict") |
              hcenter | bold,
      }) | borderRounded,
      text("Losses") | underlined | hcenter,
      hbox({text("Blue") | border, filler(), text("Red") | border}),
      separatorDashed(),
      container->Render(),
  });
});
