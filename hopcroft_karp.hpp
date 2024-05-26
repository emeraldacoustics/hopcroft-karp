#include <queue>
#include <vector>

using namespace std;

class HopcroftKarp
{
public:
	static const int maxn = 1000;
	static const int maxm = 1000;
	static const int inf = 0x7f7f7f7f;

	int n, m;
	vector<int> E[maxn];
	bool vis[maxm];
	int xdst[maxn], ydst[maxm], xlnk[maxn], ylnk[maxm];

	HopcroftKarp(void) : n(0), m(0)
	{

	}

	void resize(const int & n, const int & m)
	{
		for (int i = 0; i < this->n; i++)
			E[i].clear();
		this->n = n;
		this->m = m;
	}

	void add_edge(const int & u, const int & v)
	{
		E[u].push_back(v);
	}

	int get_length(void)
	{
		queue<int> que;
		int res = inf;
		memset(xdst, inf, sizeof xdst[0] * n);
		memset(ydst, inf, sizeof ydst[0] * m);
		for (int u = 0; u < n; u++)
		{
			if (xlnk[u] == -1)
			{
				xdst[u] = 0;
				que.push(u);
			}
		}
		for (; !que.empty(); que.pop())
		{
			int u = que.front();
			for (const auto & v : E[u])
			{
				if (ydst[v] == inf && xdst[u] + 1 <= res)
				{
					ydst[v] = xdst[u] + 1;
					if (ylnk[v] == -1)
						res = ydst[v];
					else if (xdst[ylnk[v]] == inf && ydst[v] + 1 <= res)
					{
						xdst[ylnk[v]] = ydst[v] + 1;
						que.push(ylnk[v]);
					}
				}
			}
		}
		return res;
	}

	bool augpath(const int & u)
	{
		for (const auto & v : E[u])
		{
			if (vis[v])
				continue;
			vis[v] = true;
			if (ydst[v] != inf && (ylnk[v] == -1 || augpath(ylnk[v])))
			{
				ylnk[v] = u;
				xlnk[u] = v;
				return true;
			}
		}
		return false;
	}

	int hopcroft(void)
	{
		int ans = 0;
		memset(xlnk, -1, sizeof xlnk[0] * n);
		memset(ylnk, -1, sizeof ylnk[0] * m);
		for (; get_length() != inf; )
		{
			memset(vis, false, sizeof vis[0] * m);
			for (int u = 0; u < n; u++)
			{
				if (xdst[u] != inf && xlnk[u] == -1)
					ans += augpath(u);
			}
		}
		return ans;
	}
};
