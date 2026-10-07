#include <stddef.h>
#include <stdint.h>
#include <termios.h>
#include <unistd.h>

#include <config.h>

static int16_t select_index = 0;
static int16_t downtime = 0;
static const char *options[] = {"envycontrol"};

static int option_count = sizeof(options) / sizeof(options[0]);

static void render() {
  printf("\033[H\033[J"); // clear screen
  printf("┌──────────────────┐\n│ Use ↑ and ↓      │\n│   Select:        │\n");

  for (int i = 0; i < option_count; i++) {
    if (select_index == i)
      printf("│  > %-13s │\n", options[i]);

    else
      printf("│    %-13s │\n", options[i]);
  }

  printf("└──────────────────┘\n");

  fflush(stdout);
}

static inline void clamp_index() {
  if (select_index >= option_count) {
    select_index = 0;
  } else if (select_index < 0) {
    select_index = option_count - 1;
  }
}

static char key(void) {
  char c = 0;
  read(STDIN_FILENO, &c, 1);
  return c;
}

int main(void) {
  struct termios original, modified;
  char c;

  tcgetattr(STDIN_FILENO, &original);

  modified = original;
  modified.c_lflag &= ~(ICANON | ECHO);
  modified.c_cc[VMIN] = 0;  // read() doesn't block indefinitely
  modified.c_cc[VTIME] = 1; // timeout 100ms
  tcsetattr(STDIN_FILENO, TCSANOW, &modified);

  render();

  while (1) {
    c = key();
    if (c == 0) {
      if (++downtime >= 100) {
        select_index = 0;
        break;
      }
      continue;
    }
    downtime = 0;
    if (c == '\033') {
      if (key() != '[')
        continue; // ignore Esc

      c = key(); // 'A' || 'B'

      if (c == 'A') {
        select_index--;
        clamp_index();
        render();
      } else if (c == 'B') {
        select_index++;
        clamp_index();
        render();
      }
    } else if (c == '\n' || c == '\r') {
      break;
    }
  }
  Config::default_setup();
  tcsetattr(STDIN_FILENO, TCSANOW, &original);

  return 0;
}
