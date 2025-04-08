package hw3;

import edu.du.dudraw.Draw;

public abstract class Avatar implements Drawable {
    protected TerrainMap tm;
    protected GridPoint location;
    protected double x;
    protected double y;
    
    protected Avatar(TerrainMap tm, GridPoint location) {
    	this.location = location;
        this.tm = tm;
    }

	public void draw(Draw duDwin) {
    	duDwin.picture((location.getx() * 35) - 17.5, (location.gety() * 35) + 17.5, getSrcImg(),30, 30);
    }
    protected abstract String getSrcImg();
    protected abstract void moveAvatar();
    
    public void ProcessEvent(Draw duDwin) {
    	x = duDwin.mouseX();
    	x = duDwin.mouseY();
    }
}