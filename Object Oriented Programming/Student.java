package class4_1;

import java.util.List;

interface Student {
	void enroll(String course);
	void drop(String course);
	List<String> getEnrolledCourses();
}

