#include <stdio.h>
#include <stdlib.h>
#include "./machine.h"



void allouer(Instruction** nouveau)
{
    *nouveau=(Instruction*) malloc(sizeof(Instruction));
}

void liberer(Instruction** ancien)
{
    free(*ancien); *ancien=NULL;
}

void aff_Etat1(Instruction* p,int q)
{
    p->Etat1=q;
}

void aff_Etat2(Instruction* p,int q)
{
    p->Etat2=q;
}

void aff_Lettre(Instruction* p, char l)
{
    p->lettre=l;
}

int valEtat1(Instruction* p)
{
    return p->Etat1;
}

int valEtat2(Instruction* p)
{
    return p->Etat2;
}

char valLettre(Instruction* p)
{
    return p->lettre;
}



