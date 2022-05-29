#ifndef SAMPLE_H
# define SAMPLE_H
#include <stdio.h>
#include <stdlib.h>
typedef struct sample
{
	int a;
	char *s;
} s_a;
extern s_a g_m;
extern int count;
int func(void);
#endif