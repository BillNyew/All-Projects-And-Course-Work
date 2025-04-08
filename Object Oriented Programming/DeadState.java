package life6visitor;

public class DeadState implements CellState {
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

    @Override
    public void die(Cell cell) {
    }
    
    @Override
    public void accept(LifeVisitor visitor, Cell cell) {
        visitor.visitDeadCell(cell);
    }
}
