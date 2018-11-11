/*Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки. 
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; 
иначе в левое поддерево root. Выведите элементы в порядке pre-order (сверху вниз). Рекурсия запрещена.*/

#include<iostream>
#include<stack>

struct CBinaryNode
{
    int data;
    CBinaryNode* left;
    CBinaryNode* right;
    CBinaryNode(int value)
    {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

void Insert(CBinaryNode* root, int value)
{
    bool stop = false;
    while(!stop)
    {
        if (root -> data > value)
        {
            if (root -> left != nullptr)
                root = root -> left;
            else
            {
                root -> left = new CBinaryNode(value);
                stop = true;
            }
        }
        else
        {
            if (root -> right != nullptr)
                root = root -> right;
            else
            {
                root -> right = new CBinaryNode(value);
                stop = true;
            }
        }
    }
}

int main()
{
    int N, elem;
    std::cin >> N >> elem;
    CBinaryNode* root = new CBinaryNode(elem);
    for (int i = 1; i < N; ++i)
    {
        std::cin >> elem;
        Insert(root, elem);
    }
    std::stack <CBinaryNode> Stack;
    Stack.push(*root);
    CBinaryNode node = *root;
    while(!Stack.empty())
    {
        node = Stack.top();
        Stack.pop();
        std::cout << node.data << " ";
        if (node.right != nullptr)
            Stack.push(*node.right);
        if (node.left != nullptr)
            Stack.push(*node.left);
    }
    delete root;
    return 0;
}
