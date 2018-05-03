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

/*struct planete new_planete()
{
  struct planete p;
  return p;
}

struct flotte new_flotte()
{
  struct flotte f;
  return f;
}*/

/*struct liste_planete
{
  struct planete liste_p[100];
  int nbre_p;
};

struct liste_flotte
{
  struct flotte liste_f[100];
  int nbre_f;
};*/

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

float distance(struct Data *D,int id_source,int id_dest)
{
  float delta_x = ((D->liste_p[id_dest].x)-(D->liste_p[id_source].x));
  float delta_y = ((D->liste_p[id_dest].y)-(D->liste_p[id_source].y));
  float distance = ceil(sqrt(delta_x*delta_x+delta_y*delta_y));
  return distance;
}

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

void print_distance(struct Data *D,int liste_distance[],int id_source)
{
  int i;
  for(i=0;i<D->nbre_p;i++)
  {
    printf("planete: %d distance: %f\n",liste_distance[i],distance(D,id_source,liste_distance[i]));
  }
}


int main()
{
  setvbuf(stdout, NULL, _IOLBF, 0);
  struct Data D;
  D.nbre_p=0;
  D.nbre_f=0;
  D.nbre_n=0;
  D.nbre_1=0;
  D.nbre_2=0;
  int liste_id_distance[100];
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
      if(D.nbre_1<6)
      {
        int k=0;
        tri_id_distance(&D,liste_id_distance,D.id_1[0]);
        if(D.liste_p[liste_id_distance[k]].owner_planete==1)
          k++;
        ordre_attaque(D.id_1[0],liste_id_distance[k],1);

      }
      /*tri_id_distance(&D,liste_id_distance,0);
      print_planete(&D);
      print_distance(&D,liste_id_distance,0);*/
      reset(&D);
      printf("go\n");
    }

  }
  return 0;
}
