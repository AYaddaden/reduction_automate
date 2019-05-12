#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "./machine/machine.h"
#include <string.h>



void menu()
{
    printf("Le menu:\n\n");
    printf("\t1) Construire l'automate\n");
    printf("\t2) Voir l'automate\n");
    printf("\t3) Tester un mot\n");
    printf("\t4) Reduire l'automate\n");
    printf("\t5) Voir l'automate reduit\n");
    printf("\t0) Sortir\n\n\tVotre choix: ");
}
/*

*/
void alphabet(int n, char* tabl)
{
    int i=0;
    int j=0;
    int trouv=0;

    for(i=0;i<n;i++)
    {
       do{
            getchar();
            scanf("%c",&tabl[i]);
            //c=tabl[i];
            trouv=0;
            j=0;
            while((j<i) && !trouv)
            {
                //printf("recherche\n");
                if (tabl[i]==tabl[j])
                {
                    trouv=1;
                }
                else j++;
            }
            if (trouv)
            {
                printf("Ce caractere existe deja, entrez un autre different\n");
            }
        }while(trouv);
    }
}

void isFinal(int *tab, int n,int *nbFinal)
{
    int i=0;
    int j=0;
    char rep;
    *nbFinal=0;
    for(i=0;i<n;i++)
    {
            getchar();
            printf("Est-ce que l'etat S%d est final? (o/n)",i);
            scanf("%c",&rep);
            //printf("rep=%c\n",tolower(rep));
            if(tolower(rep)=='o')
            {

                tab[j]=i;
                j++;
            }
    }
    *nbFinal=j;
}

void Inst(int nbInst, Instruction* tabInst, int nbEtat, int nbAlph, char* Alpha )
{
    int i=0;
    int etatDep=0;
    int etatArv=0;
    char lettre;
    Instruction *inst=NULL;
    allouer(&inst);
    int exist=1;
    int appartient=0;
    for(i=0;i<nbInst;i++)
    {
        printf("Nouvelle instruction:\n");
        exist=1;
        while(exist)
       {
            appartient=0;
            while (!appartient)
            {
                getchar();
                printf("Etat de depart: S");
                scanf("%d",&etatDep);
                appartient=verifEtat(nbEtat,etatDep);
                if (!appartient)
                {
                    printf("Cet etat n'existe pas dans la table des etats!\n");
                }
            }
            appartient=0;
            while(!appartient)
            {
                getchar();
                printf("Lettre: ");
                scanf("%c", &lettre);
                appartient=verifLettre(Alpha,nbAlph,lettre );
                if (!appartient)
                {
                    printf("Cette lettre ne fait pas partie de l'alphabet!\n");
                }
            }
            appartient=0;
            while(!appartient)
            {
                getchar();
                printf("Etat d'arrivee: S");
                scanf("%d",&etatArv);
                appartient=verifEtat(nbEtat,etatArv);
                    if (!appartient)
                    {
                        printf("Cet etat n'existe pas dans la table des etats!\n");
                    }
            }
            //getchar();

            aff_Etat1(inst,etatDep);
            aff_Etat2(inst,etatArv);
            aff_Lettre(inst,lettre);
            exist=verif(i,tabInst, inst);
            if (!exist)
            {
                tabInst[i]=*inst;
                //printf("Inseree\n");
            }
            else {
                printf("Instruction deja existante\n");
            }
        }
    }
}

int verif(int taille, Instruction *tabInst, Instruction *inst)
{
    //printf("verification\n");
    int trouv=0;
    int i=0;
    while ((!trouv) && (i<taille))
    {
        if (valEtat1(&tabInst[i])==valEtat1(inst))
        {
            if(valLettre(&tabInst[i])==valLettre(inst)){
                //printf("Même lettre\n");
                trouv=1;
            }
            else{
                if (valEtat2(&tabInst[i])==valEtat2(inst)){
                    //printf("meme destination\n");
                    trouv=1;
                }
            }
        }
            //printf("au suivant\n");
            i++;
    }
    //printf("fin de vérification\n");
    return trouv;
}

int verifEtat(int nbEtat, int etat)
{
    int trouv=0;
    if ((etat>=0) && (etat<nbEtat))
    {
    trouv=1;
    }
    return trouv;
}

int verifLettre(char *Tab, int taille, char lettre)
{
    int i=0;
    int trouv=0;
    while((!trouv) && (i<taille))
    {
        if (Tab[i]==lettre)
        {
            trouv=1;
        }
        else i++;
    }
    return trouv;
}

int verifMot(char *mot, Instruction *tab,int nbInst, int* tabFinal,int nbFinal, char* trace )
{
    int i=0;
    int arret=0;
    int EtatActu=0;
    int k=0;
    int verif=0;
    char chaine[max]="";
    while((i<strlen(mot)) && ( !arret))
    {
        //if (EtatActu!=(-1)) printf("Etat S%d\n",EtatActu);
        k=EtatActu;
        EtatActu=RechInst(EtatActu,mot[i], nbInst, tab);
        if (EtatActu==(-1))
        {
            sprintf(chaine,"%s","");
            sprintf(chaine,"( S%d ; %c ; ?): Instruction incorrecte!\n",k,mot[i]);
            printf("%s\n",chaine);
            arret=1;
        }
        else
        {
            //printf("( S%d ; %c ; S%d )\n",k,mot[i],EtatActu);
            sprintf(chaine,"%s","");
            sprintf(chaine,"( S%d ; %c ; S%d )\n",k,mot[i],EtatActu);
            printf("%s",chaine);
        }
        i++;
        strcat(trace,chaine);
    }
    if((!arret) && (estFinal(tabFinal,nbFinal,EtatActu)))
    {
        verif=1;
    }
    return verif;
}

