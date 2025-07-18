#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)

string input_s(){
    string s;
    cout << "ドミノをいれてください(W,Bのみで)" << endl; 
    cin >> s;

    for(char &e:s) if(&e!="W"||&e!="B") {
        cout << "W,B以外の文字は入れないでください" << endl;
        string new_s = input_s();
        s = new_s;
    }
    return s;
}



int main() {
    string s = input_s();
    return 0;
}