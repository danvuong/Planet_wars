# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <math.h>

# define MAX_CHAR 100
# define MAX_PLANETES 50
# define MAX_FLOTTES 100


//TO DO

struct infos_planete
{
  int numero_planete;
  float coordonnee_x;
  float coordonnee_y;
  int proprietaire;
  int nombre_vaisseaux;
  int croissance;
};

struct planete 
{
  struct infos_planete infos_planete;
  struct planete * planete_suivante;
  
};

struct flotte
{
  int numero_flotte;
  int joueur;
  int nombre_vaisseaux;
  int source;
  int destination;
  int total_tours;
  int tours_restants;
  struct flotte * flotte_suivante;
};

struct carte
{
  struct planete planetes[MAX_PLANETES];
  struct flotte flottes[MAX_FLOTTES];
  struct planete * planetes_conquises;
  struct planete * planetes_ennemies;
  struct planete * planetes_neutres;
  struct flotte * flottes_ennemies;
  struct flotte * flottes_alliees;
};

int verif_go(char buf [])
{
  if (buf[0] == 'g' && buf[1] == 'o')
    return 1;
  return 0;
}

void add_planete(struct carte * carte, int *compteur_planete, int * joueur)
{
  if(*joueur == 0)
    {
      if (carte->planetes_neutres == NULL)
	{
	  carte->planetes_neutres = &(carte->planetes[*compteur_planete]);
	  carte->planetes_neutres->planete_suivante = NULL;
	} else {
	carte->planetes[*compteur_planete].planete_suivante = carte->planetes_neutres;
	carte->planetes_neutres = &(carte->planetes[*compteur_planete]);
      }
    } else if(*joueur == 1){
    if (carte->planetes_conquises == NULL)
      {
	carte->planetes_conquises = &(carte->planetes[*compteur_planete]);
	carte->planetes_conquises->planete_suivante = NULL;
      } else {
      carte->planetes[*compteur_planete].planete_suivante = carte->planetes_conquises;
      carte->planetes_conquises = &(carte->planetes[*compteur_planete]);
    }
  } else if(*joueur == 2){
    if (carte->planetes_ennemies == NULL)
      {
	carte->planetes_ennemies = &(carte->planetes[*compteur_planete]);
	carte->planetes_ennemies->planete_suivante = NULL;
      } else {
      carte->planetes[*compteur_planete].planete_suivante = carte->planetes_ennemies;
      carte->planetes_ennemies = &(carte->planetes[*compteur_planete]);
    }
  }
  return;
}

//void print_planetes_conquises(struct carte * carte)
//{
//  struct planete * planete_actuelle = carte->planetes_conquises;
//  while(planete_actuelle)
//    {
//      print_planete(planete_actuelle);
//      planete_actuelle = planete_actuelle->planete_suivante;
//    }
//}

void add_flotte(struct carte *carte, int * compteur_flotte, int * joueur)
{
  if(*joueur == 1)
    {
      if(carte->flottes_alliees == NULL)
	{
	  carte->flottes_alliees = &(carte->flottes[*compteur_flotte]);
	  carte->flottes_alliees->flotte_suivante = NULL;
	} else {
	carte->flottes[*compteur_flotte].flotte_suivante = carte->flottes_alliees;
	carte->flottes_alliees = &(carte->flottes[*compteur_flotte]);
      }
    } else if(*joueur == 2) {
    if(carte->flottes_ennemies == NULL)
      {
	carte->flottes_ennemies = &(carte->flottes[*compteur_flotte]);
	carte->flottes_ennemies->flotte_suivante = NULL;
      } else {
      carte->flottes[*compteur_flotte].flotte_suivante = carte->flottes_ennemies;
      carte->flottes_ennemies = &(carte->flottes[*compteur_flotte]);
    }
  }
  return;
}

