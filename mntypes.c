#include "mntypes.h"

/*
                testing
*/


void print_red(char* message)
{
    printf(ANSI_COLOR_RED);
    printf("%s", message);
    printf(ANSI_COLOR_RESET);

}

void print_green(char* message)
{
    printf(ANSI_COLOR_GREEN);
    printf("%s", message);
    printf(ANSI_COLOR_RESET);

}

void print_yellow(char* message)
{
    printf(ANSI_COLOR_YELLOW);
    printf("%s", message);
    printf(ANSI_COLOR_RESET);
}

void print_blue(char* message)
{
    printf(ANSI_COLOR_BLUE);
    printf("%s", message);
    printf(ANSI_COLOR_RESET);
}

void print_magenta(char* message)
{
    printf(ANSI_COLOR_MAGENTA);
    printf("%s", message);
    printf(ANSI_COLOR_RESET);
}

void print_cyan(char* message)
{
    printf(ANSI_COLOR_CYAN);
    printf("%s", message);
    printf(ANSI_COLOR_RESET);
}

char test(char bool_res, char* pass_message)
{
    if (bool_res) {
        print_green(pass_message);

    }
    else {
        printf(ANSI_COLOR_RED "not ");
        print_red(pass_message);

    }
    return bool_res;
}

char test_v1(char bool_res)
{
    return test(bool_res, "working\n");
}

char do_test()
{
    cstring_test();
    TArray_test();
    TString_test();
    TStringList_test();
    TVariant_test();
    TField_test();
    TFieldList_test();
    TSql_test();
    return 1;
}





/*
                cstring
*/

char cstring_test()
{
    print_cyan("\n\n**********\nTESTING CSTRING\n**********\n\n");
    print_yellow("cstring_count>>>\n");
    char res = 1;
    res =  (cstring_count("hello") == 5);
    test_v1(res);
    print_yellow("cstring_new>>>\n");
    char* str=cstring_new(10);
    res =  (cstring_count(str) == 0);
    test_v1(res);
    print_yellow("cstring_clone>>>\n");
    print_yellow("cstring_is_equal>>>\n");
    char* str2 = cstring_clone("hello");
    res = cstring_count(str2) == 5;
    res =res* cstring_is_equal(str2, "hello");
    test_v1(res);
    print_yellow("cstring_free>>>\n");
    cstring_free((TPtrHld)&str2);
    res = str2==0;
    test_v1(res);

    print_yellow("cstring_from_int>>>\n");
    print_yellow("cstring_from_double>>>\n");
    res = cstring_is_equal(cstring_from_int(5), "5");
    res = res * cstring_is_equal(cstring_from_double(5.0), "5.000000");
    test_v1(res);
    return res;
}

char* cstring_new(TLint size)
{
    size++;
    char* str = calloc(size , sizeof(char));
    if (str <= 0) {
        assert(str);
    }
    return str;
}

