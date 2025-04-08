package life6visitor;

import java.awt.Color;
import edu.du.dudraw.Draw;
import edu.du.dudraw.DrawListener;

public class GameOfLifeUI implements LifeObserver, DrawListener {
    private int width;
    private int height;
    private Draw window;
    private GameOfLife game;

    // the following constructor initializes the UI with a game instance and window dimensions
    public GameOfLifeUI(GameOfLife game, int width, int height) {
        this.game = game;
        this.width = width;
        this.height = height;
        this.window = new Draw("The Game of Life 6 Visitor");
        window.setCanvasSize(width, height);
        window.setXscale(0, width);
        window.setYscale(0, height);
        window.addListener(this);
        game.attach(this);
        update();
    }

    // the following method updates the UI to reflect the current state of the game
    @Override
    public void update() {
        window.clear(Color.white);
        drawGrid();
        drawLives();
    }

    // the following draws the grid lines on the board
    private void drawGrid() {
        window.setPenColor(Color.black);
        
        // the following calculates cell width and height
        int rows = game.getRows();
        int cols = game.getCols();
        int cellWidth = width / cols;
        int cellHeight = height / rows;

        // the following draws the horizontal lines 
        for (int i = 0; i <= rows; i++) {
            window.line(0, i * cellHeight, this.width, i * cellHeight);
        }

        //the following draws vertical lines
        for (int i = 0; i <= cols; i++) {
            window.line(i * cellWidth, 0, i * cellWidth, this.height);
        }
    }

    // the following fills in the cells on the board that are alive with red
    private void drawLives() {
        int rows = game.getRows();
        int cols = game.getCols();
        int cellWidth = width / cols;
        int cellHeight = height / rows;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
            	// draw the alive cells as red
                if (game.getCell(i, j).isAlive()) {
                    window.setPenColor(Color.RED);
                    window.filledRectangle((j * cellWidth) + (cellWidth / 2), (i * cellHeight) + (cellHeight / 2), cellWidth / 2, cellHeight / 2);
                }
            }
        }
    }

    // Below are the mouse/key listeners

    @Override
    public void keyPressed(int key) {
		// This is the advance button
		// Only advance for spacebar (ascii 32)
        if (key == 32) {
            game.advance();
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

	// the following will bring a cell to life or kill it 
    @Override
    public void mousePressed(double x, double y) {
        int cellWidth = width / game.getCols();
        int cellHeight = height / game.getRows();
        int row = (int) (y / cellHeight);
        int col = (int) (x / cellWidth);
        game.toggle(row, col);
    }

    @Override
    public void mouseReleased(double x, double y) {
    	// Do nothing
    }
}

