class Seg {
	Vec from, to, dir;
	
	public Seg(Vec from, Vec to) {
		this.from=from;
		this.to=to;
		dir=to.sub(from);
	}
	
	//line-line intersection
	public Vec lineIntersect(Seg o) {
		double det=o.dir.x*dir.y-dir.x*o.dir.y;
		if (Vec.eq(det, 0)) return null;
		double dist=(o.dir.x*(o.from.y-from.y)-
				o.dir.y*(o.from.x-from.x))/det;
		return from.add(dir.scale(dist));
	}
	
	public boolean containsPoint(Vec o) {
		double distFromLine=dir.unit().cross(o.sub(from));
		if (!Vec.eq(distFromLine, 0)) return false;
		return Vec.eq(dir.mag(), from.sub(o).mag()+to.sub(o).mag());
	}
	
	//seg-seg intersection
	public Vec segIntersection(Seg o) {
		Vec intersect=lineIntersect(o);
		if(intersect == null) return null;
		return containsPoint(intersect)&&o.containsPoint(intersect)?intersect:null;
	}
	
	//returns 1 if above, 0 if on, -1 if below
	public int side(Vec o) {
		Vec oDir=o.sub(from);
		double distFromLine=dir.unit().cross(oDir);
		if (Vec.eq(distFromLine, 0))
			return 0;
		return (int)Math.signum(distFromLine);
	}
	
	public boolean intersects(Seg o) {
		return side(o.from)!=side(o.to) && o.side(from)!=o.side(to);
	}
	
	public Vec getClosestTo(Vec o) {
		double percentThere=o.sub(from).dot(dir)/dir.mag2();
		return from.add(dir.scale(Math.max(0, Math.min(1, percentThere))));
	}
	
	public Vec projectToLine(Vec o) {
		return dir.scale(o.sub(from).dot(dir)/dir.mag2()).add(from);
	}
	
	//toContain must be a point with positive x and y coordinates.
	//this method returns the shortest line segment from the x-axis to the point to the y axis
	public static Seg getShortestSegFromAxesContainingQ1Point(Vec toContain) {
		double slope=-Math.pow(toContain.y/toContain.x, 1.0/3);
		double b=toContain.y-toContain.x*slope;
		double xInt=-b/slope;
		return new Seg(new Vec(0, b), new Vec(xInt, 0));
	}
	
	public String toString() {
		return from+" -> "+to;
	}
}
