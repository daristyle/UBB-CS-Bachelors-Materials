#include <iostream>
#include <array>
#include <map>
#include <vector>
#include <queue>

using std::map, std::array, std::cin, std::cout, std::pair;

int parity(const array<int, 16>& a){
    int inversions = 0;
    for(int i = 0; i < 16; i++){
        for(int j = i + 1; j < 16; j++){
            inversions += (a[i] > a[j]);
        }
    }

    int manhattan = 0;
    for(int i = 0; i < 16; i++){
        if(a[i] == 16){
            manhattan = 8 - (i / 4 + 1) - (i % 4 + 1);
        }
    }

    return (inversions + manhattan) % 2;
}

bool isReachable(const array<int, 16>& a, const array<int, 16>& b){
    return parity(a) == parity(b);
}

map<array<int, 16>, array<int, 16>> Astar(array<int, 16> start, array<int, 16> end){
    if(!isReachable(start, end)){
        return {};
    }
    //cout << parity(start) << ' ' << parity(end) << '\n';
    const pair<int, int> directions[] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    map<array<int, 16>, array<int, 16>> parent;
    map<array<int, 16>, int> distance;
    
    auto compute_coords = [](int x) -> pair<int, int>{
        return {x / 4 + 1, x % 4 + 1};
    };
    auto compute_manhattan_distance = [&compute_coords](const array<int, 16>& a){
        int sum = 0;
        for(int i = 0; i < 16; i++){
            if(a[i] == 16) continue;
            auto [xfinal, yfinal] = compute_coords(a[i] - 1);
            auto [xstart, ystart] = compute_coords(i);
            sum += abs(xfinal - xstart) + abs(yfinal - ystart);
        }

        return sum;
    };
    auto compute_heuristic = [&compute_manhattan_distance](const pair<array<int, 16>, int>& a){
        return (50 * a.second + 50 * compute_manhattan_distance(a.first)) / 100;
    };
    auto cmp = [&compute_heuristic](const pair<array<int, 16>, int>& a, const pair<array<int, 16>, int>& b){
        return compute_heuristic(a) > compute_heuristic(b);
    };
    std::priority_queue<pair<array<int, 16>, int>, std::vector<pair<array<int, 16>, int>>, decltype(cmp)> pq{cmp};
    
    auto in_mat = [](const pair<int, int>& p){return p.first >= 1 && p.first <= 4 && p.second >= 1 && p.second <= 4;};
    
    distance[start] = 1;
    pq.push({start, 1});
    while(distance[end] == 0){
        auto [node, dist] = pq.top();
        pq.pop();
        if(distance[node] < dist) continue;
        for(int i = 0; i < 16; i++){
            if(node[i] == 16){
                auto [x, y] = compute_coords(i);
                for(auto [dx, dy] : directions){
                    pair<int, int> p = {x + dx, y + dy};
                    auto [xnew, ynew] = p;
                    if(in_mat(p)){
                        int delta = dx * 4 + dy;
                        auto new_node = node;
                        //cout << i << ' ' << delta << ' ' << xnew << ' ' << ynew << ' ' << x << ' ' << y<< '\n';
                        std::swap(new_node[i], new_node[i + delta]);
                        if(distance[new_node] == 0 || distance[new_node] > dist + 1){
                            distance[new_node] = dist + 1;
                            parent[new_node] = node;
                            pq.push({new_node, dist + 1});
                        }
                    }
                }
            }
        }
    }
    
    return parent;
}

void print15puzzle(const array<int, 16>& a){
    for(int i = 0; i < 16; i++){
        int val = (a[i] < 16 ? a[i] : 0);
        cout << (val < 10 ? " " : "") << val << ' ';
        if(i % 4 == 3) cout << "\n";
    }
}

void printPathRec(const array<int, 16>& start, const array<int, 16>& end, map<array<int, 16>, array<int, 16>>& parent){
    if(start == end){
        print15puzzle(end);
        return;
    }
    printPathRec(start, parent[end], parent);
    cout << "     |\n     |\n     V\n";
    print15puzzle(end);
}


void printPath(const array<int, 16>& start, const array<int, 16>& end, map<array<int, 16>, array<int, 16>>& parent){
    if(parent.find(end) == parent.end()){
        cout << "Impossible\n";
        return;
    }
    printPathRec(start, end, parent);
}

int main(){
    array<int, 16> start{};
    cout << "Enter the initial configuration, use 0 for space:\n" << std::flush;
    for(int i = 0; i < 16; i++){
        cin >> start[i];
        if(start[i] == 0) start[i] = 16;
    }

    array<int, 16> end{};
    for(int i = 0; i < 16; i++){
        end[i] = i + 1;
    }

    auto parent = Astar(start, end);
    printPath(start, end, parent);

    return 0;
}
/*
1 2 3 4
0 5 7 8
9 6 10 12
13 14 11 15

1 2 3 4
5 6 7 8
9 10 11 12
13 0 14 15
*/