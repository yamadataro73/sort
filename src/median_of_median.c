#include <stdio.h>

// フェルマー素数
#define N ((1<<16)+1)

int A[N];

/*
 A[0], A[1], ..., A[n-1] の中でk+1番目に小さい値を返す関数
 ただし、Aの中身は書き換えてしまう。
 */
int quick_select(int A[], int n, int k){
    if(n<=5){
        for(int l=0;l<n;l++)for(int m=1;m<n;m++)if(A[m-1]>A[m]){int z=A[m];A[m]=A[m-1];A[m-1]=z;}
        return A[k];
    }
    
    int i, j, pivot;
    int bunkatu=(n+4)/5;
    int Aprime[bunkatu];
    for(i=0;i<bunkatu;i++)Aprime[i]=quick_select(A+5*i,5*bunkatu>n?n%5:5 , (5*bunkatu>n?n%5:5)/2);
    // 先頭の要素をピボットとする
    pivot = quick_select(Aprime,bunkatu,bunkatu/2);
    for(i=0;i<n;i++)if(A[i]==pivot){A[i]=A[0];A[0]=pivot;break;}
    
    for(i = j = 1; i < n; i++){
        if(A[i] <= pivot){
            int z = A[j];
            A[j] = A[i];
            A[i] = z;
            j++;
        }
    }
    
    
    if(j == k+1) return pivot;
    else if(j < k+1) return quick_select(A+j, n-j, k-j);
    else return quick_select(A+1, j-1, k);
}

int main(){
    int i;
    A[0] = 0;
    A[1] = 3; //原始元
    for(i=2;i<N;i++){
        A[i] = (long long int) A[i-1] * A[1] % N;
    }
    for(i=0;i<N;i++){
        // if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
        printf("%d th element is %d\n", i, quick_select(A, N, i));
    }
}
