package class7_1;

import java.util.Scanner;

public class OrderManager {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		boolean done = false;
		System.out.println("Enter order number");
		int orderNumber = sc.nextInt();
		Order tracker = new Order(orderNumber);
		
		while (!done) {
			System.out.println("View Order(v), Ship Order(s), Deliver Order(d), Quit(q)");
			
			String request = sc.next();
			
			try {
				if (request.equals("v")) {
					tracker.viewStatus();
				} else if (request.equals("s")) {
					tracker.shipOrder();
				} else if (request.equals("d")) {
					tracker.deliverOrder();
				} else if (request.equals("q")) {
					done = true;
				}
			} catch (OrderException e) {
				System.out.println(e.getMessage());
			}
		}
		sc.close();
	}
}
