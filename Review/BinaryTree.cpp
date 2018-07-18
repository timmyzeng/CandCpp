#include <iostream>
#include <cstdlib>
#include <stack>
#include <queue>
#include <string>

using namespace std;

struct BinaryTreeNode {
    struct BinaryTreeNode * _left;
    struct BinaryTreeNode * _right;
    int _val;

    BinaryTreeNode(int x)
        :_left(NULL)
         ,_right(NULL)
         ,_val(x)
    {}
};

class BinaryTree{
    typedef BinaryTreeNode Node;
public:
    Node* BulidTree(int arr[], int& index, int inval){
        Node* root = NULL;
        if(arr[index] != inval){
            root = new Node(arr[index]);
            root->_left = BulidTree(arr, ++ index, inval);
            root->_right = BulidTree(arr, ++ index, inval);
        }
        return root;
    }

    BinaryTree(int* arr, int inval){
        int index = 0;
        _root = BulidTree(arr, index, inval);
    }

    //1. 前序/中序/后序遍历（递归&非递归）
    void _PrevOrder(Node* root){
        if(root){
            cout << root->_val << " ";
            _PrevOrder(root->_left);
            _PrevOrder(root->_right);
        }
    }
    void PrevOrder(){
        _PrevOrder(_root);
        cout << endl;
    }

    void PrevOrderNoR(){
        stack<Node*> s;
        Node* cur = _root;
        while(cur || !s.empty()){
            while(cur){
                cout << cur->_val << " ";
                s.push(cur);
                cur = cur->_left;
            }
            cur = s.top();
            cur = cur->_right;
            s.pop();
        }
        cout << endl;
    }

    void InOrderNoR(){
        stack<Node*> s;
        Node* cur = _root;
        while(cur || !s.empty()){
            while(cur){
                s.push(cur);
                cur = cur->_left;
            }
            cur = s.top();
            s.pop();
            cout << cur->_val << " ";
            cur = cur->_right;
        }
        cout << endl;
    }

    void PostOrderNoR(){
        stack<Node*> s;
        Node* cur = _root;
        Node* prev = NULL;
        while(cur || !s.empty()){
            while(cur){
                s.push(cur);
                cur = cur->_left;
            }
            //不能使用cur代替top
            Node* top = s.top();
            if(top->_right == NULL || prev == top->_right){
                cout << top->_val << " ";
                prev = top;
                s.pop();
            }
            else{
                cur = top->_right;
            }
        }
        cout << endl;
    }

    //2. 层序遍历
    void LevelOrder(){
        queue<Node*> q;
        Node* cur = _root;
        q.push(cur);
        while(cur){
            cout << cur->_val << " ";
            if(cur->_left)
                q.push(cur->_left);
            if(cur->_right)
                q.push(cur->_right);
            q.pop();
            cur = q.front();
        }
        cout << endl;
    }

    //3. 求二叉树的高度
    int Height(){
        return _Height(_root);
    }

    int _Height(Node* root){
        if(root == NULL){
            return 0;
        }
        int left = _Height(root->_left);
        int right= _Height(root->_right);
        return (left > right ? left : right) + 1;
    }
    
    //4. 求叶子节点的个数
    int LeafNode(){
        return _LeafNode(_root);
    }
    int _LeafNode(Node* root){
        if(root == NULL){
            return 0;
        }
        if(root->_left == NULL && root->_right == NULL){
            return 1;
        }
        return _LeafNode(root->_left) + _LeafNode(root->_right);
    }

    //5. 求二叉树第k层的节点个数
    int KNode(int k){
        return _KNode(_root, k);
    }
    int _KNode(Node* root, int k){
        if(root == NULL)
            return 0;
        if(k == 1)
            return 1;
        return _KNode(root->_left, k-1)
             + _KNode(root->_right, k-1);
    }

