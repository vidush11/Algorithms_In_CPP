#include <cstdio>
#include <iostream>
#include <cmath>
#include <variant>
#include <fstream>
#include <vector>
#include <time.h>
#include <map>

using namespace std;


double epsilon=1e-9;
enum class ORT{
    left,
    right,
    between,
    before,
    after,
};

enum class type{
    point,
    line_segment,
    event_queue,
    status_queue,
};

void print_ORT(ORT ort){
    switch (ort){
        case (ORT::left):{
            cout<<"left"<<endl;
        }break;
        case (ORT::right):{
            cout<<"right"<<endl;
        }break;
        case (ORT::between):{
            cout<<"between"<<endl;
        }break;
        case (ORT::before):{
            cout<<"before"<<endl;
        }break;
        case (ORT::after):{
            cout<<"after"<<endl;
        }break;
    }
}

struct Point{
    double x;
    double y;
    type booby_tag= type::point;
    
    Point():x{__DBL_MIN__}, y{__DBL_MIN__}{}
    Point(double x, double y): x{x}, y{y}{}
    
    
    ORT orientation(Point& source, Point& target){
        Point self_direction=*this- source;
        Point target_direction=target- source;
        
        double val=self_direction.perp_dot(target_direction);
        
        if (val<-epsilon){
            return ORT::left;
        }
        else if (val>epsilon){
            return ORT::right;
        }
        else {
            double ratio=self_direction.x/target_direction.x;
            if (ratio<0){
                return ORT::before;
            }
            else if (ratio>1){
                return ORT::after;
            }
            else{
                return ORT::between;
            }
        }
    }
    
    double dot(Point& other){
        return x*other.x+y*other.y;
    }
    
    double perp_dot(Point& other){
        return x*other.y-y*other.x;
    }
    
    bool operator==(const Point& other) const{
        return abs(x-other.x)<=epsilon and abs(y-other.y)<=epsilon;
    }
    
    bool operator!=(const Point& other) const{
        return not (*this == other);
    }
    
    bool operator<(const Point& other) const{
        return (  (*this).y<other.y || ( (*this).y==other.y && (*this).x<other.x )  );
    }
    
    Point operator+(const Point& other){
        Point temp=*this;
        temp.x += other.x;
        temp.y += other.y;
        return temp;
    }
    
    Point operator-(const Point& other){
        Point temp=*this;
        temp.x -= other.x;
        temp.y -= other.y;
        return temp;
    }
    
    Point operator*(double other){
        Point temp=*this;
        temp.x *= other;
        temp.y *= other;
        return temp;
    }
    

};

Point operator*(double other, const Point& point){
    Point temp=point;
    temp.x *= other;
    temp.y *= other;
    return temp;
}

ostream& operator<<(ostream& os, const Point& point)
{
    os << point.x << " " << point.y;
    return os;
}

double max(double a, double b){
    double answer=a;
    if (b>a) answer=b;
    return answer;
}

double min(double a, double b){
    double answer=a;
    if (b<a) answer=b;
    return answer;
}

struct LineSegment{
    Point upper;
    Point lower;
    type booby_tag= type::line_segment;
    
    LineSegment(): upper{}, lower{}{}
    
    LineSegment(Point p, Point q): upper{q}, lower{p}{
        if (p.y>q.y or (p.y==q.y and p.x<=q.x)){
            
            upper=p;
            lower=q;
        }
    }
    
