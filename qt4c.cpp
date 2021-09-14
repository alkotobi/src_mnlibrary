

/*
                QString
*/

#include <QString>

extern "C" QString* QString_new(){
    QString* s= new (std::nothrow) QString();
    return s;
}
extern "C" QString* QString_new_from_cstring(const char* str){
    QString* s= new (std::nothrow) QString(str);
    return s;
}
extern "C" void QString_free(QString** s_hld){
    delete *s_hld;
    *s_hld=0;
}
extern "C" char QString_is_empty(QString* s){
    if(s->isEmpty()){
        return 1;
    }else {
        return 0;
    }
}
extern "C" char QString_is_right_to_left(QString*s){

    if (s->isRightToLeft()) {
        return 1;
    }else return 0;
}
extern "C" double QString_to_double(QString*s){
    return s->toDouble();
}
extern "C" int QString_to_int(QString*s){
    return s->toInt();
}

extern "C" QString* QString_add_cstring(QString*s,char* cstring){
    *s=*s+cstring;
    return s;
}

extern "C" QString* QString_add_QString(QString*s,QString* s_sub){
    *s=*s+s_sub;
    return s;
}

extern "C" QString* QString_add_char(QString*s,char c){
    *s=*s+c;
    return s;
}
uint cstring_count(char* str)
{
    if (str) {
        for (uint i = 0; ; i++)
        {
            if (str[i] == 0)
            {
                return i;
            }
        }
    }
    else assert(str);
    return 0;
}
char* cstring_clone(char* str_src)
{
    if (!str_src)
    {
        str_src=(char*) "";
    }
    char* str = 0;
    uint count = cstring_count(str_src);
    str = (char*)calloc((count+1),sizeof (char));
    if(str){
        for (uint i = 0; i < count; i++)
        {
            str[i] = str_src[i];
        }
    }else assert(str);

    return str;
}

extern "C"
char* QString_to_cstring_cpy(QString*s){
    return cstring_clone(s->toUtf8().data());
}
extern "C"
void QString_printf(QString* s){
    printf("%s",s->toUtf8().data()) ;
}


/*
                QApplication
*/

#include <QApplication>

extern "C"
QApplication* QApplication_new(int argc, char** argv)
{
    return new QApplication(argc, argv);
}

extern "C"
QApplication* QApplication_new_no_param()
{
    static int   argc = 1;
    static const char* argv [] = { "dummy_app" };
    return new QApplication(argc, (char**) argv);
}

extern "C"
int QApplication_exec(QApplication* self)
{
    return self->exec();
}

extern "C"
void QApplication_setActiveWindow(QApplication *self, QWidget *active)
{
    self->setActiveWindow(active);
}

extern "C"
QWidget *QApplication_activeWindow(QApplication *self)
{
    return self->activeWindow();
}


/*
                QWidget
*/

#include <QWidget>

extern "C"
QWidget* QWidget_new_widget(QWidget *parent){
    return new QWidget(parent,Qt::Widget);
}

extern "C"
QWidget* QWidget_new_window(QWidget *parent){
    return new QWidget(parent,Qt::Window);
}

extern "C"
QWidget* QWidget_new_dialog(QWidget *parent){
    return new QWidget(parent,Qt::Dialog);
}

extern "C"
QWidget* QWidget_new_sheet(QWidget *parent){
    return new QWidget(parent,Qt::Sheet);
}

extern "C"
QWidget* QWidget_new_drawer(QWidget *parent){
    return new QWidget(parent,Qt::Drawer);
}

extern "C"
QWidget* QWidget_new_popup(QWidget *parent){
    return new QWidget(parent,Qt::Popup);
}

extern "C"
void QWidget_activate_window(QWidget *self)
{
    self->activateWindow();
}

extern "C"
void QWidget_adjust_size(QWidget *self)
{
    self->adjustSize();
}

extern "C"
QWidget *QWidget_focus_widget(QWidget *self)
{
    return self->focusWidget();
}

extern "C"
char QWidget_has_focus(QWidget *self)
{
    if(self->hasFocus()) return 1;else return 0;
}

extern "C"
int QWidget_height(QWidget *self)
{
    return self->height();
}

extern "C"
char QWidget_is_active_window(QWidget *self)
{
    if(self->isActiveWindow()) return 1;else return 0;
}

extern "C"
char QWidget_is_ancestor_of(QWidget *self,const QWidget *child)
{
    if(self->isAncestorOf(child)) return 1;else return 0;
}

extern "C"
char QWidget_is_enabled(QWidget *self)
{
   if(self->isEnabled()) return 1;else return 0;
}

extern "C"
char QWidget_is_full_screen(QWidget *self)
{
    if(self->isFullScreen()) return 1;else return 0;
}

extern "C"
char QWidget_is_hidden(QWidget *self)
{
    if(self->isHidden()) return 1;else return 0;
}

extern "C"
char QWidget_is_visible(QWidget *self)
{
    if(self->isVisible()) return 1;else return 0;
}


extern "C"
char QWidget_is_window(QWidget *self)
{
    if(self->isWindow()) return 1;else return 0;
}

extern "C"
QLayout *QWidget_layout(QWidget *self)
{
    return self->layout();
}

int QWidget_layoutDirection(QWidget *self)
{
    return self->layoutDirection();
}

extern "C"
QWidget *QWidget_next_in_focus_chain(QWidget *self)
{
    return self->nextInFocusChain();
}

extern "C"
QWidget *QWidget_parent_widget(QWidget *self)
{
    return self->parentWidget();
}

