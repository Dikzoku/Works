#include<bits/stdc++.h>
using namespace std;
#define inf 1000000000
#define maxn 200005
#define maxm 500005
struct edge
{
	int v,w,next;
}e[maxm<<1];
//注意是无向图，开两倍数组

int n,m;
int head[maxn],dis[maxn],cnt;
bool vis[maxn];

void add(int u,int v,int w)
{
	e[++cnt].v=v;
	e[cnt].w=w;
	e[cnt].next=head[u];
	head[u]=cnt;
}
int prim()
{
	for(int i=2;i<=n;++i)
	{
		dis[i]=inf;
	}
    dis[1]=0;
    vis[1]=1;
    int now = 1;
    int tot = n -1 ; //最小生成树边数
    int ans = 0;
    while(tot--)
    {
        //更新dis
        for(int i=head[now];i;i=e[i].next)
        {
        	int v=e[i].v;
        	if(dis[v]>e[i].w&&!vis[v])
        	{
        		dis[v]=e[i].w;
        	}
		}

        //找dis最小的边加入最小生成树
        int minn=inf;
        vis[now]=1;
        for(int i=1;i<=n;++i)
        {
            if(!vis[i]&&minn>dis[i])
            {
                minn=dis[i];
				now=i;
            }
        }
        if(minn == inf) return -1;
        ans+=minn;
    }
    return ans;
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;++i)
    {
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w),add(v,u,w);
    }
    int ans=prim();
    if(ans == -1)printf("orz");
    else printf("%d",ans);
    return 0;
}