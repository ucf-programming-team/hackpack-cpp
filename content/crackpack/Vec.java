class Vec {
	static final double EPS=1e-6;
	double x, y;
	public Vec(double x, double y) {this.x=x;this.y=y;}
	public Vec add(Vec o) {return new Vec(x+o.x, y+o.y);}
	public Vec sub(Vec o) {return new Vec(x-o.x, y-o.y);}
	public Vec scale(double s) {return new Vec(x*s, y*s);}
	public double dot(Vec o) {return x*o.x+y*o.y;}
	public double cross(Vec o) {return x*o.y-y*o.x;}
	public double mag2() {return dot(this);}
	public double mag() {return Math.sqrt(mag2());}
	public Vec unit() {return scale(1/mag());}
	public Vec rot90() {return new Vec(-y, x);}
	public Vec rot270() {return new Vec(y, -x);}
	
	public Vec rotate(double theta) {
		double PI=Math.PI;
		double newX=x*Math.cos(theta)+y*Math.cos(PI/2+theta);
		double newY=x*Math.sin(theta)+y*Math.sin(PI/2+theta);
		return new Vec(newX, newY);
	}
	
	//angle between 0 and 2PI
	public double angle() {
		return (Math.atan2(y, x)+2*Math.PI)%(2*Math.PI);
	}
	
	public String toString() {
		DecimalFormat df=new DecimalFormat("#.##");
		return "("+df.format(x)+", "+df.format(y)+")";
	}
	
	static boolean eq(double a, double b) {return Math.abs(a-b)<EPS;}
	static boolean leq(double a, double b) {return a-EPS<b;}
	static boolean geq(double a, double b) {return a+EPS>b;}
	
	public boolean equals(Object oo) {
		Vec o=(Vec)oo;
		return eq(x, o.x)&&eq(y, o.y);
	}
}
