
class VecL implements Comparable<VecL> {
	long x, y;
	public VecL(long x, long y) {this.x=x;this.y=y;}
	public VecL add(VecL o) {return new VecL(x+o.x, y+o.y);}
	public VecL sub(VecL o) {return new VecL(x-o.x, y-o.y);}
	public VecL scale(long s) {return new VecL(x*s, y*s);}
	public long dot(VecL o) {return x*o.x+y*o.y;}
	public long cross(VecL o) {return x*o.y-y*o.x;}
	public long mag2() {return dot(this);}
	public VecL rot90() {return new VecL(-y, x);}
	public VecL rot270() {return new VecL(y, -x);}
	public String toString() {return "("+x+", "+y+")";}
	public int hashCode() {return Long.hashCode(x<<13^(y*57));}
	
	public boolean equals(Object oo) {
		VecL o=(VecL)oo;
		return x==o.x&&y==o.y;
	}
	
	public int compareTo(VecL o) {
		if (x!=o.x) return Long.compare(x, o.x);
		return Long.compare(y, o.y);
	}
	
	//origin->q1, axes-> quadrant in ccw direction
	public int quadrant() {
		if (x==0||y==0)
			if (y==0) return x>=0 ? 1 : 3;
			else return y>=0 ? 2 : 4;
		if (x>0) return y>0 ? 1 : 4;
		else return y>0 ? 2 : 3;
	}
	
	public int radialCompare(VecL o) {
		if (quadrant()==o.quadrant())
			return -Long.signum(cross(o));
		return Integer.compare(quadrant(), o.quadrant());
	}
}
