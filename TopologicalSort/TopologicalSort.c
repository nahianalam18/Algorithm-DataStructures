#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

#define TREE 0
#define BACK 1
#define CROSS 2
#define FORWARD 3

/*Nahian Alam
    1001552659
    Compile:
        gcc -o main alam_nahian_lab5.c
    Run:
        ./main
*/

struct node
{
    int info;
    struct node *ptr;
}*top,*top1,*temp;

int topelement();
void push(int data);
void pop();
void empty();
void display();
void destroy();
void stack_count();
void create();

int n;  // number of nodes
int e;  // number of edges
int count = 0;
int distance_left;
int distance_right;
struct edge {
  int tail,head,type,dist;
};


typedef struct edge edgeType;
edgeType *edgeTab;
int *firstEdge;  // Table indicating first in range of edges with a common tail

int *discovery,*finish,*predecessor,*vertexStatus, *distance, *successor, *longest;



// Reading the input file and organize adjacency lists
void topologicalSort()
{
    int i = 0;
    for(i=edgeTab[i].tail;i<n;++i)
    {
        push(i);
    }
}
int tailThenHead(const void* xin, const void* yin)
// Used in calls to qsort() and bsearch() for read_input_file()
{
int result;
edgeType *x,*y;

x=(edgeType*) xin;
y=(edgeType*) yin;
result=x->tail - y->tail;
if (result!=0)
  return result;
else
  return x->head - y->head;
}

void read_input_file()
{
int a,b,w,i,j;
edgeType work;
edgeType *ptr;

scanf("%d %d",&n,&e);
edgeTab=(edgeType*) malloc(e*sizeof(edgeType));
if (!edgeTab)
{
  printf("edgeTab malloc failed %d\n",__LINE__);
  exit(0);
}

for (i=0; i<e; i++)
{
  scanf("%d %d %d",&a,&b, &w);
  if (a<0 || a>=n || b<0 || b>=n)
  {
    printf("Invalid input %d %d at %d\n",a,b,__LINE__);
    exit(0);
  }
  edgeTab[i].tail=a;
  edgeTab[i].head=b;
  edgeTab[i].dist=w;
}

// sort edges
qsort(edgeTab,e,sizeof(edgeType),tailThenHead);
printf("\nSorted Edge Tab \n");
for(i = 0; i<e; i++)
{
    printf("%d %d %d\n",edgeTab[i].head,edgeTab[i].tail,edgeTab[i].dist);
}
printf("\n\n");


// Coalesce duplicates into a single edge
j=0;
for (i=1; i<e; i++)
  if (edgeTab[j].tail==edgeTab[i].tail
     && edgeTab[j].head==edgeTab[i].head)
    ;

  else
  {
    j++;
    edgeTab[j].tail=edgeTab[i].tail;
    edgeTab[j].head=edgeTab[i].head;
  }
e=j+1;

// For each vertex as a tail, determine first in range of edgeTab entries
firstEdge=(int*) malloc((n+1)*sizeof(int));
if (!firstEdge)
{
  printf("malloc failed %d\n",__LINE__);
  exit(0);
}
j=0;
for (i=0; i<n; i++)
{
  firstEdge[i]=j;
  for ( ;
       j<e && edgeTab[j].tail==i;
       j++)
    ;
}
firstEdge[n]=e;
}

int time;  /*Keeps node numbering*/

void DFSvisit(int u)
{
int i,v,distance = 0, x=-1, y = -1;

vertexStatus[u]=GRAY;
time++;
discovery[u]=time;

for (i=firstEdge[u];i<firstEdge[u+1];i++)
{
  v=edgeTab[i].head;
 // distance = edgeTab[i].dist;



 //   printf("\n\nLongest u = %d \n",longest[u-1]);
 // printf("u = %d v = %d\n",u,v);
  if (vertexStatus[v]==WHITE)
  {
    edgeTab[i].type=TREE;
    predecessor[v]=u;
    successor[u] = v;
  //  distance += DFSvisit(v);
  //  longest[u] = distance;
  }
  else if (vertexStatus[v]==GRAY)
  {
    edgeTab[i].type=BACK;
    successor[u] = v;
  }

  else if (discovery[u]<discovery[v])
  {
    edgeTab[i].type=FORWARD;
    successor[u] = v;
  }

  else
  {
      edgeTab[i].type=CROSS;
      successor[u] = v;
    //  distance += DFSvisit(u);
  }

}
vertexStatus[u]=BLACK;
time++;
finish[u]=time;
//longest[u] = distance;
//return distance;
}

