void rearrangePoints(Point[] points, Line line) {
    int pivotIndex = partition(points, line);
    int startAbove = 0;
    int startBelow = pivotIndex;
    int endBelow = points.length - 1;
    
    while (startAbove < startBelow && startBelow <= endBelow) {
        while (startAbove < startBelow && compareToLine(points[startAbove], line) >= 0) {
            startAbove++;
        }
        while (startBelow <= endBelow && compareToLine(points[endBelow], line) < 0) {
            endBelow--;
        }
        if (startAbove < startBelow && startBelow <= endBelow) {
            swap(points, startAbove, endBelow);
            startAbove++;
            endBelow--;
        }
    }
}

int partition(Point[] points, Line line) {
    int left = 0;
    int right = points.length - 1;
    while (left <= right) {
        while (left <= right && compareToLine(points[left], line) < 0) {
            left++;
        }
        while (left <= right && compareToLine(points[right], line) >= 0) {
            right--;
        }
        if (left < right) {
            swap(points, left, right);
            left++;
            right--;
        }
    }
    return left;
}

void swap(Point[] points, int i, int j) {
    Point temp = points[i];
    points[i] = points[j];
    points[j] = temp;
}