void update_carte(char * buffer, struct carte * carte, int * compteur_planete, int * compteur_flotte)
{
  if (buffer[0] == 'P')
    {
      carte->planetes[*compteur_planete].infos_planete.numero_planete = *compteur_planete;
      sscanf(buffer, "P %f %f %d %d %d",
	     &(carte->planetes[*compteur_planete].infos_planete.coordonnee_x),
	     &(carte->planetes[*compteur_planete].infos_planete.coordonnee_y),
	     &(carte->planetes[*compteur_planete].infos_planete.proprietaire),
	     &(carte->planetes[*compteur_planete].infos_planete.nombre_vaisseaux),
	     &(carte->planetes[*compteur_planete].infos_planete.croissance)); 
      add_planete(carte, compteur_planete, &(carte->planetes[*compteur_planete].infos_planete.proprietaire));
    } else if (buffer[0] == 'F'){
    carte->flottes[*compteur_flotte].numero_flotte = *compteur_flotte;
    sscanf(buffer, "F %d %d %d %d %d %d",
	   &(carte->flottes[*compteur_flotte].joueur),
	   &(carte->flottes[*compteur_flotte].nombre_vaisseaux),
	   &(carte->flottes[*compteur_flotte].source),
	   &(carte->flottes[*compteur_flotte].destination),
	   &(carte->flottes[*compteur_flotte].total_tours),
	   &(carte->flottes[*compteur_flotte].tours_restants));
    add_flotte(carte, compteur_flotte, &(carte->flottes[*compteur_flotte].joueur));
  } else if (verif_go(buffer)){
    *compteur_planete = 0;
    *compteur_flotte = 0;
  }
  return;
}
// Fonctions d'échange avec le programme Java

void go()
{
  printf("go\n");
}

void copy_buffer (char *  buf1, char * buf2)
{
  for (int i = 0; i < MAX_CHAR; i++)
    {
      buf2[i] = buf1[i];
    }
}

void read(char buffer [])
{
  fgets(buffer, MAX_CHAR, stdin);
}

int verif_attaque(struct carte * carte, struct planete * planete)
{
  struct flotte * flotte = carte->flottes_alliees;
  int numero_planete = planete->infos_planete.numero_planete;
  while(flotte)
    {
      int destination = flotte->destination;
      if(destination == numero_planete)
	return 0;
      flotte = flotte->flotte_suivante;
    }
  return 1;
}

int under_attack(struct carte * carte, struct planete * planete)
{
  struct flotte * flotte = carte->flottes_ennemies;
  int numero_planete = planete->infos_planete.numero_planete;
  while(flotte)
    { 
      int destination = flotte->destination;
      if(destination == numero_planete)
	return 1;
      flotte = flotte->flotte_suivante;
    }
  return 0;
}

void print_flotte_alliee(struct carte * carte)
{
  struct flotte * flotte = carte->flottes_alliees;
  while(flotte)
    {
      printf("Joueur %d\nNombre vaisseaux %d\nSource %d\n Destination %d\n Touts total %d \nTours restants %d\n",
	     flotte->joueur,
	     flotte->nombre_vaisseaux,
	     flotte->source,
	     flotte->destination,
	     flotte->total_tours,
	     flotte->tours_restants);
      flotte = flotte->flotte_suivante;
    }
  return;
}

int compare_distance(struct planete * planete_source, struct planete * attaque_planete, struct planete * planete_prospection)
{
  double distance_x_prosp = planete_prospection->infos_planete.coordonnee_x - planete_source->infos_planete.coordonnee_x;
  double distance_y_prosp = planete_prospection->infos_planete.coordonnee_y - planete_source->infos_planete.coordonnee_y;
  int tours_distance_prosp = (int)(ceil(sqrt(distance_x_prosp * distance_x_prosp - distance_y_prosp * distance_y_prosp)));
  double distance_x_attaque = attaque_planete->infos_planete.coordonnee_x - planete_source->infos_planete.coordonnee_x;
  double distance_y_attaque = attaque_planete->infos_planete.coordonnee_y - planete_source->infos_planete.coordonnee_y;
  int tours_distance_attaque = (int)(ceil(sqrt(distance_x_attaque * distance_x_attaque - distance_y_attaque * distance_y_attaque)));
  if(tours_distance_prosp < tours_distance_attaque)
    return 1;
  return 0;
}

