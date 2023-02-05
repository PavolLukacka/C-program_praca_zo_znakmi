#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STROP 50 //Definovane maximum
#define LIM 20  //Definovany limit povolenych zadanych prvkov

//Funkcie
void samohl_spoluhl(char *s, char *pol_sam, char *pol_spol, int *poc_samohl, int *poc_spoluhl);
void interp_z_cisla(char *p, char *pol_cis, char *pol_interpunk, char *pol_ineznak, char *pol_medzier, int *poc_cisel, int *poc_interp_z, int *poc_ine_znaky, int *poc_medzier);
void alloc(char **data);
void realoc(char **data, int length);
void print_first_char(char *input);

//---------------------------------------------------------------------------------------------------------------------

int main()
{
    int poc_samohl = 0, poc_spoluhl = 0, poc_cisel = 0, poc_interp_z = 0, poc_ine_znaky = 0, poc_medzier = 0;
    char *ret_znakov, *pol_sam, *pol_spol, *pol_cis, *pol_interpunk, *pol_ineznak, *pol_medzier;

    alloc(&ret_znakov);
    alloc(&pol_sam);
    alloc(&pol_spol);
    alloc(&pol_cis);
    alloc(&pol_interpunk);
    alloc(&pol_ineznak);
    alloc(&pol_medzier);

    printf("Zadaj %d znakov (pozor, medzera sa rata ako znak!). \nProgram nasledne zrata a vypise pocet samohlasok, spoluhlasok, interpunkcnych znamienok, cislic a inych znakov.\n",LIM);
    fflush(stdin);
    fgets(ret_znakov,LIM+1,stdin);

    printf("\n Zadane znaky su: %s \n",ret_znakov);

    samohl_spoluhl(ret_znakov,pol_sam, pol_spol, &poc_samohl, &poc_spoluhl); //Zavolanie prvej funkcie
    realoc(&pol_sam,poc_samohl);
    realoc(&pol_sam,poc_spoluhl);

    printf(" Pocet samohlasok: %d ", poc_samohl);
    if(poc_samohl > 0)
    {
        printf(" zadane samohlasky su:");
    }
    for(int i=1; i<=poc_samohl; i++)
    {
        print_first_char(&pol_sam[i]);
        if(i<poc_samohl)
        {
            printf(",");
        }
    }
    printf("\n\n");

    printf(" Pocet spoluhlasok: %d ", poc_spoluhl);
    if(poc_spoluhl > 0)
    {
        printf(" zadane spoluhlasky su:");
    }
    for(int i=1; i<=poc_spoluhl; i++)
    {
        print_first_char(&pol_spol[i]);
        if(i<poc_spoluhl)
        {
            printf(",");
        }
    }
    printf("\n\n");

    interp_z_cisla(ret_znakov, pol_cis, pol_interpunk, pol_ineznak, pol_medzier, &poc_cisel, &poc_interp_z, &poc_ine_znaky, &poc_medzier); //Zavolanie druhej funkcie
    realoc(&pol_cis,poc_samohl);
    realoc(&pol_interpunk,poc_interp_z);
    realoc(&pol_ineznak,poc_ine_znaky);
    realoc(&pol_medzier,poc_medzier);

    printf(" Pocet cisel: %d ", poc_cisel);
    if(poc_cisel > 0)
    {
        printf(" zadane cisla su:");
    }
    for(int i=1; i<=poc_cisel; i++)
    {
        print_first_char(&pol_cis[i]);
        if(i<poc_cisel)
        {
            printf(",");
        }
    }
    printf("\n\n");

    printf(" Pocet interpunkcnych znamienok: %d ", poc_interp_z);
    if(poc_interp_z > 0)
    {
        printf(" zadane interpunkcne znamienka su:");
    }
    for(int i=1; i<=poc_interp_z; i++)
    {
        print_first_char(&pol_interpunk[i]);
        if(i<poc_interp_z)
        {
            printf(",");
        }
    }
    printf("\n\n");

    printf(" Pocet inych znamienok: %d ", poc_ine_znaky);
    if(poc_ine_znaky> 0)
    {
        printf(" zadane ine znamienka su:");
    }
    for(int i=1; i<=poc_ine_znaky; i++)
    {
        print_first_char(&pol_ineznak[i]);
        if(i<poc_ine_znaky)
        {
            printf(",");
        }
    }
    printf("\n\n");

    printf(" Pocet medzier: %d ", poc_medzier);
    if(poc_ine_znaky> 0)
    {
        printf(" zadane medzery su:");
    }
    for(int i=1; i<=poc_medzier; i++)
    {
        print_first_char(&pol_medzier[i]);
        if(i<poc_medzier)
        {
            printf(",");
        }
    }

    free(ret_znakov);
    free(pol_sam);
    free(pol_spol);
    free(pol_cis);
    free(pol_interpunk);
    free(pol_ineznak);
    free(pol_medzier);
    return 0;
}
//-----------------------------------------------------------------------------------------------------------------------------------

