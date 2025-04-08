package songs;

public class Artist implements Comparable<Artist> {

    private String lastName;
    private String firstName;

    public Artist(String lastName, String firstName) {
        this.lastName = lastName;
        this.firstName = firstName;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Artist artist = (Artist) o;

        return lastName.equals(artist.lastName) &&
                firstName.equals(artist.firstName);
    }

    @Override
    public int hashCode() {
        int result = lastName.hashCode();
        result = 31 * result + firstName.hashCode();
        return result;
    }

    @Override
    public int compareTo(Artist a) {
        int result = lastName.compareTo(a.lastName);
        if (result == 0) {
            result = firstName.compareTo(a.firstName);
        }
        return result;
    }

    @Override
    public String toString() {
        return firstName + " " + lastName;
    }
}
