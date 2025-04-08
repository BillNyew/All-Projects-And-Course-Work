
package hw3;

import java.util.Random;

import edu.du.dudraw.Draw;

public class Grass extends TerrainTile{
	private int vegitation;
	protected Grass(GridPoint location) {
		super(location);
		this.wetness = 20;
		this.bumpiness = 40;
		//color variation setting
		Random random = new Random();
		this.vegetation = 90 + random.nextInt(10);
		vegitation = random.nextInt(vegetation) + 55;
	}

	@Override
	public void setColor(Draw duDwin) {
		//sets pen color, with color variation
		duDwin.setPenColor(0, vegitation + (100 - vegetation), 0);		
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