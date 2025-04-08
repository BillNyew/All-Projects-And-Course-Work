package hw3;

import edu.du.dudraw.Draw;


public abstract class TerrainTile implements Drawable {
    private GridPoint location;
    protected int vegetation; // Amount of vegetation on the tile (0-100)
    protected int wetness;   // Wetness of the tile (0-100)
    protected int bumpiness; // Bumpiness of the tile (0-100)

    protected TerrainTile(GridPoint location) {
        this.location = location;
    }
    public void draw(Draw duDwin) {
        setColor(duDwin); // Set the color first
        duDwin.filledRectangle(location.getx() * 35, location.gety() * 35, 35, 35);
    }
    public abstract void setColor(Draw duDwin);
    
    public int getVeg() {
        return vegetation;
    }

    public int getWet() {
        return wetness;
    }

    public int getBumpy() {
        return bumpiness;
    }

    public void reduceVeg(int amount) {
        vegetation = Math.max(0, vegetation - amount); // Ensure it doesn't go below 0
    }

    // Implement setting the color based on the properties
   

   
}