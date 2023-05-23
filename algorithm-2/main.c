#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int v1;
    int v2;
	int weight;
    int T;
} edge;

int edgeCount(int graph[][6]) {
	int count = 0;
    for (int i = 0; i < 6; i++) {
        for (int j = i+1; j < 6; j++) {
            if (graph[i][j] != 0) {
				count++;
			}
		}
	}
	return count;
}

edge* edgesort(int graph[][6], edge* edges) {
    int Aedge = 0;
    for (int i = 0; i < 6; i++) {
        for (int j = i + 1; j < 6; j++) {
            if (graph[i][j] != 0) {
                edges[Aedge].v1 = i;
				edges[Aedge].v2 = j;
				edges[Aedge].weight = graph[i][j];
                Aedge++;
            }
        }
    }
    // 가중치 정렬
    for (int i = 0; i < Aedge-1; i++) {
        for (int j = i + 1; j < Aedge; j++) {
            if (edges[i].weight > edges[j].weight) {
                edge temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
            else if (edges[i].weight == edges[j].weight) {
                if (edges[i].v1 > edges[j].v1) {
                    edge temp = edges[i];
                    edges[i] = edges[j];
                    edges[j] = temp;
                }
            }
        }
    }
    return edges;
}

int findroot(int v, int v_union[]) {
    while (v_union[v] > -1) {
        v = v_union[v];
    }
    return v;
}

int iscycle(edge edges, int v_union[]) {
    int v1 = edges.v1;
    int v2 = edges.v2;
    while (v_union[v1] > -1) {
        v1 = v_union[v1];
    }
    while (v_union[v2] > -1) {
        v2 = v_union[v2];
    }
    //printf("%d  %d\n", v1, v2);
    if (v1 == v2) {
        printf("사이클이 탐지되었다.\n");
        return 1;
    }
    return 0;
}




void printMST(edge tree) {
    if (tree.v1 == 0)
        printf("A  ");
    else if (tree.v1 == 1) {
        printf("B  ");
    }
    else if (tree.v1 == 2) {
        printf("C  ");
    }
    else if (tree.v1 == 3) {
        printf("D  ");
    }
    else if (tree.v1 == 4) {
        printf("E  ");
    }
    else if (tree.v1 == 5) {
        printf("F  ");
    }
    if (tree.v2 == 0)
        printf("A  ");
    else if (tree.v2 == 1) {
        printf("B  ");
    }
    else if (tree.v2 == 2) {
        printf("C  ");
    }
    else if (tree.v2 == 3) {
        printf("D  ");
    }
    else if (tree.v2 == 4) {
        printf("E  ");
    }
    else if (tree.v2 == 5) {
        printf("F  ");
    }
}

void Kruskal(edge* edges, int alledge) {
    int v_union[6] = { -1,-1,-1,-1,-1,-1 };
    int count = 0;
    while (count < alledge) {
        if(iscycle(edges[count],v_union)){
            count++;
            continue;
        }
        int v1 = edges[count].v1;
        int v2 = edges[count].v2;
        edges[count].T = 1;
        if (v_union[v1] == -1 && v_union[v2] == -1) {
            v_union[v1] -= 1;
            v_union[v2] = v1;
        }
        else if (v_union[v1] > -1 && v_union[v2] < -1) {
            int root = findroot(v1, v_union);
            v_union[v2] = root;
            v_union[root] -= 1;
        }
        else if (v_union[v2] > -1 && v_union[v1] < -1) {
            int root = findroot(v2, v_union);
            v_union[v1] = root;
            v_union[root] -= 1;
        
        }
        else if (v_union[v1] < -1) {
            v_union[v1] -= 1;
            v_union[v2] = v1;
        }
        else if (v_union[v2] < -1) {
            v_union[v2] -= 1;
            v_union[v1] = v2;
        }
        else if (v_union[v1] > -1) {
            int root = findroot(v1, v_union);
            v_union[v2] = root;
            v_union[root] -= 1;
        }
        else if (v_union[v2] > -1) {
            int root = findroot(v2, v_union);
            v_union[v1] = root;
            v_union[root] -= 1;
        }

        /*for (int i = 0; i < 6; i++) {
            printf("%d  ", v_union[i]);
        }
        printf("\n");*/
        printMST(edges[count]);
        printf("간선추가\n");
        count++;
    }
}


int main(void) {
    int A_graph[6][6] = { {0,8,0,2,4,0},
                          {8,0,1,4,0,2},
                          {0,1,0,0,0,1},
                          {2,4,0,0,3,7},
                          {4,0,0,3,0,9},
                          {0,2,1,7,9,0} };
    int B_graph[6][6] = { {0, 9, 0, 4, 7, 2},
                          {9, 0, 13, 17, 0, 11},
                          {0, 13, 0, 16, 0, 14},
                          {4, 17, 16, 0, 12, 20},
                          {7, 0, 0, 12, 0, 0},
                          {2, 11, 14, 20, 0, 0} };
    


    int Alledge = 0;
    Alledge = edgeCount(A_graph, 6);
    edge* A_edges = malloc(sizeof(edge) * Alledge);
    A_edges = edgesort(A_graph, A_edges, Alledge);
    /*for (int i = 0; i < Alledge; i++) {
        printf("%d  %d  %d\n", A_edges[i].v1, A_edges[i].v2, A_edges[i].weight);
    }*/
    printf("교안의 Kruskal 알고리즘 수행과정 예시의 그래프를 입력으로 넣었을때\n");
    Kruskal(A_edges,Alledge);
    printf("\n");
    for (int i = 0; i < Alledge; i++) {
        if (A_edges[i].T == 1) {
            printMST(A_edges[i]);
            printf("-  ");
        }
    }
    printf("MST의 연결된 간선들\n\n");
    free(A_edges);

    Alledge = edgeCount(B_graph, 6);
    edge* B_edges = malloc(sizeof(edge) * Alledge);
    B_edges = edgesort(B_graph, B_edges, Alledge);
    printf("\n6개의 정점을 가진 가중치 그래프\n");
    for (int i = 0; i < Alledge; i++) {
        printMST(B_edges[i]);
        printf("%d\n", B_edges[i].weight);
    }
    printf("가중치에 따라 정렬된 그래프의 엣지들\n");
    Kruskal(B_edges, Alledge);
    printf("\n");
    for (int i = 0; i < Alledge; i++) {
        if (B_edges[i].T == 1) {
            printMST(B_edges[i]);
            printf("-  ");
        }
    }
    printf("MST의 연결된 간선들\n");
    free(B_edges);

    return 1;
}