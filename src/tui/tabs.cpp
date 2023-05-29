#include <chrono> // for operator""ms, literals
#include <vector> // for vector

#include "ftxui/component/component.hpp"         // for Menu, Renderer, Vertical
#include "ftxui/component/component_options.hpp" // for MenuOption, UnderlineOption
#include "ftxui/screen/color.hpp" // for Color, Color::Blue, Color::Red

#include "mainTab.cpp"
using namespace ftxui;
int tab_index = 0;

std::vector<std::string> tab_entries = {
    "Main", "empty", "empty", "empty", "empty", "Settings",
};

// should be customizable
class optional {
public:
  MenuOption option = MenuOption::HorizontalAnimated();
  optional() {
    using namespace std::literals; // for operator""ms
    option.underline.SetAnimationFunction(animation::easing::BackOut);
    option.underline.color_inactive = Color::Blue;
    // option.underline.color_active = Color::Red;
    option.underline.SetAnimationDuration(350ms);
    // option.underline.follower_delay = 250ms;
  }
} tabOption;

auto tab_selection = Menu(&tab_entries, &tab_index, tabOption.option);
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
      text("武装冲突装备损失开源信息管理系统") | bold | hcenter,
      tab_selection->Render(),
      tab_content->Render() | flex,
  });
});
