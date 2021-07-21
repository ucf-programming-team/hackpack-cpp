
class Plane {
	//point on plane and unit normal vector, p2 and p3 are arbitrary other points on the plane
	Vec3 p, n, p2, p3;
	
	Vec3 planeXAxis, planeYAxis;
	static final Vec3 randPoint1=new Vec3(157.157, 123.123, 0.102), 
							 randPoint2=new Vec3(-14.14, 3.14159, 814.12);
	
	public Plane(Vec3 p, Vec3 n) {
		this.p=p;
		this.n=n=n.unit();
		
		p2=projectToPlane(randPoint1);
		p3=projectToPlane(randPoint2);
		
		planeXAxis=p2.sub(p).unit();
		Vec3 p3Dir=p3.sub(p);
		planeYAxis=p3Dir.sub(planeXAxis.scale(planeXAxis.dot(p3Dir))).unit();
	}
	
	public Vec3 projectToPlane(Vec3 o) {
		Vec3 dir=o.sub(p);
		return o.sub(n.scale(n.dot(dir)));
	}
	
	public Vec getXY(Vec3 o) {
		o=o.sub(p);
		return new Vec(o.dot(planeXAxis), o.dot(planeYAxis));
	}
	
	//line-plane intersection
	public Vec3 intersect(Seg3 line) {
		if (parallelToLine(line))
			return null;
		double speedToPlane=-line.dir.dot(n);
		double timeToPlane=dist(line.from)/speedToPlane;
		return line.from.add(line.dir.scale(timeToPlane));
	}
	
	//point to plane distance, negative if below plane
	public double dist(Vec3 o) {
		return n.dot(o.sub(p));
	}
	
	//checks if the plane is parallel to the line
	public boolean parallelToLine(Seg3 line) {
		return Vec.eq(line.dir.dot(n), 0);
	}
	
	public String toString() {
		return "{p: "+p+", n: "+n+"}";
	}
	
}
