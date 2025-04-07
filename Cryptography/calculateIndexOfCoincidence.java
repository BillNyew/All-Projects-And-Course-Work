public static double calculateIndexOfCoincidence(String message) {
    int[] frequency = new int[26];
    int total = 0;

    for (char c : message.toCharArray()) {
        if (Character.isLetter(c)) {
            int index = Character.toLowerCase(c) - 'a';
            frequency[index]++;
            total++;
        }
    }

    double sum = 0;
    for (int f : frequency) {
        sum += (f * (f - 1));
    }

    return sum / (total * (total - 1));
}