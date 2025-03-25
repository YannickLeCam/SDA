#include "arbre.h"
#define SIZE_TAB_INIT 10
//pour tester si realloc fonctionne bien
/***************ANNEXE***************/

void copieStr(char*out,char*in)
{
    int i=0;
    while (in[i]!='\0')
    {
        if (i==LG_MAX)
        {
            out[i]='\0';
            return;
        }
        out[i]=in[i];
        i++;
    }
    out[i]=in[i];
    return;
}

date creationDate(unsigned short jour, unsigned short mois, unsigned short annee)
{
    date d;
    d.jour=jour;
    d.mois=mois;
    d.annee=annee;
    return d;
}

date creationDateVide()
{
    date d;
    d.jour=0;
    d.mois=0;
    d.annee=0;
    return d;
}
//si A plus vieux que B true sinon false
bool plusVieux(Genealogie* ga, ident id_A,Genealogie* gb, ident id_B)
{
    Individu* A=get(ga,id_A);
    Individu* B=get(gb,id_B);
    if (A->naissance.annee==0&&B->naissance.annee==0)
    {
        return false;
    }
    if (A->naissance.annee==0)
    {
        return false;
    }
    if (B->naissance.annee==0)
    {
        return true;
    }
    
    
    
    if(A->naissance.annee<B->naissance.annee)
    {
        return true;
    }
    if (A->naissance.annee>B->naissance.annee)
    {
        return false;
    }
    if (A->naissance.mois<B->naissance.mois)
    {
        return true;
    }
    if (A->naissance.mois>B->naissance.mois)
    {
        return false;
    }
    if (A->naissance.jour<B->naissance.jour)
    {
        return true;
    }
        if (A->naissance.jour>B->naissance.jour)
    {
        return false;
    }
    return true;
    //si jumeau true
}
//x == ident du faine et y celui a ajouter
void ajoutCadet(Genealogie* g,ident x_ident,ident y_ident)
{
    Individu* X=get(g,x_ident);
    Individu* Y=get(g,y_ident);
    //donc Y plus jeune que X
    if(plusVieux(g,x_ident,g,y_ident)==true){
        if(X->cadet==0)
        {
            X->cadet=y_ident;
            return;
        }
        Individu* X_cadet=get(g,X->cadet);
        //si X_cadet plus jeune que Y
        if (plusVieux(g,y_ident,g,X->cadet)==true)
        {
            Y->cadet=X->cadet;
            X->cadet=y_ident;
            return;
        }
        else
        {
            ajoutCadet(g,X->cadet,y_ident);
            return;
        }
        
    }
}

int ancetre_rec(Genealogie* g, ident aTrouver,ident check)
{
    if (check==aTrouver)
    {
        return 1;
    }
    
    Individu* ind_Check=get(g,check);
    int verif=0;
    if (ind_Check->mere==0&&ind_Check->pere==0)
    {
        return 0;
    }
    if(ind_Check->mere==aTrouver)
    {
        return 1;
    }
    if (ind_Check->pere==aTrouver)
    {
        return 1;
    }
    if (ind_Check->pere!=0)
    {
        //check tout les frr/souer de l'individu
        Individu* Pere=get(g,ind_Check->pere);
        if(Pere->faine!=0){
        
            if(Pere->faine==aTrouver)
            {
                return 1;
            }
            

            Individu* Temp=get(g,Pere->faine);

            while (Temp->cadet!=0)
            {   
                if (Temp->cadet==aTrouver)
                {
                    return 1;
                }
                Temp=get(g,Temp->cadet);
                
            }
        }
    }else
    {
        //si pere n'existe pas faire avec la mere!
                //check tout les frr/souer de l'individu
        Individu* Mere=get(g,ind_Check->mere);
        if(Mere->faine!=0){
        
            if(Mere->faine==aTrouver)
            {
                return 1;
            }
            

            Individu* Temp=get(g,Mere->faine);

            while (Temp->cadet!=0)
            {   
                if (Temp->cadet==aTrouver)
                {
                    return 1;
                }
                Temp=get(g,Temp->cadet);
                
            }
        }
    }
    
    
    if(ind_Check->pere!=0){
        if(ancetre_rec(g,aTrouver,ind_Check->pere)==1)
        {
            return 1;
        }
    }
    if(ind_Check->mere!=0){
        if (ancetre_rec(g,aTrouver,ind_Check->mere)==1)
        {
            return 1;
        }
        
    }

    //si arrive ici =0 normalement 
    return verif;
}


