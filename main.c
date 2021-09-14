
#include <stdio.h>
#include "mntypes.h"
//#include "src/qt_wrap/headers.h"

#include "./src/qt_wrapper/tqstring.h"


int main(int argc, char *argv[])
{
    do_test();
    printf("hello world %d\n",(int)cstring_count("hello"));
    QString* s= QString_new_from_cstring("ana\n");
    QString_add_cstring(s," merhab \n");
    //QString_printf(s);
    printf("%s",QString_to_cstring_cpy(s));
    QString_free(&s);


    //    void* app=TQApplication_new(&argc,argv);
    //    void* win= QMainWindow_new(0,2);
    //    void* tabwin=QTabWidget_new(win);
    //    QTabWidget_set_tabs_closable(tabwin,true);
    //    QTabWidget_tabCloseRequested_connect(tabwin,tabwin,tabwin,QTabWidget_close_tab);
    //    void* widget = QWidget_new(win,0);
    //    void* vbox = QVBoxLayout_new(widget);
    //    void* lab =QLabel_new("label",win,0);
    //    QCLineEdit* edit=QLineEdit_new(widget);
    //    QLineEdit_set_text(edit,"hello world! me");
    //    QBoxLayout_addWidget(vbox,lab,0,0);
    //    QBoxLayout_addWidget(vbox,edit,0,0);
    //    //QLabel_setText(lab,QLineEdit_text(edit)->string);
    //    //QLabel_adjust_size(lab);
    //    QTabWidget_add_tab(tabwin,widget,"just a tab");
    //    QTabWidget_add_tab(tabwin,QLabel_new("2nd label",win,0),"another  tab");
    //    QMainWindow_setCentralWidget(win,tabwin);
    //    QMainWindow_show(win);
    //    printf("hello world!\n");
    //    return TQApplication_exec(app);
}

