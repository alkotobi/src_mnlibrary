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
}





/*
				cstring
*/

char cstring_test()
{
	print_cyan("TESTING CSTRING\n");
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
	res = cstring_is_equal(str2, "hello");
	test_v1(res);
	print_yellow("cstring_free>>>\n");
	cstring_free(&str2);
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
	assert(str);
	return str;
}

TLint cstring_count(char* str)
{
	if (str) {
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
	if (!str_src)
	{
		return 0;
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
	sprintf_s(cstring,30, "%d", i);
	return cstring;
}

char* cstring_from_double(double f)
{
	char* cstring = cstring_new(40);
	sprintf_s(cstring,40, "%f", f);
	return cstring;
}

/*
			TArray

*/


void TArray_test()
{
	print_cyan("TESTING TARRAY\n");
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
	print_yellow("TArray_clean>>>>>\n");
	TArray_clean(&arr, cstring_free);
	res = (arr->data != 0) && (TArray_size(arr) == 8) &&
		(TArray_count(arr) ==0);
	test_v1(res);
	print_yellow("TArray_free>>>>>\n");
	TArray_free(&arr);
	res = arr == 0;
	test_v1(res);
}

TArray* TArray_new()
{
	TArray* arr = (TArray*)malloc(sizeof(TArray));

	if (arr)
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
	TArray_init_v1(arr, TARRAY_DEFAULT_SIZE);
	return arr;
}

TArray* TArray_init_v1(TArray* arr, TLint size)
{
	arr->data = (TPtrHld)calloc(size, sizeof(TVar));
	assert(arr->data);
	arr->size = size;
	return arr;
	return NULL;
}

TArray** TArray_clean(TArray** arr_hld, TFVoidPtrHld free_val)
{
	for (TLint i = 0; i < TArray_count(*arr_hld); i++)
	{
		TVar var = TArray_item_at(*arr_hld, i);
		free_val(&var);
	}
	TArray_set_count(*arr_hld, 0);
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
	return arr->count;
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
	assert(index < arr->count);
	return arr->data[index];
}

TVar TArray_add(TArray* arr, TVar var)
{
	if (TArray_count(arr) == TArray_size(arr))
	{
		TLint size = arr->size * 2;
		TPtrHld data = (TPtrHld)calloc((size), sizeof(TVar));
		assert(data);
		if (data)
		{
			for (TLint i = 0; i < TArray_count(arr); i++)
			{
				data[i] = arr->data[i];
			}
			free(arr->data);
			arr->data = data;
			arr->size = arr->size * 2;
		}

	}
	if (arr->data)
	{
		arr->data[arr->count] = var;
	}

	arr->count++;
	return var;
}

void TString_test()
{
	print_cyan("TESTING TString\n");
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
	
}

TString* TString_new()
{
	TString* str = (TString*)malloc(sizeof(TString));
	
	if (str) {
		str->count = 0;
		//str->size = 0;
		str->cstring = 0;
	}else assert(str);
	return str;
}

TString* TString_init(TString* str, char* cstring)
{
	return TString_init_with_size(str, cstring_count(cstring), cstring);
}
TString* TString_init_with_size(TString* str, TLint size, char* cstring) {
	str->count = size;
	//str->size =size;
	str->cstring = cstring;
	return str;
}

TString** TString_clean(TString** str)
{
	free((*str)->cstring);
	(*str)->cstring = 0;
	(*str)->count = 0;
	//(*str)->size = 0;
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
	TLint size = str->count+1; 
	char* cstring = (char*)malloc(sizeof(char) * size);
	TString* res = 0;
	if (cstring) {
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

TString* TString_add(TString* str_src, TString* str_sub)
{
	TLint count = str_src->count + str_sub->count;
	TLint size = count + 1;
	char* cstring = (char*)calloc((size), sizeof(char));
	
	if (cstring) {
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
			else if (str[i] == 'm') {//for mnstring
				TString* ss = va_arg(ap, TString*);
				TArray_add(list, TString_clone(ss));
			}
			else if (str[i] == 'f') {//for mnstring
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
	TString* s = TStringList_text(list);
	TArray_free(TArray_clean(&list, TString_destroy));
	return  s;
}



/*
        TStringList
*/


TLint TStringList_char_count(TStringList* str_l) {
	TLint count = 0;
	for (TLint i = 0; i < TArray_count(str_l); i++)
	{
		count = count + ((TString*)TArray_item_at(str_l, i))->count;
	}
	return count;
}

TString* TStringList_text(TStringList* str_l)
{
	TLint count = TStringList_char_count(str_l);
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
	TArray_clean(str_l, TString_destroy);
	return str_l;
}

void TStringList_free(TStringList** str_l)
{
	TArray_free(str_l);
}

void TStringList_destroy(TStringList** str_l)
{
	TStringList_free(TStringList_clean(str_l));
}


/*
				TVariant
*/



TVariant* TVariant_new()
{
	TVariant* var = (TVariant*)malloc(sizeof(TVariant));
	if (var) {
		var->name = 0;
		var->value = 0;
		var->value_type = -1;
	}
	else assert(var);
	return var;
}

TVariant* TVariant_init(TVariant* var, TVar value,TTypes value_type)
{
	var->value = value;
	var->value_type = value_type;
	return var;
}

TVariant* TVariant_init_int(TVariant* var, int i)
{
	int* n = (int*)malloc(sizeof(int));
	*n = i;
	var->value = n;
	var->value_type = Int;
	return var;
}

TVariant* TVariant_init_cstring(TVariant* var, char* str)
{
	var->value = str;
	var->value_type = CString;
	return var;
}

TVariant* TVariant_init_double(TVariant* var, double f)
{
	double* d = (double*)malloc(sizeof(double));
	if (d != NULL) { *d = f; }
	else assert(d);
	var->value = d;
	var->value_type = Double;
	return var;
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

TVariant* TVariant_clean(TVariant** var_hld)
{
	free((*var_hld)->value);
	(*var_hld)->value = 0;
	return var_hld;
}

void TVariant_free(TVariant** var_hld)
{
	free((*var_hld)->name);
	free(*var_hld);
	*var_hld = 0;
}





