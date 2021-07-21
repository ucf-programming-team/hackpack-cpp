class ConvexHull {

	static VecL[] upperHull, lowerHull;

	public static VecL[] removeDupes(VecL[] points) {
		HashSet<VecL> set=new HashSet<>();
		for (VecL v:points)
			set.add(v);
		int counter=0;
		points=new VecL[set.size()];
		for (VecL v:set) points[counter++]=v;
		return points;
	}

	// returns the hull in CCW order
	public static VecL[] getHull(VecL[] points) {
		points=points.clone();
		Arrays.sort(points);
		if (points.length<3)
			return upperHull=lowerHull=points;
		int n=points.length, j=2, k=2;
		VecL[] lo=new VecL[n], up=new VecL[n];
		lo[0]=points[0];
		lo[1]=points[1];
		for (int i=2; i<n; i++) {
			VecL p=points[i];
			while (j>1&&!right(lo[j-2], lo[j-1], p)) j--;
			lo[j++]=p;
		}
		up[0]=points[n-1];
		up[1]=points[n-2];
		for (int i=n-3; i>=0; i--) {
			VecL p=points[i];
			while (k>1&&!right(up[k-2], up[k-1], p)) k--;
			up[k++]=p;
		}

		VecL[] res=new VecL[j+k-2];
		for (int i=0; i<k; i++) res[i]=up[i];
		for (int i=1; i<j-1; i++) res[k+i-1]=lo[i];

		// if you need upper and lower hulls
		upperHull=new VecL[k];
		for (int i=0; i<k; i++) upperHull[i]=up[k-i-1];
		lowerHull=new VecL[j];
		for (int i=0; i<j; i++) lowerHull[i]=lo[i];

		return res;
	}

	// check if a->b->c are in the right order
	static boolean right(VecL a, VecL b, VecL c) {
		return b.sub(a).cross(c.sub(a))>0;
	}

}