int ancetreCommun_rec(Genealogie*g,ident ancetre_X,ident aTrouver)
{
    if (ancetre(g,ancetre_X,aTrouver))
    {
        return 1;
    }
    Individu* Ind_anc_X=get(g,ancetre_X);
    Individu* ind_atrouver=get(g,aTrouver);
    if(Ind_anc_X->mere==0&&Ind_anc_X->pere==0)
    {
        return 0;
    }
    if(Ind_anc_X->mere!=0)
    {
        if(ancetre(g,Ind_anc_X->mere,aTrouver))
        {
            return 1;
        }
        Individu* Grand_mere_X=get(g,Ind_anc_X->mere);
        if(ancetre(g,Grand_mere_X->faine,aTrouver))
        {
            return 1;
        }

        Individu* temp=get(g,Grand_mere_X->faine);
        while (temp->cadet!=0)
        {   
            if (ancetre(g,temp->cadet,aTrouver))
            {
                return 1;
            }
            temp=get(g,temp->cadet);
        }
    }else
    {
        if(Ind_anc_X->pere!=0)
        {
            if(ancetre(g,Ind_anc_X->pere,aTrouver))
            {
                return 1;
            }
            Individu* Grand_pere_X=get(g,Ind_anc_X->pere);
            if(ancetre(g,Grand_pere_X->faine,aTrouver))
            {
                return 1;
            }

            Individu* temp=get(g,Grand_pere_X->faine);
            while (temp->cadet!=0)
            {
                if (ancetre(g,temp->cadet,aTrouver))
                {
                    return 1;
                }
                temp=get(g,temp->cadet);
            }
        }
    }
    int verif=0;
    if(Ind_anc_X->mere!=0){
        verif=ancetreCommun_rec(g,Ind_anc_X->mere,aTrouver);
        if(verif==1)
        {
            return 1;
        }
    }
    if(Ind_anc_X->pere!=0){
        verif=ancetreCommun_rec(g,Ind_anc_X->pere,aTrouver);
        if (verif==1)
        {
            return 1;
        }
    }
    return verif;
}

ident affiche_ind_hauteur(Genealogie* g,ident x,int hauteur)
{
    Individu*indX=get(g,x);
    ident retour=0;
    if(hauteur==0)
    {
        affiche_freres_soeurs(g,x);
        retour=x;     
    }
    if (hauteur>0)
    {
        if (indX->mere!=0)
        {
            retour+=affiche_ind_hauteur(g,indX->mere,hauteur-1);
        }
        if (indX->pere!=0)
        {
            retour+=affiche_ind_hauteur(g,indX->pere,hauteur-1);
        }
    }
    return retour;
    
}

ident affiche_ind_hauteur_Descendance(Genealogie* g,ident x,int hauteur)
{
    ident retour=0;
    if(x==0){
        return retour;
    }
    Individu*indX=get(g,x);
    if (hauteur==0)
    {
        if(indX->faine!=0){
            affiche_enfants(g,x);
            retour+=x;
        }
    }
    if (hauteur>0)
    {
        if (indX->faine!=0)
        {
            Individu* temp=get(g,indX->faine);
            retour+=affiche_ind_hauteur_Descendance(g,indX->faine,hauteur-1);
            while (temp->cadet!=0)
            {
                
                temp=get(g,temp->cadet);
                if(temp->faine!=0){
                    retour+=affiche_ind_hauteur_Descendance(g,temp->cadet,hauteur-1);
                }
                
            }
        }
        
    }
    return retour;
    
}
//ne pas avoir de date de naissance vide
ident plus_vieux_fusion(Genealogie* g)
{
    int i=2;
    ident p_v=1;
    Individu* ind_p_v=get(g,p_v);
    Individu* temp;

    while (i<g->id_cur)
    {
        temp=get(g,i);   
        if (plusVieux(g,i,g,p_v))
        {
            ind_p_v=temp;
            p_v=i;
        }
        temp=get(g,i);
        i++;
    }
    //pour verifier si l'arbre est vide car dans fusion on va mettre une date vide
    
    if(ind_p_v->naissance.jour==0)
    {
        return 0;
    }
    return p_v;
}

