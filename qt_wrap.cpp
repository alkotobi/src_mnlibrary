
#include <QtWidgets>
#include <QApplication>
#include <QSysInfo>
#include <QtConcurrent/QtConcurrent>
//#include <QObject>
#include <functional>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

/** extern "C" =>  Remove C++ name mangling and makes the function
 * compatible with C. It enforces C linkage to the annotated symbol.
 **-----------------------------------------------------------------*/
#define EXPORT_C extern "C"

/** Delete any instance of a derived class of QObject
 * Note: It can be used for deleting instances QWidget, QApplication or QLayout.
 */
EXPORT_C
void qt_qobject_del(QObject* self)
{
    delete self;
}

EXPORT_C
const char* qt_qobject_ClassName(QObject* self)
{
    return self->metaObject()->className();
}

EXPORT_C
void qt_qobject_dumpObjectInfo(QObject* self)
{
    self->dumpObjectInfo();
}

EXPORT_C
void qt_qobject_dumpObjectTree(QObject* self)
{
    self->dumpObjectTree();
}

EXPORT_C
void qt_qobject_print(QObject* self)
{
    qDebug() << " [QOBjec] " << self;
}

enum class WidgetType
{
      Window         = 1
    , Window_main    = 2
    , QPushButton    = 3
    , QLabel         = 4
    , QLineEdit      = 5
    , QDoubleSpinBox = 6
};

using CtorFunction = std::function<QWidget* (QWidget* parent)>;
using CtorDatabase = std::map<int, CtorFunction>;

template<typename T> void register_ctor(CtorDatabase&  db, int type)
{
    db[type] = [](QWidget* parent){ return new (std::nothrow) T(parent); };
}

// Create an object of a QWidget given class, given its name
EXPORT_C
QWidget* qt_widget_new(QWidget* parent, int type)
{
    // 'static' => Initialize static object only once.
    static const CtorDatabase ctordb = []{
        auto db = CtorDatabase{};
        register_ctor<QWidget>(db,        (int) WidgetType::Window);
        register_ctor<QPushButton>(db,    (int) WidgetType::QPushButton);
        register_ctor<QLabel>(db,         (int) WidgetType::QLabel);
        register_ctor<QLineEdit>(db,      (int) WidgetType::QLineEdit);
        register_ctor<QDoubleSpinBox>(db, (int) WidgetType::QDoubleSpinBox);

        db[(int) WidgetType::Window_main] = [](QWidget* parent){
            QWidget* w = new (std::nothrow) QWidget(parent);
            w->resize(500, 400);
            w->setWindowTitle("MainWindow");
            w->show();
            return w;
        };
        return db;
    }();

    if(auto it = ctordb.find(type); it != ctordb.end())
    {  return it->second(parent);  }
    return nullptr;
}

EXPORT_C
QWidget* qt_window_main()
{
    QWidget* w = new (std::nothrow) QWidget{};
    w->resize(500, 400);
    w->setWindowTitle("MainWindow");
    w->show();
    return w;
}

EXPORT_C
QLayout* qt_layout_new(QWidget* parent, int type)
{
    if(type == 1) return new (std::nothrow) QVBoxLayout(parent);
    if(type == 2) return new (std::nothrow) QHBoxLayout(parent);
    if(type == 3) return new (std::nothrow) QFormLayout(parent);
    return nullptr;
}

EXPORT_C
QObject* qt_QFormLayout_addWidgetAndLabel(QFormLayout* self, int type, const char* label)
{
    QWidget* wdg = qt_widget_new(nullptr, type);
    if(wdg == nullptr){ return nullptr; }
    self->addRow(label, wdg);
    return wdg;
}

EXPORT_C
void qt_QFormLayout_addRowItem(QFormLayout* self, QWidget* field)
{
    self->addRow(field);
}


EXPORT_C
QLabel* qt_QFormLayout_addLabel1(QFormLayout* self, const char* label_text)
{
    auto btn = new QLabel(label_text);
    self->addRow(btn);
    return btn;
}


EXPORT_C
QApplication* qt_app_new(int argc, char** argv)
{
    std::cout << " [TRACE] Create QAppliction Object Ok" << std::endl;
    return new QApplication(argc, argv);
}

EXPORT_C
QApplication* qt_app_new2()
{
    std::cout << " [TRACE] Create QAppliction Object Ok" << std::endl;
    static int   argc = 1;
    static const char* argv [] = { "dummy_app" };
    return new QApplication(argc, (char**) argv);
}

EXPORT_C
int qt_app_exec(QApplication* self)
{
    return self->exec();
}

// -------- Wrappers for QWidget Class ------------------//

EXPORT_C
void qt_widget_show(QWidget* self)
{
    self->show();
}

template<typename T>
static bool set_text(QWidget* self, const char* text)
{
    auto obj = qobject_cast<T>(self);
    // Early return on Error.
    if(obj == nullptr ){ return false;  }
    obj->setText(text);
    return true;
}

EXPORT_C
void qt_widget_setText(QWidget* self, const char* text)
{
    if( set_text<QLabel*>(self, text))           return;
    if( set_text<QLineEdit*>(self, text))        return;
    if( set_text<QTextEdit*>(self, text))        return;
    if( set_text<QMessageBox*>(self, text))      return;
    if( set_text<QAbstractButton*>(self, text) ) return;
    // logger().log() << " [TRACE] Called function " << __FUNCTION__ << std::endl;
    self->setWindowTitle(text);
}


// -------- Wrappers for QPushButton Class ------------------//

// Install event handler (callback) for button clicked event
EXPORT_C
void qt_button_onClicked(  // Pointer to button
                           QAbstractButton* self
                           // Context of the callback. Note: C does not support closures
                           // or stateful function pointer. All data needs to be passed
                           // as arguments
                         , void* ctx
                           // Pointer to callback function pointer.
                         , void (* callback) (void* ctx) )
{
    QObject::connect(self, &QPushButton::clicked, [=]{
        callback(ctx);
    });
}


// Install event handler for
EXPORT_C
void qt_QLineEdit_onTextChanged(  QLineEdit* self
                                , void* ctx
                                , void (* callback) (void* ctx, QLineEdit* self) )
{
    QObject::connect(self, &QLineEdit::textChanged, [=]{
        callback(ctx, self);
    });
}


EXPORT_C
void qt_msgbox_info(QWidget* parent, const char* title, const char* text)
{
    QMessageBox::information(parent, title, text);
}

// Note: The string has to be released after with free() function.
EXPORT_C
const char* qt_QLineEdit_text(QLineEdit* self)
{
    return self->text().toLocal8Bit().constData();
}

EXPORT_C
double qt_QDoubleSpinBox_value(QDoubleSpinBox* self)
{
    return self->value();
}

EXPORT_C
void qt_QDoubleSpinBox_setValue(QDoubleSpinBox* self, double value)
{
    self->setValue(value);
}

EXPORT_C
void qt_QDoubleSpinBox_onValueChanged(
     QDoubleSpinBox* self
   , void* ctx
   , void (* callback)(void* ctx) )
{
    QObject::connect(  self, qOverload<double>(&QDoubleSpinBox::valueChanged)
                     , [=](double x){ callback(ctx);  }
                    );
}
