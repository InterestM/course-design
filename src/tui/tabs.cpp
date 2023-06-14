#include <ftxui/component/component.hpp>         // for Menu, Renderer, Vertical
#include <ftxui/component/component_options.hpp> // for MenuOption, UnderlineOption

#include "tui/edit.hpp"
#include "tui/homescreen.hpp"
#include "tui/manageData.hpp"
#include "tui/option/options.hpp"
#include "tui/setting.hpp"

namespace {

int tab_index = 0;

std::vector<std::string> tab_entries = {
    "主界面",
    "数据",
    "设置",
};
auto tab_selection =
    Menu(&tab_entries, &tab_index, Options::GetInstance().GetOption());
auto tab_content = Container::Tab(
    {
        homescreen,
        dataManager,
        settings,
    },
    &tab_index);

auto main_container = Container::Vertical({
    tab_selection,
    tab_content | flex,
});

} // namespace

auto main_renderer = Renderer(main_container, [] {
  return vbox({
      text("武装冲突装备损失开源信息管理系统") | bold | hcenter,
      main_container->Render(),
  });
});
