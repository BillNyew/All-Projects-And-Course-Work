package class4_1;

import java.util.ArrayList;
import java.util.List;

public class StudentFactory {
	
	public static Student newStudent(String studentName, int studentID)
	{
		return new StudentImpl(studentName, studentID);
	}

	private static class StudentImpl implements Student
	{
		private String studentName;
		private int studentID;
		private List<String> enrolledCourses;

		public StudentImpl(String studentName, int studentID) {
			this.studentName = studentName;
			this.studentID = studentID;
			this.enrolledCourses = new ArrayList<>();
		}

		@Override
		public void enroll(String course) {
			enrolledCourses.add(course);
			System.out.println(studentName + " enrolled in " + course);
		}

		@Override
		public void drop(String course) {
			if (enrolledCourses.contains(course)) {
				enrolledCourses.remove(course);
				System.out.println(studentName + " dropped " + course);
			} else {
				System.out.println(studentName + " is not enrolled in " + course);
			}
		}

		@Override
		public List<String> getEnrolledCourses() {
			return new ArrayList<String>(enrolledCourses);
		}

		@Override
		public String toString() {
			return this.studentID + " " + this.studentName + " " + this.enrolledCourses.toString();
		}
	}	
}
