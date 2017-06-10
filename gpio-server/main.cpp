#include "RPI.h"

#include <stdio.h>
#include <string.h>
#include "hysocket.h"


#define INP_GPIO(g)   *(gpio.addr + ((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g)   *(gpio.addr + ((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio.addr + (((g)/10))) |= (((a)<=3?(a) + 4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET  *(gpio.addr + 7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR  *(gpio.addr + 10) // clears bits which are 1 ignores bits which are 0

#define GPIO_READ(g)  *(gpio.addr + 13) &= (1<<(g))

int map_peripheral(struct bcm2835_peripheral *p);
void unmap_peripheral(struct bcm2835_peripheral *p);

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
