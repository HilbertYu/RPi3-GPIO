#include "RPI.h"

#define INP_GPIO(g)   *(gpio.addr + ((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g)   *(gpio.addr + ((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio.addr + (((g)/10))) |= (((a)<=3?(a) + 4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET  *(gpio.addr + 7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR  *(gpio.addr + 10) // clears bits which are 1 ignores bits which are 0

#define GPIO_READ(g)  *(gpio.addr + 13) &= (1<<(g))

int map_peripheral(struct bcm2835_peripheral *p);

int main(void)
{

    if(map_peripheral(&gpio) == -1)
    {
        printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
        return -1;
    }

    int g = 4;
    // Define pin 7 as output
    INP_GPIO(g);
    OUT_GPIO(g);

//    printf("rd = %u\n", GPIO_READ(g));
//    while(1)
    {
        // Toggle pin 7 (blink a led!)
        GPIO_SET = (1 << g);
        sleep(2);

        GPIO_CLR = (1 << g);
        sleep(2);
 //   printf("rd = %u\n", GPIO_READ(g));

   //     GPIO_CLR = 1 << g;
  //      sleep(1);
    }

    unmap_peripheral(&gpio);
    return 0;
}
