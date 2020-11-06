#include "bcm_lib/bcm2835.h"
#include "header.h"

#define L1 RPI_GPIO_P1_11   //17
#define L2 RPI_GPIO_P1_12   //18
#define L3 RPI_GPIO_P1_13   //27
#define L4 RPI_GPIO_P1_15   //22
#define AR1 RPI_GPIO_P1_16  //23
#define AR2 RPI_GPIO_P1_18  //24

int init_gpio() {
    if (!bcm2835_init())
        return 1;

    bcm2835_gpio_fsel(L1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(L2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(L3, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(L4, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(AR1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(AR2, BCM2835_GPIO_FSEL_OUTP);
}

void change_status(int code, char *mode, uint8_t on){
    switch (code) {
        case 11:
            printf("%s Lampada 1", mode);
            bcm2835_gpio_write(L1, on);
            break;
        case 12:
            printf("%s Lampada 2", mode);
            bcm2835_gpio_write(L2, on);
            break;
        case 13:
            printf("%s Lampada 3", mode);
            bcm2835_gpio_write(L3, on);
            break;
        case 14:
            printf("%s Lampada 4", mode);
            bcm2835_gpio_write(L4, on);
            break;
        case 21:
            printf("%s Ar 1", mode);
            bcm2835_gpio_write(AR1, on);
            break;
        case 22:
            printf("%s Ar 2", mode);
            bcm2835_gpio_write(AR2, on);
            break;
        default:
            break;
    }
}

void turn_on_device(int code) {
    change_status(code, "Ligando", LOW);
}

void turn_off_device(int code) {
    change_status(code, "Desligando", HIGH);
}
