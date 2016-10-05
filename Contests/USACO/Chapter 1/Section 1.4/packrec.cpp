/*
ID: b0002141
PROG: packrec
LANG: C++
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct Rect Rect;
struct Rect {
    int wid;
    int ht;
};

Rect
rotate(Rect r)
{
    Rect nr;

    nr.wid = r.ht;
    nr.ht = r.wid;
    return nr;
}

int
max(int a, int b)
{
    return a > b ? a : b;
}

int
min(int a, int b)
{
    return a < b ? a : b;
}

int tot;
int bestarea;
int bestht[101];

void
record(Rect r)
{
    int i;

    if(r.wid*r.ht < tot)
        *(long*)0=0;

    if(r.wid*r.ht < bestarea || bestarea == 0) {
        bestarea = r.wid*r.ht;
        for(i=0; i<=100; i++)
            bestht[i] = 0;
    }
    if(r.wid*r.ht == bestarea)
        bestht[min(r.wid, r.ht)] = 1;
}

void
check(Rect *r)
{
    Rect big;
    int i;

    /* schema 1: all lined up next to each other */
    big.wid = 0;
    big.ht = 0;
    for(i=0; i<4; i++) {
        big.wid += r[i].wid;
        big.ht = max(big.ht, r[i].ht);
    }
    record(big);

    /* schema 2: first three lined up, fourth on bottom */
    big.wid = 0;
    big.ht = 0;
    for(i=0; i<3; i++) {
        big.wid += r[i].wid;
        big.ht = max(big.ht, r[i].ht);
    }
    big.ht += r[3].ht;
    big.wid = max(big.wid, r[3].wid);
    record(big);

    /* schema 3: first two lined up, third under them, fourth to side */
    big.wid = r[0].wid + r[1].wid;
    big.ht = max(r[0].ht, r[1].ht);
    big.ht += r[2].ht;
    big.wid = max(big.wid, r[2].wid);
    big.wid += r[3].wid;
    big.ht = max(big.ht, r[3].ht);
    record(big);

    /* schema 4, 5: first two rectangles lined up, next two stacked */
    big.wid = r[0].wid + r[1].wid;
    big.ht = max(r[0].ht, r[1].ht);
    big.wid += max(r[2].wid, r[3].wid);
    big.ht = max(big.ht, r[2].ht+r[3].ht);
    record(big);

    /*
     * schema 6: first two pressed next to each other, next two on top, like:
     * 2 3
     * 0 1
     */
    big.ht = max(r[0].ht+r[2].ht, r[1].ht+r[3].ht);
    big.wid = r[0].wid + r[1].wid;

    /* do 2 and 1 touch? */
    if(r[0].ht < r[1].ht)
        big.wid = max(big.wid, r[2].wid+r[1].wid);
    /* do 2 and 3 touch? */
    if(r[0].ht+r[2].ht > r[1].ht)
        big.wid = max(big.wid, r[2].wid+r[3].wid);
    /* do 0 and 3 touch? */
    if(r[1].ht < r[0].ht)
        big.wid = max(big.wid, r[0].wid+r[3].wid);

    /* maybe 2 or 3 sits by itself */
    big.wid = max(big.wid, r[2].wid);
    big.wid = max(big.wid, r[3].wid);
    record(big);
}

void
checkrotate(Rect *r, int n)
{
    if(n == 4) {
        check(r);
        return;
    }

    checkrotate(r, n+1);
    r[n] = rotate(r[n]);
    checkrotate(r, n+1);
    r[n] = rotate(r[n]);
}

void
checkpermute(Rect *r, int n)
{
    Rect t;
    int i;

    if(n == 4)
        checkrotate(r, 0);

    for(i=n; i<4; i++) {
        t = r[n], r[n] = r[i], r[i] = t;    /* swap r[i], r[n] */
        checkpermute(r, n+1);
        t = r[n], r[n] = r[i], r[i] = t;    /* swap r[i], r[n] */
    }
}

int
main(void)
{
    FILE *fin, *fout;
    Rect r[4];
    int i;

    fin = fopen("packrec.in", "r");
    fout = fopen("packrec.out", "w");
    assert(fin != NULL && fout != NULL);

    for(i=0; i<4; i++)
        fscanf(fin, "%d %d", &r[i].wid, &r[i].ht);

    tot=(r[0].wid*r[0].ht+r[1].wid*r[1].ht+r[2].wid*r[2].ht+r[3].wid*r[3].ht);

    checkpermute(r, 0);
    fprintf(fout, "%d\n", bestarea);
    for(i=0; i<=100; i++)
        if(bestht[i])
            fprintf(fout, "%d %d\n", i, bestarea/i);
    return(0);
}


