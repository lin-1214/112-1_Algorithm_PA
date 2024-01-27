#include "main.h" 

void print_mat_2d(vector<vector<int>> &mat, int row, int col){
    
    for (int i=0; i<row; i++){
        for (int j=0; j<col; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

// void find_mps(vector<vector<int>> &chord_cnt, vector<vector<int>> &chords, int pivot_num) {
//     for (int j = 0; j < pivot_num; j++){
//         for (int i = 0; i < j; i++){
//             if (i >= j) {
//                 chord_cnt[i][j] = 0;
//                 break;
//             }
            
//             for (int k = i; k < j; k++) {
//                 int head = -1;
//                 int tail = -1;
//                 // check whether chord exists
//                 for (int n = 0; n < chords.size(); n++) {
//                     if (chords[n][0] != k || chords[n][1] != j) continue;
//                     else {
//                         head = k;
//                         tail = j;
//                     }
//                 }

//                 // specific chord doesn't exist
//                 if (head < 0 || tail < 0) break;
//                 else if (i > k - 1 && k + 1 > j - 1) {
//                     if (1 > chord_cnt[i][j-1]) chord_cnt[i][j] = 1;
//                     else chord_cnt[i][j] = chord_cnt[i][j-1];
//                 }else if (i > k-1) {
//                     if (1 + chord_cnt[k+1][j-1] > chord_cnt[i][j-1]) chord_cnt[i][j] = 1 + chord_cnt[k+1][j];
//                     else chord_cnt[i][j] = chord_cnt[i][j-1];
//                 }else if (k + 1 > j - 1) {
//                     if (chord_cnt[i][k-1] + 1 > chord_cnt[i][j-1]) chord_cnt[i][j] = chord_cnt[i][k-1] + 1;
//                     else chord_cnt[i][j] = chord_cnt[i][j-1];
//                 }
//             }
//         }
//     }

//     return;
// }

void find_chords(vector<vector<int>> &chord_cnt, vector<int> &ans_chords, vector<int> chords, int m, int n, int pivot_num) {    
    
    if (n >= pivot_num || m < 0 || m >= n) return;
    // if (chord_cnt[n][m] == -1) find_chords(chord_cnt, ans_chords, chords, m+1, n, pivot_num);
    
    #ifdef DEBUG
        printf("m: %d, n: %d\n", m, n);
    #endif
    
    int k = chords[chord_cnt[n][m]];
    int j = chord_cnt[n][m];
    #ifdef DEBUG
        printf("n: %d, m: %d, k: %d, j: %d\n", n, m, k, j); // 3, 1, 4, 0
    #endif

    ans_chords.push_back(k);
    if (k == j || j == -1) {
        ans_chords.pop_back();
        find_chords(chord_cnt, ans_chords, chords, m+1, n, pivot_num);
    }else if (k == m && j == n){
        find_chords(chord_cnt, ans_chords, chords, k+1, j-1, pivot_num);
    }else {
        find_chords(chord_cnt, ans_chords, chords, k+1, j-1, pivot_num);
        find_chords(chord_cnt, ans_chords, chords, j+1, n, pivot_num);
    } 
    
    return;
}

int find_mps(vector<vector<int>> &chord_cnt, vector<int> &chords, int i, int j, int pivot_num){
    
    // DP solution (top down)
    // seperate to 4 cases
    // if (k > i && k <= j && find_mps(chord_cnt, chords, rec_chord, i+1, k-1, pivot_num) + 1 + find_mps(chord_cnt, chords, rec_chord, k+1, j, pivot_num) > find_mps(chord_cnt, chords, rec_chord, i+1, j, pivot_num)) {
    //     chord_cnt[i][j] = chord_cnt[i+1][k-1] + 1 + chord_cnt[k+1][j]; 

    if (i >= j || i < 0 || j >= pivot_num) return 0;
    #ifdef DP
        if (chord_cnt[i][j] > 0) return chord_cnt[i][j];
    #endif
    int k = chords[i];
    chord_cnt[j][i] = k;
    #ifdef DEBUG
        printf("i: %d, k: %d, j: %d\n", i, k, j);
    #endif

    if (k == j) {
        // case 1
        // printf("i: %d, k: %d, j: %d\n", i, k, j);
        chord_cnt[i][j] = find_mps(chord_cnt, chords, i+1, k-1, pivot_num) + 1;

    } else if (k > i && k <= j && find_mps(chord_cnt, chords, i, k, pivot_num) + find_mps(chord_cnt, chords, k+1, j, pivot_num) > find_mps(chord_cnt, chords, i+1, j, pivot_num)) {
        // case 2
        chord_cnt[i][j] = chord_cnt[i][k] + chord_cnt[k+1][j];
        
    } else {
        // case 3
        chord_cnt[j][i] = -1;
        chord_cnt[i][j] = find_mps(chord_cnt, chords, i+1, j, pivot_num);
    }
                
    return chord_cnt[i][j];
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (argc != 3){
        printf("Please follow the format: ./mps a.in a.out");
        exit(0);
    }
    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;

    int pivot_num;
    int head;
    int tail;
    int chord_max = NEGATIVE_INF;

    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);
    fin >> pivot_num;
    // save all the chords from input
    // chords[head] = tail
    // chords[tail] = head
    vector<int> chords(pivot_num, 0);
    
    // save chords used in answer
    vector<int> ans_chords;

    // up-right half: number of available chords in partition chord_cnt[i][j]
    // bottom-left half: record the chord we want
    vector<vector<int>> chord_cnt(pivot_num, vector<int> (pivot_num, 0));
    for (int i=0; i<pivot_num; i++) {
        for (int j=0; j<pivot_num; j++) {
            if (j < i) {
                chord_cnt[i][j] = -1;
            }
        }
    }
    // print_mat_2d(chord_cnt, pivot_num, pivot_num);

    // vector<vector<pair<int, int>>> rec_chord;
    // for (int i=0 ; i<pivot_num; i++) {
    //     vector<pair<int, int>> tmp;
    //     for (int j=0; j<pivot_num; j++) {
    //         tmp.push_back(make_pair(0, 0));
    //     }
    //     rec_chord.push_back(tmp);
    // }

    while (fin >> head >> tail){
        // printf("(head, tail): (%d, %d)\n", head, tail);
        chords[head] = tail;
        chords[tail] = head;   
    }

    tmusg.periodStart();

    chord_max = find_mps(chord_cnt, chords, 0, pivot_num-1, pivot_num);
    fout << chord_max << endl;
    // print_mat_2d(chord_cnt, chord_cnt.size(), chord_cnt[0].size());
    // find_chords(rec_chord, ans_chords, chords, 0, pivot_num-1, pivot_num);
    find_chords(chord_cnt, ans_chords, chords, 0, pivot_num-1, pivot_num);
    #ifdef DEBUG
        for (int i=0; i<pivot_num; i++) {
            for (int j=0; j<pivot_num; j++) {
                printf("(%d, %d) ", rec_chord[i][j].first, rec_chord[i][j].second);
            }
            printf("\n");
        }
    #endif
    
    for (int i=0; i<ans_chords.size(); i++) {
        fout << ans_chords[i] << " " << chords[ans_chords[i]] << endl;
    }

    #ifdef DEBUG
        printf("after: \n");
        print_mat_2d(chord_cnt, chord_cnt.size(), chord_cnt[0].size());
        printf("----------------------\n");
        print_mat_2d(rec_chord, rec_chord.size(), rec_chord[0].size());
        printf("answer chords: ");
        for (int i=0; i< ans_chords.size(); i++) {
            printf("%d ", ans_chords[i]);
        }
        printf("\n");
    #endif

    tmusg.getPeriodUsage(stat);
    cout <<"The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    cout <<"memory: " << stat.vmPeak << "KB" << endl; // print peak memory


    fin.close();
    fout.close();
    return 0;
}