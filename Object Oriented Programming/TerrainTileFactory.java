package hw3;

public class TerrainTileFactory {

	public static TerrainTile newTerrainTile(String valueOf, GridPoint point) throws InvalidTerrainTypeException{
		switch (valueOf) {
        case "g":
            return new Grass(point);
        case "w":
            return new Water(point);
        case "r":
            return new Road(point);
        case "m":
            return new Mountain(point);
        default:
            throw new InvalidTerrainTypeException("Invalid terrain type: " + valueOf);
    }
	}
}
