// PROIECT PROGRAMARE PROCEDURALA
// AUTOR: ISPAS ADRIAN, FACULTATEA DE MATEMATICA SI INFORMATICA, UNIVERSITATEA DIN BUCURESTI
// SPECIALIZAREA: INFORMATICA
// AN: I
// GRUPA: 143

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int ok, pin_ok, i, j, sw, intoarecere = 1, bancnote_v [5] = {500, 200, 100, 50, 10}, informatii[100][3],
    nr_conturi, tranzactii[100][12], id_cont, x, nr_total = 1;

char optiune, nume[25];

struct cont
    {
        char nume[25];
        int nr_cont;

    } utilizator[100];

struct data
    {
        struct
            {
                char date[30];
            } nr_tranz[100];

    } d_tranz[100];

void afisare_instructiuni()
    {
        system("cls");

        printf("\n 1: In 'Interogare sold' veti gasi suma dvs. disponibila din contul accesat.");
        printf("\n");
        printf("\n 2: In 'Depunere numerar' veti o suma in contul dvs.\n   Depunere se face prin introducerea nr. de bancnote si valoarea acestora.\n   De exemplu 2 bancnote cu valoarea de 100 lei.");
        printf("\n");
        printf("\n 3: In 'Retragere numerar' veti putea retrage o suma disponibila din contul dvs.\n   accesat.\n   ATENTIE! Aceasta suma trebuie sa fie multiplu de 10.\n   Daca suma este multiplu de 10 si exista in contul dvs., la final veti\n   veti primi bancnotele retrase.");
        printf("\n");
        printf("\n 4: In 'Creare cont' puteti crea un nou cont prin introducerea numelui si \n   prenumeleui.\n   Dupa crearea acestuia veti fi redirectionat catre lista de conturi active\n   de unde puteti accesa contul nou creat.");
        printf("\n");
        printf("\n 5: In 'Istoric tranzactii' veti putea vedea ultimele 5 tranzactii sub tipul\n   acesteia si data la care s-a efectuat.");
        printf("\n");
        printf("\n 6: In 'Afisare conturi' veti putea vedea toate conturile dvs. active.");
        printf("\n");
        printf("\n 7: In 'Revenire la conturi' veti fi redirectionat catre lista de conturi unde\n   puteti accesa un alt cont.");
        printf("\n");
        printf("\n 8: In 'Resetare PIN' va puteti reseta PIN-ul din contul pe care va aflati in\n   momentul respectiv prin introducerea actualului cod si noului cod PIN.");

        printf("\n\n   ");
        system ("PAUSE");
        meniu();
    }

void citire_conturi()
    {
        char nume[25];
        i = 0;

        FILE *f = fopen("conturi_bancare.txt","r");

        fscanf(f,"%d",&nr_conturi);

        while (!feof(f))
            {
                i++;

                fscanf(f,"%d",&utilizator[i].nr_cont);

                fscanf(f,"%s",&utilizator[i].nume);

                fscanf(f,"%s",&nume);
                strcat(utilizator[i].nume," ");

                strcat(utilizator[i].nume,nume);
            }

        fclose(f);
    }

void scriere_conturi()
    {

        FILE *f = fopen("conturi_bancare.txt","w");

        fprintf(f,"%d\n",nr_conturi);

        for (i = 1; i <= nr_conturi; i++)
            fprintf(f,"%d %s\n",utilizator[i].nr_cont,utilizator[i].nume);

        fclose(f);

    }

void citire_informatii()
    {
         FILE *info = fopen("informatii_conturi.txt","r");
         FILE *t = fopen("tranzactii_conturi.txt","r");
         FILE *d = fopen("date_tranzactii.txt","r");

         for (i = 1; i <= nr_conturi; i++)
            for (j = 1; j <= 3; j++)
                fscanf(info, "%d", &informatii[i][j]);

         for (i = 1; i <= 12; i++)
            for (j = 1; j <= 12; j++)
                fscanf(t,"%d",&tranzactii[i][j]);

         for (i = 1; i <= nr_conturi; i++)
            for (j = 1; j <= 12; j++)
            {
                fscanf(d,"%d",&x);
                //fscanf(d,"%d",&x);
                //fscanf(d,"%s\n",&d_tranz[x].nr_tranz[j].date);
                fgets(d_tranz[i].nr_tranz[j].date,35,d);
            }

         fclose(info);
         fclose(t);
         fclose(d);
    }

