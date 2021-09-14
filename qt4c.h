#ifndef QT4C_H
#define QT4C_H

#define Qt_LeftToRight 0
#define Qt_RightToLeft 1
#define Qt_LayoutDirectionAuto 2
typedef void QApplication ;
typedef void QString ;
typedef void QWidget ;
typedef void QLayout ;
typedef void QBoxLayout ;
typedef void QLayoutItem;


 ;
/*
                QString
*/


QString* QString_new();
QString* QString_new_from_cstring(const char* str);
void QString_free(QString** s_hld);
char QString_is_empty(QString* s);
char QString_is_right_to_left(QString*s);
double QString_to_double(QString*s);
int QString_to_int(QString*s);
QString* QString_add_cstring(QString*s,char* cstring);
QString* QString_add_QString(QString*s,QString* s_sub);
QString* QString_add_char(QString*s,char c);
char* QString_to_cstring_cpy(QString*s);
void QString_printf(QString* s);


/*
                QApplication
*/


QApplication* QApplication_new(int argc, char** argv);
QApplication* QApplication_new_no_param();
int QApplication_exec(QApplication* self);
void QApplication_setActiveWindow(QApplication* self,QWidget *active);
QWidget *QApplication_activeWindow(QApplication *self);


/*
                QWidget
*/

QWidget* QWidget_new(QWidget *parent);
QWidget* QWidget_new_window(QWidget *parent);
QWidget* QWidget_new_sheet(QWidget *parent);
QWidget* QWidget_new_drawer(QWidget *parent);
QWidget* QWidget_new_popup(QWidget *parent);
void QWidget_activate_window(QWidget *self);
void QWidget_adjust_size(QWidget *self);
QWidget *QWidget_focus_widget(QWidget *self);
char QWidget_has_focus(QWidget *self) ;
int QWidget_height(QWidget *self);
char QWidget_is_active_window(QWidget *self);
char QWidget_is_ancestor_of(QWidget *self,const QWidget *child);
char QWidget_is_enabled(QWidget *self);
char QWidget_is_full_screen(QWidget *self);
char QWidget_is_hidden(QWidget *self);
char QWidget_is_visible(QWidget *self);
char QWidget_is_window(QWidget *self);
QLayout *QWidget_layout(QWidget *self);
int  QWidget_layoutDirection(QWidget *self);
QWidget *QWidget_next_in_focus_chain(QWidget *self);
QWidget *QWidget_parent_widget(QWidget *self);
QWidget *QWidget_previous_in_focus_chain(QWidget *self);
void QWidget_scroll(QWidget *self,int dx, int dy);
void QWidget_set_parent(QWidget *self,QWidget *parent);
int QWidget_width(QWidget *self);
char Widget_close(QWidget *self);
void Widget_hide(QWidget *self);
void Widget_lower(QWidget *self);
void Widget_raise(QWidget *self);
void Widget_repaint(QWidget *self);
void Widget_set_disabled(QWidget *self,char disabled_state);
void Widget_set_visible(QWidget *self,char hidden_state);
void Widget_set_style_sheet(QWidget *self,QString* style_sheet);
void Widget_set_window_modified(QWidget *self,char modified_state);
void Widget_set_window_title(QWidget *self,QString* window_title);
void Widget_show(QWidget *self);
void Widget_show_full_screen(QWidget *self);
void Widget_show_maximized(QWidget *self);
void Widget_show_minimized(QWidget *self);
void Widget_show_normal(QWidget *self);
void Widget_update(QWidget *self);
void Widget_free(QWidget ** wid_hld);



/*
         QLayout
*/

//alignement

#define Qt_AlignLeft 0x0001//Aligns with the left edge.
#define Qt_AlignRight 0x0002//Aligns with the right edge.
#define Qt_AlignHCenter 0x0004//Centers horizontally in the available space.
#define Qt_AlignJustify 0x0008//Justifies the text in the available space.
#define Qt_AlignTop 0x0020//Aligns with the top.
#define Qt_AlignBottom 0x0040//Aligns with the bottom.
#define Qt_AlignVCenter 0x0080//Centers vertically in the available space.
#define Qt_AlignBaseline 0x0100//Aligns with the baseline
#define Qt_AlignCenter Qt_AlignVCenter | Qt_AlignHCenter//Centers in both dimensions
#define Qt_AlignAbsolute 0x0010//If  the widget's layout direction is Qt::RightToLeft (instead of Qt::LeftToRight, the default), Qt::AlignLeft refers to the right edge and Qt::AlignRight to the left edge. This is normally the desired behavior. If you want Qt::AlignLeft to always mean "left" and Qt::AlignRight to always mean "right", combine the flag with Qt::AlignAbsolute.
#define Qt_AlignLeading Qt_AlignLeft //Synonym for Qt::AlignLeft.
#define Qt_AlignTrailing Qt_AlignRight //Synonym for Qt::AlignRight.

//directions

#define QBoxLayout_LeftToRight 0//Horizontal from left to right.
#define QBoxLayout_RightToLeft 1//Horizontal from right to left.
#define QBoxLayout_TopToBottom 2//Vertical from top to bottom.
#define QBoxLayout_BottomToTop 3//Vertical from bottom to top.

QBoxLayout* QBoxLayout_new_left_to_right(QWidget* parent);
QBoxLayout* QBoxLayout_new_right_to_left(QWidget* parent);
QBoxLayout* QBoxLayout_new_top_to_bottom(QWidget* parent);
QBoxLayout* QBoxLayout_new_bottom_to_top(QWidget* parent);
void QBoxLayout_free(QBoxLayout** layout_hld);
void QBoxLayout_add_layout(QBoxLayout* self,QLayout* layout);
void QBoxLayout_add_spacing(QBoxLayout* self,int size);
void QBoxLayout_add_stretch(QBoxLayout* self,int stretch);
void QBoxLayout_add_widget
(QBoxLayout *self,QWidget *widget, int stretch,int alignement);
void QBoxLayout_insertLayout
(QBoxLayout *self,int index, QLayout *layout, int stretch);
void QBoxLayout_insert_spacing(QBoxLayout *self,int index, int size);
void QBoxLayout_insert_stretch(QBoxLayout *self,int index, int stretch);
void QBoxLayout_insert_widget
(QBoxLayout *self,int index, QWidget *widget, int stretch , int alignment );
void QBoxLayout_set_direction(QBoxLayout *self,int direction);
void QBoxLayout_set_pacing(QBoxLayout *self,int spacing);
void QBoxLayout_set_stretch(QBoxLayout *self,int index, int stretch);
 int QBoxLayout_count(QBoxLayout *self);
QLayoutItem* QBoxLayout_item_at(QBoxLayout *self,int index);

#endif // QT4C_H
