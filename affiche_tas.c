#include <stdio.h>
#include "affiche_tas.h"
#include <ctype.h>

void afficher_tas(){
    int i, j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 16; j++) { 
	    printf("%4d", j + 16*i);
        }
        
        printf("\n");
        for (j = 0; j < 16; j++) { 
	    printf("%4d", tas[j + 16*i]);
        }
        printf("\n");
        for (j = 0; j < 16; j++) { 
	    if (isalnum(tas[j + 16*i])) {
	        printf("%4c", tas[j + 16*i]);
	    } else {
		printf("    ");
	    }
        }
        printf("\n\n");
    }
    printf("---------------------------------------------------------------\n\n");
}

void tas_init(){
  libre = 0;
  tas[0] = TAILTAS;
  tas[1] = -1;
}

int first_fit(int taille, int *pred){
	int p=libre;
	while(p!=-1 && tas[p]<taille){
		*pred=p;
		p=tas[p+1];
	}
	return p;
}



char* tas_malloc(int taille){
	int cas, avant;
	cas=first_fit(taille, &avant); 

	
	if(cas==libre){
		printf("cas 1er\n");
		tas[cas]=taille;
		tas[cas+1]= &tas[taille+1]; 
		tas[cas+taille+1]=TAILTAS-taille-1; 
		tas[cas+taille+2]=-1;
		libre+=taille+1;
		return &tas[cas+1];
	}
	//cas 1
	if (tas[cas]-taille<=TAILMIN){
		printf("CAS 1: p=%d taille=%d pred=%d\n",cas,taille,avant);
		tas[pred+1]=tas[cas+1];
		return &tas[cas+1];
	}
	
	else{
		printf("CAS 2: p=%d taille=%d pred=%d\n",cas,taille,avant);
		tas[cas+taille+1]=tas[cas]-taille-1; 
		tas[cas+taille+2]=tas[cas+1]; 
		tas[pred+1]+=taille+1;
		tas[cas]=taille;
		return &tas[cas+1];
	}
	
	return NULL;
}

void tas_free(char *ptr){
	ptr[0]=tas[libre];
	libre=
}
