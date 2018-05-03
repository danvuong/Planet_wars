#include<stdio.h>
#include<math.h>
#include <fcntl.h>

struct planete
{
  float x;
  float y;
  int owner_planete;
  int ships_planete;
  int growth;
  int id_p;
};

struct flotte
{
  int owner_flotte;
  int ships_flotte;
  int source;
  int dest;
  int total_turn;
  int remaining_turn;
  int id_f;
};

struct Data
{
  struct planete liste_p[100];
  int nbre_p;
  struct flotte liste_f[200];
  int nbre_f;
  int id_neutre[100];
  int nbre_n;
  int id_1[100];
  int nbre_1;
  int id_2[100];
  int nbre_2;
};

void tri_planete(struct Data *D,struct planete *p)
{
  if(p->owner_planete==0)
    D->id_neutre[D->nbre_n++]=p->id_p;
  if(p->owner_planete==1)
    D->id_1[D->nbre_1++]=p->id_p;
  if(p->owner_planete==2)
    D->id_2[D->nbre_2++]=p->id_p;
}

void print_tri(struct Data *D)
{
  int i;int j;int k;
  printf("planete neutre: ");
  for(i=0;i<D->nbre_n;i++)
    printf("%d ",D->id_neutre[i]);
  printf("\n");
  printf("planete 1: ");
  for(j=0;j<D->nbre_1;j++)
    printf("%d ",D->id_1[j]);
  printf("\n");
  printf("planete 2: ");
  for(k=0;k<D->nbre_2;k++)
    printf("%d ",D->id_2[k]);
  printf("\n");

}

void append_planete(struct Data *D,struct planete *p)
{
  //p->id_p=D->nbre_p;
  D->liste_p[D->nbre_p++]=*p;
}

void append_flotte(struct Data *D,struct flotte *f)
{
  D->liste_f[D->nbre_f++]=*f;
}

void ordre_attaque(int source,int dest,int ships)
{
  printf("%d %d %d\n",source,dest,ships);
}

void reset(struct Data *D)
{
  /*int i;int j;int k;
  for(i=0;i<D->nbre_n;i++)
    D->id_neutre[i]=0;
  for(j=0;j<D->nbre_1;j++)
    D->id_1[i]=0;
  for(j=0;j<D->nbre_2;k++)
    D->id_2[i]=0;*/
  D->nbre_n=D->nbre_1=D->nbre_2=0;
  D->nbre_p=0;
  D->nbre_f=0;
}

void print_planete(struct Data *D)
{
  int i;
  for(i=0;i<D->nbre_p;i++)
  {
    printf("planete %d :\n x=%f ; y=%f ; owner=%d ; ships=%d ; growth=%d ; id=%d\n",D->liste_p[i].id_p,D->liste_p[i].x,D->liste_p[i].y,D->liste_p[i].owner_planete,D->liste_p[i].ships_planete,D->liste_p[i].growth,D->liste_p[i].id_p);
  }
}

void print_flotte(struct Data *D)
{
  int i;
  for(i=0;i<D->nbre_f;i++)
  {
    printf("flotte %d :\n owner=%d ; ships=%d ; source=%d ; dest=%d ; total turn=%d ; remaining=%d ; id=%d\n",D->liste_f[i].id_f,D->liste_f[i].owner_flotte,D->liste_f[i].ships_flotte,D->liste_f[i].source,D->liste_f[i].dest,D->liste_f[i].total_turn,D->liste_f[i].remaining_turn,D->liste_f[i].id_f);
  }
}

float distance(struct Data *D,int id_source,int id_dest)
{
  float delta_x = ((D->liste_p[id_dest].x)-(D->liste_p[id_source].x));
  float delta_y = ((D->liste_p[id_dest].y)-(D->liste_p[id_source].y));
  float distance = ceil(sqrt(delta_x*delta_x+delta_y*delta_y));
  return distance;
}

void copie_liste(int *liste,int *new_liste,int nbre)
{
  int i;
  for(i=0;i<nbre;i++)
  {
    new_liste[i]=liste[i];
  }
}

void inversion_liste(int *liste,int taille)
{
  int i;int temp;
  for(i=0;i<(taille/2);i++)
  {
    temp=liste[i];
    liste[i]=liste[taille-i-1];
    liste[taille-i-1]=temp;
  }
}



  //#######################################################################//
 //                           Fonction de TRI                             //
//#######################################################################//

