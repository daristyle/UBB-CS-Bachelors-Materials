#include "../Graph/Graph.h"
#include <iostream>
#include <fstream>
#include <vector>

using std::vector;

//ASSUMING THE VERTICS IN THE GRAPH ARE INDEXED FROM 0 TO noVertices() - 1

template<typename T>
struct Matrix{
    vector<vector<T>> matrix;
    int n;
    Matrix(int n){
        this->n = n;
        matrix.resize(n, vector<T>(n, T{}));
    }

    vector<T>& operator[](int row){
        return matrix[row];
    }

    const vector<T>& operator[](int row) const{
        return matrix[row];
    }
};

const int INF = INT32_MAX;

pair<Matrix<int>, Matrix<int>> createMatrices(Graph& g){
    int n = g.noVertices();
    Matrix<int> w(n), f(n);
    for(auto i: g.getVertices()){
        for(auto j: g.getVertices()){
            if(i == j){
                w[i][j] = 0;
                f[i][j] = -1;
            }else if(g.isEdge(i, j)){
                w[i][j] = g.getCost(i, j);
                f[i][j] = j;
            }else{
                w[i][j] = INF;
                f[i][j] = -1;
            }
        }
    }

    return {w, f};
}

pair<Matrix<int>, Matrix<int>> multiplyMatrices(const pair<const Matrix<int>&,const Matrix<int>&>& mat1,
    const pair<const Matrix<int>&,const Matrix<int>&>& mat2){
    auto& [w1, f1] = mat1;
    auto& [w2, f2] = mat2;
    int n = w1.n;
    Matrix<int> w(n), f(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            w[i][j] = w1[i][j];
            f[i][j] = f1[i][j];
            for(int k = 0; k < n; k++){
                if(w1[i][k] != INF && w2[k][j] != INF){
                    if(w[i][j] > w1[i][k] + w2[k][j]){
                        w[i][j] = w1[i][k] + w2[k][j];
                        f[i][j] = f1[i][k];
                    }
                }
            }
        }
    }

    return {w, f};
}

bool hasNegativeCycle(const Matrix<int>& w){
    for(int i = 0; i < w.n; i++){
        if(w[i][i] < 0){
            return true;
        }
    }
    return false;
}

int main(){
    std::ifstream fin{"graph5.in"};
    Graph g = readGraph(fin, true, true);
    auto [w, f] = createMatrices(g);
    int k = 0;
    while((1 << k) < g.noVertices()){
        ++k;
        std::tie(w, f) = multiplyMatrices({w, f}, {w, f});
    }

    if(hasNegativeCycle(w)){
        std::cout << "NEGATIVE CYCLE FOUND" << std::endl;
        return 0;
    }

    int start, end;
    vector<int> path;
    fin >> start >> end;
    while(start != -1){
        path.push_back(start);
        start = f[start][end];
    }

    if(path.back() != end){
        std::cout << "NO PATH FOUND" << std::endl;
        return 0;
    }

    for(auto node: path){
        std::cout << node << " ";
    }
    std::cout << std::endl;
    int cost = 0;
    for(int i = 0; i < path.size() - 1; i++){
        cost += g.getCost(path[i], path[i + 1]);
    }
    std::cout << cost << std::endl;

    for(int kk = 0; kk < k; kk++){
        std::cout << "\n\n\n";
        for(int i = 0; i < g.noVertices(); i++){
            for(int j = 0; j < g.noVertices(); j++){
                std::cout << w[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}