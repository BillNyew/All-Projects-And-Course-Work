package hw3;

import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class Rabbit extends Avatar {
    protected Rabbit(TerrainMap terrainMap, GridPoint startingLocation) {
        super(terrainMap, startingLocation);
    }
    
    protected String getSrcImg() {
        return "src/rabbit.png"; // Correct the path to the rabbit image file
    }
    

    @Override
	protected void moveAvatar() {
		Collection<? extends GridPoint> neighbor = location.getNeighbors(1);
		Collections.shuffle((List<?>) neighbor);
		
		
		for (GridPoint point : neighbor) {
			if ((tm.getVeg(point) > tm.getVeg(location))){
				
			    this.location = point;
				Random random = new Random();
				if (random.nextInt(3) <= 1) {
					tm.reduceVeg(point);
				}
			}else {
				tm.reduceVeg(location);
			}
		}
		
	}
}