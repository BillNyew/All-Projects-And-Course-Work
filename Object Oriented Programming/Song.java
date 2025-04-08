package songs;

public class Song implements Comparable<Song> {

    private String title;
    private Artist artist;
    private int runningTime; // in seconds

    public Song(String title, Artist artist, int runningTime) {
        this.title = title;
        this.artist = artist;
        this.runningTime = runningTime;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Song song = (Song) o;

        return title.equals(song.title) &&
                artist.equals(song.artist) &&
                runningTime == song.runningTime;
    }

    @Override
    public int hashCode() {
        int result = title.hashCode();
        result = 31 * result + artist.hashCode();
        result = 31 * result + runningTime;
        return result;
    }

    @Override
    public int compareTo(Song s) {
        int result = artist.compareTo(s.artist);
        if (result == 0) {
            result = title.compareTo(s.title);
            if (result == 0) {
                result = Integer.compare(runningTime, s.runningTime);
            }
        }
        return result;
    }

    @Override
    public String toString() {
        return title + " (" + runningTime + ") by " + artist;
    }
}
