#pragma once
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
typedef long int TLint;
typedef void* TVar;
typedef void** TPtrHld;
typedef TVar(*TFVarVar)(TVar);
typedef char(*TFCharVarVar)(TVar, TVar);
typedef void(*TFVoidPtrHld)(TPtrHld);
typedef TVar(*TFVarVoid)(void);
typedef void(*TFVoidVarVar)(TVar, TVar);
typedef TLint(*TFLintVar)(TVar);
typedef TVar(*TFVarVarLint)(TVar, TLint);
typedef void(*TFVoidVar)(TVar);
typedef TLint(*TFLintVarVar)(TVar, TVar);


/*
                testing
*/

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void print_red(char* message);
void print_green(char* message);
void print_yellow(char* message);
void print_blue(char* message);
void print_magenta(char* message);
void print_cyan(char* message);
char test(char bool_res, char* message);
char test_v1(char bool_res);
char do_test();
/*
                cstring
*/


char cstring_test();
char* cstring_new(TLint size);
TLint cstring_count(char* str);
char* cstring_clone(char* str_src);
void cstring_free(TPtrHld str_hld);
char cstring_is_equal(char* str1, char* str2);
char* cstring_from_int(int i);
char* cstring_from_double(double f);



/*
                TArray
*/

struct TArray {
    TPtrHld data;
    TLint size;
    TLint count;
};
typedef struct TArray TArray;
#define TARRAY_DEFAULT_SIZE 250
void TArray_test();
TArray* TArray_new();
TArray* TArray_init(TArray* arr);
TArray* TArray_init_v1(TArray* arr,TLint size);
TArray** TArray_clean(TArray** arr_hld, TFVoidPtrHld free_val);
void TArray_free(TPtrHld arr_hld);
TLint TArray_count(TArray* arr);
void TArray_set_count(TArray* arr,TLint count);
TLint TArray_size(TArray* arr);
void TArray_set_size(TArray* arr, TLint size);
TVar TArray_item_at(TArray* arr, TLint index);
TVar TArray_add(TArray* arr, TVar var);

/*
            TString
*/

struct TString {
    char* cstring;
    TLint count;
};
typedef struct TString TString;
void TString_test();
TString* TString_new();
TString* TString_init(TString* str, char* cstring);
TString* TString_init_with_size(TString* str, TLint size, char* cstring);
TString** TString_clean(TString** str);
void TString_destroy(TString** str_hld);
void TString_free(TString** str);
TString* TString_clone(TString* str);
TString* TString_add(TString* str_src, TString* str_sub);
TString* TString_concat_multi(const char* str, ...);


/*
                    TStringList
*/

typedef TArray TStringList;
TLint TStringList_char_count(TStringList* str_l);
TString* TStringList_text(TStringList* str_l);
TString* TStringList_item_at(TStringList* str_l, TLint index);
TString* TStringList_add(TStringList* str_l, TString* str);
TStringList** TStringList_clean(TStringList** str_l);
void TStringList_free(TStringList** str_l);
void TStringList_destroy(TStringList** str_l);


/*
                TVariant
*/

enum TTypes
{
    Int,Double,CString,Var
};
#define NAMELESS 0;
typedef enum TTypes TTypes;
struct  TVariant
{
    TVar value;
    TTypes value_type;
    char* name;

};
typedef struct TVariant TVariant;
TVariant* TVariant_new();
TVariant* TVariant_init(TVariant* var, TVar value, TTypes value_type);
TVariant* TVariant_init_int(TVariant* var, int i);
TVariant* TVariant_init_cstring(TVariant* var, char* str);
TVariant* TVariant_init_double(TVariant* var, double f);
int TVariant_int(TVariant* var);
double TVariant_double(TVariant* var);
TVar TVariant_value(TVariant* var);
char* TVariant_cstring(TVariant* var);
TVariant* TVariant_clean(TVariant** var_hld);
void TVariant_free(TVariant** var_hld);

