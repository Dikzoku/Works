#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButton_ChooseDicFile,&QPushButton::clicked,this,&::Widget::pushButon_ChooseDicFile_clicked);
    connect(ui->pushButton_AddDic,&QPushButton::clicked,this,&::Widget::on_pushButton_AddDic_clicked);
    connect(ui->pushButton_ClearDic,&QPushButton::clicked,this,&::Widget::on_pushButton_ClearDic_clicked);
    connect(ui->pushButton_EraseDic,&QPushButton::clicked,this,&::Widget::on_pushButton_EraseDic_clicked);

    connect(ui->lineEdit_QueryWord,&QLineEdit::textChanged,this,&::Widget::lineEdit_QueryWord_changed);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::lineEdit_QueryWord_changed(){
    QString word=ui->lineEdit_QueryWord->text();
    if(word.size()){
        vector<string> vec=tree.query(word.toStdString(),1);
        vector<string> eql=tree.query(word.toStdString(),0);
        QStringList strlist;
        QStringListModel *model = new QStringListModel(this);

        matchword.clear();
        for(auto i:vec) matchword.insert(i);
        for(auto i:matchword) strlist<<QString::fromStdString(i);
        model->setStringList(strlist);
        ui->listView->setModel(model);
        ui->lcdNumber->display(QString::number(eql.size(),10));
        ui->lcdNumber_2->display(QString::number(vec.size()-eql.size(),10));
        ui->lcdNumber_3->display(QString::number(vec.size(),10));
    }else{
        QStringListModel *model = new QStringListModel(this);
        ui->listView->setModel(model);
        ui->lcdNumber->display(0);
        ui->lcdNumber_2->display(0);
        ui->lcdNumber_3->display(0);
    }
}


void Widget::pushButon_ChooseDicFile_clicked()
{
    QString curPath=QDir::currentPath()+"//text";
    QString dlgTitle="选择一个字典文件";
    QString filter="文本文件(*.txt);;所有文件(*.*)";
    QString aFileName=QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if (!aFileName.isEmpty()){
        ifstream in(aFileName.toStdString());
        string dic;
        while(in>>dic){
            tree.insert(dic);
            if(!dictionary.count(dic)) dictionary.insert(dic);
        }
        in.close();
        QStringList strlist;
        QStringListModel *model = new QStringListModel(this);
        for(auto i:dictionary) strlist<<QString::fromStdString(i);
        model->setStringList(strlist);
        ui->listView_2->setModel(model);
        ui->lcdNumber_4->display(QString::number(dictionary.size(),10));

        Widget::lineEdit_QueryWord_changed();
        QMessageBox::information(this,"从文件向词典中添加单词","单词添加完毕！",QMessageBox::Ok,QMessageBox::NoButton);
    }
}




void Widget::on_pushButton_AddDic_clicked()
{
    QString dlgTitle="向词典中添加单词";
    QString txtLabel="请输入单词";
    QString defaultInput="";
    QLineEdit::EchoMode echoMode=QLineEdit::Normal;
    bool ok=false;
    QInputDialog Dialog;
    QString text = Dialog.getText(this, dlgTitle,txtLabel, echoMode,defaultInput,&ok);
    if (ok && !text.isEmpty()){
        string dic=text.toStdString();
        tree.insert(dic);
        if(!dictionary.count(dic)) dictionary.insert(dic);
        QStringList strlist;
        QStringListModel *model = new QStringListModel(this);
        for(auto i:dictionary) strlist<<QString::fromStdString(i);
        model->setStringList(strlist);
        ui->listView_2->setModel(model);
        ui->lcdNumber_4->display(QString::number(dictionary.size(),10));

        Widget::lineEdit_QueryWord_changed();
        QMessageBox::information(this,"向词典中添加单词","单词添加完毕！",QMessageBox::Ok,QMessageBox::NoButton);
    }
}


void Widget::on_pushButton_ClearDic_clicked()
{
    tree.clear();
    dictionary.clear();
    QStringListModel *model = new QStringListModel(this);
    ui->listView_2->setModel(model);
    ui->lcdNumber_4->display(QString::number(dictionary.size(),10));

    Widget::lineEdit_QueryWord_changed();
    QMessageBox::information(this,"清空词典","词典已经清空！",QMessageBox::Ok,QMessageBox::NoButton);
}


void Widget::on_pushButton_EraseDic_clicked()
{
    QString dlgTitle="从词典中删除单词";
    QString txtLabel="请输入单词";
    QString defaultInput="";
    QLineEdit::EchoMode echoMode=QLineEdit::Normal;
    bool ok=false;
    QInputDialog Dialog;
    QString text = Dialog.getText(this, dlgTitle,txtLabel, echoMode,defaultInput,&ok);
    if (ok && !text.isEmpty()){
        string dic=text.toStdString();
        tree.erase(dic);
        if(dictionary.count(dic)) dictionary.erase(dic);
        QStringList strlist;
        QStringListModel *model = new QStringListModel(this);
        for(auto i:dictionary) strlist<<QString::fromStdString(i);
        model->setStringList(strlist);
        ui->listView_2->setModel(model);
        ui->lcdNumber_4->display(QString::number(dictionary.size(),10));

        Widget::lineEdit_QueryWord_changed();
        QMessageBox::information(this,"从词典中删除单词","单词删除完毕！",QMessageBox::Ok,QMessageBox::NoButton);
    }
}


void Widget::on_pushButton_DicOut_clicked()
{
    QString curPath=QDir::currentPath()+"//text";
    QString dlgTitle="导出词典";
    QString filter="文本文件(*.txt);;所有文件(*.*)";
    QString aFileName=QFileDialog::getSaveFileName(this,dlgTitle,curPath,filter);

    if (!aFileName.isEmpty()){
        ofstream out(aFileName.toStdString());
        string dic;
        for(auto i:dictionary){
            out<<i<<'\n';
        }
        out.close();
        QMessageBox::information(this,"导出词典","词典导出完毕！",QMessageBox::Ok,QMessageBox::NoButton);
    }
}


void Widget::on_pushButton_WordOut_clicked()
{
    QString curPath=QDir::currentPath()+"//text";
    QString dlgTitle="导出匹配词";
    QString filter="文本文件(*.txt);;所有文件(*.*)";
    QString aFileName=QFileDialog::getSaveFileName(this,dlgTitle,curPath,filter);

    if (!aFileName.isEmpty()){
        ofstream out(aFileName.toStdString());
        string dic;
        for(auto i:matchword){
            out<<i<<'\n';
        }
        out.close();
        QMessageBox::information(this,"导出匹配词","匹配词导出完毕！",QMessageBox::Ok,QMessageBox::NoButton);
    }
}


void Widget::on_pushButton_BKTreeOut_clicked()
{
    QString curPath=QDir::currentPath()+"//text";
    QString dlgTitle="导出词典树结构";
    QString filter="png图片(*.png);;jpg图片(*.jpg);;pdf文件(*.pdf);;所有文件(*.*)";
    QString aFileName=QFileDialog::getSaveFileName(this,dlgTitle,curPath,filter);

    if (!aFileName.isEmpty()){
        string picpath=aFileName.toStdString();
        string dotpath=picpath.substr(0,picpath.size()-4)+".dot";
        tree.bKTreeOut(dotpath);

        string cmd="dot -T"+picpath.substr(picpath.size()-3,3)+" "+dotpath+" -o "+picpath;
        system(cmd.c_str());
        QMessageBox::information(this,"导出词典树结构","词典树导出完毕！",QMessageBox::Ok,QMessageBox::NoButton);
    }

}

