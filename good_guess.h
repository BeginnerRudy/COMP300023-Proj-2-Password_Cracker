/*************************** HEADER FILES ***************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "brute_force.h"

/****************************** MACROS ******************************/
#define TO_UPPER_PROB 0.07

// This is the cummulative density function table, which would be used in good guess
#define _e 0.095388
#define _a 0.088034 + _e
#define _r 0.067375 + _a
#define _o 0.066070 + _r
#define _n 0.062320 + _o
#define _i 0.061211 + _n
#define _s 0.058227 + _i
#define _t 0.050254 + _s
#define _l 0.049439 + _t
#define _c 0.033915 + _l
#define _d 0.032888 + _c
#define _m 0.031828 + _d
#define _h 0.028877 + _m
#define _g 0.026284 + _h
#define _b 0.025975 + _g
#define _u 0.025502 + _b
#define _p 0.024099 + _u
#define _1 0.022029 + _p
#define _y 0.021751 + _1
#define _k 0.017691 + _y
#define _f 0.014234 + _k
#define _w 0.013762 + _f
#define _2 0.009587 + _w
#define _v 0.009424 + _2
#define _j 0.007337 + _v
#define _3 0.006473 + _j
#define _z 0.006098 + _3
#define _0 0.005984 + _z
#define _4 0.0054624 + _0
#define _5 0.005348 + _4
#define _9 0.005234 + _5
#define _6 0.005038 + _9
#define _x 0.005022 + _6
#define _7 0.004484 + _x
#define _8 0.003587 + _7
#define _q 0.003081 + _8
#define star 0.000244 + _q
#define question_mark 0.000179 + star


/*********************** FUNCTION PROTOTYPES ***********************/
void guess(int total_num_guesses);
char pick_char(double num);
char randomly_converting(char character);
char choose_from_special();
char* generate_guess(int len_of_pwd);
