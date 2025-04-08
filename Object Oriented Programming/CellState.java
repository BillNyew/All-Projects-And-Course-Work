package life6visitor;

public interface CellState {
    boolean isAlive();

    // the following transitions the cell to alive
    void live(Cell cell);

    // the following transitions the cell to dead
    void die(Cell cell);

    // the following is for the visitor 
    void accept(LifeVisitor visitor, Cell cell);
}
