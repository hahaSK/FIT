/**
 * Autor: Juraj Lahvička, 164322
 * ID: xlahvi00
 * Predmet: IZP
 * Názov: projekt1 - práca s textom
 * URL: https://wis.fit.vutbr.cz/FIT/st/cwk.php?title=IZP:Projekt1&csid=647749&id=12214
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAXSIZE (42)
#define MAXBUFSIZE (101)

/**
 * načítanie miest zo súboru Adresy do poľa znaky_miest
 * @param znaky_miest - dvojrozmerné pole znakov miest zo súboru Adresy
 * @return vracia počet miest (počet riadkov), ak je zadaný nepodporovaný znak vráti -1
 */

int nacitanie_adries(int znaky_miest[MAXSIZE][MAXBUFSIZE])
{
    int c=0, i=0, pocet_miest=0;
    while((c=getchar())!=EOF)
    {

        if(c=='\n')
        {
            znaky_miest[pocet_miest][i]='\0';
            pocet_miest++;
            i=0;
        }

        if(c==0 || c=='\n')
        {
            continue;
        }

        if(isalpha(c)==0 && isspace(c)==0)
        {
            printf("ERROR: Wrong character in Addresses\n");
            return -1;
        }

        //Prevod na velke;
        c=toupper(c);
        znaky_miest[pocet_miest][i]=c;
        i++;
    }
    return pocet_miest;
}

/**
 * abecedné zoradenie povolených znakov
 * @param enable_chars - povolené znaky
 */

void zoradenie_abecedne(char enable_chars[MAXBUFSIZE])
{
    char abecedne[26]={0};              //26 je počet prvkov od A po Z v ASCII
    int i=0,x=0;
    bool is_space=false;

    while(enable_chars[i])
    {
        abecedne[enable_chars[i]-'A']=enable_chars[i];
        i++;
    }

    //vyhladanie medzery
    if(strchr(enable_chars,32))     //32 je space (medzera)
        is_space=true;

    //resetovanie premennej enable_chars
    memset(enable_chars,0,i);

    for(i=0;i<26;i++)
    {
        if(abecedne[i]!='\0')
        {
            enable_chars[x]=abecedne[i];
            x++;
        }
    }

    if(is_space==true)
        enable_chars[strlen(enable_chars)]=32;

}

/**
 * funkcia sa vykoná ak používateľ nezadal žiadny argument
 * @param znaky_miest - dvojrozmerné pole znakov miest zo súboru Adresy
 * @param pocet_miest - počet miest (možno povedať aj ako počet riadkov v súbore Adresy)
 */
void Ziadny_argument(int znaky_miest[MAXSIZE][MAXBUFSIZE], int pocet_miest)
{
    char enable_chars[MAXBUFSIZE]={0};
    int i=0;

    while(i<pocet_miest)
    {
        enable_chars[i]=znaky_miest[i][0];
        i++;
    }

    zoradenie_abecedne(enable_chars);
    printf("Enable: %s\n",enable_chars);
}

/**
 * načítanie mesta do premennej
 * @param znaky_miest - dvojrozmerné pole znakov miest zo súboru Adresy
 * @param mesto - dané mesto zo súboru Adresy (daný riadok zo súboru Adresy)
 * @param riadok - pozícia riadku
 */

void nacitanie_mesta(int znaky_miest[MAXSIZE][MAXBUFSIZE], char mesto[MAXBUFSIZE], int riadok)
{
    int x=0;

    while(znaky_miest[riadok][x])
    {
        mesto[x]=znaky_miest[riadok][x];
        x++;
    }
}

/**
 * porovnávanie zadaného argumentu a jednotlivých miest
 * @param argv - užívateľom zadaný argument
 * @param znaky_miest - dvojrozmerné pole znakov miest zo súboru Adresy
 * @param pocet_miest - počet miest (možno povedať aj ako počet riadkov v súbore Adresy)
 * @param argc - počet zadaných argumentov
 */

void Porovnavanie(char **argv, int znaky_miest[MAXSIZE][MAXBUFSIZE], int pocet_miest)
{
    int i=0,pocet_enabled_znakov=0, pocet_approx_najdenych=0;
    char enable_chars[MAXBUFSIZE]={0}, argument[MAXBUFSIZE]={0}, mesto[MAXBUFSIZE]={0}, found[MAXBUFSIZE]={0};
    bool found_same=false, enable=false, found_one_word_left=false;


    strcpy(argument,argv[1]);

//presne vyhladavanie
    while(i<pocet_miest)
    {
        nacitanie_mesta(znaky_miest,mesto,i);

        if(strcmp(argument,mesto)==0)
        {
            strcpy(found,argument);
            printf("Found: %s\n",found);
            found_same=true;
        }

        //reset premennej mesto
        memset(mesto,0,sizeof(mesto));

        i++;
    }

//vyhladavanie Enable
    i=0;
    while(i<pocet_miest)
    {
        nacitanie_mesta(znaky_miest,mesto,i);

        int pocet_ostavajucich_znakov=strlen(mesto) - strlen(argument);
        if((strncmp(argument,mesto,strlen(argument))==0) && (pocet_ostavajucich_znakov)>1)
        {
            enable_chars[pocet_enabled_znakov++]=mesto[strlen(argument)];
            //return 0;
            enable=true;
        }

        //reset premennej mesto
        memset(mesto,0,sizeof(mesto));

        i++;
    }

//ostava iba jeden znak
    i=0;
    while(i<pocet_miest)
    {

        nacitanie_mesta(znaky_miest,mesto,i);
        int pocet_ostavajucich_znakov=strlen(mesto) - strlen(argument);

        if((strncmp(argument,mesto,strlen(argument))==0) && (pocet_ostavajucich_znakov==1) && (found_one_word_left==false))
        {
            strcpy(found,mesto);
            pocet_approx_najdenych++;
            found_one_word_left=true;
        }
        else if((strncmp(argument,mesto,strlen(argument))==0) && (pocet_ostavajucich_znakov==1) && (found_one_word_left==true))
        {
            enable_chars[strlen(enable_chars)]=found[strlen(found)];
            enable_chars[strlen(enable_chars)]=mesto[strlen(argument)];
            pocet_approx_najdenych++;
        }

        //reset premennej mesto
        memset(mesto,0,sizeof(mesto));

        i++;
    }

    if((found_same==false) && (found_one_word_left==false) && (enable==false))
    {
        printf("Not found\n");
        return;
    }

    if( (pocet_approx_najdenych==true) && ((pocet_approx_najdenych)==1) && (found_same==false) )
    {
        printf("Found: %s\n",found);
    }
    else if((enable==true) || (found_one_word_left==true))
    {
        zoradenie_abecedne(enable_chars);
        printf("Enable: %s\n",enable_chars);
    }

}


int main(int argc, char *argv[])
{
    int i=0, pocet_miest=0;
    int znaky_miest[MAXSIZE][MAXBUFSIZE];

    //načítanie adries a prevod na veľké písmená
    pocet_miest=nacitanie_adries(znaky_miest);
    if(pocet_miest==-1)
        return -1;

    //nebol zadany ziadny argument
    if(argc==1)
    {
        Ziadny_argument(znaky_miest,pocet_miest);
        return 0;
    }

    while(argv[1][i]!='\0')
    {
        if(isalpha(argv[1][i])==0)
        {
            printf("ERROR: Wrong character in User's input, argument at %d\n",++i);
            return -2;
        }

        argv[1][i]=toupper(argv[1][i]);
        i++;
    }

    Porovnavanie(argv,znaky_miest,pocet_miest);

    return 0;
}
