#include<stdio.h>

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
      //print_tri(&D);
      //print_planete(&D);
      int rand_dest;
      int rand_source;
      int rand_ships;
      int x = rand()%4;
      if(x==0)
        if(D.nbre_2!=0 && D.nbre_1!=0)
        {
          rand_source = D.id_1[rand()%(D.nbre_1)];//Genere un nbre aléatoire choisissant la planete source pour l'attaque
          rand_ships = rand()%D.liste_p[rand_source].ships_planete;
          rand_dest = D.id_2[rand()%(D.nbre_2)];
          ordre_attaque(rand_source,rand_dest,rand_ships);
        }
      if(x==1)
        if(D.nbre_n!=0 && D.nbre_1!=0)
        {
          rand_source = D.id_1[rand()%(D.nbre_1)];//Genere un nbre aléatoire choisissant la planete source pour l'attaque
          rand_ships = rand()%D.liste_p[rand_source].ships_planete;
          rand_dest = D.id_neutre[rand()%(D.nbre_n)];
          ordre_attaque(rand_source,rand_dest,rand_ships);
        }
      if(x==2)
        if(D.nbre_1!=0 && D.nbre_1!=1)
        {
          rand_source = D.id_1[rand()%(D.nbre_1)];//Genere un nbre aléatoire choisissant la planete source pour l'attaque
          rand_ships = rand()%D.liste_p[rand_source].ships_planete;
          rand_dest = D.id_1[rand()%(D.nbre_1)];
          while(rand_dest==rand_source)
            rand_dest = D.id_1[rand()%(D.nbre_1)];
          ordre_attaque(rand_source,rand_dest,rand_ships);
        }
      reset(&D);
      printf("go\n");
    }

  }
  return 0;

}