    auto intersection(LineSegment& other){
        Point self_direction=upper-lower;
        Point other_direction=other.upper-other.lower;
        
        Point lower_offset=other.lower-lower;
        double sd_od=self_direction.perp_dot(other_direction);
        double od_l=lower_offset.perp_dot(other_direction);
        double sd_l=lower_offset.perp_dot(self_direction);
        
        variant<int, Point, LineSegment> answer;
        answer=0;
        
        if (abs(sd_od)>epsilon){ //if they aren't parallel
            double a=od_l/sd_od;
            double b=sd_l/sd_od;
            
            if ( (-epsilon<=a)&&(a<=1+epsilon) && (-epsilon<=b)&&(b<=1+epsilon) ){
                answer= lower+self_direction* a;
            }
            else {
                answer= 0;
            }
   
            return answer;
        }
        
        if (abs(od_l)<=epsilon || abs (sd_l)<=epsilon){ //they are parallel 'and on the same line (this check ensures that)'
            Point upper_offset=other.upper-lower;
            double self_dot=self_direction.dot(self_direction);
            
            double lower_div=(lower_offset.dot(self_direction) )/self_dot;
            double upper_div=(upper_offset.dot(self_direction) )/self_dot;
            
            double lower_clipped=max(0,lower_div);
            double upper_clipped=min(upper_div,1);
            
            Point lower_interection=lower+lower_clipped*self_direction;
            
            if (lower_clipped==upper_clipped){ //why not abs(diff)<=epsilon
                answer= lower_interection;

            }
            else if (lower_clipped<upper_clipped){
                Point upper_intersection=lower+upper_clipped*self_direction;
                answer= LineSegment(lower_interection,upper_intersection);
            }
            else answer=0; //no intersection if lower_clipped>upper_clipped
            return answer;
        }
            
        else {return answer;}
        
    }
    
    double length(){
        double lensq=(upper.x-lower.x)*(upper.x-lower.x)+(upper.y-lower.y)*(upper.y-lower.y);
        return sqrt(lensq);
    }
    
};

ostream& operator<<(ostream& os, const LineSegment& line)
{
    os << line.upper << " ; " << line.lower;
    return os;
}

//later code for data structures

enum class CRT{
    before,
    after,
    match,
};

void print_CRT(CRT crt){
    switch (crt){
        case (CRT::before):{
            cout<<"before"<<endl;
        }break;
        case (CRT::after):{
            cout<<"after"<<endl;
        }break;
        case (CRT::match):{
            cout<<"match"<<endl;
        }break;
    }
    return;
}


Point ep;

CRT event_comparer(Point& p, Point& key){
    if (p==key) return CRT::match;
    else if ( (p.y>key.y + epsilon) || (key.y-p.y<=epsilon and epsilon+ p.x<key.x) )return CRT::before;
    else return CRT::after;
}

CRT status_comparator(Point& ep, Point& p, LineSegment& key){
    //if ( key.lower.y<=p.y+epsilon and p.y<=key.upper.y+epsilon ){} //good code by adding epsilon
    
//    if ( abs(key.upper.x-key.lower.x)<=epsilon ){
//        if (key.upper.x-p.x>epsilon ) return CRT::before;
//        else if (p.x-key.lower.x > epsilon) return CRT::after;
//        else return CRT::match;
//    }
    ORT ort=p.orientation(key.lower, key.upper);
    if (ort==ORT::left or ort==ORT::before) return CRT::before;
    else if (ort==ORT::right or ort==ORT::after) return CRT::after;
    else return CRT::match;
}

