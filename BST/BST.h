#pragma once

template<typename Type>
class BST {

private:
	struct Node
	{
		Type Data;
		Node* left;
		Node* right;		
		Node() { left = nullptr; right = nullptr; }
	};
	Node * root;
	int tamano = 0;

public:
	/////////////////////////////////////////////////////////////////////////////
	// Function : Constuctor
	// Notes : constucts an empty BST
	/////////////////////////////////////////////////////////////////////////////
	BST() 
	{ 
		root = nullptr; 
	}

		/////////////////////////////////////////////////////////////////////////////
		// Function : Destructor
		// Notes : destroys the BST cleaning up any dynamic memory
		/////////////////////////////////////////////////////////////////////////////
	~BST() 
	{
		clear();
	}

		/////////////////////////////////////////////////////////////////////////////
		// Function : assignment operator
		/////////////////////////////////////////////////////////////////////////////
	BST& operator=(const BST& that)
	{
		if (tamano == 0)
		{
			root = nullptr;
		}
		clear();
		Node* current = that.root;
		preOrder(current);
		return *this;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function: copy constructor
	/////////////////////////////////////////////////////////////////////////////
	BST(const BST& that) 
	{
		if (tamano == 0)
		{
			root = nullptr;
		}
		clear();
		Node* current = that.root;
		preOrder(current);
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : insert
	// Parameters :  v - the item to insert 
	/////////////////////////////////////////////////////////////////////////////
	void insert(const Type& v)
	{
		Node * temp = new Node;
		temp->Data = v;
		if (root == nullptr)
		{
			root = temp;
			return;
		}

		Node* current = root;
		while (true)
		{
			if (temp->Data >= current->Data)
			{
				if (current->right == nullptr)
				{
					current->right = temp;
					return;
				}
				else
				{
					current = current->right;
					continue;
				}
			}
			else if (temp->Data < current->Data)
			{
				if (current->left == nullptr)
				{
					current->left = temp;
					return;
				}
				else
				{
					current = current->left;
					continue;
				}
			}
		}
		tamano++;
	}


		/////////////////////////////////////////////////////////////////////////////
		// Function : findAndRemove
		// Parameters : v - the item to find (and remove if it is found)
		// Return : bool - true if the item was removed, false otherwise
		/////////////////////////////////////////////////////////////////////////////
	bool findAndRemove(const Type& v)
	{
		if (!find(v))
		{
			return false;
		}
		tamano--;

		Node* current = root;
		Node* current2 = nullptr;
		Node* parent = nullptr;
		if (v == current->Data)
		{
			if (current->left == nullptr && current->right == nullptr)
			{
				delete current;
				root = nullptr;
				current = nullptr;
				return true;
			}
			else if (current->left == nullptr)
			{
				current2 = current->right;
				delete current;
				current = current2;
				root = current;
				return true;
			}
			else if (current->right == nullptr)
			{
				current2 = current->left;
				delete current;
				current = current2;
				root = current;
				return true;
			}
			else
			{
				current2 = current->right;

				while (current2->left->left != nullptr)
				{
					current2 = current2->left;
				}
				Type D = current2->left->Data;
				findAndRemove(D);
				current->Data = D;
				return true;
			}
		}

		while (current->Data != v)
		{
			if (v < current->Data)
			{
				parent = current;
				current = current->left;
			}
			else if (v > current->Data)
			{
				parent = current;
				current = current->right;
			}
		}

		if (current->right == nullptr && current->left == nullptr)
		{
			if (current->Data < parent->Data)
			{
				parent->left = nullptr;
			}
			else
			{
				parent->right = nullptr;
			}
			delete current;
			//current = nullptr;
			return true;
		}
		else if (current->right == nullptr && current->left != nullptr)
		{
			if (current->Data < parent->Data)
			{
				parent->left = current->left;
			}
			else
			{
				parent->right = current->left;
			}
			delete current;
			return true;
		}
		else if (current->right != nullptr && current->left == nullptr)
		{
			if (current->Data < parent->Data)
			{
				parent->left = current->right;
			}
			else
			{
				parent->left = current->right;
			}
			delete current;
			return true;
		}
		else if (current->right != nullptr && current->left != nullptr)
		{
			current2 = current->right;
			while (current2->left->left != nullptr)
			{
				current2 = current2->left;
			}
			//current->Data = parent->Data;
			Type dataS = current2->left->Data;
			findAndRemove(dataS);
			current->Data = dataS;

			
			return true;
		}
		tamano--;

		
	}
	
		/////////////////////////////////////////////////////////////////////////////
		// Function : find
		// Parameters : v - the item to find
		// Return : bool - true if the item was found, false otherwise
		/////////////////////////////////////////////////////////////////////////////
	bool find(const Type& v) const 
	{
		//Node * temp = new Node;
		//temp->Data = v;
		Node* current = root;

		while (true)
		{
			if (current == nullptr)
			{
				return false;
			}
			if (v == current->Data)
			{
				return true;
			}
			else if (v < current->Data)
			{
				current = current->left;
				continue;
			}
			else if (v > current->Data)
			{
				current = current->right;
				continue;
			
			}
			
		}
	}


		/////////////////////////////////////////////////////////////////////////////
		// Function : clear
		// Notes : clears the BST, cleaning up any dynamic memory
		/////////////////////////////////////////////////////////////////////////////
	void clear() 
	{
		posOrder(root);
		root = nullptr;
		tamano = 0;

	}

		/////////////////////////////////////////////////////////////////////////////
		// Function : printInOrder
		// Notes : prints the contents of the BST to the screen, in ascending order
		/////////////////////////////////////////////////////////////////////////////
	void printInOrder() const
	{		
		if (root!= nullptr)
		{
			printInOrder(root->left);
			cout << root->Data << " ";
			printInOrder(root->right);
		}
		cout << '\n';
	}
	void printInOrder(Node* r) const
	{
		if (r != nullptr)
		{
			printInOrder(r->left);
			cout << r->Data << " ";
			printInOrder(r->right);
		}

	}
	void preOrder(Node* n)
	{
		if (n != nullptr)
		{
			insert(n->Data);
			preOrder(n->left);
			preOrder(n->right);
		}
	}
	void posOrder(Node* d) const
	{
		if (d != nullptr)
		{
			posOrder(d->left);
			posOrder(d->right);
			delete d;
		}

	}
};