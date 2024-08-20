/*
 To test: g++ -D__TEST_ALLOCARRAY__ allocarray.cc
 
 Time-stamp: <allocarray.cc on Saturday, 8 September, 2012 at 16:02:07 MST (philip)>
 */

#ifndef __ALLOCARRAY_H_INCLUDED__
#define __ALLOCARRAY_H_INCLUDED__

/* Code to allocate multi-dimensional arrays
 Philip A. Pinto
 
 Time-stamp: <allocarray.cc on Saturday, 8 September, 2012 at 14:48:35 MST (philip)>
 
 allocation of 2-, 3-, and 4-d arrays which are addressable as both
 the usual C pointers-to-pointer-to data form or as contiguous
 arrays addressable as 1d offsets with
 index2(i,j) = j + ncol*i
 and
 index3(i,j,k) = k + ndep*j + i*ndep*ncol
 and so on...
 
 (NB: these are still transposed from Fortran form)
 
 Usage:
 double ***a = AllocArray<double>(10,20,20);
 FreeArray(a);
 
 An optional numeric second argument to the template specifies the alignment:
 double **a = AllocArray<double,128>(10,20);
 
 The alignment must be a power of two times sizeof(void *). The minimum value actually used
 for align with a call
 T **a = AllocArray<T, alignment>(10,20);
 will be
 alignment = MAX(8*sizeof(void *), 8*sizeof(type), alignment)
 
 */

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cassert>

#define FreeArray(x) __freearray(&x, #x)

// internal function; should not be called explicitly
template <class T>
T **_AllocArray(long int nrow, int long ncol, size_t align) {
    T **m;
    
    m = new T*[nrow];
    assert( m != NULL);
    
    assert( posix_memalign((void **) &(m[0]), align, nrow*ncol*sizeof(T)) == 0 );
    assert( ((unsigned long int)m[0])%align == 0);
    
    for(int i=1; i<nrow; i++) m[i] = m[i-1] + ncol;
    
    return m;
}

// alignment is given in template
template <class T, size_t alignment>
T **AllocArray(long int nrow, long int ncol) {
    size_t align = 8*std::max(sizeof(T), sizeof(void *));
    align = std::max(align, alignment);
    return _AllocArray<T>(nrow, ncol, align);
}

// alignment is not given; defaults to 8*sizeof(T) or 8*sizeof(void *), whichever is larger
template <class T>
T **AllocArray(long int nrow, long int ncol) {
    size_t align = 8*std::max(sizeof(T), sizeof(void *));
    return _AllocArray<T>(nrow, ncol, align);
}

/* ------------------------------------------------------------------------ */

template <class T>
T ***_AllocArray(long int nrow, long int ncol, long int ndep, size_t align) {
    T ***m;
    
    m = new T**[nrow];
    assert(m != NULL);
    
    m[0] = new T*[nrow*ncol];
    assert(m[0] != NULL);
    
    assert( posix_memalign((void **) &(m[0][0]), align, nrow*ncol*ndep*sizeof(T)) == 0 );
    assert( ((unsigned long int)m[0][0])%align == 0);
    
    for(int j=1; j<ncol; j++) m[0][j] = m[0][j-1] + ndep;
    for(int i=1; i<nrow; i++) {
        m[i] = m[i-1] + ncol;
        m[i][0] = m[i-1][0] + ncol*ndep;
        for(int j=1; j<ncol; j++) m[i][j] = m[i][j-1] + ndep;
    }
    
    return m;
}

template <class T, size_t alignment>
T ***AllocArray(long int nrow, long int ncol, long int ndep) {
    size_t align = 8*std::max(sizeof(T), sizeof(void *));
    align = std::max(align, alignment);
    return _AllocArray<T>(nrow, ncol, ndep, align);
}

template <class T>
T ***AllocArray(long int nrow, long int ncol, long int ndep) {
    size_t align = 8*std::max(sizeof(T), sizeof(void *));
    return _AllocArray<T>(nrow, ncol, ndep, align);
}

/* ------------------------------------------------------------------------ */

