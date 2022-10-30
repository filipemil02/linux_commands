/*Filip Emil Florentin - 313CB*/
#include "functii.h"

void touchFisier(TDir * dir, char * cuvant)
{
    int a = verifExistentaDir(dir->directories,cuvant);
    int b = verifExistentaFis(dir->fisiere,cuvant);
    if((a + b) == 0)
        Inserare_ABCFis(&(dir->fisiere),cuvant,dir);
    else
    {
        if(a == 1)
            printf("Directory %s already exists!\n",cuvant);
        else
            printf("File %s already exists!\n",cuvant);
    }
}

void ls(TDir dir)
{
    srdDir(dir.directories);
    srdFis(dir.fisiere);
    printf("\n");
}

void mkdir(TDir * dir, char * cuvant)
{
    int a = verifExistentaDir(dir->directories,cuvant);
    int b = verifExistentaFis(dir->fisiere,cuvant);
    if((a + b) == 0)
        Inserare_ABCDir(&(dir->directories),cuvant,dir);
    else
    {
        if(a == 1)
            printf("Directory %s already exists!\n",cuvant);
        else
            printf("File %s already exists!\n",cuvant);
    }
    
}

void rm(TFis ** fis, char * cuvant)
{
    if(verifExistentaFis(*fis,cuvant) == 0)
    {
        printf("File %s doesn't exist!\n",cuvant);
        return;
    }
    TFis * root = *fis;
    TFis * nou = NULL;
    recFis(root,cuvant,&nou);
    *fis = nou;
}

void rmdir(TDir ** dir, char * cuvant)
{
    if(verifExistentaDir(*dir,cuvant) == 0)
    {
        printf("Directory %s doesn't exist!\n",cuvant);
        return;
    }
    TDir * root = *dir;
    TDir * nou = NULL;
    recDir(root,cuvant,&nou);
    *dir = nou;
}

void cd(ADir * dir,char * cuvant)
{
    TDir * curent = (*dir)->directories;
    int ok = 0;
    if(strcmp(cuvant,"..") == 0)
    {
        if(strcmp((*dir)->nume,"root") == 0)
            return;
        *dir = (*dir)->parinte;
        return;
    }
    ok = verifExistentaDir(curent,cuvant);
    if(ok == 0)
        printf("Directory not found!\n");
    else
    {
        while(ok == 1)
        {
            if(strcmp(cuvant,curent->nume) == 0)
                ok = 0;
            else
            {
                if(strcmp(cuvant,curent->nume) < 0)
                    curent = curent->st;
                else
                    curent = curent->dr;
            }
        }
        *dir = curent;
    }
}

void pwd(TDir * dir)
{
    if(strcmp(dir->nume,"root") == 0)
        printf("/root");
    else
    {
        pwd(dir->parinte);
        printf("/%s",dir->nume);
    }
}

int findFis(TDir * root, char * cuvant)
{
    if(root == NULL)
        return 0;
    if(verifExistentaFis(root->fisiere,cuvant) == 1)
    {
        printf("File %s found!\n",cuvant);
        pwd(root);
        printf("\n");
    }
        
    return verifExistentaFis(root->fisiere,cuvant) +
        findFis(root->st,cuvant) +
        findFis(root->dr,cuvant) +
        findFis(root->directories,cuvant);
}

int findDir(TDir * root, char * cuvant)
{
    if(root == NULL)
        return 0;
    if(verifExistentaDir(root->directories,cuvant) == 1)
    {
        printf("Directory %s found!\n",cuvant);
        pwd(root);
        printf("/%s",cuvant);
        printf("\n");
    }
        
    return verifExistentaDir(root->directories,cuvant) +
        findDir(root->st,cuvant) +
        findDir(root->dr,cuvant) +
        findDir(root->directories,cuvant);
}

int main()
{
    TDir * root = malloc(sizeof(TDir));
    root->nume = malloc(5 * sizeof(char));
    strcpy(root->nume,"root");
    root->parinte = NULL;
    root->directories = NULL;
    root->fisiere = NULL;
    root->st = NULL;
    root->dr = NULL;
    size_t len;
    char * line = NULL, * cuv;
    int rez;
    TDir * poz = root;
    while (getline(&line, &len, stdin) != -1)
    {
        cuv = strtok(line," \n");
        if(strcmp(cuv,"touch") == 0)
        {
            cuv = strtok(NULL," ");
            if(cuv[strlen(cuv)-1] == '\n')
                cuv[strlen(cuv)-1] = '\0';
            touchFisier(poz,cuv);
        }else
        {
            if(strcmp(cuv,"ls") == 0)
                ls(*poz);
            else
            {
                if(strcmp(cuv,"mkdir") == 0)
                {
                    cuv = strtok(NULL," ");
                    if(cuv[strlen(cuv)-1] == '\n')
                        cuv[strlen(cuv)-1] = '\0';
                    mkdir(poz,cuv); 
                }
                else
                {
                    if(strcmp(cuv,"rm") == 0)
                    {
                        cuv = strtok(NULL," ");
                        if(cuv[strlen(cuv)-1] == '\n')
                            cuv[strlen(cuv)-1] = '\0';
                        rm(&(poz->fisiere),cuv);
                    }
                    else
                    {
                        if(strcmp(cuv,"rmdir") == 0)
                        {
                            cuv = strtok(NULL," ");
                            if(cuv[strlen(cuv)-1] == '\n')
                                cuv[strlen(cuv)-1] = '\0';
                            rmdir(&(poz->directories),cuv);
                        }
                        else
                        {
                            if(strcmp(cuv,"cd") == 0)
                            {
                                cuv = strtok(NULL," ");
                                if(cuv[strlen(cuv)-1] == '\n')
                                    cuv[strlen(cuv)-1] = '\0';
                                    cd(&poz,cuv);
                            }
                            else
                            {
                                if(strcmp(cuv,"pwd") == 0)
                                {
                                    pwd(poz);
                                    printf("\n");
                                }
                                else
                                {
                                    if(strcmp(cuv,"find") == 0)
                                    {
                                        cuv = strtok(NULL," ");
                                        if(cuv[strlen(cuv)-1] == '\n')
                                            cuv[strlen(cuv)-1] = '\0';
                                        if(strcmp(cuv,"-d") == 0)
                                        {
                                            cuv = strtok(NULL," ");
                                            if(cuv[strlen(cuv)-1] == '\n')
                                                cuv[strlen(cuv)-1] = '\0';
                                            if(findDir(root,cuv) == 0)
                                                printf("Directory %s not found!\n",cuv);
                                        }
                                        else
                                        {
                                            cuv = strtok(NULL," ");
                                            if(cuv[strlen(cuv)-1] == '\n')
                                                cuv[strlen(cuv)-1] = '\0';
                                            if(findFis(root,cuv) == 0)
                                                printf("File %s not found!\n",cuv);
                                        }
                                    }
                                    else
                                    {
                                        if(strcmp(cuv,"quit") == 0)
                                        {
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
                
        }
    }
}