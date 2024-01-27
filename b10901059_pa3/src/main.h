# include <stdio.h>
# include <string.h>
# include <vector>
# include <iostream>
# include <queue>
# include <algorithm>
# include <fstream>
# include <stack>
# include "./tm_usage.h"

// # define DEBUG
# define INF 0x3f3f3f3f
# define MAX_UNODE 10000
# define MAX_DNODE 5000
# define MAX_UEDGE 20000000
# define MAX_DEDGE 10000

using namespace std;

struct edge{
    int head, tail, weight;
    edge();
    edge(int &_head, int &_tail, int &_weight); 
};

struct vertex{
    int index, distance, parent;
    vertex();
    vertex(int _index);
};

// define priority queue sorting method
class compare_edge{
    public:
        bool operator()(edge &a, edge &b){
            return a.weight < b.weight;
        }
};

struct util_function{
    void print_edges(vector<edge> &edges);
    void print_vertices(vector<vertex> &vertices);
    void print_priority_queue(priority_queue<edge, vector<edge>, compare_edge> &pq);
    void print_adj_matrix(vector<vector<int>> &adj_matrix);
    // void output_result(vector<edge> cut_edges, int total_weight, fstream fout);
    int trace_root(vector<vertex> &vertices, int vertex_index);
    // compare distance between two vertices
    void adjust_parent(vector<vertex> &vertices, int index1, int index2);
    void DFS(int head, int tail, vector<vector<int>> &adj_matrix, vector<int> &visited, vector<int> &record, int current);
    int DFS_traversal(int head, int tail, vector<vector<int>> &adj_matrix);
};

