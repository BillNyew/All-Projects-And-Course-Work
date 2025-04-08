package hw3;
import java.util.Random;

import edu.du.dudraw.Draw;

public class Mountain extends TerrainTile{
	
	private int vegitation;
	protected Mountain(GridPoint location) {
		super(location);
		this.wetness = 30;
		this.vegetation = 50;
		this.bumpiness = 100;
		//color variation setting
		Random random = new Random();
		vegitation = random.nextInt(vegetation) + 50;
	}
	
	@Override
	public void setColor(Draw duDwin) {
		//sets color with color variation
		duDwin.setPenColor(100, vegitation + (50 - vegetation), 100);		
		
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