CRT status_comparator(Point& ep, LineSegment& ls, LineSegment& key){ //ep- event_point
    
    //        if ( (ls.lower.y<=ep.y+epsilon and ep.y<=ls.upper.y+epsilon) and (key.lower.y<=ep.y+epsilon and ep.y<=key.upper.y+epsilon) ){}
    //    is the above if check really necessary
    
    //special cases
    if ( abs(ls.lower.y-key.lower.y)<=epsilon and abs(ls.lower.x-key.lower.x)<=epsilon and abs(ls.upper.y-key.upper.y)<=epsilon and abs(ls.upper.x-key.upper.x)<=epsilon ) return CRT::match; //same segments
    
    auto inter= (ls.intersection(key));
    
    if (get_if<LineSegment>(&inter) ){
        vector<double> ls_coords{ls.upper.x, ls.upper.y, ls.lower.x, ls.lower.y}; //arbitary order for comparing segments
        vector<double> key_coords{key.upper.x, key.upper.y, key.lower.x, key.lower.y};
        
        for (int i=0; i<4; i++){
            if (ls_coords[i]<key_coords[i]) return CRT::before;
            else if (ls_coords[i]>key_coords[i]) return CRT::after;
            
        }
        return CRT::match;
    }
    
    if ( abs(ls.upper.y-ls.lower.y)<=epsilon){ //need to be updated?
        if (status_comparator(ep,ep ,key)==CRT::before) return CRT::before;
        else return CRT::after;
    }
    else if (abs(key.upper.y-key.lower.y)<=epsilon){
        if (status_comparator(ep, ep, ls)==CRT::before) return CRT::after;
        else return CRT::before;
    }
    
    double mini=min(min(key.upper.x, key.lower.x), min(ls.upper.x, ls.lower.x))-1;
    double maxi=max(max(key.upper.x, key.lower.x), max(ls.upper.x, ls.lower.x))+1;
    
    
    LineSegment sweep_line=LineSegment(Point(mini, ep.y), Point(maxi,ep.y));
    Point seg_1=get<Point>(sweep_line.intersection(ls));
    Point seg_2=get<Point>(sweep_line.intersection(key));
    
    CRT cr=status_comparator(ep, seg_1 , key);
    CRT cr2=status_comparator(ep, seg_2, ls);
    
    if (seg_1==seg_2 or cr==CRT::match or cr2==CRT::match){
        CRT ori_ep;
        ori_ep= status_comparator(ep, ep, ls); // can do ls or key both will give same result as event point lies on same side of them always (left/right)
//        if ( (ep.x<seg_1.x+ epsilon) || (ep.x<seg_2.x+epsilon) ) ori_ep=ORT::left;
//        else ori_ep=ORT::right;
        
//        ORT ori= ls.upper.orientation(key.lower, key.upper);
//
//        if (ori_ep==ORT::left){
//            if (ori==ORT::left) {return CRT::before;}
//            else {return CRT::after;}
//        }
//        else {  //if (ori_ep==ORT::between or ori_ep==ORT::right)
//            if (ori==ORT::left) return CRT::after;
//            else return CRT::before;
//        }
        Point endpoint= (ori_ep==CRT::before) ? ls.upper : ls.lower;
        ORT ori= endpoint.orientation(key.lower, key.upper);
        
        if (ori==ORT::left){
            return CRT::before;
        }
        else return CRT::after;
    }
    else {
        return cr;
    }
}

//            double y=(max(ls.lower.y, key.lower.y)+ep.y)/2;
//            LineSegment sweep_line=LineSegment(Point(mini, y), Point(maxi,y));
//            seg_1=get<Point>(sweep_line.intersection(ls));
//            seg_2=get<Point>(sweep_line.intersection(key));

// comparator code above (recheck)

struct Node_Point{
    Point key;
    vector<LineSegment> value;
    
    int level=0;
    Node_Point *left;
    Node_Point *right;
    
    type booby_tag= type::event_queue;

};

struct Node_LS{
    LineSegment key;
    int level=0;
    Node_LS *left;
    Node_LS *right;
    type booby_tag= type::status_queue;
    

};

int get_height(auto node){
    if (not node) return 0;
    else return node->level;
}

void update(auto &node){
    int lh= node->left ? node->left->level : 0;
    int rh= node->right ? node->right->level : 0;

    node->level=max(lh, rh)+1;
}

void rr(auto &node){
    auto temp= node->left;
    node->left=temp->right;
    temp->right=node;
    update(node);
    update(temp);
    
    node=temp;
    
}

void ll(auto &node){
    auto temp=node->right;
    node->right=temp->left;
    temp->left=node;
    update(node);
    update(temp);
    
    node=temp;
}

