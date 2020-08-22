#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


int c[101][101];
int mod = 1000000007;

void init()
{
    c[0][0]=1;
    for(int i=1;i<=100;i++){
        c[i][0]=1;
        for(int j=1;j<=100;j++){
            c[i][j] = (c[i-1][j-1]+c[i-1][j])%mod;
        }
    } 
}

int main() {
	int n;
	cin >> n;
	cout << n << endl;
}