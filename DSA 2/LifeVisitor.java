package life6visitor;

public abstract class LifeVisitor {
    // the following method is for processing live cells
    public abstract void visitLiveCell(Cell cell);

    // the following method is for processing dead cells
    public abstract void visitDeadCell(Cell cell);
}
