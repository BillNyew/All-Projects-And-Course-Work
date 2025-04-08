package songs;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.TreeMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeSet;

public class Driver {
	
	Map<Artist, ArrayList<Song>> theArtists;
	
	public void testingConsistency() {
		// Testing of compareTo directly
		System.out.println("-----Testing of equals/compareTo consistency-----");
		Song s1 = new Song("Hello", new Artist("John", "Smith"), 100);
		Song s2 = new Song("Hello", new Artist("John", "Smith"), 200);
		System.out.println("S1 is " + s1);
		System.out.println("S2 is " + s2);
		
		// See what equals says about Songs
		if (s1.equals(s2)) {
			System.out.println("S1 equals S2");
		} else {
			System.out.println("S1 not equals S2");
		}
		
		// See what compareTo says about Songs
		if (s1.compareTo(s2) == 0) {
			System.out.println("S1 compareTo S2 says 0 (Same)");
		} else {
			System.out.println("S1 compareTo S2 says Pos/Neg (Different)");
		}
		
		// Put Songs into an ArrayList
		ArrayList<Song> theSongs1 = new ArrayList<Song>();
		theSongs1.add(s1);
		theSongs1.add(s2);
		boolean c1 = theSongs1.contains(new Song("Hello", new Artist("John", "Smith"), 300));
		System.out.println("Contains from ArrayList: " + c1);
		
		// Put Songs into a TreeSet
		TreeSet<Song> theSongs2 = new TreeSet<Song>();
		theSongs2.add(s1);
		theSongs2.add(s2);
		boolean c2 = theSongs2.contains(new Song("Hello", new Artist("John", "Smith"), 300));
		System.out.println("Contains from TreeSet: " + c2);
	}
	
	public void loadData(String filename) {
		System.out.println("-----Loading Data From File-----");
		
		theArtists = new TreeMap<Artist, ArrayList<Song>>();
		//theArtists = new HashMap<Artist, ArrayList<Song>>();
		
		try {
			File f = new File(filename);
			Scanner sc = new Scanner(f);
		
			while (sc.hasNextLine()) {			
				String sTitle = sc.next();
				String aFirst = sc.next();
				String aLast = sc.next();
				int runningTime = sc.nextInt();
				
				// Create the new Artist
				Artist a = new Artist(aFirst, aLast);
				
				// See if the artist is already one we have seen
				if (!theArtists.containsKey(a)) {
					// If not then add them in with an empty song list
					theArtists.put(a, new ArrayList<Song>());
				}
				
				// Create the Song
				Song s = new Song(sTitle, a, runningTime);
				
				// Add the Song to the song list
				theArtists.get(a).add(s);
				
			}
			sc.close();
		
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}
	
	public void displaySongs(Artist a) {
		System.out.println("-----Displaying Artist Songs-----");
		
		// Look up the songs by the given artist
		List<Song> artistSongs = theArtists.get(a);
		
		if (artistSongs == null) {
			System.out.println("Artist has no Songs");
			
		} else {
			System.out.println("Songs before sorting: " + artistSongs);
			
			// Sort them
			Collections.sort(artistSongs);

			System.out.println("Songs after sorting: " + artistSongs);
		}
	}

	public static void main(String[] args) {
		Driver d = new Driver();
		
		d.testingConsistency();
		
		//d.loadData("src/songs/songs.txt");
		
		//d.displaySongs(new Artist("Peter", "Parker"));
	}

}



