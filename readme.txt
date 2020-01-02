cJSON 开源项目位置：  http://sourceforge.net/projects/cjson/
cJSON，只有两个文件，一个cJSON.c 一个cJSON.h文件
编译:gcc -g -Wall *.c -l m

一.创造json
1.创建根对象，cJSON_CreateObject(),用完了以后，需要手工调用 cJSON_Delete(root); 进行内存回收
2.使用cJSON_AddItemToObject向根对象添加元属


二.解析json
使用cJSON_Parse(),cJSON_GetObjectItem
