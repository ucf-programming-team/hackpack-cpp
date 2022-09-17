class SegL {
	VecL from, to, dir;
	
	public SegL(VecL from, VecL to) {
		this.from=from;
		this.to=to;
		dir=to.sub(from);
	}
	
	//check if the segment contains the point
	public boolean contains(VecL p) {
		VecL d=p.sub(from);
		if (d.cross(dir)!=0) return false;
		long dot=d.dot(dir);
		return dot>=0&&dot<=dir.mag2();
	}
	
	//(assuming I go left to right)
	//returns:
	//	1 if point is above me
	//	0 if point is on me
	//	-1 if point is below me
	public long side(VecL o) {
		long cross=dir.cross(o.sub(from));
		return cross==0?0:cross/Math.abs(cross);
	}
	
	//returns true if this segl intersects the other, including at endpoints
	//note: returns false if the two segments lie on the same line
	public boolean intersects(SegL o) {
		return side(o.from)!=side(o.to) && o.side(from)!=o.side(to);
	}
	
	public String toString() {
		return from+" -> "+to;
	}
	
	//#
	static long gcd(long a, long b) {
		a=Math.abs(a);
		b=Math.abs(b);
		return b==0?a:gcd(b, a%b);
	}
	//$
	
	//returns the lattice point of intersection or null if it is nonlattice or does not exist 
	public VecL latticeIntersect(SegL o) {
		if (!intersects(o)) return null;
		long dirGCD=gcd(dir.x, dir.y), oDirGCD=gcd(o.dir.x, o.dir.y);
		VecL va=new VecL(dir.x/dirGCD, dir.y/dirGCD), vb=new VecL(o.dir.x/oDirGCD, o.dir.y/oDirGCD);
		if (va.x<0&&va.y<0) {
			va.x*=-1;
			va.y*=-1;
		}
		if (vb.x<0&&vb.y<0) {
			vb.x*=-1;
			vb.y*=-1;
		}
		if (va.equals(vb)) {
			return null;
		}
		long bottomScalar=va.x/gcd(va.x, va.y);
		long topScalar=va.y/gcd(va.x, va.y);
		long t2Scalar=-bottomScalar*vb.y + topScalar*vb.x;
		long t2Ans=bottomScalar*(o.from.y-from.y) - topScalar*(o.from.x-from.x);
		if (t2Ans%t2Scalar!=0)
			return null;
		long t2=t2Ans/t2Scalar;
		return new VecL(t2*vb.x+o.from.x, t2*vb.y+o.from.y);
	}
}
