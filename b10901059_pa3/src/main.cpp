# include "main.h"

// function definition
// -------------------------------------------------------------------------------
// init edge
edge::edge() : head(0), tail(0), weight(0) {}
edge::edge(int &_head, int &_tail, int &_weight) : head(_head), tail(_tail), weight(_weight) {}

// init vertex
vertex::vertex() : index(-1), distance(INF), parent(-1) {}
vertex::vertex(int _index) : index(_index), distance(1), parent(_index) {}

void util_function::print_vertices(vector<vertex> &vertices) {
    for(int i = 0; i < vertices.size(); i++) {
        printf("vertex %d: distance: %d, parent: %d\n", i, vertices[i].distance, vertices[i].parent);
    }
}
void util_function::print_edges(vector<edge> &edges) {
    for(int i = 0; i < edges.size(); i++) {
        printf("edge %d: %d -> %d, weight: %d\n", i, edges[i].head, edges[i].tail, edges[i].weight);
    }
}
void util_function::print_priority_queue(priority_queue<edge, vector<edge>, compare_edge> &pq) {
    printf("%ld\n", pq.size());
    while(!pq.empty()) {
        edge e = pq.top();
        pq.pop();
        printf("edge: %d -> %d, weight: %d\n", e.head, e.tail, e.weight);
    }
}

void util_function::print_adj_matrix(vector<vector<int>> &adj_matrix) {
    for (int i = 0; i < adj_matrix.size(); i++) {
        for (int j = 0; j < adj_matrix.size(); j++) {
            printf("%d ", adj_matrix[i][j]);
        }
        printf("\n");
    }
}

int util_function::trace_root(vector<vertex> &vertices, int vertex_index) {
    int root = vertex_index;
    while (root != vertices[root].parent) {
        root = vertices[root].parent;
    }
    # ifdef DEBUG
    printf("%d\n", root);
    # endif
    while (vertices[vertex_index].parent != root) {
        int next = vertices[vertex_index].parent;
        vertices[vertex_index].parent = root;
        vertex_index = next;
    }
    return root;
}


void util_function::adjust_parent(vector<vertex> &vertices, int index1, int index2) {
    if (vertices[index1].distance < vertices[index2].distance){
        vertices[index1].parent = index2;
    } else if (vertices[index1].distance >= vertices[index2].distance) {
        vertices[index2].parent = index1;
        vertices[index1].distance += (vertices[index1].distance == vertices[index2].distance);
    }
}

int util_function::DFS_traversal(int head, int tail, vector<vector<int>> &adj_matrix) {
    // TODO: DFS traverse to find whether the path exists
    // printf("head: %d, tail: %d\n", head, tail);
    // util_function::print_adj_matrix(adj_matrix);

    vector<int> visited(adj_matrix.size(), 0);
    vector<int> record;
    visited[head] = 1;
    record.push_back(head);

    while(!record.empty() && adj_matrix[head][tail] == 0){
        #ifdef DEBUG
        printf("stack top: %d\n", record.top());
        #endif
        int current = record.back();
        if (current == tail) {
            for (int i = record.size()-1; i>-1; i--) {
                adj_matrix[record[i]][tail] = 1;
            }
            break;
        } else {
            DFS(head, tail, adj_matrix, visited, record, current);
        }
    }
    
    #ifdef DEBUG
    printf("Result: %d\n", adj_matrix[head][tail]);
    printf("head: %d, tail: %d\n", head, tail);
    #endif

    // util_function::print_adj_matrix(adj_matrix);
    return adj_matrix[head][tail];
}

void util_function::DFS(int head, int tail, vector<vector<int>> &adj_matrix, vector<int> &visited, vector<int> &record, int current){
    #ifdef DEBUG
    printf("In DFS\n");
    #endif
    int i;
    for (i = 0; i < adj_matrix.size(); i++) {
        // path exist but haven't be visited      
        if (adj_matrix[current][i] == 1 && visited[i] == 0) {
            visited[i] = 1;
            record.push_back(i);
            break;
        }
    }
    // all path have been visited
    if (i == adj_matrix.size()) {
        record.pop_back();
        adj_matrix[head][current] = 1;
    }    
}

// void util_function::output_result(vector<edge> cut_edges, int total_weight, fstream fout) {
    
// }

// -------------------------------------------------------------------------------
// main function