extern "C"
QWidget *QWidget_previous_in_focus_chain(QWidget *self)
{
    return self->previousInFocusChain();
}

extern "C"
void QWidget_scroll(QWidget *self, int dx, int dy)
{
    self->scroll(dx,dy);
}

extern "C"
void QWidget_set_parent(QWidget *self,QWidget *parent)
{
    self->setParent(parent);
}

extern "C"
int QWidget_width(QWidget *self)
{
    return self->width();
}

extern "C"
char Widget_close(QWidget *self)
{
    return self->close();
}

extern "C"
void Widget_hide(QWidget *self)
{
    self->hide();
}

extern "C"
void Widget_lower(QWidget *self)
{
    self->lower();
}

extern "C"
void Widget_raise(QWidget *self)
{
    self->raise();
}

extern "C"
void Widget_repaint(QWidget *self)
{
    self->repaint();
}

extern "C"
void Widget_set_disabled(QWidget *self, char disabled_state)
{
    self->setDisabled(disabled_state);
}

extern "C"
void Widget_set_visible(QWidget *self, char hidden_state)
{
    self->setVisible(hidden_state);
}

extern "C"
void Widget_set_style_sheet(QWidget *self, QString *style_sheet)
{
    self->setStyleSheet(*style_sheet);
}

extern "C"
void Widget_set_window_modified(QWidget *self, char modified_state)
{
    self->setWindowModified(modified_state);
}

extern "C"
void Widget_set_window_title(QWidget *self, QString *window_title)
{
    self->setWindowTitle(*window_title);
}

extern "C"
void Widget_show(QWidget *self)
{
    self->show();
}

extern "C"
void Widget_show_full_screen(QWidget *self)
{
    self->showFullScreen();
}

extern "C"
void Widget_show_maximized(QWidget *self)
{
    self->showMaximized();
}

extern "C"
void Widget_show_minimized(QWidget *self)
{
    self->showMinimized();
}

extern "C"
void Widget_show_normal(QWidget *self)
{
    self->showNormal();
}

extern "C"
void Widget_update(QWidget *self)
{
    self->update();
}

extern "C"
void Widget_free(QWidget ** wid_hld)
{
    delete *wid_hld;
    *wid_hld=0;
}




/*
         QLayout
*/
#include <QLayout>
#include <QBoxLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QStackedLayout>
#include <QFormLayout>

extern "C"
QBoxLayout* QBoxLayout_new_left_to_right(QWidget* parent){
    return new (std::nothrow) QBoxLayout(QBoxLayout::LeftToRight,parent);
}

extern "C"
QBoxLayout* QBoxLayout_new_right_to_left(QWidget* parent){
    return new (std::nothrow) QBoxLayout(QBoxLayout::RightToLeft,parent);
}

extern "C"
QBoxLayout* QBoxLayout_new_top_to_bottom(QWidget* parent){
    return new (std::nothrow) QBoxLayout(QBoxLayout::TopToBottom,parent);
}

extern "C"
QBoxLayout* QBoxLayout_new_bottom_to_top(QWidget* parent){
    return new (std::nothrow) QBoxLayout(QBoxLayout::BottomToTop,parent);
}

extern "C"
void QBoxLayout_free(QBoxLayout** layout_hld){
    delete *layout_hld;
    *layout_hld=0;
}

extern "C"
void QBoxLayout_add_layout(QBoxLayout *self, QLayout *layout)
{
    self->addLayout(layout);
}

extern "C"
void QBoxLayout_add_spacing(QBoxLayout *self, int size)
{
    self->addSpacing(size);
}

extern "C"
void QBoxLayout_add_stretch(QBoxLayout *self, int stretch)
{
    self->addStretch(stretch);
}

extern "C"
void QBoxLayout_add_widget
(QBoxLayout *self,QWidget *widget, int stretch,int alignement)
{
    self->addWidget(widget,stretch,(Qt::Alignment)alignement);
}


extern "C"
void QBoxLayout_insertLayout(QBoxLayout *self, int index, QLayout *layout, int stretch)
{
    self->insertLayout(index,layout,stretch);
}

extern "C"
void QBoxLayout_insert_spacing(QBoxLayout *self, int index, int size)
{
    self->insertSpacing(index,size);
}

extern "C"
void QBoxLayout_insert_stretch(QBoxLayout *self, int index, int stretch)
{
    self->insertStretch(index,stretch);
}

extern "C"
void QBoxLayout_insert_widget(QBoxLayout *self,int index, QWidget *widget, int stretch, int alignment)
{
    self->insertWidget(index,widget,stretch,(Qt::Alignment)alignment);
}


extern "C"
void QBoxLayout_set_direction(QBoxLayout *self, int direction)
{
    self->setDirection((QBoxLayout::Direction)direction);
}

extern "C"
void QBoxLayout_set_pacing(QBoxLayout *self, int spacing)
{
    self->setSpacing(spacing);
}

extern "C"
void QBoxLayout_set_stretch(QBoxLayout *self, int index, int stretch)
{
    self->setStretch(index,stretch);
}

extern "C"
int QBoxLayout_count(QBoxLayout *self)
{
    return self->count();
}

extern "C"
QLayoutItem *QBoxLayout_item_at(QBoxLayout *self, int index)
{
    return self->itemAt(index);
}

extern "C"
QLayout *QLayoutItem_layout(QLayoutItem *self)
{
    return self->layout();
}

extern "C"
QWidget *QLayoutItem_widget(QLayoutItem *self)
{
    return self->widget();
}
