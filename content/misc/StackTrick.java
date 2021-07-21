public class StackTrick implements Runnable {
	public static void main(String[] args) {
		// adjust the size as needed
		new Thread(null, new StackTrick(), "", (1 << 24)).start();
	}
	public void run() {
		solve();
	}
	void solve() {
		// solve the problem here
		System.out.println("brother.");
	}
}
