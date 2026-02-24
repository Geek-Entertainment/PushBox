#include <gflags/gflags.h>
#include <ncurses.h>
#include <stage/map_file.h>
#include <stage/stage.h>

DEFINE_string(map, "maps/map1.txt", "Path to the map file to load");

int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  refresh();
  Stage stage;
  stage.MapRead(MapFile().Read(FLAGS_map));
  stage.Show();

  int ch;
  while ((ch = getch()) != ERR) {
    if (ch == 'q' || ch == 'Q' || ch == 27) {
      break;
    }
    switch (ch) {
      case KEY_UP:
        stage.RunUp();
        stage.Show();
        break;
      case KEY_DOWN:
        stage.RunDown();
        stage.Show();
        break;
      case KEY_LEFT:
        stage.RunLeft();
        stage.Show();
        break;
      case KEY_RIGHT:
        stage.RunRight();
        stage.Show();
        break;
      default:
        break;
    }

    // show the prompt after re-rendering (cursor automatically at last used
    // position)
    printw("\nPress arrow or 'q' to quit (last code %d)\n", ch);
    refresh();  // 刷新屏幕以显示新内容
  }
  endwin();
  return 0;
}