void scriere_informatii()
    {
        FILE *info = fopen("informatii_conturi.txt","w");
        FILE *t = fopen("tranzactii_conturi.txt","w");
        FILE *d = fopen("date_tranzactii.txt","w");

        for (i = 1; i <= nr_conturi; i++)
            {
                for (j = 1; j <= 3; j++)
                    fprintf(info, "%d ", informatii[i][j]);
                fprintf(info,"\n");
            }

        for (i = 1; i <= 12; i++)
            {
                for (j = 1; j <= 12; j++)
                    fprintf(t,"%d ",tranzactii[i][j]);
                fprintf(t,"\n");
            }

        for (i = 1; i <= nr_conturi; i++)
           for (x = 1; x <= 12; x++)
                if(d_tranz[i].nr_tranz[x].date)
                    fprintf(d,"%d%s\n",i,d_tranz[i].nr_tranz[x].date);


         fclose(info);
         fclose(t);
         fclose(d);
    }

void creare_pin()
    {
        system ("cls");
        printf ("\n Deoarece este prima dvs. accesare a contului va rugam sa setati un cod PIN.\n Introduceti codul PIN ce il veti folosi in viitor pentru acest cont.\n Cod PIN (4 cifre): ");
        scanf ("%d", &pin_ok);

        informatii[id_cont][1] = pin_ok;
        acces_pin();

    }

void acces_pin()
    {
        system ("cls");
        int pin, incercari = 2;

        pin_ok = informatii[id_cont][1];

        if (pin_ok)
            {
                printf ("\n Va rugam introduceti codul PIN: ");
                scanf  ("%d", &pin);

                while (incercari && pin != pin_ok)
                    {
                        printf ("\n Codul PIN introdus este gresit!\n Va rugam introduceti un nou cod PIN: ");
                        scanf  ("%d", &pin);

                        incercari --;
                    }

                if (pin == pin_ok)
                    ok = 1;
                else
                    iesire();
            }
        else
            creare_pin ();

    }

void sold()
    {
        system("cls");

        printf ("\n Soldul dvs. curent este: %d LEI\n", informatii[id_cont][2]);

        printf("\n ");
        system("PAUSE");
        meniu();
    }

void depunere()
    {
        int bancnota, nr;
        i = 1;

        time_t rawtime;
        struct tm * timeinfo;

        time (&rawtime);
        timeinfo = localtime (&rawtime);

        system("cls");

        printf ("\n Va rugam sa nr. de bancnote si tipul acestora.\n Numarul de bancnote: ");
        scanf("%d",&nr);

        do
            {
                printf(" Tipul de bancnote (doar bancnote valide): ");
                scanf("%d",&bancnota);
            }
        while(bancnota != 500 && bancnota != 200 && bancnota != 100 && bancnota != 50 && bancnota != 10 && bancnota != 5 && bancnota != 1);

        informatii[id_cont][2] += nr * bancnota;

        printf ("\n Tranzactie efectuata cu succes!\n ");

        for (i = 12; i >=2 ; i--)
            {
               tranzactii[id_cont][i] = tranzactii[id_cont][i - 1];
               strcpy(d_tranz[id_cont].nr_tranz[i].date,d_tranz[id_cont].nr_tranz[i - 1].date);
            }

        for (i = 12; i >=2 ; i--)
            {
                tranzactii[id_cont][i] = tranzactii[id_cont][i - 1];
                strcpy(d_tranz[id_cont].nr_tranz[i].date,d_tranz[id_cont].nr_tranz[i - 1].date);
            }

        tranzactii [id_cont][3] = nr * bancnota;
        tranzactii [id_cont][2] = 1;
        strcpy(d_tranz[id_cont].nr_tranz[2].date,asctime(timeinfo));

        system("PAUSE");

        meniu();

    }

