#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

typedef unsigned char uchar;
typedef unsigned long long ull;

struct bigint {
    bigint(int i) : data(1, i) {}
    vector<int> data;
    void output() {
        printf("%d", data.empty() ? 0 : data.back());
        for (int i=(int)data.size()-2; i>=0; --i) {
            printf("%09d", data[i]);
        }
    }

    bigint& operator+=(const bigint &r) {
        int carry = 0;
        for (size_t i=0; i<max(data.size(),r.data.size()) || carry; ++i) {
            if (i == data.size())
                data.push_back(0);
            data[i] += carry + (i < r.data.size() ? r.data[i] : 0);
            carry = data[i] >= 1000000000;
            if (carry) data[i] -= 1000000000;
        }
        return *this;
    } 
};

typedef bigint ulll;

class AhoCorasickTrie {
    struct node {
        int id;
        unordered_map<uchar, node*> next;
        unordered_map<uchar, node*> jump;
        node *parent;
        uchar upchar;
        node *suff;
        node *uplink;
        bool terminal;
        short length;

        node(int id, node *parent, uchar upchar) : 
            id(id),
            parent(parent),
            upchar(upchar),
            suff(0),
            uplink(0),
            terminal(false),
            length(0)
        { }
    };

    int _size = 0;
    unordered_map<int, node*> nodes;

    node *root;

    node *getSuff(node *v) {
        if (!v->suff) {
            if (v->parent == root) {
                v->suff = root;
            } else {
                v->suff = getJump(getSuff(v->parent), v->upchar);
            }
        }
        return v->suff;
    }

    node *getUplink(node *v) {
        if (!v->uplink) {
            node *u = getSuff(v);
            if (u == root) {
                v->uplink = root;
            } else if (u->terminal) {
                v->uplink = u;
            } else {
                v->uplink = getUplink(u);
            }
        }
        return v->uplink;
    }

    node *getNext(node *v, uchar c) {
        if (v->next.find(c) == v->next.end()) {
            if (v == root) {
                v->next[c] = root;
            } else {
                v->next[c] = getNext(getSuff(v), c);
            }
        }
        return v->next[c];
    }

    node *getJump(node *v, uchar c) {
        if (v->jump.find(c) == v->jump.end()) {
            if (v->next.find(c) != v->next.end()) {
                v->jump[c] = v->next[c];
            } else {
                v->jump[c] = v == root ? root : getJump(getSuff(v), c);
            }
        }
        return v->jump[c];
    }

public:
    AhoCorasickTrie() {
        root = new node(0, 0, 0);
        root->parent = root;
        nodes.insert(make_pair(_size++, root));
    }

    int size() {
        return _size;
    }

    void add(const string &sample) {
        node *v = root;
        for (uchar c : sample) {
            if (!v->next[c]) {
                v->next[c] = new node(_size, v, c);
                nodes.insert(make_pair(_size++, v->next[c]));
            }
            v = v->next[c];
      }
        v->terminal = true;
        v->length = sample.length();
    }

    vector<int> find(const string &text) {
        vector<int> r;
        node *v = root;
        for (int i = 0; i < (int)text.length(); ++i) {
            v = getJump(v, text[i]);
            for (node *u = v; u != root; u = getSuff(u)) {
                if (u->terminal) {
                    r.push_back(i - u->length + 1);
                }
            }
        }
        return r;
    }

    ulll count_possible(int m, set<uchar> a) {
        /*cerr << "size: " << _size << endl;
        cerr << "m_size: " << nodes.size() << endl;

        for (auto p : nodes) {
            cerr << p.first << ' ' << p.second << ' ' << p.second->upchar << endl;
        }*/

        vector<vector<ulll>> d(_size, vector<ulll>(m+1, 0));
        d[0][0] = 1;

        for (int n = 0; n < m; ++n) {
            for (int i = 0; i < _size; ++i) {
                node *v = nodes[i];
                bool f = false;
                for (node *u = v; u != root; u = getSuff(u)) {
                    if (u->terminal) {
                        f = true;
                        break;
                    }
                }
                if (f) continue;
                // d[getUplink(v)->id][n] += d[i][n-1];
                for (uchar c : a) {
                    node *u = getNext(v, c);
                    // cerr << "next for " << v->id << " by " << c << " -> " << u->id << endl;
                    // cerr << c << ' ' << u << endl;
                    d[u->id][n+1] += d[i][n];
                }
            }
        }

        ulll c = 0;
        for (int i = 0; i < _size; ++i) {
            bool f = false;
            for (node *u = nodes[i]; u != root; u = getSuff(u)) {
                if (u->terminal) {
                    f = true;
                    break;
                }
            }
            if (f) continue;
            c += d[i][m];
        }

        /*for (auto v : d) {
            for (auto a : v) {
                cerr << a << ' ';
            }
            cerr << endl;
        }*/

        return c;
    }
};

int main() {
#ifdef FTEST
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#endif
    int n, m, p;
    cin >> n >> m >> p;
    set<uchar> a;
    uchar t;
    for (int i=0; i<n; ++i) {
        cin >> t;
        a.insert(t);
    }

    AhoCorasickTrie trie;
    vector<string> dict;
    string ban;
    for (int i=0; i<p; ++i) {
        cin >> ban;
        trie.add(ban);
    }

    /*for (auto c : a) {
        cerr << "'" << c << "'\n";
    }*/

    /*ulll r = trie.count_possible(m, a);
    string rs;
    while (r) {
        rs = to_string(int(r%1000000000)) + rs;
        r /= 1000000000;
    }*/
    ulll r = trie.count_possible(m, a);
    r.output();

    return 0;
}