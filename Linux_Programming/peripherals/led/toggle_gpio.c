// toggle_gpio.c
#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>

#define CHIP_NAME "gpiochip0"   // Adjust if needed
#define GPIO_LINE 18            // BCM pin number

int main() {
    struct gpiod_chip *chip;
    struct gpiod_line *line;

    chip = gpiod_chip_open_by_name(CHIP_NAME);
    if (!chip) {
        perror("Open chip failed");
        return 1;
    }

    line = gpiod_chip_get_line(chip, GPIO_LINE);
    if (!line) {
        perror("Get line failed");
        gpiod_chip_close(chip);
        return 1;
    }

    if (gpiod_line_request_output(line, "toggle_gpio", 0) < 0) {
        perror("Request line as output failed");
        gpiod_chip_close(chip);
        return 1;
    }

    printf("Toggling GPIO %d...\n", GPIO_LINE);
    for (int i = 0; i < 5; i++) {
        gpiod_line_set_value(line, 1);
        sleep(1);
        gpiod_line_set_value(line, 0);
        sleep(1);
    }

    gpiod_line_release(line);
    gpiod_chip_close(chip);
    return 0;
}
