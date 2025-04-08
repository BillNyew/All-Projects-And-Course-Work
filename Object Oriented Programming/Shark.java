package hw3;

public class Shark extends Fish {
	protected Shark(GridPoint location, TerrainMap tm) {
		super(tm, location);
	}
	@Override
	protected String getSrcImg() {
		return "src/shark.png";
	}
}
