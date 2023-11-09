#include "my_xarray.h"

unsigned long long globalPlus1(unsigned long long *total_count)
{
    __sync_fetch_and_add(total_count, 1);
    return *total_count;
}


void initialize_xarray(struct my_xarray *my_xarr) {
    xa_init(&my_xarr->xarr);
}

void insert_data(struct my_xarray *my_xarr, int key, int value) {
    xa_store(&my_xarr->xarr, key, &value, GFP_KERNEL);
}

int retrieve_data(struct my_xarray *my_xarr, int key) {
    int *value = xa_load(&my_xarr->xarr, key);
    if (value) {
        return *value;
    } else {
        return -1; // 데이터가 없을 때
    }
}

void remove_data(struct my_xarray *my_xarr, int key) {
    xa_erase(&my_xarr->xarr, key);
}

void cleanup_xarray(struct my_xarray *my_xarr) {
    xa_destroy(&my_xarr->xarr);
}  
