/*В одной военной части решили построить в одну шеренгу по росту. Т.к. часть была далеко не образцовая, 
то солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги. 
Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, 
а в конце – самые низкие. За расстановку солдат отвечал прапорщик, который заметил интересную особенность – все солдаты в части разного роста. 
Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, а именно для каждого приходящего солдата указывать, 
перед каким солдатом в строе он должен становится. Требуемая скорость выполнения команды - O(log n).*/


#include<iostream>
#include<algorithm>
#include<queue>

struct CNode
{
    int key;
    int height;
    int treeSize;
    CNode* left;
    CNode* right;
    CNode(int value)
    {
        key = value;
        height = 1;
        treeSize = 1;
        left = nullptr;
        right = nullptr;
    }
};

int Height(CNode* node) //высота дерева с данным корнем
{
    if (node == nullptr)
        return 0;
    else
        return node -> height;
}

int TreeSize(CNode* node) //количество вершин в дереве с данным корнем
{
    if (node == nullptr)
        return 0;
    else
        return node -> treeSize;
}

int Diff(CNode* node) //разница между высотами правого и левого поддеревьев
{
    return Height(node -> right) - Height(node -> left);
}

CNode* LeftRotation(CNode* node) // левый поворот
{
    CNode* newRoot = node -> right;
    node -> right = newRoot -> left;
    newRoot -> left = node;
    node -> height = std::max(Height(node -> right), Height(node -> left));
    newRoot -> height = std::max(Height(newRoot -> right), Height(newRoot -> left));
    newRoot -> treeSize = node -> treeSize;
    node -> treeSize = TreeSize(node -> right) + TreeSize(node -> left) + 1;
    return newRoot;
}

CNode* RightRotation(CNode* node) // правый поворот
{
    CNode* newRoot = node -> left;
    node -> left = newRoot -> right;
    newRoot -> right = node;
    node -> height = std::max(Height(node -> right), Height(node -> left));
    newRoot -> height = std::max(Height(newRoot -> right), Height(newRoot -> left));
    newRoot -> treeSize = node -> treeSize;
    node -> treeSize = TreeSize(node -> right) + TreeSize(node -> left) + 1;
    return newRoot;
}

CNode* Balance(CNode* node) // балансировка
{
    if (Diff(node) == 2)
    {
        if (Diff(node -> right) < 0)
            node -> right = RightRotation(node -> right);
        return LeftRotation(node);
    }
    if (Diff(node) == -2)
    {
        if (Diff(node -> left) < 0)
            node -> left = LeftRotation(node -> left);
        return RightRotation(node);
    }
    return node;
}

CNode* Insert(CNode* root, int value) // вставка элемента
{
    if (root == nullptr)
    {
        CNode* newRoot = new CNode(value);
        return newRoot;
    }
    if (root -> key > value)
    {
        root -> left = Insert(root -> left, value);
    }
    else
    {
        root -> right = Insert(root -> right, value);
    }
    (root -> treeSize)++;                                                  //обновляем высоту и размер дерева
    root -> height = std::max(Height(root -> right), Height(root -> left));
    return Balance(root);
}

CNode* DeleteMin(CNode* root) //удаление минимального элемента
{
    if (root -> left == nullptr)
    {
        return root -> right;
    }
    root -> left = DeleteMin(root -> left);
    root -> height = std::max(Height(root -> right), Height(root -> left));
    (root -> treeSize)--;
    return Balance(root);
}

CNode* Delete(CNode* root, int value) //удаление вершины по ключу
{
    if (root -> key == value)
    {
        CNode* l = root -> left;
        CNode* r = root -> right;
        CNode* minimum = r;
        delete root;
        if (minimum == nullptr)
            return l;
        while (minimum -> left != nullptr)
        {
            minimum = minimum -> left;
        }
        minimum -> right = DeleteMin(r);
        minimum -> left = l;
        minimum -> height = std::max(Height(minimum -> right), Height(minimum -> left));
        minimum -> treeSize = TreeSize(minimum -> right) + TreeSize(minimum -> left) + 1;
        return Balance(minimum);

    }
    else if (root -> key > value)
    {
        root -> left = Delete(root -> left, value);
    }
    else
    {
        root -> right = Delete(root -> right, value);
    }
    (root -> treeSize)--;
    root -> height = std::max(Height(root -> right), Height(root -> left));
    return Balance(root);
}

int Number(CNode* root, int value) //номер вершины с указанным ключом 
{
    int n = 0;
    while (root -> key != value)
    {
        if (root -> key > value)
        {
            root = root -> left;
        }
        else
        {
            n += TreeSize(root -> left) + 1;
            root = root -> right;
        }
    }
    n += TreeSize(root -> left);
    return n;
}

CNode* KStat(CNode* root, int k) //k-ый по порядку элемент
{
    int n = TreeSize(root -> left);
    if (k == n)
        return root;
    else if (k < n)
        return KStat(root -> left, k);
    else
        return KStat(root -> right, k - n - 1);
}

void Destroy(CNode* root)
{
    if (root != nullptr)
    {
        Destroy(root -> right);
        Destroy(root -> left);
        delete root;
    }
}

int main()
{
    int N, x, y;
    std::cin >> N;
    CNode* root = nullptr;
    int value;
    while (N > 0)
    {
        N--;
        std::cin >> x >> y;
        if (x == 1)
        {
            root = Insert(root, y);
            std::cout << TreeSize(root) - 1 - Number(root, y) << std::endl;
        }
        else
        {
            value = KStat(root, TreeSize(root) - 1 - y) -> key;
            root = Delete(root, value);
        }
    }
    Destroy(root);
    return 0;
}


