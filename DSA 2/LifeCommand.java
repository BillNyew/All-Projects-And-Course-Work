package life6visitor;

public abstract class LifeCommand {
    protected Cell cell;

    // the following constructor initializes the command with a specific cell
    public LifeCommand(Cell cell) {
        this.cell = cell;
    }

    // the following method is an abstract execution behavior that subclasses must implement
    public abstract void execute();
}
