#include <iostream>
#include <vector>
#include <pthread.h>

#define TREAD_NUM 8

pthread_mutex_t mutexFuel;

double res = 0;
std::vector<double>coef(3);
std::vector<int> pow(3);
int n = 3;
double west = 0, east = 0, start = 0, finish = 0, size = 0.01;

void* count_space(void* args) {
    pthread_mutex_lock(&mutexFuel);
    pthread_mutex_lock(&mutexFuel);
    for (double i = start; i < finish; i += size) {
        double height = 0;
        for (size_t j = 0; j < coef.size(); ++j) {
            if (pow[j] == 2) {
                height += coef[j] * i * i;
            } 
            if (pow[j] == 1) {
                height += coef[j] * i;
            }
            if (pow[j] == 0) {
                height += coef[j];
            }           
        }
        std::cout << i << "\n";
        // std::cout << (l - height) << " ";
        res += (west - height) * size;
    }
    pthread_mutex_unlock(&mutexFuel);
    pthread_mutex_unlock(&mutexFuel);
}


int main(){
    std::cout << "Write length of west, east and north border:\n";
    std::cin >> west >> east >> north;
    // We will think that f(x) is a ratioanal function 
    // Where the main element is in the power of n

    std::cout << "Write 3 coefficients: "<< "\n";
    for (size_t i = 0; i < n + 1; ++i) {
        std::cin >> coef[i];
    }
    for (size_t i = 0; i < n; ++i) {
        pow[i] = (n - 1 -i);
    }
    std::cout << "\n";
    std::cout << "result: \n";


    pthread_t th[TREAD_NUM];
    pthread_mutexattr_t recursiveMutexAttributes;
    pthread_mutexattr_init(&recursiveMutexAttributes);
    pthread_mutexattr_settype(&recursiveMutexAttributes, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mutexFuel, &recursiveMutexAttributes);

    int i;
    for (int i = 0; i < TREAD_NUM; ++i) {
        if (pthread_create(&th[i], NULL, count_space, NULL) != 0) {
            perror("Failed to create thread");
        }
    }

    
    std::cout << res << "\n";
    
    pthread_mutexattr_destroy(&recursiveMutexAttributes);
    pthread_mutex_destroy(&mutexFuel);

    return 0;
}