int main ()
{
int u,i,j,k,nextDFS;
distance_left = 0;
distance_right = 0;
read_input_file();
discovery=(int*) malloc(n*sizeof(int));
finish=(int*) malloc(n*sizeof(int));
predecessor=(int*) malloc(n*sizeof(int));
vertexStatus=(int*) malloc(n*sizeof(int));
distance = (int*) malloc(n*sizeof(int));
successor = (int*) malloc(n*sizeof(int));
longest = (int*) malloc(n*sizeof(int));
if (!discovery || !finish || !predecessor ||!vertexStatus || !distance)
{
  printf("malloc failed\n");
  exit(0);
}
// DFS code
for (u=0;u<n;u++)
{
  vertexStatus[u]=WHITE;
  predecessor[u]=(-1);
  successor[u] = (-1);
  longest[u] = 0;
}
time=0;
for (u=0;u<n;u++)
  if (vertexStatus[u]==WHITE){
    DFSvisit(u);
   // longest[u] = distance_left;
  //  distance_left = 0;
  }


//Output code
printf("Vertex  discovery    finish     predecessor     longest     successor\n");
for (i=0;i<n;i++)
  printf(" %3d      %3d         %3d          %3d          %3d          %3d\n",i,
    discovery[i],finish[i],predecessor[i],longest[i],successor[i]);
printf("Edge Tail Head Type \t Dist\n");
for (i=0;i<e;i++)
{
  printf(" %3d  %3d  %3d  ",i,edgeTab[i].tail,edgeTab[i].head);
  switch(edgeTab[i].type)
  {
    case TREE:    printf("tree"); break;
    case BACK:    printf("back"); break;
    case CROSS:   printf("cross"); break;
    case FORWARD: printf("forward"); break;
  }
    printf(" \t %4d \n",edgeTab[i].dist);
}


free(edgeTab);
free(firstEdge);
free(discovery);
free(finish);
free(predecessor);
free(vertexStatus);
free(distance);
free(successor);
return 0;
}

void create()
{
    top = NULL;
}

/* Count stack elements */
void stack_count()
{
    printf("\n No. of elements in stack : %d", count);
}

/* Push data into stack */
void push(int data)
{
    if (top == NULL)
    {
        top =(struct node *)malloc(1*sizeof(struct node));
        top->ptr = NULL;
        top->info = data;
    }
    else
    {
        temp =(struct node *)malloc(1*sizeof(struct node));
        temp->ptr = top;
        temp->info = data;
        top = temp;
    }
    count++;
}

/* Display stack elements */
void display()
{
    top1 = top;

    if (top1 == NULL)
    {
        printf("Stack is empty");
        return;
    }

    while (top1 != NULL)
    {
        printf("%d ", top1->info);
        top1 = top1->ptr;
    }
 }

/* Pop Operation on stack */
void pop()
{
    top1 = top;

    if (top1 == NULL)
    {
        printf("\n Error : Trying to pop from empty stack");
        return;
    }
    else
        top1 = top1->ptr;
    printf("\n Popped value : %d", top->info);
    free(top);
    top = top1;
    count--;
}

/* Return top element */
int topelement()
{
    return(top->info);
}

/* Check if stack is empty or not */
void empty()
{
    if (top == NULL)
        printf("\n Stack is empty");
    else
        printf("\n Stack is not empty with %d elements", count);
}

/* Destroy entire stack */
void destroy()
{
    top1 = top;

    while (top1 != NULL)
    {
        top1 = top->ptr;
        free(top);
        top = top1;
        top1 = top1->ptr;
    }
    free(top1);
    top = NULL;

    printf("\n All stack elements destroyed");
    count = 0;
}
