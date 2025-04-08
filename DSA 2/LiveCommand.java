package life6visitor;

public class LiveCommand extends LifeCommand {

    // the following constructor creates a LiveCommand for a specific cell
    public LiveCommand(Cell cell) {
        super(cell);
    }

    // the following method executes the live action on the cell
    @Override
    public void execute() {
        cell.live();
    }
}