void retragere()
    {
        int suma, suma2;

        time_t rawtime;
        struct tm * timeinfo;

        time (&rawtime);
        timeinfo = localtime (&rawtime);

        system ("cls");

        do
            {
                printf ("\n Intrduceti suma pe care doriti sa o retrageti (multiplu de 10): ");
                scanf ("%d", &suma);
            }
        while (suma % 10 != 0);

        suma2 = suma;

        if (informatii[id_cont][2] >= suma)
            {
             informatii[id_cont][2] -= suma;
             printf(" Bancnote retrase: ");
             while (suma)
                for (i = 0; i < 5; i ++)
                    for (j = 0; j < 5; j ++)
                        {
                            if (suma >= bancnote_v [j])
                                {
                                    printf ("%d\n                   ", bancnote_v [j]);
                                    suma -= bancnote_v[j];
                                }

                        }
             printf("\n Tranzactie efectuata cu succes!");

             for (i = 12; i >=2 ; i--)
                {
                    tranzactii[id_cont][i] = tranzactii[id_cont][i - 1];
                    strcpy(d_tranz[id_cont].nr_tranz[i].date,d_tranz[id_cont].nr_tranz[i - 1].date);
                }

             for (i = 12; i >=2 ; i--)
                {
                    tranzactii[id_cont][i] = tranzactii[id_cont][i - 1];
                    strcpy(d_tranz[id_cont].nr_tranz[i].date,d_tranz[id_cont].nr_tranz[i - 1].date);
                }

             tranzactii [id_cont][3] = suma2;
             tranzactii [id_cont][2] = 2;
             strcpy(d_tranz[id_cont].nr_tranz[2].date,asctime(timeinfo));

            }
        else
            printf ("\n Ne pare rau, dar nu dispuneti de suma respectiva in cont!");


       printf("\n ");
       system("PAUSE");
       meniu();
    }

void iesire ()
    {
      system("cls");
      printf ("\n           Va dorim o zi excelenta!\n");
      scriere_conturi();
      scriere_informatii();
    }

void creare_cont()
    {
        system("cls");
        printf("\n Va rugam sa introduceti numele dvs. sub forma <Nume Prenume>: ");

        nr_conturi++;
        scanf("%s",&utilizator[nr_conturi].nume);
        scanf("%s",&nume);

        strcat(utilizator[nr_conturi].nume," ");
        strcat(utilizator[nr_conturi].nume,nume);
        utilizator[nr_conturi].nr_cont = nr_conturi;

        printf("\n Contul dvs. a fost creat cu succes!\n ");
        system("PAUSE");
        alegere_cont();
    }

void afisare_conturi()
    {
        system("cls");
        for(i = 1; i <= nr_conturi; i++)
            printf("\n %d. %s",i,utilizator[i].nume);

        printf("\n\n Apasati orice tasta pentru a reveni la meniu.\n ");
        system("PAUSE");
        meniu();
    }

void alegere_cont()
    {
            system("cls");

            for(i = 1; i <= nr_conturi; i++)
                printf("\n %d. %s",i,utilizator[i].nume);

            printf("\n\n Va rugam sa alegeti un cont din lista de mai sus.\n ATENTIE! Introduceti doar numarul acestuia, de exemplu '1'.");
            printf("\n Cont: ");
            scanf("%d",&id_cont);

            cont_ales();

    }

void cont_ales()
    {
        acces_pin();

        if (ok == 1)
            meniu();
        else
            {
                system("cls");
                printf("\n Codul PIN introdus este gresit!\n Veti fi redirectionat catre iesire din sistem\n\n ");
                system("PAUSE");
                iesire();
            }
    }

