/*Filip Emil Florentin - 313CB*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct dir
{
    char * nume;
    struct dir * parinte;
    struct fis * fisiere;
    struct dir * directories;
    struct dir * st;
    struct dir * dr;
}TDir, *ADir;

typedef struct fis
{
    char * nume;
    TDir * parinte;
    struct fis *st;
    struct fis *dr;
}TFis, *AFis;

TDir * ConstrFrDir(char * x)
{
	TDir * aux = (TDir *)malloc (sizeof(TDir));
	if (!aux) return NULL;
    aux->nume = malloc(strlen(x));
	memcpy(aux->nume,x,strlen(x)); aux->st = aux->dr = NULL;
    aux->nume[strlen(x)] = '\0';
    aux->fisiere = NULL;
    aux->parinte = NULL;
	return aux;
}

TFis * ConstrFrFis(char * x)
{
	TFis * aux = (TFis *)malloc (sizeof(TFis));
	if (!aux) return NULL;
    aux->nume = malloc(strlen(x));
	memcpy(aux->nume,x,strlen(x)); aux->st = aux->dr = NULL;
    aux->nume[strlen(x)] = '\0';
	return aux;
}

int Inserare_ABCDir(TDir ** a, char * x,TDir * parinte)
{
	TDir *aux, *p, *n;
	if(*a == NULL)
	{	
		*a = ConstrFrDir(x);
		if(!*a) return -1;
        (*a)->parinte = parinte;
		return 1;
	}
	n = *a;
	while(n)
	{
		p = n;
		if(strcmp(x,n->nume) == 0) 
			return 0;
		if(strcmp(x,n->nume) < 0)
			n = n->st;
		else	
			n = n->dr;
	}
	aux = ConstrFrDir(x);
    aux->parinte = parinte;
	if(!aux) return -1;

	if(strcmp(x,p->nume) < 0)
		p->st = aux;
	else	
		p->dr = aux;
	return 1;
}

int Inserare_ABCFis(AFis * a, char * x,TDir * parinte)
{
	TFis *aux, *p, *n;
	if(*a == NULL)
	{	
		*a = ConstrFrFis(x);
		if(!(*a)) return -1;
        (*a)->parinte = parinte;
		return 1;
	}
	n = *a;
	while(n)
	{
		p = n;
		if(strcmp(x,n->nume) == 0) 
			return 0;
		if(strcmp(x,n->nume) < 0)
			n = n->st;
		else	
			n = n->dr;
	}
	aux = ConstrFrFis(x);
    aux->parinte = parinte;
	if(!aux) return -1;

	if(strcmp(x,p->nume) < 0)
		p->st = aux;
	else	
		p->dr = aux;
	return 1;
}

void srdDir(ADir x)
{
    if(x != NULL)
    {
        srdDir(x->st);
        printf("%s ",x->nume);
        srdDir(x->dr);
    }
}

void srdFis(AFis x)
{
    if(x != NULL)
    {
        srdFis(x->st);
        printf("%s ",x->nume);
        srdFis(x->dr);
    }
}

int verifExistentaDir(ADir x,char * cuv)
{
    if(x == NULL)
        return 0;
    if(strcmp(cuv,x->nume) == 0)
        return 1;
    if(strcmp(cuv,x->nume) < 0)
        return verifExistentaDir(x->st,cuv);
    else
        return verifExistentaDir(x->dr,cuv);
}

int verifExistentaFis(AFis x,char * cuv)
{
    if(x == NULL)
        return 0;
    if(strcmp(cuv,x->nume) == 0)
        return 1;
    if(strcmp(cuv,x->nume) < 0)
        return verifExistentaFis(x->st,cuv);
    else
        return verifExistentaFis(x->dr,cuv);
}

void recFis(AFis fis,char * cuvant,AFis * nou)
{
    if(strcmp(fis->nume,cuvant) != 0)
        Inserare_ABCFis(nou,fis->nume,fis->parinte);
    if(fis->st != NULL)
        recFis(fis->st,cuvant,nou);
    if(fis->dr != NULL)
        recFis(fis->dr,cuvant,nou);
}

void recDir(ADir dir, char * cuvant,ADir * nou)
{
    if(strcmp(dir->nume,cuvant) != 0)
        Inserare_ABCDir(nou,dir->nume,dir->parinte);
    if(dir->st != NULL)
        recDir(dir->st,cuvant,nou);
    if(dir->dr != NULL)
        recDir(dir->dr,cuvant,nou);
}
