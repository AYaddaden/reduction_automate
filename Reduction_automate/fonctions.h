#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

#include "./machine/machine.h"
#define max 40


void alphabet(int n, char* tabl);

void isFinal(int *tab, int n,int *nbFinal);

void Inst(int nbInst, Instruction* tabInst, int nbEtat, int nbAlph, char* Alpha );

int verif(int taille, Instruction *tabInst, Instruction *inst);

int verifEtat(int nbEtat, int etat);

int verifLettre(char *Tab, int taille, char lettre);

int verifMot(char *mot, Instruction *tab,int nbInst, int* tabFinal,int nbFinal,char* trace );

int RechInst(int EtatDep, char lettre,int nbInst, Instruction *tab);

int estFinal(int *tabFinal, int taille, int etat);

void accessible(Instruction* tabInst, int taille,char* Alpha, int* EtatAcces, int* nbAcces);

void Coaccessible(Instruction* tabInst, int nbInst, int* EtatFinal, int nbFinal, int* EtatCoacc, int* nbCoacc);

int rech(int *tab, int taille, int val);

void rechDep(int EtatArv, Instruction* tabInst, int nbInst, int* tabEtat, int *taille);

void intersection(int *tab1, int taille1, int* tab2, int taille2, int* intersec,int *taille);

void tabInstR(Instruction* tabInst, int nbInst,int* tabEtat, int nbEtat, Instruction* tabInstRed, int* nbInstRed);

void AlphaR(Instruction* tabInst, int nbInst, char* Alpha, char* AlphaRed);

void tabFinalR(int* tabEtat,int nbEtat,int* tabFinal, int nbFinal,int* tabFinalRed,int* nbFinalRed);

void menu();

#endif // FONCTIONS_H_INCLUDED
