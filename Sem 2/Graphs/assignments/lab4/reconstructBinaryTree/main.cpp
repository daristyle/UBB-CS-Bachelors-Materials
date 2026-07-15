#include "../Graph/Graph.h"
#include <iostream>
#include <map>
#include <vector>

using std::vector, std::map;

struct TreeNode{
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int _value, TreeNode* _left = nullptr, TreeNode* _right = nullptr): value(_value), left(_left), right(_right){}
};

TreeNode* buildTreeFromPreorderInorderRec(int bPre, int bIn, int eIn,
                                        const vector<int>& preorder, const map<int, int>& posInorder){
    if(bIn > eIn){
        return nullptr;
    }
    int n = preorder[bPre], pos = posInorder.at(n);
    int bPreLeft = bPre + 1, bInLeft = bIn, eInLeft = pos - 1;
    int bPreRight = bPre + pos - bIn + 1, bInRight = pos + 1, eInRight = eIn;

    return new TreeNode{n,
                     buildTreeFromPreorderInorderRec(bPreLeft, bInLeft, eInLeft, preorder, posInorder),
                    buildTreeFromPreorderInorderRec(bPreRight, bInRight, eInRight, preorder, posInorder)};
}

TreeNode* buildTreeFromPreorderInorder(const vector<int>& preorder, const vector<int>& inorder){
    int n = preorder.size();
    map<int, int> posInorder;
    for(int i = 0; i < n; ++i){
        posInorder[inorder[i]] = i;
    }

    return buildTreeFromPreorderInorderRec(0, 0, n - 1, preorder, posInorder);
}

TreeNode* buildTreeFromPostorderInorderRec(int ePost, int bIn, int eIn,
                                        const vector<int>& postorder, const map<int, int>& posInorder){
    if(bIn > eIn){
        return nullptr;
    }
    int n = postorder[ePost], pos = posInorder.at(n);
    int ePostLeft = ePost - eIn + pos - 1, bInLeft = bIn, eInLeft = pos - 1;
    int ePostRight = ePost - 1, bInRight = pos + 1, eInRight = eIn;

    return new TreeNode{n,
                     buildTreeFromPostorderInorderRec(ePostLeft, bInLeft, eInLeft, postorder, posInorder),
                    buildTreeFromPostorderInorderRec(ePostRight, bInRight, eInRight, postorder, posInorder)};
}

TreeNode* buildTreeFromPostorderInorder(const vector<int>& postorder, const vector<int>& inorder){
    int n = postorder.size();
    map<int, int> posInorder;
    for(int i = 0; i < n; ++i){
        posInorder[inorder[i]] = i;
    }

    return buildTreeFromPostorderInorderRec(n - 1, 0, n - 1, postorder, posInorder);
}

TreeNode* buildTreeFromPreorderPostorderRec(int bPre, int ePre, int bPost, int ePost,
                                        const vector<int>& preorder, const map<int, int>& posPostorder){
    if(bPre > ePre){
        return nullptr;
    }
    if(bPre == ePre){
        return new TreeNode{preorder[bPre]};
    }

    int n = preorder[bPre], left = preorder[bPre + 1], pos = posPostorder.at(left);
    int bPreLeft = bPre + 1, ePreLeft = bPre + pos - bPost + 1, bPostLeft = bPost, ePostLeft = pos;
    int bPreRight = ePreLeft + 1, ePreRight = ePre, bPostRight = pos + 1, ePostRight = ePost - 1;

    return new TreeNode{n,
                     buildTreeFromPreorderPostorderRec(bPreLeft, ePreLeft,bPostLeft, ePostLeft, preorder, posPostorder),
                    buildTreeFromPreorderPostorderRec(bPreRight, ePreRight,bPostRight, ePostRight, preorder, posPostorder)};
}

TreeNode* buildTreeFromPreorderPostorder(const vector<int>& preorder, const vector<int>& postorder){
    int n = preorder.size();
    map<int, int> posPostorder;
    for(int i = 0; i < n; ++i){
        posPostorder[postorder[i]] = i;
    }

    return buildTreeFromPreorderPostorderRec(0, n - 1, 0, n - 1, preorder, posPostorder);
}

void printTree(TreeNode* root, std::string indent, bool last, std::ostream& os){
    os << indent;
    if(last){
        os << "└────";
        indent += "     ";
    }else{
        os << "├────";
        indent += "│    ";
    }
    if(root != nullptr){
        os << root->value << std::endl;
        printTree(root->left, indent, false, os);
        printTree(root->right, indent, true, os);
    }else{
        os << "X" << std::endl;
    }
}

int main(){
    int type;
    std::cout << "1. Build Tree From Preorder Inorder" << std::endl;
    std::cout << "2. Build Tree From Postorder Inorder" << std::endl;
    std::cout << "3. Build Tree From Preorder Postorder" << std::endl;
    std::cout << "Enter type: ";
    std::cin >> type;
    TreeNode* root;
    int n;
    std::cout << "Enter number of nodes: ";
    std::cin >> n;
    if(type == 1){
        std::vector<int> preorder(n), inorder(n);
        std::cout << "Enter preorder: ";
        for(int i = 0; i < n; ++i){
            std::cin >> preorder[i];
        }
        std::cout << "Enter inorder: ";
        for(int i = 0; i < n; ++i){
            std::cin >> inorder[i];
        }

        root = buildTreeFromPreorderInorder(preorder, inorder);
    }else if(type == 2){
        std::vector<int> postorder(n), inorder(n);
        std::cout << "Enter postorder: ";
        for(int i = 0; i < n; ++i){
            std::cin >> postorder[i];
        }
        std::cout << "Enter inorder: ";
        for(int i = 0; i < n; ++i){
            std::cin >> inorder[i];
        }

        root = buildTreeFromPostorderInorder(postorder, inorder);
    }else if(type == 3){
        std::vector<int> preorder(n), postorder(n);
        std::cout << "Enter preorder: ";
        for(int i = 0; i < n; ++i){
            std::cin >> preorder[i];
        }
        std::cout << "Enter postorder: ";
        for(int i = 0; i < n; ++i){
            std::cin >> postorder[i];
        }

        root = buildTreeFromPreorderPostorder(preorder, postorder);
    }else{
        std::cout << "Invalid input" << std::endl;
        return 0;
    }

    printTree(root, "", true, std::cout);

    return 0;
}
/*
1
6
1 2 4 3 5 6
4 2 1 5 3 6


2
4
5 20 15 10
5 10 15 20


3
3
1 2 3
3 2 1


33
1 2 3
2 3 1
7
1 2 4 5 3 6 7
4 5 2 6 7 3 1
*/