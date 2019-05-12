#ifndef MACHINE_H_INCLUDED
#define MACHINE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct Instruction
{
    int Etat1;
    char lettre;
    int Etat2;
}Instruction;

void allouer(Instruction** nouveau);

void liberer(Instruction** ancien);

void aff_Etat1(Instruction* p,int q);

void aff_Etat2(Instruction* p,int q);

void aff_Lettre(Instruction* p, char l);

int valEtat1(Instruction* p);

int valEtat2(Instruction* p);

char valLettre(Instruction* p);





#endif // FONCTIONS_H_INCLUDED
