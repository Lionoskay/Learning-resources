//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#define PLACE_NUM 13 //有13个地点
//#define PLACE_NAME_MAX 4
//#define WEIGHT_MAX INT_MAX
//
//typedef struct {
//	char* name;
//}Address;
//
//Address* Init_Name(int place_num) { //地名赋值
//	Address* arr = (Address*)malloc(sizeof(Address) * PLACE_NUM);
//	if (!arr) exit(0);
//	for (int i = 0; i < PLACE_NUM; i++)
//	{
//		arr[i].name = (char*)malloc(PLACE_NAME_MAX * sizeof(char));
//		if (!arr[i].name)
//		{
//			for (int j = 0; j < i; j++)
//			{
//				free(arr[j].name);
//			}
//			exit(0);
//		}
//	}
//	char input[] = "北门 饮水思源 腾飞塔 图书馆 教学主楼 活动中心 南门 宪梓堂 西迁馆 传送门1 传送门2 传送门3 传送门4";
//	const char delim[] = " ";
//	char* address_name = strtok(input, delim);
//	for (int i = 0; i < PLACE_NUM; i++)
//	{
//		strcpy(arr[i].name, address_name);
//	}
//}
//
//void Init_weight(int weight[PLACE_NUM][PLACE_NUM])//用于表示各节点之间的权值
//{
//	weight[0][1] = 18;
//	weight[0][11] = 22;
//	weight[1][2] = 19;
//	weight[1][9] = 27;
//	weight[2][3] = 23;
//	weight[2][11] = 4;
//	weight[2][12] = 32;
//	weight[3][4] = 15;
//	weight[3][9] = 4;
//	weight[3][10] = 4;
//	weight[4][5] = 21;
//	weight[4][7] = 8;
//	weight[5][6] = 30;
//	weight[6][7] = 14;
//	weight[6][8] = 20;
//	weight[6][10] = 21;
//	weight[7][12] = 4;
//	weight[8][10] = 43;
//}
//
//void ShortestPath(Address* arr, char* Ad1, char* Ad2,int weight[PLACE_NUM][PLACE_NUM],int length)
//{//使用迪杰斯特拉算法计算两个节点之间的最小路径
////首先查找输入的名称对应的节点
//	int idx_1 = 0;
//	for (idx_1 = 0; idx_1 < PLACE_NUM; idx_1++)
//	{
//		if (Ad1 == arr[idx_1].name) break;
//	}
//	int idx_2 = 0;
//	for (idx_2 = 0; idx_2 < PLACE_NUM; idx_2++)
//	{
//		if (Ad2 == arr[idx_2].name) break;
//	}
//	//找到了两个输入的地址所对应的节点idx_1和idx_2
//	//判断是否有路径
//
//
//}
//
//
//
//void Judge(char* Ad1, char* Ad2,Address* arr)
//{
//	if (!Ad1 || !Ad2 )
//	{
//		printf("ERROR_01");
//		exit(0);
//	}
//	int index = 0;
//	for (int i = 0; i < PLACE_NUM; i++)
//	{
//		if (Ad1 != arr[i].name||Ad2 !=arr[i].name)
//		{
//			index++;
//		}
//		if (index)
//		{
//			printf("ERROR_02");
//			exit(0);
//		}
//	}
//}
//
//int main()
//{
////生成一个邻接矩阵用于表示两点之间的权值
//	int weight[PLACE_NUM][PLACE_NUM] = { WEIGHT_MAX,WEIGHT_MAX };
//	Init_weight(weight);
//	char* Ad1=NULL;
//	char* Ad2 = NULL;
//	fgets(Ad1, PLACE_NAME_MAX, stdin);
//	fgets(Ad2, PLACE_NAME_MAX, stdin);
//
//}


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>  

#define PLACE_NUM 13
#define PLACE_NAME_MAX 20  // 地名最大长度
#define WEIGHT_MAX INT_MAX

typedef struct {
    char* name;
} Address;

// 初始化地名数组
Address* Init_Name() {
    Address* arr = (Address*)malloc(sizeof(Address) * PLACE_NUM);
    if (!arr) {
        exit(0);
    }
    // 为每个节点分配地名内存
    for (int i = 0; i < PLACE_NUM; i++) {
        arr[i].name = (char*)malloc(PLACE_NAME_MAX * sizeof(char));
        if (!arr[i].name) {

            // 释放已分配的内存
            for (int j = 0; j < i; j++) {
                free(arr[j].name);
            }
            free(arr);
            exit(0);
        }
    }
    // 分割输入字符串并赋值
    const char* input = "北门 饮水思源 腾飞塔 图书馆 教学主楼 活动中心 南门 宪梓堂 西迁馆 传送门1 传送门2 传送门3 传送门4";
    const char* delim = " ";
    char* token;
    int i = 0;
    char* input_copy = (char*)malloc(strlen(input) + 1);
    if (!input_copy) {
        for (int j = 0; j < i; j++) {
            free(arr[j].name);
        }
        free(arr);
        exit(0);
    }
    strcpy(input_copy, input);
    token = strtok(input_copy, delim);
    while (token != NULL && i < PLACE_NUM) {
        strncpy(arr[i].name, token, PLACE_NAME_MAX - 1);
        arr[i].name[PLACE_NAME_MAX - 1] = '\0';
        token = strtok(NULL, delim);
        i++;
    }
    return arr;
}

