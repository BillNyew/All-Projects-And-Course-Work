package hw3;

import edu.du.dudraw.Draw;

public class Water extends TerrainTile{
	
	protected Water(GridPoint location) {
		super(location);
		this.wetness = 100;
		this.vegetation = 0;
		this.bumpiness = 0;
	}

	@Override
	public void setColor(Draw duDwin) {
		//sets tile color
		duDwin.setPenColor(0, 100, 255);
	}

	@Override
	public int getVeg() {
		return vegetation;
	}

	@Override
	public int getWet() {
		return wetness;
	}

	@Override
	public int getBumpy() {
		return bumpiness;
	}
	
}