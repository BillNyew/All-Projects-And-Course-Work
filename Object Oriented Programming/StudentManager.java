package class4_1;

import java.util.HashMap;
import java.util.Map;
import java.util.Iterator;
import java.util.Map.Entry;

class StudentManager {
	private Map<Integer, Student> students;

	public StudentManager() {
		students = new HashMap<>();
	}

	public void printAllStudentInfo() {
		// TODO: loop across the students and print each one using the toString()
		// TODO: method of the student object
	}

	public void addStudent(String studentName, int studentID) {
		// TODO: if the studentID is already a key in students throw DuplicateStudentException
		// TODO: otherwise get a new Student object from the StudentFactory and add it to students.
		System.out.println("Student added: " + studentID + " - " + studentName);
	}

	public Student getStudent(int studentID) {
		if (students.containsKey(studentID)) {
			return students.get(studentID);
		} else {
			// TODO: this should throw StudentNotFoundException instead of printing an error
			System.out.println("ERROR: Student not found: " + studentID);
		}

		// TODO: if the students collection contains the requested studentId, 
		// TODO: return the corresponding Student object.
		// TODO: otherwise throw StudentNotFoundException
		return null;
	}

	public void enrollStudentInCourse(int studentID, String course) {
		// TODO: if the students collection contains the studentID, and
		// TODO: if the student is not already enrolled in the course,
		// TODO: enroll the student in the course
		// TODO: if the students collection does not contain studentID, throw StudentNotFoundException
		// TODO: if the student is already enrolled in the course throw DuplicateEnrollmentException
	}

	public void dropStudentFromCourse(int studentID, String course) {
		// TODO: if the students collection contains the studentID, and
		// TODO: if the student is already enrolled in the course,
		// TODO: drop the student from the course
		// TODO: if the students collection does not contain studentID, throw StudentNotFoundException
		// TODO: if the student is not enrolled in the course throw MissingEnrollmentException
	}
}
