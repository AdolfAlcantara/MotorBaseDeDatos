//
// Created by Chronos-Laptop on 2/9/2017.
//

#include <cstring>
#include "Idx_Entry.h"
Idx_Entry::Idx_Entry()
{
    strncpy(id,"", sizeof(id)-1);
    id[19]= '\0';
    numeroBloque=-1;
    numeroRegRel=-1;
}
Idx_Entry::Idx_Entry(int nb, int nrr, char *n)
{
    strncpy(id,n, sizeof(id)-1);
    id[19] ='\0';
    numeroBloque=nb;
    numeroRegRel=nrr;

}


Idx_Entry::~Idx_Entry()
{

}
