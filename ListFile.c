#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

#include "finder.h"

void listFiles(const char* dirname) {
    DIR* dir = opendir(dirname); 
    struct dirent *entry; 
    int files = 0;
    entry = readdir(dir); 
    if (dir == NULL) {
        return;
    }
    printf("Lire les fichiers dans: %s\n", dirname);
    
    while (entry != NULL ) { 
        files++;
        printf("File %3d: %hdd %s/%s/%d\n",files, entry->d_type, dirname, entry->d_name);
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            char path[100] = { 0 };
            strcat(path, dirname);
            strcat(path, "/");
            strcat(path, entry->d_name);
            listFiles(path);
        }
        entry = readdir(dir); 
    } 
    closedir(dir); 

}


void RechercheDate(const char* dirname)
{
    DIR* dir = opendir(dirname);
    struct dirent *entry;
    struct stat filestat;
    char cwdpath[256];
    int count = 1;
    long long total = 0;

    if(dir == NULL)
    {
        perror("Impossible de lire le repertoire");
        return;
    }

    /* Indiquer le nom du répertoire */
    getcwd(cwdpath,256);
    printf(" Directory of %s\n\n",cwdpath);

    /* Lire les entrées du répertoire */
    while( (entry=readdir(dir)) )
    {
        /* Extraire le nom du fichier */
        stat(entry->d_name,&filestat);
        printf("%-16s",entry->d_name);

        /* Extraire la taille */
        if( S_ISDIR(filestat.st_mode) )
            printf("%-8s  ","<DIR>");
        else
        {
            printf("%8lld  ",filestat.st_size);
            total+=filestat.st_size;
        }
        printf("\n        %d File(s) for %lld bytes\n",
            count,
            total
          );
        printf("-----------------------------------------------------------------\n");

        /* Extraire la date et l'heure */
        printf("%s dernière consultation",ctime(&filestat.st_atime));
        printf("%s dernière modification",ctime(&filestat.st_mtime));
        printf("%s dernière modification de l'etat",ctime(&filestat.st_ctime));
  
    }

    closedir(dir);
    

}

void RechercheRepertoire(char *directory,int depth)
{
    DIR* dir ; 
    struct dirent *entry; 
    struct stat filestat; 
    /* Passe au répertoire nommé */ 
    if(chdir(directory)) { 
        fprintf(stderr,"Erreur lors du passage dans %s\n",directory); 
        exit(1); 
    }

        /* ouvre le répertoire */
    dir = opendir("."); 
    if(dir == NULL) { 
        fprintf(stderr,"Impossible de lire le répertoire %s\n",directory); 
        exit(1); 
    } 
    printf("%*s%s\n",depth*2," ",directory); 
    /* Recherche un sous-répertoire */
    while( (entry=readdir(dir)) ) { 
        stat(entry->d_name,&filestat); 
        /* recherche uniquement les répertoires */ 
        if( S_ISDIR(filestat.st_mode) ) { 
            /* ignore le . et .. entrées */ 
            if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0) 
                continue; 
            /* revenir au répertoire trouvé */ 
            RechercheRepertoire(entry->d_name,depth+1); 
        } 
    } 
    chdir(".."); 
    closedir(dir); 
}

void RechercheRepertoireArbo(char *directory,char *parent)
{
    DIR *dir;
	struct dirent *entry;
	struct stat filestat;
	char pathname[PATH_MAX];

	/* Passe au répertoire nommé */
	if(chdir(directory))
	{
		fprintf(stderr,"Error changing to %s\n",directory);
		exit(1);
	}

	/* ouvre le répertoire */
	dir = opendir(".");
	if(dir == NULL)
	{
		fprintf(stderr,"Unable to read directory %s\n",directory);
		exit(1);
	}

	/* fetch the current directory for output, but also for
	   the recursive call later */
	getcwd(pathname,PATH_MAX);
	printf("%s\n",pathname);

	/* Look for a subdirectory */
	while( (entry=readdir(dir)) )
	{
		stat(entry->d_name,&filestat);
		/* look for only directories */
		if( S_ISDIR(filestat.st_mode) )
		{
			/* skip the . and .. entries */
			if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0)
				continue;
			/* recurse to the found directory */
			RechercheRepertoireArbo(entry->d_name,pathname);
		}
	}

	closedir(dir);
	chdir(parent);

}