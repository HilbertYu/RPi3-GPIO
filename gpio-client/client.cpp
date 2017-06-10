#include <stdio.h>
#include "hysocket.h"
// void* rec(void* s)
// {
//     HySocketBase * b = (HySocketBase*)s;
//
//     while(1)
//     {
//         int len = 0;
//         b->recv(&len , 4);
//         char buf[128] = {0};
//         b->recv_all(buf, len);
//         printf("\n>> :%s\n", buf);
//     }
//
// }

int main(int argc, const char * argv[])
{
    HySocketClient * cl = new HySocketClient;
    cl->connect("192.168.50.249", 20000);

    // pthread_t p;
    // pthread_create(&p, NULL, rec, cl);

    while (1)
    {
        char buf[128];
        printf("Me:");
        scanf("%[^\n]s", buf);
        getchar();
        int len = strlen(buf);
        int ret = cl->send_all(&len, 4);
        ret = cl->send_all(buf, len);
    }
    return 0;
}
