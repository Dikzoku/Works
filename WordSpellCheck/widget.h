#ifndef WIDGET_H
#define WIDGET_H

#include "BKTree.h"
#include <QWidget>
#include <QDir>
#include <QFileDialog>
#include <QStringList>
#include <QStringListModel>
#include <QLineEdit>
#include <QListView>
#include <QLCDNumber>
#include <QInputDialog>
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void pushButon_ChooseDicFile_clicked();//从文件向词典中添加单词
    void lineEdit_QueryWord_changed();//输入要查找的单词
    void on_pushButton_AddDic_clicked();//向词典中添加单词
    void on_pushButton_ClearDic_clicked();//清空词典
    void on_pushButton_EraseDic_clicked();//从词典中删除单词
private slots:
    void on_pushButton_DicOut_clicked();//导出词典
    void on_pushButton_WordOut_clicked();//导出匹配词
    void on_pushButton_BKTreeOut_clicked();//导出BK树结构

private:
    Ui::Widget *ui;
    BKTree tree;
    set<string> dictionary;
    set<string> matchword;
};
#endif // WIDGET_H
