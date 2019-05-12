#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"
#include "./machine/machine.h"
#include <string.h>

//#include "./machine/machine.h"

int main()
{


    int nAlph=0;//le nombre de symb de l'alphabet
    int nbEtat=0; //nombre des états
    char Alpha[max]="";
    char AlphaRed[max]="";
    int tabFinal[max];

    int nbFinal=0;
    int tabFinalRed[max];
    int nbFinalRed=0;
    int nbInst=0;
    int i=0;
    char mot[max];
    int trouv=0;

    char EnsAlphabet[max]="X={";
    char EnsAlphabetRed[max]="X'={";

    char EnsEtat[max]="S={";
    char EnsEtatRed[max]="S'={";

    char EnsFinal[max]="F={";
    char EnsFinalRed[max]="F'={";

    char EnsInst[5*max]="II={";
    char EnsInstRed[5*max]="II'={";

    char chaine[max]="";
    char trace[10*max]="";

    int EtatAcces[max];
    int nbAcces=0;

    int EtatCoacc[max];
    int nbCoacc=0;

    int EtatReduit[max];
    int nbReduit=0;

    Instruction tabInst[max];
    Instruction tabInstRed[max];
    int nbInstRed=0;

    FILE* f=NULL;
    int choix=0,stop=0;
    int autoCree=0;
    int autoRed=0;
    f=fopen("trace.txt","a+");
    do{
        menu();
        scanf( " %d", &choix );
        printf( "\n" );

         switch(choix)
         {
            case 1:
                printf("Creation de l'automate:\n");
                nAlph=0;
                while(nAlph<=0)// || (!autoCree))
                {
                    printf("Donner le nombre de symboles de l'alphabet:\n");
                    scanf("%d",&nAlph);
                }
                printf("Donner l'alphabet:\n");
                alphabet(nAlph,Alpha);
                sprintf(EnsAlphabet,"%s","X={");
                for(i=0;i<strlen(Alpha);i++)
                {
                   // printf("Alpha i %c\n",Alpha[i]);
                    strncat(EnsAlphabet,&Alpha[i],1);
                    //printf("%s\n",EnsAlphabet);
                   if(i!=strlen(Alpha)-1) strcat(EnsAlphabet, "; ");
                }
                //printf("ok\n");
                //strncat(EnsAlphabet, &Alpha[strlen(Alpha)-1],1);
                strcat(EnsAlphabet, "}");
                printf("%s\n",EnsAlphabet);
                fputs("Les donnees de l'automate sont:\n\tL'alphabet: ",f);
                fputs(EnsAlphabet,f);
                fputs("\n",f);
                nbEtat=0;
                while (nbEtat<=0)
                {
                    printf("Donner le nombre d'etats:\n");
                    scanf("%d",&nbEtat);
                }
                sprintf(EnsEtat,"%s","S={");
                for(i=0;i<nbEtat;i++)
                {
                   // printf("Alpha i %c\n",Alpha[i]);
                    strcat(EnsEtat,"S");
                    sprintf(chaine,"%d",i);
                    strcat(EnsEtat,chaine);
                    sprintf(chaine,"%s","");
                    //printf("%s\n",EnsAlphabet);
                   if(i!=nbEtat-1) strcat(EnsEtat, "; ");
                }
                //printf("ok\n");
                //strncat(EnsAlphabet, &Alpha[strlen(Alpha)-1],1);
                strcat(EnsEtat, "}");
                printf("%s\n",EnsEtat);
                fputs("\tL'ensemble des etats est: ",f);
                fputs(EnsEtat,f);
                fputs("\n",f);
                nbFinal=0;
                while(nbFinal<=0)
                {
                    isFinal(tabFinal, nbEtat, &nbFinal);
                    if (nbFinal==0)
                    {
                        printf("\nAucun etat final! Recommencez.\n\n");
                    }
                }
                sprintf(chaine,"%s","");
                sprintf(EnsFinal,"%s","F={");
                for(i=0;i<nbFinal;i++)
                {
                   
                    strcat(EnsFinal,"S");
                    sprintf(chaine,"%d",tabFinal[i]);
                    strcat(EnsFinal,chaine);
                    sprintf(chaine,"%s","");
                    
                   if(i!=nbFinal-1) strcat(EnsFinal, "; ");
                }
                
                strcat(EnsFinal, "}");
                printf("%s\n",EnsFinal);
                fputs("\tL'ensemble des etats finaux est: ",f);
                fputs(EnsFinal,f);
                fputs("\n",f);
                
                nbInst=0;
                while(nbInst<=0)
                {
                    printf("Donnez le nombre d'instructions:\n");
                    scanf("%d",&nbInst);
                }
                Inst(nbInst,tabInst,nbEtat,nAlph,Alpha);

                sprintf(chaine,"%s","");
                sprintf(EnsInst,"%s","II={");
                for(i=0;i<nbInst;i++)
                {
                   
                    strcat(EnsInst,"(S");
                    sprintf(chaine,"%d",valEtat1(&tabInst[i]));
                    strcat(EnsInst,chaine);
                    strcat(EnsInst,", ");
                    sprintf(chaine,"%s","");
                    sprintf(chaine,"%c",valLettre(&tabInst[i]));
                    strcat(EnsInst,chaine);
                    strcat(EnsInst,", ");
                    strcat(EnsInst,"S");
                    sprintf(chaine,"%s","");
                    sprintf(chaine,"%d",valEtat2(&tabInst[i]));
                    strcat(EnsInst,chaine);
                    strcat(EnsInst,")");
                    sprintf(chaine,"%s","");
                    
                   if(i!=nbInst-1) strcat(EnsInst, "; ");
                }
                
                strcat(EnsInst, "}");
                printf("%s\n",EnsInst);
                fputs("\tL'ensemble des instructions est: ",f);
                fputs(EnsInst,f);
                autoCree=1;
                break;
            case 2:
                printf("Voir l'automate\n");
                if(!autoCree){
                    printf("Vous devez d'abord creer un automate!\n");
                    break;
                }

                printf("L'alphabet: %s\n",EnsAlphabet);
                printf("L'ensemble des etats: %s\n",EnsEtat);
                printf("L'ensemble des etats finaux: %s\n",EnsFinal);
                printf("L'ensemble des instructions: %s\n",EnsInst);
                break;

            case 3:
                printf("Tester un mot:\n");
                if(!autoCree){
                    printf("Vous devez d'abord creer un automate!\n");
                    break;
                }
                fputs("\n\nTester un mot\n\t Le mot: ",f);
                printf("Donner un mot: ");
                scanf("%s",mot);
                fputs(mot,f);
                fputs("\n",f);
                trouv=verifMot(mot,tabInst,nbInst,tabFinal,nbFinal,trace);
                fputs("\nLe chemin suivi par l'automate est:\n",f);
                fputs(trace,f);
                fputs("\nResultat:\n",f);
                if (trouv)
                {
                    printf("Le mot appartient au langage\n");
                    fputs("Le mot appartient au langage\n",f);
                }
                else
                {
                    printf("Le mot n'appartient pas au langage\n");
                    fputs("Le mot n'appartient pas au langage\n",f);
                }
                break;

            case 4:
                printf("Reduction de l'automate:\n");
                if(!autoCree){
                    printf("Vous devez d'abord creer un automate!\n");
                    break;
                }
                accessible(tabInst,nbInst,Alpha,EtatAcces,&nbAcces);
                
                Coaccessible(tabInst,nbInst,tabFinal,nbFinal,EtatCoacc,&nbCoacc);
                
                intersection(EtatAcces,nbAcces,EtatCoacc,nbCoacc,EtatReduit,&nbReduit);
                
                sprintf(chaine,"%s","");
                sprintf(EnsEtatRed,"%s","S'={");
                for(i=0;i<nbReduit;i++)
                {
                   
                    strcat(EnsEtatRed,"S");
                    sprintf(chaine,"%d",EtatReduit[i]);
                    strcat(EnsEtatRed,chaine);
                    sprintf(chaine,"%s","");
                   
                   if(i!=nbReduit-1) strcat(EnsEtatRed, "; ");
                }
                
                strcat(EnsEtatRed, "}");
                printf("%s\n",EnsEtatRed);

                tabInstR(tabInst,nbInst,EtatReduit,nbReduit,tabInstRed,&nbInstRed);
                sprintf(chaine,"%s","");
                sprintf(EnsInstRed,"%s","II'={");
                for(i=0;i<nbInstRed;i++)
                {
                   
                    strcat(EnsInstRed,"(S");
                    sprintf(chaine,"%d",valEtat1(&tabInstRed[i]));
                    strcat(EnsInstRed,chaine);
                    strcat(EnsInstRed,", ");
                    sprintf(chaine,"%s","");
                    sprintf(chaine,"%c",valLettre(&tabInstRed[i]));
                    strcat(EnsInstRed,chaine);
                    strcat(EnsInstRed,", ");
                    strcat(EnsInstRed,"S");
                    sprintf(chaine,"%s","");
                    sprintf(chaine,"%d",valEtat2(&tabInstRed[i]));
                    strcat(EnsInstRed,chaine);
                    strcat(EnsInstRed,")");
                    sprintf(chaine,"%s","");
                   
                   if(i!=nbInstRed-1) strcat(EnsInstRed, "; ");
                }
                
                strcat(EnsInstRed, "}");
                printf("%s\n",EnsInstRed);

                AlphaR(tabInstRed,nbInstRed,Alpha,AlphaRed);
                
                sprintf(EnsAlphabetRed,"%s","X'={");
                for(i=0;i<strlen(AlphaRed);i++)
                {
                
                    strncat(EnsAlphabetRed,&AlphaRed[i],1);
                
                   if(i!=strlen(AlphaRed)-1) strcat(EnsAlphabetRed, "; ");
                }
                
                strcat(EnsAlphabetRed, "}");
                printf("%s\n",EnsAlphabetRed);
                fputs("Les donnees de l'automate reduit sont:\n\tL'alphabet: ",f);
                fputs(EnsAlphabetRed,f);
                fputs("\n\tL'ensemble des instructions: ",f);
                fputs(EnsInstRed,f);

                tabFinalR(EtatReduit,nbReduit,tabFinal,nbFinal,tabFinalRed,&nbFinalRed);
                sprintf(chaine,"%s","");
                sprintf(EnsFinalRed,"%s","F'={");
                for(i=0;i<nbFinalRed;i++)
                {
                
                    strcat(EnsFinalRed,"S");
                    sprintf(chaine,"%d",tabFinalRed[i]);
                    strcat(EnsFinalRed,chaine);
                    sprintf(chaine,"%s","");
                
                   if(i!=nbFinalRed-1) strcat(EnsFinalRed, "; ");
                }
                
                strcat(EnsFinalRed, "}");
                printf("%s\n",EnsFinalRed);
                fputs("\n\tL'ensemble des etats finaux: ",f);
                fputs(EnsFinalRed,f);

               
                autoRed=1;
                break;

            case 5:
                printf("Voir l'automate reduit\n");
                if(!autoCree){
                    printf("Vous devez d'abord creer un automate!\n");
                    break;
                }
                else
                {
                    if(!autoRed)
                    {
                        printf("Vous devez d'abord reduire un automate!\n");
                        break;
                    }
                    else
                    {
                        printf("L'alphabet reduit: %s\n",EnsAlphabetRed);
                        printf("L'ensemble des etats reduit: %s\n",EnsEtatRed);
                        printf("L'ensemble des etats finaux reduit: %s\n",EnsFinalRed);
                        printf("L'ensemble des instructions reduit: %s\n",EnsInstRed);
                        break;
                    }
                }

            case 0:
                printf("\nFin\n");
                stop=1;
                break;
         }
        if (autoCree) fputs("\n*****************************************************************\n",f);
        if(choix)
        {
            printf("\n\nAppuyez sur ENTREE pour continuer...");
            getchar();
            getchar();
        }
    }while(!stop);

    
    fclose(f);
    return 0;
}
