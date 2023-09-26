#include<bits/stdc++.h>

using namespace std;

struct BKTreeNode{
	string word;
	map<int,BKTreeNode*> chd;
	BKTreeNode(const string &_word)
		:word(_word){}
};
class BKTree{
	private:
		BKTreeNode* root;
		int distance(string s1,string s2); 
		//返回s1与s2的编辑距离
		void insert(BKTreeNode* t,const string &word); 
		//向t为根的树中加入一个单词word,递归实现
		void query(BKTreeNode* t,const string &word,int dist,vector<string> &vec); 
		//从t为根的树中查询与word的编辑距离小于等于dist的所有单词,存到vec中,递归实现
		void erase(BKTreeNode* t);
        void erasechd(BKTreeNode* t,vector<string> &vec);
        void output(BKTreeNode* t,ofstream &out);
	public:
		BKTree(){root=NULL; };
        ~BKTree(){if(root!=NULL) erase(root); };
		
        void clear(){if(root!=NULL) erase(root); root=NULL; };

		void insert(const string &word); //外部调用接口
        void erase(const string &word);
		vector<string> query(const string &word,int dist); //外部调用接口
        void bKTreeOut(string outpath);

};
