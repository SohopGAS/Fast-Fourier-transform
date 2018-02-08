//
//  main.cpp
//  FFT_check
//
//  Created by Gal Argov Sofer Sofer on 08/09/17.
//  Copyright © 2017 Gal Argov Sofer. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <complex>

#define MAX 200

using namespace std;

#define M_PI 3.1415926535897932384  // Pi

// Function to calculate the log2(.) of int numbers
int log2(int N)
{
    int k = N, i = 0;
    while(k) {
        k >>= 1;
        i++;
    }
    return i - 1;
}

// Checking if the number of element is a power of 2
int check(int n)
{
    return n > 0 && (n & (n - 1)) == 0;
}

// Calculating reverse number
int reverse(int N, int n)
{
    int j, p = 0;

    for(j = 1; j <= log2(N); j++) {
        if(n & (1 << (log2(N) - j)))
            p |= 1 << (j - 1);
    }
    return p;
}

// Using the reverse order in the array
void ordina(complex<double>* f1, int N)
{
    complex<double> f2[MAX];

    for(int i = 0; i < N; i++)
        f2[i] = f1[reverse(N, i)];

    for(int j = 0; j < N; j++)
        f1[j] = f2[j];
}

// Calculating the fransformation
void transform(complex<double>* f, int N)
{
    ordina(f, N);    // 1.Reverse order
    complex<double> *W;
    int n = 1;
    int a = 0;
    
    W = (complex<double> *)malloc(N / 2 * sizeof(complex<double>));
    W[1] = polar(1., -2. * M_PI / N); // 2. Calculate W(n), it aslo can be: polar(1., 2. * M_PI / N)
    W[0] = 1;
    
    for(int i = 2; i < N / 2; i++)
        W[i] = pow(W[1], i);
    
    a = N / 2;

    for(int j = 0; j < log2(N); j++) {
        for(int i = 0; i < N; i++) {
            if(!(i & n)) {
                complex<double> temp = f[i];
                complex<double> Temp = W[(i * a) % (n * a)] * f[i + n];
                f[i] = temp + Temp;
                f[i + n] = temp - Temp;
            }
        }
        n *= 2;
        a = a / 2;
    }
}

// FFT function
void FFT(complex<double>* f, int N, double d)
{
    transform(f, N);
    for(int i = 0; i < N; i++)
        f[i] *= d; // Multiplying by step
}

int main()
{
    int n;      // Number of elements
    double d;   // Value of w
    complex<double> vec[MAX];

    do {
        cout << "Specify array dimension (MUST be power of 2): ";
        cin >> n;
    } while(!check(n));

    cout << "Specify sampling step (1 is default): "; // Just write 1 in order to have the same results of matlab fft(.)
    cin >> d;
    cout << "Specify the array" << endl;
    
    for(int i = 0; i < n; i++) {
        cout << "Specify element number " << i <<": ";
        cin >> vec[i];
    }
    
    FFT(vec, n, d);
    
    cout << "Printing the FFT of the array specified:" << endl;
    
    for(int j = 0; j < n; j++)
        cout << vec[j] << endl;
    
    return 0;
}
