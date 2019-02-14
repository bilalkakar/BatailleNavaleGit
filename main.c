#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define Max_Car_Nom 8
#define LIGNE_AFFICH 11
#define COLONNE_AFFICH 11
#define TIRE_TOTAL 51
#define BKSP 8



void RetournMenuPrinc()
{
    int MenuPrincipal;
    printf("Pour retourner au menu principal veuillez entrer un chiffre SVP:");
    MenuPrincipal=OnlyNumber();
}


void Authentification()
{
    char nom[Max_Car_Nom]="";
    system("cls");
    printf("Veuillez tapez votre nom SVP: ");
    scanf("%s",&nom);
    printf("\n\nJoueur:\t%s\n\n", nom);
}
    // Tableau qui sera affiché pour l'utilisateur
    char grilleDuJeu[LIGNE_AFFICH][COLONNE_AFFICH]={
        {' ',' ','1','2','3','4','5','6','7','8','9'},              // (1,2,3,4,5,6,7,8,9) les nombre des lignes
        {'_','_','_','_','_','_','_','_','_','_','_'},              // (1,2,3,4,5,6,7,8,9) les nombre des colonnes
        {'1','|','0','0','0','0','0','0','0','0','0'},              //  X  Quand la case est deja chosie
        {'2','|','0','0','0','0','0','0','0','0','0'},
        {'3','|','0','0','0','0','0','0','0','0','0'},
        {'4','|','0','0','0','0','0','0','0','0','0'},
        {'5','|','0','0','0','0','0','0','0','0','0'},
        {'6','|','0','0','0','0','0','0','0','0','0'},
        {'7','|','0','0','0','0','0','0','0','0','0'},
        {'8','|','0','0','0','0','0','0','0','0','0'},
        {'9','|','0','0','0','0','0','0','0','0','0'},
    };

/** \brief Cette fonction Affiche la grille de jeu
 *
 * \return void
 *
 */
void AfficherGrille()
{
    int posy, posx;
    for(posy=0;posy<LIGNE_AFFICH;posy++) {
        for(posx=0;posx<COLONNE_AFFICH;posx++) {
            printf("%3c", grilleDuJeu[posy][posx]);
        }
        printf("\n");
    }
}

/** \brief Cette fonction permet a utilisateur ou joueur d'entrer que les chiffre entre 1 et 9
 *
 * \return int
 *
 */
int OnlyNumber()
    {
        int number=0, caracter;
        do {
        caracter=getch();
        if(caracter>48&&caracter<=57)
        {
            printf("%c",caracter);
            number=number*10+(caracter-48);
        }
        if (caracter==13)
        {
            break;
        }
        if (caracter==BKSP)
        {
            continue;
        }
        } while(1);
        return(number);
    }

void Raffichage()
{
    system("pause");
    system("cls");
    AfficherGrille();
}

/** \brief Cette fonction affiche le message après avoir coulé un bateau et change les valeur des cases dans lesquelles ce bateau existait
 *
 * \param placementDesBateau[][10] est un tableau de deux dimensions dans lequel les bateaux sont placés
 * \param heady int: la position y (ligne du tableau) de la "tete" d'un bateau
 * \param headx int: la position X (colonne du tableau) de la "tete" d'un bateau
 * \param bodyy int: la position y (ligne du tableau) de la partie "milieu" d'un bateau
 * \param bodyx int: la position X (Colonne du tableau) de la partie "milieu" d'un bateau
 * \param feety int: la position y (ligne du tableau) de la troisième partie d'un bateau
 * \param feetx int: la position x (ligne du tableau) de la troisième partie d'un bateau
 * \return void
 *
 */
void ControlCoule(char placementDesBateau[][10], int heady, int headx, int bodyy, int bodyx, int feety, int feetx)
{
    system("cls");
    printf("\nEt Felicitation pour une victoire ! vous avez coule un bateau\n\n");
    placementDesBateau[heady][headx]=-11;
    placementDesBateau[bodyy][bodyx]=-11;
    placementDesBateau[feety][feetx]=-11;
    Raffichage();
}
/** \brief Cette fonction est utilisée pour sauvegarder la date et l'horaire d'une action faite par utilisateur, par exemple: si on s'authentifie, le record sera sauvegarde dans un fichier
 *
 * \param loguer[100] char
 * \return void
 *
 */
