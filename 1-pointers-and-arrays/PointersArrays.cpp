//
// Created by Guillermo Galvez on 08/01/2025.
//


#include <iostream>
using namespace std;

// EXAMPLE 1

/*
int f(int x, int *py, int **ppz) {
    int y, z;
    **ppz += 1;
    z = **ppz;
    *py += 2;
    y = *py;
    x += 3;
    return x + y + z;
}
int main() {
    int c, *b, **a;
    c = 4;
    b = &c;
    a = &b;
    cout << f(c, b, a);
    return 0;
}
 */

// EXAMPLE 2

/*
int main() {
    int ***r, **q, *p, i=8;
    p = &i;
    (*p)++;
    q = &p;
    (**q)++;
    r = &q;
    cout<<*p << " " <<**q << " "<<***r;
    return 0;
}
 */

// EXAMPLE 3

/*
void Q(int z) {
    z += z;
    cout<<z << " ";
}
void P(int *y) {
    int x = *y + 2;
    Q(x);
    *y = x- 1;
    cout<<x << " ";
}
int main() {
    int x = 5;
    P(&x);
    cout<<x;
    return 0;
} */

// EXAMPLE 4

/*
void square(int *p){
    int a = 10;
    p = &a;
    *p = (*p) * (*p);
}
int main(){
    int a = 10;
    square(&a);
    cout << a << endl;
}
 */

// EXAMPLE 5

/*
void increment(int **p) {
    (**p)++;
}
int main(){
    int num = 10;
    int *ptr = &num;
    increment(&ptr);
    cout << num << endl;
}
 */

// EXAMPLE 6

/*
int main(){
    int a = 10;
    int *p = &a;
    int **q = &p;
    int b = 20;
    *q = &b;
    (*p)++;
    cout << a << " " << b << endl;
} */