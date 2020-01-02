#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

int create_js(void) {	//创建简单的json
	cJSON *root;
	root = cJSON_CreateObject();
	if (!root) {
		printf("get root faild !\n");
		return -1;
	} else
		printf("get root success!\n");

	cJSON * js_body;

	const char * const body = "body";
	cJSON_AddItemToObject(root, body, js_body = cJSON_CreateObject());
	cJSON_AddStringToObject(js_body, "name", "xiaohui");
	cJSON_AddNumberToObject(js_body, "value", 600);
	char *s = cJSON_PrintUnformatted(root);
	if (s) {
		printf("create js string is %s\n", s);
		free(s);
	}
	cJSON_Delete(root);

	return 0;
}

int create_jsArray(void) //创建数组
{
	cJSON *root;
	root = cJSON_CreateArray();
	cJSON_AddItemToArray(root, cJSON_CreateString("Hello world"));
	cJSON_AddItemToArray(root, cJSON_CreateNumber(10));
	{
//        char *s = cJSON_Print(root);
		char *s = cJSON_PrintUnformatted(root);
		if (s) {
			printf(" %s \n", s);
			free(s);
		}
	}
	if (root)
		cJSON_Delete(root);

	return 0;
}

int create_jsArray2(void) //对象里面一个数组，数组里面包括对象
{
	cJSON *root, *js_body, *js_list;
	root = cJSON_CreateObject();
	cJSON_AddItemToObject(root, "body", js_body = cJSON_CreateArray());
	cJSON_AddItemToArray(js_body, js_list = cJSON_CreateObject());
	cJSON_AddStringToObject(js_list, "name", "xiaohui");
	cJSON_AddNumberToObject(js_list, "status", 100);

	{
		//        char *s = cJSON_Print(root);
		char *s = cJSON_PrintUnformatted(root);
		if (s) {
			printf(" %s \n", s);
			free(s);
		}
	}
	if (root)
		cJSON_Delete(root);

	return 0;
}

int parse_js() {
	char *s = "{\"name\":\"xiao hong\",\"age\":10}";
	cJSON *root = cJSON_Parse(s);
	if (!root) {
		printf("get root faild !\n");
		return -1;
	}
	cJSON *name = cJSON_GetObjectItem(root, "name");
	if (!name) {
		printf("No name !\n");
		return -1;
	}
	printf("name type is %d\n", name->type);
	printf("name is %s\n", name->valuestring);

	cJSON *age = cJSON_GetObjectItem(root, "age");
	if (!age) {
		printf("no age!\n");
		return -1;
	}
	printf("age type is %d\n", age->type);
	printf("age is %d\n", age->valueint);
	return 0;
}

int parse_js2() {
	char *s =
			"{\"list\":{\"name\":\"xiao hong\",\"age\":10},\"other\":{\"name\":\"hua hua\"}}";
	cJSON *root = cJSON_Parse(s);
	if (!root) {
		printf("get root faild !\n");
		return -1;
	}

	cJSON *js_list = cJSON_GetObjectItem(root, "list");
	if (!js_list) {
		printf("no list!\n");
		return -1;
	}
	printf("list type is %d\n", js_list->type);

	cJSON *name = cJSON_GetObjectItem(js_list, "name");
	if (!name) {
		printf("No name !\n");
		return -1;
	}
	printf("name type is %d\n", name->type);
	printf("name is %s\n", name->valuestring);

	cJSON *age = cJSON_GetObjectItem(js_list, "age");
	if (!age) {
		printf("no age!\n");
		return -1;
	}
	printf("age type is %d\n", age->type);
	printf("age is %d\n", age->valueint);

	cJSON *js_other = cJSON_GetObjectItem(root, "other");
	if (!js_other) {
		printf("no list!\n");
		return -1;
	}
	printf("list type is %d\n", js_other->type);

	cJSON *js_name = cJSON_GetObjectItem(js_other, "name");
	if (!js_name) {
		printf("No name !\n");
		return -1;
	}
	printf("name type is %d\n", js_name->type);
	printf("name is %s\n", js_name->valuestring);

	if (root)
		cJSON_Delete(root);
	return 0;
}
int parse_jsArray() {
	char *s = "{\"list\":[\"name1\",\"name2\"]}";
	cJSON *root = cJSON_Parse(s);
	if (!root) {
		printf("get root faild !\n");
		return -1;
	}
	cJSON *js_list = cJSON_GetObjectItem(root, "list");
	if (!js_list) {
		printf("no list!\n");
		return -1;
	}
	int array_size = cJSON_GetArraySize(js_list);
	printf("array size is %d\n", array_size);
	int i = 0;
	cJSON *item;
	for (i = 0; i < array_size; i++) {
		item = cJSON_GetArrayItem(js_list, i);
		printf("item type is %d\n", item->type);
		printf("%s\n", item->valuestring);
	}

	if (root)
		cJSON_Delete(root);
	return 0;
}
int parse_jsArray2() {
	char *s =
			"{\"list\":[{\"name\":\"xiao hong\",\"age\":10},{\"name\":\"hua hua\",\"age\":11}]}";
	cJSON *root = cJSON_Parse(s);
	if (!root) {
		printf("get root faild !\n");
		return -1;
	}
	cJSON *js_list = cJSON_GetObjectItem(root, "list");
	if (!js_list) {
		printf("no list!\n");
		return -1;
	}
	int array_size = cJSON_GetArraySize(js_list);
	printf("array size is %d\n", array_size);

	int i = 0;
	cJSON *item, *it, *js_name, *js_age;
	char *p = NULL;
	for (i = 0; i < array_size; i++) {
		item = cJSON_GetArrayItem(js_list, i);
		if (item == NULL) {
			break;
		}
		p = cJSON_PrintUnformatted(item);
		it = cJSON_Parse(p);
		free(p);
		if (!it)
			continue;
		js_name = cJSON_GetObjectItem(it, "name");
		printf("name is %s\n", js_name->valuestring);
		js_age = cJSON_GetObjectItem(it, "age");
		printf("age is %d\n", js_age->valueint);

	}

	if (root)
		cJSON_Delete(root);
	return 0;
}
int main(int argc, char **argv) {
//	create_js(); 		//创建简单的json {"body":{"name":"xiaohui","value":600}}
//	create_jsArray(); 	//创建数组  ["Hello world",10]
//	create_jsArray2();	//复杂数组  {"body":[{"name":"xiaohui","status":100}]}

//	parse_js();			//{"name":"xiao hong","age":10}"
//	parse_js2();		//{"list":{"name":"xiao hong","age":10},"other":{"name":"hua hua"}}";
//	parse_jsArray();	//{"list\":["name1","name2"]}
	parse_jsArray2();//{"list\":[{"name":"xiao hong","age":10},{"name":"hua hua","age":11}]}
	return 0;
}
