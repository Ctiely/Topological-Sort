//
// Created by Clytie on 2018/3/11.
//

#ifndef DAY11_GRAPH_H
#define DAY11_GRAPH_H

#include <list>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
using namespace std;

template <typename Comparable>
class Graph {
public:
    Graph()
            : Vertexs(list<Vertex *>()), EdgNum(0), TOPSORT(0) {}
    ~Graph() {
        Vertexs.clear();
    }


    void addNode(Comparable eleV) {
        Vertex * v = new Vertex(eleV);
        addNode(v);
    }
    void addEdge(Comparable eleV1, Comparable eleV2) {
        Vertex * v1 = NULL; //必须定义在外面,不然就成了局部变量了
        Vertex * v2 = NULL;
        typename list<Vertex *>::const_iterator itr = Vertexs.begin();
        for (; itr != Vertexs.end(); ++itr) {
            if ((*itr)->element == eleV1) {
                v1 = *itr;
            } else if ((*itr)->element == eleV2) {
                v2 = *itr;
            }
        }
        if (v1 == NULL) {
            v1 = new Vertex(eleV1);
        }
        if (v2 == NULL) {
            v2 = new Vertex(eleV2);
        }
        addEdge(v1, v2);
    }

    int getNodeNum() const {
        return Vertexs.size();
    }
    int getEdgeNum() const {
        return EdgNum;
    }
    void topsort() {
        queue<Vertex *> q;
        int counter = 0;

        if (!q.empty()) {
            queue<Vertex *>().swap(q);
        }
        typename list<Vertex *>::const_iterator itr = Vertexs.begin();
        for (; itr != Vertexs.end(); ++itr) {
            if ((*itr)->indegree == 0) {
                q.push(*itr);
            }
        }
        while (!q.empty()) {
            Vertex * v = q.front();
            q.pop();
            v->topNum = ++counter;

            typename list<Vertex *>::const_iterator itr = v->adj.begin();
            for (; itr != v->adj.end(); ++itr) {
                if (--((*itr)->indegree) == 0) {
                    q.push(*itr);
                }
            }
        }
        if (counter != Vertexs.size()) {
            throw "ERROR!";
        }
        TOPSORT = 1;
    }

    void quicksort(vector<pair<Comparable, int> > & a, int begin, int end) {
        if (begin < end) {
            int left = begin, right = end;
            pair<Comparable, int> pivot = a[left];
            while (begin < end) {
                while (begin < end && a[end].second >= pivot.second) {
                    --end;
                }
                if (begin < end) {
                    a[begin++] = a[end];
                }

                while (begin < end && a[begin].second <= pivot.second) {
                    ++begin;
                }
                if (begin < end) {
                    a[end--] = a[begin];
                }
            }

            a[begin] = pivot;
            quicksort(a, left, begin - 1);
            quicksort(a, begin + 1, right);
        }
    }

    void quickSort(vector<pair<Comparable, int> > & a) {
        quicksort(a, 0, a.size() - 1);
    }

    void topsortPrint() {
        if (!TOPSORT) {
            topsort();
        }
        vector<pair<Comparable, int> > TPvec;
        typename list<Vertex *>::const_iterator itr = Vertexs.begin();
        cout << endl;
        cout << "topsort result:" << endl;
        for (; itr != Vertexs.end(); ++itr) {
            cout << "vertex element: " << (*itr)->element << ", " << "topsort value: " << (*itr)->topNum << endl;
            pair<Comparable, int> ipair;
            ipair.first = (*itr)->element;
            ipair.second = (*itr)->topNum;
            TPvec.push_back(ipair);
        }
        quickSort(TPvec);
        cout << endl;
        cout << "quicksort of topsort result:" << endl;
        for (int i = 0; i < TPvec.size(); ++i) {
            cout << "vertex element: " << TPvec[i].first << ", " << "topsort value: " << TPvec[i].second << endl;
        }
    }

private:
    struct Vertex {
        Vertex(Comparable theElement)
                : element(theElement), adj(list<Vertex *>()), indegree(0), topNum(0) {}
        ~Vertex() {
            adj.clear();
        }

        Comparable element;
        list<Vertex *> adj;
        int indegree;
        int topNum;

        bool exist(Vertex * v2) {
            //list<Vertex *>::const_iterator itr = find(adj.begin(), adj.end(), v2); 怎么老报错啊,啥情况啊,前面必须加typename才行
            typename list<Vertex *>::const_iterator itr = adj.begin(); //itr是指针的指针
            for (; itr != adj.end(); ++itr) {
                //*itr才是Vertex * 类型
                if ((*itr)->element == v2->element) {
                    return 1;
                }
            }
            return 0;
        }
    };

    list<Vertex *> Vertexs;
    //int VerNum;
    int EdgNum;
    bool TOPSORT;

    bool exist(Vertex * v) const {
        //list<Vertex *>::const_iterator itr = find(Vertexs.begin(), Vertexs.end(), v);
        typename list<Vertex *>::const_iterator itr = Vertexs.begin(); //itr是指针的指针
        for (; itr != Vertexs.end(); ++itr) {
            //*itr才是Vertex * 类型
            if ((*itr)->element == v->element) {
                return 1;
            }
        }
        return 0;
    }
    void addNode(Vertex * v) {
        if (!exist(v)) {
            Vertexs.push_back(v);
            //++VerNum;
        }
    }
    void addEdge(Vertex * v1, Vertex * v2) { //由v1指向v2
        addNode(v1);
        addNode(v2);
        if (!v1->exist(v2)) {
            v1->adj.push_back(v2);
            ++(v2->indegree);
            ++EdgNum;
        }
    }
};


#endif //DAY11_GRAPH_H
