#include "arbre.h"
#define SIZE_TAB_INIT 20

int main()
{

    
    Genealogie g;
    genealogieInit(&g);
    ident ia = adj(&g, "Arthur", 0, 0, creationDate(9, 11, 1879), creationDate(12, 11, 1934));
    ident im = adj(&g, "Marcel", ia, 0, creationDate(1, 7, 1928 ), creationDate (21, 9, 2004 ));
    ident ic = adj(&g, "Clothilde", 0, 0, creationDate(30, 8, 1929), creationDate(26, 4, 2005 ));
    ident ije = adj(&g, "Jeanne", im, ic, creationDate(13,4, 1948), creationDateVide());   
    ident ihe = adj(&g, "Henri", 0,0, creationDate(2,8, 1947), creationDateVide());
    ident ial = adj(&g, "Aline", 0,0, creationDate (7,9, 1943 ), creationDateVide());
    ident ipi = adj(&g, "Pierre", 0, 0, creationDate( 26,6, 1941 ), creationDateVide());
    ident iju = adj(&g, "Julien", ipi, ial, creationDate( 13,8, 1965 ), creationDateVide());
    ident ialex = adj(&g, "Alex", ipi, ial, creationDate( 18,4, 1969 ), creationDateVide());
    ident iso = adj(&g, "Sophie", ihe, ije, creationDate( 9,11, 1972), creationDateVide());
    ident icl = adj(&g, "Clementine", ihe, ije, creationDate( 12,10, 1973 ), creationDateVide());
    ident ima = adj(&g, "Marion", ihe, ije, creationDate( 5,5, 1976 ), creationDateVide());
    ident ich = adj(&g, "Christian", 0, 0, creationDate( 13,2, 1971 ), creationDateVide());
    ident itho = adj(&g, "Thomas", ialex, iso, creationDate( 18,10, 2012 ), creationDateVide());
    ident icloe = adj(&g, "Cloe", ialex, iso, creationDate( 21,6, 2002 ), creationDateVide());
    ident ihu = adj(&g, "Hugo", ialex, iso, creationDate( 12,5, 2005 ), creationDateVide());
    ident isa = adj(&g, "Isabelle", ich, ima, creationDate( 28,4, 2003 ), creationDateVide());
    Genealogie g2;
    genealogieInit(&g2);
    ident ija = adj(&g2, "Jacques", 0, 0, creationDate(9, 11, 1899), creationDate(12, 12, 1974));
    ident imar = adj(&g2, "Marie", 0, 0, creationDate(12, 4, 1897), creationDate(15, 6, 1970));
    ident ian = adj(&g2, "Anna", ija, imar, creationDate(7, 1, 1930), creationDate(20, 3, 2000));
    ident ijea = adj(&g2, "Jeannine", ija, imar, creationDate(19, 7, 1950), creationDateVide());
    ident ili = adj(&g2, "Lucie", ija, imar, creationDate(24, 10, 1940), creationDate(30, 11, 2005));
    ident ila = adj(&g2, "Lucas", 0, 0, creationDate(13, 10, 1933), creationDateVide());
    ident ichr = adj(&g2, "Christian", ila, ian, creationDate(13, 2, 1971), creationDateVide()); 
    ident iluc = adj(&g2, "luc", ila, ian, creationDate(3, 6, 1966), creationDateVide());
    ident ipie = adj(&g2, "Pierre", 0, 0, creationDate(19, 7, 1971), creationDateVide());
    ident iji = adj(&g2, "Jimmy", ipie, ili, creationDate(3, 8, 2001), creationDateVide());
    ident iad = adj(&g2, "Adrien", 0, 0, creationDate(2, 8, 1951), creationDateVide());
    ident ijui = adj(&g2, "Justine", 0, 0, creationDate(28, 9, 1955), creationDateVide());
    ident ichl = adj(&g2, "Chloe", iad, ijui, creationDate(7, 2, 1959), creationDateVide());
    ident ifab = adj(&g2, "Fabien", iluc, ichl, creationDate(12, 3, 1990), creationDateVide());
    if(freres_soeurs(&g,icloe,itho)==true)
    {
        printf("Ils sont frere et soeurs \n");
    }else
    {
        printf("Il ne sont pas frere ou soeurs \n");
    }
    
    
    affichage_current(&g);
    printf("====================\n");
    printf("Test du get Individu : \n");
    Individu* indi=get(&g,2);
    printf("%s \n",indi->nom);

    printf("====================\n");
    
    printf("Teste affichage freres et soeur\n");
    printf("Teste 1 en prennant l'ainée \n");
    affiche_freres_soeurs(&g,iso);
    printf("Teste 2 en prennant le cadet \n");
    affiche_freres_soeurs(&g,icl);

    printf("====================\n");

    printf("Teste affichage enfant \n");
    printf("Teste avec un enfant \n");
    affiche_enfants(&g,ije);
    printf("Teste 2 sans enfants \n");
    affiche_enfants(&g,iju);

    printf("====================\n");

    printf("Teste affichage cousin \n");
    printf("Teste avec cousin existant \n");
    affiche_cousins(&g,isa);
    printf("Teste sans cousin \n");
    affiche_cousins(&g,iju);

    printf("====================\n");

    printf("Teste affichage des oncles/tantes \n");
    printf("Teste avec oncles/tantes \n");
    affiche_oncles(&g,itho);
    printf("Teste sans oncles/tante connues \n");
    affiche_oncles(&g,ije);

    printf("====================\n");
    
    printf("Teste Y ancetre de X \n");
    if (ancetre(&g,itho,ial)==true)
    {
        printf("c'est bien un de ses ancetres \n");
    }else
    {
        printf("Ce n'est pas de ses ancetres \n");
    }
    printf("Teste X ancetre de Y \n");
    if(ancetre(&g,ial,itho)==true)
    {
        printf("C'est bien un de ses ancetres \n");
    }else
    {
        printf("Ce n'est pas de ses ancetres \n");
    }
    printf("TESTE Julien ancetre de Thomas \n");
    if(ancetre(&g,iju,itho))
    {
        printf("C'est bien un de ses ancetres \n");
    }else
    {
        printf("Ce n'est pas de ses ancetres \n");
    }
    printf("TESTE Clothilde ancetre de Chloé \n");
    if(ancetre(&g,ic,icloe))
    {
        printf("C'est bien un de ses ancetres \n");
    }else
    {
        printf("Ce n'est pas de ses ancetres \n");
    }
    printf("TESTE Pierre ancetre de Isabelle (FAUX) \n");
    if(ancetre(&g,ipi,isa))
    {
        printf("C'est bien un de ses ancetres \n");
    }else
    {
        printf("Ce n'est pas de ses ancetres \n");
    }
    printf("====================\n");

    printf("TESTE ANCETRE COMMUN \n");
    printf("TESTE Hugo ET Julien (vrai) \n");
    if(ancetreCommun(&g,ihu,iju))
    {
        printf("true\n");
    }else{
        printf("false\n");
    }

    printf("TESTE Hugo ET Christian (FAUX) \n");
    if(ancetreCommun(&g,ihu,ich))
    {
        printf("true\n");
    }else{
        printf("false\n");
    }
    printf("====================\n");
    printf("TESTE PLUS VIEUX \n");
    
    ident plusvi=plus_ancien(&g,ihu);
    Individu* ind_plusvi=get(&g,plusvi);
    printf("Je suis %s l'ancetre le plus vieu de Hugo (ARTHUR) \n",ind_plusvi->nom);
    
    plusvi=plus_ancien(&g,ialex);
    ind_plusvi=get(&g,plusvi);
    printf("Je suis %s l'ancetre le plus vieu de Alex (PIERRE) \n",ind_plusvi->nom);
    printf("====================\n");
    printf("TESTE parenté de cloé \n");
    affiche_parente(&g,icloe); 
    printf("====================\n");
    printf("TESTE descendance de Arthur \n");
    affiche_descendance(&g,ia);
    printf("====================\n");
    printf("TESTE Fusion \n");
    affichage_current(&g2);
    Genealogie g3;
    genealogieInit(&g3);
    genealogieFusion(&g3,&g2,&g);
    affichage_current(&g3);

    
    return 0;
}