package life6visitor;

import java.util.ArrayList;
import java.util.List;

public class Cell {
    private CellState state;
    private List<Cell> neighbors;

    public Cell() {
        this.state = DeadState.create();
        this.neighbors = new ArrayList<>();
    }

    // the following adds a cell to the list of neighbors
    public void addNeighbor(Cell neighbor) {
        neighbors.add(neighbor);
    }

    // the following returns true if the cell is alive and false if it's dead
    public boolean isAlive() {
        return state.isAlive();
    }

    // the following returns the number of alive neighbors
    public int nbrAliveNeighbors() {
        int count = 0;
        for (Cell neighbor : neighbors) {
            if (neighbor.isAlive()) {
                count++;
            }
        }
        return count;
    }

    // the following sets the state of the cell
    public void setState(CellState state) {
        this.state = state;
    }

    // the following sets the cell to alive
    public void live() {
        state = AliveState.create();
    }

    //the following sets the cell to dead
    public void die() {
        state = DeadState.create();
    }
    
    public void toggle() {
        if (isAlive()) {
            state.die(this);
        } 
        else {
            state.live(this);
        }
    }
    
    public void accept(LifeVisitor visitor) {
        if (isAlive()) {
            visitor.visitLiveCell(this);
        } else {
            visitor.visitDeadCell(this);
        }
    }
}
