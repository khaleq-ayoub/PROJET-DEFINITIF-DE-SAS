#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX_TEXT 2000
#define LENG_MOTS 50
#define MAX_MOTS 400
typedef struct {
    char mots[LENG_MOTS];
    int len ;//lengueur
    int occ ;//occurence(le nombre de reoition le mot
    int posi ;//nombre de position ou compteur de position
    int Tpo[50] ;//tableau contenent les position
}mots;
int analyse(mots m1[]){
    char texte[MAX_TEXT];

    printf("entrer le texte pour couriger :\n");
    fgets(texte , sizeof(texte) ,stdin);
    texte[strcspn(texte, "\n")] = '\0';// Supprime le saut de ligne à la fin du texte
    int le = strlen(texte);
    for (int i = 0; i < le; i++){
      texte[i] = tolower(texte[i]);//metrer le texte en miniscule
        if(ispunct (texte[i])){//suprimmer tout les virgule ;.,?!..
         texte[i]= ' ';
        }
    }

    char *token = strtok(texte , " ");//t9ssm un chaine de caracter on mot grace a des vergule les espace
    int  nb_mots = 0 ;
    int possis = 0 ;
    while (token != NULL){
     int trouve = 0 ;
     for (int i = 0; i < nb_mots; i++){
       if (strcmp(token , m1[i].mots) ==0){//la comparaison ente le token et la mots 1
        m1[i].occ++;
         if(m1[i].posi <50){
           m1[i].Tpo[m1[i].posi++] = possis;
         }
       trouve = 1;
       break;
      }
     }

     if (trouve == 0){
        if(nb_mots<MAX_MOTS){
        strncpy( m1[nb_mots].mots , token,LENG_MOTS-1);
        m1[nb_mots].mots[LENG_MOTS-1]='\0';
        m1[nb_mots].len = strlen(token);
        m1[nb_mots].Tpo[0] = possis;
        m1[nb_mots].occ = 1 ;
        m1[nb_mots].posi=1;
        nb_mots++;
        }
     }
    possis ++ ;
    token = strtok(NULL," ");
   }
   return nb_mots;
}
void affichage_les_mots(mots m2[],int nb_mots){
 printf("\n__________________Affichage des mots__________________\n");
  for(int i=0 ; i<nb_mots ; i++){
    printf("Le mots%d : %s\n",i+1,m2[i].mots);
    printf("La lengueur :%d\n",m2[i].len);
    printf("l'occurrence :%d\n",m2[i].occ);
    printf("position :");
    for(int j=0 ; j<m2[i].posi;j++){
        printf("%d\t",m2[i].Tpo[j]);
    }
    printf("\n\n");
  }
}
void trie_Alpha(mots m2[] , int nbr_mot){
  for(int i=0 ; i<nbr_mot-1 ; i++){
    for(int j = i + 1 ; j < nbr_mot ; j++){
        if (strcmp(m2[i].mots, m2[j].mots) > 0) {
         mots mot=m2[i];
         m2[i]=m2[j];
         m2[j]=mot;
       }
    }
 }
  printf("^^Le trie par alphabect ^^\n");
  affichage_les_mots(m2, nbr_mot);
}
void trie_Freq(mots m2[] , int nbr_mot){
 for(int i=0 ; i<nbr_mot-1 ; i++){
    for(int j=i+1 ;j<nbr_mot ; j++){
        if(m2[i].occ < m2[j].occ){
            mots o=m2[i];
            m2[i]=m2[j];
            m2[j]=o;
        }
    }
 }
 printf("^^Le trie par frequence ^^\n");
affichage_les_mots(m2, nbr_mot);
}
void trie_long(mots m2[] , int nbr_mot){
 for(int i=0 ; i<nbr_mot-1 ; i++){
    for(int j=i+1 ;j<nbr_mot ; j++){
        if(m2[i].len>m2[j].len){
            mots o=m2[i];
            m2[i]=m2[j];
            m2[j]=o;
        }
    }
 }
 printf("^^Le trier par longueur ^^\n");
 affichage_les_mots(m2, nbr_mot);
 printf("_____________________________________\n");
}
void trie_global(mots m2[] , int nbr_mot){
    int choix;

    printf("Entrer votre choix :");
    scanf("%d",&choix);
   affichage_les_mots(m2, nbr_mot);
    do {
         printf("===============TRIE===============\n");
         printf("case1 : Trie par alphabitique .\n");
         printf("case2 : Trie par frequence(occurence).\n");
         printf("case3 : Trie par lengueur.\n");
         printf("0. Quitter\n");
         printf("Votre choix : ");
         scanf("%d", &choix);
         getchar(); // Pour éviter les bugs avec fgets

        switch (choix) {
     case 1:
       trie_Alpha(m2, nbr_mot);
     break;
     case 2:
       trie_Freq(m2, nbr_mot);
     break;
     case 3:
       trie_long(m2, nbr_mot);
     break;
     case 0 :
     printf("Fin de Trie\n");
     default :
        printf("Choix non exist\n");
        }
    } while (choix != 0);
    }
