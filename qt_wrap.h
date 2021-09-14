// Non standard directive, but supported by most compiler to includer the
// header only once
#pragma once

// Type aliases
typedef void   ANY;
typedef void   QObject;
typedef void   QApplication;
typedef void   QPushButton;
typedef void   QWidget;
typedef void   QAbstractButton;
typedef void   QLineEdit;
typedef void   QLayout;
typedef void   QFormLayout;
typedef void   QLabel;

void qt_qobject_del(QObject* self);
void qt_qobject_dumpObjectInfo(QObject* self);
void qt_qobject_dumpObjectTree(QObject* self);
void qt_qobject_print(QObject* self);


QApplication* qt_app_new(int argc, char** argv);
QApplication* qt_app_new2();

// Instantiate any QT widget by name
QWidget* qt_widget_new(QWidget* parent, int type);

void qt_widget_setText(QWidget* self, const char* text);

// QApplication
int  qt_app_exec(QApplication* self);

// Any QtWidget
void          qt_QWidget_show(QWidget* self);
void          qt_QWidget_setToolTip(QWidget* self, const char* tooltip);

// QPushButton wrappers
QPushButton*  qt_QPushButton_new(QWidget* parent, const char* label);
void          qt_QPushButton_onClicked_test(QPushButton* self );

// Abstract PushbButton
void          qt_button_onClicked(QAbstractButton* self, void* ctx, void (* callback) (void*) );
void          qt_button_setText(QAbstractButton* self, const char* text);

const char*   qt_QLineEdit_text(QLineEdit* self);

QLayout*     qt_layout_new(QWidget* parent, int type);
QObject*     qt_QFormLayout_addWidgetAndLabel(QFormLayout* self, int type, const char* label);

QLabel* qt_QFormLayout_addLabel1(QFormLayout* self, const char* label_text);

void qt_msgbox_info(QWidget* parent, const char* title, const char* text);

void qt_QLineEdit_onTextChanged( QLineEdit* self
                               , void* ctx
                               , void (* callback) (void* ctx, QLineEdit* self) );
