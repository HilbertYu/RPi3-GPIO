#include "RPI.h"
#include "rpi_gpio.h"

#include <stdio.h>
#include <string.h>
#include "hysocket.h"


RPiGpio gpios;
int g_server_stop = 0;

void* rec(void* s)
{
    HySocketBase * b = (HySocketBase*)s;

    while(1)
    {
        int len = 0;
        b->recv(&len , 4);
        char buf[128] = {0};
        b->recv_all(buf, len);
        printf("\n>> :%s\n", buf);

        if (strcmp(buf, "r1") == 0)
        {
            gpios.setOuput(17, RPiGpio::HIGH);
        }
        else if (strcmp(buf, "r0") == 0)
        {
            gpios.setOuput(17, RPiGpio::LOW);
        }
        else if (strcmp(buf, "g1") == 0)
        {
            gpios.setOuput(4, RPiGpio::HIGH);
        }
        else if (strcmp(buf, "g0") == 0)
        {
            gpios.setOuput(4, RPiGpio::LOW);

        }
        else if (strcmp(buf, "22l") == 0)
        {
            gpios.setOuput(22, RPiGpio::LOW);
        }
        else if (strcmp(buf, "22h") == 0)
        {
            gpios.setOuput(22, RPiGpio::HIGH);
        }
        else if (strcmp(buf, "27l") == 0)
        {
            gpios.setOuput(27, RPiGpio::LOW);
        }
        else if (strcmp(buf, "27h") == 0)
        {
            gpios.setOuput(27, RPiGpio::HIGH);
        }
        else if (strcmp(buf, "bye") == 0)
        {
            gpios.setOuput(4, RPiGpio::LOW);
            gpios.setOuput(17, RPiGpio::LOW);
            break;
        }
    }

    g_server_stop = 1;

    return NULL;
}

int main(int argc, const char * argv[])
{

    if (gpios.init() < 0)
    {
        fprintf(stderr, "init fail\n");
        return -1;
    }

    gpios.setup(4, RPiGpio::FUNC_OUPUT);
    gpios.setup(17, RPiGpio::FUNC_OUPUT);

    gpios.setup(27, RPiGpio::FUNC_OUPUT);
    gpios.setup(22, RPiGpio::FUNC_OUPUT);

    gpios.setOuput(22, RPiGpio::LOW);
    gpios.setOuput(27, RPiGpio::LOW);
    gpios.setOuput(4, RPiGpio::LOW);
    gpios.setOuput(17, RPiGpio::LOW);

//    return 0;

//    gpios.setOuput(22, RPiGpio::HIGH);
//    gpios.setOuput(27, RPiGpio::HIGH);
#if 0
    //gpios.setOuput(22, RPiGpio::HIGH);
    //gpios.setOuput(27, RPiGpio::HIGH);


    gpios.setOuput(27, RPiGpio::HIGH);
    gpios.setOuput(22, RPiGpio::LOW);
    sleep(2);

    gpios.setOuput(22, RPiGpio::LOW);
    gpios.setOuput(27, RPiGpio::LOW);
    sleep(1);

    gpios.setOuput(27, RPiGpio::LOW);
    gpios.setOuput(22, RPiGpio::HIGH);

    sleep(2);
    gpios.setOuput(22, RPiGpio::LOW);
    gpios.setOuput(27, RPiGpio::LOW);

//    return 0;
 //   return 0;
#endif

#if 0
    gpios.setOuput(4, RPiGpio::HIGH);
    gpios.setOuput(17, RPiGpio::LOW);
    sleep(2);

    gpios.setOuput(17, RPiGpio::LOW);
    gpios.setOuput(4, RPiGpio::LOW);
    sleep(1);

    gpios.setOuput(4, RPiGpio::LOW);
    gpios.setOuput(17, RPiGpio::HIGH);

    sleep(2);
    gpios.setOuput(17, RPiGpio::LOW);
    gpios.setOuput(4, RPiGpio::LOW);
#endif




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
    gpios.setOuput(22, RPiGpio::LOW);
    gpios.setOuput(27, RPiGpio::LOW);
    gpios.setOuput(4, RPiGpio::LOW);
    gpios.setOuput(17, RPiGpio::LOW);

    return 0;
}