void Loguer(char loguer[100])
{
    FILE* Fichier = NULL;
    time_t t;
    struct tm* current_time;

    Fichier = fopen("loguer.txt", "r+");
    t = time(NULL);
    current_time = localtime(&t);


    if (Fichier != NULL) // verifie si le fichier s'est ouvert correctement
    {
        fseek(Fichier, 0, SEEK_END);
        //ecrire la date ainsi que le message dans le fichier log
        fprintf(Fichier,"[%02d/%02d/%d %02d:%02d:%02d] %s\n",current_time->tm_mday,current_time->tm_mon+1,current_time->tm_year+1900,current_time->tm_hour,current_time->tm_min,current_time->tm_sec,loguer);
        fclose(Fichier);
    }else{
        printf("impossible de lire le fichier !");
    }
}


int main()
{
    int MenuPrincipal=1; // pour retourner au menu principal
    int ChoixDeMenu;
    int line=0;         // ligne du tableau dans lequel les bateaux sont placés
    int column=0;       // colonne du tableau dans lequel les bateaux sont placés
    int ChoixDeLigne;
    int ChoixDeColonne;
    int FinDeJeu=0;
    char nom[Max_Car_Nom]="";
    char PlacementDesBateaux[9][10];
    char score=' ';
    double tire=TIRE_TOTAL;

    printf("\n\n\t\t\t\t    Bienvenu au jeu Bataille Navale!\n\n");

    while(MenuPrincipal>0)
    {
        printf("\n\t\t\t\t\tVeuillez faire un choix: \n\n");
        printf("\n\n\n\n");
        printf("\t1- S'authentifier\n");
        printf("\t2- Demander de l'aide\n");
        printf("\t3- Jouer\n");
        printf("\t4- Voir les score\n");
        printf("\n\nChoix: ");
        ChoixDeMenu=OnlyNumber();

        switch (ChoixDeMenu)
        {
            case 1:
                Loguer("Le joueur s'est authentifie");
                Authentification();
                RetournMenuPrinc();
            break;

            case 2:  system("cls");
                Loguer("Le joueur a affiche de l'aide");
                printf("\n");
                printf("\t\t\t\tLa Bataille Navale");
                printf("\n\nC'est un jeu dans lequel deux joueur doivent placer des (navires) sur une grille tenue secrete et tenter de (toucher) les navires adverses\n");
                printf("\n\nQuelque regles par rapport au jeu:\n");
                printf("\n\n1- Afin de jouer il faut s'authentifier d'abord.");
                printf("\n\n1- En choisissant (jouer) (Apres avoir fait l'authentification) le grille de jeu s'affiche et demande de choisir une case.");
                printf("\n\n2- On choisit la case en donnant le coordonne (numero de ligne et de colonne).");
                printf("\n\n3- Si dans  cette  case  la il y a un bateau on voit un message (Bravo vous avez touche un bateau).");
                printf("\n\n4- Si on touche toutes les cases d'un bateau, on voit un message (Felicitation ! (vous avez coule un bateau).");
                printf("\n\n5- Sinon on voit un message (Desole vous n'avez pas touche un bateau).");
                printf("\n\n6- Il ne faut pas choisir deux fois la meme case. ");
                printf("\n\n7- Si on coule tous les bateaux adverses, on voit un message (Bravo et felicitation! vous avez gagnez). ");
                printf("\n\n8- Si on n'a pas coule tous les bateaux adverses en 50 tire, on va perdre\n\n");
                RetournMenuPrinc();
                break;

            case 3:
                Loguer("Le joueur a commence a joue");
                system("cls");
                printf("Veuillez tapez votre Nom SVP: ");
                scanf("%s",&nom);
                system("cls");
                AfficherGrille();
                FILE *fichier;
                fichier=fopen("bateaux.txt","r");
                for(line=0;line<9;line++)
                    {
                        for(column=0;column<10;column++)
                        {
                            PlacementDesBateaux[line][column]=fgetc(fichier);
                        }
                    }
                    fclose(fichier);
                while (tire>0)
                {
                    printf("\n\nTires restes: %.0lf\n\n",tire-1);
                    printf("\nVeuiilez choisir les coordonnees de la case que vous voulez choisir:\n\n");
                    do
                    {
                        printf("\nLigne: ");
                        ChoixDeLigne=OnlyNumber();
                    }while(ChoixDeLigne>9 || ChoixDeLigne<=0);
                    printf("\n");
                    do
                    {
                        printf("\nColonne:");
                        ChoixDeColonne=OnlyNumber();
                    }while(ChoixDeColonne>9 || ChoixDeColonne<=0);

                    system("cls");

                    if(PlacementDesBateaux[ChoixDeLigne-1][ChoixDeColonne-1]=='0')  // "0" veut dire qu'il n'y a pas de bateau
                    {
                        printf("\n\nDesole vous n'avez pas touche un bateau\n\n");
                        PlacementDesBateaux[ChoixDeLigne-1][ChoixDeColonne-1]=2;    // "2" pour les case qui étaient deja choisies
                        grilleDuJeu[ChoixDeLigne+1][ChoixDeColonne+1]='X';          // la valeur de la case choisie sera changé de "0" à "X" (dans la grille qui s'affiche à l'utilisateur)
                        tire--;
                        Raffichage();
                    }
                    else
                    {
                        if(PlacementDesBateaux[ChoixDeLigne-1][ChoixDeColonne-1]==2)
                        {
                            printf("\nLa case etait deja choisie\n");
                            Raffichage();
                        }
                        else
                        {
                            if(PlacementDesBateaux[ChoixDeLigne-1][ChoixDeColonne-1]=='1')  // les bateaux sont définis par "1"
                            {
                                printf("\n\nVous avez touche un bateau\n\n");
                                FinDeJeu++;
                                PlacementDesBateaux[ChoixDeLigne-1][ChoixDeColonne-1]=-1;   // la valeur de la case dans laquelle le bateau deja touché, change de "1" à "-1"
                                grilleDuJeu[ChoixDeLigne+1][ChoixDeColonne+1]='X';
                                tire--;
                                Raffichage();
                            }
                            else
                            {
                                if(PlacementDesBateaux[ChoixDeLigne-1][ChoixDeColonne-1]<0)
                                {
                                    printf("\nLe bateau etait deja touche\n");
                                    Raffichage();
                                }
                            }
                        }
                    }
                                                    //Controler afin de verifier si un bateau est complètement touché
                    if(PlacementDesBateaux[1][6]==-1 && PlacementDesBateaux[1][7]==-1 &&PlacementDesBateaux[1][8]==-1 )
                    {
                        ControlCoule(PlacementDesBateaux, 1,6,1,7,1,8);
                    }
                    else
                    {                               //Controler afin de verifier si un bateau est complètement touché
                        if(PlacementDesBateaux[2][0]==-1 && PlacementDesBateaux[3][0]==-1 && PlacementDesBateaux[4][0]==-1)
                        {
                            ControlCoule(PlacementDesBateaux,2,0,3,0,4,0);
                        }
                        else
                        {                           //Controler afin de verifier si un bateau est complètement touché
                            if(PlacementDesBateaux[3][8]==-1&& PlacementDesBateaux[4][8]==-1 && PlacementDesBateaux[5][8]==-1)
                            {
                                ControlCoule(PlacementDesBateaux,3,8,4,8,5,8);
                            }
                            else
                            {                       //Controler afin de verifier si un bateau est complètement touché
                                if(PlacementDesBateaux[6][2]==-1&& PlacementDesBateaux[6][3]==-1 && PlacementDesBateaux[6][4]==-1)
                                {
                                    ControlCoule(PlacementDesBateaux,2,0,3,0,4,0);
                                }
                            }
                        }
                    }
                    if(FinDeJeu==12)    // vue qu'il y a 4 bateau de taille 3, alors la fin de jeu sera quand le joueur touche 12 fois les bateaux
                    {
                        system("cls");
                        printf("\nFelicitation vous avez gagne le jeu\n");
                        printf("\nJoueur: %s\n\n",nom);
                        printf("Score: %7.0lf\n\n", TIRE_TOTAL-tire);
                        system("pause");
                        system("cls");
                        // ecrire les scores dans un fichier
                        fichier=fopen("socre.txt","a");
                        if(fichier!=NULL)
                        {
                            fprintf(fichier,"%s %.0lf\n",nom,TIRE_TOTAL-tire);
                            fclose(fichier);
                        }
                        else
                        {
                            printf("Erreur! \n");
                        }
                        return;
                    }
                    if(tire==1)
                    {
                        system("cls");
                        printf("\nVous avez perdu le jeu. Bonne chance pour la prochaine fois\n");
                        return;
                    }
                }
                break;

            case 4:
                Loguer("Le joueur a vu les socres");
                system("cls");
                printf("\nVoici les scores\n\n");
                // lire le fichier et afficher les scores
                fichier=fopen("socre.txt","r");
                if(fichier!=NULL)
                {
                    while(score!=EOF)
                    {
                        score=getc(fichier);
                        printf("%c",score);
                    }
                    fclose(fichier);
                }
                else
                {
                    printf("\n\nErreur\n");
                }
                return;

            default:
                printf("\n\nVotre choix n'est pas valid\n\n");
                system("pause");
                system("cls");
        }


    }
    return 0;
}