// 初始化邻接矩阵
void Init_weight(int weight[PLACE_NUM][PLACE_NUM]) {
    // 初始化所有边为WEIGHT_MAX，对角线为0
    for (int i = 0; i < PLACE_NUM; i++) {
        for (int j = 0; j < PLACE_NUM; j++) {
            weight[i][j] = (i == j) ? 0 : WEIGHT_MAX;
        }
    }

    // 设置具体边权
    weight[0][1] = 18;   weight[1][0] = 18;
    weight[0][11] = 22;  weight[11][0] = 22;
    weight[1][2] = 19;   weight[2][1] = 19;
    weight[1][9] = 27;   weight[9][1] = 27;
    weight[2][3] = 23;   weight[3][2] = 23;
    weight[2][11] = 4;   weight[11][2] = 4;
    weight[2][12] = 32;  weight[12][2] = 32;
    weight[3][4] = 15;   weight[4][3] = 15;
    weight[3][9] = 4;    weight[9][3] = 4;
    weight[3][10] = 4;   weight[10][3] = 4;
    weight[4][5] = 21;   weight[5][4] = 21;
    weight[4][7] = 8;    weight[7][4] = 8;
    weight[5][6] = 30;   weight[6][5] = 30;
    weight[6][7] = 14;   weight[7][6] = 14;
    weight[6][8] = 20;   weight[8][6] = 20;
    weight[6][10] = 21;  weight[10][6] = 21;
    weight[7][12] = 4;   weight[12][7] = 4;
    weight[8][10] = 43;  weight[10][8] = 43;
}

// 查找地名对应的节点索引
int find_index(Address* arr, const char* target) {
    for (int i = 0; i < PLACE_NUM; i++) {
        if (strcmp(arr[i].name, target) == 0) {
            return i;  // 找到返回索引
        }
    }
    return -1;  // 未找到
}

// 打印路径函数
void PrintPath(Address* arr, int* prev, int src, int dest) {
    int path[PLACE_NUM];
    int path_len = 0;
    int current = dest;

    // 构造路径
    while (current != -1 && path_len < PLACE_NUM) {
        if (current < 0 || current >= PLACE_NUM) {
            return;
        }
        path[path_len++] = current;
        current = prev[current];
    }

    // 输出路径
    printf("Path: ");
    for (int i = path_len - 1; i >= 0; i--) {
        printf("%s", arr[path[i]].name);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
}


// 迪杰斯特拉算法实现
void ShortestPath(Address* arr, char* Ad1, char* Ad2, int weight[PLACE_NUM][PLACE_NUM]) {
    int src = find_index(arr, Ad1);
    int dest = find_index(arr, Ad2);

    // 检查地址是否存在
    if (src == -1 || dest == -1) {
        printf("ERROR_02");
        return;
    }

    int dist[PLACE_NUM];     // 最短距离数组
    int prev[PLACE_NUM];     // 前驱节点数组
    int visited[PLACE_NUM];  // 访问标记数组

    // 初始化
    for (int i = 0; i < PLACE_NUM; i++) {
        dist[i] = weight[src][i];
        prev[i] = (weight[src][i] != WEIGHT_MAX) ? src : -1;
        visited[i] = 0;
    }
    dist[src] = 0;
    visited[src] = 1;
    prev[src] = -1;
    // 迭代更新最短路径
    for (int count = 0; count < PLACE_NUM - 1; count++) {
        // 找到当前未访问的最短距离节点
        int min_dist = WEIGHT_MAX;
        int u = -1;
        for (int i = 0; i < PLACE_NUM; i++) {
            if (!visited[i] && dist[i] < min_dist) {
                min_dist = dist[i];
                u = i;
            }
        }
        if (u == -1) break;  // 无可达节点

        visited[u] = 1;  // 标记为已访问

        // 更新邻居节点的最短距离
        for (int v = 0; v < PLACE_NUM; v++) {
            if (!visited[v] && weight[u][v] != WEIGHT_MAX &&
                dist[u] != WEIGHT_MAX && dist[u] + weight[u][v] < dist[v]) {
                dist[v] = dist[u] + weight[u][v];
                prev[v] = u;
            }
        }
    }
    // 输出结果
    if (dist[dest] == WEIGHT_MAX) {
        printf("ERROR_02");
        return;
    }
    
    printf("%d\n", dist[dest]);
    PrintPath(arr, prev, src, dest);
}


// 输入验证函数
void Judge(char* Ad1, char* Ad2, Address* arr) {
    if (!Ad1 || !Ad2) {
        printf("ERROR_01");
        exit(0);
    }
    Ad1[strcspn(Ad1, "\n")] = '\0';
    Ad2[strcspn(Ad2, "\n")] = '\0';
    int exist1 = find_index(arr, Ad1);
    int exist2 = find_index(arr, Ad2);
    if (exist1 == -1 || exist2 == -1) {
        printf("ERROR_02");
        exit(0);
    }
}

int main() {
    // 初始化地名数组
    Address* addr_arr = Init_Name();
    // 初始化邻接矩阵
    int weight[PLACE_NUM][PLACE_NUM] = { 0,0 };
    Init_weight(weight);
    // 分配输入缓冲区
    char Ad1[PLACE_NAME_MAX] = { 0 };
    char Ad2[PLACE_NAME_MAX] = { 0 };

    // 读取输入
    if (fgets(Ad1, sizeof(Ad1), stdin) == NULL) {
        printf("ERROR_01");
        exit(0);
    }
    if (fgets(Ad2, sizeof(Ad2), stdin) == NULL) {
        printf("ERROR_01");
        exit(0);
    }
    Ad1[strcspn(Ad1, "\n")] = '\0';
    Ad2[strcspn(Ad2, "\n")] = '\0';
    // 验证输入
    Judge(Ad1, Ad2, addr_arr);

    // 计算最短路径
    ShortestPath(addr_arr, Ad1, Ad2, weight);

    // 释放内存
    for (int i = 0; i < PLACE_NUM; i++) {
        free(addr_arr[i].name);
    }
    free(addr_arr);

    return 0;
}