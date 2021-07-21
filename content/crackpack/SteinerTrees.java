// O(2^m * n^2   +   3^m * n)
// precomp distances array
// m is # of leaves; n is # of nodes
int[][] dp = new int[n][1 << m];
for(int[] a : dp) Arrays.fill(a, oo);
// Fill all leave's distances with their individual masks to 0
for(int i = 0; i < m; i++) dp[ mapping[i] ][1 << i] = 0;
for(int mask = 1; mask < (1 << m); mask++)
  for(int i = 0; i < n; i++) {
    for(int sm = mask; sm > 0; sm = (sm - 1) & mask)
      dp[i][mask] = Math.min(dp[i][mask], dp[i][sm] + dp[i][mask - sm]);
    for(int j = 0; j < n; j++)
      dp[j][mask] = Math.min(dp[j][mask], dp[i][mask] + dists[i][j]);
  }
  
// Spiderman method for m <= 5
// O( (v + e) * 2^m * log e )
// pick start leaf, do augmented dijkstra's on path
// precomp distances from all leaves
// state [i][leaves mask] = minCost
// transition: either continue building path or grab some leaf
