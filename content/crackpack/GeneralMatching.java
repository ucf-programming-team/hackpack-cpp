//O(V*V*E) but tends to run faster in practice
public class GeneralMatchingBetter {
	HashSet<Integer>[] g;  int[] match;
	public GeneralMatchingBetter(HashSet<Integer>[] G) {
		Arrays.fill(match = new int[(g = G).length], -1);
	}
	public int Matching(){
		for(int count = 0;;count+=2) {		
			ArrayDeque<Integer> path = getPath(g);
			if(path == null) return count;
			while (!path.isEmpty()) {
				int cur = path.poll(), next = path.poll();
				match[cur] = next;  match[next] = cur;
			}
		}
	}
	public ArrayDeque<Integer> getPath(HashSet<Integer>[] gg){
		int[] prev, label, dist = new int[gg.length];
		Arrays.fill(prev = new int[gg.length], -1);
		Arrays.fill(label = new int[gg.length], -1);
		ArrayDeque<Integer> qu = new ArrayDeque<Integer>();
		ArrayDeque<Integer> path = new ArrayDeque<Integer>();
		for(int i = 0;i<gg.length;i++)  if(match[i] == -1) qu.add(label[i] = i); 
		while (!qu.isEmpty()) {
			int cur = qu.poll();
			for(int e : gg[cur]){
				if(e == cur || !(e == match[cur] ^ dist[cur]%2 == 0)) continue;
				if(label[e] == -1 && qu.add(e)){
					label[e] = label[cur];  dist[e] = dist[prev[e] = cur]+1;
				}
				else if(dist[e] == dist[cur]){
					if(label[e] == label[cur])  return Contract(gg, e, cur, prev);
					while(e != -1){
						path.addFirst(e);  path.add(cur);
						e = prev[e];  cur = prev[cur];
					}
					return path;
				}			
			}
		}
		return null;
	}
	public ArrayDeque<Integer> Contract(HashSet<Integer>[] gg, int s1, int s2, int[] prev){
		int cs1 = s1, cs2 = s2, len = 0;
		for(;cs1 != cs2;len+=2, cs1 = prev[cs1], cs2 = prev[cs2]);
		int rr = cs1, lp = len/2 -1, rp = len/2;
		int[] cycle = new int[len], nroot = new int[g.length];
		HashSet<Integer> cs = new HashSet<Integer>();
		while(lp != -1){
			cs.add(s1);  cs.add(s2);
			s1 = prev[cycle[lp--] = s1];  s2 = prev[cycle[rp++] = s2];
		}
		HashSet<Integer>[] ng = new HashSet[g.length];
		for(int i = 0;i<g.length;i++) { ng[i] = new HashSet<Integer>(); }
		for(int i = 0;i<g.length;i++)
			for(int e : gg[i]) ng[(cs.contains(i) ? rr : i)].add(cs.contains(e) ? rr : e);
		ArrayDeque<Integer> path = getPath(ng), rpath = new ArrayDeque<Integer>();
		if(path == null) return path;  int last = path.poll();
		while(path.size() > 0){
			int cur = path.poll(), pos = -1;  rpath.add(last);
			if(last == rr || cur == rr){
				boolean found = false;
				for(int e : gg[last]) if(e == cur) { found = true; break; }
				if(!found){
					for(int i = 0;i<cycle.length;i++)
						for(int e : gg[cycle[i]])
							if(e == (cur == rr ? last : cur)) {
								pos = i; break;
							}
					
					if(pos % 2 == 0 && last == rr) 
						for(int i = cycle.length-1;i>=pos;i--) rpath.add(cycle[i]);
					
					else if(pos % 2 == 0 && cur == rr) 
						for(int i = pos;i<cycle.length;i++) rpath.add(cycle[i]);
					
					else if(pos %2 == 1 && cur == rr) 
						for(int i = pos;i>=0;i--) rpath.add(cycle[i]);
					
					else  for(int i = 0;i<=pos;i++) rpath.add(cycle[i]);
				}
			}
			last = cur;
		}
		rpath.add(last);  return rpath;
	}
}
