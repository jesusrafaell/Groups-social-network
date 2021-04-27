#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

//Nodos de la lista
struct nodo {
 int c;
 int* Grup;
 int size_Grup;
 nodo *next;
};

//Lista para Imprimir los casos de prueba
typedef struct nodo *Jlist;

//Recorrer y imprimir los valores en la lista
void imprimir_lista(Jlist &list){
  Jlist Node = list;
  int idg, c = 0;
  while (Node != NULL){
    if(Node->c != c){
      if(c != 0)
        cout << endl;
      cout << "Caso " << Node->c << ":" <<endl;
      c = Node->c;
      idg = 1;
    }
    cout << "Grupo " << idg << ":" <<endl;
    for(int i = 0; i < Node->size_Grup; i++){
      cout << Node->Grup[i] << endl;
    }
    idg++;
    Node = Node->next;
  }
}

//Validad si se han creado todos los grupos posibles
int ready_groups(int usuarios[], int m){
  for(int i = 0; i < m; i ++){
    if(usuarios[i] == 1)
      //Faltan grupos por crear
      return 0;
  }
  //todos los grupos fueron creados
  return 1;
}

//Busca el prirmir usuario que no este asignado a ningun grupo
int primerusuario(int usuarios[], int m){
  for(int i = 0; i < m; i ++){
    if(usuarios[i] == 1)
      return i;
  }
  return -1;
}

//Validad si cada usuario del grupo ya fue revisado
int finishGroup(int cont, int group[], int usuarios[]){
  for(int i = 0; i < cont; i ++){
    //el usuario del grupo fue revisado?
    if(usuarios[group[i]] == 1)
      //no fue revisado
      return 0;
  }
  return 1;
}

//Validad si el usuario ya fue agreado al grupo
int addedGroup(int user, int group[], int cont){
  for(int i = 0; i < cont; i++){
    if(group[i] == user)
      return 1;
  }
  return 0;
}

//crea los grupos de cada caso de prueba y los guarda en una lista
void groups(int **red, int m, Jlist &list, int x){
  int usuarios[m];
  for(int i = 0; i < m; i++)
    usuarios[i] = 1;
  while(!ready_groups(usuarios, m)){
    Jlist Node = new (struct nodo);
    Node->c = x;
    Node->next = NULL;
    int group[m];
    for(int i = 0; i < m; i++)
      group[i] = -1;
    int contg = 0, id_user = 0;
    int user = primerusuario(usuarios, m);
    group[0] = user;
    contg++;
      while(!finishGroup(contg, group, usuarios)){
          //Revisar los amigos del siguente usuario del grupo
          for(int i = 0; i < m; i ++){
            if(red[user][i] == 1 && !addedGroup(i, group, contg)){
                //cout << user << " add-> " << i << endl;
                group[contg] = i,
                contg++;
            }
          }
          usuarios[user] = 0; //Descarto el usuario agreado a un grupo
          id_user++;
          user = group[id_user]; //Siguente usuario en el grupo
      }
      //Ordenar Grupo de manera ascendente
      for (int i=0; i<contg; i++)
      {
        int imin=i;
        for (int j=i+1; j<contg; j++)
        {
          if(group[j]<group[imin])
          imin=j;
        }
        int aux = group[i];
        group[i] = group[imin];
        group[imin] = aux;
      }
      Node->size_Grup = contg;
      Node->Grup = new int[contg];
      for(int i = 0; i < contg; i ++)
        Node->Grup[i] = group[i];
    //Agregar grupo a la lista
    if(list == NULL)
      list = Node;
    else{
      Jlist t = list;
      while(t->next != NULL){
        t = t->next;
      }
      t->next = Node;
    }
  }
}

int main(){
  int c, x = 1;
  cin >> c;
  Jlist list = NULL;
  while(x <= c){
    int n,m;
    cin >> m >> n;
    int **red = new int *[m];
    for(int i = 0; i <m; i++)
        red[i] = new int[m];

    //Initializar red
    for(int i = 0; i < m; i++){
      for(int j = 0; j < m; j++)
        red[i][j]= 0;
    }
    for (int i = 0; i < n; i++){
      int a,b;
      cin >> a >> b;
      red[a][b] = 1;
      red[b][a] = 1;
    }
    groups(red, m, list, x);
    x++;
  }
  imprimir_lista(list);
}
