/********************************************************************************
** Form generated from reading UI file 'downloadwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNLOADWIDGET_H
#define UI_DOWNLOADWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DownloadWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QProgressBar *progressBar;

    void setupUi(QWidget *DownloadWidget)
    {
        if (DownloadWidget->objectName().isEmpty())
            DownloadWidget->setObjectName(QStringLiteral("DownloadWidget"));
        DownloadWidget->resize(325, 61);
        DownloadWidget->setStyleSheet(QStringLiteral("background-color: rgb(73, 73, 73);"));
        horizontalLayout_2 = new QHBoxLayout(DownloadWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(DownloadWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QLatin1String("QLabel {\n"
"    font-family: \"Microsoft YaHei\";\n"
"    font-size: 14px;\n"
"    color: #FFFFFF;\n"
"}"));

        horizontalLayout->addWidget(label);

        progressBar = new QProgressBar(DownloadWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setStyleSheet(QLatin1String("QProgressBar{\n"
"	font-family: \"Microsoft YaHei\";\n"
"    font-size: 14px;\n"
"    color: #FFFFFF;\n"
"}"));
        progressBar->setValue(0);

        horizontalLayout->addWidget(progressBar);


        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(DownloadWidget);

        QMetaObject::connectSlotsByName(DownloadWidget);
    } // setupUi

    void retranslateUi(QWidget *DownloadWidget)
    {
        DownloadWidget->setWindowTitle(QApplication::translate("DownloadWidget", "\350\265\204\346\272\220\344\270\213\350\275\275\345\231\250", Q_NULLPTR));
        label->setText(QApplication::translate("DownloadWidget", "\344\270\213\350\275\275\344\270\255..", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DownloadWidget: public Ui_DownloadWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOADWIDGET_H
