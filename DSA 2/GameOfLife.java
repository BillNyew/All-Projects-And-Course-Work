package life6visitor;

import java.util.ArrayList;
import java.util.List;

//Game of life main app using DuDraw
//Use mouse clicks to toggle cells
//Use spacebar to advance game

public class GameOfLife {
    private int rows;
    private int cols;
    private Cell[][] grid;
    private List<LifeObserver> observers;

    // the following constructor initializes the game with a specified number of rows and columns
    public GameOfLife(int rows, int cols) {
        this.rows = rows;
        this.cols = cols;
        this.grid = new Cell[rows][cols];
        this.observers = new ArrayList<>();
        setupGrid(grid);
    }

    // the following method sets up the grid with cells and their neighbors
    private void setupGrid(Cell[][] g) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                g[i][j] = new Cell();
            }
        }

        // the following initializes neighbors for each cell
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                for (int rowOffset = -1; rowOffset <= 1; rowOffset++) {
                    for (int colOffset = -1; colOffset <= 1; colOffset++) {
                        if (rowOffset == 0 && colOffset == 0) 
                        	continue;
                        int newRow = (i + rowOffset + rows) % rows;
                        int newCol = (j + colOffset + cols) % cols;
                        g[i][j].addNeighbor(g[newRow][newCol]);
                    }
                }
            }
        }
    }

    // the following method returns the number of rows in the grid
    public int getRows() {
        return rows;
    }

    // the following method returns the number of columns in the grid
    public int getCols() {
        return cols;
    }

    // the following method returns the cell at the specified row and column
    public Cell getCell(int row, int col) {
        return grid[row][col];
    }

    // the following method registers an observer to be notified of state changes
    public void attach(LifeObserver observer) {
        observers.add(observer);
    }

    // the following method unregisters an observer from notifications
    public void detach(LifeObserver observer) {
        observers.remove(observer);
    }

    // the following method notifies all registered observers of a state change
    public void notifyObservers() {
        for (LifeObserver observer : observers) {
            observer.update();
        }
    }

    // the following method toggles the state of the cell at the specified row and column and notifies observers
    public void toggle(int row, int col) {
        grid[row][col].toggle();
        notifyObservers();
    }

    // the following method advances the state of the game by one step and notifies observers
    public void advance() {
        LifeVisitor visitor = new StandardLifeVisitor();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                Cell cell = grid[i][j];
                cell.accept(visitor);
            }
        }
        
        notifyObservers();
    }
}
