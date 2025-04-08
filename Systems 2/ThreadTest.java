package threads;

public class ThreadTest {

	public static void main(String[] args) {
		
		int n = 100;
		int[] a = new int[n];
		int[] b = new int[n];
		int[] c = new int[n];
		
		for (int i=0; i<n; i++) {
			a[i] = i;
			b[i] = i;
		} 
		
		
		int numThreads = 4;
		Thread[] ths = new Thread[numThreads];
		for (int i=0; i<numThreads; i++) {
			int start = (n/numThreads) * i; // watch out for int div
			int stop = (n/numThreads) * (i+1);
			
			VecAddThread va = new VecAddThread(i, start, stop, a, b, c);
			Thread th = new Thread(va);
			ths[i] = th;
			th.start();  // fork	
		}
		
		for (int i=0; i<numThreads; i++) {
			try {
				ths[i].join();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		for (int i=0; i<n; i++) {
			System.out.println(c[i]);
		}
		
		
		/*
		 * 
		 * VecAdThread va = new VecAddThread();
		Thread th = new Thread(va);
		th.start();  // fork
		
		try {
			Thread.sleep(1);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		System.out.println("in main");
		
	
		 */
		
	}

}
