#include <vector> // for vector

#include "ftxui/component/component.hpp" // for Checkbox, Renderer, Horizontal, Vertical, Input, Menu, Radiobox, ResizableSplitLeft, Tab

#include "mainTab.cpp"
using namespace ftxui;
int tab_index = 0;

std::vector<std::string> tab_entries = {
    "Main", "empty", "empty", "empty", "empty", "Help",
};
auto tab_selection =
    Menu(&tab_entries, &tab_index, MenuOption::HorizontalAnimated());
auto tab_content = Container::Tab(
    {
        mainTab,
    },
    &tab_index);

auto main_container = Container::Vertical({
    tab_selection,
    tab_content,
});

auto main_renderer = Renderer(main_container, [] {
  return vbox({
      text("Demo 测试中") | bold | hcenter,
      tab_selection->Render(),
      tab_content->Render() | flex,
  });
});
