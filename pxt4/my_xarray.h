#ifndef MY_XARRAY_H
#define MY_XARRAY_H

#include <linux/xarray.h>

struct my_xarray {
    struct xarray xarr;
};

unsigned long long globalPlus1(unsigned long long *total_count);
void initialize_xarray(struct my_xarray *my_xarr);
void insert_data(struct my_xarray *my_xarr, int key, int value);
int retrieve_data(struct my_xarray *my_xarr, int key);
void remove_data(struct my_xarray *my_xarr, int key);
void cleanup_xarray(struct my_xarray *my_xarr);

#endif

