#include <bits/stdc++.h>
using namespace std;


void to_2(char vec[32], int n) { //int型網羅するためにvecは32にした
    int index = 0;
    while (n > 0) {
        vec[index] = (n % 2 == 0) ? '0' : '1';
        n /= 2;
        index++;
    }
    vec[index] = '\0'; 
}

struct num{ //structを使う根拠はn個のnim和を今後求めたいから classはよくわからないから辞めた
    int n;
    char r_to2[32];
};


int main() {
    int a,b;
    cin >> a >> b;
    struct num a2;
    struct num b2;
    a2.n = a;
    b2.n = b;
    to_2(a2.r_to2, a);
    to_2(b2.r_to2, b);

     for (int i = strlen(a2.r_to2) - 1; i >= 0; i--) {
        cout << a2.r_to2[i]; 
    }
    cout << endl;

    for (int i = strlen(b2.r_to2) - 1; i >= 0; i--) {
        cout << b2.r_to2[i]; 
    }
    cout << endl;

    return 0;


}