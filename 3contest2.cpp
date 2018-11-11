/*Дано число N < 106 и последовательность пар целых чисел из [-231, 231].
Построить декартово дерево из N узлов, характеризующихся парами чисел (Xi, Yi). 
Каждая пара чисел (Xi, Yi) определяет ключ Xi и приоритет Yi в декартовом дереве. 
Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции: 
При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом. Затем разбейте найденное поддерево по ключу x так,
чтобы в первом поддереве все ключи меньше x, а во втором больше или равны x. 
Получившиеся два дерева сделайте дочерними для нового узла (x, y). Новый узел вставьте на место узла P. 
Построить также наивное дерево поиска по ключам Xi. Равные ключи добавляйте в правое поддерево. 
Вычислить количество узлов в самом широком слое декартового дерева и количество узлов в самом широком слое наивного дерева поиска.
Вывести их разницу. Разница может быть отрицательна.*/

#include<iostream>
#include<queue>

struct CNode
{
    int key;
    int priority;
    CNode* left;
    CNode* right;
    CNode(int x, int y)
    {
        key = x;
        priority = y;
        left = nullptr;
        right = nullptr;
    }
    CNode(int value)
    {
        key = value;
        priority = 0;
        left = nullptr;
        right = nullptr;
    }
};

void Split(CNode* currentNode, int Key, CNode*& left, CNode*& right) //разрезание дерева по ключу
{
    if (currentNode == nullptr)
    {
        left = nullptr;
        right = nullptr;
    }
    else if (currentNode -> key <= Key)
    {
        Split(currentNode -> right, Key, currentNode -> right, right);
        left = currentNode;
    }
    else
    {
        Split(currentNode -> left, Key, left, currentNode -> left);
        right = currentNode;
    }
}

CNode* Insert2(CNode* root, int x, int y) //добавление вершины в декартово дерево
{
    CNode* node = new CNode(x, y);
    while (root -> priority >= node -> priority)
    {
        if (root -> key > node -> key)
        {
            if (root -> left != nullptr)
                root = root -> left;
            else
            {
                root -> left = node;
                return nullptr;
            }
        }
        else
        {
            if (root -> right != nullptr)
                root = root -> right;
            else
            {
                root -> right = node;
                return nullptr;
            }
        }
    }
    std::swap(*root, *node);
    Split(node, root -> key, root -> left, root -> right);
    return node;
}

void Insert1(CNode* root, int value) //добавление вершины в наивное дерево
{
    bool stop = false;
    while(!stop)
    {
        if (root -> key > value)
        {
            if (root -> left != nullptr)
                root = root -> left;
            else
            {
                root -> left = new CNode(value);
                stop = true;
            }
        }
        else
        {
            if (root -> right != nullptr)
                root = root -> right;
            else
            {
                root -> right = new CNode(value);
                stop = true;
            }
        }
    }
}

int MaxWidth(CNode* root) //максимальная ширина дерева
{
    std::queue <CNode> Queue;
    Queue.push(*root);
    CNode node = *root;
    int current_width = 1;
    int max_width = 1;
    int n;
    while (!Queue.empty())
    {
        n = current_width;
        current_width = 0;
        while (n > 0)
        {
            n--;
            node = Queue.front();
            Queue.pop();
            if (node.right != nullptr)
            {
                Queue.push(*node.right);
                ++current_width;
            }
            if (node.left != nullptr)
            {
                Queue.push(*node.left);
                ++current_width;
            }
        }
        if (current_width > max_width)
            max_width = current_width;
    }
    return max_width;
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
    std::cin >> N >> x >> y;
    CNode* root1 = new CNode(x);
    CNode* root2 = new CNode(x, y);
    for (int i = 1; i < N; ++i)
    {
        std::cin >> x >> y;
        Insert1(root1, x);        //построение двух деревьев: наивного(приоритет равен 0) и декартова
        Insert2(root2, x, y);
    }
    std::cout << MaxWidth(root2) - MaxWidth(root1);
    Destroy(root1);
    Destroy(root2);
    return 0;
}

