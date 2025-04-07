package dataviewer3;

public class RawVisState implements VisState{

	@Override
	public String toString() {
		return "Raw ";
	}

	@Override
	public VisState Raw() {
		return this;
	}

	@Override
	public VisState Extrema() {
		return new ExtremaVisState();
	}

	@Override
	public boolean isRaw() {
		return true;
	}

}
