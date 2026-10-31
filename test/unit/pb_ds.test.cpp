#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <data_structure/pb_ds/hashmap.hpp>
#include <data_structure/pb_ds/pairing_heap.hpp>
#include <data_structure/pb_ds/red_black_tree.hpp>

void hashTest() {
    mt19937_64 rng(91472);
    HashMap<u64, i64> table;
    HashSet<u64> keys;
    map<u64, i64> expected;
    for (int q = 0; q < 3000; q++) {
        u64 key = q % 3 ? rng() % 50 : rng();
        if (rng() % 3) {
            i64 value = rng() % 10000;
            table[key] = value;
            keys.insert(key);
            expected[key] = value;
        } else {
            assert(table.erase(key) == expected.erase(key));
            keys.erase(key);
        }
        assert(table.size() == expected.size() && keys.size() == expected.size());
        for (auto [k, v] : expected) {
            assert(table.find(k) != table.end() && table.find(k)->second == v);
            assert(keys.find(k) != keys.end());
        }
    }
    HashMap<string, int, hash<string>> words;
    words["hello"] = 7;
    assert(words.find("hello")->second == 7 && words.find("missing") == words.end());
    table.clear();
    keys.clear();
    assert(table.empty() && keys.empty());
}

void orderedTest() {
    mt19937 rng(1729);
    OrderedSet<int> values;
    OrderedMap<int, int> table;
    map<int, int> expected;
    for (int q = 0; q < 1000; q++) {
        int key = int(rng() % 101) - 50;
        if (rng() % 3) {
            values.insert(key);
            table[key] = expected[key] = rng() % 1000;
        } else {
            values.erase(key);
            table.erase(key);
            expected.erase(key);
        }
        assert(values.size() == expected.size() && table.size() == expected.size());
        int rank = 0;
        for (auto [k, v] : expected) {
            assert(*values.find_by_order(rank) == k);
            assert(table.find_by_order(rank)->first == k && table.find_by_order(rank)->second == v);
            assert(int(values.order_of_key(k)) == rank && int(table.order_of_key(k)) == rank);
            rank++;
        }
        assert(values.find_by_order(rank) == values.end());
        assert(table.find_by_order(rank) == table.end());
        int less = distance(expected.begin(), expected.lower_bound(key));
        assert(int(values.order_of_key(key)) == less && int(table.order_of_key(key)) == less);
    }
    OrderedSet<int, greater<int>> descending;
    for (int x : {3, 1, 4, 1, 5}) descending.insert(x);
    assert(*descending.find_by_order(0) == 5 && descending.order_of_key(3) == 2);
    OrderedSet<int> left, right;
    for (int i = 0; i < 10; i++) left.insert(i);
    left.split(4, right);
    assert(left.size() == 5 && right.size() == 5);
    left.join(right);
    assert(left.size() == 10 && right.empty());
}

void heapTest() {
    using Value = pair<int, int>;
    PairingHeap<Value> heap;
    vector<PairingHeap<Value>::point_iterator> handles(1000);
    vector<Value> values(1000);
    set<Value> expected;
    vector<int> alive;
    mt19937 rng(78231);
    for (int i = 0; i < 1000; i++) {
        values[i] = {int(rng() % 100), i};
        handles[i] = heap.push(values[i]);
        alive.push_back(i);
        expected.insert(values[i]);
    }
    for (int q = 0; !alive.empty(); q++) {
        int p = rng() % alive.size(), id = alive[p];
        if (q % 3 == 0) {
            expected.erase(values[id]);
            values[id].first = int(rng() % 200) - 100;
            heap.modify(handles[id], values[id]);
            expected.insert(values[id]);
        } else {
            if (q % 3 == 1) {
                id = heap.top().second;
                p = find(alive.begin(), alive.end(), id) - alive.begin();
                heap.pop();
            } else heap.erase(handles[id]);
            expected.erase(values[id]);
            alive.erase(alive.begin() + p);
        }
        assert(heap.size() == expected.size());
        if (!expected.empty()) assert(heap.top() == *expected.rbegin());
    }
    assert(heap.empty());
    PairingHeap<int, greater<int>> a, b;
    for (int x : {7, 1, 5}) a.push(x);
    for (int x : {2, 4, 6}) b.push(x);
    a.join(b);
    assert(b.empty());
    for (int x : {1, 2, 4, 5, 6, 7}) { assert(a.top() == x); a.pop(); }
    assert(a.empty());
}

int main() {
    hashTest();
    orderedTest();
    heapTest();
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
