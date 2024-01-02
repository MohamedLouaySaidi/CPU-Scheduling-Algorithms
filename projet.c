#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct procesus{
    char pid[25];
    int te;
    int ta;
    int prio;
    int tatt;
    int trot;
    int fin;
    int debut;
};

typedef struct procesus processus;

void tri_fin(processus p[],int n){
    int i,j;
    processus c;
        for(i=0;i<n-1;i++)
            for(j=i+1;j<n;j++)
                if ( p[i].fin > p[j].fin){
                c = p[i];
                p[i] = p[j];
                p[j] = c;
        }
}

void tri_ta(processus p[],int n){
    int i,j;
    processus c;
        for(i=0;i<n-1;i++)
            for(j=i+1;j<n;j++)
                if ( p[i].ta > p[j].ta){
                c = p[i];
                p[i] = p[j];
                p[j] = c;
        }
}

void menu(){
    int choix;
    printf("\tMENU des algorithmes a choisir");
    printf("\n  ---------------------------------------------------");
    printf("\n  [1] (FCFS)First Come, First Serve");
    printf("\n  [2] (SJF)Shortest Job First");
    printf("\n  [3] (RR)Round-robin");
    printf("\n  [4] Priorite");
    printf("\n  [5] EXIT");
    printf("\n\nDonner votre choix: ");
    scanf("%d",&choix);
    switch(choix){
    case 1:
        system("cls");
        fcfs();
        break;
    case 2:
        system("cls");
        sjf();
        break;
    case 3:
        system("cls");
        rr();
        break;
    case 4:
        system("cls");
        priorite();
        break;
    case 5:
        system("exit");
        break;
    default:
        system("cls");
        printf("Donner un choix valide!!\n");
        menu();
        break;
    }
}

void encore(){
    char choix2;
    printf("\n\nVoulez vous essayer une autre fois? o/n, O/N: ");
    scanf("%s",&choix2);
    switch (choix2)
    {
    case 'o':
        system("cls");
        menu();
        break;
    case 'O':
        system("cls");
        menu();
        break;
    case 'n':
        system("cls");
        printf("\n\n                                             MERCI POUR VOTRE ATTENTION");
        printf("\n\n\n                                                 ^_^  A bientot  ^_^ \n\n");
        system("pause");
        exit(0);
        break;
    case 'N':
        system("cls");
        printf("\n\n                                             MERCI POUR VOTRE ATTENTION");
        printf("\n\n\n                                                 ^_^  A bientot  ^_^ \n\n");
        system("pause");
        exit(0);
        break;
    default:
        system("cls");
        printf("Donner un choix valide!!\n");
        encore();
    break;
}
}

void fcfs(){
    int i,n;
    printf("\n Donner le nombre des processus: ");
    scanf("%d",&n);
    processus p[n];
    for(i=0;i<n;i++){
        printf("\n Processus[%d]",i+1);
        printf(" Donner le nom du processus: ");
        scanf("%s",p[i].pid);
        printf(" Donner le temps d'execution: ");
        scanf("%d",&p[i].te);
        printf(" Donner la date d'arrive: ");
        scanf("%d",&p[i].ta);
    }
    tri_ta(p,n);
    p[0].debut=p[0].ta;
    for(i=1;i<n;i++){
        if(p[i].ta<=p[i-1].debut+p[i-1].te){
            p[i].debut=p[i-1].debut+p[i-1].te;
        }else{
            p[i].debut=p[i].ta;
        }
    }
    for(i=0;i<n;i++){
        p[i].fin=p[i].te+p[i].debut;
    }
    for(i=0;i<n;i++){
        p[i].tatt=p[i].debut-p[i].ta;
        p[i].trot=p[i].fin-p[i].ta;
    }
    system("cls");
    printf("\t\tAlgorithme d'ordonnancement First Come, First Serve\n");
    printf("\t");
    affichageTableau(p,n);
    affichageDiagramme(p,n);
    encore();
}

