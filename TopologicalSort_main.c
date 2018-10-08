/*
	@brief:拓扑排序
	@author:WavenZ
	@time:2018/10/8
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "ALGraph.h"

int indegree[MAX_VERTEX_NUM];//保存所有顶点的入度

FindInDegree(const ALGraph *G, int *in) {
	ArcNode *p = NULL;
	int i;
	for (i = 0; i < MAX_VERTEX_NUM; ++i) {
		in[i] = 0;
	}
	for (i = 0; i < G->vexnum; ++i) {
		p = G->vertices[i].firstarc;
		while (p)
		{
			in[p->adjvex]++;
			p = p->nextarc;
		}
	}
}

Status TopologicalSort(const ALGraph *G) {
	int i;
	int count;
	ArcNode *p = NULL;
	SElemType data;
	SqStack S;
	FindInDegree(G, indegree);
	S = InitStack();
	for (i = 0; i < G->vexnum; ++i) {
		if (!indegree[i]) 
			Push(&S, G->vertices[i].data);
	}
	count = 0;
	while (!StackEmpty(&S)) {
		Pop(&S, &data); 
		printf("%c ", data);
		++count;
		p = G->vertices[LocateVex(G, data)].firstarc;
		while (p) {
			if (!(--(indegree[p->adjvex]))) Push(&S, G->vertices[p->adjvex].data);
			p = p->nextarc;
		}
	}
	if (count < G->vexnum) return 0;
	else return 1;
}

int main(int argc, char *argv[]) {
	ALGraph G;
	CreateGraph(&G);
	TopologicalSort(&G);
	system("pause");
	return 1;
}