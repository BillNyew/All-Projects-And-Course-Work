package hw3;

import edu.du.dudraw.Draw;
import java.util.List;
import java.util.ArrayList;

public class Human extends Avatar {
    private GridPoint targetLocation;
    private List<GridPoint>path = new ArrayList<>();// Internal path list for the Human

    protected Human(TerrainMap tm, GridPoint location) {
        super(tm, location);
        this.targetLocation = new GridPoint(3,0);
    	}

    protected String getSrcImg() {
        return "src/human.png"; // Correct the path to the human image file
    }
    public void draw(Draw duDwin) {
        try {
        	if (path.size() > 1) {
        		path = path.subList(1,  path.size());
        		location = new GridPoint (path.get(0).getx(), path.get(0).gety());
        	}
        	duDwin.picture((location.getx() * 35) - 17.5, (location.gety() * 35) +17.5, getSrcImg(), 30, 30);
        } catch (NullPointerException e) {
        	duDwin.picture((location.getx() * 35) - 17.5, (location.gety() * 35) +17.5, getSrcImg(), 30, 30);
        	
        }
        
    }

    @Override
    protected void moveAvatar() {
    	GridPoint moveLoc = new GridPoint ((int)super.x/35 + 1, (int)super.y/35);
        if (!(targetLocation.equals(moveLoc))) {
        	PathFinder pathFinder = new PathFinder(tm);
        	path = pathFinder.findPath(location, moveLoc);
        	targetLocation = moveLoc;
        }
        }
    }

            