package life6visitor;

import java.util.ArrayList;
import java.util.List;

public class GameOfLife {
    private int rows;
    private int cols;
    private Cell[][] grid;
    private List<LifeObserver> observers;

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

    public int getRows() {
        return rows;
    }

    public int getCols() {
        return cols;
    }

    public Cell getCell(int row, int col) {
        return grid[row][col];
    }

    public void attach(LifeObserver observer) {
        observers.add(observer);
    }

    public void detach(LifeObserver observer) {
        observers.remove(observer);
    }

    public void notifyObservers() {
        for (LifeObserver observer : observers) {
            observer.update();
        }
    }

    public void toggle(int row, int col) {
        grid[row][col].toggle();
        notifyObservers();
    }

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
