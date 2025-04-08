package life4command;

import java.awt.Color;
import edu.du.dudraw.Draw;
import edu.du.dudraw.DrawListener;
import java.util.List;
import java.util.ArrayList;

public class GameOfLifeApp implements DrawListener {
    private int width;
    private int height;
    private Draw window;
    private int rows;
    private int cols;
    private Cell grid[][]; // Use Cell objects instead of booleans
    
    
    public GameOfLifeApp(String title, int rows, int cols, int width, int height) {
        this.rows = rows;
        this.cols = cols;
        this.width = width;
        this.height = height;
        
        
        this.grid = new Cell[rows][cols]; // Initialize the grid with Cell objects
        setGrid(this.grid);
        
        
        window = new Draw(title);
        window.setCanvasSize(width, height);
        window.setXscale(0, width);
        window.setYscale(0, height);
        window.addListener(this);
        update();
    }
    private void setGrid(Cell[][] grid2) {
    	for(int i = 0; i < rows; i++) {
    		for(int j = 0; j<cols; j++) {
    			grid2[i][j]= new Cell();
    		}
    	}
    	for (int r = 0; r < rows; r++) {
    		for (int c = 0; c < cols; c++) {
    			int x = 0;
    			int y =  r - 1;
    			if (y < 0) {
    				y= rows - 1;
    			}
    			for (int rCt = 1; rCt <= 3; rCt++) {
    				x = c-1;
    				if (x<0) {
    					x= cols -1;
    				}
    				for (int cCt = 1; cCt<=3; cCt++) {
    					if (x!= c|| y !=r) {
    						grid2[r][c].addNeighbor(grid2[y][x]);
    					}
    					x=(x+1)%cols;
    				}
    				y=(y+1)%rows;
    		
    			}
    		}
    	}
    }
   

    
    private void drawGrid() {
        
    	window.setPenColor(Color.black);
 		
        int cellWidth = width / cols;
        int cellHeight = height / rows;
     
        for (int i = 0; i <= rows; i++) {
        	window.line(0, i * cellHeight, this.width, i * cellHeight);
        }
        
        for (int i = 0; i <= cols; i++) {
        	window.line(i * cellWidth, 0, i * cellWidth, this.height);
        }
    }
     
    private void drawLives() {
    	int cellWidth = width / cols;
        int cellHeight = height / rows;
        
    	window.setPenColor(Color.red);
        for (int i = 0; i < rows; i++) {
        	for (int j = 0; j < cols; j++) {
        		if (grid[i][j].isAlive()) {
        			// This is the center and half width/height
        			window.filledRectangle((j * cellWidth)+(cellWidth/2), (i * cellHeight)+(cellHeight/2), cellWidth/2, cellHeight/2);
                }
            }
        }
    }
   
    // This method implements the rules of the Game of Life. For each cell,
    //   we simple find the number of neighbors and then bring the cell to life
    //   if appropriate.
    public void advance() {
        List<LifeCommand> commands = new ArrayList<>();
        int n = 0;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                Cell cell = grid[i][j];
                n = cell.nbrAliveNeighbors();

                if (cell.isAlive()) {
                    if (n != 2 && n != 3) {
                        // Add a DieCommand to the list
                        commands.add(new DieCommand(cell));
                    }
                } else {
                    if (n == 3) {
                        // Add a LiveCommand to the list
                        commands.add(new LiveCommand(cell));
                    }
                }
            }
        }

        // Execute the commands
        for (LifeCommand command : commands) {
            command.execute();
        }
        
        // After executing the commands, update the window to reflect the changes
        update();
    }
	            
	        
	    


    // Below are the mouse/key listeners
    
	@Override
	public void keyPressed(int key) {
		// This is the advance button
		// Only advance for spacebar (ascii 32)
		if (key==32) {
			advance();
		}
	}

	@Override
	public void keyReleased(int key) {
		// Do nothing
	}

	@Override
	public void keyTyped(char key) {
		// Do nothing
	}

	@Override
	public void mouseClicked(double arg0, double arg1) {
		// Do nothing
	}

	@Override
	public void mouseDragged(double x, double y) {
		// Do nothing
	}

	@Override
	public void mousePressed(double x, double y) {
		// This is the toggle of grid locations
		int cellWidth = width / cols;
        int cellHeight = height / rows;
        
        int cellLocRow = (int)(y / cellHeight);
        int cellLocCol = (int)(x / cellWidth);
       
		if(grid[cellLocRow][cellLocCol].isAlive()) {
			grid[cellLocRow][cellLocCol].die();
		} else {
			grid[cellLocRow][cellLocCol].live();
		}
		update();
	}

	@Override
	public void mouseReleased(double x, double y) {
		// Do nothing
	}

	@Override
	public void update() {
		// Redraw the entire board
		window.clear(Color.white);  // Clear in white
	 	drawGrid();
	 	drawLives();
	}
        
}