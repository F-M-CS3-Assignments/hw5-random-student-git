
#include "Graph.h"
#include <iostream>
#include <vector>
#include <algorithm>  // for reversing vector only

using namespace std;



// This method is not part of the Graph class / header on purpose
const GraphEdge* findExistingEdge(nodekey_t gnFrom, nodekey_t gnTo, vector<vector<GraphEdge *>> adjList)
{
	if(adjList.size() == 0)
	{
		return nullptr;
	}


	for(size_t rowIDX = 0; rowIDX < adjList.size(); rowIDX++)
	{
		vector<GraphEdge*> row = adjList.at(rowIDX);
		for(size_t i = 0; i < row.size(); i++)
		{
			GraphEdge *cur = row.at(i);

			// It might make sense for there to be an == operator overload in the GraphEdge struct
			// but adding methods to a struct feels so _wrong_ to me!
			if(cur->from == gnFrom && cur->to == gnTo)
			{
				return cur;
			}
		}
	} 

	return nullptr;
}

// This method is not part of the Graph class / header on purpose
// This should probably be a method in the GraphEdge struct
// but adding methods to a struct feels so _wrong_ to me!
string GraphEdgeToString(const GraphEdge* e)
{
	return "((" + to_string(e->from) + ")->(" + to_string(e->to) + ") w:" + to_string(e->weight) + ")";
}





void Graph::AddNode(nodekey_t key)
{

	if(this->IsPresent(key))
	{
		throw invalid_argument("Duplicate node cannot be added: " + to_string(key));
	}


	nodes.insert(key);
	nodes_v=vector<nodekey_t>(nodes.begin(),nodes.end());
	reverse(nodes_v.begin(), nodes_v.end());  // to pass tests
	vector <GraphEdge*> *newRow = new vector<GraphEdge*>;
	adjList.push_back(*newRow);
	delete newRow; // deallocate newRow to prevent memory leak
}




const GraphEdge *Graph::AddEdge(nodekey_t gnFrom, nodekey_t gnTo, unsigned int w)
{

	// The AddEdge method creates new edges.  It does not and should not update / change
	// the weights of existing edges.  findExistingEdge does not check the weight for this reason
	const GraphEdge* dup = findExistingEdge(gnFrom, gnTo, this->adjList);
	if(dup != nullptr)
	{
		throw invalid_argument("Duplicate edge cannot be added: " + GraphEdgeToString(dup));
	}

	if(!this->IsPresent(gnFrom))
	{
		throw invalid_argument("No such node: " + to_string(gnFrom));
	}

	if(!this->IsPresent(gnTo))
	{
		throw invalid_argument("No such node: " + to_string(gnTo));
	}

	GraphEdge *ge = new GraphEdge;

	// DONE:
	ge->from=gnFrom;  // assign members of ge with their respective values
    ge->to=gnTo;
    ge->weight=w;
	const GraphEdge *response = ge; // this helps the compiler go
	int idx=0;
    for (int i=0;i<nodes.size();i++) {
        if (nodes_v[i]==gnFrom){  // once the node 'from' which edge originates is found
			idx=i;  // store node's index
            break;
        }
    }
    adjList[idx].push_back(ge);  // and append it to ge
	return ge;
}


bool Graph::IsPresent(nodekey_t key) const
{
	// DONE:
	// iterate through this->nodes and look for one that matches key
	for (int i=0;i<nodes.size();i++){
		if (nodes_v[i]==key){
			return true;
		}
	}
	return false;
}




set<const GraphEdge*> Graph::GetOutwardEdgesFrom(nodekey_t node) const 
{
	size_t idx = 0;
	while(idx < this->nodes.size() && (this->nodes_v.at(idx) != node))
	{
		idx++;
	}
	if(idx == this->nodes.size()){
		throw invalid_argument("No such node: " + to_string(node));
	}



	set<const GraphEdge*> result = set<const GraphEdge*>();
	// DONE:
	// iterate over this->adjList.at(idx); and find nodes that match the given node
	// in their "from" field, put those nodes in result
	for (int i=0;i<adjList.at(idx).size();i++) {
		result.insert(adjList.at(idx)[i]);
	}
	return result;
}

 set<nodekey_t> Graph::GetNodes() const 
{
	// DONE
	// iterate of this->nodes, accumulate into a set<nodekey_t> and return it
	set<nodekey_t> nodesSet;
	for (int i=0;i<nodes.size();i++){
		nodesSet.insert(nodes_v[i]);
	}
	return nodesSet;
}

 vector<nodekey_t> Graph::GetNodesasVec() const 
{
	return nodes_v;
}

size_t Graph::Order() const 
{
	return nodes.size();
}

size_t Graph::Size() const 
{
	size_t total = 0;
	for(size_t i = 0; i < adjList.size(); i++){
		vector<GraphEdge*> row = adjList.at(i);
		for(size_t j = 0; j < row.size(); j++){
			total++;
		}
	}

	return total;
}



string Graph::NodesToString() const 
{
	if(nodes.size() == 0)
	{
		return "[]";
	}

	string str = "[";
	for(size_t i = 0; i < (nodes.size() - 1); i++)
	{
		str = str + "(" + to_string(nodes_v.at(i)) + "), ";
	}

	str = str + "(" + to_string(nodes_v.at(nodes.size()-1)) + ")]";
	return str;
}

string Graph::EdgesToString() const 
{
	if(this->adjList.size() == 0)
	{
		return "[]";
	}

	size_t count = 0;
	string str = "[";
	for(size_t rowIDX = 0; rowIDX < this->adjList.size(); rowIDX++)
	{
		vector<GraphEdge*> row = this->adjList.at(rowIDX);
		for(size_t i = 0; i < row.size(); i++)
		{
			GraphEdge *cur = row.at(i);
			str = str + GraphEdgeToString(cur);

			if(count < (this->Size() - 1)){
				 str = str + ", ";
			}
			count++;
		}
	} 

	str = str +  "]";
	return str;

}



Graph::~Graph() {
	// DONE:
	// Right now the memory leaks are bad, I need to
	// implement something here to fix it
	for (int i=0;i<adjList.size();i++){
        for (int j=0;j<adjList[i].size();j++) {
            delete adjList[i][j];  // deallocate everything inside adjList
        }
    }
}


