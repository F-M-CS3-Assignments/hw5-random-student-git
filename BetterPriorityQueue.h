#include <queue>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>
#include "Graph.h"

// I learnt about priority queue here: https://www.youtube.com/watch?v=dxHx7EYehAQ and https://stackoverflow.com/questions/74097037/inheritance-from-stl-priority-queue-with-custom-comparator-not-working


struct BPQNode {
	int pri = INT_MAX;
	bool visited = false;
	nodekey_t gnode = INVALID_NODE_KEY;
	
	bool operator<(const BPQNode &other) const {
		return pri < other.pri;
	}

	bool operator>(const BPQNode &other) const {
		return pri > other.pri;
	}
	
	bool operator==(const BPQNode &other) const {
		return this->gnode == other.gnode;
	}
};

class BetterPriorityQueue : public priority_queue<BPQNode,vector<BPQNode>,greater<BPQNode>> {
public:  
    // declare methods
    bool Update(BPQNode n);
    bool Contains(BPQNode n);
    static string BPQNodeToString(const BPQNode& n);
    string ToString() const;
};


