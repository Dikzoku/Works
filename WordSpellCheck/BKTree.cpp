#include "BKTree.h"

void BKTree::erase(BKTreeNode* t){
	for(auto i:t->chd) erase(i.second);
	delete t;
}
int BKTree::distance(string s1,string s2){
	if(s1.size()==0) return s2.size();
	if(s2.size()==0) return s1.size();
	int D[s1.size()+1][s2.size()+1];
    for(int i=1;i<=(int)s1.size();i++) D[i][0]=i;
    for(int j=1;j<=(int)s2.size();j++) D[0][j]=j;
	D[0][0]=0;
    for(int i=1;i<=(int)s1.size();i++){
        for(int j=1;j<=(int)s2.size();j++){
            D[i][j]=min(D[i-1][j]+1,D[i][j-1]+1);
			D[i][j]=min(D[i][j],D[i-1][j-1]+(s1[i-1]==s2[j-1]?0:1));
		}
	}
	return D[s1.size()][s2.size()];
}
void BKTree::insert(BKTreeNode* t,const string &word){
	int D=distance(t->word,word);
    if(D==0) return;
    if(t->chd.count(D)) insert(t->chd[D],word);
	else{
		BKTreeNode* newt=new BKTreeNode(word);
		t->chd[D]=newt;
	}
}
void BKTree::insert(const string &word){ //外部调用接口
	if(root==NULL){
		root=new BKTreeNode(word);
	}else insert(root,word);
}
void BKTree::query(BKTreeNode* t,const string &word,int dist,vector<string> &vec){
	int D=distance(t->word,word);
	if(D<=dist) vec.push_back(t->word);
    for(int i=max(D-dist,1);i<=D+dist;i++){
		if(t->chd.count(i)) 
			query(t->chd[i],word,dist,vec);
	}
} 
vector<string> BKTree::query(const string &word,int dist){ //外部调用接口
    vector<string> vec;
	if(root!=NULL) query(root,word,dist,vec);
	return vec;
}

void BKTree::erasechd(BKTreeNode* t,vector<string> &vec){
    for(auto i:t->chd){
        vec.push_back(i.second->word);
        erasechd(i.second,vec);
    }
    delete t;
}
void BKTree::erase(const string &word){
    if(root==NULL) return;
    BKTreeNode* t=root,*pre=NULL;
    int D=distance(t->word,word);
    while(D){
        if(t->chd.count(D)) pre=t,t=t->chd[D];
        else return;
        D=distance(t->word,word);
    }
    if(pre!=NULL){//删除的不是根
        pre->chd.erase(distance(t->word,pre->word));
    }else{//删除的是根
        root=NULL;
    }
    vector<string> vec;
    erasechd(t,vec);
    for(auto i:vec) insert(i);
}

void BKTree::output(BKTreeNode* t,ofstream &out){
    for(auto i:t->chd){
        out<<t->word<<" -> "<<i.second->word<<" [label=\""<<i.first<<"\"];\n";
        output(i.second,out);
    }
}
void BKTree::bKTreeOut(string outpath){
    ofstream out(outpath);
    out<<"digraph G {"<<'\n';
    if(root!=NULL) output(root,out);
    out<<"}"<<endl;
    out.close();
}