    //6. 判断一个节点是否在一棵二叉树中
    bool InBinaryTree(Node* node){
        return _InBinaryTree(_root, node);
    }
    bool _InBinaryTree(Node* root, Node* node){
        if(root == NULL)
            return false;
        if(root->_val == node->_val)
            return true;
        return _InBinaryTree(root->_left, node) ||
               _InBinaryTree(root->_right, node);
    }

    bool InBinaryTreeNoR(Node* node){
        Node* cur = _root;
        stack<Node*> s;
        while(cur || !s.empty()){
            while(cur){
                if(cur->_val == node->_val)
                    return true;
                s.push(cur);
                cur = cur->_left;
            }
            cur = s.top()->_right;
            
            s.pop();
        }
        return false;
    }

    //7. 求两个节点的最近公共祖先
    Node* LestCommonAncestor(Node* node1, Node* node2){
        return _LCA(_root, node1, node2);
    }

    Node* _LCA(Node* root, Node* node1, Node* node2){
        if(root == NULL || node1 == NULL || node2 == NULL)
            return NULL;
        if(root == node1 || root == node2)
            return root;
        
        Node* cur = NULL;

        Node* left = _LCA(root, node1, node2);
        if(left){
            cur = _LCA(left->_left, node1, node2);
            if(cur)
                return left;
            cur = _LCA(left->_right, node1, node2);
            if(cur)
                return left;
        }
        Node* right = _LCA(root, node1, node2);
        if(right){
            cur = _LCA(right->_left, node1, node2);
            if(cur)
                return right;
            cur = _LCA(right->_right, node1, node2);
            if(cur)
                return right;
        }

        if(left && right)
            return root;
        if(left)
            return left;
        if(right)
            return right;
    }

    //8. 判断一棵二叉树是否是平衡二叉树
    bool Isbalanced(){
        int height = 0;
        return _Isbalanced(_root, height);
    }

    bool _Isbalanced(Node* root, int& height){
        if(root == NULL){
            height = 0;
            return true;
        }
        int left = 0;
        int right = 0;

        if(_Isbalanced(root->_left, left)
        && _Isbalanced(root->_right, right)){
            if(abs(left-right) < 2){
                height = (left > right ? left : right) + 1;
                return true;
            }
        }
        return false;
    }

    //9. 求二叉树中最远的两个节点的距离
    int FarthestNode(){
        int left = 0;
        int right = 0;
        int max = 0;
        _FarthestNode(_root, left, right, max);
        return max;
    }
    void _FarthestNode(Node* root, int& left, int& right, int & max){
        if(root == NULL){
            left = right = max = 0;
            return;
        }
        int leftL = 0;
        int rightL = 0;
        int leftR = 0;
        int rightR = 0;
        _FarthestNode(root->_left, leftL, rightL, max);
        _FarthestNode(root->_right, leftR, rightR, max);
        left = (leftL > rightL ? leftL : rightL) + 1;
        right = (leftR > rightR ? leftR : rightR) + 1;
        max = (left+right-1) > max ? (left+right-1) : max;
    }

    //10. 由前序遍历和中序遍历重建二叉树（前序序列：1 2 3 4 5 6 - 中序序列:3 2 4 1 6 5）
    void RebuildTree(string& Prev, string& In){
        if(Prev.size() != In.size() ||
           Prev.empty() || In.empty()){
            _root = NULL;
            return;
        }
        _root = Rebuild(Prev, 0, Prev.size()-1, In, 0, In.size()-1);
    }

    Node* Rebuild(string& Prev, int Pbegin, int Pend, string& In, int Ibegin, int Iend){
        if(Pbegin >= Prev.size()){
            return NULL;
        }
        Node* root = new Node(Prev[Pbegin]-48);
        int index = Ibegin;
        int num = 0;
        while(index <= Iend){
            if(Prev[Pbegin] == In[index]){
                break;
            }
            ++ index;
            ++ num;
        }

        if(Pbegin != Pend){
            root->_left = Rebuild(Prev, Pbegin+1, Pbegin+num, In, Ibegin, index-1);
            root->_right= Rebuild(Prev, Pbegin+num+1, Pend, In, index+1, Iend);
        }
        else{
            root->_left = NULL;
            root->_right = NULL;
        }
        return root;
    }

