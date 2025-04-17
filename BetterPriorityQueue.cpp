#include <queue>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>
#include "BetterPriorityQueue.h"
#include "Graph.h"

bool BetterPriorityQueue::Update(BPQNode n){
    for (int i=0;i<c.size();i++) {   // this->c is not necessary, and it's a huge pain to write. anyways, when we scan c...
        if (c[i].gnode==n.gnode && n.pri<c[i].pri) {  // if we've found the same node and n has shorter distance
            c[i].pri=n.pri;   // then update node
            make_heap(c.begin(),c.end());  //  and reconstruct priority queue since it's likely disarranged now
            return true;
        }
    }
    return false;   // update did not happen
}
bool BetterPriorityQueue::Contains(BPQNode n){
    for (int i=0;i<c.size();i++){   // if c contains n, return true, otherwise return false
        if (c[i].gnode==n.gnode){
        return true;
        }
    }
    return false;
}
string BetterPriorityQueue::BPQNodeToString(const BPQNode& n){
    return "("+to_string(n.gnode)+", pri: "+to_string(n.pri)+")";  // return string concatenation
}

string BetterPriorityQueue::ToString() const{
    string queuestr="[";
    for (int i=0;i<c.size();i++){   // for all nodes in c
        queuestr+=BPQNodeToString(c[i]);  // concatenate each node
        if (i!=c.size()-1){    // use commas if not the last node
            queuestr+=",";
        }
    }
    queuestr+="]";  // to close the queue
    return queuestr;
}