package hw3;

import edu.du.dudraw.Draw;
import java.util.HashMap;
import java.util.Map;
import java.io.File;
import java.util.Scanner;
import java.io.FileNotFoundException;

public class TerrainMap implements Drawable {
    private Map<GridPoint, TerrainTile> theTiles;

    // public static constants set in the constructor.
    public static int gridWidth;
    public static int gridHeight;

    // Constructor to read from file
    public TerrainMap(String filename) throws TerrainFileException {
        //makes the map a HashMap
        theTiles = new HashMap<GridPoint, TerrainTile>();

        try {
            //scans in the values from the file
            Scanner scan = new Scanner(new File("src/" + filename));
            //if statements for catching if a size bound is correct or not (in the case its not an int)
            if (scan.hasNextInt()) {
                gridWidth = scan.nextInt();
            } else {
                throw new MalformedTerrainFileException("First element is not an integer");
            }
            if (scan.hasNextInt()) {
                gridHeight = scan.nextInt();
            } else {
                throw new MalformedTerrainFileException("Second element is not an integer");
            }
            //Proceeds past the first line in the file
            scan.nextLine();

            //iterator for the tiles
            for (int height = 0; height < gridHeight; height++) {
                //reads each letter line in the file
                String line = scan.nextLine();
                System.out.println(line);
                //strips all the spaces from between each letter
                line = line.replaceAll("\\s", "");
                for (int width = 0; width < gridWidth; width++) {
                    //gets each char in each string
                    char letter = line.charAt(width);
                    //sets a grid point location for each tile, with proper spacing
                    GridPoint point = new GridPoint(width + 1, gridHeight - height - 1);
                    // Use the TerrainTileFactory to create the terrain tile based on the letter
                    TerrainTile terrainTile = TerrainTileFactory.newTerrainTile(String.valueOf(letter), point);
                    theTiles.put(point, terrainTile);
                }
            }
        } catch (FileNotFoundException e) {
            //error checking for lost files
            e.printStackTrace();
            throw new TerrainFileException("File not found");
        }
    }

    public void draw(Draw duDwin) {
        System.out.println("Called DRAW in terrainMap");
        for (int y = 0; y < gridHeight; y++) {
            for (int x = 0; x < gridWidth; x++) {
                GridPoint gridP = new GridPoint(x + 1, gridHeight - y - 1);
                theTiles.get(gridP).draw(duDwin);
            }
        }
    }

    public int getVeg(GridPoint location) {
        TerrainTile tile = theTiles.get(location);
        return (tile != null) ? tile.getVeg() : 0; // Return 0 if no tile is found
    }

    public int getWet(GridPoint location) {
        TerrainTile tile = theTiles.get(location);
        return (tile != null) ? tile.getWet() : 0; // Return 0 if no tile is found
    }

    public int getBumpy(GridPoint location) {
        TerrainTile tile = theTiles.get(location);
        return (tile != null) ? tile.getBumpy() : 0; // Return 0 if no tile is found
    }
    public void reduceVeg(GridPoint location) {
        TerrainTile tile = theTiles.get(location);
         	tile.reduceVeg(5); // Return 0 if no tile is found
    }
}