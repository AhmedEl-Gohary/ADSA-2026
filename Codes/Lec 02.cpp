#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct PersistentArray {
    // Each index holds a vector of {time, value} pairs
    vector<vector<pair<int, int>>> data;

    PersistentArray(vector<int>& a) {
        int n = a.size();
        data.resize(n);
        for (int i = 0; i < n; i++) {
            data[i].push_back({0, a[i]});
        }
    }

    int get_item(int index, int time) {
        // Find the first element with time > given time, then step back
        auto& history = data[index];
        auto ub = std::upper_bound(history.begin(), history.end(), std::make_pair(time, INT_MAX));

        // If the user asks for a time before time 0, this might fail,
        // but since we init at time 0, prev(ub) is safe.
        return std::prev(ub)->second;
    }

    void update_item(int index, int value, int time) {
        // Ensure strictly increasing time for this specific index
        assert(!data[index].empty() && data[index].back().first < time);
        data[index].push_back({time, value});
    }
};


struct Node {
    ll sum = 0;
    Node *left, *right;
    Node(int sum) :sum(sum) ,left(nullptr), right(nullptr) {}
    Node(Node *left, Node *right) : left(left), right(right){
        if (left) sum+=left->sum;
        if (right) sum+=right->sum;
    }
};

struct PersistentSegTree {
    int n;
    vector<Node*> versions;
    PersistentSegTree(int n) :n(n){ versions.push_back(build(0, n-1));};
    Node *build(int l , int r) {
        if (l == r) return new Node(0);
        int mid = (l + r) / 2;
        return new Node(build(l, mid), build(mid + 1, r));
    }
    Node *update(Node *node,int idx,int val, int l , int r) {
        if (l == r) return new Node(val);
        int mid = (l + r) / 2;
        if (idx <= mid)
            return new Node(update(node->left, idx, val, l, mid), node->right);
        return new Node(node->left, update(node->right, idx, val, mid + 1, r));
    }
    Node* query(Node *node, int a, int b, int l , int r) {
        if (l > b || r < a) return nullptr;
        if (l >= a && r <= b) return node;
        int mid = (l + r) / 2;
        return new Node(query(node->left, a, b, l, mid) , query(node->right, a, b, mid + 1, r));
    }
    Node* update(int id,int idx,int val){
        return update(versions[id],idx,val,0,n-1);
    }
    ll query(int id, int a , int b){
        return query(versions[id],a,b,0,n-1)->sum;
    }
    void add(Node *node){
        versions.push_back(node);
    }
};