void sjf(){
    int choix;
    printf("\tSHORTEST JOB FIRST");
    printf("\n  ----------------------------");
    printf("\n  [1] Non Preemptive");
    printf("\n  [2] Preemptive");
    printf("\n  [3] Retourner");
    printf("\n  [4] Exit");
    printf("\n\n Donner votre choix: ");
    scanf("%d",&choix);
    switch(choix){
    case 1:
        system("cls");
        sjfnp();
        break;
    case 2:
        system("cls");
        sjfp();
        break;
    case 3:
        system("cls");
        menu();
        break;
    case 4:
        break;
    default:
        printf(" Donner un choix valide!!\n\n");
        sjf();
        break;
    }
}

void sjfnp(){
    int i,j,n;
    int t=0;
    int indmin=0;
    printf("\n Donner le nombre des processus: ");
    scanf("%d",&n);
    processus p[n];
    for(i=0;i<n;i++){
        printf("\n Processus[%d]",i+1);
        printf(" Donner le nom du processus: ");
        scanf("%s",p[i].pid);
        printf(" Donner le temps d'execution: ");
        scanf("%d",&p[i].te);
        printf(" Donner la date d'arrive: ");
        scanf("%d",&p[i].ta);
    }
    for(i=0;i<n;i++){
        p[i].fin=0;
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(p[j].fin == 0){
                indmin=j;
                break;
            }
        }
        for(j=0;j<n;j++){
            if((p[j].fin == 0) && (p[j].ta<=t) && (p[j].te < p[indmin].te)){
                indmin=j;
            }
        }
        p[indmin].debut=t;
        t+=p[indmin].te;
        p[indmin].fin=t;
        p[indmin].tatt=t-p[indmin].ta;
        p[indmin].trot=p[indmin].fin-p[indmin].ta;
    }
    tri_fin(p,n);
    system("cls");
    printf("\t\tAlgorithme d'ordonnancement Shortest Job First\n");
    printf("\t");
    affichageTableau(p,n);
    affichageDiagramme(p,n);
    encore();
}
void sjfp(){
    int i,j,n;
    int t=0,k=0,nb=0;
    int indmin=0,tempmin=0,totale=0;
    int tempte[100];
    processus tempP[100];
    printf("\n Donner le nombre des processus: ");
    scanf("%d",&n);
    processus p[n];
    for(i=0;i<n;i++){
        printf("\n Processus[%d]",i+1);
        printf(" Donner le nom du processus: ");
        scanf("%s",p[i].pid);
        printf(" Donner le temps d'execution: ");
        scanf("%d",&p[i].te);
        printf(" Donner la date d'arrive: ");
        scanf("%d",&p[i].ta);
    }
    tri_ta(p,n);
    for(i=0;i<n;i++){
        p[i].fin=0;
        totale+=p[i].te;
        tempte[i]=p[i].te;
    }
    while(t<=totale){
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(p[j].fin == 0){
                indmin=j;
                break;
            }
        }
        for(j=0;j<n;j++){
            if((p[j].fin == 0) && (p[j].ta<=t) && (p[j].te < p[indmin].te)){
                indmin=j;
            }
        }
        if(p[indmin].te == tempte[indmin]){
            p[indmin].debut = t;
        }
        p[indmin].te--;

        if(t>0 && tempmin != indmin){
            strcpy(tempP[k].pid,p[tempmin].pid);
            tempP[k].fin=t;
            k++;
        }else if(p[indmin].fin == 0 && nb == n-1){
            t+=p[indmin].te+1;
            strcpy(tempP[k].pid,p[tempmin].pid);
            p[indmin].fin=t;
            p[indmin].tatt = t-tempte[indmin]-p[indmin].ta;
            tempP[k].fin=t;
            k++;
        }
        tempmin=indmin;
        t++;
        if(p[indmin].te == 0){
            p[indmin].fin = t;
            p[indmin].tatt = t-tempte[indmin]-p[indmin].ta;
            nb++;
        }
    }
    }
    tri_fin(tempP,k);
    tempP[0].debut=0;
    tempP[0].te=tempP[0].fin-tempP[0].debut;
    for(i=1;i<k;i++){
        tempP[i].te=tempP[i].fin-tempP[i-1].fin;
    }
    for(i=0;i<n;i++){
        p[i].te=tempte[i];
        p[i].trot=p[i].fin-p[i].ta;
    }
    system("cls");
    printf("\t\tAlgorithme d'ordonnancement Shortest Job First Preemptive\n");
    printf("\t");
    affichageTableau(p,n);
    affichageDiagramme(tempP,k);
    encore();
}

