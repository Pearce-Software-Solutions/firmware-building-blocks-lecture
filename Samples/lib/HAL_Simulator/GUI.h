#include <ncurses.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <cstring>

class tGUI {
public:
  tGUI();
  ~tGUI();
  void UpdateGUI();
  bool ExitRequested() const;
  void SetLEDState(bool state) {
    ledState_ = state;
  }
  bool InputState(unsigned index) const {
    return inputStates_.at(index);
  }
private:
  static constexpr auto WindowX = 0;
  static constexpr auto WindowY = 0;
  static constexpr auto WindowW = 19;
  static constexpr auto WindowH = 7;
  static constexpr auto ToggleColumn = 11;

  WINDOW* window_ {};
  int inputFD_ {};
  bool exitRequested_ {};
  bool ledState_ {};
  std::array<bool, 2> inputStates_ {};

  void BuildGUI();
  static int FindKeyboardDevice();
};

tGUI::tGUI()
{
	initscr();
  curs_set(0); // Hide cursor
	noecho(); // Don't echo typed characters
	keypad(stdscr, TRUE);
	refresh(); // Initialize stdscr
	window_ = newwin(WindowH, WindowW, WindowY, WindowX);
  inputFD_ = FindKeyboardDevice();
  if (inputFD_ < 0) {
    endwin();
    throw std::runtime_error("Failed to open keyboard device");
  }
  BuildGUI();
}

tGUI::~tGUI()
{
	endwin();
}

void tGUI::BuildGUI()
{
	wborder(window_, '|', '|', '-', '-', ' ', ' ', ' ', ' ');
  auto rowCount {0U};
	mvwprintw(window_, rowCount++, 5, "Pico2 Sim");
	mvwprintw(window_, rowCount++, 2, "LED     ( )");
	mvwprintw(window_, rowCount++, 2, "Button1 ( )");
	mvwprintw(window_, rowCount++, 2, "Button2 ( )");
	mvwprintw(window_, WindowH - 2, 2, "Press x to exit");
	wrefresh(window_);
}

void tGUI::UpdateGUI()
{
  struct input_event ev;
  if (read(inputFD_, &ev, sizeof(ev)) == sizeof(ev)) {
    if (ev.type == EV_KEY) {
      if (ev.code == KEY_X) {
          exitRequested_ = true;
      }
    }

    for (auto i = 0U; i < inputStates_.size(); i++) {
      if (ev.code == KEY_1 + i) {
        if ((ev.value == 1) || (ev.value == 2)) {
          inputStates_[i] = true;
        }
        else {
          inputStates_[i] = false;
        }
      }
    }
  }

  mvwprintw(window_, 1, ToggleColumn, "%c", ledState_ ? 'X' : ' ');
  mvwprintw(window_, 2, ToggleColumn, "%c", inputStates_.at(0) ? 'X' : ' ');
  mvwprintw(window_, 3, ToggleColumn, "%c", inputStates_.at(1) ? 'X' : ' ');

	wrefresh(window_);
}

bool tGUI::ExitRequested() const
{
  return exitRequested_;
}

int tGUI::FindKeyboardDevice() {
    for (int i = 0; i < 32; i++) {
        char path[64];
        snprintf(path, sizeof(path), "/dev/input/event%d", i);

        int fd = open(path, O_RDONLY | O_NONBLOCK);
        if (fd < 0) continue;

        char name[256];
        if (ioctl(fd, EVIOCGNAME(sizeof(name)), name) >= 0) {
            if (strstr(name, "keyboard") || strstr(name, "Keyboard")) {
                return fd;
            }
        }
        close(fd);
    }
    return -1;
}