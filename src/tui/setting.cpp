#include <string>

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/color.hpp>

#include "db/database.hpp"
#include "tui/option/options.hpp"
////设置&帮助
namespace {
// another ascii art of tank
auto tank = vbox({
    text("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣴⠟⢿⣿⣿"),
    text("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⠀⠀⠀⠀⠀⣴⣶⠲⣶⢦⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⠶⠋⠁⢈⣷⠾⠟⠉"),
    text("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⠀⠀⠀⠀⠐⣿⣶⣺⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⠞⠋⠀⣠⡴⠞⠉⠀⠀⠀⠀"),
    text("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⡏⡍⠉⢹⡞⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡴⠞⠋⠘⣿⣶⠶⠋⠁⠀⠀⠀⠀⠀⠀⠀"),
    text("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣷⣄⣴⠿⠦⠤⣤⣀⣸⡇⠳⠶⠘⣧⣀⣀⣀⣀⠀⠀⠀⠀⣀⡤⠞⣏⠀⣀⡤⠖⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"),
    text("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣤⣶⣦⣼⡿⢦⣿⡀⢐⠐⣿⠉⢽⡿⠿⠿⠿⠿⠿⣿⠿⠿⣧⣤⠶⢿⠁⣀⡤⠞⠋⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"),
    text("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⠿⢿⣯⣿⣥⣤⣤⣽⠿⣶⡶⠦⠀⠙⠂⠐⢦⢀⣺⠿⣶⡞⠉⠀⣠⣾⡿⣿⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"),
    text("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡘⣆⠋⢀⡔⠋⢠⠞⠀⣴⠛⠶⣄⠀⠀⠑⡶⠞⢫⣠⠞⢀⣱⢶⣿⠇⣠⠟⣶⡿⢷⣽⣿⡷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"),
    text("⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣈⣓⣾⣦⣀⣱⣄⣈⣧⣀⣘⣦⣀⣘⣦⣀⡼⠓⠶⠛⣣⣤⠟⠛⣻⣯⣾⣿⣿⣷⣾⣿⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"),
    text("⢠⣤⣤⣴⣶⣶⣿⣿⣿⣏⣵⣿⣷⣶⣷⣿⣿⣿⠿⠶⠶⣶⣶⣶⡶⠾⠾⠿⢿⣟⣛⠛⢻⣛⣛⣉⣉⣉⣉⡉⢹⣯⡙⠛⢿⣛⠻⣗⣒⠶⠦⢤⣄⣀⡀⠀⠀⠀⠀"),
    text("⣾⣿⠶⣿⣿⠧⢾⣧⠀⡇⠀⠀⠀⠇⠀⢹⠉⠉⡟⠲⢤⡀⠀⠈⣉⣙⣒⣲⣦⣤⣉⣻⣏⣉⠉⠉⠉⠉⠉⠁⠀⠀⠙⢦⣀⡼⣷⣤⡈⠉⠓⢲⣶⣾⣿⣿⡳⢶⡄"),
    text("⠚⣿⣠⣿⡇⠀⣾⡿⠒⡿⠒⢶⣆⣱⣤⣤⣤⠀⣇⠀⠈⣇⡴⠻⠛⠛⠛⠋⠉⠉⠉⢿⠿⠿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠞⠛⠛⠳⣄⡴⠋⠀⠀⠀⢀⣀⣀⣿"),
    text("⠀⠛⠛⢻⡆⠀⣿⣧⠀⠁⠀⠀⠀⡇⠀⠈⠉⠉⡇⠀⠀⣿⠃⠀⣀⣤⣴⣶⣶⣶⣤⠬⣷⣤⣤⣤⣤⣤⣤⣶⣶⣶⣶⣖⣶⣶⡶⠾⢿⡿⣷⣤⣴⣶⣿⣿⣿⣿⠛"),
    text("⠀⠀⠀⠈⣷⣿⣷⣬⠀⠀⠒⠒⠒⢶⠤⠬⢤⣀⣀⠀⠀⣯⣴⣿⣿⡿⢿⣿⣛⠻⣷⠀⠀⠀⠀⠀⠉⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⣠⢿⣿⣷⣿⣿⣟⣸⣿⣿⡿⠀"),
    text("⠀⠀⠀⠀⠹⣿⣿⣿⣶⣶⣤⣤⣀⣸⣄⠀⠀⠀⠘⣠⣴⣿⣿⣿⣿⣿⣟⣛⣛⣻⣯⣀⣀⣀⣀⣀⡀⠀⢀⣠⣤⣤⣤⣤⣤⣄⣞⣡⠟⢉⣿⣿⣿⣲⣿⣿⡿⠃⠀"),
    text("⠀⠀⠀⠀⠀⠹⣿⣿⣾⣿⣼⣿⣏⢸⣿⡋⢹⣶⠋⢹⣿⡟⠛⣿⣿⣿⣿⣿⣿⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣼⣇⣼⣿⡅⢳⣀⣿⣿⠿⠿⢿⣿⠟⠁⠀⠀"),
    text("⠀⠀⠀⠀⠀⠀⠙⠻⠿⢿⣿⣿⣿⣿⣿⣷⣾⣿⣇⣾⣿⣇⣸⣿⣿⣿⣛⠃⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣽⢟⣱⣿⣿⠟⠁⠀⠀⠀⠀"),
    text("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠛⠛⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣥⣾⣿⣿⣿⣿⠿⠿⠿⠿⠟⠛⠛⠛⠛⠋⠉⠉⠉⠙⠛⠛⠛⠛⠛⠋⠁⠀⠀⠀⠀⠀⠀"),
    text("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠙⠉⠉⠉⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"),
});

// 删除所有数据，需要二次确认
bool modal_shown = false;
auto show_modal = [] { modal_shown = true; };
auto hide_modal = [] { modal_shown = false; };
auto clear_data = [] {
  Database::ClearRecord();
  modal_shown = false;
};

Component ModalComponent(std::function<void()> clear_data,
                         std::function<void()> hide_modal) {
  auto component =
      Container::Horizontal({
          Button("确定(危险)", clear_data, ButtonOption::Animated(Color::Red)),
          Button("退出", hide_modal, ButtonOption::Animated()),
      }) |
      center;
  return component;
}

Component setting_main =
    Container::Horizontal({
        Button("清除数据", [] { show_modal(); }),
    }) |
    Modal(ModalComponent(clear_data, hide_modal), &modal_shown);
//
} // namespace

auto settings = Renderer(setting_main, [] {
  return vbox({
      text("De Wapens Neder") | center | inverted,
      text("不要战争!") | center | inverted,
      dbox({
          tank | center | color(Color::NavajoWhite1),
          setting_main->Render() | clear_under | center,
      }),
      separatorHeavy(),
      // 帮助文字
      text("帮助") | center | bold,
      hbox({
          vbox({
              text("快捷键:      "),
              text("------主界面    F1"),
              text("------数据      F2"),
              text("------设置&帮助 F3"),
              text("------退出      Esc"),
              text("------顺序切换  Tab"),
          }) | border,
      }) | center,
  });
});