TLint cstring_count(char* str)
{
    if (str>0) {
        for (TLint i = 0; ; i++)
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
    if (str_src<=0)
    {
        str_src= "";
    }
    char* str = 0;
    TLint count = cstring_count(str_src);
    str = cstring_new(count);
    for (TLint i = 0; i < count; i++)
    {
        str[i] = str_src[i];
    }
    return str;
}

void cstring_free(TPtrHld str_hld)
{
    free((char*)*str_hld);
    *str_hld = 0;
}

char cstring_is_equal(char* str1, char* str2)
{
    if (cstring_count(str1) != cstring_count(str2))
    {
        return 0;
    }
    for (TLint i = 0; ; i++)
    {
        if (str1[i] == 0)
        {
            return 1;
        }
        if (str1[i] != str2[i])
        {
            return 0;
        }
    }
    return 0;
}

char* cstring_from_int(int i)
{
    char* cstring = cstring_new(30);
    snprintf(cstring,30, "%d", i);
    //sprintf_s(cstring,30, "%d", i);
    return cstring;
}

char* cstring_from_double(double f)
{
    char* cstring = cstring_new(40);
    snprintf(cstring,40, "%f", f);
    return cstring;
}

char* cstring_new_empty()
{
    return cstring_new(0);
}

char* cstring_new_from_const(const char* str)
{
    return cstring_clone((char*)str);
}

char cstring_is_great(char* str1, char* str2)
{
    TLint str1_count = cstring_count(str1);
    TLint str2_count = cstring_count(str2);
    for (TLint i = 0; i < str1_count && i<str2_count; i++)
    {
        if (str1[i] < str2[i]) return 0;
        if(str1[i] > str2[i]) return 1;
    }
    return 0;
}

void TEvent_on_event(TEvent* event)
{
    event->on_event(event);
}

/*
            TArray

*/


void TArray_test()
{
    print_cyan("\n\n**********\nTESTING TARRAY\n**********\n\n");
    print_yellow("TArray_new>>>>>\n");
    TArray* arr = TArray_new();
    char res = (arr != 0) && (arr->count == 0) &&
            (arr->data == 0) && (arr->size == 0);
    test_v1(res);
    print_yellow("TArray_init>>>>>\n");
    print_yellow("TArray_size>>>>>\n");
    print_yellow("TArray_count>>>>>\n");
    TArray_init_v1(arr,2);
    if(arr) res = (arr->data != 0) && (TArray_size(arr) == 2) &&
            (TArray_count(arr) == 0);
    print_yellow("TArray_add>>>>>\n");
    TArray_add(arr, cstring_clone("0"));
    TArray_add(arr, cstring_clone("1"));
    if (arr) res = (arr->data != 0) && (TArray_size(arr) == 2) &&
            (TArray_count(arr) == 2);
    TArray_add(arr, cstring_clone("2"));
    if (arr) res = res * (arr->data != 0) && (TArray_size(arr) == 4) &&
            (TArray_count(arr) == 3);
    TArray_add(arr, cstring_clone("3"));
    TArray_add(arr, cstring_clone("4"));
    if (arr) res = res * (arr->data != 0) && (TArray_size(arr) == 8) &&
            (TArray_count(arr) == 5);
    test_v1(res);
    print_yellow("TArray_item_at>>>>>\n");
    res = cstring_is_equal((char*)TArray_item_at(arr, 0), "0");
    res = res * cstring_is_equal((char*)TArray_item_at(arr, 1), "1");
    res = res * cstring_is_equal((char*)TArray_item_at(arr, 2), "2");
    res = res * cstring_is_equal((char*)TArray_item_at(arr, 3), "3");
    res = res * cstring_is_equal((char*)TArray_item_at(arr, 4), "4");
    test_v1(res);

    print_yellow("TArray_resize>>>>>\n");
    TLint l= TArray_size(arr);
    TArray_resize(arr, l * 2);
    res = TArray_size(arr) == l * 2;
    if (arr && arr->data)res = res * (arr->data[arr->size - 1] == 0);
    test_v1(res);
    print_yellow("TArray_set_item_at>>>>>\n");
    TArray_set_item_at(arr, cstring_clone("one"),0);
    if (arr && arr->data)res = cstring_is_equal(arr->data[0], "one");
    test_v1(res);
    print_yellow("TArray_find>>>>>\n");
    l = TArray_find(arr, "4",(TFCharVarVar) cstring_is_equal);
    res = cstring_is_equal(TArray_item_at(arr, l), "4");
    test_v1(res);
    print_yellow("TArray_insert_item_at>>>>>\n");
    TArray_insert_item_at(arr, cstring_clone("insert"), 3);
    res = cstring_is_equal(TArray_item_at(arr, 3), "insert");
    res = res * cstring_is_equal((char*)TArray_item_at(arr, 4), "3");
    res = res * cstring_is_equal((char*)TArray_item_at(arr, 5), "4");
    test_v1(res);
    print_yellow("TArray_remove_item_at>>>>>\n");
    TArray_remove_item_at(arr,3);
    res = cstring_is_equal(TArray_item_at(arr, 3), "3");
    res = res * cstring_is_equal((char*)TArray_item_at(arr, 4), "4");
    if (arr && arr->data)res = res * (arr->data[5] == 0);
    test_v1(res);
    print_yellow("TArray_add_or_replace>>>>>\n");
    char* s4 = TArray_add_or_replace(arr, cstring_clone("4"),(TFCharVarVar)cstring_is_equal);
    res = s4 != TArray_item_at(arr, 4) &&
            cstring_is_equal((char*)TArray_item_at(arr, 4), "4");
    test_v1(res);
    print_yellow("TArray_sort>>>>>\n");
    TArray_add(arr,cstring_clone("9"));
    TArray_add(arr, cstring_clone("8"));
    TArray_add(arr, cstring_clone("7"));
    TArray_add(arr, cstring_clone("6"));
    TArray_add(arr, cstring_clone("5"));
    for (TLint i = 0; i < TArray_count(arr); i++)
    {
        print_magenta((char*)TArray_item_at(arr, i));
        print_magenta("\n");
    }
    TArray_sort(arr,(TFCharVarVar) cstring_is_great);
    print_blue(">>>>>>>>>>>\n");
    for (TLint i = 0; i < TArray_count(arr); i++)
    {
        print_magenta((char*)TArray_item_at(arr, i));
        print_magenta("\n");
    }

    print_yellow("TArray_clean>>>>>\n");
    TArray_clean(&arr, cstring_free);
    res = (arr->data != 0) && (TArray_size(arr) == 16) &&
            (TArray_count(arr) == 0);
    test_v1(res);
    print_yellow("TArray_free>>>>>\n");
    TArray_free((TPtrHld)&arr);
    res = arr == 0;
    test_v1(res);

}

TArray* TArray_new()
{
    TArray* arr = (TArray*)malloc(sizeof(TArray));

    if (arr>0)
    {
        arr->count = 0;
        arr->data = 0;
        arr->size = 0;
    }
    else
    {
        assert(arr);
    }

    return arr;
}

TArray* TArray_init(TArray* arr)
{
    if (arr<=0) {
        arr=TArray_new();
    }
    TArray_init_v1(arr, TARRAY_DEFAULT_SIZE);
    return arr;
}

TArray* TArray_init_v1(TArray* arr, TLint size)
{
    if (arr <= 0) {
        arr = TArray_new();
    }
    arr->data = (TPtrHld)calloc(size, sizeof(TVar));
    if (arr->data > 0) {

        arr->size = size;
    }
    else
    {
        assert(arr->data);
    }
    return arr;

}

TArray* TArray_resize(TArray* arr, TLint size)
{
    assert(TArray_size(arr) < size);
    TPtrHld data= realloc(arr->data, size * sizeof(TVar));
    //(TPtrHld)calloc((size), sizeof(TVar));
    if (data)
    {
        arr->data = data;
        arr->size = size;
        for (TLint i = TArray_count(arr); i < size; i++)
        {
            arr->data[i] = 0;
        }
    }
    else
    {
        assert(data);
    }
    return arr;
}

TArray** TArray_clean(TArray** arr_hld, TFVoidPtrHld free_val)
{
    if (*arr_hld) {
        for (TLint i = 0; i < TArray_count(*arr_hld); i++)
        {
            TVar var = TArray_item_at(*arr_hld, i);
            free_val(&var);
        }
        TArray_set_count(*arr_hld, 0);
    }
    return arr_hld;
}

void TArray_free(TPtrHld arr_hld)
{
    free(((TArray*)(*arr_hld))->data);
    free((TArray*)(*arr_hld));
    *arr_hld = 0;
}

TLint TArray_count(TArray* arr)
{
    if(arr)
        return arr->count;
    return 0;
}

void TArray_set_count(TArray* arr, TLint count)
{
    arr->count = count;
}

TLint TArray_size(TArray* arr)
{
    return arr->size;
}

void TArray_set_size(TArray* arr, TLint size)
{
    arr->size = size;
}

TVar TArray_item_at(TArray* arr, TLint index)
{
    if (arr && arr->data) {
        assert(index < arr->count);
        return arr->data[index];
    }else {
        assert(0);
    }
}

TVar TArray_add(TArray* arr, TVar var)
{
    if (TArray_count(arr) == TArray_size(arr))
    {
        TArray_resize(arr, arr->size * 2);
    }
    if (arr->data)
    {
        arr->data[arr->count] = var;
    }

    arr->count++;
    return var;
}

TArray* TArray_clone(TArray* arr_src, TFVarVar clone_value)
{
    TArray* arr = TArray_init(TArray_new());
    for (TLint i = 0; i < TArray_count(arr_src); i++)
    {
        TArray_add(arr, clone_value(TArray_item_at(arr_src, i)));
    }
    return arr;
}

char TArray_is_equal(TArray* arr1, TArray* arr2, TFCharVarVar is_equal)
{
    if (arr1->count != arr2->count) return 0;
    for (TLint i = 0; i < TArray_count(arr1); i++)
    {
        if (!is_equal(TArray_item_at(arr1, i), TArray_item_at(arr2, i))) return 0;
    }
    return 1;
}

TLint TArray_find(TArray* arr, TVar item, TFCharVarVar is_equal)
{
    for (TLint i = 0; i < TArray_count(arr); i++) {
        if (is_equal(item,TArray_item_at(arr,i))) {
            return i;
        }
    }
    return -1;
}

TVar TArray_set_item_at(TArray* arr, TVar item, TLint index)
{
    assert(index < TArray_count(arr));
    TVar var = TArray_item_at(arr, index);
    arr->data[index] = item;
    return var;
}

void TArray_insert_item_at(TArray* arr, TVar item, TLint index)
{
    assert(index < TArray_count(arr));
    if (arr->count == arr->size) {
        TArray_resize(arr, arr->size * 2);
    }
    for (TLint i = arr->count; i > index; i--)
    {
        arr->data[i] = arr->data[i - 1];
    }
    arr->data[index] = item;
    arr->count++;
}

TVar TArray_remove_item_at(TArray* arr, TLint index)
{
    assert(index < TArray_count(arr));
    TVar var = arr->data[index];
    if (index<arr->count-1) for (TLint i = index; i < arr->count-1; i++)
    {
        arr->data[i] = arr->data[i + 1];
    }
    arr->data[arr->count-1] = 0;
    arr->count--;
    return var;
}

TVar TArray_add_or_replace(TArray* arr, TVar item, TFCharVarVar is_equal)
{
    TVar var = 0;
    TLint index = TArray_find(arr, item, is_equal);
    if (index >= 0) {
        var = arr->data[index];
        arr->data[index] = item;
    }
    else
    {
        TArray_add(arr, item);
    }
    return var;
}

void TArray_sort(TArray* arr, TFCharVarVar is_great)
{
    char switched = 0;
    do
    {
        switched = 0;
        for (TLint i = 0; i < TArray_count(arr)-1; i++)
        {
            if (is_great(TArray_item_at(arr, i), TArray_item_at(arr, i + 1))) {
                TArray_set_item_at(arr,
                                   TArray_set_item_at(arr, TArray_item_at(arr, i + 1), i),
                                   i + 1);
                switched = 1;
            }
        }
    } while (switched);
}


/*
            TLinkedListEntry
*/


TLinkedListEntry* TLinkedListEntry_new()
{
    //TODO: test TLinkedListEntry_new
    TLinkedListEntry* l = (TLinkedListEntry*)malloc(sizeof(TLinkedListEntry));
    if (l>0)
    {
        l->next_entry = 0;
        l->value = 0;
    }
    else
    {
        assert(l);
    }
    return l ;
}

TLinkedListEntry* TLinkedListEntry_init(TLinkedListEntry* l, TVar value, TLinkedListEntry* next_entry)
{
    if (l<=0)
    {
        l = TLinkedListEntry_new();
    }
    l->next_entry = next_entry;
    l->value = value;
    return l;
}


/*
            TLinkedList
*/





TLinkedList* TLinkedList_new()
{
    TLinkedList* list = (TLinkedList*)malloc(sizeof(TLinkedList));
    if (list>0)
    {
        list->last = 0;
        list->root = 0;
    }
    else assert(list);
    return list;
}

TLinkedList* TLinkedList_init(TLinkedList* list, TLinkedListEntry* root)
{
    if (list<=0)
    {
        list = TLinkedList_new();
    }
    list->root = root;
    list->last = root;
    return list;
}

TLinkedListEntry* TLinkedList_add(TLinkedList* list, TLinkedListEntry* entry)
{
    list->last->next_entry = entry;
    list->last = entry;
    return entry;
}

TLinkedList** TLinkedList_clean(TLinkedList** list_hld, TFVoidPtrHld free_val)
{
    TLinkedListEntry* l = (*list_hld)->root;
    for(; l ;l=l->next_entry )
    {
        free_val(&l->value);
    }
    return list_hld;
}

void TLinkedList_free(TLinkedList** list_hld)
{
    TLinkedListEntry* l = (*list_hld)->root;
    TLinkedListEntry* next = 0;
    for (; l; l =next)
    {
        next = l->next_entry;
        free(l);
    }
    free(*list_hld);
    *list_hld = 0;
}

void TLinkedList_destroy(TLinkedList** list_hld, TFVoidPtrHld free_val)
{
    TLinkedListEntry* l = (*list_hld)->root;
    TLinkedListEntry* next = 0;
    for (; l; l = next)
    {
        next = l->next_entry;
        free_val(&l->value);
        free(l);
    }
    free(*list_hld);
    *list_hld = 0;
}

TLinkedListEntry* TLinkedList_find(TLinkedList list, TVar value, TFCharVarVar is_equal)
{
    TLinkedListEntry* l = list.root;
    for (; l;l=l->next_entry )
    {
        if (is_equal(l->value,value))
        {
            return l;
        }
    }
    return l;
}

TLinkedListEntry* TLinkedList_insert_after(TLinkedList* list, TLinkedListEntry* entry_to_ensert, TLinkedListEntry* entry_to_insert_after)
{
    if (list->last==entry_to_insert_after)
    {
        list->last = entry_to_ensert;
    }
    entry_to_ensert->next_entry = entry_to_insert_after->next_entry;
    entry_to_insert_after->next_entry = entry_to_ensert;
    return entry_to_ensert;
}

TLinkedListEntry* TLinkedList_remove(TLinkedList* list, TLinkedListEntry* entry)
{
    TLinkedListEntry* root = list->root;
    if (root==entry)
    {
        list->root = 0;
        list->last = 0;
    }
    do
    {
        if (root->next_entry == entry) {
            root->next_entry = entry->next_entry;
            if (entry->next_entry==0)
            {
                list->last = root;
            }
            break;

        }else
        {
            root = root->next_entry;
        }
    } while (root);
    return entry;
}


/*
            TString
*/

void TString_test()
{
    print_cyan("\n\n**********\nTESTING TString\n**********\n\n");
    print_yellow("TString_init>>>\n");
    print_yellow("TString_new>>>\n");
    TString* str =TString_init(TString_new(),cstring_clone("0"));
    char res = str->cstring != 0 &&
            str->count == 1 &&
            cstring_is_equal(str->cstring, "0");
    test_v1(res);
    print_yellow("TString_clone>>>\n");
    TString* str1= TString_clone(str);
    res = str1 != str && str1->count == 1 &&
            cstring_is_equal(str->cstring, str1->cstring);
    test_v1(res);
    print_yellow("TString_add>>>\n");
    TString s = { 0,0 };
    TString_add(str,TString_init(&s,"1"));

    res = str->count == 2 && cstring_is_equal(str->cstring, "01");
    test_v1(res);
    print_yellow("TString_concat_multi>>>\n");
    TString* strcon= TString_concat_multi("%d%f%s%m", 1, 1.0, "22", str);
    res = cstring_is_equal(strcon->cstring, "11.0000002201");
    test_v1(res);

    print_yellow("TString_clean>>>\n");
    print_yellow("TString_free>>>\n");
    TString_clean(&strcon);
    res = strcon->count == 0 && strcon->cstring == 0;
    TString_free(&strcon);
    res =res* (strcon == 0);
    test_v1(res);
    print_yellow("TString_clone_cstring>>>\n");
    TString* ss = TString_from_cstring_cpy("hello world\n");
    print_magenta(ss->cstring);
    res = cstring_is_equal(ss->cstring, "hello world\n");
    test_v1(res);
    print_yellow("TString_fill_range>>>\n");
    TString_fill_range(ss,' ', 0, 4);
    print_magenta(ss->cstring);
    res = cstring_is_equal(ss->cstring, "      world\n");
    test_v1(res);
    TString_fill(ss, '.');
    print_magenta(ss->cstring);
    res = cstring_is_equal(ss->cstring, "............");
    printf("\n");
    test_v1(res);
    print_yellow("TString_replace>>>\n");
    TArray* trash=TArray_init(0);
    TString_replace(ss,TArray_add(trash,TString_from_cstring_cpy("hello")), 0);
    TString_replace(ss, TArray_add(trash,TString_from_cstring_cpy("\n")), 11);
    print_magenta(ss->cstring);
    res = TString_is_equal_cstring(ss, "hello......\n");
    TString_destroy(&str1);
    TArray_clean(&trash,(TFVoidPtrHld)TString_destroy);
    TArray_free((TPtrHld)&trash);
    printf("\n");
    test_v1(res);

}

TString* TString_new()
{
    TString* str = (TString*)malloc(sizeof(TString));

    if (str>0) {
        str->count = 0;
        //str->size = 0;
        str->cstring = 0;
    }else assert(str);
    return str;
}

TString* TString_init(TString* str, char* cstring)
{
    if (cstring<=0)
    {
        cstring = cstring_new_from_const("");
    }
    return TString_init_with_size(str, cstring_count(cstring), cstring);
}

TString* TString_init_cstring_cpy(TString* str, char* cstring)
{
    return TString_init( str, cstring_clone(cstring));
}

TString* TString_init_with_size(TString* str, TLint size, char* cstring) {
    if (str<=0)
    {
        str = TString_new();
    }
    str->count = size;
    str->cstring = cstring;
    return str;
}

TString* TString_from_cstring(char* cstring)
{
    return TString_init(TString_new(),cstring);
}

TString* TString_from_cstring_cpy(char* cstring)
{
    return TString_from_cstring(cstring_clone(cstring));
}

TString** TString_clean(TString** str)
{

    if (*str) {
        free((*str)->cstring);
        (*str)->cstring = 0;
        (*str)->count = 0;
    }
    return str;
}

void TString_destroy(TString** str_hld)
{
    TString_free(TString_clean(str_hld));
}

void TString_free(TString** str)
{
    free(*str);
    *str = 0;
}

TString* TString_clone(TString* str)
{
    if (str && str->cstring) {
        TLint size = (str->count)+1;
        char* cstring = (char*)malloc(sizeof(char) * size);
        TString* res = 0;
        if (cstring>0) {
            for (TLint i = 0; i < str->count; i++)
            {
                cstring[i] = str->cstring[i];
            }
            cstring[str->count] = 0;
            res = TString_new();
            res->count = str->count;
            //res->size = str->size;
            res->cstring = cstring;
        }
        else assert(cstring);
        return res;
    }
    return 0;

}

char TString_is_equal(TString* str1, TString* str2)
{

    if (str1->count != str2->count) return 0;
    for (TLint i = 0; i < str1->count; i++)
    {
        if (str1->cstring[i] != str2->cstring[i]) return 0;
    }
    return 1;
}

char TString_is_equal_cstring(TString* str1, char* cstring)
{
    TLint count = cstring_count(cstring);
    if (str1->count != count) return 0;
    for (TLint i = 0; i < str1->count; i++)
    {
        if (str1->cstring[i] != cstring[i]) return 0;
    }
    return 1;
}

TString* TString_add(TString* str_src, TString* str_sub)
{
    TLint count = str_src->count + str_sub->count;
    TLint size = count + 1;
    char* cstring = (char*)calloc((size), sizeof(char));
    if (cstring>0) {
        for (TLint i = 0; i < str_src->count; i++)
        {
            cstring[i] = str_src->cstring[i];

        }
        for (TLint i = str_src->count; i < count; i++)
        {
            cstring[i] = str_sub->cstring[i - str_src->count];
        }
        free(str_src->cstring);
        str_src->cstring = cstring;
        str_src->count = count;
        //str_src->size = count;
    }
    else assert(cstring);
    return str_src;

}


TString* TString_concat_multi(const char* str, ...) {
    va_list ap;
    int i = 0;
    int j = 0;
    va_start(ap, str);
    char str1[250];
    TArray* list = TArray_init(TArray_new());
    while (str[i] != '\0') {
        if (str[i] == '%') {
            str1[j] = 0;
            TArray_add(list, TString_init(TString_new(), cstring_clone(str1)));
            i++;
            if (str[i] == 's') {
                TArray_add(list, TString_init(TString_new(),
                                              cstring_clone(va_arg(ap, char*))));
            }
            else if (str[i] == 'd') {
                TArray_add(list, TString_init(TString_new(),
                                              cstring_from_int(va_arg(ap, int))));
            }
            else if (str[i] == 'm') {//for TString
                TString* ss = va_arg(ap, TString*);
                TArray_add(list, TString_clone(ss));
            }
            else if (str[i] == 'f') {//for TString
                TArray_add(list, TString_init(TString_new(),
                                              cstring_from_double(va_arg(ap, double))));
            }
            j = 0;
            i++;
            continue;
        }
        str1[j] = str[i];
        j++;
        i++;
    }
    va_end(ap);
    str1[j] = 0;
    TArray_add(list, TString_init(TString_new(),cstring_clone(str1)));
    TString* s = TStringList_text(list,"");
    TArray_free((TPtrHld)TArray_clean((&list),(TFVoidPtrHld) TString_destroy));
    return  s;
}

TString* TString_fill(TString* str, char c)
{
    TLint end_ind = str->count - 1;
    return TString_fill_range(str,c,0,end_ind);
}

TString* TString_replace(TString* str, TString* sub_str, TLint index)
{
    assert(index < str->count);
    for (TLint i = index; (i<str->count)&&(i < (index+sub_str->count)); i++)
    {
        str->cstring[i] = sub_str->cstring[i - index];
    }
    return str;
}

char TString_is_empty(TString* str)
{
    return str->count==0;
}

TString* TString_from_int(int n)
{
    char* s = cstring_new(25);
    snprintf(s, 25, "%d", n);
    return TString_init(TString_new(), s);
}

TString* TString_from_double(double f)
{
    char* s = cstring_new(50);
    snprintf(s, 50, "%f", f);
    return TString_init(TString_new(), s);
}

TString* TString_fill_range(TString* str, char c, TLint start_ind, TLint end_ind)
{
    assert(start_ind >= 0 && start_ind < str->count && end_ind < str->count);
    for (TLint i = start_ind; i <= end_ind; i++)
    {
        str->cstring[i] = c;
    }
    return str;
}



/*
        TStringList
*/


void TStringList_test()
{
    print_cyan("\n\n**********\nTESTING TSTRINGLIST\n**********\n\n");
    print_yellow("TStringList_init>>>\n");
    print_yellow("TStringList_new>>>\n");
    print_yellow("TStringList_add>>>\n");
    print_yellow("TStringList_item_at>>>\n");
    TStringList* strs = TStringList_init(TStringList_new());
    TString* s1 = TString_from_cstring_cpy("hello ");
    TString* s2 = TString_from_cstring_cpy("world ");
    TString* s3 = TString_from_cstring_cpy("!\n");
    TStringList_add(strs, s1);
    TStringList_add(strs, s2);
    TStringList_add(strs, s3);
    char res = TString_is_equal_cstring(TStringList_item_at(strs, 0), "hello ");
    res = res * TString_is_equal_cstring(TStringList_item_at(strs, 1), "world ");
    res = res * TString_is_equal_cstring(TStringList_item_at(strs, 2), "!\n");
    test_v1(res);
    print_yellow("TStringList_char_count>>>\n");
    res = TStringList_char_count(strs) == 14;
    test_v1(res);
    print_yellow("TStringList_text>>>\n");
    TString* s = TStringList_text(strs,"/toto/\n");
    print_magenta(s->cstring);
    res = TString_is_equal_cstring(s, "hello ""/toto/\n""world ""/toto/\n""!\n""/toto/\n");
    test_v1(res);
    TStringList_clean(&strs);
    TStringList_free(&strs);


}

TStringList* TStringList_new()
{
    return TArray_new();
}

TStringList* TStringList_init(TStringList* strs)
{
    return TArray_init(strs);
}

TLint TStringList_char_count(TStringList* str_l) {
    TLint count = 0;
    for (TLint i = 0; i < TArray_count(str_l); i++)
    {
        count = count + ((TString*)TArray_item_at(str_l, i))->count;
    }
    return count;
}

TString* TStringList_text(TStringList* str_l, char* str_end)
{

    TLint str_end_count = cstring_count(str_end);
    TLint count = TStringList_char_count(str_l)+(str_end_count*TArray_count(str_l));
    char* cstring = cstring_new(count);
    TLint char_count = 0;
    for (TLint i = 0; i < TArray_count(str_l); i++)
    {
        TString* s = TStringList_item_at(str_l, i);
        for (TLint j = 0; j < s->count; j++)
        {
            cstring[char_count] = s->cstring[j];
            char_count++;

        }
        for (TLint j = 0; j < str_end_count;j++) {
            cstring[char_count] = str_end[j];
            char_count++;
        }
    }
    TString* res = TString_new();
    res->cstring = cstring;
    res->count = char_count;
    //res->size = char_count;
    return res;
}

TString* TStringList_item_at(TStringList* str_l, TLint index)
{
    assert(index < TArray_count(str_l));
    return (TString*)str_l->data[index];
}

TString* TStringList_add(TStringList* str_l, TString* str)
{
    TArray_add(str_l, str);
    return str;
}

TStringList** TStringList_clean(TStringList** str_l)
{
    if (*str_l) {
        TArray_clean(str_l, (TFVoidPtrHld)TString_destroy);
    }
    return str_l;
}

void TStringList_free(TStringList** str_l)
{
    TArray_free((TPtrHld)str_l);
}

void TStringList_destroy(TStringList** str_l)
{
    TStringList_free(TStringList_clean(str_l));
}


/*
                TVariant
*/



void TVariant_test()
{
    print_cyan("\n\n**********\nTESTING TVARIANT\n**********\n\n");
    print_yellow("TVariant_new>>>\n");
    print_yellow("TVariant_init_int>>>\n");
    print_yellow("TVariant_init>>>\n");
    TVariant* var = TVariant_new();
    TVariant_init_int(var, 5);
    char res = TVariant_int(var) == 5 &&
            var->value_type == Int;
    test_v1(res);
    print_yellow("TVariant_clean>>>\n");
    TVariant_clean(&var);
    res = var->value == 0;
    test_v1(res);
    print_yellow("TVariant_init_double>>>\n");
    TVariant_init_double(var, 1.56);
    if (var->value)
        res = TVariant_double(var) == 1.56 &&
                var->value_type == Double;
    test_v1(res);
    TVariant_clean(&var);
    print_yellow("TVariant_init_cstring>>>\n");
    TVariant_init_cstring(var, cstring_clone("hi"));
    if (var->value)
        res = cstring_is_equal(TVariant_cstring(var),"hi") &&
                var->value_type ==  CString;
    test_v1(res);
    TVariant_clean(&var);
    TVariant_free(&var);
    print_yellow("TVariant_is_equal>>>\n");
    TArray* trash=TArray_init(0);
    res = TVariant_is_equal(TArray_add(trash,TVariant_create_cstring(cstring_clone("me"))),
                            TArray_add(trash,TVariant_create_cstring(cstring_clone("me"))));
    res=res* TVariant_is_equal(TArray_add(trash,TVariant_create_int(5)),
                               TArray_add(trash,TVariant_create_int(5)));
    res = res * TVariant_is_equal(TArray_add(trash,TVariant_create_double(5.2)),
                                  TArray_add(trash,TVariant_create_double(5.2)));
    res = res * !TVariant_is_equal(TArray_add(trash,TVariant_create_double(5.4)),
                                   TArray_add(trash,TVariant_create_int(5)));
    test_v1(res);
    print_yellow("TVariant_clone>>>\n");
    res = TVariant_is_equal(TArray_add(trash,TVariant_create_cstring(cstring_clone("me"))),
                            TArray_add(trash,TVariant_clone(TVariant_create_cstring(cstring_clone("me")))));
    res = res * TVariant_is_equal(TArray_add(trash,TVariant_create_int(5)),
                                  TArray_add(trash,TVariant_clone(TVariant_create_int(5))));
    res = res * TVariant_is_equal(TArray_add(trash,TVariant_create_double(5.2)),
                                  TArray_add(trash,TVariant_clone(TVariant_create_double(5.2))));
    res = res * !TVariant_is_equal(TArray_add(trash,TVariant_create_double(5.4)),
                                   TArray_add(trash,TVariant_clone(TVariant_create_int(5))));
    test_v1(res);
    TArray_clean(&trash,(TFVoidPtrHld)TVariant_destroy);
    TArray_free((TPtrHld)&trash);

}

TVariant* TVariant_new()
{
    TVariant* var = (TVariant*)malloc(sizeof(TVariant));
    if (var>0) {
        var->value = 0;
        var->value_type = -1;
    }
    else assert(var);
    return var;
}


TVariant* TVariant_init(TVariant* var, TVar value,TTypes value_type)
{
    if (var<=0)
    {
        var = TVariant_new();
    }
    var->value = value;
    var->value_type = value_type;
    return var;
}

TVariant* TVariant_init_int(TVariant* var, int i)
{
    int* n = (int*)malloc(sizeof(int));
    if (n > 0) *n = i; else assert(n);
    TVariant_init(var, n, Int);
    return var;
}

TVariant* TVariant_init_cstring(TVariant* var, char* str)
{
    TVariant_init(var, str, CString);
    return var;
}

TVariant* TVariant_init_double(TVariant* var, double f)
{
    double* d = (double*)malloc(sizeof(double));
    if (d > 0) { *d = f; }
    else assert(d);
    TVariant_init(var, d, Double);
    return var;
}

TVariant* TVariant_create_cstring(char* cstring)
{
    return TVariant_init_cstring(TVariant_new(),cstring);
}

TVariant* TVariant_create_int( int n)
{
    return TVariant_init_int(TVariant_new(),n);
}

TVariant* TVariant_create_double( double f)
{
    return TVariant_init_double(TVariant_new(),f);
}



int TVariant_int(TVariant* var)
{
    assert(var->value_type == Int);
    return *((int*)(var->value));
}

double TVariant_double(TVariant* var)
{
    assert(var->value_type == Double);
    return *((double*)(var->value));;
}

TVar TVariant_value(TVariant* var)
{
    return var->value;
}

char* TVariant_cstring(TVariant* var)
{
    assert(var->value_type == CString);
    return (char*)var->value;
}

TVariant** TVariant_clean(TVariant** var_hld)
{
    if (*var_hld) {
        free((*var_hld)->value);
        (*var_hld)->value = 0;
    }
    return var_hld;
}

void TVariant_free(TVariant** var_hld)
{
    free(*var_hld);
    *var_hld = 0;
}

void TVariant_destroy(TVariant** var_hld)
{
    TVariant_free(TVariant_clean(var_hld));
}

char TVariant_is_equal(TVariant* var1, TVariant* var2)
{
    if (TVariant_type(var1) != TVariant_type(var2)) return 0;
    if (TVariant_type(var1)==CString)
    {
        return cstring_is_equal(TVariant_cstring(var1),
                                TVariant_cstring(var2));
    }
    else if (TVariant_type(var1)==Int)
    {
        return TVariant_int(var1) == TVariant_int(var2);
    }else if(TVariant_type(var1) == Double)
    {
        return TVariant_double(var1) == TVariant_double(var2);
    }
    return 0;
}

TTypes TVariant_type(TVariant* var)
{
    return var->value_type;
}

TVariant* TVariant_clone(TVariant* var)
{
    TVariant* v = TVariant_new();
    switch (TVariant_type(var))
    {
    case Int:
        TVariant_init_int(v, TVariant_int(var));
        break;
    case Double:
        TVariant_init_double(v, TVariant_double(var));
        break;
    case CString:
        TVariant_init_cstring(v, TVariant_cstring(var));
        break;
    default:
        assert(0);
        break;
    }
    return v;
}


/*
                TField
*/


void TField_test()
{
    print_cyan("\n\n**********\nTESTING TFIELD\n**********\n\n");
    print_yellow("TField_new>>>\n");
    TField* fld = TField_new();
    char res = fld->name == 0 && fld->data == 0 && fld->is_generated == 0;
    test_v1(res);
    print_yellow("TField_init_int>>>\n");
    TArray* trash = TArray_init(0);
    fld=TArray_add(trash, TField_create_int( "age", 1));
    res= TVariant_int(fld->data) == 1 &&
            cstring_is_equal("age",TField_name(fld));
    test_v1(res);
    print_yellow("TField_init_double>>>\n");
    fld=TArray_add(trash,TField_create_double( "salary", 1.2));
    res = TVariant_double(fld->data) == 1.2 &&
            cstring_is_equal("salary", TField_name(fld));
    test_v1(res);
    print_yellow("TField_init_cstring>>>\n");
    fld=TArray_add(trash,TField_create_cstring( "salary", cstring_clone("me")));
    if(fld->data) res = cstring_is_equal("me", (char*)fld->data->value) &&
            cstring_is_equal("salary", TField_name(fld));
    test_v1(res);
    print_yellow("TField_is_equal>>>\n");
    res = TField_is_equal(TArray_add(trash,TField_create_int("me", 1)),
                          TArray_add(trash,TField_create_int("me", 1)));
    test_v1(res);
    print_yellow("TField_clone>>>\n");
    res = TField_is_equal(TArray_add(trash,TField_create_int("me", 1)),
                          TArray_add(trash,TField_clone(TField_create_int("me", 1))));
    test_v1(res);
    TArray_clean(&trash,(TFVoidPtrHld)TField_destroy);
    TArray_free((TPtrHld)&trash);
}

TField* TField_new()
{
    TField* fld = (TField*)malloc(sizeof(TField));
    if (fld) {
        fld->name = 0;
        fld->data = 0;
        fld->is_generated = 0;
        fld->order = 0;
    }
    else assert(fld);
    return fld;
}

TField* TField_init(TField* fld,
                    TVariant* var,
                    char is_generated,
                    char* name)
{
    if (fld<=0)
    {
        fld = TField_new();
    }
    fld->data = var;
    fld->is_generated = is_generated;
    TField_set_name(fld, name);
    return fld;
}

TField* TField_init_int(TField* fld, char* name, int val)
{
    TField_init(fld,
                TVariant_init_int(TVariant_new(), val ),
                1,
                name);
    return fld;
}

TField* TField_init_double(TField* fld, char* name, double val)
{
    TField_init(fld, TVariant_init_double(TVariant_new(), val), 1,name);
    return fld;
}

TField* TField_init_cstring(TField* fld, char* name, char* val)
{
    TField_init(fld, TVariant_init_cstring(TVariant_new(), val), 1,name);
    return fld;
}

TField* TField_create_int(char* name, int val)
{
    return TField_init_int(TField_new(),name,val);
}

TField* TField_create_double(char* name, double val)
{
    return  TField_init_double(TField_new(), name, val);;
}

TField* TField_create_cstring(char* name, char* val)
{
    return TField_init_cstring(TField_new(), name, val);
}

TField** TField_clean(TField** fld_hld){

    TVariant_destroy(&((*fld_hld)->data));
    return fld_hld;
}
void TField_free(TField** fld_hld){
    free((*fld_hld)->name);
    free((*fld_hld));
    (*fld_hld)=0;

}
void TField_destroy(TField** fld_hld){
    TField_free(TField_clean(fld_hld));

}

TVariant* TField_data(TField* fld)
{
    return fld->data;
}

void TField_set_name(TField* fld, char* name)
{
    if (fld->name) free(fld->name);
    fld->name = cstring_clone(name);
}

char* TField_name(TField* fld)
{
    return fld->name;
}

char TField_isgenerated(TField* fld)
{
    return fld->is_generated;
}

void TField_set_generated(TField* fld, char is_generated)
{
    fld->is_generated = is_generated;
}

char TField_is_equal(TField* fld1, TField* fld2)
{
    return cstring_is_equal(TField_name(fld1), TField_name(fld2)) &&
            TVariant_is_equal(fld1->data, fld2->data);
}

TField* TField_clone(TField* fld)
{
    TField* f= TField_init(TField_new(),
                           TVariant_clone(fld->data),
                           fld->is_generated,fld->name);
    TField_set_order(f, TFielld_order(fld));
    return f;
}

void TField_set_order(TField* fld, char order)
{
    fld->order = order;
}

char TFielld_order(TField* fld)
{
    return fld->order;
}

char TField_order_is_greater(TField* fld1, TField* fld2)
{
    return TFielld_order(fld1)>TFielld_order(fld2);
}


/*
                    TFieldList
*/


void TFieldList_test()
{
    print_cyan("\n\n**********\nTESTING TFieldList\n**********\n\n");
    print_yellow("TFieldList_new>>>\n");
    TFieldList* flds = TFieldList_new();
    char res = flds->fields == 0 &&
            flds->is_changed == -1 &&
            flds->is_deleted == -1 &&
            flds->is_new == -1;
    test_v1(res);
    print_yellow("TFieldList_init>>>\n");
    TFieldList_init(flds);
    res = flds->fields != 0;
    test_v1(res);
    print_yellow("TFieldList_add>>>\n");
    print_yellow("TFieldList_item_at>>>\n");
    TField* fld1 = TField_create_int("age", 45);
    TField* fld2 = TField_create_cstring("name", "nour");
    TField* fld3 = TField_create_double("salary", 200.5);
    TFieldList_add(flds, TField_clone(fld1));
    TFieldList_add(flds, TField_clone(fld2));
    TFieldList_add(flds, TField_clone(fld3));
    res = TField_is_equal(TFieldList_item_at(flds, 0), fld1) &&
            TField_is_equal(TFieldList_item_at(flds, 1), fld2) &&
            TField_is_equal(TFieldList_item_at(flds, 2), fld3);
    test_v1(res);
    print_yellow("TFieldList_item_with_name>>>\n");
    res = TField_is_equal(TFieldList_item_with_name(flds, "age"), fld1) &&
            TField_is_equal(TFieldList_item_with_name(flds, "name"), fld2) &&
            TField_is_equal(TFieldList_item_with_name(flds, "salary"), fld3);
    test_v1(res);
    print_yellow("TFieldList_clone>>>\n");
    print_yellow("TFieldList_is_equal>>>\n");
    TFieldList* flds1 = TFieldList_clone(flds);
    res = TFieldList_is_equal(flds, flds1);
    test_v1(res);

}

TFieldList* TFieldList_new()
{
    TFieldList* flds = (TFieldList*)malloc(sizeof(TFieldList));
    if (flds) {
        flds->fields = 0;
        flds->is_changed = -1;
        flds->is_deleted = -1;
        flds->is_new = -1;
    }
    else assert(flds);
    return flds;
}

TFieldList* TFieldList_init(TFieldList* flds)
{
    flds->fields = TArray_init(TArray_new());
    return flds;
}

void TFieldList_set_changed(TFieldList* flds, char is_changed)
{
    flds->is_changed=is_changed;
}

char TFieldList_is_changed(TFieldList* flds)
{
    return flds->is_changed;
}

void TFieldList_set_deleted(TFieldList* flds, char is_deleted)
{
    flds->is_deleted = is_deleted;
}

char TFieldList_is_deleted(TFieldList* flds)
{
    return flds->is_deleted;
}

void TFieldList_set_new(TFieldList* flds, char is_new)
{
    flds->is_new = is_new;
}

char TFieldList_is_new(TFieldList* flds)
{
    return flds->is_new;
}

TField* TFieldList_add(TFieldList* flds, TField* fld)
{
    TArray_add(flds->fields, fld);
    TField_set_order(fld, (char)TArray_count(flds->fields) - 1);
    return fld;
}

TField* TFieldList_item_at(TFieldList* flds, TLint index)
{
    return (TField*)TArray_item_at(flds->fields,index);
}

TField* TFieldList_item_with_name(TFieldList* flds, char* name)
{
    for (TLint i = 0; i < TArray_count(flds->fields); i++)
    {
        if (cstring_is_equal(TField_name(TFieldList_item_at(flds, i)),name)) {
            return TFieldList_item_at(flds, i);
        }
    }
    return 0;
}

TFieldList* TFieldList_clone(TFieldList* flds)
{
    TFieldList* f = TFieldList_new();
    f->is_changed = flds->is_changed;
    f->is_deleted = flds->is_deleted;
    f->is_new = flds->is_new;
    f->fields = TArray_clone(flds->fields,(TFVarVar)TField_clone);
    return f;
}

char TFieldList_is_equal(TFieldList* flds1, TFieldList* flds2)
{
    return TArray_is_equal(flds1->fields,flds2->fields,
                           (TFCharVarVar)TField_is_equal);
}

void TFieldList_sort_by_order(TFieldList* flds)
{
    TArray_sort(flds->fields,(TFCharVarVar) TField_order_is_greater);
}



/*
                   TSQL
*/



void TSql_test()
{
    print_cyan("\n\n**********\nTESTING TSQL\n**********\n\n");
    print_yellow("TSql_new>>>\n");
    TSql* sql = TSql_new();
    char res = sql->fields == 0 &&
            sql->filters == 0 &&
            sql->limit == 0 &&
            sql->offset == 0 &&
            sql->sql == 0 &&
            sql->sql_order_by == 0 &&
            sql->sql_rec_count == 0 &&
            sql->sql_where == 0 &&
            sql->table_name == 0;
    test_v1(res);
    print_yellow("TSql_init>>>\n");
    TSql_init(sql, TString_init(0, cstring_clone("client")),
              TString_init(0,cstring_clone("name,age,salary")),
              TString_init(0, cstring_clone("client='me'")),
              TString_init(0, cstring_clone("name")), 10, 0);
    if(sql->fields) res = cstring_is_equal(sql->fields->cstring, "name,age,salary") &&
            sql->filters != 0 &&
            sql->limit == 10 &&
            sql->offset == 0 &&
            sql->sql == 0 &&
            cstring_is_equal(sql->sql_order_by->cstring, "name") &&
            sql->sql_rec_count == 0 &&
            cstring_is_equal(sql->sql_where->cstring, "client='me'") &&
            cstring_is_equal(sql->table_name->cstring, "client");
    test_v1(res);
    print_yellow("TSql_make_sql>>>\n");
    TString* str = TSql_make_sql(sql);
    res = TString_is_equal_cstring(str, " SELECT name,age,salary FROM client  WHERE client='me'  ORDER BY name  LIMIT 10 OFFSET 0 ");
    test_v1(res);
    print_yellow("TSql_add_filter>>>\n");
    TSql_add_filter(sql, AND, cstring_clone("age=40"));
    TSql_add_filter(sql, OR, cstring_clone("salary=40"));
    str = TSql_make_sql(sql);
    res = TString_is_equal_cstring(str, " SELECT name,age,salary FROM client  WHERE client='me'  AND age=40 OR salary=40 ORDER BY name  LIMIT 10 OFFSET 0 ");
    test_v1(res);
    print_yellow("TSql_clone>>>\n");
    print_yellow("TSql_is_equal>>>\n");
    TSql* sql2 = TSql_clone(sql);
    res = TSql_is_equal(sql, sql2);
    test_v1(res);
    print_yellow("TSql_destroy>>>\n");
    TSql_destroy(&sql2);
    TSql_destroy(&sql);
    test_v1(1);
}

TSql* TSql_new()
{
    TSql* sql = (TSql*)malloc(sizeof(TSql));
    if (sql)
    {
        sql->fields = 0;
        sql->filters = 0;
        sql->limit = 0;
        sql->offset = 0;
        sql->sql = 0;
        sql->sql_order_by = 0;
        sql->sql_rec_count = 0;
        sql->sql_where = 0;
        sql->table_name = 0;
    }
    else assert(sql);
    return sql;
}

TSql* TSql_init(TSql* sql,
                TString* table_name,
                TString* fields,
                TString* w_where,
                TString* w_order_by,
                int limit,
                int offset)
{
    if (sql<=0)
    {
        sql = TSql_new();
    }
    sql->fields = fields;
    sql->limit = limit;
    sql->offset = offset;
    //sql->sql = sql;
    sql->sql_order_by = w_order_by;
    sql->sql_where = w_where;
    sql->table_name = table_name;
    sql->filters = TArray_init(TArray_new());
    return sql;
}

TSql* TSql_init_with_cstring(TSql* sql, char* table_name, char* fields, char* w_where, char* w_order_by, int limit, int offset)
{
    return TSql_init(sql,
                     TString_from_cstring(table_name),
                     TString_from_cstring(fields),
                     TString_from_cstring(w_where),
                     TString_from_cstring(w_order_by),
                     limit,
                     offset);
}

TSql* TSql_init_with_cstring_cpy(TSql* sql, char* table_name, char* fields, char* w_where, char* w_order_by, int limit, int offset)
{
    return TSql_init_with_cstring(sql,
                                  cstring_clone(table_name),
                                  cstring_clone(fields),
                                  cstring_clone(w_where),
                                  cstring_clone(w_order_by),
                                  limit,
                                  offset);
}

TSql** TSql_clean(TSql** msql_hld)
{
    if (*msql_hld) {
        TString_destroy(&((*msql_hld)->sql));
    }
    return msql_hld;
}

void TSql_free(TSql** msql_hld)
{
    TString_destroy(&(*msql_hld)->fields);
    TString_destroy(&(*msql_hld)->sql_order_by);
    TString_destroy(&(*msql_hld)->sql_where);
    TString_destroy(&(*msql_hld)->table_name);
    TString_destroy(&(*msql_hld)->sql_rec_count);
    TArray_free((TPtrHld)TArray_clean(&(*msql_hld)->filters,
                                      (TFVoidPtrHld) TString_destroy));
    free(*msql_hld);
    *msql_hld = 0;
}

void TSql_destroy(TSql** msql_hld)
{
    TSql_free(TSql_clean(msql_hld));
}

TSql* TSql_clone(TSql* msql)
{
    TSql* s = TSql_new();
    s->filters = TArray_clone(msql->filters, (TFVarVar)TString_clone);
    s->limit = msql->limit;
    s->offset = msql->offset;
    s->sql = TString_clone(msql->sql);
    s->sql_order_by = TString_clone((msql->sql_order_by));
    s->table_name = TString_clone(msql->table_name);
    s->fields = TString_clone(msql->fields);
    s->sql_where = TString_clone(msql->sql_where);
    return s;
}

char TSql_is_equal(TSql* msql1, TSql* msql2)
{
    return msql1->limit == msql2->limit &&
            msql1->offset == msql2->offset &&
            (TArray_is_equal(msql1->filters, msql2->filters, (TFCharVarVar)TString_is_equal)) &&
            (TString_is_equal(msql1->sql, msql2->sql)) &&
            TString_is_equal(msql1->sql_order_by, msql2->sql_order_by) &&
            TString_is_equal(msql1->table_name, msql2->table_name) &&
            TString_is_equal(msql1->fields, msql2->fields) &&
            TString_is_equal(msql1->sql_where, msql2->sql_where);
}

TString* TSql_make_sql(TSql* msql)
{

    TArray* arr = 0;
    if (msql->fields == 0 || msql->table_name == 0) {
        return 0;
    }
    TStringList* trash=TArray_init(TArray_new());
    TString* select_Sql = TStringList_add(trash,
                                          TString_concat_multi(" SELECT %m FROM %m ",
                                                               msql->fields,
                                                               msql->table_name));
    TString* where_sql = 0;
    if (msql->sql_where != 0 && (msql->sql_where->count!=0)) {
        where_sql = TStringList_add(trash,
                                    TString_concat_multi(" WHERE %m ", msql->sql_where));
    }
    else {
        where_sql = TStringList_add(trash, TString_init(TString_new(), cstring_clone("")));
    }
    TString* order_by = 0;
    if (msql->sql_order_by != 0 && (msql->sql_order_by->count!=0)) {
        order_by = TStringList_add(trash,
                                   TString_concat_multi(" ORDER BY %m ", msql->sql_order_by));
    }
    else {
        order_by = TStringList_add(trash, TString_init(TString_new(), cstring_clone("")));
    }
    TString* limit_sql = 0;
    if (msql->limit != 0) {
        limit_sql = TStringList_add(trash, TString_concat_multi(
                                        " LIMIT %d OFFSET %d ",
                                        msql->limit,
                                        msql->offset));
    }
    else {
        limit_sql = TStringList_add(trash, TString_init(TString_new(), cstring_clone("")));
    }

    TString* filters = 0;
    if (TArray_count(msql->filters) != 0) {
        arr = TArray_clone(msql->filters, (TFVarVar)TString_clone);
        if (!where_sql || (where_sql->count==0)) {
            TString_free(TArray_item_at(arr, 0));
            arr->data[0]= TString_init(TString_new(), cstring_clone(" WHERE "));
        }
        filters = TStringList_add(trash, TStringList_text(arr,""));
    }
    else {
        filters = TStringList_add(trash, TString_init(TString_new(), cstring_clone("")));
    }
    if (msql->sql) {
        TString_free(&msql->sql);
    }
    if (msql->sql) TString_free(&msql->sql);
    msql->sql = TString_concat_multi("%m%m%m%m%m", select_Sql,
                                     where_sql, filters, order_by, limit_sql);
    if (msql->sql_rec_count) TString_destroy(&msql->sql_rec_count);
    msql->sql_rec_count = TString_concat_multi("SELECT COUNT() as count from %m %m",
                                               msql->table_name, where_sql);
    if (arr) {
        TArray_clean(&arr, (TFVoidPtrHld)TString_free);
        TArray_free((TPtrHld)&arr);
    }
    TStringList_destroy(&trash);

    return msql->sql;
}

void TSql_add_filter(TSql* msql, enum logic_op log_oper,  char* filter)
{
    if (log_oper == AND) {
        TArray_add(msql->filters, TString_init(TString_new(),cstring_clone(" AND ")));
    }
    else if (log_oper == OR) {
        TArray_add(msql->filters, TString_init(TString_new(), cstring_clone(" OR ")));
    }
    else {
        return;
    }
    TArray_add(msql->filters, TString_init(TString_new(), filter));
}


void TSql_add_filter_cpy(TSql* msql, logic_op log_oper, char* filter)
{
    TSql_add_filter(msql, log_oper, cstring_clone(filter));
}

void TSql_set_where(TSql* msql,  char* w_where)
{
    if (msql->sql_where) {
        TString_destroy(&msql->sql_where);
    }
    msql->sql_where = TString_init(TString_new(),(w_where));
}

void TSql_set_where_cpy(TSql* msql, char* w_where)
{
    TSql_set_where(msql, cstring_clone(w_where));
}

void TSql_set_order(TSql* msql,  char* w_order)
{
    if (msql->sql_order_by) {
        TString_destroy(&msql->sql_order_by);
    }
    msql->sql_order_by = TString_init(TString_new(), (w_order));
}

void TSql_set_order_cpy(TSql* msql, char* w_order)
{
    TSql_set_order(msql, cstring_clone(w_order));
}

void TSql_set_limit(TSql* msql, int limit, int offset)
{
    msql->limit = limit;
    msql->offset = offset;
}

void TSql_set_fields(TSql* msql,  char* fields)
{
    if (msql->fields) {
        TString_destroy(&msql->fields);
    }
    msql->fields = TString_init(TString_new(), (fields));
}

void TSql_set_fields_cpy(TSql* msql, char* fields)
{
    TSql_set_fields( msql, cstring_clone(fields));
}

void TSql_set_table(TSql* msql,  char* table_name)
{
    if (msql->table_name) {
        TString_destroy(&msql->table_name);
    }
    msql->table_name = TString_init(TString_new(), (table_name));
}

void TSql_set_table_cpy(TSql* msql, char* table_name)
{
    TSql_set_table(msql, cstring_clone(table_name));
}

void TSql_clear_filters(TSql* msql)
{
    TArray_clean(&msql->filters, (TFVoidPtrHld)TString_destroy);
}

TString* TSql_sql(TSql* sql)
{
    return sql->sql;
}


