#include <vector>
#include <set>
#include <iostream>

using namespace std;

const int INF = 0x3FFFFFFF;

/*
 * Note: graph represent
 * Edge represents the weight and end point of a edge
 * Graph stores a adjacent list which keeps edges from each node
 */

struct Edge
{
    int weight;
    int finish;
    Edge():weight(INF), finish(0) {}
    Edge(int w, int f):weight(w), finish(f) {}
    //bool operator<(const Edge & other)  const { return (finish < other.finish); } // for set
    bool operator<(const Edge & other)  const { return (finish < other.finish)||(finish == other.finish && weight < other.weight); } // for set
};

class Graph
{
    public:
        Graph(int size) { adj_list.resize(size); }
        set<Edge> & get_adj_nodes(int id) { return adj_list[id]; }
        void add_edge(int start, int finish, int w);
    private:
        vector<set<Edge> > adj_list;
};

void Graph::add_edge(int start, int finish, int w)
{
    adj_list[start].insert(Edge(w, finish));
}

/* Note: heap
 * to implement decrease key a reference to position of a key must be kept.
 */

struct Elem
{
    int id;
    int key;
    Elem():id(0), key(INF) {}
    Elem(int ix, int d):id(ix), key(d) {}
};

class PQueue
{
    public:
        PQueue(int size);
        int dist(int ix);
        Elem extract_min();
        void decrease_key(int id, int key);
    private:
        int cnt;  //# of elements in heap
        vector<int> ref;
        vector<Elem> heap;
        void heap_swap(int x, int y);
        void down(int pos);
        void up(int pos);
};

PQueue::PQueue(int size)
{
    cnt = size;
    ref.resize(size);
    for (int i = 0; i < size; ++i){
        ref[i] = i + 1;
    }
    heap.resize(size + 1);
    for (int i = 0; i < size; ++i){
        heap[i + 1] = Elem(i, INF);
    }
}

int PQueue::dist(int ix)
{
    return heap[ref[ix]].key;
}

Elem PQueue::extract_min()
{
    Elem res = heap[1];
    heap_swap(cnt, 1);
    --cnt;
    down(1);
    return res;
}

void PQueue::decrease_key(int id, int key)
{
    heap[ref[id]].key = key;
    up(ref[id]);
}

void PQueue::heap_swap(int x, int y)
{
    Elem t = heap[x];
    heap[x] = heap[y];
    heap[y] = t;
    ref[heap[x].id] = x;
    ref[heap[y].id] = y;
}

void PQueue::up(int pos)
{
    while(pos > 1){
        int father = pos / 2;
        if (heap[father].key > heap[pos].key){
            heap_swap(father, pos);
            pos = father;
        }else{
            break;
        }
    }
}

void PQueue::down(int pos)
{
    while (pos * 2 <= cnt){
        int son = pos * 2;
        if ((son + 1 <= cnt) && (heap[son + 1].key < heap[son].key)){
            ++son;
        }
        if (heap[son].key < heap[pos].key){
            heap_swap(son, pos);
            pos = son;
        }else{
            break;
        }
    }
}

int to_ans(int x)
{
    if (x == INF){
        return -1;
    }else{
        return x;
    }
}

int main()
{
    int n;
    int m;
    cin >> m;
    cin >> n;
    ++n;
    Graph graph(n);
    for (int i = 0; i < m; ++i){
        int s, f, w;
        cin >> s >> f >> w;
        graph.add_edge(s, f, w);
        graph.add_edge(f, s, w);
    }
    vector<bool> visited(n, false);
    PQueue pq(n);
    pq.decrease_key(n - 1,0);
    for (int i = 0; i < n; ++i){
        Elem cur = pq.extract_min();
        visited[cur.id] = true;
        set<Edge> & arcs = graph.get_adj_nodes(cur.id);
        cout << cur.id << " " << arcs.size() <<endl;
        for (set<Edge>::iterator iter = arcs.begin(); iter != arcs.end(); ++iter){
            if (!visited[iter->finish] && pq.dist(iter->finish) > cur.key + iter->weight){
                pq.decrease_key(iter->finish, cur.key + iter->weight); //relax
            }
        }
    }
    cout << pq.dist(1) << endl;
    return 0;
}







