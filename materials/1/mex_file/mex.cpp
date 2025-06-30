#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)

string mk_midkakko(vector<int>v){
    int n = v.size();
    string s="{";
    for(int i=0;i<n;i++){
        s+= v[i];
        if(i!=n-1) s+=',';
    }
    s+='}';
    return s;
}

string mk_kakko(string s1,string s2){
    string s= s1 + '(' + s2 +')';
}
string mk_mex(string a){
    string s = "mex"+ '(' + a +')';
    return s;
}
string mk_min(string a){

}

int main() {
    int n,ans=0;
    cout << "数列の個数をいれてください:";
    cin >> n;
    cout << "数列をいれてください:";
    vector<int> a(n);
    for(auto & e:a)cin >> e;
    sort(a.begin(),a.end());
    int fin= a[n-1];
    vector<bool> check(fin,0);
    for(int i=0;i<n;i++){
        check[a[i]]=1;
    }

    for(int i=0;i<=fin;i++){
        if(check[i]==0){
            ans = i;
            break;
        }
        ans = fin+1;
    }
    

    cout << ans << endl;
    return 0;
}