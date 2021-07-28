#include "RBTree.h"

//���ڳ���ͬ����������ο����¹��ں������صĶ������
//����������һ�����������C++������ͬһ�������������������Ƶ�ͬ����������Щͬ���������β��б��������������ͣ�˳�򣩱��벻ͬ������������ʵ�ֹ��������������Ͳ�ͬ�����⡣


/*
 * ���캯��
 */

RBTree ::RBTree() :mRoot(NULL)
{
    mRoot = NULL;
}

/*
 * ��������
 */

RBTree ::~RBTree()
{
    destroy();
}

/*
 * ǰ�����"�����"
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
 * �������"�����"
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
 * �������"�����"
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
 * (�ݹ�ʵ��)����"�����x"�м�ֵΪindex�Ľڵ�
 */
RBTNode * RBTree ::search(RBTNode * x, int index) const
{
    if(x == NULL){
        //cout << index << "�޼�¼" << endl;
        return x;
    }
    if(x->index == index){
        //cout << index << "��mac��ַΪ��" << x->mac << endl;
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
 * �Ժ�����Ľڵ�(x)��������ת
 *
 * ����ʾ��ͼ(�Խڵ�x��������)��
 *      px                              px
 *     /                               /
 *    x                               y
 *   /  \      --(����)-->           / \                #
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
 * �Ժ�����Ľڵ�(y)��������ת
 *
 * ����ʾ��ͼ(�Խڵ�y��������)��
 *            py                               py
 *           /                                /
 *          y                                x
 *         /  \      --(����)-->            /  \                     #
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
 * �����������������
 *
 * ���������в���ڵ�֮��(ʧȥ*��)���ٵ��øú�����
 * Ŀ���ǽ������������һ�ź������
 *
 * ����˵����
 *     root ������ĸ�
 *     node ����Ľ��        // ��Ӧ���㷨���ۡ��е�z
 */

void RBTree ::insertFixUp(RBTNode *& root, RBTNode * node)
{
    RBTNode* y;
    // ������е�ʱ����while����������ˣ�Ȼ����ʶ�������һ�����Ϊ���ڵ�
    // ������insert���������ǰѸ��ڵ��parent����Ϊ��NULL����NULL��Ȼ�ǲ��ܷ���color���
    // ������ȡcolorǰ���ж�node->parent�Ƿ�ΪNULL
    while(node != NULL && node->parent != NULL && node->parent->color == RED){
        if(node->parent == node->parent->parent->left){ // case 1-3
            y = node->parent->parent->right; // ������
            // �˴�������ͬ����Ϊû������Nil���Ϳ�ڣ�����y==NULL����Ϊ�Ǻ�ɫ���
            // �����Ƚ���y!=NULL���жϣ���������
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
            // �������case1 or case 2��ֱ��ִ�����´��뼴case3
            // ������case2ת����case3��ִ��
            node->parent->color = BLACK;
            node->parent->parent->color = RED;
            rightRotate(root, node->parent->parent);
        }
        else{ // case 4-6
            y = node->parent->parent->left; // ������
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
            // �������case4 or case 5��ֱ��ִ�����´��뼴case6
            // ������case5ת����case6��ִ��
            node->parent->color = BLACK;
            node->parent->parent->color = RED;
            leftRotate(root, node->parent->parent);
        }
    }
    root->color = BLACK;
}

/*
 * �������뵽�������
 *
 * ����˵����
 *     root ������ĸ����
 *     node ����Ľ��        // ��Ӧ���㷨���ۡ��е�node
 */

void RBTree ::insert(RBTNode *& root, RBTNode * node)
{
    // ����
    RBTNode* y = NULL;
    RBTNode* x = root;
    while(x != NULL){
        y = x; // yָ���������ĸ����
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
    node->color = RED; // Ϳ��
    insertFixUp(root, node);
}

/*
 * �����(indexΪ�ڵ��ֵ)���뵽�������
 *
 * ����˵����
 *     tree ������ĸ����
 *     index ������ļ�ֵ
 */

void RBTree::insert(int index, string mac)
{
    RBTNode * z = NULL;

    // ����½����ʧ�ܣ��򷵻ء������������һ���½����ķ�����
    if ((z = new RBTNode (index, mac, BLACK, NULL, NULL, NULL)) == NULL)
        return;

    insert(mRoot, z);
}

/*
 * �����ɾ����������
 *
 * �ڴӺ������ɾ������ڵ�֮��(�����ʧȥƽ��)���ٵ��øú�����
 * Ŀ���ǽ������������һ�ź������
 *
 * ����˵����
 *     root ������ĸ�
 *     node �������Ľڵ�
 */

void RBTree ::removeFixUp(RBTNode *& root, RBTNode * node, RBTNode * parent)
{
    RBTNode* w = NULL;
    while(node != NULL && node != root && node->color == BLACK){
        if(node == node->parent->left){ // case 1-4
            w = node->parent->right; // node���ֵ�
            if(w != NULL && w->color == RED){ // case 1
                w->color = BLACK;
                node->parent->color = RED;
                leftRotate(root, node->parent);
                w = node->parent->right;
            }
            // ҪôwΪ�ڣ�ҪôwΪ�죬����������Ϊ�ڣ�ִ���������
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
            // case4 ������ case1 or case3ת��Ϊcase4��ִ�����´���
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
                w = node->parent->left; // node���ֵ�
                if(w != NULL && w->color == RED){ // case 5
                    w->color = BLACK;
                    node->parent->color = RED;
                    rightRotate(root, node->parent);
                    w = node->parent->left;
                }
                // ҪôwΪ�ڣ�ҪôwΪ�죬����������Ϊ�ڣ�ִ���������
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
                // case8 ������ case5 or case7ת��Ϊcase8��ִ�����´���
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
 * ɾ�����(node)�������ر�ɾ���Ľ��
 *
 * ����˵����
 *     root ������ĸ����
 *     node ɾ���Ľ��
 */

void RBTree ::transplant(RBTNode *& root, RBTNode *u, RBTNode *v){
    // ֻ��һ������ �� û�к��ӵ�ָ�����
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
    // ���洦����ֻ��һ�����Ӽ�û�к��ӵ��������transplant�У���������û�к�����xΪNULL
    // ���洦�����������ӵ���������Һ��
    else{
        y = tree_minimal(node->right); // y��node�ĺ��Ԫ��
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
    // ���ɾ�����Ǻڽ�㣬����Ҫ���е���
    if(y_ori_color == BLACK)
        removeFixUp(root, x, NULL); // y������ɾ���Ľ�㣬x�����Һ��ӣ�����Ϊ�գ�
}

/*
 * ɾ��������м�ֵΪindex�Ľڵ�
 *
 * ����˵����
 *     tree ������ĸ����
 */

void RBTree ::remove(int index)
{
    // ����index��Ӧ�Ľڵ�(node)���ҵ��Ļ���ɾ���ýڵ㣨����ǰһ��remove������
    RBTNode *x = search(index);
    if(x != NULL){
        cout << index << "��mac��ַΪ��" << x->mac << endl;
        remove(mRoot, x);
    }
    else
        cout << index << "�޼�¼" << endl;

}

/*
 * ���ٺ����
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
 * ��ӡ"���������"
 *
 * index       -- �ڵ�ļ�ֵ
 * direction  --  0����ʾ�ýڵ��Ǹ��ڵ�;
 *               -1����ʾ�ýڵ������ĸ���������;
 *                1����ʾ�ýڵ������ĸ������Һ��ӡ�
 */

void RBTree ::print(RBTNode * tree, int index, int direction)
{
    if (tree != NULL)
    {
        if (direction == 0)    // tree�Ǹ��ڵ�
            cout << setw(2) << tree->index << "(B) is root" << endl;
        else                // tree�Ƿ�֧�ڵ�
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


