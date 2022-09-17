//Nodes 0 and 1 are dummy nodes. Not actual palindromes in the string
//link[i] is suffix link, slink[i] is series link
static class Eertree {
	int[] s, len, link, slink, diff;
	int[][] to;
	int sz, last, n;
	long pCnt;
	public Eertree(int nn) {
		s = new int[nn+2];
		len = new int[nn+2];
		link = new int[nn+2];
		to = new int[26][nn+2];
		slink = new int[nn+2];
		diff = new int[nn+2];
		s[n++] = -1;
		link[0] = link[1] = 1;
		len[1] = -1;
		sz = 2;
	}
	int getLink(int v) {
		while(s[n-len[v]-2] != s[n-1]) v = link[v];
		return v;
	}
	void addLetter(char ch) {
		int c = ch-'a';
		s[n++] = c;
		last = getLink(last);
		if(to[c][last] == 0) {
			len[sz] = len[last]+2;
			link[sz] = to[c][getLink(link[last])];
			diff[sz] = len[sz]-len[link[sz]];
			if(diff[sz] == diff[link[sz]]) slink[sz] = slink[link[sz]];
			else slink[sz] = link[sz];
			to[c][last] = sz++;
		}
		last = to[c][last];
	}
}

// Series link DP optimization:
res = new long[N+1]; //Actual DP
// res[i] is answer if at index (i-1) in the string (res[0] is base case)
dpS = new long[N+2]; //DP for the eetree
//Initialize the eertree and fill dpS with -1.
//Fill res[baseCase] with the answer for base case
Eertree et = new Eertree(N);
Arrays.fill(dpS, -1);
res[0] = 1;
for(int i = 1; i <= N; i++) { //Loop over the palindromes ending at index (i-1)
	//Add the character to the eertree and now et.last is the
	// node of the longest suffix ending at index (i-1)
	et.addLetter(c[i-1]);
	//get res[i] by looping through the suffix links
	for(int j = et.last; et.len[j] > 0; j = et.slink[j]) {
		dpS[j] = 0; // Starting value
		dpS[j] = update(dpS[j], res[i-(et.len[et.slink[j]] + et.diff[j])]);
		if(et.diff[j] == et.diff[et.link[j]]) { // Non trivial series
			dpS[j] = update(dpS[j], dpS[et.link[j]]);
		}
		// In sample problem we only want palindromes ending at even indeces
		if((i&1) == 0) {
			res[i] = update(res[i], dpS[j]);
		}
	}
}
// update(a, b): returns new value if a is current dp value and b is dp of next state
long update(long a, long b){ return (a+b)%mod;}
public class Eertree {
	
}
