#include "player.h"
#include "ctime"
#include "time.h"
#define ONE_SECOND ((clock_t)1000)
int player::showColor() {
    return colorflag;
}

point player::nextMove(const board &bd) {

    return tryMonteCarloTreeSearch(bd, maxTries);
}
//有问题
point player::tryMonteCarloTreeSearch(const board &bd, int maxTries) {

    Node root(bd,colorflag);
    clock_t start,finish;
    start=clock();
    for(int i=0;i<maxTries && (clock()-start)<ONE_SECOND*60;i++){

        Node node=root;

        Node* vl=node.treePolicy();
        double won=vl->defaultPolicy(vl->bd);
        vl->backup(won);

    }
    return root.bestChild()->move;
}

Node* Node::treePolicy() {

    Node* node=this;
    while (node->childNodes.size()!=node->bd.getAvaliable(color).size()){
        if(node->untriedMoves.size()!=0)
            return node->expand();
        else
            node=node->bestChild();
    }

    return node;
}
//对的。。
Node* Node::expand() {
    // vector<point>::iterator tmp;
    srand(time(0));
    int size= (int) this->untriedMoves.size();
    int i=rand()%(size);
    point move=this->untriedMoves.operator[](i);
    this->untriedMoves.erase(this->untriedMoves.begin()+i);
    Node *newchild=new Node(this->bd.oneStep(color,move),!color);   ///颜色的问题
    //这里是不是要指出parentnode
    newchild->parentNode=this;
    this->childNodes.push_back(newchild);
    return newchild;
}

Node* Node::bestChild() {
    int totalvisits=this->visits;
    double tmpvalues=0;
    double maxvalue=0;
    int tmpi=0;
    int size= (int) this->childNodes.size();

    for(int i=0;i<size;i++){
        Node* child=this->childNodes[i];
        tmpvalues=child->wins/child->visits + sqrt(2*log(totalvisits)/child->visits);
        if(tmpvalues>maxvalue){
            maxvalue=tmpvalues;
            tmpi=i;
        }
    }
    return this->childNodes[tmpi];
}

//有问题。。。。
void Node::backup(double score) {
    Node *node1=this;

    while(node1!=NULL){
        node1->update(score);
        node1=node1->parentNode;
    }
}

void  Node::update(double won) {
    this->wins+=won;
    this->visits+=1;
}

double Node::defaultPolicy(board bd) {
    board board1=bd;
    srand(time(0));
    int colorrem=color;
    while(board1.getAvaliable(colorrem).size()!=0){
        int i=rand()%((int)board1.getAvaliable(colorrem).size()); /////随机数
        point nextstep=board1.getAvaliable(colorrem).operator[](i);
        board1=board1.oneStep(colorrem, nextstep);   //yanse
        colorrem=!colorrem;
    }

    if(board1.winner()==color)
        return 0 ;
    else
        return 1;
}