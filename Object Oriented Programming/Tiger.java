package hw3;

import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class Tiger extends Avatar {
    protected Tiger(TerrainMap tm, GridPoint location) {
        super(tm, location);
    }

    protected String getSrcImg() {
        return "src/tiger.png"; // Correct the path to the tiger image file
    }    

    @Override
    protected void moveAvatar() {
    	Collection<? extends GridPoint> neighbor = location.getNeighbors(1);
    	Collections.shuffle((List<?>) neighbor);
    	Random random = new Random();
    	if (random.nextInt(4) <= 1) {
    		for (GridPoint item : neighbor) {
    			if((tm.getBumpy(item) == 100)) {
					this.location = item;
    			}
    		}
    	}
    }
}