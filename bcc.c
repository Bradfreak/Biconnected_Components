#include <stdio.h>
#include <stdlib.h>

struct edge {
    int medge;
    int oedge;
};

struct resedge {
    int resn;
    struct edge edge;
};

void insertionSort(struct edge [], int , int );
void sort_edges(struct edge [], int);
int pop(int [], int );
struct edge poppedge(  struct edge [], int );
void bcc(int [], int [], int, int, struct resedge []);
int min(int, int);

int main(){
    FILE *infile;
    infile = fopen("graph.txt", "r");
    if(infile == NULL){ 
        fprintf(stderr, "Error in opening input file\n"); 
        exit (1); 
    }
    int ver, edg, i, j = 0, pv = 0, pe, res = -1;
    fscanf(infile, "%d %d", &ver, &edg);
    struct edge alledge[2*edg];

    for(i = 0; i <edg; i++){
        fscanf(infile, "%d %d", &pv, &pe);
        alledge[2*i].medge = pv;
        alledge[2*i].oedge = pe;
        alledge[(2*i)+1].medge = pe;
        alledge[(2*i)+1].oedge = pv;
    }

    fclose(infile);

    sort_edges(alledge, 2*edg);
    int vertex[ver], edge[2*edg];
    struct resedge result[edg];

    for (i = 0; i <2*edg; i++){
        if(i == 0){
            j = alledge[i].medge;
            vertex[j-1] = i;
            edge[i] = alledge[i].oedge;
        }
        else if(j == alledge[i].medge){
            edge[i] = alledge[i].oedge;
        }
        else if(j+1 == alledge[i].medge){
            j = alledge[i].medge;
            vertex[j-1] = i;
            edge[i] = alledge[i].oedge;
        }
    }

    bcc(vertex, edge, ver, 2*edg, result);

    for(i = 0; i <edg; i++) {
        if(res != result[i].resn){
            if(res != -1){
                printf("}\n");
            }
            res++;
            printf("Biconnected Component %d:-\n { (%d, %d) ",result[i].resn+1,result[i].edge.medge, result[i].edge.oedge);
        }
        else
        {
            printf("(%d %d) ",result[i].edge.medge, result[i].edge.oedge);
        }
    }
    printf("}\n");

    exit(0);
}

void sort_edges(struct edge edges[], int n){
    insertionSort(edges, n, 0);
    insertionSort(edges, n, 1);
}

void insertionSort(struct edge arr[], int n, int mo) 
{
    int i, j;
    struct edge key;
    if(mo == 0){
        for (i = 1; i < n; i++) { 
            key = arr[i]; 
            j = i - 1; 
            while (j >= 0 && arr[j].oedge > key.oedge) { 
                arr[j + 1] = arr[j]; 
                j = j - 1; 
            } 
            arr[j + 1] = key; 
        } 
    }
    else {
        for (i = 1; i < n; i++) { 
            key = arr[i]; 
            j = i - 1; 
            while (j >= 0 && arr[j].medge > key.medge) { 
                arr[j + 1] = arr[j]; 
                j = j - 1; 
            } 
            arr[j + 1] = key; 
        }
    }
} 

int pop(int arr[], int head){
    return(arr[head]);
}

struct edge poppedge(struct edge arr[], int head){
    return(arr[head]);
}

void bcc(int vertex[], int edge[], int ver, int edg, struct resedge result[]){
    int parent[ver], dis[ver], low[ver], stknum[ver], stack[ver], heads = 0, heade = -1, i, neig, j;
    struct edge edgestack[edg], backedge[edg];

    for(i = 0; i < ver; i++) {
        stknum[i] = 0;
    }

    stack[heads] = 1;
    dis[0] = low[0] = stknum[0] = 1;
    parent[0] = 0;
 
    int res = 0, v = 0, be = 0, boolbe = 0;
    while(heads != -1){
        if(stack[heads] == ver) {
            neig = edg;
        }
        else {
            neig = vertex[stack[heads]]; 
        }
        for(i = vertex[stack[heads]-1] ; i < neig; i++) {
            for(j = 0; j < ver; j++){
    }
            if(stknum[edge[i]-1] == 0) {
                parent[edge[i]-1] = stack[heads];
                heade++;
                edgestack[heade].medge = stack[heads];
                heads++;
                stack[heads] = edge[i];
                edgestack[heade].oedge = stack[heads];
                stknum[edge[i]-1] = 1;
                dis[edge[i]-1] = edge[i];
                low[edge[i]-1] = edge[i];
                break;
            }
            else if(parent[stack[heads]-1] == edge[i]) {
            }
            else if(stknum[edge[i]-1] == 1) {
                boolbe = 0;
                for(j = 0; j < be; j++){
                    if(backedge[j].medge == stack[heads] && backedge[j].oedge == edge[i]){
                        boolbe = 1;
                        break;
                    }
                }
                if(boolbe != 1){
                    low[stack[heads]-1] = min(low[stack[heads]-1], dis[edge[i]-1]);
                    heade++;
                    edgestack[heade].medge = stack[heads];
                    backedge[be].medge = stack[heads];
                    edgestack[heade].oedge = edge[i];
                    backedge[be].oedge = edge[i];
                    be++;
                }
            }
            else if(stknum[edge[i]-1] == 2) {
                stknum[edge[i]-1] = 3;
                if(low[edge[i]-1] >= dis[stack[heads]-1]){
                    while(edgestack[heade].medge != stack[heads] || edgestack[heade].oedge != edge[i]){
                        result[v].edge.medge = edgestack[heade].medge;
                        result[v].edge.oedge = edgestack[heade].oedge;
                        result[v].resn = res;
                        heade--;
                        v++;
                    }
                    result[v].edge.medge = edgestack[heade].medge;
                    result[v].edge.oedge = edgestack[heade].oedge;
                    result[v].resn = res;
                    heade--;
                    v++;
                    res++;
                }
            }
            else if(stknum[edge[i]-1] == 3) {
            }
        }
        if(heads == 0 && i == neig){
            stknum[stack[heads]-1] = 2;
            pop(stack, heads);
            heads--;
            continue;
        }
        if(i == neig){
            stknum[stack[heads]-1] = 2;
            low[parent[stack[heads]-1]-1] = min(low[parent[stack[heads]-1]-1], low[stack[heads]-1]);
            pop(stack, heads);
            heads--;
        }
    }
}

int min(int a, int b){
    if(a < b){
        return a;
    }

    return b;
    
}