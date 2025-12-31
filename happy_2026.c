#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("\033[2J\033[H");

    for (int i = 3; i > 0; i--) {
        printf("\033[H\n\n  COUNTDOWN: %d...", i);
        fflush(stdout);
        sleep(1);
    }

    printf("\033[2J\033[H");
    const char *frames[] = {
        "      .      \n      |      ",
        "    \\ | /    \n    -- * --  \n    / | \\    ",
        "  '  .  .  ' \n  .  HAPPY  .\n  '   2026  ' \n  .  .  .  . "
    };

    for (int f = 0; f < 3; f++) {
        printf("\033[H\n\n%s\n", frames[f]);
        fflush(stdout);
        usleep(500000);
    }

    printf("\n   HAPPY NEW YEAR!!\n\n");
    return EXIT_SUCCESS;
}
