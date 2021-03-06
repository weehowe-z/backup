#include <iostream>
#define INFINITE 9999999
#define NILL -1
#define UNVISITED 0
#define VISITED 1
using namespace std;
template<typename E>
class Node
{
public:
    E element;
    Node<E>* next;
    Node()
    {
        next=NULL;
    }
    Node(E e,Node<E>* n)
    {
        element=e;
        next=n;
    }
};
template <typename E>
class LList
{
public:
    Node<E>* head;
    Node<E>* tail;
    int length;
    LList()
    {
        length=0;
        head=tail=new Node<E>;
    }
 ~ LList()
    {
        Node<E>* tmp;
        while (head->next!=NULL){
            tmp=head;
            head=head->next;
            delete tmp;
        }
        delete head;
    }
    void append(const E it)
    {
        tail->next=new Node<E>(it,NULL);
        tail=tail->next;
        ++length;
    }
    E headremove()
    {
        Node<E>* tmp=head->next;
        E result=tmp->element;
        head->next=tmp->next;
        delete tmp;
        --length;
        if (length==0) tail=head;
        return result;
    }
    void print()
    {
        Node<E>* p=head;
        while (p->next!=NULL){
            p=p->next;
            cout<<p->element<<" ";
        }
    }
};

template <typename E>
class LQueue
{
public:
    int length;
    LList<E>* queue;
    LQueue()
    {
        length=0;
        queue=new LList<E>;
    }
    ~LQueue()
    {
        delete queue;
    }
    void enqueue(const E it)
    {
        queue->append(it);
        ++length;
    }
    E dequeue()
    {
        E result=queue->headremove();
        --length;
        return result;
    }
};

class Edge
{
public:
    int weight;
    int vertex;
    Edge(int w=INFINITE,int v=NILL)
    {
        weight=w;
        vertex=v;
    }
};
class Graphl
{
private:
    int numVertex;
    int *mark;
    LList<Edge>** adjList;
public:
    Graphl(int n)
    {
        numVertex=n;
        adjList=new LList<Edge>*[numVertex];
        for (int i=0;i<numVertex;++i) adjList[i]=new LList<Edge>;
        mark=new int[numVertex];
        for (int i=0;i<numVertex;++i) mark[i]=UNVISITED;
    }
    ~Graphl()
    {
        for (int i=0;i<numVertex;++i) delete adjList[i];
        delete []adjList;
        delete []mark;
    }
    bool isEdge(int v1,int v2)
    {
        Node<Edge>* tmp;
        tmp=adjList[v1]->head;
        while (tmp->next!=NULL){
            tmp=tmp->next;
            if (tmp->element.vertex==v2) return true;
        }
        return false;
    }
    int getWeight(int v1,int v2)
    {
        if (v1==v2) return 0;
        Node<Edge>* tmp;
        tmp=adjList[v1]->head;
        while (tmp->next!=NULL){
            tmp=tmp->next;
            if (tmp->element.vertex==v2) return tmp->element.weight;
        }
        return INFINITE;
    }
    void setEdge(int v1,int v2,int weight)
    {
        Node<Edge>* tmp;
        bool flag1=true;
        bool flag2= true;
        tmp=adjList[v1]->head;
        while (tmp->next!=NULL){
            tmp=tmp->next;
            if (tmp->element.vertex==v2) {
                flag1=false;
                if (weight<tmp->element.weight) {flag2=false;tmp->element.weight=weight;}
                break;
            }
        }
        if (flag1) {
            adjList[v1]->append(Edge(weight,v2));
            adjList[v2]->append(Edge(weight,v1));
        }
            else if (!flag2){
                 tmp=adjList[v2]->head;
                 while (tmp->next!=NULL){
                    tmp=tmp->next;
                    if (tmp->element.vertex==v1) tmp->element.weight=weight;
                }
            }

    }
    int first(int v)
    {
        if (adjList[v]->head->next==NULL) return numVertex;
        return adjList[v]->head->next->element.vertex;
    }
    int next(int v,int w)
    {
        Node<Edge>* tmp;
        tmp=adjList[v]->head->next;
        while (tmp->next!=NULL){
            if(tmp->element.vertex!=w)  tmp=tmp->next;
                else return tmp->next->element.vertex;
        }
        return numVertex;
    }

    int findMin(int distanceMatrix[])
    {
        int v;
        for (int i=0;i<numVertex;++i){
            if (mark[i]==UNVISITED) {v=i;break;}
        }
        for (int i=v+1;i<numVertex;++i){
            if (mark[i]==UNVISITED&& distanceMatrix[i]<distanceMatrix[v]) v=i;
        }
        return v;
    }

    void Prim_Algorithm()
    {
        int totalweight=0;
        int minDistanceMatrix[numVertex];
        int prevNode[numVertex];
        for (int i=0;i<numVertex;++i) minDistanceMatrix[i]=INFINITE;
        for (int i=0;i<numVertex;++i) prevNode[i]=NILL;
        minDistanceMatrix[0]=0;
        prevNode[0]=0;
        for (int i=0;i<numVertex;++i) mark[i]=UNVISITED;
        for (int i=0;i<numVertex;++i){
            int v=findMin(minDistanceMatrix);
            mark[v]=VISITED;
            totalweight+=getWeight(v,prevNode[v]);
            for (int w=first(v);w<numVertex;w=next(v,w)){
                if (getWeight(v,w)<minDistanceMatrix[w]) {
                    minDistanceMatrix[w]=getWeight(v,w);
                    prevNode[w]=v;
                }
            }
        }
    cout<<totalweight<<endl;
    }
};
int main()
{

    int m,n,u,v,l;
    Graphl* G;
    cin>>n>>m;
    G=new Graphl(n);
    for (int i=0;i<m;++i){
        cin>>u>>v>>l;
        G->setEdge(u-1,v-1,l);
    }
    G->Prim_Algorithm();
    return 0;
}
