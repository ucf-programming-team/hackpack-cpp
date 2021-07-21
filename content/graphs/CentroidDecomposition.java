class CentroidDecomposition implements Runnable {
    // stack trick
    static int n, k, out, max = Integer.MAX_VALUE / 2, currIt;
    static ArrayDeque[] edges;
    static int[] size;
    static boolean[] del;
    static int[] minL, it;
    static ArrayList<Integer> cds, cls;
    static void solve() throws Exception {
      edges = new ArrayDeque[n];
      for(int i = 0; i < n; ++i) edges[i] = new ArrayDeque<>();
	    del = new boolean[n];
	    minL = new int[k + 1];
	    it = new int[k + 1];
	    Arrays.fill(it, -1);
	    currIt = -1;
	    size = new int[n];
	    cds = new ArrayList<>();
	    cls = new ArrayList<>();
	    out = max;
	    go(0);
    }
    static void go(int idx){
      dfs1(idx, -1);
	    int root = getCentroid(idx, -1, size[idx]);
	    ++currIt;
	    it[0] = currIt;
	    minL[0] = 0;
	    dfs2(root, -1, 0, 0);
	    del[root] = true;
	    for(edge e : (ArrayDeque<edge>) edges[root]){
	        if(!del[e.v]) go(e.v);
	    }
    }
    static void dfs2(int idx, int par, int d, int l){
	    cds.add(d);
	    cls.add(l);
	    
	    int need = k - d;
	    if(it[need] != currIt){
	        it[need] = currIt;
	        minL[need] = max;
	    }
	    int currL = l + minL[need];
	    out = Math.min(out, currL);
	    for(edge e : (ArrayDeque<edge>) edges[idx]){
	        if(!del[e.v] && e.v != par && d + e.w <= k){
	            dfs2(e.v, idx, d + e.w, l + 1);
	            if(par == -1){
	                for(int i = 0; i < cds.size(); ++i){
	                    int cd = cds.get(i), cl = cls.get(i);
	                    if(it[cd] != currIt){
	                        it[cd] = currIt;
	                        minL[cd] = max;
	                    }
	                    if(cl < minL[cd]) minL[cd] = cl;
	                }
	                cds.clear();
	                cls.clear();
	            }
	        }
	    }
	}
	static int getCentroid(int idx, int par, int totSize){
	    for(edge e : (ArrayDeque<edge>) edges[idx]){
	        if(!del[e.v] && e.v != par && size[e.v] * 2 > totSize) return getCentroid(e.v, idx, totSize);
	    }
	    return idx;
	}
	static int dfs1(int idx, int par){
	    int out = 1;
	    for(edge e : (ArrayDeque<edge>) edges[idx]){
	        if(!del[e.v] && e.v != par) out += dfs1(e.v, idx);
	    }
	    return size[idx] = out;
	}
}