void tranzactii_cont()
    {
        int t_d = 0;
        system("cls");

        for(i = 2; i < 12; i ++)
            if(tranzactii[id_cont][i])
                if(tranzactii[id_cont][i] == 1)
                    {
                     printf("\n Depunere de %d LEI la %s", tranzactii[id_cont][i+1], d_tranz[id_cont].nr_tranz[i].date);
                     t_d = 1;
                    }
                else
                    if(tranzactii[id_cont][i] == 2)
                        {
                         printf("\n Retragere de %d LEI la %s", tranzactii[id_cont][i+1], d_tranz[id_cont].nr_tranz[i].date);
                         t_d = 1;
                        }

        if (t_d == 0)
            printf ("\n Nu s-au efectuat tranzactii in contul dvs. pana in prezent.");
        printf("\n\n ");
        system("PAUSE");
        meniu();


    }

void resetare_pin()
    {
        int pin_actual;

        system("cls");

        printf ("\n Va rugam sa introduceti actualul cod PIN: ");
        scanf("%d",&pin_actual);

        if (pin_actual == pin_ok)
            {
                printf ("\n Va rugam sa introduceti noul cod PIN: ");
                scanf("%d",&pin_ok);
                informatii[id_cont][1] = pin_ok;
            }
        else
            printf("\n Codurile PIN nu corespund!");

            printf("\n ");
            system("PAUSE");
            alegere_cont();
    }

void meniu()
    {
        system("cls");

        printf ("\n                   Bine ati venit!\n Va rugam sa alegeti una dintre optiunile de mai jos!\n\n");
        printf (" 0. Instructiuni de utilizare.\n");
        printf (" 1. Interogare sold\n");
        printf (" 2. Depunere numerar\n");
        printf (" 3. Retragere numerar\n");
        printf (" 4. Creare cont\n");
        printf (" 5. Istoric tranzactii\n");
        printf (" 6. Afisare conturi\n");
        printf (" 7. Revenire la conturi\n");
        printf (" 8. Resetare PIN\n");
        printf (" 9. Iesire\n\n");

        printf(" Opiunea dvs: ");
        scanf("%d", &sw);

        switch (sw)
            {
                case 0: afisare_instructiuni(); break;
                case 1: sold(); break;
                case 2: depunere(); break;
                case 3: retragere(); break;
                case 4: creare_cont(); break;
                case 5: tranzactii_cont(); break;
                case 6: afisare_conturi(); break;
                case 7: alegere_cont(); break;
                case 8: resetare_pin(); break;
                case 9: iesire(); break;

                default: meniu();

            }
    }

int main()
{
    citire_conturi();

    citire_informatii();

    if(nr_conturi)
        {
            printf("\n                          Bun venit!\n");
            printf("\n Doriti sa alegeti un cont din lista sau sa introduceti dvs. unu?\n Pentru a alege din lista apasati A, iar pentru a introduce apasati orice tasta.");
            printf("\n Opiunea dvs.: ");
            scanf("%s",&optiune);

            if (optiune == 'a' || optiune == 'A')
                alegere_cont();
            else
                {
                    system("cls");
                    printf("\n Va rugam sa introduceti un numar de cont intre 1 si %d.\n Nr.Cont: ",nr_conturi);
                    scanf ("%d",&id_cont);
                    cont_ales();

                }

        }
    else
        {   printf("\n                          Bun venit!\n\n Deoarece sunteti la prima dvs. aceesare a sistemului nu dispuneti de cont activ Pentru a putea tranzactiona aveti nevoie de un cont pe care il puteti crea\n la pasul urmator.\n\n ");
            system("PAUSE");
            system("cls");
            printf("\n Nu ati creat niciun cont pana acum. Doriti sa realizati un cont?\n Pentru DA apasati tasta D, iar pentru NU apasati orice tasta.\n Optiunea dvs: ");
            scanf("%s",&optiune);

            if (optiune == 'd' || optiune == 'D')
                    creare_cont();
            else
                iesire();
        }

    return 0;
}
