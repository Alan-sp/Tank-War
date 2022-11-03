#include "widget.h"
#include "ui_widget.h"
#include<QPushButton>//按钮控件的头文件
#include<QDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //创建第一个按钮
    QPushButton *end=new QPushButton;
    end->setParent(this);
    end->setText("关闭");
    end->move(600,0);
    connect(end,&QPushButton::clicked,this,&QPushButton::close);
    resize(800,600);
    setWindowTitle("坦克动荡");
    QPushButton *start=new QPushButton;
    start->setText("开始游戏");
    start->setParent(this);
    start->move(400,400);
    QWidget *widget1=new QWidget;
    connect(start,&QPushButton::clicked,this,[=]()
    {widget1->show();this->close();});
}

Widget::~Widget()
{
    delete ui;
}

