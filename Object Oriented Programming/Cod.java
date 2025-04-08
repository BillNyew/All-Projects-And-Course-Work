package hw3;


public class Cod extends Fish {
	protected Cod(GridPoint location, TerrainMap tm) {
		super(tm, location);
	}
	@Override
	protected String getSrcImg() {
		return "src/cod.png";
	}
}

