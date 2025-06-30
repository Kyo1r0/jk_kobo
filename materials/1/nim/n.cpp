#include <iostream>
#include <unordered_set>
using namespace std;

int calculate_mex(unordered_set<int> &T_set){
    if(T_set.empty()){
             return 0;
    }

    int i=0;
    while(true){
        if(T_set.count(i)==0){
        return i;
        }
    i++;
    };
}



int main()
{
   unordered_set<int> T_set;
    int n,i;
    cout << "入力する数値の個数:" << endl;
    cin >> n;
    cout << n << "個の数値の入力" << endl;
    while(i < n){
        int num;
        cin >> num;
        if(num < 0){
        cout << "入力する数値は非負でお願いします" << endl;
        }
        else{
        T_set.insert(num);
        i++;}
    }

    int mex = calculate_mex(T_set);

    cout << "mexは" << mex << endl;
    cin >> n;
    
}