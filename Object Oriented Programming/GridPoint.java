package hw3;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;


public class GridPoint implements Comparable<GridPoint> {
    private int x;
    private int y;

    public GridPoint(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public int getx() {
        return x;
    }

    public int gety() {
        return y;
    }

    
    public String toString() {
        return "(" + x + ", " + y + ")";
    }

    public int hashCode() {
        return toString().hashCode();
    }

    public boolean equals(Object o) {
        if (o instanceof GridPoint) {
        	GridPoint gridPoint = (GridPoint) o;
        	return x == gridPoint.x && y == gridPoint.y;
        }
        return false;
        
    }


   
    public int compareTo(GridPoint that) {
        if ( x != that.x) {
            if (x < that.x) {
            	return -1;
            } else {
            	return 1;
            }
        } else if (y != that.y) {
            if (y < that.y) {
                return -1;
            } else {
                return 1;
            }
        }
        return 0;
    }
    
	public Collection<? extends GridPoint> getNeighbors(int levels) {
		List<GridPoint> neighbors = new ArrayList<GridPoint>();
        for (int dx = -levels; dx <= levels; dx++) {
            for (int dy = -levels; dy <= levels; dy++) {

                if ((getx() + dx > 0 && gety() + dy > -1) && (getx() + dx < TerrainMap.gridWidth && gety() + dy < TerrainMap.gridHeight)) {
                    GridPoint surroundingPoint = new GridPoint(getx() + dx, gety() + dy);
                    neighbors.add(surroundingPoint);
                    
                    }
                }
            }
        return neighbors;
	}
}