void samohl_spoluhl(char *p, char *pol_sam, char *pol_spol, int *poc_samohl, int *poc_spoluhl) //funkcia na hladanie poctu samohl. a spoluhl. pomocou ASCII tabulky
{
    int i;
    for(i=0; p[i]; i++)
    {
        if((p[i]>=65 && p[i]<=90) || (p[i]>=97 && p[i]<=122)) //porovna ci sa ASCII hodnota kazdeho znaku nachadza
        {
            if(p[i]=='a' || p[i]=='e' || p[i]=='i' || p[i]=='y'|| p[i]=='o' || p[i]=='u' || p[i]=='A' || p[i]=='E' || p[i]=='I' || p[i]=='O' || p[i]=='U' || p[i]=='Y') //znak porovna so samohlaskami
            {
                (*poc_samohl)++; //pokial znak je samohlaskou, zvysi sa hodnota integeru samohlasky
                pol_sam[*poc_samohl] = p[i];
            }
            else
            {
                (*poc_spoluhl)++; //pokial znak nie je samohlaskou, zvysi sa hodnota integeru spoluhlasky
                pol_spol[*poc_spoluhl] = p[i];

            }
        }
    }
}

void interp_z_cisla(char *p, char *pol_cis, char *pol_interpunk, char *pol_ineznak, char *pol_medzier, int *poc_cisel, int *poc_interp_z, int *poc_ine_znaky, int *poc_medzier) //funkcia na hladanie poctu samohl. a spoluhl. pomocou ASCII tabulky
{
    int i;
    for(i=0; p[i]; i++)
    {
        if((p[i]>=32 && p[i]<=64) || (p[i]>=91 && p[i]<=96) || (p[i]>=123 && p[i]<=126))
        {
            if(p[i]=='0' || p[i]=='1' || p[i]=='2' || p[i]=='3' || p[i]=='4' || p[i]=='5' || p[i]=='6' || p[i]=='7' || p[i]=='8' || p[i]=='9')
            {
                (*poc_cisel)++; //ak je znak cislo, navysi sa hodnota poc_cisel
                pol_cis[*poc_cisel] = p[i];
            }
            else if(p[i]=='.' || p[i]==',' || p[i]==';' || p[i]==':' || p[i]=='-' || p[i]=='/' || p[i]=='!' || p[i]=='?' || p[i]=='(' || p[i]==')' || p[i]=='[' || p[i]==']' || p[i]=='{' || p[i]=='}' || p[i]=='"')
            {
                (*poc_interp_z)++; //ak znak nie je cislo, navysi sa hodnota poc_interp_z
                pol_interpunk[*poc_interp_z] = p[i];
            }
            else if(p[i]==' ')
            {
                (*poc_medzier)++;
                pol_medzier[*poc_medzier] = p[i];
            }
            else
            {
                (*poc_ine_znaky)++; //ak znak nie je cislo, navysi sa hodnota poc_interp_z
                pol_ineznak[*poc_ine_znaky] = p[i];

            }
        }
    }
}
void alloc(char **data)
{
    *data = malloc(sizeof(char)*STROP+1);
    if(NULL==*data)
    {
        printf("Nedostatok pamate. \n");
    }

}
void realoc(char **data, int length)
{
    realloc(*data, sizeof(char)*length);
}
void print_first_char(char *input)
{
    printf(" '%c' ", input[0]);
}
