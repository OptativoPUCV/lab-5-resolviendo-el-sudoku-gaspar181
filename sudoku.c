#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      if(n->sudo[i][j] > 0){
        int num = n->sudo[i][j];
        for(int k = 0; k < 9; k++){
          if(n->sudo[k][j] == num && k != i) return 0;
          if(n->sudo[i][k] == num && k != j) return 0;
        }

        int k = (i / 3) * 3 + (j / 3);
        for(int p = 0; p < 9; p++){
          int check_i = 3*(k/3) + (p/3);
          int check_j = 3*(k%3) + (p%3);
          if(n->sudo[check_i][check_j] == num && (check_i != i || check_j != j)) return 0;
        }
      }
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      if(n->sudo[i][j] == 0){
        for(int num = 1; num <= 9; num++){
          Node* aux = copy(n);
          aux->sudo[i][j] = num;
          if(is_valid(aux)) pushBack(list, aux);
          else free(aux);
        }
        return list;
      }
    }
  }
  return list;
}


int is_final(Node* n){
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      if(n->sudo[i][j] == 0) return 0;
    }
  }
  return 1;
}

/*Node* DFS(Node* initial, int* cont){
  Stack* S = createStack();
  push(S, initial);
  while(!is_empty(S)){
    Node* current = top(S);
    pop(S);
    (*cont)++;
    if(is_final(current)) return current;
    List* nodos = get_adj_nodes(current);
    Node* nodo_adj = front(nodos);
    popFront(nodos);
    while(nodo_adj != NULL) push(S, nodo_adj);
    free(current);
  }
  return NULL;
}
*/


/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/