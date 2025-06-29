#include <bits/stdc++.h>
using namespace std;

struct num{ //structを使う根拠はn個のnim和を今後求めたいから classはよくわからないから辞めた
    int n;
    char r_to2[32];
};

void to_2(char vec[32], int n) { //int型網羅するためにvecは32にした
    int index = 0;
    while (n > 0) {
        vec[index] = (n % 2 == 0) ? '0' : '1';
        n /= 2;
        index++;
    }
    vec[index] = '\0'; 
}

void sum( struct num &n3,struct num &n1,struct num &n2){ //n3にn1とn2の和を挿入する それぞれアドレスを取得
    int len1 = strlen(n1.r_to2);
    int len2 = strlen(n2.r_to2);
    int min_len = min(len1, len2);
    int max_len = max(len1, len2);

    
    for (int i = 0; i < min_len; i++) {
        n3.r_to2[i] = (n1.r_to2[i] != n2.r_to2[i]) ? '1' : '0';
    }

    
    for (int i = min_len; i < max_len; i++) {
        if (len1 > len2) {
            n3.r_to2[i] = n1.r_to2[i];
        } else {
            n3.r_to2[i] = n2.r_to2[i];
        }
    }
    n3.r_to2[max_len] = '\0'; 
    n3.n=0;
    for(int i=0;i<max_len;i++){
        if(n3.r_to2[i]=='1')n3.n += std::pow(2, i);
    }
}



int main() {
    int a,b;
    cin >> a >> b;
    struct num a2;
    struct num b2;
    a2.n = a;
    b2.n = b;
    to_2(a2.r_to2, a);
    to_2(b2.r_to2, b);



    struct num c2;
    sum(c2,a2,b2);

    for (int i = strlen(a2.r_to2) - 1; i >= 0; i--) { //a
        int diff = strlen(a2.r_to2) - strlen(b2.r_to2);
        if(i==strlen(a2.r_to2) - 1 &&diff<0){
            for(int j=0;j<diff*-1;j++){
                cout << " ";
            }
        }
        cout << a2.r_to2[i]; 
    }
    cout << endl;

    for (int i = strlen(b2.r_to2) - 1; i >= 0; i--) { //b
        int diff = strlen(a2.r_to2) - strlen(b2.r_to2);
        if(i==strlen(b2.r_to2) - 1 && diff>0){
            for(int j=0;j<diff;j++){
                cout << " ";
            }
        }
        cout << b2.r_to2[i]; 
    }
    cout << endl;


    for (int i = strlen(c2.r_to2) - 1; i >= 0; i--) { //cを新しくつくりa+bの結果をつくる   
        cout << c2.r_to2[i]; 
    }
    cout << endl;

    cout << c2.n << endl;

    return 0;


}