void reche_partiel(mots m[],int nb_mots){
   char extr_mot[LENG_MOTS];
   printf("Entrer une partie de mot : ");
   scanf("%49s",extr_mot);
   for (int i = 0; i < strlen(extr_mot); i++) {
        extr_mot[i] = tolower(extr_mot[i]);
    }
   int trouve=0;
   for(int i=0 ; i<nb_mots ; i++){
    if(strstr(m[i].mots ,extr_mot)){
        printf("le mot %d : %s\n",i+1,m[i].mots);
        trouve=1;
        }
        printf("\n\n");
    }

   if(!trouve){
    printf("Aucun mot contient '%s' trouver.\n",extr_mot);
   }
   printf("_________________________________________\n");
}
void recheche(mots m3[], int nb_mots){
   char m_rechercher[LENG_MOTS];
   printf("Entrer votre recherche exact : ");
   scanf("%49s",m_rechercher);
   int le=strlen(m_rechercher);
   for(int i=0 ; i<le ;i++){
    m_rechercher[i]=tolower(m_rechercher[i]);
   }
   int trouve=0;
   for(int i=0 ; i<nb_mots ; i++){
    if(strcmp(m3[i].mots,m_rechercher)==0){
        printf("Le mot '%s' a etait trouve ,\n",m3[i].mots);
        printf("Son occurence est : %d\n",m3[i].occ);
        printf("Longueur : %d\n",m3[i].len);
        printf("Leur posision est :");
        for(int j=0 ; j<m3[i].posi ;j++){
            printf("%d\t",m3[i].Tpo[j]);
        }
        printf("\n\n");
        trouve=1;
    }
   }
   if(trouve==0){
    printf("Le mot '%s' n existe pas dans le texte.\n\n" ,m_rechercher);
   }
}
void statistique_global(mots m[] , int nb_mots){
  int total_mot = 0;
  int total_leng =0;
  float devers;
  char mot_long[LENG_MOTS];
  char mot_court[LENG_MOTS];
  char mot_occ[LENG_MOTS];
  int max_leng=0 , min_leng=LENG_MOTS , max_occ=0;
   for(int i=0 ; i<nb_mots ;i++){
    total_mot += m[i].occ;
    total_leng += m[i].len * m[i].occ;
      if(m[i].len >max_leng){
        max_leng=m[i].len;
        strcpy(mot_long, m[i].mots);
      }
      if(m[i].len<min_leng){
        min_leng = m[i].len;
        strcpy(mot_court ,m[i].mots);
      }
      if(m[i].occ>max_occ){
        max_occ = m[i].occ;
        strcpy(mot_occ ,m[i].mots);
      }
  }
  devers = (float)nb_mots/total_mot;
  float moyen = total_leng /total_mot;
  printf("\n::::::::::::::::STATISTIQUE GLOBALE:::::::::::::::::\n");
  printf("le nombre totale des mots dans ce text est : %d\n",total_mot);
  printf("Le nombre de mot unique est : %d\n",nb_mots);
  printf("La devirsiter lexicale est : %.2f\n",devers);
  printf("La longueur moyenne est : %.2f\n",moyen);
  printf("Le mot la plus long est : %s\n",mot_long);
  printf("Le mot la plus court est : %s\n",mot_court);
  printf("le mot le plus frequent est : %s\n",mot_occ);
}

int main() {
    mots le_mots[MAX_MOTS];
    int nb = analyse(le_mots);
    int choix;

    do {
        printf("\n========= MENU PRINCIPAL =========\n");
        printf("1. Afficher les mots\n");
        printf("2. Trier les mots\n");
        printf("3. Recherche exacte\n");
        printf("4. Recherche partielle\n");
        printf("5. Statistiques globales\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        getchar(); // Pour éviter les bugs avec fgets

        switch (choix) {
            case 1:
                affichage_les_mots(le_mots, nb);
                break;
            case 2:
                trie_global(le_mots, nb); // Appelle le menu de tri
                break;
            case 3:
                recheche(le_mots, nb);
                break;
            case 4:
                reche_partiel(le_mots, nb);
                break;
            case 5:
                statistique_global(le_mots, nb);
                break;
            case 0:
                printf("Fin du programme.\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);

    return 0;
}
