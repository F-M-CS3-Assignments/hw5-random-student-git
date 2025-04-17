#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <climits>

using namespace std;

// I learnt about Dijkstra here: https://www.youtube.com/watch?v=V6H1qAeB-l4

// Time Complexity: O((E + V) log V)

int dijkstra(nodekey_t start, nodekey_t end, const Graph *g) {
    BetterPriorityQueue bet;  // create a priority queue 
    vector<nodekey_t> ns;   // contain graph nodes
    vector<int> min_d; // store the minimal weights
    ns = g->GetNodesasVec();   // store graph nodes in ns
    for (int i=0;i<ns.size();i++) {
        min_d.push_back(INT_MAX);     //  in the beginning, the minimal weights are all infinity (maxed out)
    }
    
    int start_i=-1;
    for (int i=0;i<ns.size();i++) {   // for node in nodes
        if (ns[i]==start) {        //  if start node is found
            min_d[i]=0;             // the mimimum weight here is 0 since we're already here
            start_i=i;        // store the start node's index
            break;
        }
    }
    if (start_i==-1) {     // if there's no start node
        return -1;         // can't do anything, terminate
    }
    BPQNode s;       // make a BPQNode 
    s.gnode=start;  // for the start
    s.pri=0;        //  and set priority distance as 0
    bet.push(s);     // add start node to priority queue
    while (bet.size()>0){      //  while priority queue isn't empty
        BPQNode cur=bet.top();   // current node will be node with smallest distance
        bet.pop();       // and remove from queue since we've taken it out
        if (cur.gnode==end){    // if we've reached the end, then already just return its distance
            return cur.pri;
        }
        int cur_i=-1;   
        for (int i=0;i<ns.size();i++){  // for node in nodes
            if (ns[i]==cur.gnode){   // once we've found the current node in ns, store its index
                cur_i=i;             // in cur_i
                if (cur.pri>min_d[i]){   // unless its distance is longer, which in that case revert the assigning
                    cur_i=-1;
                    break;
                }
                break;
            }
        }
        if (cur_i==-1){    
            continue;    // skip this node as it has no index
        }
        if (g->GetOutwardEdgesFrom(cur.gnode).empty()){   // if no adjacent nodes, skip
            continue;
        }
        set<const GraphEdge*> e_s=g->GetOutwardEdgesFrom(cur.gnode);  // stores all outward edges as a set
        vector<const GraphEdge*> e_v(e_s.begin(),e_s.end());  // convert set to vector for indexing
        for (int i=0;i<e_v.size();i++){  // for edge in edges
            const GraphEdge* e=e_v[i];  // current edge
            nodekey_t adj=e->to;   // store what node the edge is pointing to in adj
            for (int j=0;j<ns.size();j++){  // for node in nodes
                if (ns[j]==adj){         // finding our adjacent node
                    int cand=min_d[cur_i]+e->weight;   // calculate new candidate's distance
                    if (cand>=min_d[j]){   // if higher distance, then break as it's useless
                        continue;
                    }
                    if (cand<min_d[j]){  // but if lower distance
                        min_d[j]=cand;   // then we have a new lowest distance
                        BPQNode adj_n{adj,cand,adj};  // make a BPQNode for this adjacent node
                        if (bet.Contains(adj_n)){ // update the node in the priority queue if it exists
                            bet.Update(adj_n);
                        } 
                        else{
                            bet.push(adj_n); // but if the node doesn't exist in the priority queue, then append it
                        }
                        break;
                    }
                }
            }
        }
    }
    return -1; // no path found
}
#endif