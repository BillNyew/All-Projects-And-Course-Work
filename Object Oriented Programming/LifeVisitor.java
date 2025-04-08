package life6visitor;

public abstract class LifeVisitor {
    public abstract void visitLiveCell(Cell cell);

    public abstract void visitDeadCell(Cell cell);
}
