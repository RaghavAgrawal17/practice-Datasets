#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

// Converts key current character into index
// use only 'A' through 'Z'
#define char_int(c) ((int)c - (int)'A')

// Alphabet size
#define SIZE 26

#define M 3
#define N 3

// trie Node
struct TrieNode {
	struct TrieNode* Child[SIZE];

	// isLeaf is true if the node represents
	// end of a word
	bool leaf;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode* getNode()
{
    struct TrieNode s;
	struct TrieNode* newNode = &s;
	newNode->leaf = false;
	for (int i = 0; i < SIZE; i++)
		newNode->Child[i] = NULL;
	return newNode;
}

// If not present, inserts a key into the trie
// If the key is a prefix of trie node, just
// marks leaf node
void insert(struct TrieNode* root, char* Key)
{
	int n = strlen(Key);

	//debug1
	printf("Hello Insert\n");

	struct TrieNode* pChild = root;

	for (int i = 0; i < n; i++)
    {
		int index = char_int(Key[i]);

		if (pChild->Child[index] == NULL)
			pChild->Child[index] = getNode();

		pChild = pChild->Child[index];
	}

	// make last node as leaf node
	pChild->leaf = true;
}

// function to check that current location
// (i and j) is in matrix range
bool isSafe(int i, int j, bool visited[M][N])
{
	return ((i>=0) && (i < M) && (j >= 0) && (j < N) && !visited[i][j]);
}

// A recursive function to print all words present on boggle
void searchWord(struct TrieNode* root, char boggle[M][N], int i,int j, bool visited[M][N], char* str)
{
    printf("1234\n");
	// if we found word in trie / dictionary
	if (root->leaf == true)
        printf("%s\n",str);

	// If both I and j in range and we visited
	// that element of matrix first time
	if (isSafe(i, j, visited)) {
		// make it visited
		visited[i][j] = true;

		// traverse all childs of current root
		for (int K = 0; K < SIZE; K++) {
			if (root->Child[K] != NULL) {
				// current character
				char ch = (char)K + (char)'A';

				// Recursively search reaming character of word
				// in trie for all 8 adjacent cells of boggle[i][j]
				if (isSafe(i + 1, j + 1, visited)&& (boggle[i + 1][j + 1] == ch))
                {
                    strncat(str,&ch,1);
                    searchWord(root->Child[K], boggle,i + 1, j + 1, visited, str);
                }
				if (isSafe(i, j + 1, visited)&& (boggle[i][j + 1] == ch))
                {
                    strncat(str,&ch,1);
                    searchWord(root->Child[K], boggle, i, j + 1, visited, str);
                }
				if (isSafe(i - 1, j + 1, visited)&& (boggle[i - 1][j + 1] == ch))
                {
                    strncat(str,&ch,1);
                    searchWord(root->Child[K], boggle,i - 1, j + 1, visited, str);
                }
				if (isSafe(i + 1, j, visited)&& (boggle[i + 1][j] == ch))
                {
                    strncat(str,&ch,1);
                    searchWord(root->Child[K], boggle,i + 1, j, visited, str);
                }

				if (isSafe(i + 1, j - 1, visited) && (boggle[i + 1][j - 1] == ch))
                {
                    strncat(str,&ch,1);
                    searchWord(root->Child[K], boggle, i + 1, j - 1, visited, str);
                }

				if (isSafe(i, j - 1, visited) && (boggle[i][j - 1] == ch))
                {
                    strncat(str,&ch,1);
                    searchWord(root->Child[K], boggle, i, j - 1, visited, str);
                }
				if (isSafe(i - 1, j - 1, visited) && (boggle[i - 1][j - 1] == ch))
                {
                    strncat(str,&ch,1);
                    searchWord(root->Child[K], boggle, i - 1, j - 1, visited, str);
                }
				if (isSafe(i - 1, j, visited) && (boggle[i - 1][j] == ch))
                {
                    strncat(str,&ch,1);
                    searchWord(root->Child[K], boggle, i - 1, j, visited, str);
                }
			}
		}

		// make current element unvisited
		visited[i][j] = false;
	}
}

// Prints all words present in dictionary.
void findWords(char boggle[M][N], struct TrieNode* root)
{
	// Mark all characters as not visited
	bool visited[M][N];
	memset(visited, false, sizeof(visited));

	struct TrieNode* pChild = root;

	char* str ;
	str = (char*)malloc(100 * sizeof(char));

	// traverse all matrix elements
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			// we start searching for word in dictionary
			// if we found a character which is child
			// of Trie root
			if (pChild->Child[char_int(boggle[i][j])])
            {
				strncat(str,&boggle[i][j],1);
                printf("FindWords\n");
				searchWord(pChild->Child[char_int(boggle[i][j])],boggle, i, j, visited, str);
				str = "";
			}
		}
	}
}

// Driver program to test above function
int main()
{
	// Let the given dictionary be following
	char* dictionary[] = {"GEEKS", "FOR", "QUIZ", "GEE"};

	// root Node of trie
	struct TrieNode* root = getNode();

	// insert all words of dictionary into trie
	int n = sizeof(dictionary) / sizeof(dictionary[0]);
	for (int i = 0; i < n; i++)
		insert(root, dictionary[i]);

	char boggle[M][N] = {{ 'G', 'I', 'Z' },
						{ 'U', 'E', 'K' },
						{ 'Q', 'S', 'E' }};

	findWords(boggle, root);

	return 0;
}
