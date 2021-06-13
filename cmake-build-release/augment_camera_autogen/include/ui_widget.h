/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *static_foreground;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QListWidget *foreground_list;
    QSpacerItem *horizontalSpacer_2;
    QLabel *foreground_preview;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *add_foreground;
    QWidget *background;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QListWidget *background_list;
    QSpacerItem *horizontalSpacer_3;
    QLabel *background_preview;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *take_background_picture;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *add_background;
    QWidget *face_masks;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QListWidget *mask_list;
    QSpacerItem *horizontalSpacer_5;
    QLabel *mask_preview;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *add_mask;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(554, 450);
        gridLayout = new QGridLayout(Widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(Widget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        static_foreground = new QWidget();
        static_foreground->setObjectName(QStringLiteral("static_foreground"));
        gridLayout_2 = new QGridLayout(static_foreground);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        foreground_list = new QListWidget(static_foreground);
        new QListWidgetItem(foreground_list);
        foreground_list->setObjectName(QStringLiteral("foreground_list"));
        foreground_list->setEditTriggers(QAbstractItemView::NoEditTriggers);

        horizontalLayout_2->addWidget(foreground_list);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        foreground_preview = new QLabel(static_foreground);
        foreground_preview->setObjectName(QStringLiteral("foreground_preview"));

        horizontalLayout_2->addWidget(foreground_preview);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        add_foreground = new QPushButton(static_foreground);
        add_foreground->setObjectName(QStringLiteral("add_foreground"));

        horizontalLayout->addWidget(add_foreground);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        tabWidget->addTab(static_foreground, QString());
        background = new QWidget();
        background->setObjectName(QStringLiteral("background"));
        gridLayout_3 = new QGridLayout(background);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        background_list = new QListWidget(background);
        new QListWidgetItem(background_list);
        background_list->setObjectName(QStringLiteral("background_list"));
        background_list->setEditTriggers(QAbstractItemView::NoEditTriggers);

        horizontalLayout_3->addWidget(background_list);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        background_preview = new QLabel(background);
        background_preview->setObjectName(QStringLiteral("background_preview"));

        horizontalLayout_3->addWidget(background_preview);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        take_background_picture = new QPushButton(background);
        take_background_picture->setObjectName(QStringLiteral("take_background_picture"));

        horizontalLayout_4->addWidget(take_background_picture);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        add_background = new QPushButton(background);
        add_background->setObjectName(QStringLiteral("add_background"));

        horizontalLayout_4->addWidget(add_background);


        verticalLayout_2->addLayout(horizontalLayout_4);


        gridLayout_3->addLayout(verticalLayout_2, 0, 0, 1, 1);

        tabWidget->addTab(background, QString());
        face_masks = new QWidget();
        face_masks->setObjectName(QStringLiteral("face_masks"));
        gridLayout_4 = new QGridLayout(face_masks);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        mask_list = new QListWidget(face_masks);
        new QListWidgetItem(mask_list);
        mask_list->setObjectName(QStringLiteral("mask_list"));
        mask_list->setEditTriggers(QAbstractItemView::NoEditTriggers);

        horizontalLayout_5->addWidget(mask_list);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        mask_preview = new QLabel(face_masks);
        mask_preview->setObjectName(QStringLiteral("mask_preview"));

        horizontalLayout_5->addWidget(mask_preview);


        verticalLayout_3->addLayout(horizontalLayout_5);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        add_mask = new QPushButton(face_masks);
        add_mask->setObjectName(QStringLiteral("add_mask"));

        horizontalLayout_6->addWidget(add_mask);


        verticalLayout_3->addLayout(horizontalLayout_6);


        gridLayout_4->addLayout(verticalLayout_3, 0, 0, 1, 1);

        tabWidget->addTab(face_masks, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(Widget);

        tabWidget->setCurrentIndex(1);
        foreground_list->setCurrentRow(0);
        background_list->setCurrentRow(0);
        mask_list->setCurrentRow(0);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));

        const bool __sortingEnabled = foreground_list->isSortingEnabled();
        foreground_list->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = foreground_list->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("Widget", "None", Q_NULLPTR));
        foreground_list->setSortingEnabled(__sortingEnabled);

        foreground_preview->setText(QApplication::translate("Widget", "TextLabel", Q_NULLPTR));
        add_foreground->setText(QApplication::translate("Widget", "+", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(static_foreground), QApplication::translate("Widget", "Static Foreground", Q_NULLPTR));

        const bool __sortingEnabled1 = background_list->isSortingEnabled();
        background_list->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem1 = background_list->item(0);
        ___qlistwidgetitem1->setText(QApplication::translate("Widget", "None", Q_NULLPTR));
        background_list->setSortingEnabled(__sortingEnabled1);

        background_preview->setText(QApplication::translate("Widget", "TextLabel", Q_NULLPTR));
        take_background_picture->setText(QApplication::translate("Widget", "take background picture", Q_NULLPTR));
        add_background->setText(QApplication::translate("Widget", "+", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(background), QApplication::translate("Widget", "Background", Q_NULLPTR));

        const bool __sortingEnabled2 = mask_list->isSortingEnabled();
        mask_list->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem2 = mask_list->item(0);
        ___qlistwidgetitem2->setText(QApplication::translate("Widget", "None", Q_NULLPTR));
        mask_list->setSortingEnabled(__sortingEnabled2);

        mask_preview->setText(QApplication::translate("Widget", "TextLabel", Q_NULLPTR));
        add_mask->setText(QApplication::translate("Widget", "+", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(face_masks), QApplication::translate("Widget", "Face Masks", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