template <class T>
T ****_AllocArray(long int nrow, long int ncol, long int ndep, long int nq, size_t align) {
    T ****m;
    
    m = new T***[nrow];
    assert(m != NULL);
    
    m[0] = new T**[nrow*ncol];
    assert(m[0] != NULL);
    
    m[0][0] = new T*[nrow*ncol*ndep];
    assert(m[0][0] != NULL);
    
    assert( posix_memalign((void **) &(m[0][0][0]), align, nrow*ncol*ndep*nq*sizeof(T)) == 0);
    assert( ((unsigned long int)m[0][0][0])%align == 0);
    
    for(int j=1; j<ncol; j++) m[0][j] = m[0][j-1] + ndep;
    for(int i=1; i<nrow; i++) {
        m[i] = m[i-1] + ncol;
        m[i][0] = m[i-1][0] + ncol*ndep;
        for(int j=1; j<ncol; j++) m[i][j] = m[i][j-1] + ndep;
    }
    
    for(int k=1; k<ndep; k++) m[0][0][k] = m[0][0][k-1] + nq;
    for(int j=1; j<ncol; j++) {
        m[0][j][0] = m[0][j-1][0] + nq*ndep;
        for(int k=1; k<ndep; k++) m[0][j][k] = m[0][j][k-1] + nq;
    }
    for(int i=1; i<nrow; i++) {
        m[i][0][0] = m[i-1][0][0] + nq*ndep*ncol;
        for(int k=1; k<ndep; k++) m[i][0][k] = m[i][0][k-1] + nq;
        for(int j=1; j<ncol; j++) {
            m[i][j][0] = m[i][j-1][0] + nq*ndep;
            for(int k=1; k<ndep; k++) m[i][j][k] = m[i][j][k-1] + nq;
        }
    }
    
    return m;
}

template <class T, size_t alignment>
T ****AllocArray(long int nrow, long int ncol, long int ndep, long int nq) {
    size_t align = 8*std::max(sizeof(T), sizeof(void *));
    align = std::max(align, alignment);
    return _AllocArray<T> (nrow, ncol, ndep, nq, align);
}

template <class T>
T ****AllocArray(int nrow, int ncol, int ndep, int nq) {
    size_t align = 8*std::max(sizeof(T), sizeof(void *));
    return _AllocArray<T>(nrow, ncol, ndep, nq, align);
}

/* ------------------------------------------------------------------------ */

template <class T>
void __freearray(T ***m, std::string name) {
    if(*m==(T **)NULL) {
        std::cerr << "attempt to free already-freed 2D array '" << name << "'\n";
        exit(1);
    }
    free(*(m[0]));
    delete[] *m;
    *m = (T **) NULL; // set pointer to null
}

template <class T>
void __freearray(T ****m, std::string name) {
    if(*m==(T ***)NULL) {
        std::cerr << "attempt to free already-freed 3D array '" << name << "'\n";
        exit(1);
    }
    free(*(m[0][0]));
    delete[] *(m[0]);
    delete[] *m;
    *m = (T ***) NULL;
}

template <class T>
void __freearray(T *****m, std::string name) {
    if(*m==(T ****)NULL) {
        std::cerr << "attempt to free already-freed 4D array '" << name << "'\n";
        exit(1);
    }
    free(*(m[0][0][0]));
    delete[] *(m[0][0]);
    delete[] *(m[0]);
    delete[] *m;
    *m = (T ****) NULL;
}
#endif // __ALLOCARRAY_H_INCLUDED__

#ifdef __TEST_ALLOCARRAY__
using namespace std;

#include <iostream>
#include "threevector.cc"

template <typename T>
int alignment(T a) {
    int i=1;
    while((unsigned long int)a%i == 0) i*=2;
    return i/2;
}

struct big {
    double x, y, z, q;
};

long int map(long int i, long int j) {
    return i + 1000L*j;
}

long int map(long int i, long int j, long int k) {
    return i + 1000L*j + 1000000L*k;
}

long int map(long int i, long int j, long int k, long int l) {
    return i + 1000L*j + 1000000000L*k;
}

ThreeVector<long int> map3v(long int i, long int j, long int k) {
    return ThreeVector<long int>(i,j,k);
}

void test2d(int n1, int n2) {
    
    long int **a = AllocArray<long int>(n1, n2);
    long int *onea = a[0];
    
    for(int i=0; i<n1; i++) {
        for(int j=1; j<n2; j++) {
            a[i][j] = map(i,j);
        }
    }
    
    for(int i=0; i<n1; i++) {
        for(int j=1; j<n2; j++) {
            assert( a[i][j] == map(i,j) );
        }
    }
    
    for(int i=0; i<n1; i++) {
        for(int j=1; j<n2; j++) {
            assert( onea[j + i*n2] == map(i,j) );
        }
    }
    
    FreeArray(a);
}

