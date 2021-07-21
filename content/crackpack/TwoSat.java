static class TwoSat {
	int n, n2;  byte[] vals, cvals;  SCC scc;

	public TwoSat(int nn) {  n2 = 2 * (n = nn);  scc = new SCC(n2);  vals = new byte[n2];}

	// Example: (true, 0, false, 1) => 0 --> !1
	public void addImpl(boolean va, int a, boolean vb, int b) {
		a <<= 1; b <<= 1;  if (!va) a++;  if (!vb) b++;
		scc.add(a, b);  scc.add(b ^ 1, a ^ 1);
	}

	//# Add (a NAND b)
	public void addNand(boolean va, int a, boolean vb, int b) {
		addImpl(va, a, !vb, b);
	}//$

	//# Add (a OR b)
	public void addOr(boolean va, int a, boolean vb, int b) {
		addImpl(!va, a, vb, b); // ~a -> b
	}//$

	//# Add (a XOR b)
	public void addXor(boolean va, int a, boolean vb, int b) {
		addImpl(!va, a, vb, b); // ~a -> b
		addImpl(va, a, !vb, b); // a -> ~b
	}//$

	//# Forces a to have whatever value va is
	public void addForce(int a, boolean va) {
		addImpl(!va, a, va, a);
	}//$

	// Returns the value of the variable v
	public boolean getVal(int v) {
		return vals[v << 1] == 1;
	}

	public boolean solve() {
		int map[] = scc.go();
		for(int i = 0; i < n; i++) {
			if(map[2*i] == map[2*i+1]) return false;
		}
		for(int i = 0; i < n2; i++) vals[i] = (byte)-1;
		for(int i = 0; i < scc.cs; i++) {
			for(int v : scc.comp[i]) {
				if(vals[v] == -1) {
					vals[v] = 1;
				}
				vals[v^1] = (byte)(vals[v]^1);
			}
		}
		return true;
	}
}
