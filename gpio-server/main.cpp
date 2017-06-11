#include "RPI.h"

#include <stdio.h>
#include <string.h>
#include "hysocket.h"

int map_peripheral(struct bcm2835_peripheral *p);
void unmap_peripheral(struct bcm2835_peripheral *p);


#define INP_GPIO(g)   *(gpio.addr + ((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g)   *(gpio.addr + ((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio.addr + (((g)/10))) |= (((a)<=3?(a) + 4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET  *(gpio.addr + 7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR  *(gpio.addr + 10) // clears bits which are 1 ignores bits which are 0

#define GPIO_READ(g)  *(gpio.addr + 13) &= (1<<(g))

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

};


int g_server_stop = 0;

void* rec(void* s)
{
    HySocketBase * b = (HySocketBase*)s;

    int g = 17;
    while(1)
    {
        int len = 0;
        b->recv(&len , 4);
        char buf[128] = {0};
        b->recv_all(buf, len);
        printf("\n>> :%s\n", buf);

        if (strcmp(buf, "r1") == 0)
        {

            int g = 17;
            GPIO_SET = (1 << g);
        }
        else if (strcmp(buf, "r0") == 0)
        {
            int g = 17;
            GPIO_CLR = (1 << g);

        }
        else if (strcmp(buf, "g1") == 0)
        {
            int g = 4;
            GPIO_SET = (1 << g);

        }
        else if (strcmp(buf, "g0") == 0)
        {
            int g = 4;
            GPIO_CLR = (1 << g);

        }
        else if (strcmp(buf, "bye") == 0)
        {
            GPIO_CLR = (1 << g);
            break;

        }
    }

    g_server_stop = 1;

    return NULL;
}

int main(int argc, const char * argv[])
{

    {
        RPiGpio gpios;
        if (gpios.init() < 0)
        {
            fprintf(stderr, "init fail\n");
            return -1;
        }


        gpios.setup(4, RPiGpio::FUNC_OUPUT);
        gpios.setup(17, RPiGpio::FUNC_OUPUT);


        printf("1\n");

        gpios.setOuput(4, RPiGpio::HIGH);
        printf("1\n");
        sleep(1);
        gpios.setOuput(17, RPiGpio::HIGH);
        printf("1\n");
        sleep(1);
        gpios.setOuput(17, RPiGpio::LOW);
        sleep(1);
        printf("1\n");
        gpios.setOuput(4, RPiGpio::LOW);


        unmap_peripheral(&gpio);
        return 0;
    }

    if(map_peripheral(&gpio) == -1)
    {
        printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
        return -1;
    }

    int g = 4;
    INP_GPIO(g);
    OUT_GPIO(g);

    g = 17;
    INP_GPIO(g);
    OUT_GPIO(g);


    HySocketServer * s = new HySocketServer;
    s->setup("0.0.0.0", 20000);
    HySocketClient * cl = s->accept();
    pthread_t p;
    pthread_create(&p, NULL, rec, cl);

    while (!g_server_stop)
    {
        sleep(1);
#if 0
        char buf[128];
        printf("Me:");
        scanf("%[^\n]s", buf);
        getchar();
        int len = strlen(buf);
        int ret = 0;
        ret = cl->send_all(&len, 4);
        ret = cl->send_all(buf, len);
#endif
    }

    unmap_peripheral(&gpio);
    return 0;
}

#if 0
int main(void)
{

    if(map_peripheral(&gpio) == -1)
    {
        printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
        return -1;
    }

    int g = 4;
    INP_GPIO(g);
    OUT_GPIO(g);

    {
        GPIO_SET = (1 << g);
        sleep(2);

        GPIO_CLR = (1 << g);
        sleep(2);
    }

    unmap_peripheral(&gpio);
    return 0;
}
#endif
