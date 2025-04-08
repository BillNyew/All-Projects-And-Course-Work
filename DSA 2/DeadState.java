package life6visitor;

public class DeadState implements CellState {
    // the following instance holds the single instance of DeadState
    private static DeadState instance = new DeadState();

    private DeadState() {
    }

    // the following method returns the single instance of DeadState
    public static DeadState create() {
        return instance;
    }

    // the following method returns false since this state represents a dead cell
    @Override
    public boolean isAlive() {
        return false;
    }
    
    // the following method changes the cell's state to alive
    @Override
    public void live(Cell cell) {
        cell.setState(AliveState.create());
    }

    // the following method does nothing since the cell is already dead in this state
    @Override
    public void die(Cell cell) {
    }
    
    // the following is the visitor for the dead cell
    @Override
    public void accept(LifeVisitor visitor, Cell cell) {
        visitor.visitDeadCell(cell);
    }
}