void tri_id_distance(struct Data *D,int *liste_id_distance,int id_source)
{
  int i;int j;int k;int temp;
  for(k=0;k<D->nbre_p;k++)
    {
      liste_id_distance[k]=D->liste_p[k].id_p;
    }
  for(i=0;i<(D->nbre_p)-1;i++)
  {
      for(j=i+1;j<(D->nbre_p);j++)
      {
        if(distance(D,id_source,liste_id_distance[j])<distance(D,id_source,liste_id_distance[i]))
          {
            temp=liste_id_distance[i];
            liste_id_distance[i]=liste_id_distance[j];
            liste_id_distance[j]=temp;
          }
        }
      }
}

void biggest_p(struct Data *D,int *liste_biggest_p)
{
  int p1=D->id_1[0];//int p2=D->liste_p[D->id_2[0]].ships_planete;int pn=D->liste_p[D->id_neutre[0]].ships_planete;
  int i;//int j;int k;
  for(i=0;i<D->nbre_1;i++)
  {
    if(D->liste_p[D->id_1[i]].ships_planete>D->liste_p[p1].ships_planete)
    {
      p1=D->id_1[i];
    }
  }
  liste_biggest_p[0]=p1;
}

void tri_id_growth(struct Data *D,int *liste_id_growth)
{
  int i;int j;int k;int temp;
  for(k=0;k<D->nbre_p;k++)
    {
      liste_id_growth[k]=D->liste_p[k].id_p;
    }
  for(i=0;i<(D->nbre_p)-1;i++)
  {
      for(j=i+1;j<(D->nbre_p);j++)
      {
        if(D->liste_p[liste_id_growth[j]].growth>=D->liste_p[liste_id_growth[i]].growth)
          {
            temp=liste_id_growth[i];
            liste_id_growth[i]=liste_id_growth[j];
            liste_id_growth[j]=temp;
          }
        }
      }
}

void tri_id_ships(struct Data *D,int *liste_id_ships,int taille_liste)
{
  int i;int j;int temp;
  for(i=0;i<taille_liste-1;i++)
  {
      for(j=i+1;j<taille_liste;j++)
      {
        if(D->liste_p[liste_id_ships[j]].ships_planete<=D->liste_p[liste_id_ships[i]].ships_planete)
          {
            temp=liste_id_ships[i];
            liste_id_ships[i]=liste_id_ships[j];
            liste_id_ships[j]=temp;
          }
      }
  }
}

void tri_id_ships_owner(struct Data *D,int *liste_id_ships_owner,int owner)
{
  int i;int taille;
  if(owner==1)
  {
    taille=D->nbre_1;
  }
  if(owner==2)
  {
    taille=D->nbre_2;
  }
  for(i=0;i<taille;i++)
  {
    liste_id_ships_owner[i]=D->id_1[i];
  }
  tri_id_ships(D,liste_id_ships_owner,taille);
  inversion_liste(liste_id_ships_owner,taille);
}

void planete_alliee(struct Data *D,int *liste_planete_allie,int planete_source)
{
  int i;int k=0;
  for(i=0;i<D->nbre_1;i++)
  {
    if(D->id_1[i]==planete_source);
    else
    {
      liste_planete_allie[k++]=D->id_1[i];
    }
  }
}

//#######################################################################//
//                                                                       //
//#######################################################################//


void print_distance(struct Data *D,int liste_distance[],int id_source)
{
  int i;
  for(i=0;i<D->nbre_p;i++)
  {
    printf("planete: %d distance: %f\n",liste_distance[i],distance(D,id_source,liste_distance[i]));
  }
}

int somme_flotte_target(struct Data *D,int id_dest)
{
  int s=0;int i;
  for(i=0;i<D->nbre_f;i++)
  {
    if(D->liste_f[i].dest==id_dest)
    {
      s+=D->liste_f[i].ships_flotte;
    }
  }
  return s;
}

int somme_flotte_renfort(struct Data *D,int id_dest)
{
  int s=0;int i;
  for(i=0;i<D->nbre_f;i++)
  {
    if(D->liste_f[i].dest==id_dest && D->liste_f[i].owner_flotte==D->liste_f[id_dest].owner_flotte)
    {
      s+=D->liste_f[i].ships_flotte;
    }
  }
  return s;
}

int futur_conquise(struct Data *D,int id_dest)
{
  if(somme_flotte_target(D,id_dest)>D->liste_p[id_dest].ships_planete)
    return 0;
  else
    return 1;
}

int ships_arrive(struct Data *D,int id_source,int id_dest)
{
  int s=0;
  int total_turn = distance(D,id_source,id_dest);
  s=D->liste_p[id_dest].ships_planete+total_turn*D->liste_p[id_dest].growth;
  return s;
}

int danger(struct Data *D,int id_source,int id_ennemi)
{
  if(somme_flotte_target(D,id_source)>ships_arrive(D,id_ennemi,id_source)+somme_flotte_renfort(D,id_source))
      return 1;
  else
      return 0;
}

