package hw3;


import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class Bird extends Avatar {
    public Bird(TerrainMap terrainMap, GridPoint startingLocation) {
        super(terrainMap, startingLocation);
    }

    @Override
    protected String getSrcImg() {
        return "src/bird.png"; // Correct the path to the bird image file
    }

    @Override
    protected void moveAvatar() {
        // Implement the bird's movement logic here
        Collection<? extends GridPoint> neighbors = location.getNeighbors(1);
        Collections.shuffle((List<?>) neighbors);
        Random random = new Random();
        if (random.nextInt(3) <= 1) {
            for (GridPoint point : neighbors) {
                
                    this.location = point;
                    break; // Bird can only move to one valid location in this case
                }
            
        }
    }
}