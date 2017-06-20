#ifndef RPI_GPIO_H
#define RPI_GPIO_H

#include "RPI.h"

class RPiGpio
{
    bcm2835_peripheral m_gpio;

    void cleanFSL(int pin)
    {
        *(m_gpio.addr + ((pin)/10)) &= ~(7<<(((pin)%10)*3));
    }

public:
    enum
    {
        LOW  = 0,
        HIGH = 1,
        FUNC_OUPUT


    };

    RPiGpio(void)
    {
        m_gpio.addr_p = GPIO_BASE;
    }

    ~RPiGpio(void)
    {
        unmap_peripheral(&m_gpio);
    }

    int init(void)
    {
        if(map_peripheral(&m_gpio) == -1)
        {
            printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
            return -1;
        }
        return 0;
    }

    void setup(int pin, int mode)
    {
        if (mode == FUNC_OUPUT)
        {
            cleanFSL(pin);
            *(m_gpio.addr + ((pin)/10)) |=  (1<<(((pin)%10)*3));
        }

    }

    void setInput(int pin)
    {
        cleanFSL(pin);
    }

    void setOuput(int pin, int lv)
    {
        if (lv == HIGH)
        {
            *(m_gpio.addr + 7)  = (1 << pin);
        }
        else
        {
            *(m_gpio.addr + 10)  = (1 << pin);
        }
    }

    void setMultiOuput(int pin, int lv)
    {
        if (lv == HIGH)
        {
            *(m_gpio.addr + 7)  = pin;
        }
        else
        {
            *(m_gpio.addr + 10)  = pin;
        }
    }


};


#endif /* end of include guard: RPI_GPIO_H */