void bot_prospection(struct carte * carte)
{
  struct planete * planetes_source = carte->planetes_conquises;
  struct planete * planetes_destination = carte->planetes_neutres;
  struct planete * planete_prospection = NULL;
  int vaisseaux_dispos;
  int vaisseaux_arrivee;
  while(planetes_source != NULL)
    {
      planete_prospection = NULL;
      vaisseaux_dispos = (planetes_source->infos_planete.nombre_vaisseaux) - 1;
      planete_prospection = NULL;
      while(planetes_destination != NULL)
	{
	  vaisseaux_arrivee = planetes_destination->infos_planete.nombre_vaisseaux;
	  if(verif_attaque(carte, planetes_destination)){
	    if(vaisseaux_arrivee < vaisseaux_dispos - 10)
	      {
		if(!planete_prospection)
		  {
		    planete_prospection = planetes_destination;
		  } else if(planetes_destination->infos_planete.croissance > planete_prospection->infos_planete.croissance){
		  planete_prospection = planetes_destination;
		} else if(planetes_destination->infos_planete.croissance == planete_prospection->infos_planete.croissance){
		  if(compare_distance(planetes_source, planete_prospection, planetes_destination)){
		    planete_prospection = planetes_destination;
		  }
		}
	      }
	  }
	  planetes_destination = planetes_destination->planete_suivante;
	}
      if(planete_prospection)
	{
	printf("%d %d %d\n",
	       planetes_source->infos_planete.numero_planete,
	       planete_prospection->infos_planete.numero_planete,
	       planete_prospection->infos_planete.nombre_vaisseaux + 10);
	}
      planetes_source = planetes_source->planete_suivante;
    }
  go();
  return;
}

void bot_attaque(struct carte * carte)
{
  struct planete * planetes_source = carte->planetes_conquises;
  struct planete * planetes_nemesis = carte->planetes_ennemies;
  int vaisseaux_dispos;
  int vaisseaux_ennemies_arrivee;
  int attaque_planete = 0;
  while(planetes_source != NULL)
    {
      int tours_attaque_planete = 0;
      attaque_planete = 0;
      vaisseaux_dispos = planetes_source->infos_planete.nombre_vaisseaux - 1;
      planetes_nemesis = carte->planetes_ennemies;
      while(planetes_nemesis != NULL)
	{
	  double distance_x = planetes_nemesis->infos_planete.coordonnee_x - planetes_source->infos_planete.coordonnee_x;
	  double distance_y = planetes_nemesis->infos_planete.coordonnee_y - planetes_source->infos_planete.coordonnee_y;
	  int tours_distance = (int)(ceil(sqrt(distance_x * distance_x + distance_y * distance_y)));
	  vaisseaux_ennemies_arrivee = planetes_nemesis->infos_planete.nombre_vaisseaux + tours_distance*planetes_nemesis->infos_planete.croissance;
	  if(vaisseaux_ennemies_arrivee < vaisseaux_dispos)
	    {
	      if(!tours_attaque_planete)
		{
		  tours_attaque_planete = tours_distance;
		  attaque_planete = planetes_nemesis->infos_planete.numero_planete;
		} else if(tours_distance < tours_attaque_planete){
		tours_attaque_planete = tours_distance;
		attaque_planete = planetes_nemesis->infos_planete.numero_planete;
	      } else if(tours_distance == tours_attaque_planete){
		if(planetes_nemesis->infos_planete.croissance > carte->planetes[attaque_planete].infos_planete.croissance)
		  attaque_planete = planetes_nemesis->infos_planete.numero_planete;
	      }
	      vaisseaux_dispos -= vaisseaux_ennemies_arrivee + 1;	    
	    }
	  planetes_nemesis = planetes_nemesis->planete_suivante;
	}
      if(attaque_planete && verif_attaque(carte, &(carte->planetes[attaque_planete])))
	{
	  printf ("%d %d %d\n",
		  planetes_source->infos_planete.numero_planete,
		  attaque_planete,
		  carte->planetes[attaque_planete].infos_planete.nombre_vaisseaux + tours_attaque_planete*(carte->planetes[attaque_planete].infos_planete.croissance) +1);
	}
      planetes_source = planetes_source->planete_suivante;
    }
  go();
  return;
}


void dual_bot(struct carte *carte)
{
  int croissance_totale_alliee = 0;
  int croissance_totale_ennemie = 0;
  struct planete * planetes_source = carte->planetes_conquises;
  struct planete * planetes_nemesis = carte->planetes_ennemies;
  while(planetes_source)
    {
      croissance_totale_alliee += planetes_source->infos_planete.croissance;
      planetes_source = planetes_source->planete_suivante;
    }
  while(planetes_nemesis)
    {
      croissance_totale_ennemie += planetes_nemesis->infos_planete.croissance;
      planetes_nemesis = planetes_nemesis->planete_suivante;
    }
  if(croissance_totale_alliee > croissance_totale_ennemie)
    {
      bot_attaque(carte);
    } else {
    bot_prospection(carte); 
  }
  return;
}

