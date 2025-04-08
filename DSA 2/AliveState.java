package life6visitor;

public class AliveState implements CellState {
	// the following instance holds the single instance of AliveState
    private static AliveState instance = new AliveState();

    private AliveState() {
    }

    // the following returns the single instance of AliveState
    public static AliveState create() {
        return instance;
    }

    // the following returns true since this state represents an alive cell
    @Override
    public boolean isAlive() {
        return true;
    }

    @Override
    public void live(Cell cell) {
    }

    // the following changes the cell's state to dead
    @Override
    public void die(Cell cell) {
        cell.setState(DeadState.create());
    }
    
    // the following makes it so the cell can accept the visitor
    @Override
    public void accept(LifeVisitor visitor, Cell cell) {
        visitor.visitLiveCell(cell);
    }
}