void test3d(int n1, int n2, int n3) {
    
    long int ***a = AllocArray<long int>(n1, n2, n3);
    long int *onea = a[0][0];
    
    for(int i=0; i<n1; i++) {
        for(int j=1; j<n2; j++) {
            for(int k=0; k<n3; k++) {
                a[i][j][k] = map(i,j,k);
            }
        }
    }
    
    for(int i=0; i<n1; i++) {
        for(int j=1; j<n2; j++) {
            for(int k=0; k<n3; k++) {
                assert( a[i][j][k] == map(i,j,k) );
            }
        }
    }
    
    for(int i=0; i<n1; i++) {
        for(int j=1; j<n2; j++) {
            for(int k=0; k<n3; k++) {
                assert( onea[k + j*n3 + i*n2*n3] == map(i,j,k) );
            }
        }
    }
    
    FreeArray(a);
}

void test4d(int n1, int n2, int n3, int n4) {
    
    long int ****a = AllocArray<long int>(n1, n2, n3, n4);
    long int *onea = a[0][0][0];
    
    for(int i=0; i<n1; i++) {
        for(int j=1; j<n2; j++) {
            for(int k=0; k<n3; k++) {
                for(int l=0; l<n4; l++) {
                    a[i][j][k][l] = map(i,j,k,l);
                }
            }
        }
    }
    
    for(int i=0; i<n1; i++) {
        for(int j=1; j<n2; j++) {
            for(int k=0; k<n3; k++) {
                for(int l=0; l<n4; l++) {
                    assert( a[i][j][k][l] == map(i,j,k,l) );
                }
            }
        }
    }
    
    for(int i=0; i<n1; i++) {
        for(int j=1; j<n2; j++) {
            for(int k=0; k<n3; k++) {
                for(int l=0; l<n4; l++) {
                    assert( onea[l + k*n4 + j*n3*n4 + i*n2*n3*n4] == map(i,j,k,l) );
                }
            }
        }
    }
    
    FreeArray(a);
}

void test3d3v(int n1, int n2, int n3) {
    ThreeVector<long int> ***a = AllocArray<ThreeVector<long int>, 256>(n1, n2, n3);
    ThreeVector<long int> *onea = a[0][0];
    
    for(int i=0; i<n1; i++) {
        for(int j=1; j<n2; j++) {
            for(int k=0; k<n3; k++) {
                a[i][j][k] = map3v(i,j,k);
            }
        }
    }
    
    for(int i=0; i<n1; i++) {
        for(int j=1; j<n2; j++) {
            for(int k=0; k<n3; k++) {
                assert( a[i][j][k] == map3v(i,j,k) );
            }
        }
    }
    
    for(int i=0; i<n1; i++) {
        for(int j=1; j<n2; j++) {
            for(int k=0; k<n3; k++) {
                assert( onea[k + j*n3 + i*n2*n3] == map3v(i,j,k) );
            }
        }
    }
    
    FreeArray(a);
}

int main() {
    
    for(int i=0; i<100; i++) {
        char **q = AllocArray<char, 256>(10,15);
        assert( alignment(&(q[0][0])) >= 256 );
        FreeArray(q);
        assert(q==0);
        
        float **a = AllocArray<float>(10,15);
        assert( alignment(&(a[0][0])) >= 64 );
        FreeArray(a);
        assert(a==0);
        
        double **b = AllocArray<double>(10,15);
        assert( alignment(&(b[0][0])) >= 64 );
        FreeArray(b);
        assert(b==0);
        
        double **c = AllocArray<double, 256>(10,15);
        assert( alignment(&(c[0][0])) >= 256 );
        FreeArray(c);
        assert(c==0);
        
        big **d = AllocArray<big>(10,15);
        assert( alignment(&(d[0][0])) >= 256 );
        FreeArray(d);
        assert(d==0);
        
        big **e = AllocArray<big, 512>(10,15);
        assert( alignment(&(e[0][0])) >= 512 );
        FreeArray(e);
        assert(e==0);
        
        test2d(10,8);
        test3d(100,80,120);
        test4d(15,21,17,13);
        
        ThreeVector<long int> ***array = AllocArray<ThreeVector<long int>, 256>(4, 6, 9);
        FreeArray(array);
        assert( array == 0 );
    }
    
    std::cout << " all done.\n";
}
#endif