package dataviewer3;

public class ExtremaVisState implements VisState{

	@Override
	public String toString() {
		return "Extrema (within 10% of min/max) ";
	}

	@Override
	public VisState Raw() {
		return new RawVisState();
	}

	@Override
	public VisState Extrema() {
		return this;
	}

	@Override
	public boolean isRaw() {
		return false;
	}

}
