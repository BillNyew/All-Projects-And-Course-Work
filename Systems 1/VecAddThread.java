package threads;

public class VecAddThread implements Runnable {
	private int tnum;
	private int start;
	private int stop;
	private int[] a;
	private int[] b;
	private int[] c;
	
	public VecAddThread(int tnum, int start, int stop, int[] a, int[] b, int[] c) {
		this.tnum = tnum;
		this.start = start;
		this.stop = stop;
		this.a = a;
		this.b = b;
		this.c = c;
	}

	@Override
	public void run() {
		System.out.println("in thread " + tnum + " " + start + " - " + stop);
		// Vec add
		for (int i=start; i<stop; i++) {
			c[i] = a[i] + b[i];
		}
		
	}

}
