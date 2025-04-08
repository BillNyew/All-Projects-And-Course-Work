package life6visitor;

public class DieCommand extends LifeCommand {

    // the following constructor creates a DieCommand for a specific cell
    public DieCommand(Cell cell) {
        super(cell);
    }

    // the following method executes the die action on the cell
    @Override
    public void execute() {
        cell.die();
    }
}
