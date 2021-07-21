// z[i] is equal to the length of the longest substring starting //%
// at i that is also a prefix of the overall string. //%
// O(n) //%
public int[] zValues(String string) {
	int n = string.length();  char[] s = string.toCharArray();
	int[] z = new int[n];  z[0] = n;
	int L = 0, R = 0;
	int[] left = new int[n], right = new int[n];
	for(int i = 1; i < n; ++i) {
		if(i > R) {
			L = R = i;
			while(R < n && s[R-L] == s[R]) R++;
			z[i] = R - L;  R--;
		} else {
			int k = i-L;
			if(z[k] < R-i+1) z[i] = z[k];
			else {
				L = i;
				while(R < n && s[R-L] == s[R]) R++;
				z[i] = R - L;  R--;
			}
		}
		left[i] = L;  right[i] = R;
	}
	return z;
}