void balance(auto &node){
    
    int lh=get_height(node->left);
    int rh=get_height(node->right);
    
    if (lh-rh >1){

        if (get_height(node->left->left)<get_height(node->left->right)){
            ll(node->left);
        }
        rr(node);
    }
    
    else if (rh-lh >1){

        if (get_height(node->right->left)>get_height(node->right->right)){
            rr(node->right);
        }
        ll(node);
    }
    
}

bool insert(Point key, LineSegment value, Node_Point* &node){ //event_comparer update with linesegment
    
    bool is_present;
    
    if (not node){
        Node_Point* new_node=new Node_Point;
        new_node->key=key;
        new_node->value.push_back(value);
        new_node->level=1;
        
        node=new_node;
        is_present=false;
    }
    
    else {
        CRT cr= event_comparer(key, node->key);
        
        if (cr==CRT::before){
            is_present=insert(key, value, node->left);
        }
        else if (cr==CRT::after){
            is_present=insert(key,value, node->right);}
        else { //CRT::match
            node->value.push_back(value);
            is_present= true;
        }
    }
    
    if (is_present==false){
        update(node);
        balance(node);
        
    }
    
    return is_present;
    
}


bool insert(Point key, Node_Point* &node){ //event_point comparer without linesegment update
    
    bool is_present;
    
    if (not node){
        Node_Point* new_node=new Node_Point;
        new_node->key=key;
        new_node->level=1;
        
        node=new_node;
        is_present=false;
    }
    
    else {
        CRT cr= event_comparer(key, node->key);
        
        if (cr==CRT::before){
            is_present=insert(key, node->left);
        }
        else if (cr==CRT::after){
            is_present=insert(key, node->right);}
        else { //CRT::match
            is_present= true;
        }
    }
    
    if (is_present==false){
        update(node);
        balance(node);
    }
    return is_present;
}

bool insert(LineSegment key, Node_LS* &node){ //status_comparator update
    bool is_present;
    
    if (not node){
        Node_LS* new_node=new Node_LS;
        new_node->key=key;
        new_node->level=1;
        
        node=new_node;
        is_present=false;
    }
    
    else {
        CRT cr= status_comparator(ep, key, node->key);

        if (cr==CRT::before){
            is_present=insert(key, node->left);
        }
        else if (cr==CRT::after){
            is_present=insert(key, node->right);}
        else { //CRT::match
            is_present= true;
        }
    }
    
    if (is_present==false){
        update(node);
        balance(node);
        
    }
    
    return is_present;
}

bool del(Point key, Node_Point* &node){ //node is passed by reference and is the root in first call, key is to be found
    bool found;
    CRT cr;
    if (not node){
        found=false;
        return found;
    }
    
    cr=event_comparer(key, node->key);;

    if (cr==CRT::before){ found= del(key, node->left) ;}
    else if (cr==CRT::after){ found= del(key, node->right); }
    else { //cr==CRT::match
        if (not node->left){ node=node->right;}
        else if (not node->right) {node=node->left;}
        else {
            Node_Point* temp=node->right;
            while (temp->left){
                temp=temp->left;
            }
            
            node->key=temp->key;
            node->value=temp->value;
            
            del(temp->key, node->right); // node->right is important to update the levels, dont just do temp
        }
        found= true;
    }
    
    if (found) {
        if (node){
            update(node);
            balance(node);
        }
    }
    
    return found;

}

bool del(LineSegment key, Node_LS* &node){ //node is passed by reference and is the root in first call, key is to be found
    bool found;
    CRT cr;
    
    if (not node){
        found=false;
        return found;
    }
    
    cr=status_comparator(ep, key, node->key);
    
    if (cr==CRT::before){ found= del(key, node->left) ;}
    else if (cr==CRT::after){ found= del(key, node->right); }
    else { //cr==CRT::match
        if (not node->left){ node=node->right;}
        else if (not node->right) {node=node->left;}
        else {
            Node_LS* temp=node->right;
            while (temp->left){
                temp=temp->left;
            }
            
            node->key=temp->key;
            
            del(temp->key, node->right);
            
        }
        found= true;
    }
    
    if (found) {
        if (node){
            update(node);
            balance(node);
        }
    }
    
    return found;
}


