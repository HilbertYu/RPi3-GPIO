#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hysocket.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_client = new HySocketClient;
    //m_client->connect("192.168.50.249", 20000);
    m_client->connect("172.20.10.14", 20000);
}

MainWindow::~MainWindow()
{
    char buf[128];
    sprintf(buf, "bye");
    int len = strlen(buf);
    int ret = m_client->send_all(&len, 4);
    ret = m_client->send_all(buf, len);

    delete ui;
}


#if 0
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
#endif

void MainWindow::on_pushButton_pressed()
{
        char buf[128];
        //printf("Me:");
        //scanf("%[^\n]s", buf);
        sprintf(buf, "r1");
        int len = strlen(buf);
        int ret = m_client->send_all(&len, 4);
        ret = m_client->send_all(buf, len);
}

void MainWindow::on_pushButton_released()
{
        char buf[128];
        sprintf(buf, "r0");
        int len = strlen(buf);
        int ret = m_client->send_all(&len, 4);
        ret = m_client->send_all(buf, len);

}

void MainWindow::on_pushButton_2_pressed()
{
        char buf[128];
        sprintf(buf, "g1");
        int len = strlen(buf);
        int ret = m_client->send_all(&len, 4);
        ret = m_client->send_all(buf, len);

}

void MainWindow::on_pushButton_2_released()
{
        char buf[128];
        sprintf(buf, "g0");
        int len = strlen(buf);
        int ret = m_client->send_all(&len, 4);
        ret = m_client->send_all(buf, len);

}

void MainWindow::on_pushButton_3_pressed()
{
        char buf[128];
        sprintf(buf, "22h");
        int len = strlen(buf);
        int ret = m_client->send_all(&len, 4);
        ret = m_client->send_all(buf, len);
}


void MainWindow::on_pushButton_3_released()
{
        char buf[128];
        sprintf(buf, "22l");
        int len = strlen(buf);
        int ret = m_client->send_all(&len, 4);
        ret = m_client->send_all(buf, len);

}

void MainWindow::on_pushButton_4_pressed()
{
        char buf[128];
        sprintf(buf, "27h");
        int len = strlen(buf);
        int ret = m_client->send_all(&len, 4);
        ret = m_client->send_all(buf, len);

}

void MainWindow::on_pushButton_4_released()
{
        char buf[128];
        sprintf(buf, "27l");
        int len = strlen(buf);
        int ret = m_client->send_all(&len, 4);
        ret = m_client->send_all(buf, len);

}
