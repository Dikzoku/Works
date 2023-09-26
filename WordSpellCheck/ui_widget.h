/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pushButton_ChooseDicFile;
    QPushButton *pushButton_AddDic;
    QLineEdit *lineEdit_QueryWord;
    QLCDNumber *lcdNumber;
    QLCDNumber *lcdNumber_2;
    QFrame *line;
    QPushButton *pushButton_EraseDic;
    QPushButton *pushButton_ClearDic;
    QListView *listView;
    QLabel *label;
    QLabel *label_2;
    QLCDNumber *lcdNumber_3;
    QLabel *label_3;
    QListView *listView_2;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *pushButton_DicOut;
    QPushButton *pushButton_WordOut;
    QPushButton *pushButton_BKTreeOut;
    QLCDNumber *lcdNumber_4;
    QLabel *label_6;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 600);
        pushButton_ChooseDicFile = new QPushButton(Widget);
        pushButton_ChooseDicFile->setObjectName(QString::fromUtf8("pushButton_ChooseDicFile"));
        pushButton_ChooseDicFile->setGeometry(QRect(10, 90, 171, 41));
        pushButton_ChooseDicFile->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_AddDic = new QPushButton(Widget);
        pushButton_AddDic->setObjectName(QString::fromUtf8("pushButton_AddDic"));
        pushButton_AddDic->setGeometry(QRect(10, 150, 171, 41));
        pushButton_AddDic->setCursor(QCursor(Qt::PointingHandCursor));
        lineEdit_QueryWord = new QLineEdit(Widget);
        lineEdit_QueryWord->setObjectName(QString::fromUtf8("lineEdit_QueryWord"));
        lineEdit_QueryWord->setGeometry(QRect(400, 50, 191, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font.setPointSize(12);
        lineEdit_QueryWord->setFont(font);
        lcdNumber = new QLCDNumber(Widget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(470, 100, 121, 51));
        lcdNumber_2 = new QLCDNumber(Widget);
        lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));
        lcdNumber_2->setGeometry(QRect(470, 160, 121, 51));
        line = new QFrame(Widget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(380, 0, 20, 601));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        pushButton_EraseDic = new QPushButton(Widget);
        pushButton_EraseDic->setObjectName(QString::fromUtf8("pushButton_EraseDic"));
        pushButton_EraseDic->setGeometry(QRect(10, 210, 171, 41));
        pushButton_EraseDic->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_ClearDic = new QPushButton(Widget);
        pushButton_ClearDic->setObjectName(QString::fromUtf8("pushButton_ClearDic"));
        pushButton_ClearDic->setGeometry(QRect(10, 270, 171, 41));
        pushButton_ClearDic->setCursor(QCursor(Qt::PointingHandCursor));
        listView = new QListView(Widget);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(605, 51, 181, 521));
        QFont font1;
        font1.setPointSize(12);
        listView->setFont(font1);
        listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(400, 110, 71, 41));
        QFont font2;
        font2.setFamily(QString::fromUtf8("AcadEref"));
        font2.setPointSize(12);
        label->setFont(font2);
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(400, 170, 71, 31));
        label_2->setFont(font2);
        lcdNumber_3 = new QLCDNumber(Widget);
        lcdNumber_3->setObjectName(QString::fromUtf8("lcdNumber_3"));
        lcdNumber_3->setGeometry(QRect(470, 220, 121, 51));
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(420, 230, 41, 31));
        label_3->setFont(font2);
        listView_2 = new QListView(Widget);
        listView_2->setObjectName(QString::fromUtf8("listView_2"));
        listView_2->setGeometry(QRect(190, 50, 181, 521));
        listView_2->setFont(font1);
        listView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
        label_4 = new QLabel(Widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(250, 10, 51, 31));
        QFont font3;
        font3.setFamily(QString::fromUtf8("AcadEref"));
        font3.setPointSize(14);
        label_4->setFont(font3);
        label_5 = new QLabel(Widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(620, 10, 151, 31));
        label_5->setFont(font3);
        pushButton_DicOut = new QPushButton(Widget);
        pushButton_DicOut->setObjectName(QString::fromUtf8("pushButton_DicOut"));
        pushButton_DicOut->setGeometry(QRect(10, 530, 171, 41));
        pushButton_DicOut->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_WordOut = new QPushButton(Widget);
        pushButton_WordOut->setObjectName(QString::fromUtf8("pushButton_WordOut"));
        pushButton_WordOut->setGeometry(QRect(420, 530, 171, 41));
        pushButton_WordOut->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_BKTreeOut = new QPushButton(Widget);
        pushButton_BKTreeOut->setObjectName(QString::fromUtf8("pushButton_BKTreeOut"));
        pushButton_BKTreeOut->setGeometry(QRect(10, 480, 171, 41));
        pushButton_BKTreeOut->setCursor(QCursor(Qt::PointingHandCursor));
        lcdNumber_4 = new QLCDNumber(Widget);
        lcdNumber_4->setObjectName(QString::fromUtf8("lcdNumber_4"));
        lcdNumber_4->setGeometry(QRect(10, 420, 151, 51));
        label_6 = new QLabel(Widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 390, 111, 31));
        label_6->setFont(font2);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "\345\215\225\350\257\215\346\213\274\345\206\231\346\243\200\346\237\245", nullptr));
        pushButton_ChooseDicFile->setText(QApplication::translate("Widget", "\344\273\216\346\226\207\344\273\266\345\220\221\350\257\215\345\205\270\344\270\255\346\267\273\345\212\240\345\215\225\350\257\215", nullptr));
        pushButton_AddDic->setText(QApplication::translate("Widget", "\345\220\221\350\257\215\345\205\270\344\270\255\346\267\273\345\212\240\345\215\225\350\257\215", nullptr));
        lineEdit_QueryWord->setPlaceholderText(QApplication::translate("Widget", "\350\257\267\350\276\223\345\205\245\346\237\245\346\211\276\347\232\204\345\215\225\350\257\215", nullptr));
        pushButton_EraseDic->setText(QApplication::translate("Widget", "\344\273\216\350\257\215\345\205\270\344\270\255\345\210\240\351\231\244\345\215\225\350\257\215", nullptr));
        pushButton_ClearDic->setText(QApplication::translate("Widget", "\346\270\205\347\251\272\350\257\215\345\205\270", nullptr));
        label->setText(QApplication::translate("Widget", "\347\233\270\345\220\214\350\257\215", nullptr));
        label_2->setText(QApplication::translate("Widget", "\347\233\270\344\274\274\350\257\215", nullptr));
        label_3->setText(QApplication::translate("Widget", "\345\220\210\350\256\241", nullptr));
        label_4->setText(QApplication::translate("Widget", "\350\257\215\345\205\270", nullptr));
        label_5->setText(QApplication::translate("Widget", "\347\233\270\345\220\214\345\222\214\347\233\270\344\274\274\350\257\215", nullptr));
        pushButton_DicOut->setText(QApplication::translate("Widget", "\345\257\274\345\207\272\350\257\215\345\205\270", nullptr));
        pushButton_WordOut->setText(QApplication::translate("Widget", "\345\257\274\345\207\272\345\214\271\351\205\215\350\257\215", nullptr));
        pushButton_BKTreeOut->setText(QApplication::translate("Widget", "\345\257\274\345\207\272\350\257\215\345\205\270\346\240\221\347\273\223\346\236\204", nullptr));
        label_6->setText(QApplication::translate("Widget", "\350\257\215\345\205\270\345\215\225\350\257\215\346\225\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
