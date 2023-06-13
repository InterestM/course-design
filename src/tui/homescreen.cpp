#include <string>

#include <db/database.hpp>
#include <system_error>

#include "ftxui/component/component.hpp" // for Checkbox, Renderer, Horizontal, Vertical, Input, Menu, Radiobox, ResizableSplitLeft, Tab
#include "ftxui/component/component_base.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"
#include "ftxui/screen/color.hpp" // for Color, Color::BlueLight, Color::RedLight, Color::Black, Color::Blue, Color::Cyan, Color::CyanLight, Color::GrayDark, Color::GrayLight, Color::Green, Color::GreenLight, Color::Magenta, Color::MagentaLight, Color::Red, Color::White, Color::Yellow, Color::YellowLight, Color::Default, Color::Palette256, ftxui

using namespace ftxui;

namespace {
auto tank = hbox({
    vbox({
        text("░░░░░░███████ ]▄▄▄▄▄▄▄▄▃"),
        text("▂▄▅█████████▅▄▃▂"),
        text("I███████████████████]."),
        text("◥⊙ ▲⊙ ▲⊙ ▲⊙ ▲⊙ ▲⊙ ▲⊙◤..."),
    }),
});

auto container = Container::Vertical({});
void LoadLoss() {
  std::vector<std::string> types = Database::QueryType();
  container = Container::Vertical({});
  for (int i = 0; i < types.size(); i++) {
    container->Add(Renderer([=] {
      int blueNum = {Database::CalcSum(types[i], "BLUE")},
          redNum = {Database::CalcSum(types[i], "RED")},
          blueSum = {Database::CalcSum("", "BLUE")},
          redSum = {Database::CalcSum("", "RED")};
      return hbox({
                 gauge(1.0 * blueNum / blueSum) | color(Color::Blue),
                 text(std::to_string(blueNum)) | color(Color::Blue),
                 text(" " + types[i] + " ") | hcenter,
                 text(std::to_string(redNum)) | color(Color::Red),
                 gaugeLeft(1.0 * redNum / redSum) | color(Color ::Red),
             }) |
             flex;
    }));
  }
}
} // namespace

Component homescreen = Renderer([] {
  LoadLoss();
  return vbox({
      vbox({
          tank | hcenter,
          text("Open Source Information Management System for Equipment Loss "
               "in Armed Conflict") |
              hcenter | bold,
      }) | borderRounded,
      text("Losses") | underlined | hcenter,
      hbox({
          text("Blue") | color(Color::Blue) | bold,
          filler(),
          text("Red") | color(Color::Red) | bold,
      }),
      separatorDashed(),
      container->Render(),
  });
});