bool date_identique(date d1,date d2)
{
    if(d1.annee==d2.annee&&d1.mois==d2.mois&&d1.jour==d2.jour)
    {
        return true;
    }
    return false;
}

ident est_dans_larbre(Genealogie* gres,Individu* ind_comp)
{
    int i=1;
    Individu * temp;
    while (gres->id_cur>i)
    {
        temp=get(gres,i);
        if(strcmp(ind_comp->nom,temp->nom)==0&&date_identique(ind_comp->naissance,temp->naissance))
        {
            return i;
        }
        i++;
    }
    return 0;
}

void genealogieFusion_aux(Genealogie* gres,Genealogie* g,ident a_ajouter)
{
    Individu* ind_a_ajouter=get(g,a_ajouter);
    ident est_deja=est_dans_larbre(gres,ind_a_ajouter);
    if(est_deja!=0)
    {
        Individu* a_ajouter_gres=get(gres,est_deja);
        if(a_ajouter_gres->mere==0&&ind_a_ajouter->mere!=0)
        {
            a_ajouter_gres->mere=ind_a_ajouter->mere;
        }
        if(a_ajouter_gres->pere==0&&ind_a_ajouter->pere!=0)
        {
            a_ajouter_gres->pere=ind_a_ajouter->pere;
        }
        if(a_ajouter_gres->mere!=0||a_ajouter_gres->pere!=0)
        {
            Individu* parent;
            if (a_ajouter_gres->mere!=0)
            {
                parent=get(gres,a_ajouter_gres->mere);
            }else
            {
                parent=get(gres,a_ajouter_gres->pere);
            }
            if (parent->faine==0)
            {
                parent->faine=est_deja;
            }else
            {
                ajoutCadet(gres,parent->faine,est_deja);
            }
        }
    }
    else
    {
        ident nouv_id=adj(gres,ind_a_ajouter->nom,ind_a_ajouter->pere,ind_a_ajouter->mere,ind_a_ajouter->naissance,ind_a_ajouter->deces);

        if(ind_a_ajouter->faine!=0)
        {
            Individu* fils=get(g,ind_a_ajouter->faine);
            if(fils->pere==a_ajouter){
                fils->pere=nouv_id;
            }else
            {
                fils->mere=nouv_id;
            }
            while (fils->cadet!=0)
            {
                fils=get(g,fils->cadet);
                if (fils->mere==a_ajouter)
                {
                    fils->mere=nouv_id;
                }else
                {
                    fils->pere=nouv_id;
                }
            }
        }
    }
    ind_a_ajouter->naissance=creationDateVide();
    return;
}

bool est_deja_dedans(Genealogie* g,char* s,date n)
{
    int i=1;
    Individu* temp;
    while (i<g->id_cur-1)
    {
        temp=get(g,i);
        if (strcmp(temp->nom,s)==0&&date_identique(temp->naissance,n))
        {
            true;
        }
        i++;
    }
    return false; 
    
}

/***************CONSTRUCTION*******************/

void genealogieInit(Genealogie* g)
{
    //g=(Genealogie*)malloc(sizeof(Genealogie));
    g->tab=(Individu*)malloc(sizeof(Individu)*SIZE_TAB_INIT);
    g->id_cur=1;
    g->taille_max_tab=SIZE_TAB_INIT;
    return;
}

void genealogieFree(Genealogie *g)
{
    free(g->tab);
    return;
}