void bot_premier_tour(struct carte * carte)
{
  struct planete * planete_depart = carte->planetes_conquises;
  struct planete * planete_ennemie = carte->planetes_ennemies;
  int tours_avant_arrivee = carte->flottes_ennemies->tours_restants;
  int vaisseaux_ennemis_approche = carte->flottes_ennemies->nombre_vaisseaux;
  int vaisseaux_dispos = planete_depart->infos_planete.nombre_vaisseaux - vaisseaux_ennemis_approche + planete_depart->infos_planete.croissance * tours_avant_arrivee - 30;
  printf("%d %d %d\n",
	 planete_depart->infos_planete.numero_planete,
	 planete_ennemie->infos_planete.numero_planete,
	 vaisseaux_dispos); 
  go();
  return;
}

struct carte init_carte()
{
  struct carte nouvelle_carte;
  nouvelle_carte.planetes_conquises = NULL;
  nouvelle_carte.planetes_ennemies = NULL;
  nouvelle_carte.planetes_neutres = NULL;
  nouvelle_carte.flottes_ennemies = NULL;
  nouvelle_carte.flottes_alliees = NULL;
  for(int i = 0; i < MAX_PLANETES; i++)
    {
      nouvelle_carte.planetes[i].planete_suivante = NULL;
    }
  for(int j = 0; j < MAX_FLOTTES; j++)
    {
      nouvelle_carte.flottes[j].flotte_suivante = NULL;
    }
  return nouvelle_carte;
}

void print_planete (struct planete * planete)
{
  printf("\nPlanète %d\nCoordonnée x %f\nCoordonnée y %f\nJoueur %d\nVaisseaux %d\nTaux de croissance %d\n\n",
	 planete->infos_planete.numero_planete,
	 planete->infos_planete.coordonnee_x,
	 planete->infos_planete.coordonnee_y,
	 planete->infos_planete.proprietaire,
	 planete->infos_planete.nombre_vaisseaux,
	 planete->infos_planete.croissance);
}

//void print_liste_planetes(struct carte * carte, int * compteur_planete)
//{
//  for (int i = 0; i <(*compteur_planete) + 1; i++)
//    {
//      print_planete(&(carte->planetes[i]));
//    }
//}

int main(int argc, char *argv[])
{
  setvbuf(stdout, NULL, _IOLBF, 0);
  srand(time(NULL));
  struct carte carte = init_carte();
  char buffer1 [MAX_CHAR];
  char buffer2 [MAX_CHAR];
  int compteur_planete = 0;
  int compteur_flotte = 0;
  int premier_tour = 2;
  while (1)
    {
      read(buffer1);
      if (buffer1[0] == 'P')
	{
	  update_carte(buffer1, &carte, &compteur_planete, &compteur_flotte);
	  compteur_planete++;
	}
      if(buffer1[0] == 'F')
	{
	  update_carte(buffer1, &carte, &compteur_planete, &compteur_flotte);
	  compteur_flotte++;
	}
      if (verif_go(buffer1))
	{
	  if (buffer2[0] == 'P' || buffer2[0] == 'F')
	    {
	      if(premier_tour == 2)
		{
		  premier_tour--;
		  compteur_planete = 0;
		  compteur_flotte = 0;
		  carte = init_carte();
		  go();
		} else if(premier_tour == 1){
		if(under_attack(&carte, carte.planetes_conquises))
		  {
		    bot_premier_tour(&carte);
		    compteur_planete = 0;
		    compteur_flotte = 0;
		    carte = init_carte();
		  } else {
		  go();
		}
		compteur_planete = 0;
		compteur_flotte = 0;
		carte = init_carte();
		premier_tour--; 
	      } else {
		dual_bot(&carte);
		compteur_planete = 0;
		compteur_flotte = 0;
		carte = init_carte();
	      }
	    }
	}
      copy_buffer(buffer1, buffer2);
    }
  return EXIT_SUCCESS;
}	