Node_Point* pop_first(auto &node){
    if (not node) return 0;
    Node_Point* to_return;
    if (node->left){
        to_return=pop_first(node->left);
        balance(node);
        update(node);
    }
    else {
        to_return=node;
        node=node->right;
    }
    
    return to_return;
        
}


Node_LS* search_succ(auto key, Node_LS* answer, Node_LS* root){ //key can be linesegment or event point

    if (not root) return answer;
    CRT cr= status_comparator(ep, key, root->key);
    
    if (cr==CRT::before){
        return search_succ(key, root, root->left );
    }
    else {
        return search_succ(key, answer, root->right);
    }
    
    
}

Node_LS* search_pred(auto key, Node_LS* answer, Node_LS* root){ //key can be event point or linesegment

    if (not root) return answer;
    CRT cr=status_comparator(ep, key, root->key);
    
    if (cr==CRT::after){
        return search_pred(key, root ,root->right );
    }
    else {
        return search_pred(key, answer, root->left);
    }
    
}

vector <LineSegment> search_matching(Point p, Node_LS* root){
    vector <LineSegment> answer;

    
    if (not root){
        return answer;
    }
    
    CRT cr=status_comparator(ep, p, root->key);

    if (cr==CRT::before){
        
        return search_matching(p, root->left);
    }
    else if (cr==CRT::match){
        for (LineSegment l:search_matching(p,root->left) ){
            answer.push_back(l);
        }
        
        answer.push_back(root->key);
        
        for (LineSegment l:search_matching(p, root->right)){
            answer.push_back(l);
        }
    }
    else { //CRT::after
        
        return search_matching(p, root->right);
    }
    
    return answer;
    
}

//later

struct PlaneSweepLSI{
    
    auto PlaneSweep(vector<LineSegment> lines){
        map<Point, vector<LineSegment>> answer;
        
        Node_Point* event_queue=0;
        //insertion(initialization of event_queue)
        for (LineSegment line: lines){
            
            insert(line.upper, line, event_queue);
            insert(line.lower, event_queue);
            
        }
        
        int u;
        int o;
        int c;
        
        Node_LS* status_queue=0;
        
//        int i=0;
        while (event_queue){
//            cout<<i<<endl;
            Node_Point* curr_event= pop_first(event_queue);
            Point ep_= curr_event->key;
            vector<LineSegment> upper=curr_event->value;
            vector<LineSegment> other;
            vector<LineSegment> contain;
            
            if (ep != Point(__DBL_MIN__,__DBL_MIN__)){

                other=search_matching(ep_, status_queue);
                
                for (LineSegment line: other){
                    del(line, status_queue);
                    
                    if (line.lower!=ep_){
                        contain.push_back(line);
                    }
                    
                }
  
            }
            
            ep=ep_;
            
            u=upper.size();
            o=other.size();
            c=contain.size();
                
              
            if ( (u+o)>1 ){ // intersections at this point
                for (int i=0; i<u; i++){
                    (answer[ep_] ).push_back(upper[i]);
                }
                for (int i=0; i<c; i++){
                    (answer[ep_] ).push_back(contain[i]);
                }
                
            }
             //still have to update status register
            for (int i=0; i<u; i++){
               
                insert(upper[i], status_queue);
            }
            for (int i=0; i<c; i++){
               
                insert(contain[i], status_queue);
            }
            
            
            Node_LS* left_pred= search_pred(ep, 0, status_queue);
            Node_LS* right_succ= search_succ(ep, 0, status_queue);
            

            
            if ( (u+c) >0){
                LineSegment left_seg= (not upper.empty()) ? upper[0] : contain[0];
                LineSegment right_seg= (not upper.empty()) ? upper[0] : contain[0];
                
                
                for (int i=0; i< upper.size(); i++){
                    CRT cr1=status_comparator(ep, upper[i], left_seg);
                    CRT cr2=status_comparator(ep, upper[i], right_seg);
                    
                    if (cr1==CRT::before) left_seg=upper[i];
                    if (cr2==CRT::after) right_seg=upper[i];
                }
                for (int i=0; i<contain.size(); i++){
                    CRT cr1=status_comparator(ep, contain[i], left_seg);
                    CRT cr2=status_comparator(ep, contain[i], right_seg);
                    
                    if (cr1==CRT::before) left_seg=contain[i];
                    if (cr2==CRT::after) right_seg=contain[i];
                }
                
//                    vector<LineSegment> ordered_contain= search_matching(ep, status_queue);
//                    LineSegment left_seg=ordered_contain[0];
//                       LineSegment right_seg=ordered_contain[ordered_contain.size()-1];
                if (left_pred) find_intersection(left_pred->key, left_seg, event_queue);
                if (right_succ) find_intersection(right_seg, right_succ->key, event_queue );
                

            }
            else {
                if (left_pred and right_succ){
                    find_intersection(left_pred->key, right_succ->key, event_queue);
                }
            }
            
//            i++;
        }

        return answer;
    }