ident adj(Genealogie *g, char *s, ident p, ident m, date n, date d)
{
    if(g==NULL){
        genealogieInit(g);
    }
    //pour ne pas rentrer de nom vide
    if(s=="")
    {
        return 0;
    }
    if (est_deja_dedans(g,s,n))
    {
        return 0;
    }
    
    if(g->id_cur+1==g->taille_max_tab-1)
    {
        g->tab=realloc(g->tab,g->taille_max_tab*2*sizeof(Individu));
        g->taille_max_tab*=2;
    }
    Nat cur = g->id_cur;
    copieStr(g->tab[g->id_cur-1].nom,s);
    g->tab[g->id_cur-1].mere=m;
    g->tab[g->id_cur-1].pere=p;
    g->tab[g->id_cur-1].deces=d;
    g->tab[g->id_cur-1].naissance=n;
    //Pour eviter les probleme avec les get rajoute +1 a l'id_cur avant les utilisation des get()
    g->id_cur+=1;
    if(g->tab[g->id_cur-2].mere!=0||g->tab[g->id_cur-2].pere!=0) {

        if(g->tab[g->id_cur-2].mere!=0){
            Individu* mere_indi_add=get(g,m);
            if(mere_indi_add->faine!=0)
            {
                //Individu* indi_temp=get(g,mere_indi_add->faine);
                Individu* indi_add=get(g,g->id_cur-1);
                Individu* indi_temp=get(g,mere_indi_add->faine);
                //ce if pas escentiel mais a voir pour le supr pour alléger adj()
                if(freres_soeurs(g,g->id_cur-1,mere_indi_add->faine)==true)
                {
                    //pas besoin de recursivité pour ce cas la car c'est l'ainé
                    if (plusVieux(g,g->id_cur-2,g,mere_indi_add->faine))
                    {
                        indi_add->cadet=mere_indi_add->faine;
                        mere_indi_add->faine=g->id_cur-1;
                        if(g->tab[g->id_cur-2].pere!=0){
                            Individu* pere_indi_add=get(g,p);
                            pere_indi_add->faine=g->id_cur-1;
                        }
                    }
                    else
                    {
                        //on fait appel a la recursivité pour savoir sa place dans la fraterie sachant qu'il ne peut pas etre l'ainée
                        ajoutCadet(g,mere_indi_add->faine,g->id_cur-1);
                    }
                }
            }else
            {
                //premier fils de la mere enregistré
                mere_indi_add->faine=g->id_cur-1;
                if(g->tab[g->id_cur-2].pere!=0){
                    Individu* pere_indi_add=get(g,p);
                    pere_indi_add->faine=g->id_cur-1;
                }
            }
        }else
        {
        
            Individu* pere_indi_add=get(g,p);
            
            
            if(pere_indi_add->faine!=0)
            {
            //Individu* indi_temp=get(g,mere_indi_add->faine);
            Individu* indi_add=get(g,g->id_cur-1);
            Individu* indi_temp=get(g,pere_indi_add->faine);
            //ce if pas escentiel mais a voir pour le supr pour alléger adj()
            if(freres_soeurs(g,g->id_cur-1,pere_indi_add->faine)==true)
            {
                //pas besoin de recursivité pour ce cas la car c'est l'ainé
                if (plusVieux(g,g->id_cur-1,g,pere_indi_add->faine))
                {
                    indi_add->cadet=pere_indi_add->faine;
                    pere_indi_add->faine=g->id_cur-1;
                }
                else
                {
                    //on fait appel a la recursivité pour savoir sa place dans la fraterie sachant qu'il ne peut pas etre l'ainée
                    ajoutCadet(g,pere_indi_add->faine,g->id_cur-1);
                }
            }
        
            }else
            {
                //premier fils de la mere enregistré
                pere_indi_add->faine=g->id_cur-1;
            }
            
        }
    }
    return g->id_cur-1;
}
 
Individu *get(Genealogie *g, ident x)
{
    if (x==0)
    {
        perror("EXIT_FAILLURE:ID_0_IMPOSSIBLE");
    }
    
    if(x>g->id_cur-1)
    {
        perror("EXIT_FAILLURE:INVALID_ID");
        exit(1);
    }

    Individu* ind=&(g->tab[x-1]);
    return ind;
}

/***************LIEN DE PARENTE***************/


bool freres_soeurs(Genealogie *g, ident x, ident y)
{
    Individu*ind_X=get(g,x);
    Individu*ind_Y=get(g,y);
    //il n'y a pas de famille recomposé
    if (ind_X->mere==ind_Y->mere||ind_X->pere==ind_Y->pere)
    {
        return true;
    }
    return false;
    
}

