package life6visitor;

public class LiveCommand extends LifeCommand {

    public LiveCommand(Cell cell) {
        super(cell);
    }

    @Override
    public void execute() {
        cell.live();
    }
}
