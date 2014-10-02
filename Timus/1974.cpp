
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
const ll modulus = 1000000007ll;
const int infty = numeric_limits<int>::max();
struct _{_(){ios_base::Init i;ios_base::sync_with_stdio(0);cin.tie(0);}}_;

vector<int> read() {
    int n;
    cin >> n;
    vector<int> tune(n);
    int oct, note, pitch;
    fr(i,n) {
        string s;
        cin >> s;
        oct = s[0]-'0';
        if (s[1] > 'B' &&
            s[1] < 'F') {
            note = (s[1]-'C') * 2;
        } else {
            note = (s[1]>'B' ? s[1]-'C' : s[1]-'C'+7) * 2 - 1;
        }
        if (s.size() > 2) {
            int sign = (s[2]=='+' ? 1 : -1);
            note += sign;
        }
        pitch = 12*oct + note;
        tune[i] = pitch;
    }
    return tune;
}

int similarity(vector<int>::iterator b1, vector<int>::iterator e1,
               vector<int>::iterator b2, vector<int>::iterator e2) {
    int d = 0;
    for (vector<int>::iterator it=b1, jt=b2; it!=e1 && jt!=e2; ++it, ++jt) {
        if (*it == *jt) ++d;
    }
    return d;
}

void solve(vector<int> &ours, vector<vector<int>> &disk) {
    for (auto tune : disk) {
        int n = ours.size();
        int m = tune.size();
        int maxd = 0;
        for (int shift = n-1; shift >= 1-m; --shift) {
            int d = similarity(ours.begin()+shift, ours.end(), tune.begin(), tune.end());
            if (maxd < d){
                maxd = d;
            }
        }
        cout << maxd / (double)m << endl;
    }
}

int main() {
#ifdef FTEST
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#endif
    vector<int> ours = read();
    int m;
    cin >> m;
    vector<vector<int>> disk(m);
    fr(i,m) disk[i] = read();

    // for (auto a : ours) cout << a << ' '; cout << endl;
    // for (auto v : disk) {for (auto a : v) cout << a << ' '; cout << endl;}

    solve(ours, disk);

    return 0;
}