bool cousins(Genealogie *g, ident x, ident y)
{
    Individu* ind_X=get(g,x);
    Individu* ind_Y=get(g,y);
    if(freres_soeurs(g,ind_X->mere,ind_Y->pere)==true)
    {
        return true;
    }
    if(freres_soeurs(g,ind_X->mere,ind_Y->mere)==true)
    {
        return true;
    }
    if(freres_soeurs(g,ind_X->pere,ind_Y->pere)==true)
    {
        return true;
    }
    if(freres_soeurs(g,ind_X->pere,ind_Y->mere)==true)
    {
        return true;
    }
    return false;
}

/***************AFFICHAGES***************/

void affichage_current(Genealogie *g){
    
    for (int i = 0; i < g->id_cur-1; i++)
    {
        printf("Id : %d \nNom : %s\nid Père : %d\nid mère : %d\ndate naissance : %d/%d/%d\ndate mort : %d/%d/%d.\n faine : %d \n cadet : %d \n", 
    i+1,
    g->tab[i].nom,
    g->tab[i].pere,
    g->tab[i].mere,
    g->tab[i].naissance.jour, 
    g->tab[i].naissance.mois, 
    g->tab[i].naissance.annee, 
    g->tab[i].deces.jour, 
    g->tab[i].deces.mois, 
    g->tab[i].deces.annee,
    g->tab[i].faine,
    g->tab[i].cadet);
    printf("=============================\n");

    }
    
}
//je ne sais pas si il faut afficher que les freres et soeur ou toute la fraterie (lui compris ou pas)
void affiche_freres_soeurs(Genealogie *g, ident x)
{
    Individu* ind_X=get(g,x);
    if(ind_X->mere==0)
    {
        printf("%s\n",ind_X->nom);
        if(ind_X->cadet==0)
        {
            return;
        }
        ind_X=get(g,ind_X->cadet);
        while (ind_X->cadet!=0)
        {
            printf("%s \n",ind_X->nom);
            ind_X=get(g,ind_X->cadet);
        }
        printf("%s \n",ind_X->nom);
        return;
    }
    //car pas de famille recomposé
    Individu* ind_mere=get(g,ind_X->mere);

    Individu* ind_Fraterie=get(g,ind_mere->faine);

    while (ind_Fraterie->cadet!=0)
    {
        printf("%s \n",ind_Fraterie->nom);
        ind_Fraterie=get(g,ind_Fraterie->cadet);
    }
    printf("%s \n",ind_Fraterie->nom);
    return;
    
}

void affiche_enfants(Genealogie *g, ident x)
{
    Individu* parent=get(g,x);
    if(parent->faine==0)
    {
        return;
    }
    
    Individu* enfant=get(g,parent->faine);
    printf("%s \n",enfant->nom);
    if(enfant->cadet!=0){
        while (enfant->cadet!=0)
        {
            enfant=get(g,enfant->cadet);
            printf("%s \n",enfant->nom);
        }
    }
    return;
}

