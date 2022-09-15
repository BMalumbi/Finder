#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include "ListFile.c"


int main(int argc, char* argv[]) {
    listFiles(".");
    printf("Etape 1 OK\n");
    printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-\n");
    RechercheDate(".");
    printf("Etape 2 OK\n");
    printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-\n");
    puts("Trouver des répertoires"); 
     if(argc==2) 
        RechercheRepertoire(argv[1],0); 
     else 
        RechercheRepertoire("finder",0);
    printf("Etape 3 OK\n");
    printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-\n");

    char directory[PATH_MAX],parent[PATH_MAX];

	puts("Recherche des repertoires...");

	//Change to or set current directory 
	if(argc==2)
	{
		strcpy(directory,argv[1]);
		chdir(directory);
	}
	else
	{
		getcwd(directory,PATH_MAX);
	}

	//fetch parent directory
	chdir("..");
	getcwd(parent,PATH_MAX);
	//and change back 
	chdir(directory);
	RechercheRepertoireArbo(directory,parent);
    
    printf("Etape 4 OK\n");
    printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-\n");
 
    return 0;
}

