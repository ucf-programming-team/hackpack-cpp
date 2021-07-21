// R * C * min(R,C)
public static void gaussian(double[][] m, boolean augmented) {
	int R = m.length, C = m[0].length;
	int pc = 0, pr = 0;
	while(pr < r && pc < (augmented ? C-1 : C )) {
		int sr = pr;
		for (int j = pr + 1; j < R; j++)
			if (Math.abs(m[j][pc]) > Math.abs(m[sr][pc]))
				sr = j;
		swap(m, sr, pr);
		if (eq(m[pr][pc],0)) { // indpt variable
			pc++;
			continue;
		}
		double piv = m[pr][pc];
		for (int j = pc; j < C; j++)
			m[pr][j] /= piv;
		for (int j = 0; j < R; j++) {
			if(j == pr) continue;
			double ratio = -m[j][pc];
			for (int k = pc; k < C; k++) {
				m[j][k] += m[pr][k] * ratio;
			}
		}
		pc++;
		pr++;
	}
}