void affiche_cousins(Genealogie *g, ident x)
{
    Individu* indX=get(g,x);
    Individu* mere=get(g,indX->mere);
    Individu* pere=get(g,indX->pere);
    Individu* temp;
    //coté mere
    if (mere->mere==0)
    {
        printf("On ne va pouvoir traiter que les oncles/tante plus jeunes que la mere \n");
        if (mere->cadet==0)
        {
            printf("Pas de cousin du coté de la mere\n");
        }
        else
        {
            affiche_enfants(g,mere->cadet);
            printf("=====================\n");
            temp=get(g,mere->cadet);
            while (temp->cadet!=0)
            {
                affiche_enfants(g,temp->cadet);
                temp=get(g,temp->cadet);
                printf("=====================\n");
            }
            
        }
        
    }
    else
    {
        Individu* grand_Mere=get(g,mere->mere);
        if (grand_Mere->faine==indX->mere)
        {
            temp=get(g,mere->cadet);
        }
        else
        {
            affiche_enfants(g,grand_Mere->faine);
            temp=get(g,grand_Mere->faine);
        }
        
        while (temp->cadet!=0)
        {
            if (temp->cadet==indX->mere)
            {
                temp=get(g,temp->cadet);
                continue;
            }
            affiche_enfants(g,temp->cadet);
            temp=get(g,temp->cadet);
        }
        
    }
    //coté pere
        if (pere->pere==0)
    {
        printf("On ne va pouvoir traiter que les oncles/tante plus jeunes que le pere \n");
        if (pere->cadet==0)
        {
            printf("Pas de cousin du coté du pere\n");
        }
        else
        {
            affiche_enfants(g,pere->cadet);
            printf("=====================\n");
            temp=get(g,pere->cadet);
            while (temp->cadet!=0)
            {
                affiche_enfants(g,temp->cadet);
                temp=get(g,temp->cadet);
                printf("=====================\n");
            }
        }
    }
    else
    {
        Individu* grand_Mere=get(g,pere->mere);
        if (grand_Mere->faine==indX->pere)
        {
            temp=get(g,pere->cadet);
        }else
        {
            affiche_enfants(g,grand_Mere->faine);
            temp=get(g,grand_Mere->faine);
        }
        
        while (temp->cadet!=0)
        {
            if (temp->cadet==indX->pere)
            {
                temp=get(g,temp->cadet);
                continue;
            }
            affiche_enfants(g,temp->cadet);
            temp=get(g,temp->cadet);
        }
    }
}

void affiche_oncles(Genealogie *g, ident x)
{
    Individu* indX=get(g,x);
    
    if (indX->mere!=0)
    {
        Individu*mereX=get(g,indX->mere);
        if (mereX->mere!=0||mereX->pere!=0)
        {
            Individu*GrandParentX;
            if (mereX->mere!=0)
            {
                GrandParentX=get(g,mereX->mere);
            }else
            {
                GrandParentX=get(g,mereX->pere);
            }
            Individu* temp=get(g,GrandParentX->faine);
            while (temp->cadet!=0)
            {
                if (mereX!=temp)
                {
                    printf("%s\n",temp->nom);
                }
                temp=get(g,temp->cadet);
            }
            if(temp!=mereX){    
                printf("%s\n",temp->nom);
            }
        }else
        {
            while (mereX->cadet!=0)
            {
                mereX=get(g,mereX->cadet);
                printf("%s\n",mereX->nom);
            }
        }
        
        
    }
    if (indX->pere!=0)
    {
        Individu* pereX=get(g,indX->pere);
        if (pereX->mere!=0||pereX->pere!=0)
        {
            Individu*GrandParentX;
            if (pereX->mere!=0)
            {
                GrandParentX=get(g,pereX->mere);
            }else
            {
                GrandParentX=get(g,pereX->pere);
            }
            Individu* temp=get(g,GrandParentX->faine);

            while (temp->cadet!=0)
            {
                if (pereX!=temp)
                {
                    printf("%s\n",temp->nom);
                }
                temp=get(g,temp->cadet);
            }
            if(temp!=pereX){    
                printf("%s\n",temp->nom);
            }
        }else
        {
            while (pereX->cadet!=0)
            {
                pereX=get(g,pereX->cadet);
                printf("%s\n",pereX->nom);
            }
        }
    }
    return;
}

