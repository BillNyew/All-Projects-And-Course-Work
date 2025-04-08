package hw3;

import edu.du.dudraw.Draw;

public class Road extends TerrainTile{

	protected Road(GridPoint location) {
		super(location);
		this.wetness = 0;
		this.bumpiness = 60;
		this.vegetation = 0;
	}

	@Override
	public void setColor(Draw duDwin) {
		//sets tile color
		duDwin.setPenColor(255, 255, 0);
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