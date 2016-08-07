#include <iostream>

using namespace std;
void countingSort(int[]);
int main() {
    int a[] {9,8,7,6,5,4,3,2,1};
    countingSort(a);
    for (int i : a) {
        cout<<i<<" ";
    }
    return 0;
}
void countingSort(int a[]) {
    size_t length = sizeof(a) / sizeof(int);
    int c[length] ;
    int b[length];
    for (int i = 0; i < length; ++i) {
        c[i] = 0;
    }

    /*
     * count how many
     */
    for (int i = 0; i < length; ++i) {
        c[a[i]]++;
    }
    /*
     * count how many less than
     */
    for (int i = 1; i < length; ++i) {
        c[i] += c[i-1];
    }
    /*
     * sort
     */
    for (int i = length - 1; i >=0 ; i--) {
        b[--c[a[i]]] = a[i];
        //c[a[i]];
    }
    /*
     * copy back
     */
    for (int i = length - 1; i >=0 ; i--) {
        a[i] = b[i];
    }
}