void rr(){
    int i,n;
    int qt;
    printf("\n Donner le nombre des processus: ");
    scanf("%d",&n);
    processus p[n];
    for(i=0;i<n;i++){
        printf("\n Processus[%d]",i+1);
        printf(" Donner le nom du processus: ");
        scanf("%s",p[i].pid);
        printf(" Donner le temps d'execution: ");
        scanf("%d",&p[i].te);
        printf(" Donner la date d'arrive: ");
        scanf("%d",&p[i].ta);
    }
    printf("\n Donner le quantum: ");
    scanf("%d",&qt);
    tri_ta(p,n);
    int tempTe[100];
    int tempn,fin,t,all=0,compteur=0;
    for(i=0;i<n;i++){
        tempTe[i]=p[i].te;
        all+=p[i].te;
    }
    processus tempP[999];
    p[0].tatt=0;
    tempn=n;
    int j=0;
    t=0;
    for(all=0, compteur=0;tempn!=0;){
        if(p[compteur].ta<=t){
        if(p[compteur].te == tempTe[compteur]){
            p[compteur].debut = t;
        }
        if(tempTe[compteur]<= qt && tempTe[compteur]>0){
            all+=tempTe[compteur];
            strcpy(tempP[j].pid,p[compteur].pid);
            if(j==0){
                tempP[j].fin=tempTe[compteur];
            }else{
                tempP[j].fin=tempP[j-1].fin+tempTe[compteur];
            }
            tempP[j].te=tempTe[compteur];
            t+=tempTe[compteur];
            tempTe[compteur]=0;
            p[compteur].tatt = t - p[compteur].te;
            p[compteur].trot = p[compteur].tatt + p[compteur].te - p[compteur].ta;
            tempP[j].tatt=p[compteur].tatt;
            tempP[j].trot=p[compteur].trot;
            p[compteur].fin = t;
            fin=1;
            j++;

        }
        else if(tempTe[compteur] > qt){
            strcpy(tempP[j].pid,p[compteur].pid);
            if(j==0){
                tempP[j].fin=qt;
            }else{
                tempP[j].fin=tempP[j-1].fin+qt;
            }
            tempP[j].te=qt;

            tempTe[compteur]-=qt;
            all+=qt;
            j++;
            t+=qt;
        }
        }else{
            compteur=-1;
            t++;
        }
        if(tempTe[compteur] == 0 && fin == 1){
            tempn--;
            fin=0;
        }
        if(compteur == n-1){
            compteur=0;
        }else{
            ++compteur;
        }
    }
    int tailleTab;
    tailleTab=j;
    system("cls");
    printf("\t\tAlgorithme d'ordonnancement Round Robin ( Quantum : %d )\n", qt);
    printf("\t");
    affichageTableau(p,n);
    affichageDiagramme(tempP,tailleTab);
    encore();
}
int choixprio;
void priorite(){
    int choix;
    printf("\tPRIORITE");
    printf("\n  ------------------------");
    printf("\n  [1] Non Preemptive");
    printf("\n  [2] Preemtive");
    printf("\n  [3] Retourner");
    printf("\n  [4] Exit");
    printf("\n\n Donner votre choix: ");
    scanf("%d",&choix);
    switch(choix){
    case 1:
        system("cls");
        printf("\n\n Choisissez une priorite:");
        printf("\n  [1] priorite croissante");
        printf("\n  [2] priorite decroissante");
        do{
        printf("\n\n Donner votre choix: ");
        scanf("%d",&choixprio);
        }while(choixprio != 1 && choixprio != 2);
        system("cls");
        prioritenp(choixprio);
        break;
    case 2:
        system("cls");
        printf("\n\n Choisissez une priorite:");
        printf("\n  [1] priorite croissante");
        printf("\n  [2] priorite decroissante");
        do{
        printf("\n\n Donner votre choix: ");
        scanf("%d",&choixprio);
        }while(choixprio != 1 && choixprio != 2);
        system("cls");
        prioritep(choixprio);
        break;
    case 3:
        system("cls");
        menu();
        break;
    case 4:
        break;
    default :
        printf("Donner un choix valid!!\n\n");
        priorite();
        break;
    }
}
void prioritenp(int choixprio){
    int i,j,n;
    int t=0;
    int indmin=0;
    printf("\n Donner le nombre des processus: ");
    scanf("%d",&n);
    processus p[n];
    for(i=0;i<n;i++){
        printf("\n Processus[%d]",i+1);
        printf(" Donner le nom du processus: ");
        scanf("%s",p[i].pid);
        printf(" Donner le temps d'execution: ");
        scanf("%d",&p[i].te);
        printf(" Donner la date d'arrive: ");
        scanf("%d",&p[i].ta);
        printf(" Donner la priorite: ");
        scanf("%d",&p[i].prio);
    }
    for(i=0;i<n;i++){
        p[i].fin=0;
    }
    tri_ta(p,n);
    if(choixprio == 2){
        for(i=0;i<n;i++){
            p[i].prio= -p[i].prio;
        }
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(p[j].fin == 0){
                indmin=j;
                break;
            }
        }
        for(j=0;j<n;j++){
            if((p[j].fin == 0) && (p[j].ta<=t) && (p[j].prio < p[indmin].prio)){
                indmin=j;
            }
        }
        p[indmin].debut=t;
        t+=p[indmin].te;
        p[indmin].fin=t;
        p[indmin].tatt=t-p[indmin].ta;
        p[indmin].trot=p[indmin].fin-p[indmin].ta;
    }
    tri_fin(p,n);
    system("cls");
    printf("\t\tAlgorithme d'ordonnancement Priorite\n");
    printf("\t");
    affichageTableau(p,n);
    affichageDiagramme(p,n);
    encore();
}

