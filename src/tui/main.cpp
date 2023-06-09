#include <chrono> // for operator""ms, literals
#include <ftxui/dom/elements.hpp>
#include <thread> // for sleep_for, thread

#include "ftxui/component/component.hpp" // for Checkbox, Renderer, Horizontal, Vertical, Input, Menu, Radiobox, ResizableSplitLeft, Tab
#include "ftxui/component/screen_interactive.hpp" // for Component, ScreenInteractive
#include "include/tui/tabs.hpp"

int main(int argc, char *argv[]) {
  using namespace ftxui;
  auto screen = ScreenInteractive::Fullscreen();
  int shift = 0;

  std::atomic<bool> refresh_ui_continue = true;
  std::thread refresh_ui([&] {
    while (refresh_ui_continue) {
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(0.05s);
      // The |shift| variable belong to the main thread. `screen.Post(task)`
      // will execute the update on the thread where |screen| lives (e.g. the
      // main thread). Using `screen.Post(task)` is threadsafe.
      screen.Post([&] { shift++; });
      // After updating the state, request a new frame to be drawn. This is done
      // by simulating a new "custom" event to be handled.
      screen.Post(Event::Custom);
    }
  });

  screen.Loop(main_renderer | bgcolor(Color::Black));
  refresh_ui_continue = false;
  refresh_ui.join();

  return 0;
}
