#ifndef RPI_H
#define RPI_H


#include <stdio.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>

//#define BCM2708_PERI_BASE       0x20000000
#define BCM2708_PERI_BASE       0x3F000000
#define GPIO_BASE               (BCM2708_PERI_BASE + 0x200000)// GPIO controller 

#define BLOCK_SIZE      (4*1024)

// IO Acces
struct bcm2835_peripheral {
    unsigned long addr_p;
    int mem_fd;
    void *map;
    volatile unsigned int *addr;
};


extern struct bcm2835_peripheral gpio;  // They have to be found somewhere, but can't be in the header


#endif /* end of include guard: RPI_H */