int main(int args, char** argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    if (args != 3) {
        printf("Please follow the format: ./bin/cb inputs/<input file name> outputs/<output file name>\n");
        exit(0);
    }
    // initializing
    util_function util;

    char type[5];
    int node_num;
    int edge_num;
    int h, t, w;
    int total_weight = 0;
    vector<edge> edges;
    vector<edge> cut_edges;
    vector<edge> non_cut_edges;
    vector<edge> revise_cut_edges;
    vector<vertex> vertices;

    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;

    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);

    fin >> type;
    fin >> node_num;
    fin >> edge_num;

    // init vertices and edges
    edges.resize(edge_num);
    vertices.resize(node_num);

    for(int i=0; i<node_num; i++) {
        vertices[i] = vertex(i);    
    }

    for(int i = 0; i < edge_num; i++) {
        fin >> h >> t >> w;
        edges[i] = edge(h, t, w);
    }
    
    # ifdef DEBUG
    util.print_edges(edges);
    util.print_vertices(vertices);
    # endif
    printf("Done Initializing!\n");

    // sort edges by weight in decreasing order
    priority_queue<edge, vector<edge>, compare_edge> pq(begin(edges), end(edges));
    // # ifdef DEBUG
    // util.print_priority_queue(pq);
    // # endif
    while (!pq.empty()) {
        edge e = pq.top();
        pq.pop();
        int head = e.head;
        int tail = e.tail;
        int weight = e.weight;
        #ifdef DEBUG
        printf("head: %d, tail: %d, weight: %d\n", head, tail, weight);
        #endif
        int head_root = util.trace_root(vertices, head);
        int tail_root = util.trace_root(vertices, tail);
        if (head_root != tail_root) {
            // vertices[head_root].parent = tail_root;
            util.adjust_parent(vertices, head_root, tail_root);
            if (strncmp(type, "d", 1) == 0) non_cut_edges.push_back(e);
        } else {
            // adding this edge forms a cycle -> cut edge
            total_weight += weight;
            cut_edges.push_back(e);
        }
    }

    #ifdef DEBUG
    printf("u weight: %d\n", total_weight);
    #endif

    // main function
    if (strncmp(type, "u", 1) == 0) {
        #ifdef DEBUG
        printf("Undirected graph\n");
        #endif
        // output
        // util.output_result(cut_edges, total_weight, fout);
    } else if (strncmp(type, "d", 1) == 0) {
        #ifdef DEBUG
        printf("Directed graph\n");
        #endif
        total_weight = 0;
        vector<int> row(node_num, 0);
        vector<vector<int>> adj_matrix(node_num, row);

        for (int i = 0; i < node_num; i++) {
            adj_matrix[i][i] = 1;
        }
        for (auto &it : non_cut_edges) {
            adj_matrix[it.head][it.tail] = 1;
        }
        
        for (auto &it : cut_edges) {
            // util.print_edges(cut_edges);
            // check head -> tail enable
            int head = it.head;
            int tail = it.tail;
            int weight = it.weight;

            if (weight <= 0 || util.DFS_traversal(tail, head, adj_matrix) == 1) {
                // accept negative weight
                # ifdef DEBUG
                printf("cut\n");
                # endif
                revise_cut_edges.push_back(it);     
                total_weight += weight;

            } else {
                // check positive weight
                # ifdef DEBUG
                printf("no cut\n");
                # endif
                adj_matrix[head][tail] = 1;
                
            }
        }
        #ifdef DEBUG
        printf("d weight: %d\n", d_total_weight);
        #endif
        // util.output_result(cut_edges, total_weight, fout);
    } else {
        printf("Wrong input type!\n");
        exit(0);
    }

    fout << total_weight << endl;
    if (strncmp(type, "u", 1) == 0) {
        for (auto &it : cut_edges) {
            fout << it.head << " " << it.tail << " " << it.weight << endl;
        }
    }
    else if (strncmp(type, "d", 1) == 0){
        for (auto &it : revise_cut_edges) {
            fout << it.head << " " << it.tail << " " << it.weight << endl;
        }
    }

    printf("Done output!\n");

    tmusg.getPeriodUsage(stat);
    cout <<"The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    cout <<"memory: " << stat.vmPeak << "KB" << endl; // print peak memory

    fin.close();
    fout.close();
    return 0;
}