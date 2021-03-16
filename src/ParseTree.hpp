struct Node {
    Node parentNode;
    std::vector<Node> childNodes;
    inline Node(Node &parentNode): parentNode(parentNode) {};
    virtual Print(); 
};

struct Expression : public Node {
    
};

struct Argument : public Node {
    
};

struct Data : public Node {
    
};

struct List : public Data {

};
