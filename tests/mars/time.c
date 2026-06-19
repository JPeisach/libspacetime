#include <libspacetime/earth.h>
#include <libspacetime/mars.h>
#include <stdio.h>
#include <time.h>

int main() {
    time_t time = earth_time();

	mars_time_t mt = mars_time();

    time_t mt_reconv = mars_time_to_earth_time(mt);

    printf("TODO: conversion is off by about one earth second");
    if((mt_reconv - time) < 1) return 0;

    return -1;
}
