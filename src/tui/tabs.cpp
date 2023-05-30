#include <chrono> // for operator""ms, literals
#include <vector> // for vector

#include "ftxui/component/component.hpp"         // for Menu, Renderer, Vertical
#include "ftxui/component/component_options.hpp" // for MenuOption, UnderlineOption
#include "ftxui/screen/color.hpp" // for Color, Color::Blue, Color::Red

#include "homescreen.cpp"
#include "include/options.hpp"
#include "setting.cpp"
#include "table.cpp"
using namespace ftxui;
int tab_index = 0;

std::vector<std::string> tab_entries = {
    "Main", "empty", "empty", "empty", "empty", "Settings",
};
auto tab_selection = Menu(&tab_entries, &tab_index, option.option);
auto tab_content = Container::Tab(
    {
        homescreen,
        records,
        settings,
    },
    &tab_index);

auto main_container = Container::Vertical({
    tab_selection,
    tab_content,
});

auto main_renderer = Renderer(main_container, [] {
  return vbox({
      text("武装冲突装备损失开源信息管理系统") | bold | hcenter,
      tab_selection->Render(),
      tab_content->Render() | flex,
  });
});
