#ifndef NODE_H
#define NODE_H

#include "TileInfo.h"
#include <vector>


class Node 
{
public:
    enum { NB_NEIGHBOURS = 6 };

private:
    TileInfo mTileInfo;

    Node* mFrom;                        //Maybe not so useful...
    std::vector<Node*> mNeighbours;     //CW - 0 on right side

public:
    Node(Node* other)
        : mTileInfo(other->mTileInfo), mFrom{ other->mFrom }, mNeighbours{ other->mNeighbours }
    {}
    Node(TileInfo& currTileInfo)
        : mTileInfo( currTileInfo ), mFrom{ nullptr }, mNeighbours{ NB_NEIGHBOURS }
    {}
    Node(TileInfo& currTileInfo, Node* from)
        : mTileInfo(currTileInfo), mFrom{ from }, mNeighbours{ NB_NEIGHBOURS }
    {
        mNeighbours[0] = nullptr;
        mNeighbours[1] = nullptr;
        mNeighbours[2] = nullptr;
        mNeighbours[3] = from;
        mNeighbours[4] = nullptr;
        mNeighbours[5] = nullptr;

        from->mNeighbours[0] = this;
    }
    //TODO: constructeur par mouvement

    ~Node()
    {
        delete mFrom;
    }

    unsigned int getID() const { return mTileInfo.tileID; }
    std::set<ETileAttribute>& getTileAttributes() { return mTileInfo.tileAttributes; }
    std::vector<Node*> getNeighbours() const { return mNeighbours; }
    Node* getNeighbour(int i) const { return mNeighbours[i]; }
    void setNeighbour(Node* neighbour, unsigned int idxNeighb, unsigned int idxCurr)
    {
        mNeighbours[idxNeighb] = neighbour;
        neighbour->mNeighbours[idxCurr] = this;
    }
};

#endif // !NODE_H