class Circle {
	Vec c;
	double r;
	
	public Circle(Vec c, double r) {
		this.c=c;
		this.r=r;
	}
	
	public boolean contains(Vec v) { 
		return c.sub(v).mag2()-Vec.EPS*Vec.EPS<=r*r;
	}
	
	//when standing at this circle, returns right tangent, then left tangent
	public Vec[] intersect(Circle o) {
		if (c.equals(o.c)) return null;
		Vec dir=o.c.sub(c);
		double d2=dir.mag2(), d=Math.sqrt(d2);
		if (r+o.r<d||r+d<o.r||o.r+d<r)
			return null;
		if (Vec.eq(r+o.r, d)||Vec.eq(o.r+d, r))
			return new Vec[] {c.add(dir.scale(r/d))};
		if (Vec.eq(r+d, o.r))
			return new Vec[] {c.sub(dir.scale(r/d))};//.sub()!!
		
		double d1=(r*r+d2-o.r*o.r)/(2*d);
		double h=Math.sqrt(r*r-d1*d1);
		Vec unitDir=dir.unit();
		Vec rInt=c.add(unitDir.scale(d1).add(unitDir.rot270().scale(h)));
		Vec lInt=c.add(unitDir.scale(d1).add(unitDir.rot90().scale(h)));
		return new Vec[] {rInt, lInt};
	}
	
	public double intersectionArea(Circle o) {
		double d=o.c.sub(c).mag();
		if (r+o.r<d) return 0;
		double minR=Math.min(r, o.r), maxR=Math.max(r, o.r), pi=Math.PI;
		if (Vec.leq(d+minR, maxR)) return pi*minR*minR;
		
		double theta1=2*Math.acos((r*r+d*d-o.r*o.r)/(2*r*d));
		double theta2=2*Math.acos((o.r*o.r+d*d-r*r)/(2*o.r*d));
		double part1Area=theta1/2*r*r;
		double part2Area=theta2/2*o.r*o.r;
		
		double tri1=r*r*Math.sin(theta1)/2;
		double tri2=o.r*o.r*Math.sin(theta2)/2;
		return part1Area+part2Area-tri1-tri2;
	}
	
	//returns right tangent, then left tangent from perspective of the point
	public Vec[] getTangentPoints(Vec p) {
		if (contains(p))
			return null;
		double d2=c.sub(p).mag2();
		return new Circle(p, Math.sqrt(d2-r*r)).intersect(this);
	}
	
	//line going from my left to his right, then my right to his left
	//lines go from me to him
	public Seg[] internalTangentLines(Circle o) {
		Vec[] tangentPoints=new Circle(c, r+o.r).getTangentPoints(o.c);
		Vec offset1=tangentPoints[0].sub(o.c).rot90().unit().scale(o.r);
		Vec offset2=tangentPoints[1].sub(o.c).rot270().unit().scale(o.r);
		return new Seg[] {new Seg(tangentPoints[0].add(offset1), o.c.add(offset1)),
						  new Seg(tangentPoints[1].add(offset2), o.c.add(offset2))};
	}
	
	//right external tangent, then left external tangent, from my perspective
	//lines go from me to him
	public Seg[] externalTangentLines(Circle o) {
		if (o.r>r) {
			Seg[] oAnswer=o.externalTangentLines(this);
			return new Seg[] {new Seg(oAnswer[1].to, oAnswer[1].from), new Seg(oAnswer[0].to, oAnswer[0].from)};
		}
		Vec[] tangentPoints=new Circle(c, r-o.r).getTangentPoints(o.c);
		Vec offset1=tangentPoints[0].sub(o.c).rot270().unit().scale(o.r);
		Vec offset2=tangentPoints[1].sub(o.c).rot90().unit().scale(o.r);
		return new Seg[] {new Seg(tangentPoints[1].add(offset2), o.c.add(offset2)),
						  new Seg(tangentPoints[0].add(offset1), o.c.add(offset1))};
	}
	
	//line (not line segment)-circle intersection in the order of line.dir
	public Vec[] intersectLine(Seg line) {
		Vec closest=line.projectToLine(c);
		double d2=closest.sub(c).mag2();
		if (d2>r*r) return null;
		double l=Math.sqrt(r*r-d2);
		if (Vec.eq(l, 0)) return new Vec[] {closest};
		Vec lVec=line.dir.unit().scale(l);
		return new Vec[] {closest.sub(lVec), closest.add(lVec)};
	}
	
	//line segment-circle intersection
	public Vec[] intersectSeg(Seg seg) {
		Vec[] lineIntersections=intersectLine(seg);
		if (lineIntersections==null) return null;
		ArrayList<Vec> contained=new ArrayList<>();
		for (Vec v:lineIntersections)
			if (seg.containsPoint(v))
				contained.add(v);
		if (contained.isEmpty()) return null;
		return contained.toArray(new Vec[contained.size()]);
	}
	
	
	public String toString() {
		DecimalFormat df=new DecimalFormat();
		return "center: "+c+", r: "+df.format(r);
	}
}