/***************PARCOURS DE L'ARBRE***************/
//Si x est un ancetre de y alors true sinon false
//il faut utiliser une autre fonction en rec pour checker les oncles
bool ancetre(Genealogie *g, ident x, ident y)
{
    if (x==y)
    {
        return true;
    }
    Individu* indY=get(g,y);
    int test=0;
    if (x==indY->mere)
    {
        return true;
    }
    
    if (x==indY->pere)
    {
        return true;
    }
    
    if (indY->pere==0&&indY->mere==0)
    {
        return false;
    }
    
    if (indY->mere==0)
    {
        if(ancetre_rec(g,x,indY->pere)==1)
        {
            return true;
        }
        else
        {
            return false;
        }
        
    }
    if (indY->pere==0)
    {

        if(ancetre_rec(g,x,indY->mere)==1)
        {
            return true;
        }
        else
        {
            return false;
        }
        
    }
    Individu* pere=get(g,indY->pere);
    Individu* mere=get(g,indY->mere);
    if(ancetre_rec(g,x,indY->pere)==1)
    {
        return true;
    }
    if (ancetre_rec(g,x,indY->mere)==1)
    {
        return true;
    }

    return false;
    
}
//Si X a un ancetre commun a Y 
bool ancetreCommun(Genealogie *g, ident x, ident y)
{
    if (x==y)
    {
        return true;
    }
    //Verification si ils sont des ancetre entre eux dans un premier temps
    if(ancetre(g,x,y))
    {
        return true;
    }
    if (ancetre(g,y,x))
    {
        return true;
    }
    //recherche d'ancetre commun donc parcour de tout l'arbre de x et comparer si celui ci est un ancetre de Y
    Individu* indX=get(g,x);
    if(indX->mere!=0){
        if(ancetreCommun_rec(g,indX->mere,y)==1)
        {
            return true;
        }
    }
    if(indX->pere!=0){
        if(ancetreCommun_rec(g,indX->pere,y)==1)
        {
            return true;
        }
    }
    return false;
    
}

ident plus_ancien(Genealogie *g, ident x)
{
    Individu* indX=get(g,x);
    ident retour=x;
    ident temp=x;
    if (indX->mere!=0)
    {
        temp=plus_ancien(g,indX->mere);
        Individu* ind_mere=get(g,indX->mere);
        Individu* ind_retour=get(g,retour);
        if(plusVieux(g,indX->mere,g,retour)){
            retour=temp;
        }
    }
    if(indX->pere!=0)
    {
        temp=plus_ancien(g,indX->pere);
        Individu* ind_pere=get(g,indX->pere);
        Individu* ind_retour=get(g,retour);
        if(plusVieux(g,indX->pere,g,retour)){
            retour=temp;
        }
    }
    return retour;
}
//faire une fonction qui affiche tout les membre a une hauteur x de l'arbre au-dessus de l'individu y
ident affiche_parente(Genealogie *g, ident x)
{
    int hauteur=1;
    printf("-%d : \n",hauteur);
    while (affiche_ind_hauteur(g,x,hauteur)!=0)
    {
        hauteur++;
        printf("-%d : \n",hauteur);
    }
    //je ne sais pas pourquoi il y a le retour d'un ident la ...
    return x;
    
}

ident affiche_descendance(Genealogie *g, ident x)
{
    int hauteur=0;
    printf("+%d : \n",hauteur);
    while (affiche_ind_hauteur_Descendance(g,x,hauteur)!=0)
    {
        hauteur++;
        printf("+%d : \n",hauteur);
    }
    //je ne sais pas pourquoi il y a le retour d'un ident la ...
    return x;
}

/***************FUSION***************/

void genealogieFusion(Genealogie *gres, Genealogie *a1, Genealogie *a2)
{
    int i=0;
    ident plus_vieux_A1;
    ident plus_vieux_A2;
    ident temp;
    ident nouv_id;
    Individu* ind_temp;
    bool est_dans_A1;
    int lim=a1->id_cur+a2->id_cur-2;
    while (i<lim)
    {
        plus_vieux_A1=plus_vieux_fusion(a1);
        plus_vieux_A2=plus_vieux_fusion(a2);
        Individu* ind_plus_vieux_A1;
        Individu* ind_plus_vieux_A2;
        if (plus_vieux_A1==0&&plus_vieux_A2==0)
        {
            return;
        }
        
        if (plus_vieux_A1!=0)
        {
            ind_plus_vieux_A1=get(a1,plus_vieux_A1);
        }
        else
        {
            genealogieFusion_aux(gres,a2,plus_vieux_A2);
            continue;
        }
        
        if (plus_vieux_A2!=0)
        {
            ind_plus_vieux_A2=get(a2,plus_vieux_A2);
        }
        else
        {
            genealogieFusion_aux(gres,a1,plus_vieux_A1);
            continue;
        }

        if (plusVieux(a1,plus_vieux_A1,a2,plus_vieux_A2))
        {
            genealogieFusion_aux(gres,a1,plus_vieux_A1);
        }else
        {
            genealogieFusion_aux(gres,a2,plus_vieux_A2);
        }
        i++;
    }
}
