package hw3;

import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.Random;


public class Fish extends Avatar {
    public Fish(TerrainMap terrainMap, GridPoint startingLocation) {
        super(terrainMap, startingLocation);
    }

    @Override
    protected String getSrcImg() {
    	return null;
    }

	@Override
	protected void moveAvatar() {
		Collection<? extends GridPoint> neighbor = location.getNeighbors(1);
		Collections.shuffle((List<?>) neighbor);
		Random random = new Random();
		if (random.nextInt(3) <= 1) {
			for (GridPoint point : neighbor) {
				if((tm.getWet(point) == 100)) {
					this.location = point;
				}
			}
		}
		
	}
}