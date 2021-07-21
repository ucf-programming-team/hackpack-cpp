public class TreeHashSharon
{
	
	static long[][] mp;
	static long[] mods = {1_000_000_007, 1_000_000_009, 1_000_000_021};
	static ArrayList<Integer>[] graph;
 
	public static void main(String[] args)
	{
		mp = new long[3][100_001];
		for(int i = 0; i < 3; i++) {
			mp[i][0] = 1;
			for(int j = 1; j < 100_001; j++) {
				mp[i][j] = (mp[i][j-1]*27)%mods[i];
			}
		}
		int n = scan.nextInt();
		graph = new ArrayList[n];
		for(int i = 0; i < n; i++) graph[i] = new ArrayList<Integer>();
		for(int i = 0; i < n-1; i++) {
			int u = scan.nextInt()-1;
			int v = scan.nextInt()-1;
			graph[u].add(v);
			graph[v].add(u);
		}
		int root = 0;
		for(int i = 0; i < n; i++) if(graph[i].size() == 1) root = i;
		depth = new int[n];
		h = new Hash[n];
		for(int i = 0; i < n; i++) h[i] = new Hash();
		if(dfs(root, 0, -1)) {
			System.out.println(root+1);
			return;
		}
		Hash x = new Hash();
		x.add(1);
		solve(graph[root].get(0), x, root);
//		if(dfs(ans, 0, -1))
//			System.out.println(ans);
//		else System.out.println(-1);
		System.out.println(ans);
	}
	
	static Hash[] h;
	
	static int ans = -1;
	static boolean foundAns = false;
	static int[] depth;
	
	static void solve(int root, Hash last, int par) {
		//System.out.println();
		//System.out.println(root+" "+Arrays.toString(last.hash));
		if(foundAns) return;
		boolean upd = false;
		Hash ne = new Hash();
		Hash np = new Hash();
		np.concat(last);
		int next = -1;
		for(int i = 0; i < graph[root].size(); i++) {
			int to = graph[root].get(i);
			if(to == par) continue;
			//System.out.println(to+" "+Arrays.toString(h[to].hash));
			if(!h[to].equal(last)) {
				if(upd) {
					ans = -1;
					foundAns = true;
					return;
				}
				next = to;
				ne = h[to];
				upd = true;
			}
			else {
				np.concat(h[to]);
			}
		}
		np.add(graph[root].size());
		if(next == -1) {
			foundAns = true;
			ans = root+1;
			return;
		}
		
		solve(next, np, root);
	}
	
	static boolean dfs(int root, int d, int par) {
		boolean good = true;
		for(int i = 0; i < graph[root].size(); i++) {
			int to = graph[root].get(i);
			if(to != par) {
				good &= dfs(to, d+1, root);
				h[root].concat(h[to]);
			}
		}
//		System.out.println("ROOT: "+root);
		h[root].add(graph[root].size());
		//System.out.println(Arrays.toString(h[root].hash));
		if(depth[d] == 0) {
			depth[d] = graph[root].size();
		}
		else if(depth[d] != graph[root].size()) return false;
		return good;
	}
	
	static class Hash{
		
		long[] hash = new long[3];
		int len;
		
		public Hash() {
			this.len = 0;
		}
		
		public void add(int p) {
			for(int i = 0; i < 3; i++) {
				hash[i] *= 27;
				hash[i] += p;
				hash[i] %= mods[i];
			}
		}
		
		public boolean equal(Hash p) {
			for(int i = 0; i < 3; i++) {
				if(hash[i] != p.hash[i]) return false;
			}
			return true;
		}
		
		public void concat(Hash p) {
			for(int i = 0; i < 3; i++) {
				long mult = mp[i][len];
				hash[i] *= mult;
				hash[i] %= mods[i];
				hash[i] += p.hash[i];
				hash[i] %= mods[i];
			}
		}
	}
}