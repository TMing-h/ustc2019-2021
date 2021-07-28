#include "RBTree.h"

//对于出现同名函数，请参考以下关于函数重载的定义理解
//函数重载是一种特殊情况，C++允许在同一作用域中声明几个类似的同名函数，这些同名函数的形参列表（参数个数，类型，顺序）必须不同，常用来处理实现功能类似数据类型不同的问题。


/*
 * 构造函数
 */

RBTree ::RBTree() :mRoot(NULL)
{
    mRoot = NULL;
}

/*
 * 析构函数
 */

RBTree ::~RBTree()
{
    destroy();
}

/*
 * 前序遍历"红黑树"
 */
void RBTree ::preOrder(RBTNode * tree) const
{
    if (tree != NULL)
    {
        cout << tree->index << " " << tree->mac << endl;
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

void RBTree ::preOrder()
{
    preOrder(mRoot);
}



/*
 * 中序遍历"红黑树"
 */
void RBTree ::inOrder(RBTNode * tree) const
{
    if (tree != NULL)
    {
        inOrder(tree->left);
        cout << tree->index << " " << tree->mac << endl;
        inOrder(tree->right);
    }
}


void RBTree ::inOrder()
{
    inOrder(mRoot);
}

/*
 * 后序遍历"红黑树"
 */

void RBTree ::postOrder(RBTNode * tree) const
{
    if (tree != NULL)
    {
        postOrder(tree->left);
        postOrder(tree->right);
        cout << tree->index << " " << tree->mac;
    }
}


void RBTree ::postOrder()
{
    postOrder(mRoot);
}

/*
 * (递归实现)查找"红黑树x"中键值为index的节点
 */
RBTNode * RBTree ::search(RBTNode * x, int index) const
{
    if(x == NULL){
        //cout << index << "无记录" << endl;
        return x;
    }
    if(x->index == index){
        //cout << index << "的mac地址为：" << x->mac << endl;
        return x;
    }
    if(index < x->index)
        return search(x->left, index);
    else
        return search(x->right, index);
}


RBTNode * RBTree ::search(int index)
{
    RBTNode* x = search(mRoot, index);
    return x;
}


/*
 * 对红黑树的节点(x)进行左旋转
 *
 * 左旋示意图(对节点x进行左旋)：
 *      px                              px
 *     /                               /
 *    x                               y
 *   /  \      --(左旋)-->           / \                #
 *  lx   y                          x  ry
 *     /   \                       /  \
 *    ly   ry                     lx  ly
 *
 *
 */

void RBTree ::leftRotate(RBTNode *& root, RBTNode * x)
{
    RBTNode* y = x->right;
    x->right = y->left;
    if(y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if(x->parent == NULL)
        root = y;
    else if(x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

/*
 * 对红黑树的节点(y)进行右旋转
 *
 * 右旋示意图(对节点y进行左旋)：
 *            py                               py
 *           /                                /
 *          y                                x
 *         /  \      --(右旋)-->            /  \                     #
 *        x   ry                           lx   y
 *       / \                                   / \                   #
 *      lx  rx                                rx  ry
 *
 */

void RBTree ::rightRotate(RBTNode *& root, RBTNode * y)
{
    RBTNode* x = y->left;
    y->left = x->right;
    if(x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if(y->parent == NULL)
        root = x;
    else if(y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

/*
 * 红黑树插入修正函数
 *
 * 在向红黑树中插入节点之后(失去*衡)，再调用该函数；
 * 目的是将它重新塑造成一颗红黑树。
 *
 * 参数说明：
 *     root 红黑树的根
 *     node 插入的结点        // 对应《算法导论》中的z
 */

void RBTree ::insertFixUp(RBTNode *& root, RBTNode * node)
{
    RBTNode* y;
    // 起初运行的时候在while处程序崩掉了，然后意识到插入第一个结点为根节点
    // 而根据insert函数，我们把根节点的parent设置为了NULL，而NULL显然是不能访问color域的
    // 所以在取color前先判断node->parent是否为NULL
    while(node != NULL && node->parent != NULL && node->parent->color == RED){
        if(node->parent == node->parent->parent->left){ // case 1-3
            y = node->parent->parent->right; // 叔叔结点
            // 此处与上述同理，因为没有声明Nil结点涂黑，所以y==NULL就认为是黑色结点
            // 若不先进行y!=NULL的判断，程序会出错
            if(y != NULL && y->color == RED){ // case 1
                node->parent->color = BLACK;
                y->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
                continue;
            }
            else if(node == node->parent->right){ // case 2
                node = node->parent;
                leftRotate(root, node);
            }
            // 如果不是case1 or case 2则直接执行以下代码即case3
            // 或者是case2转换成case3后执行
            node->parent->color = BLACK;
            node->parent->parent->color = RED;
            rightRotate(root, node->parent->parent);
        }
        else{ // case 4-6
            y = node->parent->parent->left; // 叔叔结点
            if(y != NULL && y->color == RED){ // case 4
                node->parent->color = BLACK;
                y->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
                continue;
            }
            else if(node == node->parent->left){ // case 5
                node = node->parent;
                rightRotate(root, node);
            }
            // 如果不是case4 or case 5则直接执行以下代码即case6
            // 或者是case5转换成case6后执行
            node->parent->color = BLACK;
            node->parent->parent->color = RED;
            leftRotate(root, node->parent->parent);
        }
    }
    root->color = BLACK;
}

/*
 * 将结点插入到红黑树中
 *
 * 参数说明：
 *     root 红黑树的根结点
 *     node 插入的结点        // 对应《算法导论》中的node
 */

void RBTree ::insert(RBTNode *& root, RBTNode * node)
{
    // 插入
    RBTNode* y = NULL;
    RBTNode* x = root;
    while(x != NULL){
        y = x; // y指向待插入结点的父结点
        if(node->index < x->index)
            x = x->left;
        else
            x = x->right;
    }
    node->parent = y;
    if(y == NULL)
        root = node;
    else if(node->index < y->index)
        y->left = node;
    else
        y->right = node;
    node->left = NULL;
    node->right = NULL;
    node->color = RED; // 涂红
    insertFixUp(root, node);
}

/*
 * 将结点(index为节点键值)插入到红黑树中
 *
 * 参数说明：
 *     tree 红黑树的根结点
 *     index 插入结点的键值
 */

void RBTree::insert(int index, string mac)
{
    RBTNode * z = NULL;

    // 如果新建结点失败，则返回。【这里提高了一种新建结点的方法】
    if ((z = new RBTNode (index, mac, BLACK, NULL, NULL, NULL)) == NULL)
        return;

    insert(mRoot, z);
}

/*
 * 红黑树删除修正函数
 *
 * 在从红黑树中删除插入节点之后(红黑树失去平衡)，再调用该函数；
 * 目的是将它重新塑造成一颗红黑树。
 *
 * 参数说明：
 *     root 红黑树的根
 *     node 待修正的节点
 */

void RBTree ::removeFixUp(RBTNode *& root, RBTNode * node, RBTNode * parent)
{
    RBTNode* w = NULL;
    while(node != NULL && node != root && node->color == BLACK){
        if(node == node->parent->left){ // case 1-4
            w = node->parent->right; // node的兄弟
            if(w != NULL && w->color == RED){ // case 1
                w->color = BLACK;
                node->parent->color = RED;
                leftRotate(root, node->parent);
                w = node->parent->right;
            }
            // 要么w为黑，要么w为红，经过调整后为黑，执行下面代码
            if(w != NULL && (w->left == NULL || w->left->color == BLACK) && (w->right == NULL || w->right->color == BLACK)){ // case 2
                if(w != NULL)
                    w->color = RED;
                node = node->parent;
                continue;
            }
            else if(w != NULL && (w->right == NULL || w->right->color == BLACK)){ // case 3
                w->left->color = BLACK;
                w->color = RED;
                rightRotate(root, w);
                w = node->parent->right;
            }
            // case4 或者是 case1 or case3转换为case4后执行以下代码
            if(w != NULL)
                w->color = node->parent->color;
            node->parent->color = BLACK;
            if(w != NULL && w->right != NULL)
                w->right->color = BLACK;
            leftRotate(root, node->parent);
            node = root;
        }
        else{ // case 5-8
            if(node == node->parent->right){ // case 5-8
                w = node->parent->left; // node的兄弟
                if(w != NULL && w->color == RED){ // case 5
                    w->color = BLACK;
                    node->parent->color = RED;
                    rightRotate(root, node->parent);
                    w = node->parent->left;
                }
                // 要么w为黑，要么w为红，经过调整后为黑，执行下面代码
                if(w != NULL && (w->left == NULL || w->left->color == BLACK) && (w->right == NULL || w->right->color == BLACK)){ // case 6
                    if(w != NULL)
                        w->color = RED;
                    node = node->parent;
                    continue;
                }
                else if(w != NULL && (w->left == NULL || w->left->color == BLACK)){ // case 7
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = node->parent->left;
                }
                // case8 或者是 case5 or case7转换为case8后执行以下代码
                if(w != NULL)
                    w->color = node->parent->color;
                node->parent->color = BLACK;
                if(w != NULL && w->left != NULL)
                    w->left->color = BLACK;
                rightRotate(root, node->parent);
                node = root;
            }
        }
    }
    if(node != NULL)
        node->color = BLACK;
}

/*
 * 删除结点(node)，并返回被删除的结点
 *
 * 参数说明：
 *     root 红黑树的根结点
 *     node 删除的结点
 */

void RBTree ::transplant(RBTNode *& root, RBTNode *u, RBTNode *v){
    // 只有一个孩子 或 没有孩子的指针操作
    if(v == NULL){
        if(u->parent == NULL)
            root = NULL;
        else if(u == u->parent->left)
            u->parent->left = NULL;
        else
            u->parent->right = NULL;
    }
    else{
        if(u->parent == NULL)
            root = v;
        else if(u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
   }
}
RBTNode * RBTree ::tree_minimal(RBTNode* x){
    while(x->left != NULL)
        x = x->left;
    return x;
}
void RBTree ::remove(RBTNode *& root, RBTNode * node)
{
    RBTNode* y = node;
    RBTNode* x = NULL;
    int y_ori_color = y->color;
    if(node->left == NULL){
        x = node->right;
        transplant(root, node, node->right);
    }
    else if(node->right == NULL){
        x = node->left;
        transplant(root, node, node->left);
    }
    // 上面处理了只有一个孩子及没有孩子的情况（在transplant中），其中若没有孩子则x为NULL
    // 下面处理有两个孩子的情况——找后继
    else{
        y = tree_minimal(node->right); // y是node的后继元素
        y_ori_color = y->color;
        x = y->right;
        if(x != NULL && y->parent == node)
            x->parent = y;
        else if(x != NULL){
            transplant(root, y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        else;
        transplant(root, node, y);
        y->left = node->left;
        y->left->parent = y;
        y->color = node->color;
    }
    // 如果删除的是黑结点，则需要进行调整
    if(y_ori_color == BLACK)
        removeFixUp(root, x, NULL); // y是真正删除的结点，x是其右孩子（可能为空）
}

/*
 * 删除红黑树中键值为index的节点
 *
 * 参数说明：
 *     tree 红黑树的根结点
 */

void RBTree ::remove(int index)
{
    // 查找index对应的节点(node)，找到的话就删除该节点（调用前一个remove函数）
    RBTNode *x = search(index);
    if(x != NULL){
        cout << index << "的mac地址为：" << x->mac << endl;
        remove(mRoot, x);
    }
    else
        cout << index << "无记录" << endl;

}

/*
 * 销毁红黑树
 */

void RBTree ::destroy(RBTNode *& tree)
{
    if (tree == NULL)
        return;

    if (tree->left != NULL)
        return destroy(tree->left);
    if (tree->right != NULL)
        return destroy(tree->right);

    delete tree;
    tree = NULL;
}


void RBTree ::destroy()
{
    destroy(mRoot);
}

/*
 * 打印"二叉查找树"
 *
 * index       -- 节点的键值
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */

void RBTree ::print(RBTNode * tree, int index, int direction)
{
    if (tree != NULL)
    {
        if (direction == 0)    // tree是根节点
            cout << setw(2) << tree->index << "(B) is root" << endl;
        else                // tree是分支节点
            cout << setw(2) << tree->index << (rb_is_red(tree) ? "(R)" : "(B)") << " is " << setw(2) << index << "'s " << setw(12) << (direction == 1 ? "right child" : "left child") << endl;

        print(tree->left, tree->index, -1);
        print(tree->right, tree->index, 1);
    }
}


void RBTree ::print()
{
    if (mRoot != NULL)
        print(mRoot, mRoot->index, 0);
}