int renfort(struct Data *D)
{
    int i;int j;int id_source;int k=0;int liste_planete_alliee[100];
    for(i=0;i<D->nbre_1;i++)
    {
      for(j=0;j<D->nbre_f;j++)
      {
        if(D->liste_f[j].dest==D->id_1[i])
        {
          if(danger(D,D->id_1[i],D->liste_f[j].source) && D->nbre_1>1)
          {
            planete_alliee(D,liste_planete_alliee,D->id_1[i]);
            id_source=liste_planete_alliee[k];
            if(D->liste_p[id_source].ships_planete > 5 )// (somme_flotte_target(D,D->id_1[i])-ships_arrive(D,D->liste_f[j].source,D->id_1[i]))+5)
              ordre_attaque(id_source,D->id_1[i],5);//(somme_flotte_target(D,D->id_1[i])-ships_arrive(D,D->liste_f[j].source,D->id_1[i])));
            // else if (D->liste_p[id_source].ships_planete < 5 )
            // {
            //   id_source=liste_planete_alliee[k++];
            //   ordre_attaque(id_source,D->id_1[i],5);//(somme_flotte_target(D,D->id_1[i])-ships_arrive(D,D->liste_f[j].source,D->id_1[i])));
            // }
            return 0;
          }
        }
      }
    }
    return 1;
}


//#######################################################################//
//                                                                       //
//#######################################################################//


int main()
{
  setvbuf(stdout, NULL, _IOLBF, 0);
  srand(time(NULL));
  struct Data D;
  D.nbre_p=0;
  D.nbre_f=0;
  D.nbre_n=0;
  D.nbre_1=0;
  D.nbre_2=0;
  int i;
  int liste_id_distance[100];
  int liste_id_ships[100];
  int liste_id_ships_1[100];
  int liste_biggest_p[2];
  int liste_id_growth[100];
  int liste_priority[100];
  int id_source;
  int id_dest;

  while(1)
  {

    char buffer[100];
    fgets(buffer,100,stdin);
    if(buffer[0]=='P')
    {
      struct planete p;
      sscanf(buffer,"P %f %f %d %d %d",&p.x,&p.y,&p.owner_planete,&p.ships_planete,&p.growth);
      p.id_p=D.nbre_p;
      tri_planete(&D,&p);
      append_planete(&D,&p);
    }
    if(buffer[0]=='F')
    {
      struct flotte f;
      sscanf(buffer,"F %d %d %d %d %d %d",&f.owner_flotte,&f.ships_flotte,&f.source,&f.dest,&f.total_turn,&f.remaining_turn);
      append_flotte(&D,&f);
    }
    if(buffer[0]=='g'&& buffer[1]=='o')
    {

      if(D.nbre_1>=5 && D.nbre_2!=0)
      {
        int i;int k=0;int id_source1;int id_source2;
        for(i=0;i<D.nbre_1-1;i++)
        {
          id_source1=D.id_1[i];
          //id_source2=D.id_1[i+1];
          id_dest=D.id_2[rand()%D.nbre_2];
          if((D.liste_p[id_source1].ships_planete)/*+(D.liste_p[id_source2].ships_planete/2) */ >(ships_arrive(&D,id_source,id_dest)+10) && futur_conquise(&D,id_dest)==1)
          {
            ordre_attaque(id_source1,id_dest,(ships_arrive(&D,id_source,id_dest)+10);//D.liste_p[id_dest].ships_planete+5);
            //ordre_attaque(id_source2,id_dest,(D.liste_p[id_source2].ships_planete/2)+5 );//D.liste_p[id_dest].ships_planete+5);

          }
        }
      }

      renfort(&D);

      if(D.nbre_1<D.nbre_p)
      {
        int k=0;
        //biggest_p(&D,liste_biggest_p);
        tri_id_ships_owner(&D,liste_id_ships_1,1);
        tri_id_distance(&D,liste_id_distance,liste_id_ships_1[0]);
        copie_liste(liste_id_distance,liste_priority,5);
        tri_id_ships(&D,liste_priority,5);
        id_dest=liste_priority[k];
        id_source=liste_id_ships_1[0];
        while(D.liste_p[id_dest].owner_planete==1)// || D.liste_p[id_dest].owner_planete==2)
          id_dest=liste_priority[k++];
        if(D.liste_p[id_source].ships_planete>ships_arrive(&D,id_source,id_dest)+15 && futur_conquise(&D,id_dest))
          ordre_attaque(id_source,id_dest,ships_arrive(&D,id_source,id_dest)+10);
      }

      /*printf("%d ; %d\n",somme_flotte_target(&D,0),futur_conquise(&D,0));
      print_flotte(&D);*/
      reset(&D);
      printf("go\n");
    }


  }
  return 0;
}