void prioritep(int choixprio){
    int i,j,n;
    int t=0,k=0,nb=0;
    int indmin=0,tempmin=0,totale=0;
    int tempte[100];
    processus tempP[100];
    printf("\n Donner le nombre des processus: ");
    scanf("%d",&n);
    processus p[n];
    for(i=0;i<n;i++){
        printf("\n Processus[%d]",i+1);
        printf(" Donner le nom du processus: ");
        scanf("%s",p[i].pid);
        printf(" Donner le temps d'execution: ");
        scanf("%d",&p[i].te);
        printf(" Donner la date d'arrive: ");
        scanf("%d",&p[i].ta);
        printf(" Donner la priorite: ");
        scanf("%d",&p[i].prio);
    }
    tri_ta(p,n);
    for(i=0;i<n;i++){
        p[i].fin=0;
        totale+=p[i].te;
        tempte[i]=p[i].te;
    }
    if(choixprio == 2){
        for(i=0;i<n;i++){
            p[i].prio = -p[i].prio;
        }
    }
    while(t<=totale){
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(p[j].fin == 0){
                indmin=j;
                break;
            }
        }
        for(j=0;j<n;j++){
            if((p[j].fin == 0) && (p[j].ta<=t) && (p[j].prio < p[indmin].prio)){
                indmin=j;
            }
        }
        if(p[indmin].te == tempte[indmin]){
            p[indmin].debut = t;
        }
        p[indmin].te--;

        if(t>0 && tempmin != indmin){
            strcpy(tempP[k].pid,p[tempmin].pid);
            tempP[k].fin=t;
            k++;
        }else if(p[indmin].fin == 0 && nb == n-1){
            t+=p[indmin].te+1;
            strcpy(tempP[k].pid,p[tempmin].pid);
            p[indmin].fin=t;
            p[indmin].tatt = t-tempte[indmin]-p[indmin].ta;
            tempP[k].fin=t;
            k++;
        }
        tempmin=indmin;
        t++;
        if(p[indmin].te == 0){
            p[indmin].fin = t;
            p[indmin].tatt = t-tempte[indmin]-p[indmin].ta;
            nb++;
        }
    }
    }
    tri_fin(tempP,k);
    tempP[0].debut=0;
    tempP[0].te=tempP[0].fin-tempP[0].debut;
    for(i=1;i<k;i++){
        tempP[i].te=tempP[i].fin-tempP[i-1].fin;
    }
    for(i=0;i<n;i++){
        p[i].te=tempte[i];
        p[i].trot=p[i].fin-p[i].ta;
    }
    system("cls");
    printf("\t\tAlgorithme d'ordonnancement Priorite preemptive\n");
    printf("\t");
    affichageTableau(p,n);
    affichageDiagramme(tempP,k);
    encore();
}

