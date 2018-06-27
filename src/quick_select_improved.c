#include <stdio.h>

// フェルマー素数
#define N ((1<<16)+1)

int A[N];

/*
 A[0], A[1], ..., A[n-1] の中でk+1番目に小さい値を返す関数
 ただし、Aの中身は書き換えてしまう。
 */
int quick_select(int A[], int n, int k){
    int i, j, pivot;
    int numpivot=1;
    // 先頭の要素をピボットとする
    pivot = A[0];
    for(i = j = 1; i < n; i++){
        if(A[i] < pivot){
            int z = A[j];
            A[j] = A[i];
            A[i] = z;
            j++;
        }
    }
    if(j>1){
        A[0]=A[j-1];
        A[j-1]=pivot;
    }
    for(i=j;i<n;i++)if(A[i]==pivot){A[i]=A[j-1+numpivot];A[j-1+numpivot]=pivot;numpivot++;}
    if(j+numpivot-1 < k+1)return quick_select(A+j+numpivot-1, n-(j+numpivot-1), k-(j+numpivot-1));
    if(j>k+1)return quick_select(A, j-1, k);
    return pivot;
}

int main(){
    int i;
    A[0] = 0;
    A[1] = 3; //原始元
    for(i=2;i<N;i++){
         A[i] = (long long int) A[i-1] * A[1] % N;
        //A[i]=3;
    }
    for(i=0;i<N;i++){
        // if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
        printf("%d th element is %d\n", i, quick_select(A, N, i));
    }
    return 0;
}