    //11. 判断一棵树是否是完全二叉树
    bool IsCompleteBinaryTree(){
        queue<Node*> q;
        Node* cur = _root;
        q.push(cur);
        while(cur){
            q.push(cur->_left);
            q.push(cur->_right);
            q.pop();
            cur = q.front();
        }
        while(!q.empty()){
            if(q.front() != NULL){
                return false;
            }
            q.pop();
        }
        return true;
    }

    //12. 求二叉树的镜像
    void Mirror(){
        _Mirror(_root);
    }

    void _Mirror(Node* root){
        if(root == NULL){
            return;
        }
        swap(root->_left, root->_right);
        _Mirror(root->_left);
        _Mirror(root->_right);
    }

    //13. 将二叉搜索树转换成一个排序的双向链表。要求不能创建任何新的结点，只能调整树中结点指针的指向。
    void TreeToList(){
        Node* cur = _root;
        Node* prev = NULL;
        bool first = true;
        stack<Node*> s;
        while(cur || !s.empty()){
            while(cur){
                s.push(cur);
                cur = cur->_left;
            }
            cur = s.top();
            s.pop();
            if(first){
                first = false;
                _root = cur;
            }
            else{
                cur->_left = prev;
                prev->_right = cur;
            }
            prev = cur;
            cur = cur->_right;
        }
    }
    void PrintList(){
        Node* cur = _root;
        Node* prev = NULL;
        while(cur != NULL){
            cout << cur->_val << "->";
            prev = cur;
            cur = cur->_right;
        }
        cout << "NULL" << endl;
        cur = prev;
        while(cur != NULL){
            cout << cur->_val << "->";
            cur = cur->_left;
        }
        cout << "NULL" << endl;
    }

    void Distory(Node* root){
        if(root){
            Node* tmp = root;
            Distory(root->_left);
            Distory(root->_right);
            delete tmp;
        }
    }
    ~BinaryTree(){
        Distory(_root);
    }

private:
    BinaryTreeNode* _root;
};

void Test(){
    //int arr[] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#', 8, '#', '#'};
    //int arr[] = {1,2,'#',3,'#','#',4,5,'#',6,'#','#', 8, '#', '#'};
    //int arr[] = {1,2,'#','#','#'};
    int arr[] = {5,2,1,'#','#',4,3,'#','#','#',7,'#',9,'#','#'};
    BinaryTree bt(arr, '#') ;
    bt.PrevOrder();
    //bt.PrevOrderNoR();
    //bt.InOrderNoR();
    //bt.PostOrderNoR();
    //bt.LevelOrder();
    //
    //cout << bt.Height() << endl;
    //
    //cout << bt.LeafNode() << endl;
    //
    //cout << bt.KNode(2) << endl;
    //
    //BinaryTreeNode* tmp = new BinaryTreeNode(10);
    //cout << bt.InBinaryTree(tmp) << endl;
    //cout << bt.InBinaryTreeNoR(tmp) << endl;
    //
    //BinaryTreeNode* node1 = new BinaryTreeNode(2);
    //BinaryTreeNode* node2 = new BinaryTreeNode(4);
    //cout << bt.LestCommonAncestor(node1, node2)->_val << endl;
    //
    //cout << bt.Isbalanced() << endl;
    //cout << bt.FarthestNode() << endl;
    //
    //string Prev("123456");
    //string In("324165");
    ////string Prev("1234");
    ////string In("2143");
    //bt.RebuildTree(Prev, In);
    //bt.PrevOrder();
    //bt.InOrderNoR();
    //bt.PostOrderNoR();
    //
    //cout << bt.IsCompleteBinaryTree() << endl;
    //
    //bt.InOrderNoR();
    //bt.Mirror();
    //bt.InOrderNoR();
    //
    //bt.TreeToList();
    //bt.PrintList();
    //
}

int main(){
    Test();
    return 0;
}
