package class4_1;

import java.util.*;

public class StudentMain {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		StudentManager studentManager = new StudentManager();

		while (true) {
			System.out.println("\nStudent Management System Menu:");
			System.out.println("1. Add Student");
			System.out.println("2. Enroll Student in Course");
			System.out.println("3. Drop Student from Course");
			System.out.println("4. View Student Info");
			System.out.println("5. View All Student Info");
			System.out.println("6. Exit");
			System.out.print("Enter your choice: ");

			int choice = scanner.nextInt();
			scanner.nextLine(); 

			switch (choice) {
			case 1:
				System.out.print("Enter student name: ");
				String studentName = scanner.nextLine();
				System.out.print("Enter student ID: ");
				int studentID = scanner.nextInt();
				scanner.nextLine(); // Consume newline

				// TODO: call appropriate method on the StudentManager object
				break;

			case 2:
				System.out.print("Enter student ID: ");
				int enrollStudentID = scanner.nextInt();
				scanner.nextLine(); // Consume newline

				System.out.print("Enter course to enroll: ");
				String courseToEnroll = scanner.nextLine();
				
				// TODO: call appropriate method on StudentManager object to enroll
				// TODO: a student into a course.
				break;

			case 3:
				System.out.print("Enter student ID: ");
				int dropStudentID = scanner.nextInt();
				scanner.nextLine(); // Consume newline
				System.out.print("Enter course to drop: ");
				String courseToDrop = scanner.nextLine();
				
				// TODO: call appropriate method on StudentManager object to drop
				// TODO: a student from a course.
				break;

			case 4:
				System.out.print("Enter student ID: ");
				int viewStudentID = scanner.nextInt();
				scanner.nextLine(); // Consume newline
				Student student = studentManager.getStudent(viewStudentID);
				System.out.println(student);
				break;

			case 5: 
				System.out.println("Printing All Student Information");
				studentManager.printAllStudentInfo();
				break;

			case 6:
				System.out.println("Exiting Student Management System.");
				scanner.close();
				System.exit(0);
				break;

			default:
				System.out.println("Invalid choice. Please try again.");
			}
		}
	}
}
