#include <byte.h>

int32_t get_k_LSB(int32_t key, int32_t k) {
    int32_t mask = (1 << k ) - 1;

    return mask & key;
}
