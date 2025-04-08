package hw3;

public class AvatarFactory {
    public static Avatar newAvatar(String avaName, TerrainMap tm, GridPoint loc) throws BadAvatarException {
        if (avaName.equalsIgnoreCase("Tiger")) {
            return new Tiger(tm, loc);
        } else if (avaName.equalsIgnoreCase("Rabbit")) {
            return new Rabbit(tm, loc);
        } else if (avaName.equalsIgnoreCase("Cod")) {
            return new Cod(loc, tm);
        } else if (avaName.equalsIgnoreCase("Shark")) {
            return new Shark(loc, tm);
        } else if (avaName.equalsIgnoreCase("Bird")) {
            return new Bird(tm, loc);
        } else if (avaName.equalsIgnoreCase("Human")) {
            return new Human(tm, loc);
        } else {
            throw new BadAvatarException("Invalid avatar name: " + avaName);
        }
    }
}