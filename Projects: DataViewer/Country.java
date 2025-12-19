package dataviewer3;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Country {
    private String name;
    private List<State> states;

    public Country(String name) {
        this.name = name;
        this.states = new ArrayList<>();
    }

	public boolean nameEquals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Country other = (Country) obj;
		return Objects.equals(name, other.name);
	}

	public String getName() {
        return name;
    }

    public List<State> getStates() {
        return states;
    }

    public void addState(State state) {
        states.add(state);
    }

	@Override
	public String toString() {
		return name;
	}
}