void affichageTableau(processus p[], int n){
    printf("\n");
    int s1=0,s2=0;
    int i;
    for(i=0;i<n;i++){
        s1+=p[i].tatt;
        s2+=p[i].trot;
    }
    printf("\t+----------+-------------------+---------------+-------+---------+-----+----------+\n");
    printf("\t|Processus | Temps d'Execution | Date d'Arrive | Debut | Attente | Fin | Rotation |\n");
    printf("\t+----------+-------------------+---------------+-------+---------+-----+----------+\n");
    for(i=0; i<n; i++)
    {
    printf("\t|%3s       |         %3d       |       %3d     |   %3d |    %3d  |  %3d|     %3d  |\n",
           p[i].pid,p[i].te,p[i].ta,p[i].debut,p[i].tatt,p[i].fin,p[i].trot);
           printf("\t+----------+-------------------+---------------+-------+---------+-----+----------+\n");
    }
    float f1,f2;
    f2=(float)s1/n;
    f1=(float)s2/n;
    printf("\tTemps de rotation moyenne=%.3f\n",f1);
    printf("\tTemps d'attente moyenne=%.3f\n",f2);
}
void affichageDiagramme(processus p[], int n){
    const int maxWitdh=100;
    int i,j;
    int tempsDexecutionTotale=0,echelle,compteur,tempi;
    for(i=0;i<n;i++){
        tempsDexecutionTotale+=p[i].te;
    }
    printf("\n\n\t\t\tLe diagramme de gannt de ces proccessus :\n\n");
    echelle=maxWitdh/tempsDexecutionTotale;
    for(j=0;j<echelle*tempsDexecutionTotale+2+n;j++){
        printf("-");
    }
    printf("\n|");
    compteur=0;
    tempi=0;
    for(j=0;j<echelle*tempsDexecutionTotale;j++){
        if(j==p[compteur].te*echelle+tempi){
            compteur++;
            tempi=j;
            printf("|");
        }
        else if(j==(p[compteur].te*echelle)/2+tempi){
            printf("%2s",p[compteur].pid);
        }
        else{
            printf(" ");
        }
    }
    printf("|");
    printf("\n");
    for(j=0;j<echelle*tempsDexecutionTotale+2+n;j++){
        printf("-");
    }
    printf("\n");
    compteur=0;
    tempi=0;
    printf("0");
    for(j=0;j<echelle*tempsDexecutionTotale;j++){
        if(j==p[compteur].te*echelle+tempi){
            tempi=j;
            printf("%2d",p[compteur].fin);
            compteur++;
        }
        else {
            printf(" ");
        }
    }
    printf("%2d",p[compteur].fin);
}

int main()
{
    printf("                                        BONJOUR  ET  BIENVENUE");
    sleep(1);
    printf("\n\n\n\n                Projet Systeme d'exploitation : Les Algorithmes d'Ordonnancement des Processus  ");
    sleep(1);
    printf("\n\n\n                                          Propose par:");
    printf("\n\n                                                  M. Naouai Mohamed");
    sleep(1);
    printf("\n\n\n                                          Realise par:");
    sleep(1);
    printf("\n\n                                                     MEKSI Syrine");
    printf("\n                                                     SAIDI Mohamed Louay");
    sleep(1);
    printf("\n\n\n                                  Appuyer sur une touche pour continuer ^_^");
    getch();
    system("cls");
    menu();
    retour:
    system("cls");
    printf("\n\n                                             MERCI POUR VOTRE ATTENTION");
    printf("\n\n\n                                                 ^_^  A bientot  ^_^ \n\n");
    system("pause");
    return 0;
}