int RechInst(int EtatDep, char lettre,int nbInst, Instruction *tab)
{
    int i=0;
    int trouv=0;
    int EtatArv=-1;
    while ((i<nbInst) && (!trouv))
    {
        if ((valEtat1(&tab[i])==EtatDep) && (valLettre(&tab[i])==lettre))
        {
            trouv=1;
            EtatArv=valEtat2(&tab[i]);
        }
        else i++;
    }
    return EtatArv;
}




int estFinal(int *tabFinal, int taille, int etat)
{
    int i=0;
    int trouv=0;
    while ((i<taille) && (!trouv))
    {
        if (tabFinal[i]==etat) trouv=1;
        else i++;
    }
    return trouv;
}

void accessible(Instruction* tabInst, int taille,char* Alpha, int* EtatAcces, int* nbAcces)
{
    int i=0;
    int j=0;
    EtatAcces[0]=0;
    *nbAcces=1;
    int arrive=0;
    while(i<*nbAcces)
    {
        for(j=0;j<strlen(Alpha);j++)
        {
            arrive=RechInst(EtatAcces[i],Alpha[j],taille,tabInst);
            if ((!rech(EtatAcces,*nbAcces,arrive)) && (arrive!=-1) )
            {
                EtatAcces[*nbAcces]=arrive;
               (*nbAcces)++;
            }
        }
        i++;
    }
}

void Coaccessible(Instruction* tabInst, int nbInst, int* EtatFinal, int nbFinal, int* EtatCoacc, int* nbCoacc)
{
    int i=0;
    int j=0;
    //int arrive=-1;
    //int taille=0;
    *nbCoacc=0;
    for(i=0;i<nbFinal;i++)
    {
        rechDep(EtatFinal[i],tabInst,nbInst,EtatCoacc,nbCoacc);
        while(j<(*nbCoacc))
        {
            if(!estFinal(EtatFinal,nbFinal,EtatCoacc[j]))
            {
                rechDep(EtatCoacc[j],tabInst,nbInst,EtatCoacc,nbCoacc);
            }
            j++;
        }
    }
}

void rechDep(int EtatArv, Instruction* tabInst, int nbInst, int* tabEtat, int *taille)
{
    int i=0;
    while (i<nbInst)
    {
        if (valEtat2(&tabInst[i])==EtatArv)
        {
            if(!rech(tabEtat,*taille,valEtat1(&tabInst[i])))
            {//trouv=1;
                tabEtat[*taille]=valEtat1(&tabInst[i]);
                (*taille)++;
            }
        }
        i++;
    }
}


int rech(int *tab, int taille, int val)
{
    int i=0;
    int trouv=0;
    while((i<taille) && (!trouv))
    {
        if(tab[i]==val) trouv=1;
        i++;
    }
    return trouv;
}

void intersection(int *tab1, int taille1, int* tab2, int taille2, int* intersec,int *taille)
{
    int i=0;
    int j=0;
    int trouv=0;
    *taille=0;
    for (i=0;i<taille1;i++)
    {
        trouv=0;
        j=0;
        while((j<taille2) && (!trouv))
        {
            if (tab1[i]==tab2[j])
            {
                trouv=1;
                intersec[*taille]=tab1[i];
                (*taille)++;
            }
            j++;
        }
    }
}

void tabInstR(Instruction* tabInst, int nbInst,int* tabEtat, int nbEtat, Instruction* tabInstRed, int* nbInstRed)
{
    int i=0;
    (*nbInstRed)=0;
    for(i=0;i<nbInst;i++)
    {
        if((rech(tabEtat,nbEtat,valEtat1(&tabInst[i]))) && (rech(tabEtat,nbEtat,valEtat2(&tabInst[i]))))
        {
            tabInstRed[*nbInstRed]=tabInst[i];
            (*nbInstRed)++;
        }
    }
}

void AlphaR(Instruction* tabInst, int nbInst, char* Alpha, char* AlphaRed)
{
    int i=0;
    int trouv=0;
    int j=0;
    char chaine[3]="";
    sprintf(AlphaRed,"%s","");
    for(i=0;i<strlen(Alpha);i++)
    {
        trouv=0;
        j=0;

        while((j<nbInst) && (!trouv))
        {
            sprintf(chaine,"%s","");
            if(valLettre(&tabInst[j])==Alpha[i])
            {
                trouv=1;
                sprintf(chaine,"%c",Alpha[i]);
                strcat(AlphaRed,chaine);
            }
            else j++;
        }

    }
}

void tabFinalR(int* tabEtat,int nbEtat,int* tabFinal, int nbFinal,int* tabFinalRed,int* nbFinalRed)
{
    int i=0;
    (*nbFinalRed)=0;
    for(i=0;i<nbEtat;i++)
    {
        if(estFinal(tabFinal,nbFinal,tabEtat[i]))
        {
            tabFinalRed[*nbFinalRed]=tabEtat[i];
            (*nbFinalRed)++;
        }
    }
}







