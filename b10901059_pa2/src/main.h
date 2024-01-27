# include <stdio.h>
# include <string.h>
# include <vector>
# include <iostream>
#include <algorithm>
#include <fstream>
#include "./tm_usage.h"

# define BUFFER_SIZE 256
# define NEGATIVE_INF -0xffffff
# define DP
// # define DEBUG

using namespace std;

void print_mat_2d(vector<vector<int>> &mat, int row, int col);

void find_chords(vector<vector<pair<int, int>>> &rec_chord, vector<int> &ans_chords, vector<int> chords, int m, int n, int pivot_num);

int find_mps(vector<vector<int>> &chord_cnt, vector<int> &chords, vector<vector<pair<int, int>>> &rec_chord, int i, int j, int pivot_num);
