#include <vector>
#include <cstdio>
#include <cmath>
#define ABS(x) (x < 0? -1*x : x)
#define SIZEPS 46342
#define SIZE 100002
using namespace std;

bool isPrime[SIZEPS/2];
vector <int> nPrime;
void primeSieve(int n)
{
    nPrime.push_back(2);

    int limit = sqrt(n+0.0) + 2;
    for(int i = 3;i <= n;i += 2){
        if( !isPrime[(i+1)/2] ){
            nPrime.push_back(i);
            if(i < limit){
                for(int j = i*i;j <= n;j += (i*2) ){
                    isPrime[(j+1)/2] = 1;
                }
            }
        }
    }
}

int segmentedPrimeSieve(int a,int b,bool isNotPrimeAB[]){
    if(b == 1) return 0;

    int Size = b - a + 1,Count = 0;
    int limit = sqrt(b*1.0);

    if(a == 1) isNotPrimeAB[0] = true;

    for(int i = 0;nPrime[i] <= limit;i++){
        int start = ceil(a/(nPrime[i]+0.0))*nPrime[i];

        if(nPrime[i] == start)
            start = start + nPrime[i] - a;
        else
            start = start - a;

        for(int j = start;j < Size;j += nPrime[i]){
            isNotPrimeAB[j] = true;
        }
    }
    for(int i = 0;i < Size;i++)
        if(!isNotPrimeAB[i]) Count++;

    return Count;
}
int main() {
    primeSieve(SIZEPS);
    int a,b;
    scanf("%d%d", &a,&b);
    bool isNotPrime[SIZE] = {0};
    cout << segmentedPrimeSieve(a,b,isNotPrime) << endl;
    return 0;
}
