package hw3;

public class Main {

    public static void main(String[] args) throws TerrainFileException, BadAvatarException {
        // Load in the map
    	try {
    		TerrainMap tm = new TerrainMap("map1.txt");
    		// Make the display panel
    		SimWindow window = new SimWindow(tm);
    		// Start the simulation
    		window.runSimulation();
    	
    	} catch (TerrainFileException e) {
    		e.printStackTrace();
    	}
    }
}   