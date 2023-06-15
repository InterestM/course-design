#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/screen/screen.hpp>

#include "tui/edit.hpp"
#include "tui/homescreen.hpp"
#include "tui/manageData.hpp"
#include "tui/option/options.hpp"
#include "tui/setting.hpp"
//// 标签菜单
int tab_index = 0;
namespace {
// 标签文本
std::vector<std::string> tab_entries = {
    "主界面",
    "数据",
    "设置&帮助",
};
// 标签选项
auto tab_selection =
    Menu(&tab_entries, &tab_index, Options::GetInstance().GetOption());
// 标签页内容
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

auto main_renderer =
    Renderer(main_container,
             [] {
               return vbox({
                   text("武装冲突装备损失开源信息管理系统") | bold | hcenter,
                   main_container->Render(),
               });
             }) |
    CatchEvent([](ftxui::Event event) {
      if (event == Event::F1) {
        tab_index = 0;
        return true;
      };
      if (event == Event::F2) {
        tab_index = 1;
        return true;
      }
      if (event == Event::F3) {
        tab_index = 2;
        return true;
      }
      if (event == Event::Escape) {
        exit(0);
      }
      return false;
    });