    void find_intersection(LineSegment& l1 , LineSegment& l2, Node_Point* &event_queue){
        static variant<int, Point, LineSegment> item;
        item=l1.intersection(l2);
        
        if (auto p_=get_if<Point>(&item)){
            if (event_comparer(*p_, ep)== CRT::after){
                insert(*p_,event_queue);
            }
        }
        else if (auto l_=get_if<LineSegment>(&item)){
            Point u=(*l_).upper;
            Point l=(*l_).lower;
            
            if (event_comparer(u, ep)==CRT::after){
                insert(u, event_queue);
            }
            
            if (event_comparer(l, ep)==CRT::after){
                insert(l, event_queue);
            }
        }
    }
    
    
};

//code data structures finish
int main(){

    vector<LineSegment> Lines;
    map <Point, vector <LineSegment>> Intersections;
    ifstream fin("/Users/teo/Desktop/Algorithms_In_CPP/points/out1.txt");
    ofstream fout("/Users/teo/Desktop/Algorithms_In_CPP/points/intersections.txt");
    double x;
    double y;
    double k;
    double l;
    
    

    while (fin){
        fin>>x;
        fin>>y;
        fin>>k;
        fin>>l;
        
        Lines.push_back(LineSegment(Point(x,y), Point(k,l)));
    }
    Lines.pop_back();
    


    clock_t start=clock();

//    int len=Lines.size();
//    for (int i=0; i<len; i++){
//        for (int j=i+1; j<len; j++){
//            auto inter=Lines[i].intersection(Lines[j]);
//            if (auto p=get_if<Point>(&inter)){
////                Intersections.push_back(*p);
//                fout<<*p<<' ';
//            }
//        }
//    }

    PlaneSweepLSI my_algorithm= PlaneSweepLSI();
    Intersections= my_algorithm.PlaneSweep(Lines);
    
    map <Point, vector <LineSegment>> ::iterator iter;
    
    for (iter=Intersections.begin(); iter!=Intersections.end(); iter++){
        fout<<iter->first<<" ";
//        cout<<iter->first<<" : {";
//        for (LineSegment line: iter->second){
//            cout<<line<< ", ";
//        }
//        cout<<"}"<<endl;
    }
    clock_t end=clock();
    double time=(double) (end-start)/CLOCKS_PER_SEC;
    cout<<"Time Elapsed- "<<time<<"s."<<endl;
    
    return 0;
    
}
