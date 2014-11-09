
/*
 * “Doktor! Are you sure this will work?!”
 * “Ha-ha! I have NO IDEA!”
 */

/*
 * short     2^15-1 ~ 3e4
 * int       2^31-1 ~ 2e9
 * long x86  2^31-1 ~ 2e9
 * long long 2^63-1 ~ 9e18
 */

#include <bits/stdc++.h>
#define x first
#define y second
#define pb push_back
#define mp make_pair
#define fr(a,b) for (int a=0; a<b; ++a)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll mod = 1000000007ll;
const int infty = numeric_limits<int>::max();
struct _{_(){ios_base::Init i;ios_base::sync_with_stdio(0);cin.tie(0);}}_;

#define A_SIZE 28
#define A '?'

vector<int> getSuff(string &s) {
    int n = s.length();
    vector<int> p(n);
    vector<int> c(n);
    vector<int> count(A_SIZE);

    for (char a : s) {
        ++count[a-A];
    }
    for (int i = 1; i < A_SIZE; ++i) {
        count[i] += count[i-1];
    }
    for (int i = 0; i < n; ++i) {
        p[--count[s[i]-A]] = i;
    }
    c[p[0]] = 0;
    int lastclass = 0;
    for (int i = 1; i < n; ++i) {
        if (s[p[i]] != s[p[i-1]]) {
            ++lastclass;
        }
        c[p[i]] = lastclass;
    }

    vector<int> pn(n);
    vector<int> cn(n);
    for (int k = 0; (1<<k) < n; ++k) {
        for (int i = 0; i < n; ++i) {
            pn[i] = p[i] - (1<<k);
            if (pn[i] < 0) {
                pn[i] += n;
            }
        }
        count = vector<int>(lastclass+1);
        for (int i = 0; i < n; ++i) {
            ++count[c[pn[i]]];
        }
        for (int i = 1; i < lastclass+1; ++i) {
            count[i] += count[i-1];
        }
        for (int i = n-1; i >= 0; --i) {
            p[--count[c[pn[i]]]] = pn[i];
        }
        cn[p[0]] = 0;
        lastclass = 0;
        for (int i = 1; i < n; ++i) {
            int m1 = (p[i] + (1<<k)) % n;
            int m2 = (p[i-1] + (1<<k)) % n;
            if (c[p[i]] != c[p[i-1]] || c[m1] != c[m2]) {
                ++lastclass;
            }
            cn[p[i]] = lastclass;
        }
        c = cn;
    }
    return p;
}

vector<int> getLcp(string &s, vector<int> suff) {
    int n = s.length();
    vector<int> lcp(n);
    vector<int> pos(n);
    fr(i,n) pos[suff[i]] = i;
    int k = 0;
    fr(i,n) {
        if (k > 0) --k;
        if (pos[i] == n-1) {
            lcp[n-1] = -1;
            k = 0;
        } else {
            int j = suff[pos[i] + 1];
            while (max(i+k, j+k) < n && s[i+k] == s[j+k]) {
                k++;
            }
            lcp[pos[i]] = k;
        }
    }
    return lcp;
}

string lcs(string &s, string &t) {
    int n = s.length();
    string u = s + "@" + t + "?";
    vector<int> suff = getSuff(u);
    vector<int> lcp = getLcp(u, suff);
    int max = 0;
    for (int i = 0; i < (int)lcp.size()-1; ++i) {
        if (((suff[i] < n && suff[i+1] > n) ||
             (suff[i] > n && suff[i+1] < n)) &&
            lcp[max] < lcp[i]) {
            max = i;
        }
    }
    int r = suff[max];
    while (u[r] != '@' && u[r] != '?' && r < suff[max]+lcp[max]) ++r;
    return string(u.begin()+suff[max], u.begin()+r);
}

int main() {
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;;
    cout << lcs(s, t) << endl;
    return 0;
}
