#define _RB_TREE_H_
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include <time.h>
using namespace std;
template<class KEY, class U>
class RB_Tree
{
private:
	RB_Tree(const RB_Tree& input){}
	const RB_Tree& operator=(const RB_Tree& input){}
private:
	enum COLOR{ RED, BLACK };
	class RB_Node
	{
	public:
		RB_Node()
		{
			RB_COLOR = BLACK;
			right = NULL;
			left = NULL;
			parent = NULL;
		}
		COLOR RB_COLOR;
		RB_Node* right;
		RB_Node* left;
		RB_Node* parent;
		KEY key;
		U data;
	};
public:
	RB_Tree()
	{
		this->m_nullNode = new RB_Node();
		this->m_root = m_nullNode;
		this->m_nullNode->right = this->m_root;
		this->m_nullNode->left = this->m_root;
		this->m_nullNode->parent = this->m_root;
		this->m_nullNode->RB_COLOR = BLACK;
	}
	bool Empty()
	{
		if (this->m_root == this->m_nullNode)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//find node who's key equals to key,else find the insert point;
	RB_Node* find(KEY key)
	{
		RB_Node* index = m_root;
		while (index != m_nullNode)
		{
			if (key<index->key)
			{
				index = index->left;
			}
			else if (key>index->key)
			{
				index = index->right;
			}
			else
			{
				break;
			}
		}
		return index;
	}
	const U& RB_Tree<KEY, U>::query(const KEY& key)
	{
		RB_Node *p = find(key);
		if (p == NULL) 
		return NULL;
		else 
		return p->data ;
	}
	bool Insert(KEY key, U data)
	{
		RB_Node* insert_point = m_nullNode;
		RB_Node* index = m_root;
		while (index != m_nullNode)
		{
			insert_point = index;
			if (key<index->key)
			{
				index = index->left;
			}
			else if (key>index->key)
			{
				index = index->right;
			}
			else
			{
				return false;
			}
		}
		RB_Node* insert_node = new RB_Node();
		insert_node->key = key;
		insert_node->data = data;
		insert_node->RB_COLOR = RED;
		insert_node->right = m_nullNode;
		insert_node->left = m_nullNode;
		if (insert_point == m_nullNode) //empty tree
		{
			m_root = insert_node;
			m_root->parent = m_nullNode;
			m_nullNode->left = m_root;
			m_nullNode->right = m_root;
			m_nullNode->parent = m_root;
		}
		else
		{
			if (key<insert_point->key)
			{
				insert_point->left = insert_node;
			}
			else
			{
				insert_point->right = insert_node;
			}
			insert_node->parent = insert_point;
		}
		InsertFixUp(insert_node);
		return true;
	}
	void InsertFixUp(RB_Node* node)
	{
		while (node->parent->RB_COLOR == RED)
		{
			if (node->parent == node->parent->parent->left)
			{
				RB_Node* uncle = node->parent->parent->right;
				if (uncle->RB_COLOR == RED)
				{
					node->parent->RB_COLOR = BLACK;
					uncle->RB_COLOR = BLACK;
					node->parent->parent->RB_COLOR = RED;
					node = node->parent->parent;
				}
				else if (uncle->RB_COLOR == BLACK)
				{
					if (node == node->parent->right)
					{
						node = node->parent;
						RotateLeft(node);
					}
					node->parent->RB_COLOR = BLACK;
					node->parent->parent->RB_COLOR = RED;
					RotateRight(node->parent->parent);
				}
			}
			else
			{
				RB_Node* uncle = node->parent->parent->left;
				if (uncle->RB_COLOR == RED)
				{
					node->parent->RB_COLOR = BLACK;
					uncle->RB_COLOR = BLACK;
					uncle->parent->RB_COLOR = RED;
					node = node->parent->parent;
				}
				else if (uncle->RB_COLOR == BLACK)
				{
					if (node == node->parent->left)
					{
						node = node->parent;
						RotateRight(node);
					}
					else
					{
						node->parent->RB_COLOR = BLACK;
						node->parent->parent->RB_COLOR = RED;
						RotateLeft(node->parent->parent);
					}
				}
			}
		}
		m_root->RB_COLOR = BLACK;
	}
	bool RotateLeft(RB_Node* node)
	{
		if (node == m_nullNode || node->right == m_nullNode)
		{
			return false;//can't rotate
		}
		RB_Node* lower_right = node->right;
		lower_right->parent = node->parent;
		node->right = lower_right->left;
		if (lower_right->left != m_nullNode)
		{
			lower_right->left->parent = node;
		}
		if (node->parent == m_nullNode) //rotate node is root
		{
			m_root = lower_right;
			m_nullNode->left = m_root;
			m_nullNode->right = m_root;
			//m_nullNode->parent = m_root;
		}
		else
		{
			if (node == node->parent->left)
			{
				node->parent->left = lower_right;
			}
			else
			{
				node->parent->right = lower_right;
			}
		}
		node->parent = lower_right;
		lower_right->left = node;
		return true;
	}
	bool RotateRight(RB_Node* node)
	{
		if (node == m_nullNode || node->left == m_nullNode)
		{
			return false;//can't rotate
		}
		RB_Node* lower_left = node->left;
		node->left = lower_left->right;
		lower_left->parent = node->parent;
		if (lower_left->right != m_nullNode)
		{
			lower_left->right->parent = node;
		}
		if (node->parent == m_nullNode) //node is root
		{
			m_root = lower_left;
			m_nullNode->left = m_root;
			m_nullNode->right = m_root;
			//m_nullNode->parent = m_root;
		}
		else
		{
			if (node == node->parent->right)
			{
				node->parent->right = lower_left;
			}
			else
			{
				node->parent->left = lower_left;
			}
		}
		node->parent = lower_left;
		lower_left->right = node;
		return true;
	}
	bool Delete(KEY key)
	{
		RB_Node* delete_point = find(key);
		if (delete_point == m_nullNode)
		{
			return false;
		}
		if (delete_point->left != m_nullNode && delete_point->right != m_nullNode)
		{
			RB_Node* successor = InOrderSuccessor(delete_point);
			delete_point->data = successor->data;
			delete_point->key = successor->key;
			delete_point = successor;
		}
		RB_Node* delete_point_child;
		if (delete_point->right != m_nullNode)
		{
			delete_point_child = delete_point->right;
		}
		else if (delete_point->left != m_nullNode)
		{
			delete_point_child = delete_point->left;
		}
		else
		{
			delete_point_child = m_nullNode;
		}
		delete_point_child->parent = delete_point->parent;
		if (delete_point->parent == m_nullNode)//delete root node
		{
			m_root = delete_point_child;
			m_nullNode->parent = m_root;
			m_nullNode->left = m_root;
			m_nullNode->right = m_root;
		}
		else if (delete_point == delete_point->parent->right)
		{
			delete_point->parent->right = delete_point_child;
		}
		else
		{
			delete_point->parent->left = delete_point_child;
		}
		if (delete_point->RB_COLOR == BLACK && !(delete_point_child == m_nullNode && delete_point_child->parent == m_nullNode))
		{
			DeleteFixUp(delete_point_child);
		}
		delete delete_point;
		return true;
	}
	void DeleteFixUp(RB_Node* node)
	{
		while (node != m_root && node->RB_COLOR == BLACK)
		{
			if (node == node->parent->left)
			{
				RB_Node* brother = node->parent->right;
				if (brother->RB_COLOR == RED)
				{
					brother->RB_COLOR = BLACK;
					node->parent->RB_COLOR = RED;
					RotateLeft(node->parent);
				}
				else
				{
					if (brother->left->RB_COLOR == BLACK && brother->right->RB_COLOR == BLACK)
					{
						brother->RB_COLOR = RED;
						node = node->parent;
					}
					else if (brother->right->RB_COLOR == BLACK)//left red and right black
					{
						brother->RB_COLOR = RED;
						brother->left->RB_COLOR = BLACK;
						RotateRight(brother);
					}
					else if (brother->right->RB_COLOR == RED)
					{
						brother->RB_COLOR = node->parent->RB_COLOR;
						node->parent->RB_COLOR = BLACK;
						brother->right->RB_COLOR = BLACK;
						RotateLeft(node->parent);
						node = m_root;
					}
				}
			}
			else
			{
				RB_Node* brother = node->parent->left;
				if (brother->RB_COLOR == RED)
				{
					brother->RB_COLOR = BLACK;
					node->parent->RB_COLOR = RED;
					RotateRight(node->parent);
				}
				else
				{
					if (brother->left->RB_COLOR == BLACK && brother->right->RB_COLOR == BLACK)
					{
						brother->RB_COLOR = RED;
						node = node->parent;
					}
					else if (brother->left->RB_COLOR == BLACK)
					{
						brother->RB_COLOR = RED;
						brother->right->RB_COLOR = BLACK;
						RotateLeft(brother);
					}
					else if (brother->left->RB_COLOR == RED)
					{
						brother->RB_COLOR = node->parent->RB_COLOR;
						node->parent->RB_COLOR = BLACK;
						brother->left->RB_COLOR = BLACK;
						RotateRight(node->parent);
						node = m_root;
					}
				}
			}
		}
		m_nullNode->parent = m_root;
		node->RB_COLOR = BLACK;
	}
	inline RB_Node* InOrderPredecessor(RB_Node* node)
	{
		if (node == m_nullNode)                  //null node has no predecessor
		{
			return m_nullNode;
		}
		RB_Node* result = node->left;         //get node's left child
		while (result != m_nullNode)             //try to find node's left subtree's right most node
		{
			if (result->right != m_nullNode)
			{
				result = result->right;
			}
			else
			{
				break;
			}
		}                                     //after while loop result==null or result's right child is null
		if (result == m_nullNode)
		{
			RB_Node* index = node->parent;
			result = node;
			while (index != m_nullNode && result == index->left)
			{
				result = index;
				index = index->parent;
			}
			result = index;                  // first right parent or null
		}
		return result;
	}
	inline RB_Node* InOrderSuccessor(RB_Node* node)
	{
		if (node == m_nullNode)                 //null node has no successor
		{
			return m_nullNode;
		}
		RB_Node* result = node->right;        //get node's right node
		while (result != m_nullNode)            //try to find node's right subtree's left most node
		{
			if (result->left != m_nullNode)
			{
				result = result->left;
			}
			else
			{
				break;
			}
		}                                    //after while loop result==null or result's left child is null
		if (result == m_nullNode)
		{
			RB_Node* index = node->parent;
			result = node;
			while (index != m_nullNode && result == index->right)
			{
				result = index;
				index = index->parent;
			}
			result = index;                 //first parent's left or null
		}
		return result;
	}
	void InOrderTraverse()
	{   
		ofstream outfile;
		outfile.open(".\\word.txt");
		outfile.close();
		InOrderTraverse(m_root);
	}
	void InOrderTraverse(RB_Node* node)
	{
		if (node == m_nullNode)
		{
			return;
		}
		else
		{
			InOrderTraverse(node->left);
			ofstream outfile;
			outfile.open(".\\word.txt", ios::app);
			CStringA sa(node->key);
			CStringA sb(node->data);
			outfile << sa << " " << sb << endl;
			outfile.close();
			InOrderTraverse(node->right);
		}
	}
	~RB_Tree()
	{
		clear(m_root);
		delete m_nullNode;
	}
private:
	void clear(RB_Node* node)
	{
		if (node == m_nullNode)
		{
			return;
		}
		else
		{
			clear(node->left);
			clear(node->right);
			delete node;
		}
	}
private:
	RB_Node *m_nullNode;
	RB_Node *m_root;
};
