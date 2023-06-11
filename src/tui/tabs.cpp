#include "ftxui/component/component.hpp"         // for Menu, Renderer, Vertical
#include "ftxui/component/component_options.hpp" // for MenuOption, UnderlineOption

#include "tui/option/options.hpp"
#include "tui/edit.hpp"
#include "tui/homescreen.hpp"
#include "tui/query.hpp"
#include "tui/setting.hpp"

namespace {

int tab_index = 0;

std::vector<std::string> tab_entries = {
    "主界面",
    "查询",
    "管理",
    "设置",
};
auto tab_selection =
    Menu(&tab_entries, &tab_index, Options::get_instance().option);
auto tab_content = Container::Tab(
    {
        homescreen,
        records,
        edits,
        settings,
    },
    &tab_index);

auto main_container = Container::Vertical({
    tab_selection,
    tab_content,
});

} // namespace

auto main_renderer = Renderer(main_container, [] {
  return vbox({
      text("武装冲突装备损失开源信息管理系统") | bold | hcenter,
      tab_selection->Render(),
      tab_content->Render() | flex,
  });
});
